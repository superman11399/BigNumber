#pragma once
#include <iostream>
#include <string>
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
//string chia2_v2(string str)
//{
//	string tmp;
//	tmp.resize(str.length());
//	unsigned short int i = 0, j = 0, k = 0;
//	while (str[i] == '0'&&i < str.length()){
//		tmp[i++] = '0';
//		k++;
//	}
//	if (str[i] - '0' < 2){
//		tmp[i] = '0';
//		i++;
//		j = 10; k = i;
//	}
//	for (; i< str.length(); i++)
//	{
//		tmp[k++] = ((str[i] - '0' + j) / 2 + '0');
//		j = ((str[i] - '0' + j) % 2) * 10;
//	}
//	//tmp.resize(k);
//	return tmp;
//}
string nhan2(string s){
	int nho = 0;
	string kq;
	int n = s.length()-1;
	kq.resize(n + 1);
	for (; n >= 0; n--){
		kq[n] = ((s[n] - '0') * 2 + nho) % 10 + '0';
		nho = ((s[n] - '0') * 2 + nho) / 10;
	}
	if (nho)
		kq.insert(0, "1");
	return kq;
}
bool bang0(string s){	//Chuỗi toàn 0
	int n = s.length();
	for (int i = 0; i < n;i++)
	if (s[i] != '0') return false;
	return true;
}
string SauThapPhanToBin(string s){
	string kq, tmp;
	int n = 111;
	int i = 0;
	while (!bang0(s) && i < n){
		tmp = nhan2(s);
		int m = s.length();
		s = nhan2(s);
		if (tmp.length()>m){
			kq += "1";
			s.erase(0, 1);
		}
		else kq += "0";
		i++;
	}
	return kq;
}
void chuyenNhiPhan(string &str, bool* &binary)
{
	binary = new bool[128];
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

string Cong2Chuoi(string a, string b){
	while (a.length() < b.length())
		a.insert(0, "0");
	while (b.length() < a.length())
		b.insert(0, "0");
	int i = a.length() - 1;
	int nho = 0;
	string kq; kq.resize(i + 1);
	while (i >= 0){
		int tmp = (a[i] + b[i] + nho - 2 * '0');
		kq[i] = tmp % 10 + '0';
		if (tmp>9) nho = 1;
		else nho = 0;
		i--;
	}
	if (nho)
		kq.insert(0, "1");
	return kq;
}
string Tru2Chuoi(string a, string b){	//a>b
	while (b.length() < a.length())
		b.insert(0, "0");
	int nho = 0;
	int i = a.length() - 1;
	string kq; kq.resize(i + 1);
	//if (a[i] - b[i] < 0)
	//	nho = 10;
	while (i >= 0){
		int tmp = a[i] - b[i] - nho;
		if (tmp < 0){
			kq[i] = (tmp + 10) % 10 + '0';
			nho = 1;
		}
		else {
			kq[i] = (tmp) % 10 + '0';
			nho = 0;
		}
		i--;
	}
	return kq;
}
string LuyThua2(int n){
	string kq = "1";
	for (int i = 1; i <= n; i++)
		kq = Cong2Chuoi(kq, kq);
	return kq;
}

//string LuyThuaAm2(int n){  //2^-n	0.25 thì lưu 25
//	
//	string kq = "5";
//	for (int i = 1; i < n; i++){
//		kq += "0";
//		kq = chia2_v2(kq);
//	}
//	return kq;
//}
//string Cong2ChuoiLuyThuaAm2(string a, string b){
//	while (a.length() < b.length())
//		a += "0";
//	while (b.length() < a.length())
//		b += "0";
//	string kq;
//	kq = Cong2Chuoi(a, b);
//	return kq;
//}