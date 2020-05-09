#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
using namespace std;

void main(){
		
	 QInt qa,qb;
	 string s; getline(cin, s);
	 qa.InputUnsignedDec(s);
	 string t; getline(cin, t);
	 qb.InputUnsignedDec(t);
	 QInt qc;
	 qc = qa + qb;
	 //qc.InputSignedDec(s);
	 qc.PrintBin();
	 
	 //qc.PrintBin();
	 qc.PrintDec(); cout << endl;

	 qa.PrintBin();
	 qa.PrintDec(); cout << endl;
	 qb.PrintBin();
	 qb.PrintDec(); cout << endl;

	 qa= qa << 2; qb= qb >> 3;

	 qa.PrintBin(); 
	 qa.PrintDec(); cout << endl;

	 qb.PrintBin(); 
	 qb.PrintDec(); cout << endl;

	/*string a;
	getline(cin, a);
	string b;
	getline(cin, b);
	string c = Cong2Chuoi(a, b);
	string c = Tru2Chuoi(a, b);*/
	//cout << c << endl;
    
    QInt qi,qo;
   /* qi.Input();
    qi.PrintBin();
    qi=qi>>33;
    qi.PrintBin();
    qi=qi<<32;
    qi.PrintBin();
    */
    
    qi.Input();
    qi.PrintBin();
    qo.Input();
    qo.PrintBin();
    QInt sum=qi+qo;
    sum.PrintBin();
    QInt sub=qi-qo;
    sub.PrintBin();
    QInt product=qi*qo;
    product.PrintBin();
    
}
