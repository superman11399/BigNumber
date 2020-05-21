#pragma once
#include <iostream>
//#include "Q.h"
using namespace std;

int GetBit(int X, int i);
void DocDayBit(int X, int a[32]);
int SetBit1(int X, int i);
int SetBit0(int X, int i);
int SetBit(int X, int i, int gt);
void MySetBit(int &X, int i, int gt);
int BinToDec(int kq[32]);
void XuatMang(int a[], int n);

string chia2(string str);
string chia2_v2(string str);
string nhan2(string str);

string SauThapPhanToBin(string s);	//chuyển phần thập phân thành nhị phân
void chuyenNhiPhan(string &str, bool* &binary);

string Cong2Chuoi(string a, string b);
string Tru2Chuoi(string a, string b);	//a>b
string LuyThua2(int n);
string LuyThuaAm2(int n);
string Cong2ChuoiLuyThuaAm2(string a, string b);