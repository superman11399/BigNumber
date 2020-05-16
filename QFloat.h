#pragma once
#include "Func.h"
using namespace std;

class QFloat{
	int data[4];
public:
	QFloat(){
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}
	
	friend ostream& operator << (ostream&os, QFloat p);

	void SetBitFromBin(bool* bin);
	void InputBin(string s);
	void InputUnsignedDec(string s);
	void InputSignedDec(string s);


	string ToBin();	//in chuỗi nhị phân
	string ToDec();
	~QFloat(){}

	QFloat operator&(QFloat a);
	QFloat operator|(QFloat a);
	QFloat operator^(QFloat a);
	QFloat operator~();

	QFloat operator+(QFloat a);
	QFloat operator-(QFloat a);
	QFloat operator*(QFloat a);
	QFloat operator/(QFloat a);

	

	QFloat operator>>(int n);
	QFloat operator<<(int n);


};