#include <math.h>
#include <iostream>
#include <assert.h>
#include "store.h"


Store::Store(int size,SymbolTable &symTab):_size(size) {
	_cell = new double[size];
	_status = new unsigned char[size];
	for(int i=0;i<size;i++) {
		_status[i] = stNotInit;
	}
	int id = symTab.ForceAdd("e",1);
	SetValue(id,exp(1));
	id = symTab.ForceAdd("pi",2);
	SetValue(id,2.0*acos(0.0));
}

FunctionTable::FunctionTable(SymbolTable &_symTab,FunctionEntry funArr[]):_size(0) {
	for(int i=0;i<maxIdFun;i++) {
		int len=strlen(funArr[i].strFun);
		if(len==0)
			break;

		_pFun[i]=funArr[i].pFun;
		int j=_symTab.ForceAdd(funArr[i].strFun,len);
		assert(i==j);
		++_size;
	}
}

