#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <memory> 
#include <vector>
#include <list>
#include <array>
#include <deque>
#include <set>
#include <thread> 
#include <chrono> 
#include <algorithm>
#include <numeric>
#include <mutex>
using namespace std;
//---------------------������� � ���������---------------------------------------

struct Sdata
{
	string name;
	string surname;
    string post;
	int id = 0;
	short pay_h = 0;
	short hours = 0;
	long salary = 0;
	

};

void NEW(int& size, Sdata*& basa_data);    // ����� ��������
void SAVE(int size, Sdata* basa_data);     // ��������� ������ � ����
void LOAD(int& size, Sdata*& basa_data);   // ��������� ������ �� �����
void SHOW(int size,Sdata* basa_data);      // �������� ������ �� ������
void RENEW(int size,Sdata*& basa_data);    // �������� ������ ������ �� ���������� (��������)
void DELETE(int& size, Sdata*& basa_data); // ������� ������
void SEARCH(int size,Sdata* basa_data);    // ����� ������ �� ��������
void SORT(int size,Sdata*& basa_data);     // ���������� ������


//------------------------MAIN----------------------------------------------------
int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	//-------------------------------���� �����-------------------------------------

	int size = 0;                             // size - ����� ����� � ���� ������
	                                          // Sdata - ��������� ��� �������� �������� ( ������ )
	Sdata* basa_data = new Sdata[size];       // base_data[i] - ���������� �������

	char choice = 'A';                              // choice - ����� �� ������� ����

//------- MENU--------------
	
	while (choice != 'V')
	{

	cout << "\n�������� ��������: \n";
	cout << "N ����� ��������.\n";
	cout << "S ��������� � ����.\n";
	cout << "Z ��������� �� �����.\n";
	cout << "H �������� ������ �� ������.\n";
	cout << "D �������� ������.\n";
	cout << "U �������� ������.\n";
	cout << "P ����� ������ (�� ��������).\n";
	cout << "R ���������� ������.\n";
	cout << "V �����.\n\n";
	cout << "�����:    ";
	cin >> choice;

	if (choice > 94)                              // ���������������������
	{
		choice -= 32;
	}

	//-------����-����------------


		switch (choice)
		{

		case 'N':
			NEW(size, basa_data);
			break;
//-------------------------------------
		case 'S':
            SAVE(size,basa_data);
			break;
//-------------------------------------
		case 'Z':
			LOAD(size, basa_data);
			break;
//-------------------------------------
		case 'H':
			SHOW(size, basa_data);
			break;
//-------------------------------------
		case 'D':
			RENEW(size, basa_data);
			break;
//-------------------------------------
		case 'U':
			DELETE(size, basa_data);
			break;
//-------------------------------------
		case 'P':
			SEARCH(size, basa_data);
			break;
//-------------------------------------
		case 'R':
			SORT(size, basa_data);
			break;
//--------------------------------------------------------------------
		case 'V':
			cout << "\n ����� �� ���������!\n";
            break;

//--------------------------------------------------------------------
		default:
			cout << "!! ������ !! ������ ������ ���� ����! \n";

			break;
		}

	}
	

	//delete[] basa_data;

	system("pause");

	return 0;
}

//------------------------------------FUNCTION-------------------------------


void NEW(int& size, Sdata*& basa_data)                 // N - ����� �������
{
	Sdata* reserve_data = new Sdata[size + 1];
	for (int i = 0; i < size; i++)
	{
		reserve_data[i] = basa_data[i];
	}

	cout << "\n������� ������ ��������:\n\n";

	reserve_data[size].id = size;
	cout << "ID:  " << reserve_data[size].id << endl;
	
	cout << "������� ���:  ";
	cin >> reserve_data[size].name;

	cout << "������� �������:  ";
	cin >> reserve_data[size].surname;

	cout << "������� ���������:  ";
	cin >> reserve_data[size].post;

	cout << "������� �������� �� ���:  ";
	cin >> reserve_data[size].pay_h;

	cout << "������� ����������� �����:  ";
	cin >> reserve_data[size].hours;

	reserve_data[size].salary = reserve_data[size].pay_h * reserve_data[size].hours;

	size++;

	//delete[] basa_data;                                   // �������� ���!!!!
	                                             // �������� ��������� , �� ���� ��������� �� ����� 
	                                             // ��������� ������� ���� ( �������� ����� )
	
    basa_data = reserve_data;

}

//------------------------------------------------------------------------

void SAVE(int size, Sdata* basa_data)                      // S - ���������� � ����
{
	string path;

	cout << "\n������� �������� ����� ��� ����������:  ";
	cin >> path;

	ofstream fout;

	fout.open(path, ofstream::app);

	if (!fout.is_open())
	{
		cout << "\n������ �������� �����!!\n";
	}
	else
	{
		cout << "\n���� ������ ������� ��� ������ ������!!\n";
		
		fout << size;                               // ����� ������ ������� ����� �����
		for (int i = 0; i < size; i++)
		{
			fout.write((char*)&basa_data[i], sizeof(Sdata));  // ����� ���������� ��� ������
			//fout << "\n";                                     // � ����� ������ ������ ������� , ��� �����������
		}
	}

	fout.close();
}

//------------------------------------------------------------------------

void LOAD(int& size, Sdata*& basa_data)                      // Z - �������� ������ �� �����
{
	string path;

	cout << "\n������� �������� ����� ��� ��������:  ";
	cin >> path;

	ifstream fin;

	fin.open(path);

	if (!fin.is_open())
	{
		cout << "\n������ �������� �����!!\n";
	}
	else
	{
		cout << "\n���� ������ ������� ��� ������ ������!!\n";

		fin >> size;

		Sdata* Rbasa_data = new Sdata[size];

		
		for (int i = 0; i < size; i++)
		{
			fin.read((char*)&Rbasa_data[i], sizeof(Sdata));
		}
		
	//	delete[] basa_data;
		basa_data = Rbasa_data;
	}

	fin.close();
}

//------------------------------------------------------------------------

void SHOW(int size,Sdata* basa_data)          // H - �������� �� �������
{
	cout << "ID\t" << "���\t" << "�������\t" << "���������\t" << "��/���\t" << "����\t" << "��������\n";
	cout << "------------------------------------------------------------------------------------\n\n";
	for (int i = 0; i < size; i++)
	{
		cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
			<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
			<< basa_data[i].salary << "\n";
	}

	cout << "\n SIZE:  " << size << endl;
}

//----------------------------------------------------------------------------

void RENEW(int size, Sdata*& basa_data)                // D - �������� ������
{

	int idr;
	SHOW(size, basa_data);

	cout << "\n�������� ID �������� , ��� ���������� �� �� ������ ��������: ";
	cin >> idr;

	cout << "\n������� ������ ��������:\n\n";

	cout << "ID:  " << basa_data[idr].id << endl;

	cout << "������� ���:  ";
	cin >> basa_data[idr].name;

	cout << "������� �������:  ";
	cin >> basa_data[idr].surname;

	cout << "������� ���������:  ";
	cin >> basa_data[idr].post;

	cout << "������� �������� �� ���:  ";
	cin >> basa_data[idr].pay_h;

	cout << "������� ����������� �����:  ";
	cin >> basa_data[idr].hours;

	basa_data[idr].salary = basa_data[idr].pay_h * basa_data[idr].hours;

}

//-----------------------------------------------------------------------------------

void DELETE(int& size,Sdata*& basa_data)               // U - �������� ������
{
	SHOW(size, basa_data);



	int idd;
	cout << "\n�������� ID �������� , ��� ������ �� �� ������ �������: ";
	cin >> idd;

	Sdata* reserve_data = new Sdata[size - 1];
	for (int i = 0; i < idd; i++)
	{
			reserve_data[i] = basa_data[i];
	}

	for (int i = idd; i < size - 1; i++)
	{
		reserve_data[i] = basa_data[i + 1];
		reserve_data[i].id = i;
	}

	size--;
	delete[] basa_data;
	basa_data = reserve_data;
}

//-------------------------------------------------------------------------------------

void SEARCH(int size, Sdata* basa_data)            // P - �����
{
	cout << "\n�������� ������� , �� �������� ����� ���� �����:\n";
	cout << "1. ���\n2. �������\n3. ���������\n4. ������ �� ���\n5. ����� �����\n6. ��������\n";
	int ch;
	cin >> ch;

	string strx;
	cout << "\n������� ������ ��� ������: ";
	cin >> strx;
	cout << endl;

				cout << "ID\t" << "���\t" << "�������\t" << "���������\t" << "��/���\t" << "����\t" << "��������\n";
				cout << "------------------------------------------------------------------------------------\n\n";
	switch (ch)
	{
	case 1:
	{
		for (int i = 0; i < size; i++)
		{
			if (basa_data[i].name == strx)
			{
					cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
						<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
						<< basa_data[i].salary << "\n";
				
			}
		}
	}
		break;
	case 2:
	{
		for (int i = 0; i < size; i++)
		{
			if (basa_data[i].surname == strx)
			{
				cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
					<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
					<< basa_data[i].salary << "\n";

			}
		}
	}
		break;
	case 3:
	{
		for (int i = 0; i < size; i++)
		{
			if (basa_data[i].post == strx)
			{
				cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
					<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
					<< basa_data[i].salary << "\n";

			}
		}
	}
		break;
	case 4:
	{
		for (int i = 0; i < size; i++)
		{
			if (to_string(basa_data[i].pay_h) == strx)
			{
				cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
					<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
					<< basa_data[i].salary << "\n";

			}
		}
	}
		break;
	case 5:
	{
		for (int i = 0; i < size; i++)
		{
			if (to_string(basa_data[i].hours) == strx)
			{
				cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
					<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
					<< basa_data[i].salary << "\n";

			}
		}
	}
		break;
	case 6:
	{
		for (int i = 0; i < size; i++)
		{
			if (to_string(basa_data[i].salary) == strx)
			{
				cout << basa_data[i].id << "\t" << basa_data[i].name << "\t" << basa_data[i].surname << "\t"
					<< basa_data[i].post << "\t\t" << basa_data[i].pay_h << "\t" << basa_data[i].hours << "\t"
					<< basa_data[i].salary << "\n";

			}
		}
	}
		break;
	default:
		cout << "\n������ ������! ����� � ������� ����...\n";
		break;
	}
}

//-----------------------------------------------------------------------------------------------

void SORT(int size, Sdata*& basa_data)
{
	cout << "\n�������� ������� , �� �������� ����� ���� ����������:\n";
	cout << "1. ���\n2. �������\n3. ���������\n4. ������ �� ���\n5. ����� �����\n6. ��������\n";
	int ch;
	cin >> ch;
	cout << endl;

	//cout << "ID\t" << "���\t" << "�������\t" << "���������\t" << "��/���\t" << "����\t" << "��������\n";
	//	cout << "------------------------------------------------------------------------------------\n\n";

	switch (ch)
	{
	case 1:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].name > basa_data[j + 1].name)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
		break;
	case 2:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].surname > basa_data[j + 1].surname)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
		break;
	case 3:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].post > basa_data[j + 1].post)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
		break;
	case 4:
	{
		for (int i = 0; i < size; i++)
		{
			for(int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].pay_h > basa_data[j + 1].pay_h)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
        break;
	case 5:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].hours > basa_data[j + 1].hours)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
		break;
	case 6:
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (basa_data[j].salary > basa_data[j + 1].salary)
				{
					Sdata* temp_data = new Sdata[1];

					temp_data[0] = basa_data[j];

					basa_data[j] = basa_data[j + 1];

					basa_data[j + 1] = temp_data[0];

					delete[] temp_data;
				}
			}
		}
		for (int i = 0; i < size; i++)                        // ����� ����
		{
			basa_data[i].id = i;
		}

	}
		break;
	default:
		cout << "\n������ ������ ���������!! ����� � ������� ����...\n";
		break;
	}


}