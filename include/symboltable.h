#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string.h>

// const int maxBufSize = 500;

class StringBuffer {
public:
	explicit StringBuffer(int size):_curoffset(0),_size(size){
		_buf = new char[size];
	}

	~StringBuffer() {
		delete [] _buf;
	}

	bool WillFit(int len) const {
		return _curoffset+len+1<_size;
	}

	void Add(const char *str) {
		strcpy(_buf+_curoffset,str);
		_curoffset += strlen(str) + 1;
	}

	int GetOffset() const {
		return _curoffset;
	}

	bool IsEqual(int offStr,const char *str) const {
		const char *strStored = &_buf[offStr];
		return strcmp(str,strStored)==0;
	}

	const char *GetString(int offstr) const {
		return &_buf[offstr];
	}

private:
	char *_buf;
	int _size;
	int _curoffset;
};

class Link {
public:
	Link(Link *pNext,int id):_pNext(pNext),_id(id){}
	~Link() {
		if(_pNext)
			delete _pNext;
	}
	Link *Next() const { return _pNext; }
	int Id() const { return _id; }
private:
	int _id;
	Link *_pNext;
}; 

class List {
public:
	List():_pHead(0){}
	~List() {
		if(_pHead)
			delete _pHead;
	}

	void Add(int id);
	const Link *GetHead() const { return _pHead; }
private:
	Link *_pHead;
};

// const int sizeHTable = 127;

class HTable {
public:
	explicit HTable(int size):_size(size) {
		_aList = new List[size];
	}
	~HTable() {
		delete [] _aList;
	}

	const List &Find(const char *str) const;
	void Add(const char *str,int id);
private:
	int hash(const char *str) const;
	List *_aList; 
	int _size;
};

const int idNotFound = -1;

class SymbolTable {
public:
	explicit SymbolTable(int size);
	~SymbolTable();

	int ForceAdd(const char *str,int len);
	int Find(const char *str) const;
	const char* GetString(int id) const;
private:
	HTable _htab;
	int _maxId;
	int *_offStr;
	int _curId;
	StringBuffer _strBuf;
};

#endif 