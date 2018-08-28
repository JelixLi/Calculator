#ifndef NODE_H
#define NODE_H

#include <assert.h>
#include "store.h"

class Node {
public:
	virtual ~Node(){}
	virtual double Calc() const = 0;
	virtual bool IsLvalue() const {
		return false;
	}
	virtual void Assign(double value){}
};


class NumNode:public Node {
public:
	NumNode(double num):_num(num) {}
	double Calc() const {
		return _num;
	}
private:
	const double _num;
};

	
class BinNode:public Node {
public:
	BinNode(Node *pLeft,Node *pRight):_pLeft(pLeft),_pRight(pRight) {}
	~BinNode() {
		delete _pLeft;
		delete _pRight;
	}

protected:
	const Node *_pLeft;
	const Node *_pRight;
};

class UniNode:public Node {
public:
	UniNode(Node *pNode):_pNode(pNode) {}
	~UniNode() {
		delete _pNode;
	}

protected:
	const Node *_pNode;
};


class FunNode:public UniNode {
public:
	FunNode(PtrFun pFun,Node *pNode):UniNode(pNode),_pFun(pFun){}
	double Calc() const {
		assert(_pFun != 0);
		return (*_pFun)(_pNode->Calc());
	}
private:
	PtrFun _pFun;
};


class AddNode:public BinNode {
public:
	AddNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight) {}
	double Calc() const;
};

class AssignNode:public BinNode {
public:
	AssignNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight) {
		assert(pLeft->IsLvalue());
	}
	double Calc() const;
};


class MultNode:public BinNode {
public:
	MultNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight){}
	double Calc() const;
};

class VarNode:public Node {
public:
	VarNode(int id,Store &store):_id(id),_store(store) {}
	double Calc() const;
	bool IsLvalue() const;
	void Assign(double val);
private:
	const int _id;
	Store &_store;
};

class SubNode:public BinNode {
public:
	SubNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight) {}
	double Calc() const;
};


class DivideNode:public BinNode {
public:
	DivideNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight) {}
	double Calc() const;
};



class UMinusNode:public UniNode {
public:
	UMinusNode(Node *pNode):UniNode(pNode) {}
	double Calc() const;
};



#endif