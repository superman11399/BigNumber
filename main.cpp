#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
#include "QFloat.h"
using namespace std;

int main(){
		
	QFloat a;
	string s; getline(cin, s);
	a.InputDec(s);
	//a.InputBin(s);
	cout << a.ToBin() << endl;
	cout << a.ToDec() << endl;

	//string s; getline(cin, s);
	//cout << SauThapPhanToBin(s);


    return 0;
}
