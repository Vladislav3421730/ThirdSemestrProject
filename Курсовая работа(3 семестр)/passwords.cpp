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
	cout << setw(62) << "|"; get_yellow cout << "                                      ГЛАВНОЕ МЕНЮ                                     ";get_blue cout<<"| " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	cout << setw(62) << "|"; get_red cout << "                                1. Войти как пользователь";get_blue cout<< "                              | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                2. Войти как администратор"; get_blue cout << "                             | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                3. Войти как менеджер"; get_blue cout << "                                  | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                4. Зарегистрироваться "; get_blue cout << "                                 | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                5. Выйти из программы"; get_blue cout << "                                  | " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	get_yellow cout << setw(110) << "                                   ВАШ ВЫБОР ";
	get_red
	try {
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			no_color
			throw runtime_error("Неправильно ввдён номер операции");
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
			cout << "Данные введены неверно" << endl;
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
			cout << "Данные введены неверно" << endl;
			system("pause");
			system("cls");
			show_menu_for_registr();
		}break;
	case 4:system("cls"); REGISTRATION(); show_menu_for_registr(); break;
	case 5:
		return;
	default: 
		cout << "Неверно введён номер операции" << endl;
		system("pause"); system("cls");
		workFithAuthentication::show_menu_for_registr();
	}

}
extern bool  workFithAuthentication::INPUT_FOR_USERS()
{
	cout << "Вход пользователя" << endl;
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	password = vvod(password);
	password = encryptPassword(password);
	bool result = false;
	for (auto user : users) {
		if (user.getPassword() == password && user.getLogin() == login) {
			result = true;
			if (user.getIsBan()) {
				cout << "Вы были забанены" << endl;
				return false;
			}
			else if (!user.getIsAvailable()) {
				cout << "Ваша заявка ещё не одобрена" << endl;
				return false;
			}
			UserPtr = make_shared<User>(user);
			return true;
		}
	}
	if (!result) {
		cout << "Данные введены неверно" << endl;
	}
	return false;
}
bool  workFithAuthentication::INPUT_FOR_ADMIN()
{
	cout << "Вход администратора" << endl;
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
	password = vvod(password);
	password = encryptPassword(password);
	for (auto admin : admins) {
		if (admin.getPassword() == password && admin.getLogin() == login) return true;
	}
	return false;

}

bool workFithAuthentication::INPUT_FOR_MANAGER()
{
	cout << "Вход для менеджера" << endl;
	string login, password;
	cout << "Логин: ";
	getline(cin, login);
	cout << "Пароль: ";
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
	cout << setw(62) << "|"; get_yellow cout << "                                      РЕГИСТРАЦИЯ                                      "; get_green cout << "| " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	cout << setw(62) << "|"; get_red cout << "                                1. Как пользователь"; get_green cout << "                                    | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                2. Как администратор"; get_green cout << "                                   | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                3. Как менеджер "; get_green cout << "                                       | " << endl;
	cout << setw(62) << "|"; get_red cout << "                                4. Выйти в главное меню"; get_green cout << "                                | " << endl;
	cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
	get_yellow cout << setw(110) << "                                   ВАШ ВЫБОР ";
	get_red
	cin >> n;
	no_color
	n = check(1, 4, n);
	if (n == 1)
	{
		string login, password;
		cout << "Новый логин пользователя: ";
		getline(cin, login);
		cout << "Новый пароль пользователя: ";
		password = vvod(password);
		const int shift = 3;
		for (int i = 0; i < password.length(); i++)
		{
			password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

		}

		User user(login, password, false, false);
		if (check_on_exist(users,user)) cout << "Пользователь с таким ником уже есть в системе" << endl;
		else {
			users.push_back(user);
			cout << "Ваша заявка принята на рассмотрение" << endl;
		}
		system("pause"); system("cls");
	}
	else if (n == 2)
	{
		string special_password;
		int i = 0;
		cout << "Если вы хотите зарегестрироваться как администротор нужен специальный пароль самого хоккейного клуба" << endl;
		special_password = vvod(special_password);
		while (special_password != "q1w2e3" && i < 5)
		{
			cout << "Специальный пароль неверный" << endl;
			special_password = vvod(special_password);
			i++;
		}
		if (i == 5)
		{
			cout << "Вам не удалось ввести специальный пароль цветочной компании" << endl;
		}
		else
		{
			cout << "Новый логин администратора: ";
			string login, password;
			getline(cin, login);
			cout << "Новый пароль администратора: ";
			password = vvod(password);
			const int shift = 3;
			for (int i = 0; i < password.length(); i++)
			{
				password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}

			Admin admin(login, password);
			if (check_on_exist(admins,admin)) cout << "Админ с таким ником уже есть в системе" << endl;
			else {
				admins.push_back(admin);
				cout << "Новый администротор зарегестрирован" << endl;
			}
		}
		system("pause"); system("cls");
	}
	else if (n == 3)
	{
		string special_password;
		int i = 0;
		cout << "Если вы хотите зарегестрироваться как менеджер нужен специальный пароль цветочной компании" << endl;
		special_password = vvod(special_password);
		while (special_password != "q1w2e3" && i < 5)
		{
			cout << "Специальный пароль неверный" << endl;
			special_password = vvod(special_password);
			i++;
		}
		if (i == 5)
		{
			cout << "Вам не удалось ввести специальный пароль хоккейного клуба" << endl;
		}
		else
		{
			cout << "Новый логин менеджера: ";
			string login, password;
			getline(cin, login);
			cout << "Новый пароль менеджера: ";
			password = vvod(password);
			const int shift = 3;
			for (int i = 0; i < password.length(); i++)
			{
				password[i] = (password[i] - ' ' - shift + ('~' - ' ' + 1)) % ('~' - ' ') + ' ';

			}

			Manager manager(login, password);
			if (check_on_exist(managers,manager)) cout << "Менеджер с таким ником уже есть в системе" << endl;
			else {
				managers.push_back(manager);
				cout << "Новый Менеджер зарегестрирован" << endl;
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
		cout << setw(62) << "|"; get_yellow cout << "                                      МЕНЮ ДЛЯ АДМИНИСТРАТОРА                          "; get_green cout << "| " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		cout << setw(62) << "|"; get_red cout << "                                1. Вывести всех пользователей"; get_green cout << "                          | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                2. Добавить пользователей"; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                3. Забанить пользователя "; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                4. Разбанить пользователя"; get_green cout << "                              | " << endl;
		cout << setw(62) << "|"; get_red cout << "                                5. Выйти  в главное меню"; get_green cout << "                               | " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		get_yellow cout << setw(110) << "                                   ВАШ ВЫБОР ";
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
			cout << "|    Логин    |      Статус      |     Статус бана    |" << endl;
			cout << "|_____________|__________________|____________________|" << endl;
			for (auto user : users) {
				cout << "|  " << setw(10) << user.getLogin() << " |    " << setw(11)
					<< (user.getIsAvailable() ? "Добавлен" : "Не добавлен") << "   |      "
					<< setw(10) << (user.getIsBan() ? "Забанен" : "Не забанен") << "    |" << endl;
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
				cout << "Нет недобавленых пользователей" << endl;
			}
			else {
				cout << "Список всех не добавленных пользователей" << endl;
				for (auto user : users) {
					if (!user.getIsAvailable()) {
						cout << user.getLogin() << endl;
					}
				}
				cout << "Введите логин пользователя, которого вы хотите добавить : ";
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						cout << "Данный пользователь забанен, чтобы добавить его, сначала разбаньте" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login && users[i].getIsAvailable()) {
						cout << "Пользователь уже добавлен в систему" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login) {
						users[i].setIsAvailable(true);
						cout << "Пользователь добавлен" << endl;
						result = true;
					}
				}
				if (!result) cout << "Вы ввели неправильный логин пользователя" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 3:
			for (auto user : users) {
				if (!user.getIsBan()) show = true;
			}
			if (!show) {
				cout << "Нет незабаненых пользователей" << endl;
			}
			else {
				cout << "Список всех незабаненых пользователей" << endl;
				for (auto user : users) {
					if (!user.getIsBan())	cout << user.getLogin() << endl;
				}
				cout << " Введите логин пользователя, которого вы хотите забанить : ";
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						cout << "Данный пользователь уже забанен" << endl;
						result = true;
					}
					else if (users[i].getLogin() == login && !users[i].getIsBan()) {
						result = true;
						int ch;
						cout << "Вы точно хотите забанить пользователя " << users[i].getLogin() << " ? (1/0)" << endl;
						cin >> ch;
						ch = check(0, 1, ch);
						if (ch == 1) {
							users[i].setIsBan(true);
							cout << "Пользователь был забанен" << endl;
						}
						else {
							cout << "Вы отменили банить пользователя" << endl;
						}
					}
				}
				if (!result) cout << "Вы ввели неправильный логин" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 4:
			for (auto user : users) {
				if (user.getIsBan()) show = true;
			}
			if (!show) {
				cout << "Нет забаненых пользоватлей" << endl;
			}
			else {
				cout << "Список всех забаненых пользователей" << endl;
				for (auto user : users) {
					if (user.getIsBan()) cout << user.getLogin() << endl;
				}
				cout << "Введите логин пользователя которого вы хотите забанить" << endl;
				cin >> login;
				for (int i = 0; i < users.size(); i++) {
					if (users[i].getLogin() == login && !users[i].getIsBan()) {
						cout << "Данный пользователь не забанен" << endl;
						result = true;
					}
					if (users[i].getLogin() == login && users[i].getIsBan()) {
						users[i].setIsBan(false);
						cout << "Пользователь был разбанен" << endl;
						result = true;
					}
				}
				if (!result) cout << "Вы ввели логин неправильно" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:system("cls"); show_menu_for_registr();
		}
	}
}

