#pragma one
#include <string>
#include "QFloat.h"
#include "Q.h"

void QFloat::InputUnsignedDec(string s){
	int i = s.find('.');
	string pn = s.substr(0, i);
	string tp = s.substr(i + 1);
	QInt a;
	a.Input(10, pn);
	pn = a.ToBin();
	tp = SauThapPhanToBin(tp);
	int n = pn.length();
	if (n > 1 || (n == 1 && pn[0] == '1')){	//phần nguyên >=1
		int t = n - 1;
		QInt khong(10, "16383");	//=2^14-1 (Số 0 ở dạng biased 15bit 
		for (int j = 0; j < t; j++){	
			
		}
		QInt tmp(10, to_string(t));
		QInt mu;
		mu = khong + tmp;
		string m=mu.ToBin();
		//SetBit cho phần mũ (dương biased)
		if (m.length()>15){	//độ dài chuỗi mũ lớn hơn 15
			//mu.Input(10, to_string(65535)); 
			//2^16-1 (15 bit 1)
			for (int i = 1; i <= 15; i++){	//số vô cùng
				data[i / 32] = SetBit(data[i / 32], i % 32, 1);
				return;
			}
		}
		else{	//biểu diễn được
			for (int i = 1; i <= 15; i++)	//bit 1-15 là của phần mũ
				data[i / 32] = SetBit(data[i / 32], i % 32, mu.GetMyBit(127 - 15 + i));
			tp = pn.erase(0, 1) + tp;
		}
	}
	else{	//phần nguyên =0 -> số mũ âm (biased)
		int pos = 1;	//vị trí bit 1 đầu tiên trong tp
		while (tp[pos-1] == '0'&&pos-1 < tp.length())
			pos++;
		QInt khong(10, "16383");	//=2^14-1 (Số 0 ở dạng biased 15bit 
		QInt tmp(10, to_string(pos));
		QInt mu;
		mu = khong - tmp;
		string m = mu.ToBin();
		
		if (pos - 16382 > 112){	//Số mũ quá âm, underflow
			for (int i = 1; i <= 15; i++){	//số zero
				data[i / 32] = SetBit(data[i / 32], i % 32, 0);
				return;
			}
		}
		else if (pos - 16382 >0){	//Dạng k chuẩn (pos - 16382 <= 112)
			for (int i = 1; i <= 15; i++)	// phần mũ =0
				data[i / 32] = SetBit(data[i / 32], i % 32, 0);
			tp.erase(0, 16382);	//bỏ 16382 bit đầu phần trị
		}
		else{	//biểu diễn được dạng chuẩn (pos<16382)
			for (int i = 1; i <= 15; i++)	//bit 1-15 là của phần mũ
				data[i / 32] = SetBit(data[i / 32], i % 32, mu.GetMyBit(127 - 15 + i));
			tp = tp.erase(0, pos); //viết lại từ bit sau pos vào phần trị
		}
	}
	for (int i = 16; i <= 127 && (i - 16) < tp.length(); i++)	// Set Bit phần trị
		data[i / 32] = SetBit(data[i / 32], i % 32, tp[i - 16] - '0');
}
void QFloat::InputSignedDec(string s){

}
void QFloat::InputBin(string s){
	int n = s.length() - 1;
	for (int i = 0; i <= n; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, s[i] - '0');
}
string QFloat::ToBin(){
	//cout << *this << endl;
	int pos = 0;
	string kq;
	while (pos < 128){
		kq += to_string(GetBit(this->data[pos / 32], pos % 32));
		pos++;
	}
	return kq;
}