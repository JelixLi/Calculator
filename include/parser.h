#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "Node.h"

enum Status
{
	stOK,
	stQuit,
	stError
};


class Parser {
public:
	Parser(Scanner &scanner,Store &store,FunctionTable &funTab,SymbolTable &symTab);
	~Parser();

	Status Eval();
private:
	void Parse();
	Node *Expr();
	Node *Term();
	Node *Factor();
	void Execute();

	Scanner &_scanner;
	Node *_pTree;
	Status _status;
	Store &_store;
	SymbolTable &_symTab;
	FunctionTable &_funTab;
};


#endif