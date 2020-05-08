#include <string>
#include "Q.h"
#include "Func.h"

void QInt::SetBitFromBin(bool* bin){
	for (int i = 0; i < 128; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, bin[i]);
}

ostream& operator << (ostream&os, QInt p){
	int pos = 0;
	while (!GetBit(p.data[pos / 32], pos % 32))
		pos++;
	while (pos < 128){
		os << GetBit(p.data[pos / 32], pos % 32);
		pos++;
	}
	return os;
}


void QInt::Input(){
	string s; getline(cin, s);
	bool* bin;
	chuyenNhiPhan(s, bin);
	this->SetBitFromBin(bin);
}
void QInt::PrintBin(){
	//cout << *this << endl;
	int pos = 0;
	while (!GetBit(this->data[pos / 32], pos % 32))
		pos++;
	while (pos < 128){
		cout << GetBit(this->data[pos / 32], pos % 32);
		pos++;
	}
	cout << endl;
}
void QInt::PrintDec(){
	string kq = "0";
	for (int i = 0; i < 127; i++)
	if (GetBit(data[(i + 1) / 32], (i + 1) % 32))
		kq = Cong2Chuoi(kq, LuyThua2(126-i));
	if (GetBit(data[0], 0) == 1){
		kq = Tru2Chuoi(LuyThua2(127), kq);
		kq.insert(0, "-");
	}
	cout << kq;
}