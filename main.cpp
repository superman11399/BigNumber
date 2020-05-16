#include <iostream>
#include <string>
#include "Q.h"
#include "Func.h"
#include "QFloat.h"
using namespace std;

int main(){
		
	QFloat a;
	string s; getline(cin, s);
	a.InputUnsignedDec(s);
	cout << a.ToBin() << endl;

	

    return 0;
}
