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
//---------------------Функции и Прототипы---------------------------------------

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

void NEW(int& size, Sdata*& basa_data);    // новый работник
void SAVE(int size, Sdata* basa_data);     // сохранить данные в файл
void LOAD(int& size, Sdata*& basa_data);   // загрузить данные из файла
void SHOW(int size,Sdata* basa_data);      // показать данные на экране
void RENEW(int size,Sdata*& basa_data);    // дописать данные одного из работников (обновить)
void DELETE(int& size, Sdata*& basa_data); // удалить данные
void SEARCH(int size,Sdata* basa_data);    // поиск данных по атрибуту
void SORT(int size,Sdata*& basa_data);     // сортировка данных


//------------------------MAIN----------------------------------------------------
int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));
	//-------------------------------САМА ПРОГА-------------------------------------

	int size = 0;                             // size - число людей в базе данных
	                                          // Sdata - структура для описания человека ( любого )
	Sdata* basa_data = new Sdata[size];       // base_data[i] - конкретный человек

	char choice = 'A';                              // choice - выбор по пунктам меню

//------- MENU--------------
	
	while (choice != 'V')
	{

	cout << "\nВыберите действие: \n";
	cout << "N Новый работник.\n";
	cout << "S сохранить в файл.\n";
	cout << "Z загрузить из файла.\n";
	cout << "H показать данные на экране.\n";
	cout << "D Дописать данные.\n";
	cout << "U Удаление данных.\n";
	cout << "P Поиск данных (по атрибуту).\n";
	cout << "R Сортировка данных.\n";
	cout << "V Выход.\n\n";
	cout << "Выбор:    ";
	cin >> choice;

	if (choice > 94)                              // регистронезависимость
	{
		choice -= 32;
	}

	//-------СВИЧ-БЛОК------------


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
			cout << "\n ВЫХОД ИЗ ПРОГРАММЫ!\n";
            break;

//--------------------------------------------------------------------
		default:
			cout << "!! ОШИБКА !! Такого пункта меню нету! \n";

			break;
		}

	}
	

	//delete[] basa_data;

	system("pause");

	return 0;
}

//------------------------------------FUNCTION-------------------------------


void NEW(int& size, Sdata*& basa_data)                 // N - Новый человек
{
	Sdata* reserve_data = new Sdata[size + 1];
	for (int i = 0; i < size; i++)
	{
		reserve_data[i] = basa_data[i];
	}

	cout << "\nВведите данные человека:\n\n";

	reserve_data[size].id = size;
	cout << "ID:  " << reserve_data[size].id << endl;
	
	cout << "Введите имя:  ";
	cin >> reserve_data[size].name;

	cout << "Введите фамилию:  ";
	cin >> reserve_data[size].surname;

	cout << "Введите должность:  ";
	cin >> reserve_data[size].post;

	cout << "Введите зарплату за час:  ";
	cin >> reserve_data[size].pay_h;

	cout << "Введите колличество часов:  ";
	cin >> reserve_data[size].hours;

	reserve_data[size].salary = reserve_data[size].pay_h * reserve_data[size].hours;

	size++;

	//delete[] basa_data;                                   // ПРОБЛЕМА ТУТ!!!!
	                                             // работает нормально , но если загрузить из файла 
	                                             // перестает ОЧИЩАТЬ БАЗУ ( выбивает прогу )
	
    basa_data = reserve_data;

}

//------------------------------------------------------------------------

void SAVE(int size, Sdata* basa_data)                      // S - Сохранение в файл
{
	string path;

	cout << "\nВведите название файла для сохранения:  ";
	cin >> path;

	ofstream fout;

	fout.open(path, ofstream::app);

	if (!fout.is_open())
	{
		cout << "\nОшибка открытия файла!!\n";
	}
	else
	{
		cout << "\nФайл открыт успешно для ЗАПИСИ данных!!\n";
		
		fout << size;                               // пишем первой строкой число строк
		for (int i = 0; i < size; i++)
		{
			fout.write((char*)&basa_data[i], sizeof(Sdata));  // потом записываем все строки
			//fout << "\n";                                     // в конце каждой строки перенос , как разделитель
		}
	}

	fout.close();
}

//------------------------------------------------------------------------

void LOAD(int& size, Sdata*& basa_data)                      // Z - Загрузка данных из файла
{
	string path;

	cout << "\nВведите название файла для загрузки:  ";
	cin >> path;

	ifstream fin;

	fin.open(path);

	if (!fin.is_open())
	{
		cout << "\nОшибка открытия файла!!\n";
	}
	else
	{
		cout << "\nФайл открыт успешно для ЧТЕНИЯ данных!!\n";

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

void SHOW(int size,Sdata* basa_data)          // H - Показать на консоли
{
	cout << "ID\t" << "Имя\t" << "Фамилия\t" << "Должность\t" << "Зп/час\t" << "Часы\t" << "Зарплата\n";
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

void RENEW(int size, Sdata*& basa_data)                // D - дописать данные
{

	int idr;
	SHOW(size, basa_data);

	cout << "\nВыберите ID рабочего , чью информацию Вы бы хотели дописать: ";
	cin >> idr;

	cout << "\nВведите данные человека:\n\n";

	cout << "ID:  " << basa_data[idr].id << endl;

	cout << "Введите имя:  ";
	cin >> basa_data[idr].name;

	cout << "Введите фамилию:  ";
	cin >> basa_data[idr].surname;

	cout << "Введите должность:  ";
	cin >> basa_data[idr].post;

	cout << "Введите зарплату за час:  ";
	cin >> basa_data[idr].pay_h;

	cout << "Введите колличество часов:  ";
	cin >> basa_data[idr].hours;

	basa_data[idr].salary = basa_data[idr].pay_h * basa_data[idr].hours;

}

//-----------------------------------------------------------------------------------

void DELETE(int& size,Sdata*& basa_data)               // U - Удаление данных
{
	SHOW(size, basa_data);



	int idd;
	cout << "\nВыберите ID рабочего , чьи данные вы бы хотели удалить: ";
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

void SEARCH(int size, Sdata* basa_data)            // P - поиск
{
	cout << "\nВыберете атрибут , по которому будет идти поиск:\n";
	cout << "1. Имя\n2. Фамилия\n3. Должность\n4. оплата за час\n5. Число часов\n6. Зарплата\n";
	int ch;
	cin >> ch;

	string strx;
	cout << "\nВведите данные для поиска: ";
	cin >> strx;
	cout << endl;

				cout << "ID\t" << "Имя\t" << "Фамилия\t" << "Должность\t" << "Зп/час\t" << "Часы\t" << "Зарплата\n";
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
		cout << "\nОШИБКА поиска! выход в главное меню...\n";
		break;
	}
}

//-----------------------------------------------------------------------------------------------

void SORT(int size, Sdata*& basa_data)
{
	cout << "\nВыберете атрибут , по которому будет идти сортировка:\n";
	cout << "1. Имя\n2. Фамилия\n3. Должность\n4. оплата за час\n5. Число часов\n6. Зарплата\n";
	int ch;
	cin >> ch;
	cout << endl;

	//cout << "ID\t" << "Имя\t" << "Фамилия\t" << "Должность\t" << "Зп/час\t" << "Часы\t" << "Зарплата\n";
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
		for (int i = 0; i < size; i++)                        // смена айди
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
		for (int i = 0; i < size; i++)                        // смена айди
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
		for (int i = 0; i < size; i++)                        // смена айди
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
		for (int i = 0; i < size; i++)                        // смена айди
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
		for (int i = 0; i < size; i++)                        // смена айди
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
		for (int i = 0; i < size; i++)                        // смена айди
		{
			basa_data[i].id = i;
		}

	}
		break;
	default:
		cout << "\nОШИБКА выбора параметра!! Выход в главное меню...\n";
		break;
	}


}