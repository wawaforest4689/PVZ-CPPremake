//2024.06.01

#pragma once
#include <iostream>
#include <fstream>
//#include <sstream> // owing to random access file, the standard library is not needed
#include <string>

using namespace std;

class Players
{
public:
	Players(string="", string="");
	bool userregister(string,string);
	Players& userlogin(string,string);
	string getname();
	const double* getprogress();
	void up_time(int);
	int getpnumber();	//players information file registeration number 
	void quit_and_save(int, double);
	void userlogout();
	bool userchange(string,string);
	void userdelete(); 
	//bool userchangepw(string);  //future function
private:
	bool setusername(string,int);
	bool setuserpw(string,int);
	int checkname(ifstream&, string);
	bool verify(ifstream&,string, string);
	string getpw();
	char username[11];
	char userpw[16];
	// 3x10=30 levels
	double progress[30];	//use double array to improve and enhance function(performance commment and reward)
	int chall_time;	//in seconds,2024.7.1
	int pnumber;
	static int total_num;
};
