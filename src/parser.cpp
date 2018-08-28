#include <iostream>
#include <assert.h>
#include <ctype.h>
#include <cstdlib>
#include "parser.h"

using std::cin;
using std::cout;
using std::endl;

// Parser::Parser(Scanner &scanner,SymbolTable &symTab):_scanner(scanner),_symTab(symTab) {
// 	cout<<"Parser Created"<<endl;
// }

// Parser::~Parser() {
// 	cout<<"Destroying Parser"<<endl;
// }

// Status Parser::Eval() {
// 	cout<<"Parser Eval"<<endl;

// 	for(Etoken token=_scanner.Token();token!=tEnd;_scanner.Accept()) {
// 		token = _scanner.Token();
// 		switch(token) {
// 			case tMult:
// 			cout<<"Times\n";
// 			break;

// 			case tPlus:
// 			cout<<"Plus\n";
// 			break;

// 			case tNumber:
// 			cout<<"Number: "<<_scanner.Number()<<endl;
// 			break;

// 			case tEnd:
// 			cout<<"End\n";
// 			return stQuit;

// 			case tError:
// 			cout<<"Error\n";
// 			return stQuit;

// 			default:
// 			cout<<"Error: Bad Token\n";
// 			return stQuit;
// 		}
// 	}

// 	return stOK;
// }



Parser::Parser(Scanner &scanner,Store &store,FunctionTable &funTab,SymbolTable &symTab):_scanner(scanner),
_pTree(0),_status(stOK),_funTab(funTab),_store(store),_symTab(symTab){}


Parser::~Parser() {
	delete _pTree;
}

Status Parser::Eval() {
	Parse();
	if(_status==stOK) 
		Execute();
	else
		_status=stQuit;
	return _status;
}

void Parser::Execute() {
	if(_pTree) {
		double result = _pTree->Calc();
		std::cout<<" "<<result<<std::endl;
	}
}


void Parser::Parse() {
	_pTree = Expr();
}

Node *Parser::Expr() {
	Node *pNode = Term();
	Etoken  token = _scanner.Token();
	if(token==tPlus) {
		_scanner.Accept();
		Node *pRight = Expr();
		pNode = new AddNode(pNode,pRight);
	} else if(token==tMinus) {
		_scanner.Accept();
		Node *pRight = Expr();
		pNode = new SubNode(pNode,pRight);
	} else if(token==tAssign) {
		_scanner.Accept();
		Node *pRight = Expr();
		if(pNode->IsLvalue()) {
			pNode = new AssignNode(pNode,pRight);
		} else {
			_status = stError;
			delete pNode;
			pNode = Expr();
		}
	}
	return pNode;
}

Node *Parser::Term() {
	Node *pNode=Factor();
	if(_scanner.Token()==tMult) {
		_scanner.Accept();
		Node *pRight=Term();
		pNode=new MultNode(pNode,pRight);
	} else if(_scanner.Token()==tDivide) {
		_scanner.Accept();
		Node *pRight=Term();
		pNode=new DivideNode(pNode,pRight);
	}
	return pNode;
}

Node *Parser::Factor() {
	Node *pNode;
	Etoken token=_scanner.Token();
	if(token==tLParen) {
		_scanner.Accept();
		pNode=Expr();
		if(_scanner.Token()!=tRParen) 
			_status=stError;
		else 
			_scanner.Accept();
	} else if(token==tNumber) {
		pNode = new NumNode(_scanner.Number());
		_scanner.Accept();
	} else if(token==tIdent) {
		int maxSymlen=100; //note here..
		char strSymbol[maxSymlen];
		int lenSym=maxSymlen;
		_scanner.GetSymbolName(strSymbol,lenSym);
		int id = _symTab.Find(strSymbol);
		_scanner.Accept();
		if(_scanner.Token()==tLParen) {
			_scanner.Accept();
			pNode = Expr();
			if(_scanner.Token()==tRParen)
				_scanner.Accept();
			else 
				_status=stError;
			if(id!=idNotFound && id<_funTab.Size()) {
				pNode=new FunNode(_funTab.GetFun(id),pNode);
			} else {
				std::cout<<"Unknown function\"";
				std::cout<<strSymbol<<"\"\n";
			}
		} else {
			if(id==idNotFound)
				id=_symTab.ForceAdd(strSymbol,lenSym);
			pNode=new VarNode(id,_store);
		}
	} else if(token==tMinus) {
		_scanner.Accept();
		pNode = new UMinusNode(Factor());
	} else {
		_scanner.Accept();
		_status=stError;
		pNode=0;
	}
	return pNode;
} 

