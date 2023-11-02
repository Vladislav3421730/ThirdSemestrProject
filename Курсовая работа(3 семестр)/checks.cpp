#include<iostream>
#include<string>
#include<conio.h>
#include"checks.h"
using namespace std;

bool isNumberNumeric()
{
	
	if (cin.get() == '\n')
	{
		return true;
	}
	else
	{
		cin.clear();
		cin.ignore(256, '\n');
		return false;
	}
}
extern  int check(int left_range, int right_range, int number)
{
	while (!isNumberNumeric() || number > right_range || number < left_range)
	{

		cout << "Введено некоректное значение" << endl;
		cin >> number;
	}
	return number;
}
 string check_on_digit(string str)
{
	while (str.find_first_of("0123456789") != string::npos)
	{
		cout << "Данное поле не может содержать цифры" << endl;
		getline(cin, str);
	}
	return str;
}
int check_on_letters(int n)
{
	while (!isNumberNumeric() || n < 0)
	{
		cout << "Введено некоректное значение" << endl;
		cin >> n;
	}
	return n;
}
string check_on_size(string str, int n)
{
	while (str.size() < n)
	{
		cout << "Вы ввели малое количество символов для поиска" << endl;
		getline(cin, str);
	}
	return str;
}

string vvod(string password)
{
	password = "";
	char ch;
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (password.length() > 0) {
				password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			password += ch;
			cout << "*";
		}
	}cout << endl;
	return password;
}
string encryptPassword(string to_encrypt)
{
	const int shift = 3;
	for (int i = 0; i < to_encrypt.length(); i++) {
		to_encrypt[i] = (to_encrypt[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

	}
	return to_encrypt;
}