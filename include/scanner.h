#ifndef SCANNER_H
#define SCANNER_H

enum Etoken {
	tEnd,
	tError,
	tNumber,
	tPlus,
	tMult,
	tMinus,
	tDivide,
	tLParen,
	tRParen,
	tAssign,
	tIdent
};

class Scanner {
public:
	Scanner(const char *buf);
	Etoken Token() const {
		return _token;
	}
	void Accept();
	double Number() {
		assert(_token == tNumber);
		return _number;
	}
	void GetSymbolName(char *strOut,int &len);
private:
	const char *const _buf;
	void EatWhite();
	int _iLook;
	Etoken _token;
	double _number;
	int _lenSymbol;
	int _iSymbol;
};

#endif