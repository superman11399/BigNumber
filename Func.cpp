#pragma once
#include <iostream>

#include "Q.h"
#include "Func.h"
using namespace std;
int GetBit(int X, int i){
	return (X >> (31 - i)) & 1;
}
void DocDayBit(int X, int a[32]){
	for (int i = 0; i < 32; i++)
		a[i] = GetBit(X, i);
}
int SetBit1(int X, int i){
	return  X | (1 << (31 - i));
}
int SetBit(int X, int i, int gt){
	return  X | (gt << (31 - i));
}
int BinToDec(int kq[32]){
	int X = 0;
	for (int i = 0; i < 32; i++){
		if (kq[i] == 1)
			X = SetBit1(X, i);
	}
	return X;
}
void XuatMang(int a[], int n){
	for (int i = 0; i < n; i++)
		cout << a[i];
}
string chia2(string str)
{
	string tmp;
	unsigned short int i = 0, j = 0, k = 0;
	tmp.resize(str.length());
	if (str[0] - '0' < 2){
		i = 1;
		j = 10;
	}
	for (; i< str.length(); i++)
	{
		tmp[k++] = ((str[i] - '0' + j) / 2 + '0');
		j = ((str[i] - '0' + j) % 2) * 10;
	}
	tmp.resize(k);
	return tmp;
}

void chuyenNhiPhan(string &str, int* &binary)
{
	binary = new int[128];
	for (int i = 0; i < 128; i++)
		binary[i] = 0;
	unsigned short int i;
	for (i = 0; str.length() != 0; i++){
		if ((str[str.length() - 1] - '0') % 2 != 0){
			binary[i] = 1;
			str[str.length() - 1] -= 1;
		}
		else binary[i] = 0;
		str = chia2(str);
	}
	reverse(binary, binary + 128);
}

