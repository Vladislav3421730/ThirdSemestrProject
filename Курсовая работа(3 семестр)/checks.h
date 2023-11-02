
#include<iostream>
#include<string>
#include<vector>
using namespace std;

extern bool isNumberNumeric();
extern  int check(int left_range, int right_range, int number);
extern string check_on_digit(string str);
extern int check_on_letters(int n);
extern string check_on_size(string str, int n);
extern string vvod(string password);
extern string encryptPassword(string to_encrypt);

template<class T>
extern bool check_on_exist(vector<T> vector, T obj)
{
	for (auto t : vector) {
		if (t.getLogin() == obj.getLogin()) return true;
	}
	return false;
};