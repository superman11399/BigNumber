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
        switch (type)
        {
                // Hệ thập phân
            case 10:
            {
                bool* bin;
                chuyenNhiPhan(s, bin);
                this->SetBitFromBin(bin);
                break;
            }
        }
    }
	friend ostream& operator << (ostream&os, QInt p);

	void SetBitFromBin(bool* bin);
	void InputUnsignedDec(string s);
	void InputSignedDec(string s);
    void ScanQInt();

	void PrintDec();	//in chuỗi thập phân
	void PrintBin();	//in chuỗi nhị phân
    int demBit();
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
