#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "pch.h"

template<class T> class Iterator {

private:
	T* data;
	int* prevRefs;
	int* nextRefs;
	int current;
public:
	//Конструктор без параметров (по умолчанию)
	Iterator(int current){
		this->current = current;
	}

	//Конструктор копирования
	Iterator(T* data, int* prevRefs, int* nextRefs, int current) {
		this->data = data;
		this->prevRefs = prevRefs;
		this->nextRefs = nextRefs;
		this->current = current;
	}

	//Установка итератора на следующий элемент массива ++
	Iterator& operator ++(int i)
	{
		int newCurrent = nextRefs[current];
		current = newCurrent;
		return *this;
	}

	//Установка итератора на предыдущий элемент массива 
	Iterator& operator --(int i)
	{
		int newCurrent = prevRefs[current];
		current = newCurrent;
		return *this;
	}

	////Доступ к значению текущего элемента по чтению и записи *
	int operator *() { return data[current]; }

	//Оператор ->
	int operator ->() { return current; }

	//Проверка равенства итераторов ==
	bool operator ==(const Iterator& other)
	{
		if (current == other.current)
			return true;
		else
			return false;
	}

	//Проверка неравенства итераторов ! =
	bool operator !=(const Iterator& other) { return !(*this == other); }
};

template <class DataT> class LinkedList
{
public:
	// Конструктор
	LinkedList() {
		data = new DataT[Size];
		nextRefs = new int[Size];
		prevRefs = new int[Size];

		EmptyHead = 0;

		clearList(Size);
	}
	
	// Конструктор копирования
	LinkedList(const LinkedList<DataT> &other) {

		Size = other.Size;

		Head = other.Head;
		Tail = other.Tail;

		EmptyHead = other.EmptyHead;
		EmptyCells = other.EmptyCells;

		data = new DataT[Size];
		nextRefs = new int[Size];
		prevRefs = new int[Size];

		for (int i = 0; i < Size; i++)
		{
			data[i] = other.data[i];
			nextRefs[i] = other.nextRefs[i];
			prevRefs[i] = other.prevRefs[i];
		}
	}

	// Деструктор
	~LinkedList() {
		delete data;
		delete prevRefs;
		delete nextRefs;
	}

	void resize() {

		int newSize = Size + SizeStep;

		DataT* subData = new DataT[Size];
		int* subPrevRefs = new int[Size];
		int* subNextRefs = new int[Size];

		for (size_t i = 0; i < Size; i++)
		{
			subData[i] = data[i];
			subPrevRefs[i] = prevRefs[i];
			subNextRefs[i] = nextRefs[i];
		}

		delete data;
		delete prevRefs;
		delete nextRefs;

		data = new DataT[newSize];
		prevRefs = new int[newSize];
		nextRefs = new int[newSize];

		clearList(newSize);

		for (size_t i = 0; i < Size; i++)
		{
			data[i] = subData[i];
			prevRefs[i] = subPrevRefs[i];
			nextRefs[i] = subNextRefs[i];
			EmptyCells--;
		}

		Size = newSize;
		EmptyHead = Size - EmptyCells;
	}

	void clearList(int s = 0) {
		
		if (s != 0)
		{
			// Зачистка массива с data
			for (size_t i = 0; i < s; i++)
				data[i] = NULL;

			// Заполнение массива с nextRefs на пустые ячейки
			for (size_t i = 0; i < s; i++)
			{
				EmptyCells++;
				if (i < s - 1)
					nextRefs[i] = i + 1;
				else
					nextRefs[i] = -1;
			}

			// Зачистка массива с prevRefs
			for (size_t i = 0; i < s; i++)
				prevRefs[i] = NULL;
		}
		else {
			// Полная очистка списка
			// Зачистка массива с data
			for (size_t i = 0; i < Size; i++)
				data[i] = NULL;

			// Заполнение массива с nextRefs на пустые ячейки
			for (size_t i = 0; i < Size; i++)
			{
				EmptyCells++;
				if (i < Size - 1)
					nextRefs[i] = i + 1;
				else
					nextRefs[i] = -1;
			}

			// Зачистка массива с prevRefs
			for (size_t i = 0; i < Size; i++)
				prevRefs[i] = NULL;

			EmptyHead = 0;
			Head = -1;
			Tail = -1;
			EmptyCells = Size;
		}
	}

	bool checkElement(DataT element) {

		int i = 0;
		int point = 0;
		int n = Head;

		do
		{
			if (data[n] == element) {
				return true;
			}

			if (n == -1) {
				break;
			}

			point = n;
			n = nextRefs[point];
			i++;
		} while (true);

		return false;
	}

	// Включение нового значения
	void InsertToTail(DataT element) {

		int subEmptyHead;

		if (EmptyCells == 0)
			resize();

		if (EmptyHead > -1 && EmptyCells != 0)
		{
			if (EmptyCells == Size)
			{
				data[EmptyHead] = element;

				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[EmptyHead] = -1;
				prevRefs[EmptyHead] = -1;
				Head = EmptyHead;
				Tail = EmptyHead;

				EmptyHead = subEmptyHead;
			}
			else
			{
				data[EmptyHead] = element;

				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[Tail] = EmptyHead;
				prevRefs[EmptyHead] = Tail;
				Tail = EmptyHead;
				nextRefs[EmptyHead] = -1;

				EmptyHead = subEmptyHead;
			}
			EmptyCells--;
		}
	}

	// Включение нового значения в позицию с заданным номером
	void InsertByIndex(int position, DataT element) {
		
		int subEmptyHead;

		if (EmptyCells == 0)
			resize();

		if (EmptyHead > -1 && EmptyCells != 0)
		{
			if (EmptyCells == Size)
			{
				data[EmptyHead] = element;

				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[EmptyHead] = -1;
				prevRefs[EmptyHead] = -1;
				Head = EmptyHead;
				Tail = EmptyHead;

				EmptyHead = subEmptyHead;
			}
			else if (position >= EmptyHead)
			{
				// Вставка в конец списка
				data[EmptyHead] = element;

				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[Tail] = EmptyHead;
				prevRefs[EmptyHead] = Tail;
				Tail = EmptyHead;
				nextRefs[EmptyHead] = -1;

				EmptyHead = subEmptyHead;
			}
			else if (position == 0)
			{
				// Вставка в начало списка
				data[EmptyHead] = element;

				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];

				prevRefs[Head] = EmptyHead;
				nextRefs[EmptyHead] = Head;
				Head = EmptyHead;
				prevRefs[EmptyHead] = -1;

				EmptyHead = subEmptyHead;
			}
			else if (position > 0 && position < EmptyHead)
			{
				// Вставка в середину списка
				// Записываем данные в свободную ячейку
				data[EmptyHead] = element;
				// Перезаписываем главный указатель на пустую ячейку
				subEmptyHead = nextRefs[EmptyHead];
				// Поиск места вставки
				int subPosition = Head;
				int subCounter = 0;
				while (subCounter < position) {
					int s = subPosition;
					subPosition = nextRefs[s];
					subCounter++;
				};
				int a = prevRefs[subPosition];
				int b = subPosition;
				// Связыем существующие элементы с новым элементом
				prevRefs[b] = EmptyHead;
				nextRefs[a] = EmptyHead;
				// Связыем новый элемент с существующими элементами
				prevRefs[EmptyHead] = a;
				nextRefs[EmptyHead] = b;

				EmptyHead = subEmptyHead;
			}
			EmptyCells--;
		}
	}

	// Удаление заданного значения из списка
	void DeleteElement(DataT element) {
		if (Size - EmptyCells != 0) {

			int i = 0;
			int point = 0;
			int counter = 0;
			int n = Head;

			do
			{
				if (data[n] == element) {

					DeleteByIndex(i);
					n = Head;
					i = 0;
					counter++;
				}

				if (n == -1) {
					break;
				}

				point = n;
				n = nextRefs[point];
				i++;
			} while (true);
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| Removed " << counter << " elements." << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl << std::endl;
		}
		else {
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| Удаление невозможно! Список пуст!" << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl << std::endl;
		}
	}

	// Удаление значения из позиции с заданным номером
	void DeleteByIndex(int position)
	{
		if (Size - EmptyCells > 0) {
			if (position == 0)
			{
				int newHead = nextRefs[Head];

				data[Head] = NULL;
				nextRefs[Head] = EmptyHead;
				EmptyHead = Head;
				prevRefs[Head] = NULL;

				Head = newHead;
				prevRefs[Head] = -1;
			}
			else if (position >= Size - EmptyCells)
			{
				int newTail = prevRefs[Tail];

				data[Tail] = NULL;
				nextRefs[Tail] = EmptyHead;
				EmptyHead = Tail;
				prevRefs[Tail] = NULL;

				Tail = newTail;
				nextRefs[Tail] = -1;
			}
			else if (position > 0 && position < Size - EmptyCells)
			{
				// Поиск места удаления
				int subPosition = Head;
				int subCounter = 0;
				while (subCounter < position) {
					int s = subPosition;
					subPosition = nextRefs[s];
					subCounter++;
				};
				int a = prevRefs[subPosition];
				int b = nextRefs[subPosition];
				// Связываем левую и правую ячейку от удалённой ячейки
				nextRefs[a] = b;
				prevRefs[b] = a;
				// Удаляем данные ячейки
				data[subPosition] = NULL;
				nextRefs[subPosition] = EmptyHead;
				EmptyHead = subPosition;
				prevRefs[subPosition] = NULL;
			}

			EmptyCells++;
		}
		else {
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| Удаление невозможно! Список пуст!" << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl << std::endl;
		}
	}

	// Изменение значения с заданным номером в списке
	void EditByIndex(int position, DataT element) {
		if (Size - EmptyCells > 0) {
			if (position == 0)
			{
				data[Head] = element;
			}
			else if (position >= Size - EmptyCells)
			{
				data[Tail] = element;
			}
			else if (position > 0 && position < Size - EmptyCells)
			{
				// Поиск места редактирования
				int subPosition = Head;
				int subCounter = 0;
				while (subCounter < position) {
					int s = subPosition;
					subPosition = nextRefs[s];
					subCounter++;
				};
				data[subPosition] = element;
			}
		}
		else
			std::cout << "Редактирование невозможно! Список пуст!" << std::endl << std::endl;
	}
	
	// Получение позиции в списке для заданного значения
	int getElementIndex(DataT element) {
		if (Size - EmptyCells != 0) {

			int i = 0;
			int point = 0;
			int n = Head;

			do
			{
				if (data[n] == element)
					return n;
				
				if (n == -1) break;

				point = n;
				n = nextRefs[point];
				i++;
			} while (true);
		}

		return -1;
	}

	// Чтение значения с заданным номером в списке
	int getElementByIndex(int position) {
		if (Size - EmptyCells != 0) {

			int i = 0;
			int point = 0;
			int n = Head;

			do
			{
				if (n == position) {
					return data[n];
				}
				else if (n == -1)
					break;

				point = n;
				n = nextRefs[point];
				i++;
			} while (true);
		}

		return -1;
	}

	void PrintOriginalList() {
		std::cout << "+----------------------------------------------------------------" << std::endl;
		std::cout << "| Empty Head \t" << EmptyHead << std::endl;
		std::cout << "| Head \t" << Head << std::endl;
		std::cout << "+----------------------------------------------------------------" << std::endl;

		std::cout << "# \t|\t Data \t|\t Prev \t|\t Next" << std::endl;
		for (size_t i = 0; i < Size; i++)
			std::cout << i << " \t|\t " << data[i] << " \t|\t " << prevRefs[i] << " \t|\t " << nextRefs[i] << std::endl;

		std::cout << "+----------------------------------------------------------------" << std::endl;
		std::cout << "| Tail \t" << Tail << std::endl;
		std::cout << "+----------------------------------------------------------------" << std::endl;
		std::cout << std::endl;
	}

	void PrintHeadToTailList()
	{
		if (Size - EmptyCells != 0) {
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| Head \t" << Head << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl;

			std::cout << "# \t|\t Data" << std::endl;
			int subPosition = 0;
			for (int i = 0, n = Head; i < Size - EmptyCells; i++) {

				std::cout << i << " \t|\t " << data[n] << std::endl;
				subPosition = n;
				n = nextRefs[subPosition];
			}

			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| Tail \t" << Tail << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << std::endl;
		}
		else {
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| List is Empty \t" << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl;
		}
	}

	int getSize() { return Size; }
	int getEmptyCells() { return EmptyCells; }
	int getBusyCells() { return Size - EmptyCells; }

	int EmptyCheck() {
		if (Size != EmptyCells)
			return false;
		else
			return true;
	}

	DataT getHead() { return Head; }

	typedef Iterator<DataT> iterator;
	//Создание прямого итератора begin()
	Iterator<DataT> begin() {
		return Iterator<DataT>(data, prevRefs, nextRefs, Head);
	}

	//Запрос «неустановленного» итератора end()
	Iterator<DataT> end() {
		return Iterator<DataT>(data, prevRefs, nextRefs, Tail);
	}

private:
	DataT* data;
	int* nextRefs;
	int* prevRefs;

	int SizeStep = 4;
	int Size = SizeStep;

	int Head = -1;
	int Tail = -1;

	int EmptyHead = -1;
	int EmptyCells = 0;
};

#endif