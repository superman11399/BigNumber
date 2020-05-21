#pragma once
#include <iostream>
#include "Func.h"
using namespace std;

class QInt{
	int data[4];
public:
	QInt(){
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}
    QInt(int type, string s) : QInt()
    {
		Input(type, s);
    }
	friend ostream& operator << (ostream&os, QInt p);

	void SetBitFromBin(bool* bin);
	void InputBin(string s);
	void InputUnsignedDec(string s);
	void InputSignedDec(string s);
	void InputHex(string s);

	void Input(int mode, string s);
    void ScanQInt();

	string ToDec();	//in chuỗi thập phân
	string ToBin();	//in chuỗi nhị phân
	string ToHex();	//in chuỗi thập lục phân
	string Output(int mode);
    int demBit();
	int GetMyBit(int pos);
	bool bang0();	//toàn bit 0
	~QInt(){}
    
    QInt& operator=(QInt a);
      
    int& operator[](int ind);
      
    QInt operator&(QInt a);
    QInt operator|(QInt a);
    QInt operator^(QInt a);
    QInt operator~();
      
    QInt operator+(QInt a);
    QInt operator-(QInt a);
    QInt operator*(QInt a);
    QInt operator/(QInt a);

    QInt ror();
    QInt rol();
      
    QInt operator>>(int n);
    QInt operator<<(int n);
      
    bool operator<(QInt a);
    bool operator<=(QInt a);
    bool operator>(QInt a);
    bool operator>=(QInt a);
    bool operator!=(QInt a);
    bool operator==(QInt a);
  
};
