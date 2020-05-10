#include <string>
#include "Q.h"
#include "Func.h"

void QInt::SetBitFromBin(bool* bin){
	for (int i = 0; i < 128; i++)
		data[i / 32] = SetBit(data[i / 32], i % 32, bin[i]);
}

void QInt::InputUnsignedDec(string s){
	bool* bin;
	chuyenNhiPhan(s, bin);
	this->SetBitFromBin(bin);
}
void QInt::InputSignedDec(string s){
	s.erase(0, 1);
	InputUnsignedDec(s);
	QInt One(10, "1");
	*this = ~(*this);
	*this = *this + One;
}

void QInt::ScanQInt()
{
    string s;
    getline(cin, s);
    int i = 0;

    while (i < s.length())
    {
        if (s[i] <= '0' || s[i] >= '9')
            if (s[i] != '+' && s[i] != '-')
                s.erase(i, 1);
        i++;
    }

    i = 1;
    while (i < s.length())
    {
        if (s[i] == '+' || s[i] == '-')
            s.erase(i, 1);
        i++;
    }

    if (s[0] == '-') this->InputSignedDec(s);
    else this->InputUnsignedDec(s);
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
		while (kq[0] == '0')
			kq.erase(0, 1);
		kq.insert(0, "-");
	}
	cout << kq<<endl;
}

ostream& operator << (ostream& os, QInt p) {
    int pos = 0;
    while (!GetBit(p.data[pos / 32], pos % 32))
        pos++;
    while (pos < 128) {
        os << GetBit(p.data[pos / 32], pos % 32);
        pos++;
    }
    return os;
}

int& QInt::operator[](int ind)
{
    return data[ind];
}

bool QInt::operator>(QInt q)
{
    //so sánh khi cả 2 cùng âm

    if ((*this).data[0] < 0 && q.data[0] < 0)
    {
    	for (int i = 1; i < 4; i++)
    	{
            //Nếu trên cùng thứ tự phần tử có bit là dương thì so sánh ngược
            if (data[i]*1.0 / q.data[i] < 0) 
            {
                if (data[i] < q.data[i]) return true;
                if (data[i] > q.data[i]) return false;
            }

            //So sánh bình thường
    		if (data[i] > q.data[i]) return true; 
    		else if (data[i] < q.data[i]) return false;
    	}
    }

    //so sánh trong các th khác 2 số cùng âm
    for (int i = 0; i < 4; i++)
    {
        if (data[i] > q.data[i]) return true;
        else if (data[i] < q.data[i]) return false;
    }
    return false;
}

bool QInt::operator<(QInt q)
{
    //so sánh khi cả 2 cùng âm

    if ((*this)[0] < 0 && q[0] < 0)
    {
    	for (int i = 1; i < 4; i++)
    	{
            //Nếu trên cùng thứ tự phần tử có bit là dương thì so sánh ngược
            if (data[i] * 1.0 / q.data[i] < 0)
            {
                if (data[i] > q.data[i]) return true;
                if (data[i] < q.data[i]) return false;
            }

            //So sánh bình thường
    		if (data[i] < q.data[i]) return true;
    		else if (data[i] > q.data[i]) return false;
    	}
    }

    for (int i = 0; i < 4; i++)
    {
        //So sánh bình thường
        if (data[i] < q.data[i]) return true;
        else if (data[i] > q.data[i]) return false;
    }
    return false;
}

bool QInt::operator==(QInt q)
{
    for (int i = 0; i < 4; i++)
    {
        if (data[i] != q.data[i]) return false;
    }
    return true;
}

bool QInt::operator<=(QInt q)
{
    if ((*this) < q || (*this) == q) return true;
    return false;
}

bool QInt::operator>=(QInt q)
{
    if ((*this) > q || (*this) == q) return true;
    return false;
}

QInt& QInt::operator=(QInt a)
{
    for (int i=0;i<4;i++)
        (*this)[i]=a[i];
    return *this;
}

// Phép toán trên bit: AND (&)
QInt QInt::operator&(QInt a)
{
    QInt tmp=*this;
    // AND lần lượt từng phần tử tương ứng
    for (int i=0;i<4;i++)
    {
        tmp[i]=tmp[i]&a[i];
    }
    return tmp;
}

// Phép toán trên bit: OR (|)
QInt QInt::operator|(QInt a)
{
      QInt tmp=*this;
    // OR lần lượt từng phần tử tương ứng
       for (int i=0;i<4;i++)
       {
           tmp[i]=tmp[i]|a[i];
       }
       return tmp;
}

// Phép toán trên bit: XOR (^)
QInt QInt::operator^(QInt a)
{
      QInt tmp=*this;
    // XOR lần lượt từng phần tử tương ứng
       for (int i=0;i<4;i++)
       {
           tmp[i]=tmp[i]^a[i];
       }
       return tmp;
}

// Phép toán trên bit: NOT (~)
QInt QInt::operator~()
{
    QInt tmp=*this;
    // Đảo lần lượt từng phần tử tương ứng
       for (int i=0;i<4;i++)
       {
           tmp[i]=~tmp[i];
       }
       return tmp;
}

// Phép toán trên bit: Phép dịch phải >>
QInt QInt::operator>>(int a)
{
    QInt tmp = *this;
    // Nếu dịch phải một lượng âm thì đổi sang dịch trái
    if (a < 0) return tmp << (-a);
    // Xét trường hợp
    if (a==0) return tmp;
    // Nếu dịch nhỏ hơn 32 bit thì xử lí trên từng mảng chứa
    if (a < 32)
    {
        for (int i = 3; i > 0; i--)
        {
			tmp[i] = (unsigned int)(tmp[i] >> a) | tmp[i - 1] << (32 - a);
        }
        tmp[0] = tmp[0] >> a;
    }
     // Nếu dịch lớn hơn 32 bit thì đẩy sang phải 1 mảng rồi xử lí bằng đệ quy
    else
    {
        for (int i = 3; i > 0; i--)
        {
            tmp[i] = tmp[i - 1];
        }
        // Xử lí dịch số học
        tmp[0] = tmp[0] < 0 ? -1 : 0;
        tmp = tmp >> (a - 32);
    }
    return tmp;
}

// Phép toán trên bit: Phép dịch phải >>
QInt QInt::operator<<(int a)
{
    QInt tmp = *this;
    // Nếu dịch trái một lượng âm thì đổi sang dịch phải
    if (a < 0) return tmp >> (-a);
    // Xét trường hợp
     if (a==0) return tmp;
    // Nếu dịch nhỏ hơn 32 bit thì xử lí trên từng mảng chứa
    if (a < 32)
    {
        for (int i = 0; i < 3; i++)
        {
            tmp[i] = (tmp[i] << a) | (unsigned int)tmp[i + 1] >> (32 - a);
        }
        tmp[3] = tmp[3] << a;
    }
    // Nếu dịch lớn hơn 32 bit thì đẩy sang trái 1 mảng rồi xử lí bằng đệ quy
    else
    {
        for (int i = 0; i < 4; i++)
        {
            tmp[i] = tmp[i + 1];
        }
        tmp[3] = 0;
        tmp = tmp << (a - 32);
    }
    return tmp;
}

// Phép cộng trên bit: Half Adder Logic
QInt QInt::operator+(QInt a)
{
    QInt tmp1=*this;
    // zero = 0, dùng để kiểm tra điều kiện
    QInt zero;
    // carry dùng để nhớ lượng dư ra khi thực hiện phép cộng
    QInt carry;
    // điều kiện dừng phép cộng khi lượng nhớ = 0
    while (a!=zero)
    {
        // Dùng AND để kiểm tra lượng nhớ sau khi cộng
        carry= tmp1 & a;
        // Dùng XOR để lấy kết quả phép cộng không nhớ
        tmp1=tmp1^a;
        // Dịch lượng nhớ sang trái để tiếp tục cộng
        carry=carry<<1;
        // a là số hạng mới
        a = carry;
    }
    return tmp1;
}

// Phép trừ trên bit: Lấy số âm (dạng bù 2) rồi thực hiện phép cộng
QInt QInt::operator-(QInt a)
{
    QInt bu1(10,"1");
    a= ~a;
    a=a+bu1;
    QInt result= a + (*this);
    return result;
}

bool QInt::operator!=(QInt a)
{
    QInt tmp=*this;
    for (int i=0;i<4;i++)
        if (tmp[i]!=a[i]) return true;
    return false;
}

int QInt::demBit()
{
    int count=128;
    for (int i=0;i<128;i++)
    {
        if (GetBit(data[i/32],i)==0)
            count--;
        else break;
    }
    return count;
}

// Phép nhân trên bit: Thuật toán Booth
QInt QInt::operator*(QInt a)
{
    QInt tmp=*this;
    
    QInt result;
    
    // Q[-1] = 0
    bool Q_am1=0;
    
    for (int i=0;i<128;i++)
    {
        // Trường hợp 10
        if (GetBit(tmp[3],31)==1 && Q_am1==0)
        {
            result=result - a;
        }
        // Trường hợp 01
        else if (GetBit(tmp[3],31)==0 && Q_am1==1)
        {
            result=result + a;
         
        }
        // Trường hợp 00 hoặc 11
        Q_am1=GetBit(tmp[3],31);
        
        //Đẩy bit cuối từ result sang bit đầu của tmp và dịch phải tmp
		tmp[3] = (unsigned int)tmp[3] >> 1 | tmp[2] << 31;
		tmp[2] = (unsigned int)tmp[2] >> 1 | tmp[1] << 31;
		tmp[1] = (unsigned int)tmp[1] >> 1 | tmp[0] << 31;
		tmp[0] = (unsigned int)tmp[0] >> 1 | result[3] << 31;
        
        // Dịch phải result
        result=result>>1;
       
    }
    // Sau khi dịch thì kết quả nằm ở tmp
    return tmp;
}

/*Phép chia trên bit
Đầu vào là một số QInt
*/
QInt QInt::operator/(QInt m)
{
    QInt zero;
    if (m == zero)
        throw "Loi chia 0.";

    QInt q = *this; //Q đóng vai trò là thương.
    bool sig = false;

    if (q.data[0] < 0)
    {
        q = ~q + QInt(10,"1");
        sig = !sig;
    }

    if (m.data[0] < 0)
    {
        m = ~m + QInt(10, "1");
        sig = !sig; //chỉ khi q và m khác dấu thì sig mới true
    }
 
    QInt a; //A đóng vai trò số dư

    for (int i = 0; i < 128; i++)
    {
            //Shift Q, A
        int car = GetBit(q.data[0], 0);
        a = a << 1;
        q = q << 1;
        a.data[3] = a.data[3] | car;


        a = a - m;
        if (a.data[0] < 0)
        {
            a = a + m;
            q.data[3] = SetBit(q.data[3], 31, 0); //Q0 = 0
        }
        else
        {
            q.data[3] = SetBit1(q.data[3], 31); //Q0 = 1
        }
    }

    if (sig)
    {
        q = ~q + QInt(10, "1");
    }

    return q;
}

/*
Phép xoay trái
*/
QInt QInt::rol()
{
    QInt tmp = *this;
    int car = GetBit(data[0], 0); //lấy bit đầu tiên của số
    tmp = tmp << 1;
    tmp.data[3] = tmp.data[3] | car;//gán bit đầu tiên đã lấy vào cuối dãy bit mới
    return tmp;
}

/*
Phép xoay phải
*/
QInt QInt::ror()
{
    QInt tmp = *this;
    int car = GetBit(data[3], 31); //lấy bit cuối cùng của số
    tmp = tmp >> 1;
    tmp.data[0] = tmp.data[0] | car << 31;//gán bit cuối đã lấy vào đầu dãy bit mới
    return tmp;
}
