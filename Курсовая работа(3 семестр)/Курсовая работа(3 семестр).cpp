#include"passwords.h"
#include"Flowers.h"
#include"order.h"
#include<Windows.h>
#include"files.h"
using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const string FILE_OF_ADMIN = "FileForAdmins.dat";
	const string FILE_OF_USERS = "FileForUsers.dat";
	const string FILE_OF_FLOWERS = "FileForFlowers.dat";
	const string FILE_OF_MANAGERS = "FileForMenegers.dat";
	const string FILE_OF_FLOWERS_FOR_ORDERS = "FileForFlowersForOrder.dat";
	const string FILE_OF_ORDERS = "FileForOrders.dat";
	
	copy_from_file(FILE_OF_MANAGERS, workFithAuthentication::managers);
	copy_from_file(FILE_OF_ADMIN, workFithAuthentication::admins);
	copy_from_file(FILE_OF_USERS, workFithAuthentication::users);
	copy_from_file(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	copy_from_file(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	copy_from_file(FILE_OF_ORDERS, WorkWithOrders::Orders);

	
	CopyFlowersToOrder(WorkWithOrders::FlowersForOrders, WorkWithOrders::Orders);
	CopyOrdersToUser(WorkWithOrders::Orders, workFithAuthentication::users);

	workFithAuthentication::show_menu_for_registr();


	write_in_file(FILE_OF_USERS, workFithAuthentication::users);
	write_in_file(FILE_OF_ADMIN, workFithAuthentication::admins);
	write_in_file(FILE_OF_FLOWERS, WorkWithFlowers::Flowers);
	write_in_file(FILE_OF_MANAGERS, workFithAuthentication::managers);
	write_in_file(FILE_OF_FLOWERS_FOR_ORDERS, WorkWithOrders::FlowersForOrders);
	write_in_file(FILE_OF_ORDERS, WorkWithOrders::Orders);
	
}
