#include <bits/stdc++.h>
#include <Winsock2.h>
#include "udp_php.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define format_login "Log:"
#define format_sendkey "key:"
#define format_quit "Qut:"
#define format_pulse "tim:"


//0:������¼		1:������		2:����������֤	3:�����к�	4:�������	5:��������Ա		6:�����Ҳ�����֤
#define format_Logcheck "Lck:"

//0:������¼		1��������	2�����к�����
#define format_Keycheck "Cck:"

#define format_correct "Cor"

#define Key_file "keydata.txt"

void sendmsg(string format, int k)
{
	string ret = format + (char)('0' + k);
	Sendto(ret);
}

bool strcmp(string a, string b, int k)
{
	if (a.size() < k || b.size() < k) return 0;
	for (int i = 0; i < k; i++)
		if (a[i] != b[i])
			return 0;
	return 1;
}

string recvmsg(string format)
{
	string rcv;
	rcv.clear();
	while (!strcmp(rcv, format, 4))
		rcv = Recvfrom();
	//cout << rcv << endl;
	return rcv;
}


int main(int argc, char** argv)
{
	if (argc < 3) { cout<<"�������룡"<<endl; return 0; }
	if (strlen(argv[1]) == 0)
	{
		cout << "�û�������Ϊ��" << endl;
		return 0;
	}
	if (strlen(argv[2]) == 0)
	{
		cout << "���벻��Ϊ��" << endl;
		return 0;
	}
	string username = argv[1];
	string password = argv[2];
	int c = atol(argv[3]);
	Bind();
	
	//���͵�¼����
	Sendto(format_login + username + ":" + password);
	//cout << format_login + username + ":" + password << endl;
	string rcv;
	int logmsg = -1;

	string inkey;
	inkey.clear();
	if (c == 10)inkey = "-1";
	if (c == 20)inkey = "-2";
	if (c == 30)inkey = "-3";
	if (c == 40)inkey = "-4";
	if (c == 50)inkey = "-5";


	rcv = recvmsg(format_Logcheck);
	//cout << rcv << endl;
	logmsg = rcv[4] - '0';
	//cout << "logmsg:"<<logmsg << endl;
	string userkey;
	int keymsg = -1;
	switch (logmsg)
	{
	case 1:
		
		cout << "�Ѵ������û����˺ţ�" << username << "���룺" << password << endl;
		
	case 2:
	case 3:

		Sendto(format_sendkey + username + ":" + inkey);
	
		rcv = recvmsg(format_Keycheck);
		keymsg = rcv[4] - '0';

		userkey.clear();
		if (keymsg == 0)
		{
			if (rcv.size() > 5)
			{
				for (int i = 6; i < 16; i++)
					userkey.push_back(rcv[i]);
				cout << "�������кųɹ���" << userkey << endl;
			}
				
		}


		break;



	case 4:
		cout << "�������������" << endl;
		break;
	case 5:
		cout << "�����������ˣ����Ժ�����" << endl;
		break;
	case 6:
		cout << "���������룡ͬһ�û�����������������" << endl;
		break;
	case 0:
		
		cout << "���������룡ͬһ�û�����������������" << endl;
		break;
	default:
		cout << "��Ϣ�쳣���������ѱ���" << endl;
		break;
	}
	Sendto(format_quit + username);
}