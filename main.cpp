#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Q.h"
#include "Func.h"
#include "QFloat.h"
using namespace std;

int main(int argc, char* argv[]){
	if (argc == 4)
	{
		if (strcmp(argv[3],"1")==0){		//Dạng QInt
			ifstream input(argv[1], ios::in);
			ofstream output(argv[2], ios::out);
			if (input.fail()) cout << "K the mo file!";

			while (!input.eof()){
				string s;
				getline(input, s);
				vector<string> res;
				istringstream iss(s);
				for (string s; iss >> s;)
					res.push_back(s);
				
				if (res.size() == 4){	//4 tham số -> có phép tính (trừ not, ror, rol
					QInt a(stoi(res[0]), res[1]);
					QInt b(stoi(res[0]), res[3]);
					if (res[2] == "+")
						output << (a + b).Output(stoi(res[0])) << endl;
					else if (res[2] == "-")
						output << (a - b).Output(stoi(res[0])) << endl;
					else if (res[2] == "*")
						output << (a * b).Output(stoi(res[0])) << endl;
					else if (res[2] == "/")
						output << (a / b).Output(stoi(res[0])) << endl;
					else if (res[2] == "&"){
						QInt c; c = a&b;
						output << c.Output(stoi(res[0])) << endl;
					}
					else if (res[2] == "|"){
						QInt c; c = a | b;
						output << c.Output(stoi(res[0])) << endl;
					}
					else if (res[2] == "^"){
						QInt c; c = a^b;
						output << c.Output(stoi(res[0])) << endl;
					}
					else if (res[2] == ">>"){
						QInt c; c = a >> stoi(res[3]);
						output << c.Output(stoi(res[0])) << endl;
					}
					else if (res[2] == "<<"){
						QInt c; c = a << stoi(res[3]);
						output << c.Output(stoi(res[0])) << endl;
					}
				}
				else{	//3 tham số -> chuyển hệ, và phép ~ ror rol
					QInt a(stoi(res[0]), res[2]);
					output << a.Output(stoi(res[1])) << endl;
				}
			}
		}
		else{		//2 -> Dạng QFloat
			ifstream input(argv[1], ios::in);
			ofstream output(argv[2], ios::out);
			if (input.fail()) cout << "K the mo file!";

			while (!input.eof()){
				string s;
				getline(input, s);
				vector<string> res;
				istringstream iss(s);
				for (string s; iss >> s;)
					res.push_back(s);
				
				if (res.size() == 4){	//4 tham số -> có phép tính (trừ not, ror, rol
					output << "Xin loi thay em chua lam phan nay\n";
				}
				else{	//3 tham số -> chuyển hệ, và phép ~ ror rol
					QFloat a(stoi(res[0]), res[2]);
					output << a.Output(stoi(res[1])) << endl;

				}
			}

		}
		
	}
	else if (argc > 4)
	{
		cout << "Du tham so !\n";
	}
	else
	{
		cout << "Thieu tham so!\n";
		
	}

    return 0;
}
