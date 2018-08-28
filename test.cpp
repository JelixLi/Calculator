#include <iostream>
#include <cstdio>
#include <math.h>


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



class AddNode:public BinNode {
public:
	AddNode(Node *pLeft,Node *pRight):BinNode(pLeft,pRight) {}
	double Calc() const;
};




int main() {
	Node A;
	Node B;
	Node *C=new AddNode(A,B);
}