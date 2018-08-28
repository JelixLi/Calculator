#include <iostream>
#include <assert.h>
#include <ctype.h>
#include <cstdlib>
#include <string.h>
#include "scanner.h"

using std::cin;
using std::cout;
using std::endl;

const int maxSymLen = 100;


Scanner::Scanner(const char *buf):_buf(buf),_iLook(0) {
	// cout<<"Scanner with \""<<buf<<"\""<<endl;
	Accept();
}

void Scanner::Accept() {
	EatWhite();
	switch(_buf[_iLook]) {
		case '+':
		_token = tPlus;
		_iLook++;
		break;		

		case '*':
		_token = tMult;
		_iLook++;
		break;

		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
		case '.':
		{
			char *p;
			_token = tNumber;
			_number = std::strtod(&_buf[_iLook],&p);
			_iLook = p - _buf;
		}
		break;

		case '(':
		_token = tLParen;
		_iLook++;
		break;

		case ')':
		_token = tRParen;
		_iLook++;
		break;

		case '\0':
		_token = tEnd;
		_iLook++;
		break;

		case '=':
		_token=tAssign;
		_iLook++;
		break;

		default:
		if(std::isalpha(_buf[_iLook])||_buf[_iLook]=='_') {
			_token = tIdent;
			_iSymbol = _iLook;

			int cLook;
			do {
				++_iLook;
				cLook = _buf[_iLook];
			} while(std::isalnum(cLook)||_buf[cLook]=='_');

			_lenSymbol = _iLook - _iSymbol;
			
			if(_lenSymbol >= maxSymLen) {
				_lenSymbol = maxSymLen - 1;
			}
		} else 
			_token = tError;
		break;
	}
}

void Scanner::EatWhite() {
	while(isspace(_buf[_iLook]))
		_iLook++;
}

void Scanner::GetSymbolName(char *strOut,int &len) {
	assert(len>=maxSymLen);
	assert(_lenSymbol<=maxSymLen);

	strncpy(strOut,&_buf[_iSymbol],_lenSymbol);
	strOut[_lenSymbol] = '\0';
	len = _lenSymbol;
}


