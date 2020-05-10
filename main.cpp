#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
using namespace std;

int main(){
		
	 QInt qa,qb;
	 string s; getline(cin, s);
	 qa.InputHex(s);
	 string t; getline(cin, t);
	 qb.InputUnsignedDec(t);
	 QInt qc;
	 qc = qa + qb;
	 ////qc.InputSignedDec(s);
	 qc.PrintBin();
	 //
	 ////qc.PrintBin();
	 qc.PrintDec(); cout << endl;

	 qa.PrintBin();
	 cout<<qa.PrintHex(); cout << endl;
	 qb.PrintBin();
	 qb.PrintDec(); cout << endl;

    return 0;
}
