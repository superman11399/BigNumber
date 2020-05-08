#include <string>
#include "Q.h"
#include "Func.h"

void QInt::SetBitFromBin(bool* bin){
	for (int i = 0; i < 128; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, bin[i]);
}

ostream& operator << (ostream&os, QInt p){
	int pos = 0;
	while (!GetBit(p.data[pos / 32], pos % 32))
		pos++;
	while (pos < 128){
		os << GetBit(p.data[pos / 32], pos % 32);
		pos++;
	}
	return os;
}


void QInt::Input(){
	string s; getline(cin, s);
	bool* bin;
	chuyenNhiPhan(s, bin);
	this->SetBitFromBin(bin);
}
void QInt::PrintBin(){
	//cout << *this << endl;
	int pos = 0;
	while (!GetBit(this->data[pos / 32], pos % 32))
		pos++;
	while (pos < 128){
		cout << GetBit(this->data[pos / 32], pos % 32);
		pos++;
	}
	cout << endl;
}
void QInt::PrintDec(){
	string kq = "0";
	for (int i = 0; i < 127; i++)
	if (GetBit(data[(i + 1) / 32], (i + 1) % 32))
		kq = Cong2Chuoi(kq, LuyThua2(126-i));
	if (GetBit(data[0], 0) == 1){
		kq = Tru2Chuoi(LuyThua2(127), kq);
		kq.insert(0, "-");
	}
	cout << kq;
}

int& QInt::operator[](int ind)
{
    return data[ind];
}

QInt& QInt::operator=(QInt a)
{
    for (int i=0;i<4;i++)
        (*this)[i]=a[i];
    return *this;
}

QInt QInt::operator&(QInt a)
{
    QInt tmp=*this;
    for (int i=0;i<4;i++)
    {
        tmp[i]=tmp[i]&a[i];
    }
    return tmp;
}

QInt QInt::operator|(QInt a)
{
      QInt tmp=*this;
       for (int i=0;i<4;i++)
       {
           tmp[i]=tmp[i]|a[i];
       }
       return tmp;
}

QInt QInt::operator^(QInt a)
{
      QInt tmp=*this;
       for (int i=0;i<4;i++)
       {
           tmp[i]=tmp[i]^a[i];
       }
       return tmp;
}

QInt QInt::operator~()
{
      QInt tmp=*this;
       for (int i=0;i<4;i++)
       {
           tmp[i]=~tmp[i];
       }
       return tmp;
}

QInt QInt::operator>>(int a)
{
    QInt tmp=*this;
    if (a<0) return tmp<<(-a);
    if (a<=32)
    {
        for (int i=3;i>0;i--)
        {
            tmp[i]=(tmp[i]>>a)|(tmp[i-1]<<(32-a));
        }
        tmp[0]=tmp[0]>>a;
    }
    else
    {
        for (int i=3;i>0;i--)
              {
                  tmp[i]=tmp[i-1];
              }
        tmp[0]=tmp[0] < 0 ? -1 : 0;
        tmp=tmp>>(a-32);
    }
    return tmp;
}

QInt QInt::operator<<(int a)
{
    QInt tmp=*this;
    if (a<0) return tmp>>(-a);
    if (a<=32)
    {
        for (int i=0;i<4;i++)
        {
            tmp[i]=(tmp[i]<<a)|(tmp[i+1]>>(32-a));
        }
    }
    else
    {
        for (int i=0;i<4;i++)
              {
                  tmp[i]=tmp[i+1];
              }
        tmp[3]=0;
        tmp=tmp<<(a-32);
    }
    return tmp;
}

QInt QInt::operator+(QInt a)
{
    QInt tmp1=*this;
    QInt zero;
    QInt carry;
    while (a!=zero)
    {
        carry= tmp1 & a;
        tmp1=tmp1^a;
        carry=carry<<1;
        a = carry;
    }
    return tmp1;
}


QInt QInt::operator-(QInt a)
{
    
    QInt bu(1);
    a= ~a + bu;
    
    return *this+a;
}

bool QInt::operator!=(QInt a)
{
    QInt tmp=*this;
    for (int i=0;i<4;i++)
        if (tmp[i]!=a[i]) return true;
    return false;
}
