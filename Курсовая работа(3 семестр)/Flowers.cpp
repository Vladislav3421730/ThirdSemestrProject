
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
    cout << "|   �   |      �������� ������     | ���������� �� ������ | ���� �� ����� |" << endl;
    cout << "|_______|__________________________|______________________|_______________|" << endl;
}

void MenuForManagerForOrders() {
    int choice = 0;
    while (choice != 6) {

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
        cout << setw(62) << "|"; get_yellow cout << "                                     ���� ��� ������ � ��������                        "; get_green cout << "| " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        cout << setw(62) << "|"; get_blue cout << "                                1. ������� ��� ������"; get_green cout << "                                  | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                2. ���������� ������� "; get_green cout << "                                 | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                3. �������������� �������"; get_green cout << "                              | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                4. �������� �������"; get_green cout << "                                    | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                5. ����� �������"; get_green cout << "                                       | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                6. ����� � ���� "; get_green cout << "                                       | " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        get_yellow cout << setw(110) << "                                   ��� ����� ";
        get_red
            try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                no_color
                    throw runtime_error("����������� ���� ����� ��������");
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
        default: cout << "������� ����� ����� ��������" << endl; system("pause"); system("cls");
        }
    }
}

void menu_for_manager() {
    int choice = 0;
	while (choice!=7) {

        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        get_green cout << setw(150) << "_________________________________________________________________________________________" << endl;
        cout << setw(62) << "|"; get_yellow cout << "                                     ���� ��� ���������                                "; get_green cout << "| " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        cout << setw(62) << "|"; get_blue cout << "                                1. �������� ����� ������ (��� �������)"; get_green cout << "                 | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                2. ������� ��������� ����� "; get_green cout << "                            | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                3. ��������������"; get_green cout << "                                      | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                4. ��������"; get_green cout << "                                            | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                5. ����������� "; get_green cout << "                                        | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                6. ����� "; get_green cout << "                                              | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                7. ������ � �������� "; get_green cout << "                                  | " << endl;
        cout << setw(62) << "|"; get_blue cout << "                                8. ����� �� ������� ���� "; get_green cout << "                              | " << endl;
        cout << setw(150) << "|_______________________________________________________________________________________|" << endl;
        get_yellow cout << setw(110) << "                                   ��� ����� ";
        get_red
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                no_color
                throw runtime_error("����������� ���� ����� ��������");
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
        default: cout << "������� ����� ����� ��������" << endl; system("pause"); system("cls");
		}
	}
}
void  WorkWithFlowers::addFlower() {
    int n;
    cout << "������� ������ �� ������ �������� � �����������?" << endl;
    cin >> n;
    n = check_on_letters(n);
    int size = Flowers.size();
    for (int i = size; i < size + n; i++) {
        shared_ptr<Flower> flower_ptr = make_shared<Flower>();
        string name;
        int coast, amount;
        cout << "������� �������� ������ : ";
        cin >> name;
        flower_ptr->setName(name);
        cout << "������� ���������� ������ �� ������ : ";
        cin >> amount;
        amount = check_on_letters(amount);
        flower_ptr->setAmount(amount);
        cout << "������� ���� �� ���� ������ : ";
        cin >> coast;
        coast = check_on_letters(coast);
        flower_ptr->setCoast(coast);
        Flowers.push_back(*flower_ptr);
        cout << endl;
    }
}
void WorkWithFlowers::deleteFlower() {
    AllFlowers(Flowers);
    cout << "������� ����� ������, ������� �� ������ ������� : ";
    int index;
    cin >> index;
    try  {
        Flowers.at(index - 1);
    } catch (out_of_range &e) {
        cout << "�� ����� �������� ����� ������" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        return;
    }
    viewTop();
    WorkWithFlowers::viewOneFlower(index-1, Flowers);
    cout << "�� ����� ������ ������� ������ ������ ? (1/0) : ";
    int choice;
    cin >> choice;
    choice = check(0, 1, choice);
    if (choice == 1) {
        cout << "������ " << Flowers[index-1].GetName() << " ��� �����" << endl;
        Flowers.erase(Flowers.begin() + index-1);
    }
    else {
        cout <<"�� �������� ��� �������" << endl;
    }

}
void WorkWithFlowers::editFlower() {
    AllFlowers(Flowers);
    cout << "������� ����� ������, ������� �� ������ ��������������� : " << endl;
    int number;
    cin >> number;
    try {
        Flowers.at(number-1);
    }
    catch (out_of_range &e) {
        cout << "�� ����� �������� ����� ������" << endl;
        cin.clear(); cin.ignore(256, '\n');
        return;
    }
    viewTop();
    WorkWithFlowers::viewOneFlower(number - 1,Flowers);
    cout << "��� ������ �������� � ������ ������ ?" << endl;
    cout << "1. ��������" << endl;
    cout << "2. ���������� �� ������" << endl;
    cout << "3. ���� �� ���� ������" << endl;
    cout << "4. �������� ��������������" << endl;
    int choice;
    cin >> choice;
    choice = check(1, 4, choice);
    string NewName;
    int NewAmount, NewCoast;
    switch (choice) {
    case 1:
        cout << "������� ����� �������� ������ : ";
        cin >> NewName;
        if (NewName == Flowers[number - 1].GetName()) cout << "�� ����� ����� �� �������� ������" << endl;
        else {
            cout << "�� �������� ��� ������ " << number << " � " << Flowers[number - 1].GetName() << " �� " << NewName << endl;
            Flowers[number - 1].setName(NewName);
        }
        break;
    case 2:
        cout << "������� ����� ���������� ������� : ";
        cin >> NewAmount;
        NewAmount = check(1, 10000, NewAmount);
        if (NewAmount == Flowers[number - 1].GetAmount()) cout << "�� ����� ����� �� ���������� ������" << endl;
        else {
            cout << "�� �������� ����������  ������ " << number << " � " << Flowers[number - 1].GetAmount() << " �� " << NewAmount << endl;
            Flowers[number - 1].setAmount(NewAmount);
        }
        break;
    case 3:
        cout << "������� ����� ���� ������ : ";
        cin >> NewCoast;
        NewCoast = check(1, 10000, NewCoast);
        if (NewCoast == Flowers[number - 1].GetCoast()) cout << "�� ����� ����� �� ����" << endl;
        else {
            cout << "�� �������� ���� ������ " << number << " � " << Flowers[number - 1].GetCoast() << " �� " << NewCoast << endl;
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

    cout << "�� ����� �������������� �� ������ ������������� ����� ? " << endl;
    cout << "1. �� ��������" << endl;
    cout << "2. �� ���������� �� ������" << endl;
    cout << "3. �� ����" << endl;
    cout << "4. ������ ����������" << endl;
    int choice;
    cin >> choice;
    choice = check_on_letters(choice);
    switch (choice) {
    case 1:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByName);
        cout << "��� ����� ���� ������������� �� ��������" << endl;
        break;
    case 2:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByAmount);
        cout << "��� ����� ���� ������������� �� ����������" << endl;
        break;
    case 3:
        sort(VectorFlowers.begin(), VectorFlowers.end(), CompareByCoast);
        cout << "��� ����� ���� ������������� �� ����" << endl;
        break;
    case 4: system("cls"); return;
    default:
        cout << "�� ����������� ����� ����� ��������" << endl;
        system("pause"); system("cls");
    }
    if (choice == 1 || choice == 2 || choice == 3) {
        AllFlowers(VectorFlowers);
        system("pause"); system("cls");
    }
   


}


void WorkWithFlowers::searchFlowers()
{
        cout << "�� ������ ��������� �� ������ ����� ������ ?" << endl;
        cout << "1. ��������" << endl;
        cout << "2. ���� (��������)" << endl;
        cout << "3. ���������� �� ������ (������� ����� � ����������� �� ������ ������ ��� ��������)" << endl;
        cout << "4. � ����" << endl;
        int choice;
        try {
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(256, '\n');
                throw runtime_error("�������� ����� ��������");
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
            cout << "������� �������� ������, ������� �� ������ ����� : ";
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
            if (!result1) cout << "��� ������ � ����� ���������" << endl;
        }    break;
        case 2:
        {
            int count2 = 0;
            bool result2 = false;
            cout << "������� �������� ��� ��� ������ " << endl;
            cout << "����������� ���� : ";
            cin >> MinCoast;
            MinCoast = check_on_letters(MinCoast);
            cout << "������������ ���� : ";
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
            if (!result2) cout << "��� ������ � ����� ���������� ���" << endl;
        }break;
        case 3:
        {
            int count3 = 0;
            bool result3 = false;
            cout << "������� ���������� ������ �� ������ : ";
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
            if (!result) cout << "��� ������ � ����� ����������� �� ������" << endl;
        }   break;
        case 4:system("cls"); return;
        default: cout << "�� ����� �������� ����� ��������" << endl;
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