#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

bool search_number_file(string path, long digit, bool showtime)//функция линейного поиска в файле
{
	long C = 0, pos = -1;
	ifstream f(path);
	auto start_time = chrono::high_resolution_clock::now();
	while (!f.eof())
	{
		string str;
		getline(f, str);
		for (auto ch : str)
		{
			if (isdigit(ch))
			{
				C++;
				pos++;
				if (digit == atoi(&ch))
				{
					cout<< "\nПоиск в файле. Позиция цифры \"" << digit << "\": " << pos << "; Количество сравнений : " << C;
					if (showtime) {
						auto stop_time = chrono::high_resolution_clock::now();
						chrono::duration<double, nano> dur = stop_time - start_time;
						auto T = dur.count();
						cout << "; Время поиска : " << T/1000000000 << " сек.\n";
					}
					return true;
				}
			}
		}
	}
	cout << "\nПоиск в файле. Число " << digit <<  " не найдено! ";
	if (showtime) {
		auto stop_time = chrono::high_resolution_clock::now();
		chrono::duration<double, nano> dur = stop_time - start_time;
		 auto T = dur.count();
		cout << "Время поиска : " << T/1000000000 << " сек.\n";
	}
	return false;
}

bool search_number_arr(int e, int* arr, long digit, bool showtime)//функция линейного поиска в массиве
{
	long C = 0;
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < e; i++)
	{
		C++;
		if (arr[i] == digit)
		{
			cout << "\nПоиск в массиве. Позиция цифры \"" << digit << "\": " << i << "; Количество сравнений : " << C;
			if (showtime) {
				auto stop_time = chrono::high_resolution_clock::now();
				chrono::duration<double, nano> dur = stop_time - start_time;
				auto T = dur.count();
				cout << "; Время поиска : " << T / 1000000000 << " сек.\n";
			}
			return true;

		}
	}
	cout << "\nПоиск в массиве. Число " << digit << " не найдено! ";
	if (showtime) {
		auto stop_time = chrono::high_resolution_clock::now();
		chrono::duration<double, nano> dur = stop_time - start_time;
		auto T = dur.count();
		cout << "Время поиска : " << T / 1000000000 << " сек.\n";
	}
	return false;
}

void create_file(string path, int e, bool showtime, long long int position) {//заполнение файла значениями
	ofstream f(path);
	for (int i = 0; i < e; i++) {
		if (i != position) {
			f << 1;
		}
		else {
			f << 2;
		}
	}
	f.close();
	search_number_file(path, 2, showtime);
	search_number_file(path, -5, showtime);
}

void create_arr(int e, bool showtime, long long int position) {//заполнение массива значениями
	int* arr = new int[e];
	for (int i = 0; i < e; i++) {
		if (i != position) {
			arr[i] = 1;
		}
		else {
			arr[i] = 2;
		}
	}
	search_number_arr(e, arr, 2, showtime);
	search_number_arr(e, arr, -5, showtime);
}

int main()
{
	setlocale(LC_ALL, "ru");
	int question;
	srand(time(0));
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "|Мещеряков Андрей ИКБО-15-19                                                                             |" << endl;
	cout << "|Практическая работа №4 алгоритм линейного поиска                                                        |" << endl;
	cout << "+--------------------------------------------------------------------------------------------------------+" << endl;
	cout << "Тестовый прогон (1)/Контрольный прогон (2): ";
	cin >> question;
	if (question == 1) {
		int testArr[10];
		ofstream testFile("test_file.txt");
		cout << "введите массив:";
		for (int i = 0; i < 10; i++)
		{
			cout << "[" << i << "]= ";
			cin >> testArr[i];
			testFile << testArr[i];
		}
		testFile.close();
		search_number_file("test_file.txt", testArr[5], false);
		search_number_file("test_file.txt", -1, false);
		search_number_arr(10, testArr, testArr[5], false);
		search_number_arr(10, testArr, -1, false);
	}
	else if (question == 2) {
		long long int e;
		for (e = 8000000; e <= 10000000; e += 1000000) {
			auto random = rand() * rand();
			long long int position = random % (e - 4) + 4;
			cout << "----------------------------------------------------------------------------------------------------------\n";
			cout << "n = " << e << endl;
			create_file("cintrol_file.txt", e, true, position);
			create_arr(e, true, position);
		}
	}
}
