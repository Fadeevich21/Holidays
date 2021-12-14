#include <iostream>		
#include <Windows.h>	/* SetConsoleCP(); SetConsoleOutputCP() */
#include <string>
#include <fstream>

using namespace std;

typedef struct
{
	unsigned month;
	unsigned day;
} t_data;				/* СД для хранения даты */

typedef struct
{
	t_data data;
	string name;
} t_holiday;			/* СД для хранения праздника */

void SolveTask(const string &fName);

int main()
{
	SetConsoleCP(1251);					/* Установка кодировки вывода на консоль */
	SetConsoleOutputCP(1251);			/* Установка кодировки ввода из консоли и из редактора кода */

	cout << "Начало работы программы!" << endl << endl;

	string fName = "file.txt";
	SolveTask(fName);

	cout << endl << "Конец работы программы!" << endl;

	return 0;
}

// Возвращает прадник, считанный из текстового файла fin 
t_holiday GetHoliday(ifstream &fin)
{
	t_holiday holiday;
	string str;
	getline(fin, str);

	holiday.data.day = (str[0] - '0') * 10 + (str[1] - '0');
	holiday.data.month = (str[3] - '0') * 10 + (str[4] - '0');
	holiday.name = str.substr(6, str.size() - 6);

	return holiday;
}

// Возвращает "истина", если даты data1 и data2 эквивалентны, иначе - "ложь"
#define CheckEquality2Data(data1, data2) (data1.month == data2.month) && (data1.day == data2.day)

// Возвращает "истина", если дата data была введена корректно, иначе - "ложь"
bool CheckCorrectReadData(const t_data &data)
{
	static int day[] = {31, 29, 31,
						30, 31, 30,
						31, 31, 30,
						31, 30, 31};

	return (data.month >= 1) && (data.month <= 12) && (data.day >= 0) && (data.day <= day[data.month - 1]);
}

// Вывод праздников из файла с именем fName в дни, которые вводит пользователь
void SolveTask(const string &fName)
{
	ifstream fin(fName);
	if (!fin.is_open())
	{
		cout << "Файл с именем \"" << fName << "\" не был открыт!" << endl;
		fin.close();
		return;
	}

	while (true)
	{
		// Выбор команды
		int select;
		cout << "Выберите команду:" << endl;
		cout << "1 - Ввести дату" << endl;
		cout << "2 - Выход" << endl;

		cin >> select;
		
		// Не существует данной команды
		while (select < 1 || select > 2)
		{
			cout << "Вы выбрали неверную команду. Пожалуйста, выберите команду:" << endl;
			cin >> select;
		}

		// Команда выхода из программы
		if (select == 2)
			break;

		char ch;			/* Для считывания точки из потока ввода, которая является разделителем дня и месяца */
		t_data data;
		cout << endl << "Введите дату праздника: " << endl;
		cin >> data.day >> ch >> data.month;

		// Дата введена не корректно
		while (!CheckCorrectReadData(data))
		{
			cout << "Вы ввели неправильную дату. Пожалуйста, введите другую дату:" << endl;
			cin >> data.day >> ch >> data.month;
		}

		cout << endl << "###################################################" << endl;
		cout << "Праздники в данный день:" << endl << endl;

		// Обработка текстового файла fin
		unsigned cntHolidayThisData = 0;
		t_holiday holiday;
		while (!fin.eof())
		{
			holiday = GetHoliday(fin);
			if (CheckEquality2Data(data, holiday.data))
			{
				cntHolidayThisData++;
				cout << cntHolidayThisData << ") " << holiday.name << ";" << endl;
			}
		}

		if (cntHolidayThisData == 0)
			cout << "Праздников в данный день нет" << endl;

		cout << "###################################################" << endl << endl;

		// Перемещение указателя считывания из тексового файла fin в его начало
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

	fin.close();
}