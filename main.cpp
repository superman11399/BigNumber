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
   /* qi.Input();
    qi.PrintBin();
    qi=qi>>33;
    qi.PrintBin();
    qi=qi<<32;
    qi.PrintBin();
    */
    
    //qi.Input();
    //qi.PrintBin();
    //qo.Input();
    //qo.PrintBin();
    //QInt sum=qi+qo;
    //sum.PrintBin();
    //QInt sub=qi-qo;
    //sub.PrintBin();
    //QInt product=qi*qo;
    //product.PrintBin();
    
    cout << "Nhap so 1: ";
    qi.Input();
    cout << "Nhap so 2: ";
    qo.Input();
    qi.PrintBin();
    cout << endl;
    (qi.ror()).PrintBin();
    cout << endl;
    (qi.rol()).PrintBin();

    cout << endl;
    (qi / qo).PrintDec();

}
