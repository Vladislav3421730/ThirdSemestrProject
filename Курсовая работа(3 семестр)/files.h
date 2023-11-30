#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"order.h"
#include"passwords.h"
using namespace std;

const string FILE_OF_ADMIN = "FileForAdmins.dat";
const string FILE_OF_USERS = "FileForUsers.dat";
const string FILE_OF_FLOWERS = "FileForFlowers.dat";
const string FILE_OF_MANAGERS = "FileForMenegers.dat";
const string FILE_OF_FLOWERS_FOR_ORDERS = "FileForFlowersForOrder.dat";
const string FILE_OF_ORDERS = "FileForOrders.dat";



class FileManager {
public:

    template<class T>
    static void WriteInFile(const string& filename, const vector<T>& vector) {
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
    static void CopyFromFile(const string& filename, vector<T>& vector) {
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

    static void CopyFlowersToOrder(vector<FlowerForOrder>& flowers, vector<Order>& orders) {
        for (auto& order : orders) {
            for (auto& flower : flowers) {
                if (order.getNumber() == flower.getOrderNumber()) {
                    order.addFlowerToOrder(flower);
                }
            }
        }
    }

    static void CopyOrdersToUser(vector<Order>& orders, vector<User>& users) {
        for (auto& user : users) {
            for (auto& order : orders) {
                if (user.getLogin() == order.getUserLogin()) {
                    user.addOrderToUser(order);
                }
            }
        }
    }
};
