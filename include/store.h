#ifndef STORE_H
#define STORE_H

#include <math.h>
#include <iostream>
#include "symboltable.h"

enum {
	stInit,
	stNotInit
};

class Store {
public:
	Store(int size,SymbolTable &symTab);
	~Store() {
		delete [] _cell;
		delete [] _status;
	}

	bool IsInit(int id) const {
		return (id<_size && _status[id] != stNotInit);
	}

	double Value(int id) const {
		assert(IsInit(id));
		return _cell[id];
	}

	void SetValue(int id,double val) {
		if(id<_size) {
			_cell[id] = val;
			_status[id] = stInit;
		}
	} 
private:
	int _size;
	double *_cell;
	unsigned char *_status;
};

typedef double(*PtrFun)(double);

struct FunctionEntry {
	PtrFun pFun;
	char *strFun;
};


const int maxIdFun = 16;


class FunctionTable {
public:
	FunctionTable(SymbolTable &_symTab,FunctionEntry funArr[]);
	int Size() const { return _size; }
	PtrFun GetFun(int id) const {
		return _pFun[id];
	}
private:
	PtrFun _pFun[maxIdFun];
	int _size;
};



#endif 