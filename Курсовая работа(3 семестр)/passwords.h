#pragma once
#include<iostream>
#include<vector>
#include"Flowers.h"
#include"order.h"

#define get_blue  SetConsoleTextAttribute(console, 9);
#define get_yellow  SetConsoleTextAttribute(console, 6);
#define get_green  SetConsoleTextAttribute(console, 2);
#define get_red     SetConsoleTextAttribute(console, 4);
#define no_color  SetConsoleTextAttribute(console, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

using namespace std;

class User;
class Admin;
class Manager;
namespace workFithAuthentication
{
	extern vector<Admin> admins;
	extern vector<User> users;
	extern vector<Manager> managers;
	extern shared_ptr<User> UserPtr;
	extern void show_menu_for_registr();
	extern bool INPUT_FOR_USERS();
	extern bool INPUT_FOR_ADMIN();
	extern bool INPUT_FOR_MANAGER();
	extern void REGISTRATION();
	extern void menu_for_work_with_users();
}



class CommonInterface {
protected:
	string password;
	string login;
public:
	CommonInterface() {}
	CommonInterface(string login, string password) {
		this->login = login;
		this->password = password;
	}
	string getPassword() const  {
		return password;
	}

	void setPassword(string Password) {
		this->password = Password;
	}

	string getLogin() const {
		return login;
	}

	void setLogin(string Login) {
		this->login = Login;
	}

	virtual void displayInformation() = 0;

};

class Admin : public CommonInterface {
public:
	Admin() {}
	Admin(string login, string password) : CommonInterface(login, password) {};

	friend ostream& operator<<(ostream& os, const Admin& admin) {
		os << admin.getLogin() << " " << admin.getPassword();
		return os;
	}

	void displayInformation() override {
		cout << "Admin Information: Login = " << login << ", Password = " << password << endl;
	}

	friend istream& operator>>(istream& is, Admin& admin) {
		is >> admin.login >> admin.password;
		return is;
	}
};


class Manager: public CommonInterface {
public:
	Manager() {}
	Manager(string login, string password) : CommonInterface(login, password) {};

	friend ostream& operator<<(ostream& os, const Manager& Manager) {
		os << Manager.getLogin() << " " << Manager.getPassword();
		return os;
	}

	void displayInformation() override {
		cout << "Manager Information: Login = " << login << ", Password = " << password << endl;
	}

	friend istream& operator>>(istream& is, Manager& Manager) {
		is >> Manager.login >> Manager.password;
		return is;
	}
};



class User : public CommonInterface {
private:
	bool isAvailable;
	bool isBan;
	vector<shared_ptr<Order>> orders;
public:
	User() {
		this->isAvailable = false;
		this->isBan = false;
	}
	User(string login, string password, bool isAvailable, bool isBan)
		: CommonInterface(login, password) {
		this->isAvailable = isAvailable;
		this->isBan = isBan;
	}
	bool getIsAvailable() const {
		return isAvailable;
	}


	void setIsAvailable(bool IsAvailable) {
		this->isAvailable = IsAvailable;
	}

	bool getIsBan() const {
		return isBan;
	}

	vector<shared_ptr<Order>> getOrders() {
		return orders;
	}

	void addOrderToUser(Order order) {
		shared_ptr<Order> Orderptr = make_shared<Order>(order);
		orders.push_back(Orderptr);
	}

	void addOrderToUserAtFirst(Order& order) {
		order.setUserLogin(login);
		shared_ptr<Order> Orderptr = make_shared<Order>(order);
		WorkWithOrders::Orders.push_back(order);
		orders.push_back(Orderptr);
	}

	void setIsBan(bool IsBan) {
		this->isBan = IsBan;
	}

	void displayInformation() override {
		cout << "User Information: Login = " << login << ", Password = " << password << endl;
	}


	friend ostream& operator<<(ostream& os, const User& user) {
		os << user.getLogin() << " " << user.getPassword() << " " << user.getIsAvailable() << " " << user.getIsBan();
		return os;
	}

	friend istream& operator>>(istream& is, User& user) {
		is >> user.login >> user.password >> user.isAvailable >> user.isBan;
		return is;
	}
};
