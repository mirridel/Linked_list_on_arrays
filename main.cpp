#include "pch.h"

void printMainMenu(int n = 0);
void printIteratorMenu();
int iteratorMenu(LinkedList<int>& list, LinkedList<int>::iterator& it);
void test(LinkedList<int>& list, int n = 10);

int main()
{
    setlocale(LC_ALL, "ru");

	LinkedList<int> l;
	LinkedList<int>::iterator it = l.begin();

	std::string ch;
	while (true)
	{
		try {
			printMainMenu();
			std::getline(std::cin, ch);
			if (ch == "t") {
				test(l);
			}
			// Очистка консоли
			else if (ch == "0") {
				system("cls");
			}
			// Включение нового значения (т.е. вставка в конец списка)
			else if (ch == "1") {
				std::string val;
				cout << "Введите значение элемента" << endl;
				std::getline(cin, val);
				try
				{
					l.InsertToTail(std::stoi(val));
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Включение нового значения в позицию с заданным номером
			else if (ch == "2") {
				std::string n, val;
				cout << "Введите позицию нового элемента" << endl;
				std::getline(cin, n);
				cout << "Введите  значение нового элемента" << endl;
				std::getline(cin, val);
				try
				{
					l.InsertByIndex(std::stoi(n), std::stoi(val));
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Удалить элемент по значению
			else if (ch == "3") {
				// Удаление элемента из списка
				cout << "Введите значение элемента" << endl;;
				std::string n;
				std::getline(cin, n);
				try
				{
					l.DeleteElement(std::stoi(n));
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Удалить элемент по индексу
			else if (ch == "4") {
				cout << "Введите позицию элемента" << endl;
				std::string n;
				std::getline(cin, n);
				try
				{
					l.DeleteByIndex(std::stoi(n));
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Изменение значения с заданным номером в списке
			else if (ch == "5") {
				std::string n, val;
				cout << "Введите индекс элемента" << endl;
				std::getline(cin, n);
				cout << "Введите  значение элемента" << endl;
				std::getline(cin, val);
				try
				{
					l.EditByIndex(std::stoi(n), std::stoi(val));
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Вывести отсортированный список
			else if (ch == "6") {
				l.PrintHeadToTailList();
			}
			// Вывести исходный список
			else if (ch == "7") {
				l.PrintOriginalList();
			}
			// Очистка списка
			else if (ch == "8") {
				printMainMenu(2);
				l.clearList();
			}
			// Получить индекс элемента по заданному значению
			else if (ch == "9") {
			std::string val;
			cout << "Введите значение элемента" << endl;
			std::getline(cin, val);
			try
			{
				cout << l.getElementIndex(std::stoi(val)) << endl;
			}
			catch (std::exception& ex)
			{
				cout << ex.what() << endl;
			}
			}
			// Получить индекс элемента по заданному значению
			else if (ch == "10") {
			std::string n;
			cout << "Введите позицию элемента" << endl;
			std::getline(cin, n);
			try
			{
				cout << l.getElementByIndex(std::stoi(n)) << endl;
			}
			catch (std::exception& ex)
			{
				cout << ex.what() << endl;
			}
			}
			// Проверить наличие элемента по заданному значению
			else if (ch == "11") {
				cout << "Введите значение элемента\t";
				std::string val;
				std::getline(cin, val);
				try
				{
					cout << l.checkElement(std::stoi(val)) << endl;
				}
				catch (std::exception& ex)
				{
					cout << ex.what() << endl;
				}
			}
			// Информация о списке
			else if (ch == "12") {
				if (l.EmptyCheck())
					cout << "| >> Список пуст" << endl;
				else
					cout << "| >> В списке есть элементы" << endl;
				cout << "| Количество свободных ячеек\t" << l.getEmptyCells() << endl
					 << "| Количество занятых ячеек\t" << l.getBusyCells() << endl
					 << "| Размер списка\t" << l.getSize() << endl;
			}
			// Меню с итератором
			else if (ch == "13") {
				iteratorMenu(l, it);
			}
			// Выход
			// (exit)
			else if (ch == "exit") {
				std::cout << ">> Завершение программы..." << std::endl;
				break;
			}
			else {
				std::cout << ">> Ошибка..." << std::endl;
				std::cout << ">> Выбранная операция отсутствует..." << std::endl;
			}
		}
		catch (std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	}
}

void printMainMenu(int n) {
	if (n == 0) {
		cout << "+---------------------------------------------------------------------" << endl;
		cout << "| 0  - Очистить консоль" << endl
			<< "| 1  - Включение нового значения" << endl
			<< "| 2  - Включение нового значения по индексу" << endl
			<< "| 3  - Удалить элементы по значению" << endl
			<< "| 4  - Удалить элемент по индексу" << endl
			<< "| 5  - Изменить элемент по индексу" << endl
			<< "| 6  - Вывести отсортированный список" << endl
			<< "| 7  - Вывести исходный список" << endl
			<< "| 8  - Очистить список" << endl
			<< "| 9  - Получить индекс элемента по заданному значению" << endl
			<< "| 10 - Получить значение элемента по заданному индексу" << endl
			<< "| 11 - Проверить наличие элемента по заданному значению" << endl
			<< "| 12 - Информация о списке" << endl
			<< "| 13 - Меню итератора" << endl
			<< "| (exit)" << endl;
		cout << "+---------------------------------------------------------------------" << endl << endl;
	}
	else {
		if (n == 2) {
			cout << "+----------------------------------------------------------------" << endl
				 << "| Очистка списка" << endl
				 << "+----------------------------------------------------------------" << endl;
		}
		else if (n == 3) {
			cout << "+----------------------------------------------------------------" << endl
				 << "| Проверка списка на пустоту\t" << endl
				 << "+----------------------------------------------------------------" << endl;
		}
	}
}

void printIteratorMenu() {
	std::cout << "	Операции итераторов" << std::endl;
	std::cout << "1 - Установить итератор на начало списка" << std::endl
		<< "2 - Установить итератор на конец списка" << std::endl
		<< "3 - Следующий" << std::endl
		<< "4 - Предыдущий" << std::endl
		<< "5 - Получить текущее значение" << std::endl
		<< "7 - Проверка равенства итераторов" << std::endl
		<< "8 - Проверка неравенства итераторов" << std::endl
		<< "9 - Меню итераторов" << std::endl
		<< "e - Выход" << std::endl;
}

int iteratorMenu(LinkedList<int>& list, LinkedList<int>::iterator& it) {

	std::string ch;
	auto begin = list.begin();
	auto end = list.end();
	it = begin;

	printIteratorMenu();

	while (true)
	{
		cout << "Введите номер операции: ";
		std::getline(std::cin, ch);
		try
		{
			if (ch == "1") {
				cout << "Запрос прямого итератора begin(): " << endl;
				it = list.begin();
				cout << *it << endl;
			}
			else if (ch == "2") {
				cout << "Запрос 'неустановленного' прямого итератора end(): " << endl;
				it = list.end();
				cout << *it << endl;
			}
			else if (ch == "3") {
				cout << ">> Следующий" << endl;
				if (it != end) {
					it++;
					cout << *it << endl;
				}
				else
					cout << ">> Итератор достиг конца списка..." << endl;
			}
			else if (ch == "4") {
				cout << "Предыдущий" << endl;
				if (it != begin) {
					it--;
					cout << *it << endl;
				}
				else
					cout << ">> Итератор достиг начала списка..." << endl;
				cout << *it << endl;
			}
			else if (ch == "5") {
				cout << "Получить текущее значение" << endl;
				cout << *it << endl;
			}
			else if (ch == "6") {
				/*cout << "Изменить текущее значение" << endl;
				cout << "Введите значение: ";
				int temp = 0;
				cin >> temp;
				it[] = temp;*/
			}
			else if (ch == "7") {
				cout << "Проверка равенства итераторов" << endl;
				cout << "Результат " << (int)(*list.begin() == (*list.end())) << endl;
			}
			else if (ch == "8") {
				cout << "Проверка неравенства итераторов" << endl;
				cout << "Результат " << (int)(*list.begin() != (*list.end())) << endl;
			}
			else if (ch == "9") {
				printIteratorMenu();
			}
			else if (ch == "e") {
				break;
			}
			else {
				std::cout << ">> Ошибка..." << std::endl;
				std::cout << ">> Выбранная операция отсутствует..." << std::endl;
			}
		}
		catch (std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
	return 0;
}

void test(LinkedList<int>& list, int n) {
	
	for (size_t i = 0; i < n; i++)
	{
		int val = rand() % 1024;
		list.InsertByIndex(i, val);
	}

	list.InsertByIndex(0, 1);
	list.InsertByIndex(0, 2);
	list.InsertByIndex(1, 128);
	list.InsertByIndex(1, 256);
	list.InsertByIndex(128, 1024);
	list.InsertByIndex(1, 1024);
	list.InsertByIndex(1, 1024);
	list.InsertByIndex(1024, 1024);
	list.InsertByIndex(0, 1024);
	list.InsertByIndex(3, 128);
	list.InsertByIndex(0, 64);

	LinkedList<int> l2 = LinkedList<int>(list);
	l2.PrintHeadToTailList();
}