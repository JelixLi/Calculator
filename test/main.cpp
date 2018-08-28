#include <iostream>
#include <assert.h>
#include <ctype.h>
#include <cstdlib>
#include "common.h"


double Cotan(double x) {
	double y = tan(x);
	if(y==0) {
		std::cout<<"cotan of "<<x<<" undefined\n";
		return HUGE_VAL;
	}
	return 1.0 / y;
}


using std::cin;
using std::cout;
using std::endl;


const int maxBuf = 100;
const int maxSymbols = 40;

FunctionEntry funArr[maxIdFun] = {
	log,"log",
	log10,"log10",
	exp,"exp",
	sqrt,"sqrt",
	sin,"sin",
	cos,"cos",
	tan,"tan",
	Cotan,"cotan",
	sinh,"sinh",
	cosh,"cosh",
	tanh,"tanh",
	asin,"asin",
	acos,"acos",
	atan,"atan",
	0,""
};

int main() {
	char buf[maxBuf];
	Status status;
	SymbolTable symTab(maxSymbols);
	FunctionTable funTab(symTab,funArr);
	Store store(maxSymbols,symTab);
	do {
		cout<<">";
		cin.getline(buf,maxBuf);
		Scanner scanner(buf);
		Parser parser(scanner,store,funTab,symTab);
		status = parser.Eval();
	}while(status != stQuit);

}
