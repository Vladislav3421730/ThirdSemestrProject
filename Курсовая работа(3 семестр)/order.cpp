#include"order.h"
#include"passwords.h"
#include"checks.h"
#include<iomanip>
#include<algorithm>

namespace WorkWithOrders {

	vector<Order> Orders;
	vector<FlowerForOrder> FlowersForOrders;
}

void viewTopForOrder() {
	cout << "________________________________________________________________" << endl;
	cout << "|  �  |           �����          |  ���������� | ���� (�� ��) |" << endl;
	cout << "|_____|__________________________|_____________|_______________|" << endl;

}

void MenuForUsers() {

	while (1) {

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
		cout << setw(62) << "|"; get_yellow cout << "                                     ���� ��� ������������                             "; get_green cout << "| " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		cout << setw(62) << "|"; get_blue cout << "                                1. �������� ������"; get_green cout << "                                     | " << endl;
		cout << setw(62) << "|"; get_blue cout << "                                2. ����� ������ "; get_green cout << "                                       | " << endl;
		cout << setw(62) << "|"; get_blue cout << "                                3. ����������� ������"; get_green cout << "                                  | " << endl;
		cout << setw(62) << "|"; get_blue cout << "                                4. ������� ����� "; get_green cout << "                                      | " << endl;
		cout << setw(62) << "|"; get_blue cout << "                                5. ����������� ���� ������ "; get_green cout << "                            | " << endl;
		cout << setw(62) << "|"; get_blue cout << "                                6. ����� �� ��������� "; get_green cout << "                                 | " << endl;
		cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
		get_yellow cout << setw(110) << "                                   ��� ����� ";
		get_red
			int choice;
		cin >> choice;
		no_color
			choice = check(1, 6, choice);
		switch (choice) {
		case 1:  WorkWithFlowers::AllFlowers(WorkWithFlowers::Flowers); system("pause"); system("cls"); break;
		case 2: WorkWithFlowers::searchFlowers(); system("cls"); break;
		case 3: 
		{
			vector<Flower> FlowersCopy;
			for (auto flower : WorkWithFlowers::Flowers) {
				FlowersCopy.push_back(flower);
			}
			WorkWithFlowers::sortFlower(FlowersCopy); 
			system("pause"); 
			system("cls");
			break;
		}
		case 4: WorkWithOrders::MakeOrder();  system("pause"); system("cls"); break;
		case 5: WorkWithOrders::AllOrders(workFithAuthentication::UserPtr->getOrders()); system("pause"); system("cls"); break;
		case 6: return;
		}
	}
}

void WorkWithOrders::MakeOrder() {
	cout << "������� ������ �� ������ �������� � ����� ? (0-���� �� ���������� ������ �����)" << endl;
	int Amount;
	cin >> Amount;
	Amount = check(0, 1100, Amount);
	if (Amount == 0) {
		cout << "�� �����, ��� ������ !" << endl;
		return;
	}
	Order order;
	order.setNumber(WorkWithOrders::Orders.size() + 1);
	cout << "�����, ������� ��������� � ����� ������������" << endl;
	WorkWithFlowers::AllFlowers(WorkWithFlowers::Flowers);
	int totalSum=0;
	for (int i = 0; i < Amount; i++) {
		cout << "������� ����� ������, ������� �� ������ �������� (0-���� ���������� ������� ������) : ";
		int number;
		cin >> number;
		number = check(0, WorkWithFlowers::Flowers.size(), number);
		if (number == 0) {
			cout << "�� ���������� ������� ������" << endl << endl;
			continue;
		}
		FlowerForOrder flowerfororder(WorkWithFlowers::Flowers[number-1]);
		cout << "������� ���������� ������, ������� �� ������ ������ : ";
		int flowersAmount;
		cin >> flowersAmount;
		flowersAmount = check(1, 10000, flowersAmount);
		if (flowersAmount > WorkWithFlowers::Flowers[number - 1].GetAmount()) {
			cout << "��������, �� � ��� ��� ������ ���������� ������" << endl << endl;
			continue;
		}
		WorkWithFlowers::Flowers[number - 1].setAmount(WorkWithFlowers::Flowers[number - 1].GetAmount() - flowersAmount);
		flowerfororder.setAmount(flowersAmount);
		flowerfororder.setCoast(flowersAmount * WorkWithFlowers::Flowers[number - 1].GetCoast());
		totalSum += flowerfororder.GetCoast();
		cout << "\n������ "<< flowerfororder.GetName()<< " � ����������� "<<flowerfororder.GetAmount() << " ��� �������� � �����" << endl;
		order.addFlowerToOrderAtFirst(flowerfororder);
	}
	cout << "\n������� ������ �������� : ";
	string Adress;
	getline(cin, Adress);
	order.setAdress(Adress);
	order.setDate();
	order.setTotalSum(totalSum);
	order.setStatus(OrderStatus::Accepted);
	cout << "��� ����� �������� " << endl;
	workFithAuthentication::UserPtr->addOrderToUserAtFirst(order);
}


void WorkWithOrders::EditOrders() {
	AllOrders(AllOrdersInVector());
	cout << "������� ����� ������, ������� �� ������ ��������������� : ";
	int number;
	cin >> number;
	number = check_on_letters(number);
	if (number <= 0 || number > Orders.size()) {
		cout << "�� ����� ����� ������ �������" << endl;
		return;
	}
	shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[number-1]);
	cout << "����� � " << OrderPtr->getNumber() << endl;
	viewTopForOrder();
	viewOneOrderFlowers(number-1, OrderPtr);
	ViewOneOrder(number-1,OrderPtr);
	cout << "����� ������ �� ������ ��������� ������� ������ ? " << endl;
	cout << "1. ������" << endl;
	cout << "2. ��������������" << endl;
	cout << "3. ����������" << endl;
	cout << "4. ���������" << endl;
	cout << "5. ������" << endl;
	int choice;
	cin >> choice;
	choice = check_on_letters(choice);
	switch (choice)
	{
	case 1: 
		Orders[number - 1].setStatus(OrderStatus::Accepted);
		cout << "������ ������ ��� ������� " << Orders[number - 1].getNumber() << " ��� ������ �� " << Orders[number - 1].getStatus() << endl;
		break;
	case 2:
		Orders[number - 1].setStatus(OrderStatus::Processing);
		cout << "������ ������ ��� ������� " << Orders[number - 1].getNumber() << " ��� ������ �� " << Orders[number - 1].getStatus()<<endl;
		break;
	case 3:
		Orders[number - 1].setStatus(OrderStatus::Packing);
		cout << "������ ������ ��� ������� " << Orders[number - 1].getNumber() << " ��� ������ �� " << Orders[number - 1].getStatus()<<endl;
		break;
	case 4:
		Orders[number - 1].setStatus(OrderStatus::Delivered);
		cout << "������ ������ ��� ������� " << Orders[number - 1].getNumber() << " ��� ������ �� " << Orders[number - 1].getStatus() << endl;
		break;
	case 5:
		cout << "�� �������� ��������� ������� ������" << endl;
		break;
	default:
		cout << "����������� ����� ����� ��������" << endl;
	}
}

vector<shared_ptr<Order>> WorkWithOrders::AllOrdersInVector() {
	vector<shared_ptr<Order>> ptrOrders;
	for (int i = 0; i < Orders.size();i++) {
		shared_ptr<Order> Orderptr = make_shared<Order>(Orders[i]);
		ptrOrders.push_back(Orderptr);
	}
	return ptrOrders;
}

void WorkWithOrders::ViewOneOrder(int i, shared_ptr<Order> Orders) {
	cout << "| ����� ������ ������   | " << setw(8) << Orders->getTotalSum() << "    | ���� ������ |   " << setw(4) << Orders->getDate() << "  |" << endl;
	cout << "|_______________________|_____________|_____________|__________|" << endl;
	cout << "|    ������ ��������    | " << setw(34) << Orders->getAdress() << "   |" << endl;
	cout << "|_______________________|______________________________________|" << endl;
	cout << "|     ������ ������     |       " << setw(24) << Orders->getStatus() << "       |" << endl;
	cout << "|_______________________|______________________________________|" << endl;
}

void WorkWithOrders::AllOrders(vector<shared_ptr<Order>> Orders)
{
	for (int i = 0; i < Orders.size(); i++) {
		cout << "����� � " << Orders[i]->getNumber() << endl;
		viewTopForOrder();
		viewOneOrderFlowers(i,Orders[i]);
		ViewOneOrder(i, Orders[i]);
	}
}
void WorkWithOrders::viewOneOrderFlowers(int i,shared_ptr<Order> Orders) {
	for (int j = 0; j <Orders->getFlowers().size();j++) {
		cout << "| " << setw(3) << j + 1 << " | " << setw(21) << Orders->getFlowers()[j]->GetName() << "    |      " << setw(5) <<
			Orders->getFlowers()[j]->GetAmount() << "  |       "
			<< setw(5) << Orders->getFlowers()[j]->GetCoast() << "   |" << endl;
		cout << "|_____|__________________________|_____________|_______________|" << endl;
	}
}

bool CompareByTotalCoast(Order& obj1, Order& obj2) {
	return obj1.getTotalSum() > obj2.getTotalSum();
}

bool CompareByTotalAmount(Order& obj1, Order& obj2) {
	return obj1.getFlowers().size() > obj2.getFlowers().size();
}

void WorkWithOrders::SortOrders() {
	cout << "�� ������ ��������� �� ������ ������������� ������ ?" << endl;
	cout << "1. ����� ����� ������" << endl;
	cout << "2. �� ���������� ������ � ������" << endl;
	cout << "3. ������ ����������" << endl;
	int choice = 0;
	cin >> choice;
	choice = check_on_letters(choice);
	switch (choice) {
	case 1:
		cout << "��� ������ ���� ������������� �� ����� ����� ������" << endl;
		sort(Orders.begin(),Orders.end(), CompareByTotalCoast);
		AllOrders(AllOrdersInVector());
		break;
	case 2:
		cout << "��� ������ ���� ������������� �� ��������� ������ � ������ " << endl;
		sort(Orders.begin(), Orders.end(), CompareByTotalAmount);
		AllOrders(AllOrdersInVector());
		break;
	case 3:
		cout << "���������� ��������" << endl;
		break;
	default:
		cout << " �� ����������� ����� ����� �������� " << endl;
	}

}
void WorkWithOrders::DeleteOrders() {
	AllOrders(AllOrdersInVector());
	cout << "������� ����� ������, ������� �� ������ ������� (0- ������ ��������) : ";
	int index;
	cin >> index;
	index = check_on_letters(index);
	if (index <= 0 || index > Orders.size()) {
		cout << "�� �� ����� ���������� ����� ������" << endl;
		return;
	}
	shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[index - 1]);
	cout << "����� � " << OrderPtr->getNumber() << endl;
	viewTopForOrder();
	viewOneOrderFlowers(index- 1, OrderPtr);
	ViewOneOrder(index- 1, OrderPtr);
	cout << "�� �������, ��� ������ ������� ���� ����� ? (1/0) : ";
	int choice;
	cin >> choice;
	choice = check(0, 1, choice);
	if (choice == 0) {
		cout << "�� �������� �������� ������ ��� ������� " << OrderPtr->getNumber() << endl;
	}
	else {
		Orders.erase(Orders.begin() + index - 1);
		cout << "����� ��� ������� " << OrderPtr->getNumber() << " ��� �����" << endl;
	}

}

bool ViewOrderByStatus(string status) {
	bool result = false;
	for (int i = 0; i < WorkWithOrders::Orders.size(); i++) {
		shared_ptr<Order> OrderPtr = make_shared<Order>(WorkWithOrders::Orders[i]);
		if (OrderPtr->getStatus() == status) {
			result = true;	
			cout << "����� � " << OrderPtr->getNumber() << endl;
			viewTopForOrder();
			WorkWithOrders::viewOneOrderFlowers(i, OrderPtr);
			WorkWithOrders::ViewOneOrder(i, OrderPtr);
		}
	}
	return result;
}

void WorkWithOrders::SearchOrders() {
	cout << "�� ����� ������������� �� ������ ����� ����� ? " << endl;
	cout << "1. ����� ����� ������ (��������)" << endl;
	cout << "2. ����� ������ " << endl;
	cout << "3. �� �������" << endl;
	cout << "4. ����� � ����" << endl;
	int choice;
	cin >> choice;
	choice = check_on_letters(choice);
	switch (choice) {
	case 1: {
		int MinCoast, MaxCoast;
		cout << "������� ����������� ����� ������ : ";
		cin >> MinCoast;
		MinCoast = check_on_letters(MinCoast);
		cout << "������� ������������ ����� ������ : ";
		cin >> MaxCoast;
		MaxCoast = check_on_letters(MaxCoast);
		bool result = false;
		for (int i = 0; i < Orders.size(); i++) {
			shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[i]);
			if (OrderPtr->getTotalSum() >= MinCoast && OrderPtr->getTotalSum() <= MaxCoast) {
				result = true;
				viewTopForOrder();
				cout << "����� � " << OrderPtr->getNumber() << endl;
				viewOneOrderFlowers(i, OrderPtr);
				ViewOneOrder(i, OrderPtr);
			}
		}
		if (!result) cout << "��� ������� � ����� ���������" << endl;
		break;
	}
	case 2: {
		cout << "������� ����� ������ : ";
		int index;
		cin >> index;
		index = check_on_letters(index);
		if (index <= 0 || index > Orders.size()) {
			cout << "�� ������� ����� ����� ������" << endl;
		}
		else {
			shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[index - 1]);
			viewTopForOrder();
			cout << "����� � " << OrderPtr->getNumber() << endl;
			viewOneOrderFlowers(index, OrderPtr);
			ViewOneOrder(index, OrderPtr);
		}
		break;
	}
	case 3:
	{
		cout << "1. ������" << endl;
		cout << "2. ��������������" << endl;
		cout << "3. ����������" << endl;
		cout << "4. ���������" << endl;
		cout << "�������� � ����� �������� �� ������ ������� ������ : ";
		int choice;
		cin >> choice;
		choice = check(1, 4, choice);
		switch (choice) {
		case 1:
			if (!ViewOrderByStatus("������")) cout << "��� ������� �� �������� ������" << endl;
			break;
		case 2:
			if (!ViewOrderByStatus("��������������")) cout << "��� ������� �� �������� ��������������" << endl;
			break;
		case 3:
			if (!ViewOrderByStatus("����������")) cout << "��� ������� �� �������� ����������" << endl;
			break;
		case 4:
			if (!ViewOrderByStatus("���������")) cout << "��� ������� �� �������� ���������" << endl;
			break;
		}
		break;
	}
	case 4:
		cout << "�� �������� ����� �������" << endl;
		break;
	}
}