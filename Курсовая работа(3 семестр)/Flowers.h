#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Flower;
namespace WorkWithFlowers {

	extern vector<Flower> Flowers;
	extern void addFlower();
	extern void deleteFlower();
	extern void editFlower();
	extern void sortFlower();
	extern void AllFlowers();
	extern void searchFlowers();
	extern void viewOneFlower(int i);
}
extern void menu_for_manager();
extern void MenuForManagerForOrders();
class Flower {
protected:
	string Name;
	int Coast;
	int Amount;
public:
	Flower(){}
	Flower(string Name,int coast,int Amount) {
		this->Amount = Amount;
		this->Name = Name;
		this->Coast = coast;
	}
	Flower(const Flower& flower) {
		this->Amount = flower.Amount;
		this->Name = flower.Name;
		this->Coast = flower.Coast;
	}

	void setName(string Name) {
		this->Name = Name;
	}

	void setCoast(int coast) {
		this->Coast = coast;
	}

	void setAmount(int Amount) {
		this->Amount = Amount;
	}


	string GetName() const {
		return Name;
	}

	int GetCoast() const {
		return Coast;
	}

	int GetAmount() const {
		return Amount;
	}

	friend ostream& operator<<(ostream& os, const Flower& flower) {
		os << flower.GetName() << " " << flower.GetAmount() << " " << flower.GetCoast();
		return os;
	}

	friend istream& operator>>(istream& is, Flower& flower) {
		is >> flower.Name >> flower.Amount >> flower.Coast;
		return is;
	}

};


