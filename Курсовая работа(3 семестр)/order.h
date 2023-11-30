#pragma once
#include"Flowers.h"
#include<string>
#include<Windows.h>
#include <sstream>

class Order;
class FlowerForOrder;
namespace WorkWithOrders {
	extern vector<Order> Orders;
	extern vector<FlowerForOrder> FlowersForOrders;
	extern void MakeOrder();
	extern void SortOrders();
	extern void AllOrders(vector<shared_ptr<Order>> Orders);
	extern void ViewOneOrder(int i, shared_ptr<Order> Orders);
	extern vector<shared_ptr<Order>> AllOrdersInVector();
	extern void EditOrders();
	extern void DeleteOrders();
	extern void SearchOrders();
	extern void viewOneOrderFlowers(int i, shared_ptr<Order> Orders);
}
extern void MenuForUsers();

class FlowerForOrder : public Flower
{
private:
	int OrderNumber;
public:
	FlowerForOrder() {}
	FlowerForOrder(string Name, int Amount, int coast) : Flower(Name, Amount, coast) {}
	FlowerForOrder(Flower flower) {
		this->Name = flower.GetName();
	}

	int getOrderNumber() const {
		return OrderNumber;
	}

	void setOrderNumber(int OrderNumber) {
		this->OrderNumber = OrderNumber;
	}

	friend ostream& operator<<(ostream& os, const FlowerForOrder& flower) {
		os << flower.GetName() << " " << flower.GetAmount() << " " << flower.GetCoast() << " " << flower.getOrderNumber();
		return os;
	}

	friend istream& operator>>(istream& is, FlowerForOrder& flower) {
		is >> flower.Name >> flower.Amount >> flower.Coast >> flower.OrderNumber;
		return is;
	}

};


enum OrderStatus { Accepted, Processing, Packing, Delivered };

class Order
{
private:
	
	int Number;
	vector<shared_ptr<FlowerForOrder>> Flowers;
	string UserLogin;
	string Date;
	string Adress;
	string Status;
	int TotalSum;

public:

	Order() {}

	void setNumber(int Number) {
		this->Number = Number;
	}

	void setStatus(OrderStatus status) {
		switch (status) {
		case OrderStatus::Accepted:
			this->Status = "Принят";
			break;
		case OrderStatus::Processing:
			this->Status = "Обрабатывается";
			break;
		case OrderStatus::Packing:
			this->Status = "Собирается";
			break;
		case OrderStatus::Delivered:
			this->Status = "Доставлен";
			break;
		default:
			this->Status = "Неизвестный статус";
			break;
		}
	}

	string getStatus() const {
		return Status;
	}

	void setAdress(string adress) {
		this->Adress = adress;
	}

	void setTotalSum(int TotalSum) {
		this->TotalSum = TotalSum;
	}

	void setUserLogin(string login) {
		this->UserLogin = login;
	}

	string getUserLogin() const {
		return UserLogin;
	}

	string getAdress() const {
		return Adress;
	}

	int getNumber() const {
		return Number;
	}

	int getTotalSum() const {
		return TotalSum;
	}

	void setDate() {

		int day, month, hour, minuts;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		struct tm localtime;
		time_t now = time(NULL);
		localtime_s(&localtime, &now);
		day = localtime.tm_mday;
		month = 1 + localtime.tm_mon;

		string strDay = std::to_string(day);
		string strMonth = std::to_string(month);

		this->Date = strDay + "/" + strMonth;

	}

	string getDate() const {
		return Date;
	}

	vector<shared_ptr<FlowerForOrder>> getFlowers()  {
		return Flowers;
	}

	void addFlowerToOrder(FlowerForOrder flower) {
		shared_ptr<FlowerForOrder> flowerPtr = make_shared<FlowerForOrder>(flower);
		Flowers.push_back(flowerPtr);
	}

	void addFlowerToOrderAtFirst(FlowerForOrder &flower) {
		flower.setOrderNumber(Number);
		shared_ptr<FlowerForOrder> flowerPtr = make_shared<FlowerForOrder>(flower);
		WorkWithOrders::FlowersForOrders.push_back(flower);
		Flowers.push_back(flowerPtr);
	}

	friend ostream& operator<<(ostream& os, const Order& order) {
		os << order.getNumber() << " " << order.getTotalSum()<< " "<< order.getStatus() << " " << order.getDate()<<" " << order.getUserLogin() << "  " << order.getAdress() << "  ";
		return os;
	}

	friend istream& operator>>(istream& is, Order& order) {
		string line;
		if (getline(is, line)) {
			istringstream iss(line);
			iss >> order.Number >> order.TotalSum>> order.Status >> order.Date>>order.UserLogin;
			order.Adress = "";
			string part;
			while (iss >> part) {
				order.Adress += part;
				if (iss.peek() == ' ') {
					order.Adress += "  ";
					iss.get();
				}
			}

		}
		return is;
	}
};