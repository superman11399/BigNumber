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
void QFloat::Input(int mode, string s){
	switch (mode){
	case 2:{		//Hệ nhị phân
			   InputBin(s);
			   break;
	}
	case 10:{		//Hệ thập phân
				if (s[0] == '-')
					InputSignedDec(s);
				else InputUnsignedDec(s);
				break;
	}
	default:
		break;
	}
}
void QFloat::SetMyBit(int pos, int bit){
	data[pos / 32] = SetBit(data[pos / 32], pos % 32, bit);
}
bool QFloat::chuan(){		//15 bit 0 -> k chuẩn
	for (int i = 1; i <= 15;i++)
	if (GetBit(data[i / 32], i % 32))
		return true;
	return false;
}
bool QFloat::bang0(){
	for (int i = 1; i <= 127; i++)
	if (GetBit(data[i / 32], i % 32))
		return false;
	return true;
}
bool QFloat::inf(){		//15 bit 1 -> Số vô cực ?
	for (int i = 1; i <= 15; i++)
	if (!GetBit(data[i / 32], i % 32))
		return false;
	return true;
}
bool QFloat::am(){		//có âm k ?
	return GetBit(data[0], 0);
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
	string mu_tmp = to_string(layMu());
	
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
int QFloat::layMu(){
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
		mu_tmp = "-" + mu_kq.ToDec();
	}
	return stoi(mu_tmp);
}
string QFloat::Output(int mode){
	switch (mode)
	{
	case 2:
		return ToBin();
	case 10:
		return ToDec();
	default:
		break;
	}
	return "";
}
int& QFloat::operator[](int ind)
{
	return data[ind];
}
QFloat& QFloat::operator=(QFloat a)
{
	for (int i = 0; i<4; i++)
		(*this)[i] = a[i];
	return *this;
}
QFloat QFloat::operator+(QFloat a){		//this + a
	string tmp, tmp2;
	QFloat kq;
	if (bang0())
		return a;
	else if (a.bang0())
		return *this;
	else {
		if (!this->am() && a.am()){		//this dương , a âm
			QFloat tmp = a;
			tmp.data[0] = SetBit0(tmp.data[0], 0);	// (-a)
			return *this - tmp;			//this - (-a)
		}
		else if (this->am() && !a.am()){	//this âm ,a dương
			QFloat tmp = *this;
			tmp.data[0] = SetBit0(tmp.data[0], 0);		//(-this)
			return a - tmp;			//a - (-this)
		}
		else if (this->am() && a.am()){	// cả 2 âm
			QFloat f1 = *this;
			QFloat f2 = a;
			f1.data[0] = SetBit0(f1.data[0], 0);	//( -this)
			f2.data[0] = SetBit0(f2.data[0], 0);	// (-a)
			kq = f1 + f2;
			kq.data[0] = SetBit1(kq.data[0], 0);	//đổi sang âm
			return kq;
		}
		else{							//cả 2 dương, làm bth
			//cout << ToBin() << endl;
			//cout << a.ToBin() << endl;
			for (int i = 16; i <= 127; i++)		//đưa phần trị của this vào chuỗi
				tmp += to_string(GetBit(data[i / 32], i % 32));
			//cout << tmp << endl;

			for (int i = 16; i <= 127; i++)		//đưa phần trị của a vào chuỗi
				tmp2 += to_string(GetBit(a.data[i / 32], i % 32));
			//cout << tmp2 << endl;
			if (this->chuan()) tmp.insert(0, "1");	//nếu chuẩn thì thêm bit 1 đầu
			else tmp.insert(0, "0");				//k thì thêm 0
			if (a.chuan()) tmp2.insert(0, "1");
			else tmp2.insert(0, "0");
			int mu1 = layMu(), mu2 = a.layMu();
			int n;
			QInt q1(2, tmp), q2(2, tmp2);
			if (mu1 > mu2){		//đưa về số mũ lớn hơn
				n = mu1 - mu2; mu2 = mu1;
				q2 = q2 >> n;	//phần trị của số mũ nhỏ hơn thì dịch phải

			}
			else{
				n = mu2 - mu1; mu1 = mu2;
				q1 = q1 >> n;
			}
			QInt t = q1 + q2;

			if (t.GetMyBit(14)){		//Nếu 2 phần trị + lại có nhớ sang bit 14
				t = t >> 1;		//dịch phải , tăng số mũ
				mu1++;
			}
			for (int i = 16; i <= 127; i++)	// Set Bit phần trị
				kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, t.GetMyBit(i));

			QInt mu(10, to_string(16383 + mu1));
			for (int i = 1; i <= 15; i++)		// Set Bit phần mũ
				kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, mu.GetMyBit(127 - 15 + i));
		}
	}
	return kq;
}
QFloat QFloat::operator-(QFloat a){
	string tmp, tmp2;
	QFloat kq;
	if (bang0())
		return a;
	else if (a.bang0())
		return *this;
	else {
		if (!this->am() && a.am()){		//this dương , a âm
			QFloat tmp = a;
			tmp.data[0]=SetBit0(tmp.data[0], 0);	//a dương tạm
			return *this + tmp;			//this +a
		}
		else if (this->am() && !a.am()){	//this âm ,a dương
			QFloat tmp = *this;	
			cout << "tmp " << tmp.ToBin() << endl;
			tmp.data[0] = SetBit0(data[0], 0);		//this dương tạm
			cout << "tmp " << tmp.ToBin() << endl;
			kq = tmp + a;
			cout <<"kq "<< kq.ToBin() << endl;
			kq.data[0] = SetBit1(kq.data[0], 0);		// + lại r đổi dấu sang âm
			cout << "kq " << kq.ToBin() << endl;
			return kq;
		}
		else if (this->am() && a.am()){	// cả 2 âm
			QFloat f1 = *this;
			QFloat f2 = a;
			f1.data[0]=SetBit0(f1.data[0], 0);
			f2.data[0] = SetBit0(f2.data[0], 0);
			return f2 -f1;			//a-this
		}
		else{							//cả 2 dương, làm bth
			//cout << ToBin() << endl;
			//cout << a.ToBin() << endl;
			for (int i = 16; i <= 127; i++)		//đưa phần trị của this vào chuỗi
				tmp += to_string(GetBit(data[i / 32], i % 32));
			//cout << tmp << endl;

			for (int i = 16; i <= 127; i++)		//đưa phần trị của a vào chuỗi
				tmp2 += to_string(GetBit(a.data[i / 32], i % 32));
			//cout << tmp2 << endl;
			if (this->chuan()) tmp.insert(0, "1");	//nếu chuẩn thì thêm bit 1 đầu
			else tmp.insert(0, "0");				//k thì thêm 0
			if (a.chuan()) tmp2.insert(0, "1");
			else tmp2.insert(0, "0");
			int mu1 = layMu(), mu2 = a.layMu();
			int n;
			QInt q1(2, tmp), q2(2, tmp2);

			cout << "q1 " << q1.ToBin() << endl << "q2 " << q2.ToBin() << endl;
			if (mu1 > mu2){		//đưa về số mũ lớn hơn
				n = mu1 - mu2; mu2 = mu1;
				q2 = q2 >> n;	//phần trị của số mũ nhỏ hơn thì dịch phải
				cout << "shift q2" << endl;
			}
			else{
				n = mu2 - mu1; mu1 = mu2;
				q1 = q1 >> n;
				cout << "shift q1" << endl;
			}
			bool am = 0; //0: q1>q2, 1:q1<q2
			QInt t;
			if (q1>q2)
				t = q1 - q2;
			else{
				t = q2 - q1;
				am = 1;
			}
			if (t.bang0()){		//phần trị trừ nhau =0
				QFloat k;		// kết quả =0
				return k;
			}
			cout << "t " << t.ToDec() << endl;
			cout << "t " << t.ToBin() << endl;
			
			//if (t.GetMyBit(0)){		//t âm
			//	QInt bu1(10, "1");
			//	t = ~t;
			//	t = t + bu1;
			//	while (t.GetMyBit(15)){	//vị trí bit đầu tiên =1
			//		pos++;
			//		mu1--;
			//		t = t << 1;
			//	}
			//}
			//else	//t dương
			int pos = 15;
			while (!t.GetMyBit(15)){	//vị trí bit đầu tiên =1
				pos++;
				mu1--;
				t = t << 1;
			}
			for (int i = 16; i <= 127; i++)	// Set Bit phần trị
				kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, t.GetMyBit(i));

			QInt mu(10, to_string(16383 + mu1));
			for (int i = 1; i <= 15; i++)		// Set Bit phần mũ
				kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, mu.GetMyBit(127 - 15 + i));
			if (am)		// nếu t âm thì gán dấu âm
				kq.data[0] = SetBit(kq.data[0], 0, 1);
		}
	}
	return kq;
}
QFloat QFloat::operator*(QFloat a){
	string tmp, tmp2;
	QFloat kq;
	if (bang0())
		return a;
	else if (a.bang0())
		return *this;
	else {
		//cout << ToBin() << endl;
		//cout << a.ToBin() << endl;
		for (int i = 16; i <= 127; i++)		//đưa phần trị của this vào chuỗi
			tmp += to_string(GetBit(data[i / 32], i % 32));
		//cout << tmp << endl;

		for (int i = 16; i <= 127; i++)		//đưa phần trị của a vào chuỗi
			tmp2 += to_string(GetBit(a.data[i / 32], i % 32));
		//cout << tmp2 << endl;
		if (this->chuan()) tmp.insert(0, "1");	//nếu chuẩn thì thêm bit 1 đầu
		else tmp.insert(0, "0");				//k thì thêm 0
		if (a.chuan()) tmp2.insert(0, "1");
		else tmp2.insert(0, "0");
		int mu1 = layMu(), mu2 = a.layMu();
		int n;
		QInt q1(2, tmp), q2(2, tmp2);


		if (mu1 > mu2){		//đưa về số mũ lớn hơn
			n = mu1 - mu2; mu2 = mu1;
			q2 = q2 >> n;	//phần trị của số mũ nhỏ hơn thì dịch phải

		}
		else{
			n = mu2 - mu1; mu1 = mu2;
			q1 = q1 >> n;
		}
		if (GetBit(data[0], 0)){
			QInt bu1(10, "1");
			q1 = ~q1;
			q1 = q1 + bu1;
		}
		if (GetBit(a.data[0], 0)){
			QInt bu1(10, "1");
			q2 = ~q2;
			q2 = q2 + bu1;
		}
		QInt t = q1 - q2;
		if (t.bang0()){		//phần trị trừ nhau =0
			QFloat k;		// kết quả =0
			return k;
		}
		int pos = 15;
		while (!t.GetMyBit(15)){	//vị trí bit đầu tiên =1
			pos++;
			mu1--;
			t = t << 1;
		}

		//if (t.GetMyBit(14)){		//Nếu 2 phần trị + lại có nhớ sang bit 14
		//	t = t >> 1;		//dịch phải , tăng số mũ
		//	mu1++;
		//}
		for (int i = 16; i <= 127; i++)	// Set Bit phần trị
			kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, t.GetMyBit(i));

		QInt mu(10, to_string(16383 + mu1));
		for (int i = 1; i <= 15; i++)		// Set Bit phần mũ
			kq.data[i / 32] = SetBit(kq.data[i / 32], i % 32, mu.GetMyBit(127 - 15 + i));
	}
	return kq;
}
QFloat QFloat::operator/(QFloat a){
	QFloat kq;
	return kq;
}