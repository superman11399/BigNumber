#pragma once
#include <iostream>
using namespace std;
class QInt{
	int data[4];
public:
	QInt(){
		for (int i = 0; i < 4; i++)
			data[i] = 0;
	}
    QInt (int n)
    {
      for (int i = 0; i < 3; i++)
        data[i] = 0;
        data[3]=n;
    }
	friend ostream& operator << (ostream&os, QInt p);
	void SetBitFromBin(bool* bin);
	void Input();
	void PrintDec();	//in chuỗi thập phân
	void PrintBin();	//in chuỗi nhị phân
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
      
      QInt operator>>(int n);
      QInt operator<<(int n);
      
      bool operator<(QInt a);
      bool operator<=(QInt a);
      bool operator>(QInt a);
      bool operator>=(QInt a);
      bool operator!=(QInt a);
      bool operator==(QInt a);
};
