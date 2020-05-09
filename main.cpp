#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
using namespace std;

int main(){
		
	/*string a;
	getline(cin, a);
	string b;
	getline(cin, b);
	string c = Cong2Chuoi(a, b);
	string c = Tru2Chuoi(a, b);*/
	//cout << c << endl;
	
    QInt qi,qo;
  /*  qi.Input();
    qi.PrintBin();
    qi=qi>>2;
    qi.PrintBin();
    qi=qi<<2;
    qi.PrintBin();*/
    qi.Input();
    qi.PrintBin();
    qo.Input();
    qo.PrintBin();
    QInt sum=qi+qo;
    sum.PrintBin();
    QInt sub=qi-qo;
    sub.PrintBin();
}
