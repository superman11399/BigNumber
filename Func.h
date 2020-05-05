#pragma once
#include <iostream>
#include "Q.h"
using namespace std;

int GetBit(int X, int i);
void DocDayBit(int X, int a[32]);
int SetBit1(int X, int i);
int SetBit(int X, int i, int gt);
int BinToDec(int kq[32]);
void XuatMang(int a[], int n);

string chia2(string str);
void chuyenNhiPhan(string &str, int* &binary);


void ScanQInt(QInt &x);
void PrintQInt(QInt x);