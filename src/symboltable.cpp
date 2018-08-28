#include <assert.h>
#include "symboltable.h"

const List& HTable::Find(const char *str) const {
	int i = hash(str);
	return _aList[i];
}

void HTable::Add(const char *str,int id) {
	int i = hash(str);
	_aList[i].Add(id);
}

int HTable::hash(const char *str) const {
	assert(str!=0 && str[0]!=0);
	unsigned h = str[0];
	for(int i=1;str[i]!=0;i++) {
		h = (h<<4) + str[i];
	}
	return h % _size;
}


void List::Add(int id) {
	Link *pLink = new Link(_pHead,id);
	_pHead = pLink;
}


SymbolTable::SymbolTable(int size):_curId(0),_maxId(size),_htab(size+1),_strBuf(size*10) {
	_offStr = new int[size];
}

SymbolTable::~SymbolTable() {
	delete [] _offStr;
}

int SymbolTable::ForceAdd(const char *str,int len) {
	// int len = strlen(str);
	if(_curId==_maxId || !_strBuf.WillFit(len)) {
		return idNotFound;
	}
	_offStr[_curId] = _strBuf.GetOffset();
	_strBuf.Add(str);
	_htab.Add(str,_curId);
	++_curId;
	return _curId-1;
}

int SymbolTable::Find(const char *str) const {
	const List &list = _htab.Find(str);
	for(const Link *pLink=list.GetHead();pLink!=0;pLink=pLink->Next()) {
		int id = pLink->Id();
		int offstr = _offStr[id];
		if(_strBuf.IsEqual(offstr,str))
			return id;
	}
	return idNotFound;
}

const char* SymbolTable::GetString(int id) const {
	assert(id>=0);
	assert(id<_curId);
	int offstr = _offStr[id];
	return _strBuf.GetString(offstr);
}