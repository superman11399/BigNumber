#pragma one
#include <string>
#include "QFloat.h"
#include "Q.h"

void QFloat::InputUnsignedDec(string s){
	int i = s.find('.');
	string pn = s.substr(0, i);	//phần nguyên
	string tp = s.substr(i + 1);//phần thập phân
	QInt a;
	a.Input(10, pn);
	pn = a.ToBin();				//phần nguyên sang nhị phân
	tp = SauThapPhanToBin(tp);	//phần tp sang nhị phân
	int n = pn.length();		
	if (n > 1 || (n == 1 && pn[0] == '1')){	//phần nguyên >=1
		int t = n - 1;			//dời dấu chấm sang trái ngay sau bit 1 đầu tiên của pn
		QInt khong(10, "16383");	//=2^14-1 (Số 0 ở dạng biased 15bit 
		/*for (int j = 0; j < t; j++){	
			
		}*/
		QInt tmp(10, to_string(t));
		QInt mu;
		mu = khong + tmp;		//thì cộng vào số mũ
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
			tp = pn.erase(0, 1) + tp;	//xóa bit 1 đầu (trước dấu chấm), r nối vs tp
		}
	}
	else{	//phần nguyên =0 -> số mũ âm (biased)
		int pos = 1;	//vị trí bit 1 đầu tiên trong tp
		while (tp[pos-1] == '0'&&pos-1 < tp.length())
			pos++;
		QInt khong(10, "16383");	//=2^14-1 (Số 0 ở dạng biased 15bit 
		QInt tmp(10, to_string(pos));
		QInt mu;
		mu = khong - tmp;	//dời dấu phẩy qua phải nên số mũ =0-pos
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
	s.erase(0, 1);
	InputUnsignedDec(s);
	data[0] = SetBit(data[0], 0, 1);
}
void QFloat::InputDec(string s){
	if (s[0] == '-')
		InputSignedDec(s);
	else InputUnsignedDec(s);
}
void QFloat::InputBin(string s){
	int n = s.length() - 1;
	for (int i = 0; i <= n; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, s[i] - '0');
}
bool QFloat::chuan(){		//15 bit 0 -> k chuẩn
	for (int i = 1; i <= 15;i++)
	if (GetBit(data[i / 32], i % 32))
		return true;
	return false;
}
bool QFloat::inf(){		//15 bit 1 -> Số vô cực ?
	for (int i = 1; i <= 15; i++)
	if (!GetBit(data[i / 32], i % 32))
		return false;
	return true;
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
string QFloat::ToDec(){	//dạng X*2^e 
	string kq;
	QInt khong(10, "16383");
	string mu_tmp;		
	for (int i = 1; i <= 15; i++)	//lấy chuỗi bit 1-15
		mu_tmp += to_string(GetBit(data[i / 32], i % 32));
	QInt m(2, mu_tmp);
	QInt mu_kq;
	if (m > khong){	//nếu số mũ >0
		mu_kq = m - khong;
		mu_tmp = mu_kq.ToDec();
	}
	else {		//số mũ âm
		mu_kq = khong - m;
		mu_tmp = "-"+mu_kq.ToDec();
	}
	int pos = 127;	//vị trí cuối cùng khác 0 ở phần trị
	string tmp;		//chuỗi phần trị
	
	while (GetBit(data[pos / 32], pos % 32) == 0 && pos >= 16) 
		pos--;		
	for (int i = 16; i <= pos; i++)		//đưa phần trị vào chuỗi
		tmp += to_string(GetBit(data[i / 32], i % 32));
	//if (pos == 15) tmp = "0";	//phần trị toàn 0
	int mu = pos - 16 + 1;
	if (chuan()){	//Nếu dạng chuẩn   1.f * 2^e
		tmp.insert(0, "1");	//thêm bit 1 đầu (1f)
		//cout << mu_tmp << " " << mu << endl;
		mu_tmp = to_string(stoi(mu_tmp)- mu);
		//dời dấu phẩy qua phải nên số mũ trừ đi số bit dời
		
	}
	else if (inf())
		if (pos==15)		//121 bit trị = 0 
			return "infinity and beyond!";
		else return "Error";
	else {	// Dạng k chuẩn  0.f * 2^e  (e<0)
		tmp.insert(0, "0");	//thêm bit 0 đầu (0f)
		mu_tmp = "-" + to_string(16382 + mu);
		//dời dấu phẩy qua phải nên - (mũ + số bit dời)
	}
	QInt a(2, tmp);	//chuyển phần trị (1f/0f) về thập phân 
	kq = a.ToDec() + "* 2^" + mu_tmp;
	if (GetBit(data[0], 0)) kq.insert(0, "-");	//nếu âm thêm dấu -
	return kq;
}