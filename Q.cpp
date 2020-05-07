#include <string>
#include "Q.h"
#include "Func.h"

void QInt::SetBitFromBin(int* bin){
	for (int i = 0; i < 128; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, bin[i]);
}

ostream& operator << (ostream&os, QInt p){
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 32; j++)
		os << GetBit(p.data[i], j);
	return os;
}


void QInt::Input(){
	string s; getline(cin, s);
	int* bin;
	chuyenNhiPhan(s, bin);
	this->SetBitFromBin(bin);
}
void QInt::Output(){
	cout << *this << endl;
}