#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"order.h"
#include"passwords.h"
using namespace std;

template<class T>
extern void write_in_file(const string filename, vector<T> vector) {
	ofstream file(filename, ios::binary);
	if (!file) {
		cout << "Ошибка открытия файла " << filename << endl;
		return;
	}
	for (const T& obj : vector) {
		file << obj << endl;
	}
	file.close();
}

template<class T>
extern void copy_from_file(const string filename, vector<T> &vector) {
	ifstream file(filename, ios::binary);
		if (!file) {
			cout << "Ошибка открытия файла " << filename << endl;
				return;
		}
	T obj;
	while (file >> obj) {
		vector.push_back(obj);
	}
	file.close();
}
extern void CopyFlowersToOrder(vector<FlowerForOrder> &flowers, vector<Order> &orders)
{
	for (auto& order : orders) {
		for (auto &flower : flowers) {
			if (order.getNumber() == flower.getOrderNumber()){
				order.addFlowerToOrder(flower);
			}
		}
	}
}

extern void CopyOrdersToUser(vector<Order> & orders, vector<User>& users)
{
	for (auto& user : users) {
		for (auto& order : orders) {
			if (user.getLogin() == order.getUserLogin()) {
				user.addOrderToUser(order);
			}
		}
	}
}