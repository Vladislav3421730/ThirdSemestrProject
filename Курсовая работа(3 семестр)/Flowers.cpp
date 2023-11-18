
#include<fstream>
#include<iomanip>
#include<algorithm>
#include"Flowers.h"
#include"checks.h"
#include"passwords.h"
#include<Windows.h>

namespace WorkWithFlowers {
    vector<Flower> Flowers;
}


void viewTop() {
    cout << "___________________________________________________________________________" << endl;
    cout << "|   №   |      Название цветка     | Количесвто на складе | Цена за штуку |" << endl;
    cout << "|_______|__________________________|______________________|_______________|" << endl;
}

void MenuForManagerForOrders() {
    int choice = 0;
    while (choice != 6) {

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
        cout << setw(62) << "|"; get_yellow cout << "                                     МЕНЮ ДЛЯ РАБОТЫ С ЗАКАЗАМИ                        "; get_green cout << "| " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        cout << setw(62) << "|"; get_blue cout << "                                1. Вывести все заказы"; get_green cout << "                                  | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                2. Сортировка заказов "; get_green cout << "                                 | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                3. Редактирование заказов"; get_green cout << "                              | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                4. Удаление заказов"; get_green cout << "                                    | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                5. Поиск заказов"; get_green cout << "                                       | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                6. Выйти в меню "; get_green cout << "                                       | " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        get_yellow cout << setw(110) << "                                   ВАШ ВЫБОР ";
        get_red
            try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                no_color
                    throw runtime_error("Неправильно ввдён номер операции");
            }
        }
        catch (runtime_error e) {
            cout << e.what() << endl;
            system("pause"); system("cls");
            continue;
        }
        no_color
        switch (choice) {
        case 1: {
            WorkWithOrders::AllOrders(WorkWithOrders::AllOrdersInVector());
            system("pause"); system("cls");
        }break;
        case 2: WorkWithOrders::SortOrders(); break;
        case 3: WorkWithOrders::EditOrders(); system("pause"); system("cls"); break;
        case 4: WorkWithOrders::DeleteOrders(); system("pause"); system("cls"); break;
        case 5: WorkWithOrders::SearchOrders(); break;
        case 6: system("cls"); menu_for_manager(); system("cls"); return; break;
        default: cout << "Неверно введён номер операции" << endl; system("pause"); system("cls");
        }
    }
}

void menu_for_manager() {
    int choice = 0;
	while (choice!=7) {

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
        cout << setw(62) << "|"; get_yellow cout << "                                     МЕНЮ ДЛЯ МЕНЕДЖЕРА                                "; get_green cout << "| " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        cout << setw(62) << "|"; get_blue cout << "                                1. Добавить новый цветок (для продажи)"; get_green cout << "                 | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                2. Вывести доступные цветы "; get_green cout << "                            | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                3. Редактирование"; get_green cout << "                                      | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                4. Удаление"; get_green cout << "                                            | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                5. Сортировкка "; get_green cout << "                                        | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                6. Поиск "; get_green cout << "                                              | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                7. Работа с заказами "; get_green cout << "                                  | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                8. Выйти из главное меню "; get_green cout << "                              | " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        get_yellow cout << setw(110) << "                                   ВАШ ВЫБОР ";
        get_red
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                no_color
                throw runtime_error("Неправильно ввдён номер операции");
            }
        }
        catch(runtime_error e){
            cout <<e.what() << endl;
            system("pause"); system("cls");
            continue;
        }
        no_color
		switch (choice) {
        case 1:  WorkWithFlowers::addFlower(); system("pause"); system("cls"); break;
        case 2:  WorkWithFlowers::AllFlowers(WorkWithFlowers::Flowers); system("pause"); system("cls"); break;
        case 3:  WorkWithFlowers::editFlower(); system("pause"); system("cls");   break;
        case 4:  WorkWithFlowers::deleteFlower(); system("pause"); system("cls"); break;
        case 5:  WorkWithFlowers::sortFlower(WorkWithFlowers::Flowers); break;
        case 6:  WorkWithFlowers::searchFlowers();  system("cls"); break;
        case 7:system("cls"); MenuForManagerForOrders(); system("cls"); break;
        case 8:system("cls"); workFithAuthentication::show_menu_for_registr(); return;  break;
        default: cout << "Неверно введён номер операции" << endl; system("pause"); system("cls");
		}
	}
}
void  WorkWithFlowers::addFlower() {
    int n;
    cout << "Сколько цветов вы хотите добавить в ассортимент?" << endl;
    cin >> n;
    n = check_on_letters(n);
    int size = Flowers.size();
    for (int i = size; i < size + n; i++) {
        shared_ptr<Flower> flower_ptr = make_shared<Flower>();
        string name;
        int coast, amount;
        cout << "Введите название цветка : ";
        cin >> name;
        flower_ptr->setName(name);
        cout << "Введите количесвто цветов на складе : ";
        cin >> amount;
        amount = check_on_letters(amount);
        flower_ptr->setAmount(amount);
        cout << "Введите цену за один цветок : ";
        cin >> coast;
        coast = check_on_letters(coast);
        flower_ptr->setCoast(coast);
        Flowers.push_back(*flower_ptr);
        cout << endl;
    }
}
void WorkWithFlowers::deleteFlower() {
    AllFlowers(Flowers);
    cout << "Введите номер цветка, который вы хотите удалить : ";
    int index;
    cin >> index;
    try  {
        Flowers.at(index - 1);
    } catch (out_of_range &e) {
        cout << "Вы ввели неверный номер цветка" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    viewTop();
    WorkWithFlowers::viewOneFlower(index-1, Flowers);
    cout << "Вы точно хотите удалить данный цветок ? (1/0) : ";
    int choice;
    cin >> choice;
    choice = check(0, 1, choice);
    if (choice == 1) {
        cout << "Цветок " << Flowers[index-1].GetName() << " был удалён" << endl;
        Flowers.erase(Flowers.begin() + index-1);
    }
    else {
        cout <<"Вы отменили своё решение" << endl;
    }

}
void WorkWithFlowers::editFlower() {
    AllFlowers(Flowers);
    cout << "Введите номер цветка, который вы хотите отредактировать : " << endl;
    int number;
    cin >> number;
    try {
        Flowers.at(number-1);
    }
    catch (out_of_range &e) {
        cout << "Вы ввели неверный номер цветка" << endl;
        cin.clear(); cin.ignore(256, '\n');
        return;
    }
    viewTop();
    WorkWithFlowers::viewOneFlower(number - 1,Flowers);
    cout << "Что хотите изменить в данном цветке ?" << endl;
    cout << "1. Название" << endl;
    cout << "2. Количество на складе" << endl;
    cout << "3. Цена за один цветок" << endl;
    cout << "4. Отменить редактирование" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 4, choice);
    string NewName;
    int NewAmount, NewCoast;
    switch (choice) {
    case 1:
        cout << "Введите новое название цветка : ";
        cin >> NewName;
        if (NewName == Flowers[number - 1].GetName()) cout << "Вы ввели такое же название цветка" << endl;
        else {
            cout << "Вы изменили имя цветка " << number << " с " << Flowers[number - 1].GetName() << " на " << NewName << endl;
            Flowers[number - 1].setName(NewName);
        }
        break;
    case 2:
        cout << "Введите новое количество цветков : ";
        cin >> NewAmount;
        NewAmount = check(1, 10000, NewAmount);
        if (NewAmount == Flowers[number - 1].GetAmount()) cout << "Вы ввели такое же количество цветов" << endl;
        else {
            cout << "Вы изменили количсевто  цветов " << number << " с " << Flowers[number - 1].GetAmount() << " на " << NewAmount << endl;
            Flowers[number - 1].setAmount(NewAmount);
        }
        break;
    case 3:
        cout << "Введите новую цену цветка : ";
        cin >> NewCoast;
        NewCoast = check(1, 10000, NewCoast);
        if (NewCoast == Flowers[number - 1].GetCoast()) cout << "Вы ввели такую же цену" << endl;
        else {
            cout << "Вы изменили цену цветка " << number << " с " << Flowers[number - 1].GetCoast() << " на " << NewCoast << endl;
            Flowers[number - 1].setCoast(NewCoast);
        }
        break;
    case 4:return;
    }
}

bool CompareByName(  Flower& obj1,   Flower& obj2)
{
    return obj1.GetName() < obj2.GetName();
}

bool CompareByAmount(  Flower& obj1,   Flower& obj2)
{
    return obj1.GetAmount() > obj2.GetAmount();
}

bool CompareByCoast(  Flower& obj1,   Flower& obj2)
{
    return obj1.GetCoast() < obj2.GetCoast();
}



void WorkWithFlowers::sortFlower(vector<Flower> &VectorFlowers) {

    cout << "По какой характеристеке вы хотите отсортировать цветы ? " << endl;
    cout << "1. По названию" << endl;
    cout << "2. По количеству на складе" << endl;
    cout << "3. По цене" << endl;
    cout << "4. Отмена сортировки" << endl;
    int choice;
    cin >> choice;
    choice = check_on_letters(choice);
    switch (choice) {
    case 1:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByName);
        cout << "Все цветы были отсортированы по названию" << endl;
        break;
    case 2:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByAmount);
        cout << "Все цветы были отсортированы по количеству" << endl;
        break;
    case 3:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByCoast);
        cout << "Все цветы были отсортированы по цене" << endl;
        break;
    case 4: system("cls"); return;
    default:
        cout << "Вы неправильно ввели номер операции" << endl;
        system("pause"); system("cls");
    }
    if (choice == 1 || choice == 2 || choice == 3) {
        AllFlowers(VectorFlowers);
        system("pause"); system("cls");
    }
   


}


void WorkWithFlowers::searchFlowers()
{
        cout << "По какому параметру вы хотите найти цветок ?" << endl;
        cout << "1. Название" << endl;
        cout << "2. Цена (Диапазон)" << endl;
        cout << "3. Количество нв складе (выводит цветы с количесвтом на складе больше чем введённое)" << endl;
        cout << "4. В Меню" << endl;
        int choice;
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                throw runtime_error("Неверный номер операции");
            }
        } 
        catch (runtime_error& e) {
            cout << e.what() << endl;
            system("pause"); system("cls");
            return;
        }
       
        bool result = false;
        int MinCoast, MaxCoast, amount;
        string Name;
        switch (choice)
        {
        case 1:
        {
            int count1 = 0;
            bool result1 = false;
            cout << "Введите название цветка, который вы хотите найти : ";
            cin >> Name;
            for (int i = 0; i < Flowers.size(); i++)
            {
                if (Flowers[i].GetName().find(Name) != string::npos)
                {
                    result1 = true;
                    count1++;
                    if (count1 == 1)viewTop();
                    viewOneFlower(i,Flowers);
                }
            }
            if (!result1) cout << "Нет цветка с таким названием" << endl;
        }    break;
        case 2:
        {
            int count2 = 0;
            bool result2 = false;
            cout << "Введите диапазон цен для цветка " << endl;
            cout << "Минимальная цена : ";
            cin >> MinCoast;
            MinCoast = check_on_letters(MinCoast);
            cout << "Максимальная цена : ";
            cin >> MaxCoast;
            MaxCoast = check_on_letters(MaxCoast);

            for (int i = 0; i < Flowers.size(); i++)
            {
                if (Flowers[i].GetCoast() >= MinCoast && Flowers[i].GetCoast() <= MaxCoast)
                {
                    result2 = true;
                    count2++;
                    if (count2 == 1) viewTop();
                    viewOneFlower(i,Flowers);
                }
            }
            if (!result2) cout << "Нет цветка с таким диапазонои цен" << endl;
        }break;
        case 3:
        {
            int count3 = 0;
            bool result3 = false;
            cout << "Введите количество цветов на складе : ";
            cin >> amount;

            amount = check_on_letters(amount);
            for (int i = 0; i < Flowers.size(); i++)
            {
                if (Flowers[i].GetAmount() >= amount)
                {
                    result3 = true;
                    count3++;
                    if (count3 == 1) viewTop();
                    viewOneFlower(i,Flowers);
                }
            }
            if (!result) cout << "Нет цветов с таким количеством на складе" << endl;
        }   break;
        case 4:system("cls"); return;
        default: cout << "Вы ввели неверный номер операции" << endl;
        } 
        system("pause"); system("cls");
    }

void WorkWithFlowers::AllFlowers(vector<Flower> VectorFlowers) {
    viewTop();
    for (int i = 0;i< VectorFlowers.size();i++) {
        WorkWithFlowers::viewOneFlower(i, VectorFlowers);
    }

}
void WorkWithFlowers::viewOneFlower(int i, vector<Flower> VectorFlowers) {
    cout << "|  " << setw(3) << i + 1 << "  |   " << setw(21) << VectorFlowers[i].GetName() << "  |         " << setw(5) << VectorFlowers[i].GetAmount() << "        |       "
        << setw(5) << VectorFlowers[i].GetCoast() << "   |" << endl;
    cout << "|_______|__________________________|______________________|_______________|" << endl;
}