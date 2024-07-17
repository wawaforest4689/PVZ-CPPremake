#include "Players.h"
#include "graphics.h"
#include "mmsystem.h"
#include <cstdlib>
#include <windows.h>
#pragma comment(lib, "winmm.lib")

extern HWND hwnd;
using namespace std;


int Players::total_num = 0;
Players::Players(string name,string pw)
	:pnumber(0),chall_time(0)
{
	for (int j = 0; j < 30; j++)
	{
		progress[j] = 0;
	}
	setusername(name,0);
	setuserpw(pw,0);
}

bool Players::setusername(string name,int flag)
{
	ifstream infile("players.dat", ios::in|ios::binary);
	if (!infile)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	if (flag == 0)
	{

		if (name.size() > 10)
		{
			MessageBox(hwnd, "注册用户名过长(超过10个中文或英文字符)", "提示", MB_OK | MB_ICONWARNING);
			infile.close();
			return false;
		}
		else
		{
			//infile.seekg(0);
			if (!checkname(infile, name))
			{
				name.copy(username, name.size());
				username[name.size()] = '\0';
				infile.close();
				return true;
			}
			MessageBox(hwnd, "用户名已存在，请重新注册", "提示", MB_OK | MB_ICONERROR);
			infile.close();
			return false;
		}
	}
	if (flag == 1)
	{
		if (name.size() > 10)
		{
			MessageBox(hwnd, "更新用户名过长(超过9个中文字符或19个英文字符)", "提示", MB_OK | MB_ICONWARNING);
			infile.close();
			return false;
		}

		else
		{
			//infile.seekg(0);
			if (!checkname(infile, name))
			{
				name.copy(username, name.size());
				username[name.size()] = '\0';
				infile.close();
				return true;
			}
			MessageBox(hwnd, "用户名已存在，请重新更改", "提示", MB_OK | MB_ICONERROR);
			infile.close();
			return false;
		}
	}
	if (flag == 2)
	{
		if (name.empty())
		{
			username[0]='\0';
			return false;
		}
		else
		{
			name.copy(username, name.size());
			username[name.size()] = '\0';
			infile.close();
			return true;
		}
	}
}

bool Players::setuserpw(string pw,int flag)
{
	ifstream infile("players.dat", ios::in|ios::binary);
	if (!infile)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	if (flag == 0)
	{
	if (pw.size() > 15)
	{
		MessageBox(hwnd, "用户密码过长(超过15个英文、数字或特殊符号字符),请重新注册", "提示", MB_OK | MB_ICONWARNING);
		infile.close();
		return false;
	}
	else
	{
			pw.copy(userpw, pw.size());
			userpw[pw.size()] = '\0';
			infile.close();
			return true;
	}
	}
	if (flag == 1)
	{
		if (pw.size() > 15)
		{
			MessageBox(hwnd, "用户密码过长(超过15个英文、数字或特殊符号字符),请重新更改", "提示", MB_OK | MB_ICONWARNING);
			infile.close();
			return false;
		}
		else
		{
			pw.copy(userpw, pw.size());
			userpw[pw.size()] = '\0';
			infile.close();
			return true;
		}
	}
	if (flag == 2)
	{
		pw.copy(userpw, pw.size());
		userpw[pw.size()] = '\0';
		infile.close();
		return true;
	}
}

bool Players::userregister(string name, string pw)
{
	if (setusername(name, 0) && setuserpw(pw,0))
	{
		fstream outfile("players.dat", ios::in | ios::out |ios::binary);
		Players temp_player;
		if (!outfile)
		{
			cerr << "Connection fails!" << endl;
			exit(EXIT_FAILURE);
		}
		for (int i=0; i < total_num; i++)
		{
			outfile.seekg(i * sizeof(Players));
			outfile.seekp((i+1) * sizeof(Players));
			outfile.read(reinterpret_cast<char*>(&temp_player), sizeof(Players));
			if (temp_player.pnumber == 0)
			{
				//outfile.seekp(-sizeof(Players),ios::cur);
				outfile.seekp(i * sizeof(Players));
				break;
			}
		}
		pnumber = outfile.tellp() / sizeof(Players)+1;	//essential for efficiency
		cout << "username: "<<username << endl;
		outfile.write(reinterpret_cast<const char*>(this), sizeof(Players));
		outfile.close();
		total_num++;
		return true;
	}
	else
	{
		return false;
	}
}

Players& Players::userlogin(string name, string pw)
{
	ifstream infile("players.dat", ios::binary | ios::in);
	if (!infile)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	if (name.size() > 10||pw.size()>15)
	{
		MessageBox(hwnd, "登录用户名或密码过长(超过10个中文或英文字符)", "提示", MB_OK | MB_ICONWARNING);
		infile.close();
		setusername("",2);
		//Players blank_player;
		//return blank_player;

		return *this;
	}
	//infile.seekg(0);
	if (checkname(infile,name))
	{
		//infile.seekg(0);
		if (verify(infile, name, pw))
		{
			cout << "password is correct" << endl;
			//this->setusername(name,2);
			//this->setuserpw(pw,2);
			int count = checkname(infile, name);
			infile.seekg((count - 1) * sizeof(Players));
			infile.read(reinterpret_cast<char*>(this), sizeof(Players));
			infile.close();
			return *this;
		}
		else
		{
			MessageBox(hwnd, "用户密码不正确，请确认密码", "提示", MB_OK | MB_ICONERROR);
			infile.close();
			setusername("", 2);
			//Players blank_player;
			//return blank_player;
			return *this;
		}
	}
	else
	{
		MessageBox(hwnd, "用户未注册，请先注册", "提示", MB_OK | MB_ICONERROR);
		infile.close();
		setusername("", 2);
		//Players blank_player;
		//return blank_player;
		return *this;
	}
}


int Players::checkname(ifstream& in, string name)
{
	int count = 1;
	in.clear();
	in.seekg(0);
	in.read(reinterpret_cast<char*>(this), sizeof(Players));
	while (!in.eof())
	{
		cout <<username<<endl;
		if (getname() == name)
		{
			return count;
		}
		count++;
		in.read(reinterpret_cast<char*>(this), sizeof(Players));
	}
	return 0;
}


bool Players::verify(ifstream& in, string name, string pw)
{
	in.clear();
	in.seekg(0);
	in.read(reinterpret_cast<char*>(this), sizeof(Players));
	while (!in.eof())
	{
		if (getname() == name)
		{
			cout << "user_pass" << getpw() << endl;
			cout << "pw" << pw << endl;
			if (getpw() == pw)
				return true;
			else {
				return false;
			}
		}
		in.read(reinterpret_cast<char*>(this), sizeof(Players));
	}
	return false;
}

string Players::getname()
{
	string name = username;
	return name;
}


string Players::getpw()
{
	string pw = userpw;
	return pw;
}


const double* Players::getprogress()
{
	return &progress[0];
}

int Players::getpnumber()
{
	return pnumber;
}

void Players::up_time(int time)
{
	chall_time=time;
	fstream wr_file("players.dat", ios::out | ios::binary | ios::in);
	if (!wr_file)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	wr_file.seekp((pnumber - 1) * sizeof(Players));
	wr_file.write(reinterpret_cast<const char*>(this), sizeof(Players));
	cout << "Writing successfully!" << endl;
	wr_file.close();
}


void Players::quit_and_save(int loc, double val)
{
	progress[loc] = val;
	fstream wr_file("players.dat", ios::out | ios::binary | ios::in);
	if (!wr_file)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	wr_file.seekp((pnumber-1) * sizeof(Players));
	wr_file.write(reinterpret_cast<const char*>(this), sizeof(Players));
	cout << "Writing successfully!" << endl;
	wr_file.close();
}



void Players::userlogout()
{
	setusername("", 2);
	setuserpw("", 2);
	for (int i=0;i<30;i++)
	{
		progress[i] = 0;
	}
	pnumber = 0;
}


bool Players::userchange(string name,string pw)
{
	string tempname;
	string temppw;
	tempname = username;
	temppw = userpw;
	if (setusername(name,1) && setuserpw(pw,1))
	{
		fstream outfile("players.dat", ios::in | ios::out | ios::binary);
		if (!outfile)
		{
			cerr << "Connection fails!" << endl;
			exit(EXIT_FAILURE);
		}
		outfile.seekp((pnumber - 1) * sizeof(Players));
		outfile.write(reinterpret_cast<const char*>(this), sizeof(Players));
		outfile.close();
		cout << "Changing file storage successfully!" << endl;
		return true;
	}
	tempname.copy(username, tempname.size());
	temppw.copy(userpw, temppw.size());
	return false;
}


void Players::userdelete()
{
	Players blank_player;
	fstream outfile("players.dat", ios::in | ios::out | ios::binary);
	if (!outfile)
	{
		cerr << "Connection fails!" << endl;
		exit(EXIT_FAILURE);
	}
	outfile.seekp((pnumber - 1) * sizeof(Players));
	outfile.write(reinterpret_cast<const char*>(&blank_player), sizeof(Players));
	outfile.close();
	total_num--;
	cout << "Deleting in file storage successfully!" << endl;
}





