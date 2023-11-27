#include"Flowers.h"
#include<Windows.h>
#include"files.h"
using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CopyFromFile(FILE_OF_MANAGERS, workFithAuthentication::managers);
	CopyFromFile(FILE_OF_ADMIN, workFithAuthentication::admins);
	CopyFromFile(FILE_OF_USERS, workFithAuthentication::users);
	CopyFromFile(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	CopyFromFile(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	CopyFromFile(FILE_OF_ORDERS, WorkWithOrders::Orders);

	
	CopyFlowersToOrder(WorkWithOrders::FlowersForOrders, WorkWithOrders::Orders);
	CopyOrdersToUser(WorkWithOrders::Orders, workFithAuthentication::users);

	workFithAuthentication::show_menu_for_registr();

	WriteInFile(FILE_OF_USERS, workFithAuthentication::users);
	WriteInFile(FILE_OF_ADMIN, workFithAuthentication::admins);
	WriteInFile(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	WriteInFile(FILE_OF_MANAGERS, workFithAuthentication::managers);
	WriteInFile(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	WriteInFile(FILE_OF_ORDERS, WorkWithOrders::Orders);
	
}
