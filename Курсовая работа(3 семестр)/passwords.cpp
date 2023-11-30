#include<iostream>
#include<Windows.h>
#include<fstream>
#include<string.h>
#include <conio.h>
#include <string>
#include<random>
#include<iomanip>
#include"checks.h"
#include"passwords.h"

using namespace std;

namespace workFithAuthentication
{
	vector<Admin> admins;
	vector<User> users;
	vector<Manager> managers;
	shared_ptr<User> UserPtr;

}
 void workFithAuthentication::show_menu_for_registr()
{
	int choice;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	get_blue cout << setw(150) << "_________________________________________________________________________________________" << endl;
	cout << setw(62) << "|"; get_yellow cout << "                                      ������� ����                                     ";get_blue cout<<"| " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	cout << setw(62) << "|"; get_red cout << "                                1. ����� ��� ������������";get_blue cout<< "                              | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                2. ����� ��� �������������"; get_blue cout << "                             | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                3. ����� ��� ��������"; get_blue cout << "                                  | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                4. ������������������ "; get_blue cout << "                                 | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                5. ����� �� ���������"; get_blue cout << "                                  | " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	get_yellow cout << setw(110) << "                                   ��� ����� ";
	get_red
	try {
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			no_color
			throw runtime_error("����������� ���� ����� ��������");
		}
	}
	catch (runtime_error e) {
		cout << e.what() << endl;
		system("pause"); system("cls");
		workFithAuthentication::show_menu_for_registr();
	}
	cin.ignore();
	no_color
	switch (choice)
	{
	case 1:
		
		if (INPUT_FOR_USERS()) {
			system("cls");
			MenuForUsers();
		}
		else
		{
			system("pause");
			system("cls");
			show_menu_for_registr();
		}
		break;
	case 2:
		if (INPUT_FOR_ADMIN()) {
			system("cls");
			menu_for_work_with_users();
		}
		else
		{
			cout << "������ ������� �������" << endl;
			system("pause");
			system("cls");
			show_menu_for_registr();
		}break;
	case 3:
		if (INPUT_FOR_MANAGER()) {
			system("cls");
			menu_for_manager();
		}
		else
		{
			cout << "������ ������� �������" << endl;
			system("pause");
			system("cls");
			show_menu_for_registr();
		}break;
	case 4:system("cls"); REGISTRATION(); show_menu_for_registr(); break;
	case 5:
		return;
	default: 
		cout << "������� ����� ����� ��������" << endl;
		system("pause"); system("cls");
		workFithAuthentication::show_menu_for_registr();
	}

}
extern bool  workFithAuthentication::INPUT_FOR_USERS()
{
	cout << "���� ������������" << endl;
	string login, password;
	cout << "�����: ";
	getline(cin, login);
	cout << "������: ";
	password = vvod(password);
	password = encryptPassword(password);
	bool result = false;
	for (auto user : users) {
		if (user.getPassword() == password && user.getLogin() == login) {
			result = true;
			if (user.getIsBan()) {
				cout << "�� ���� ��������" << endl;
				return false;
			}
			else if (!user.getIsAvailable()) {
				cout << "���� ������ ��� �� ��������" << endl;
				return false;
			}
			UserPtr = make_shared<User>(user);
			return true;
		}
	}
	if (!result) {
		cout << "������ ������� �������" << endl;
	}
	return false;
}
bool  workFithAuthentication::INPUT_FOR_ADMIN()
{
	cout << "���� ��������������" << endl;
	string login, password;
	cout << "�����: ";
	getline(cin, login);
	cout << "������: ";
	password = vvod(password);
	password = encryptPassword(password);
	for (auto admin : admins) {
		if (admin.getPassword() == password && admin.getLogin() == login) return true;
	}
	return false;

}

bool workFithAuthentication::INPUT_FOR_MANAGER()
{
	cout << "���� ��� ���������" << endl;
	string login, password;
	cout << "�����: ";
	getline(cin, login);
	cout << "������: ";
	password = vvod(password);
	password = encryptPassword(password);
	for (auto manager : managers) {
		if (manager.getPassword() == password && manager.getLogin() == login) return true;
	}
	return false;
}

void workFithAuthentication::REGISTRATION()
{

	int n;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
	cout << setw(62) << "|"; get_yellow cout << "                                      �����������                                      "; get_green cout << "| " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	cout << setw(62) << "|"; get_red cout << "                                1. ��� ������������"; get_green cout << "                                    | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                2. ��� �������������"; get_green cout << "                                   | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                3. ��� �������� "; get_green cout << "                                       | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                4. ����� � ������� ����"; get_green cout << "                                | " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	get_yellow cout << setw(110) << "                                   ��� ����� ";
	get_red
	cin >> n;
	no_color
	n = check(1, 4, n);
	if (n == 1)
	{
		string login, password;
		cout << "����� ����� ������������: ";
		getline(cin, login);
		cout << "����� ������ ������������: ";
		password = vvod(password);
		const int shift = 3;
		for (int i = 0; i < password.length(); i++)
		{
			password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

		}

		User user(login, password, false, false);
		if (check_on_exist(users,user)) cout << "������������ � ����� ����� ��� ���� � �������" << endl;
		else {
			users.push_back(user);
			cout << "���� ������ ������� �� ������������" << endl;
		}
		system("pause"); system("cls");
	}
	else if (n == 2)
	{
		string special_password;
		int i = 0;
		cout << "���� �� ������ ������������������ ��� ������������� ����� ����������� ������ ������ ���������� �����" << endl;
		special_password = vvod(special_password);
		while (special_password != "q1w2e3" && i < 5)
		{
			cout << "����������� ������ ��������" << endl;
			special_password = vvod(special_password);
			i++;
		}
		if (i == 5)
		{
			cout << "��� �� ������� ������ ����������� ������ ��������� ��������" << endl;
		}
		else
		{
			cout << "����� ����� ��������������: ";
			string login, password;
			getline(cin, login);
			cout << "����� ������ ��������������: ";
			password = vvod(password);
			const int shift = 3;
			for (int i = 0; i < password.length(); i++)
			{
				password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}

			Admin admin(login, password);
			if (check_on_exist(admins,admin)) cout << "����� � ����� ����� ��� ���� � �������" << endl;
			else {
				admins.push_back(admin);
				cout << "����� ������������� ���������������" << endl;
			}
		}
		system("pause"); system("cls");
	}
	else if (n == 3)
	{
		string special_password;
		int i = 0;
		cout << "���� �� ������ ������������������ ��� �������� ����� ����������� ������ ��������� ��������" << endl;
		special_password = vvod(special_password);
		while (special_password != "q1w2e3" && i < 5)
		{
			cout << "����������� ������ ��������" << endl;
			special_password = vvod(special_password);
			i++;
		}
		if (i == 5)
		{
			cout << "��� �� ������� ������ ����������� ������ ���������� �����" << endl;
		}
		else
		{
			cout << "����� ����� ���������: ";
			string login, password;
			getline(cin, login);
			cout << "����� ������ ���������: ";
			password = vvod(password);
			const int shift = 3;
			for (int i = 0; i < password.length(); i++)
			{
				password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}

			Manager manager(login, password);
			if (check_on_exist(managers,manager)) cout << "�������� � ����� ����� ��� ���� � �������" << endl;
			else {
				managers.push_back(manager);
				cout << "����� �������� ���������������" << endl;
			}
		}
		system("pause"); system("cls");
	}
	else if (n == 4) system("cls");
}

 void  workFithAuthentication::menu_for_work_with_users() {

	int choice = 0;
	while (choice != 5) {

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
		cout << setw(62) << "|"; get_yellow cout << "                                      ���� ��� ��������������                          "; get_green cout << "| " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		cout << setw(62) << "|"; get_red cout << "                                1. ������� ���� �������������"; get_green cout << "                          | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                2. �������� �������������"; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                3. �������� ������������ "; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                4. ��������� ������������"; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                5. �����  � ������� ����"; get_green cout << "                               | " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		get_yellow cout << setw(110) << "                                   ��� ����� ";
		get_red
		cin >> choice;
		no_color
		choice = check(1, 5, choice);
		string login;
		bool result = false;
		bool show = false;
		switch (choice) {
		case 1:
			cout << "_______________________________________________________" << endl;
			cout << "|    �����    |      ������      |     ������ ����    |" << endl;
			cout << "|_____________|__________________|____________________|" << endl;
			for (auto user : users) {
				cout << "|  " << setw(10) << user.getLogin() << " |    " << setw(11)
					<< (user.getIsAvailable() ? "��������" : "�� ��������") << "   |      "
					<< setw(10) << (user.getIsBan() ? "�������" : "�� �������") << "    |" << endl;
				cout << "|_____________|__________________|____________________|" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2:
			for (auto user : users) {
				if (!user.getIsAvailable()) show = true;
			}
			if (!show) {
				cout << "��� ������������ �������������" << endl;
			}
			else {
				cout << "������ ���� �� ����������� �������������" << endl;
				for (auto user : users) {
					if (!user.getIsAvailable()) {
						cout << user.getLogin() << endl;
					}
				}
				cout << "������� ����� ������������, �������� �� ������ �������� : ";
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						cout << "������ ������������ �������, ����� �������� ���, ������� ���������" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login && users[i].getIsAvailable()) {
						cout << "������������ ��� �������� � �������" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login) {
						users[i].setIsAvailable(true);
						cout << "������������ ��������" << endl;
						result = true;
					}
				}
				if (!result) cout << "�� ����� ������������ ����� ������������" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			for (auto user : users) {
				if (!user.getIsBan()) show = true;
			}
			if (!show) {
				cout << "��� ����������� �������������" << endl;
			}
			else {
				cout << "������ ���� ����������� �������������" << endl;
				for (auto user : users) {
					if (!user.getIsBan())	cout << user.getLogin() << endl;
				}
				cout << " ������� ����� ������������, �������� �� ������ �������� : ";
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						cout << "������ ������������ ��� �������" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login && !users[i].getIsBan()) {
						result = true;
						int ch;
						cout << "�� ����� ������ �������� ������������ " << users[i].getLogin() << " ? (1/0)" << endl;
						cin >> ch;
						ch = check(0, 1, ch);
						if (ch == 1) {
							users[i].setIsBan(true);
							cout << "������������ ��� �������" << endl;
						}
						else {
							cout << "�� �������� ������ ������������" << endl;
						}
					}
				}
				if (!result) cout << "�� ����� ������������ �����" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 4:
			for (auto user : users) {
				if (user.getIsBan()) show = true;
			}
			if (!show) {
				cout << "��� ��������� ������������" << endl;
			}
			else {
				cout << "������ ���� ��������� �������������" << endl;
				for (auto user : users) {
					if (user.getIsBan()) cout << user.getLogin() << endl;
				}
				cout << "������� ����� ������������ �������� �� ������ ��������" << endl;
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && !users[i].getIsBan()) {
						cout << "������ ������������ �� �������" << endl;
						result = true;
					}
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						users[i].setIsBan(false);
						cout << "������������ ��� ��������" << endl;
						result = true;
					}
				}
				if (!result) cout << "�� ����� ����� �����������" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:system("cls"); show_menu_for_registr();
		}
	}
}

