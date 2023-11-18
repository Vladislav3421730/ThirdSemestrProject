
#include"checks.h"
#include<iomanip>
#include<algorithm>
#include<conio.h>
#include"files.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13


const string FILE_OF_ORDERS = "FileForOrders.dat";
const string FILE_OF_FLOWERS_FOR_ORDERS = "FileForFlowersForOrder.dat";
const string FILE_OF_FLOWERS = "FileForFlowers.dat";

namespace WorkWithOrders {

	vector<Order> Orders;
	vector<FlowerForOrder> FlowersForOrders;
}

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void d(short x, short y)
{
	SetConsoleCursorPosition(h, { x,y });
}

void viewTopForOrder() {
	cout << "________________________________________________________________" << endl;
	cout << "|  №  |           Цветы          |  Количетсво | Цена (за всё) |" << endl;
	cout << "|_____|__________________________|_____________|_______________|" << endl;

}


void MenuForUsers() {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		cout<<setw(126)  << "________________________________________" << endl;
		cout << setw(94) << "|       "; 
		get_red cout << " МЕНЮ ДЛЯ ПОЛЬЗОВАТЕЛЯ"; no_color
		cout<<"         |" << endl;
		cout << setw(126) << "|______________________________________|" << endl;
		char aT = 0;
		char c;
		string T[] = {										
															"|        1. Просмотр цветов            |",
															"|        2. Поиск цветов               |",
															"|        3. Сортировка цветов          |",
															"|        4. Сделать заказ              |",                         
								                            "|        5. Просмотреть заказы         |",
								                            "|        6. Выйти из программы         |"
		};
		while (true)
		{
			char x = 86, y = 3;
			d(x, y);
			for (char i = 0; i < size(T); i++)
			{
				if (i == aT)  SetConsoleTextAttribute(h, FOREGROUND_RED);
				else  SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
				d(x, y++);
				cout << T[i] << endl;
			}
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout << setw(126) << "|______________________________________|" << endl;
			c = _getch();
			if (c == -32) c = _getch();
			switch (c)
			{
			case ESC:
				exit(0);
			case UP:
				if (aT > 0)	--aT;
				break;
			case DOWN:
				if (aT < size(T) - 1)	++aT;
				break;
			case ENTER:
				
				switch (aT)
				{
					
				case 0:
				{
					d(x, y);
					cout << "\n\n\n";
					WorkWithFlowers::AllFlowers(WorkWithFlowers::Flowers);
					system("pause"); system("cls");
					MenuForUsers();
					break;
				}
				case 1:
				{
					d(x, y);
					cout << "\n\n\n";
					WorkWithFlowers::searchFlowers();
					MenuForUsers();
					break;
				}
				case 2:
				{
					d(x, y);
					cout << "\n\n\n";
					vector<Flower> FlowersCopy;
					for (auto flower : WorkWithFlowers::Flowers) {
						FlowersCopy.push_back(flower);
					}
					WorkWithFlowers::sortFlower(FlowersCopy);
					MenuForUsers();
					break;
				}
				case 3:
				{
					d(x, y);
					cout << "\n\n\n";
					WorkWithOrders::MakeOrder();
					system("pause"); system("cls");
					MenuForUsers();
					break;
				}
				case 4:
				{
					d(x, y);
					cout << "\n\n\n";
					WorkWithOrders::AllOrders(workFithAuthentication::UserPtr->getOrders());
					system("pause"); system("cls");
					MenuForUsers(); 
					break;
				}
				case 5:
				{
					d(x, y);
					cout << "\n\n\n";
					write_in_file(FILE_OF_ORDERS, WorkWithOrders::Orders);
					write_in_file(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
					write_in_file(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
					exit(0);
					return;
			
				}
				default: cout << "" << (char)c << endl;
				}
			}
		}
}

void WorkWithOrders::MakeOrder() {
	
	cout << "Сколько цветов вы хотите добавить в заказ ? (0-если вы передумали делать заказ)" << endl;
	int Amount;
	cin >> Amount;
	Amount = check(0, 1100, Amount);
	if (Amount == 0) {
		cout << "Ну ладно, как хотите !" << endl;
		return;
	}
	Order order;
	order.setNumber(Orders.size()+2);
	cout << "Цветы, которые досступны в нашем ассортименте" << endl;
	WorkWithFlowers::AllFlowers(WorkWithFlowers::Flowers);
	int totalSum=0;
	for (int i = 0; i < Amount; i++) {
		cout << "Введите номер цветка, который вы хотите добавить (0-если передумали вводить цветок) : ";
		int number;
		cin >> number;
		number = check(0, WorkWithFlowers::Flowers.size(), number);
		if (number == 0) {
			cout << "Вы передумали вводить цветок" << endl << endl;
			continue;
		}
		FlowerForOrder flowerfororder(WorkWithFlowers::Flowers[number-1]);
		cout << "Введите количество цветов, которое вы хотите купить : ";
		int flowersAmount;
		cin >> flowersAmount;
		flowersAmount = check(1, 10000, flowersAmount);
		if (flowersAmount > WorkWithFlowers::Flowers[number - 1].GetAmount()) {
			cout << "Извините, но у нас нет такого количества цветов" << endl << endl;
			continue;
		}
		WorkWithFlowers::Flowers[number - 1].setAmount(WorkWithFlowers::Flowers[number - 1].GetAmount() - flowersAmount);
		flowerfororder.setAmount(flowersAmount);
		flowerfororder.setCoast(flowersAmount * WorkWithFlowers::Flowers[number - 1].GetCoast());
		totalSum += flowerfororder.GetCoast();
		cout << "\nЦветок "<< flowerfororder.GetName()<< " с количеством "<<flowerfororder.GetAmount() << " был добавлен в заказ" << endl;
		order.addFlowerToOrderAtFirst(flowerfororder);
	}
	if (order.getFlowers().empty()) {
		cout << "В заказ не было добавлено ни одного цветка, цветок не может быть добавлен" << endl;
		return;
	}
	cout << "\nВведите адресс доставки : ";
	string Adress;
	getline(cin, Adress);
	order.setAdress(Adress);
	order.setDate();
	order.setTotalSum(totalSum);
	order.setStatus(OrderStatus::Accepted);
	cout << "Ваш заказ добавлен " << endl;
	workFithAuthentication::UserPtr->addOrderToUserAtFirst(order);
}


void WorkWithOrders::EditOrders() {
	AllOrders(AllOrdersInVector());
	cout << "Введите номер заказа, который вы хотите отредактировать : ";
	int number;
	cin >> number;
	number = check_on_letters(number);
	bool result = false;
	for (int i = 0; i < Orders.size(); i++) {
		if (Orders[i].getNumber() == number) {
			number = i + 1;
			result = true;
		}
	}
	if (!result) {
		cout << "Вы ввели неверный номер заказа" << endl;
		return;
	}
	shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[number-1]);
	cout << "ЗАКАЗ № " << OrderPtr->getNumber() << endl;
	viewTopForOrder();
	viewOneOrderFlowers(number-1, OrderPtr);
	ViewOneOrder(number-1,OrderPtr);
	cout << "Какой статус вы хотите присвоить данному заказу ? " << endl;
	cout << "1. Принят" << endl;
	cout << "2. Обрабатывается" << endl;
	cout << "3. Собирается" << endl;
	cout << "4. Доставлен" << endl;
	cout << "5. Отмена" << endl;
	int choice;
	cin >> choice;
	choice = check_on_letters(choice);
	switch (choice)
	{
	case 1: 
		Orders[number - 1].setStatus(OrderStatus::Accepted);
		cout << "Статус заказа под номером " << Orders[number - 1].getNumber() << " был изменён на " << Orders[number - 1].getStatus() << endl;
		break;
	case 2:
		Orders[number - 1].setStatus(OrderStatus::Processing);
		cout << "Статус заказа под номером " << Orders[number - 1].getNumber() << " был изменён на " << Orders[number - 1].getStatus()<<endl;
		break;
	case 3:
		Orders[number - 1].setStatus(OrderStatus::Packing);
		cout << "Статус заказа под номером " << Orders[number - 1].getNumber() << " был изменён на " << Orders[number - 1].getStatus()<<endl;
		break;
	case 4:
		Orders[number - 1].setStatus(OrderStatus::Delivered);
		cout << "Статус заказа под номером " << Orders[number - 1].getNumber() << " был изменён на " << Orders[number - 1].getStatus() << endl;
		break;
	case 5:
		cout << "Вы отменили изменение статуса заказа" << endl;
		break;
	default:
		cout << "Неправильно введён номер операции" << endl;
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
	cout << "| Общая суммма заказа   | " << setw(8) << Orders->getTotalSum() << "    | Дата заказа |   " << setw(4) << Orders->getDate() << "  |" << endl;
	cout << "|_______________________|_____________|_____________|__________|" << endl;
	cout << "|    Адресс доставки    | " << setw(34) << Orders->getAdress() << "   |" << endl;
	cout << "|_______________________|______________________________________|" << endl;
	cout << "|     СТАТУС ЗАКАЗА     |       " << setw(24) << Orders->getStatus() << "       |" << endl;
	cout << "|_______________________|______________________________________|" << endl;
}

void WorkWithOrders::AllOrders(vector<shared_ptr<Order>> Orders)
{
	if (Orders.empty()) {
		cout << "ЗАКАЗОВ НЕТ" << endl;
		return;
	}

	for (int i = 0; i < Orders.size(); i++) {
		cout << "ЗАКАЗ № " << Orders[i]->getNumber() << endl;
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
	cout << "По какоку параметру вы хотите отсортировать заказы ?" << endl;
	cout << "1. Общая сумма заказа" << endl;
	cout << "2. По количеству цветов в заказе" << endl;
	cout << "3. Отмена сортировки" << endl;
	int choice = 0;
	try {
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			throw runtime_error("Вы неверно ввыели номер операции");
		}
	}
	catch (runtime_error& e) {
		cout << e.what()<< endl;
		system("pause");system("cls");
		return;
	}
	
	switch (choice) {
	case 1:
		cout << "Все заказы были отсортированы по обшей сумме заказа" << endl;
		sort(Orders.begin(),Orders.end(), CompareByTotalCoast);
		AllOrders(AllOrdersInVector());
		break;
	case 2:
		cout << "Все заказы были отсортированы по количесву цветов в заказе " << endl;
		sort(Orders.begin(), Orders.end(), CompareByTotalAmount);
		AllOrders(AllOrdersInVector());
		break;
	case 3:
		system("cls");
		return;
	default:
		cout << " Вы неправильно ввели номер операции " << endl;
	}
	system("pause"); system("cls");

}
void WorkWithOrders::DeleteOrders() {
	AllOrders(AllOrdersInVector());
	cout << "Введите номер заказа, который вы хотите удалить (0- отмена удаления) : ";
	int index;
	cin >> index;
	index = check_on_letters(index);
	bool result = false;
	for (int i = 0; i < Orders.size(); i++) {
		if (Orders[i].getNumber() == index) {
			index = i;
			result = true;
		}
	}
	if (!result) {
		cout << "Вы ввели неверный номер заказа" << endl;
		return;
	}
	shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[index]);
	cout << "ЗАКАЗ № " << OrderPtr->getNumber() << endl;
	viewTopForOrder();
	viewOneOrderFlowers(index, OrderPtr);
	ViewOneOrder(index, OrderPtr);
	cout << "Вы уверены, что хотите удалить этот заказ ? (1/0) : ";
	int choice;
	cin >> choice;
	choice = check(0, 1, choice);
	if (choice == 0) {
		cout << "Вы отменили удаление товара под номером " << OrderPtr->getNumber() << endl;
	}
	else {
		Orders.erase(Orders.begin() + index);
		cout << "Заказ под номером " << OrderPtr->getNumber() << " был удалён" << endl;
	}

}

bool ViewOrderByStatus(string status) {
	bool result = false;
	for (int i = 0; i < WorkWithOrders::Orders.size(); i++) {
		shared_ptr<Order> OrderPtr = make_shared<Order>(WorkWithOrders::Orders[i]);
		if (OrderPtr->getStatus() == status) {
			result = true;	
			cout << "ЗАКАЗ № " << OrderPtr->getNumber() << endl;
			viewTopForOrder();
			WorkWithOrders::viewOneOrderFlowers(i, OrderPtr);
			WorkWithOrders::ViewOneOrder(i, OrderPtr);
		}
	}
	return result;
}

void WorkWithOrders::SearchOrders() {
	cout << "По какой характеристке вы хотите найти заказ ? " << endl;
	cout << "1. Общая сумма заказа (Диапазон)" << endl;
	cout << "2. Номер заказа " << endl;
	cout << "3. По статусу" << endl;
	cout << "4. Выйти в меню" << endl;
	int choice;
	try {
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			throw runtime_error("Вы ввели неверный номер операции");
		}
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
		system("pause"); system("cls");
		return;
	}
	switch (choice) {
	case 1: {
		int MinCoast, MaxCoast;
		cout << "Введите минимальную сумму заказа : ";
		cin >> MinCoast;
		MinCoast = check_on_letters(MinCoast);
		cout << "Введите максимальную сумму заказа : ";
		cin >> MaxCoast;
		MaxCoast = check_on_letters(MaxCoast);
		bool result = false;
		for (int i = 0; i < Orders.size(); i++) {
			shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[i]);
			if (OrderPtr->getTotalSum() >= MinCoast && OrderPtr->getTotalSum() <= MaxCoast) {
				result = true;
				cout << "ЗАКАЗ № " << OrderPtr->getNumber() << endl;
				viewTopForOrder();
				viewOneOrderFlowers(i, OrderPtr);
				ViewOneOrder(i, OrderPtr);
			}
		}
		if (!result) cout << "Нет заказов в таком диапазоне" << endl;
		break;
	}
	case 2: {
		cout << "Введите номер заказа : ";
		int index;
		cin >> index;
		index = check_on_letters(index);
		if (index <= 0 || index > Orders.size()) {
			cout << "Вы неверно ввели номер заказа" << endl;
		}
		else {
			shared_ptr<Order> OrderPtr = make_shared<Order>(Orders[index - 1]);
			cout << "ЗАКАЗ № " << OrderPtr->getNumber() << endl;
			viewTopForOrder();
			viewOneOrderFlowers(index, OrderPtr);
			ViewOneOrder(index, OrderPtr);
		}
		break;
	}
	case 3:
	{
		cout << "1. Принят" << endl;
		cout << "2. Обрабатывается" << endl;
		cout << "3. Собирается" << endl;
		cout << "4. Доставлен" << endl;
		cout << "Выберете с каким статусом вы хотите вывести заказы : ";
		int choice;
		cin >> choice;
		choice = check(1, 4, choice);
		switch (choice) {
		case 1:
			if (!ViewOrderByStatus("Принят")) cout << "Нет заказов со статусом Принят" << endl;
			break;
		case 2:
			if (!ViewOrderByStatus("Обрабатывается")) cout << "Нет заказов со статусом Обрабатывается" << endl;
			break;
		case 3:
			if (!ViewOrderByStatus("Собирается")) cout << "Нет заказов со статусом Собирается" << endl;
			break;
		case 4:
			if (!ViewOrderByStatus("Доставлен")) cout << "Нет заказов со статусом Доставлен" << endl;
			break;
		}
		break;
	}
	case 4:
		system("cls");
		return;
	default: cout << "Вы ввели неверный номер операции" << endl; system("pause"); system("cls");
	}
	system("pause"); system("cls");
}