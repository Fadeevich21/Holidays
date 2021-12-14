#include <iostream>		
#include <Windows.h>	/* SetConsoleCP(); SetConsoleOutputCP() */
#include <string>
#include <fstream>

using namespace std;

typedef struct
{
	unsigned month;
	unsigned day;
} t_data;				/* �� ��� �������� ���� */

typedef struct
{
	t_data data;
	string name;
} t_holiday;			/* �� ��� �������� ��������� */

void SolveTask(const string &fName);

int main()
{
	SetConsoleCP(1251);					/* ��������� ��������� ������ �� ������� */
	SetConsoleOutputCP(1251);			/* ��������� ��������� ����� �� ������� � �� ��������� ���� */

	cout << "������ ������ ���������!" << endl << endl;

	string fName = "file.txt";
	SolveTask(fName);

	cout << endl << "����� ������ ���������!" << endl;

	return 0;
}

// ���������� �������, ��������� �� ���������� ����� fin 
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

// ���������� "������", ���� ���� data1 � data2 ������������, ����� - "����"
#define CheckEquality2Data(data1, data2) (data1.month == data2.month) && (data1.day == data2.day)

// ���������� "������", ���� ���� data ���� ������� ���������, ����� - "����"
bool CheckCorrectReadData(const t_data &data)
{
	static int day[] = {31, 29, 31,
						30, 31, 30,
						31, 31, 30,
						31, 30, 31};

	return data.month >= 1 && data.month <= 12 && data.day >= 0 && data.day <= day[data.month - 1];
}

// ����� ���������� �� ����� � ������ fName � ���, ������� ������ ������������
void SolveTask(const string &fName)
{
	ifstream fin(fName);
	if (!fin.is_open())
	{
		cout << "���� � ������ \"" << fName << "\" �� ��� ������!" << endl;
		fin.close();
		return;
	}

	while (true)
	{
		// ����� �������
		int select;
		cout << "�������� �������:" << endl;
		cout << "1 - ������ ����" << endl;
		cout << "2 - �����" << endl;

		cin >> select;
		
		// �� ���������� ������ �������
		while (select < 1 || select > 2)
		{
			cout << "�� ������� �������� �������. ����������, �������� �������:" << endl;
			cin >> select;
		}

		// ������� ������ �� ���������
		if (select == 2)
			break;

		char ch;			/* ��� ���������� ����� �� ������ �����, ������� �������� ������������ ��� � ������ */
		t_data data;
		cout << endl << "������� ���� ���������: " << endl;
		cin >> data.day >> ch >> data.month;

		// ���� ������� �� ���������
		while (!CheckCorrectReadData(data))
		{
			cout << "�� ����� ������������ ����. ����������, ������� ������ ����:" << endl;
			cin >> data.day >> ch >> data.month;
		}

		cout << endl << "###################################################" << endl;
		cout << "��������� � ������ ����:" << endl << endl;

		// ��������� ���������� ����� fin
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
			cout << "���������� � ������ ���� ���" << endl;

		cout << "###################################################" << endl << endl;

		// ����������� ��������� ���������� �� ��������� ����� fin � ��� ������
		fin.clear();
		fin.seekg(0, std::ios::beg);
	}

	fin.close();
}