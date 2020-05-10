#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
using namespace std;

void main(){
		
	 //QInt qa,qb;
	 //string s; getline(cin, s);
	 //qa.InputUnsignedDec(s);
	 //string t; getline(cin, t);
	 //qb.InputUnsignedDec(t);
	 //QInt qc;
	 //qc = qa + qb;
	 ////qc.InputSignedDec(s);
	 //qc.PrintBin();
	 //
	 ////qc.PrintBin();
	 //qc.PrintDec(); cout << endl;

	 //qa.PrintBin();
	 //qa.PrintDec(); cout << endl;
	 //qb.PrintBin();
	 //qb.PrintDec(); cout << endl;

	 //qa= qa << 2; qb= qb >> 3;

	 //qa.PrintBin(); 
	 //qa.PrintDec(); cout << endl;

	 //qb.PrintBin(); 
	 //qb.PrintDec(); cout << endl;

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
    
	//qi.ScanQInt();
	//cout << "----------------------\n";
	//qi.PrintBin();
	//qo.ScanQInt();
 //   qo.PrintBin();
	//cout << "----------------------\n";

	QInt a; //A đóng vai trò số dư
//dùng để khởi tạo a vối 128 bit 1.
	bool* bitfull1 = new bool[128];
	for (int i = 1; i < 128; i++)
		bitfull1[i] = 1;
	bitfull1[0] = 0;

	a.SetBitFromBin(bitfull1);
	delete[]bitfull1;

	a.PrintDec();
	a.PrintBin();

	cout << "\n----------------------\n";

	(a + a).PrintBin();
	(a + a).PrintDec();
    //tràn cmnr
	//Thử với - xem s
	bitfull1 = new bool[128];
	for (int i = 1; i < 128; i++)
		if (i % 2 == 0)
			bitfull1[i] = 0;
		else
			bitfull1[i] = 1;

	QInt b;
	bitfull1[0] = 0;
	b.SetBitFromBin(bitfull1);
	delete[]bitfull1;

	b.PrintBin();
	b.PrintDec();

	cout << "\n----------------------\n";

	(b + b).PrintBin();
	(b + b).PrintDec();
}
