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
	friend ostream& operator << (ostream&os, QInt p);
	void SetBitFromBin(int* bin);
	void Input();
	void Output();
	~QInt(){}
};