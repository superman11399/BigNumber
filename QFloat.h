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
	QFloat(int type, string s) : QFloat()
	{
		Input(type, s);
	}
	friend ostream& operator << (ostream&os, QFloat p);
	int layMu();
	//void SetBitFromBin(bool* bin);
	void InputBin(string s);
	void InputUnsignedDec(string s);
	void InputSignedDec(string s);
	void InputDec(string s);
	void Input(int mode, string s);

	void SetMyBit(int pos, int bit);
	bool chuan();  //dạng chuẩn ?
	bool bang0();
	bool inf();
	bool am();
	string ToBin();	//in chuỗi nhị phân
	string ToDec();
	string Output(int mode);
	~QFloat(){}
	
	QFloat& operator=(QFloat a);
	int& operator[](int ind);

	QFloat operator+(QFloat a);
	QFloat operator-(QFloat a);
	QFloat operator*(QFloat a);
	QFloat operator/(QFloat a);



};