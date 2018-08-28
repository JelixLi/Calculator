#include <iostream>
#include "Node.h"

double MultNode::Calc() const {
	return _pLeft->Calc()*_pRight->Calc();
}

double AssignNode::Calc() const {
	double x=_pRight->Calc();
	_pLeft->Assign(x);
	return x;
}

double VarNode::Calc() const {
	double x = 0.0;
	if(_store.IsInit(_id))
		x = _store.Value(_id);
	else 
		std::cout<<"Use of uninitialized variable\n";
	return x;
}

void VarNode::Assign(double val) {
	_store.SetValue(_id,val);
}

bool VarNode::IsLvalue() const {
	return true;
}


double SubNode::Calc() const {
	return _pLeft->Calc() - _pRight->Calc();
}


double DivideNode::Calc() const {
	return _pLeft->Calc() / _pRight->Calc();
}

double UMinusNode::Calc() const{
	return -_pNode->Calc();
}


double AddNode::Calc() const {
	return _pLeft->Calc()+_pRight->Calc();
}