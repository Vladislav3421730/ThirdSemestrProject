#include"Flowers.h"
#include<Windows.h>
#include"files.h"
using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	FileManager::CopyFromFile(FILE_OF_MANAGERS, workFithAuthentication::managers);
	FileManager::CopyFromFile(FILE_OF_ADMIN, workFithAuthentication::admins);
	FileManager::CopyFromFile(FILE_OF_USERS, workFithAuthentication::users);
	FileManager::CopyFromFile(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	FileManager::CopyFromFile(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	FileManager::CopyFromFile(FILE_OF_ORDERS, WorkWithOrders::Orders);

	
	FileManager::CopyFlowersToOrder(WorkWithOrders::FlowersForOrders, WorkWithOrders::Orders);
	FileManager::CopyOrdersToUser(WorkWithOrders::Orders, workFithAuthentication::users);

	workFithAuthentication::show_menu_for_registr();

	FileManager::WriteInFile(FILE_OF_USERS, workFithAuthentication::users);
	FileManager::WriteInFile(FILE_OF_ADMIN, workFithAuthentication::admins);
	FileManager::WriteInFile(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	FileManager::WriteInFile(FILE_OF_MANAGERS, workFithAuthentication::managers);
	FileManager::WriteInFile(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	FileManager::WriteInFile(FILE_OF_ORDERS, WorkWithOrders::Orders);
	
}
