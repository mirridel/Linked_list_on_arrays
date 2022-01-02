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
	//����������� ��� ���������� (�� ���������)
	Iterator(int current){
		this->current = current;
	}

	//����������� �����������
	Iterator(T* data, int* prevRefs, int* nextRefs, int current) {
		this->data = data;
		this->prevRefs = prevRefs;
		this->nextRefs = nextRefs;
		this->current = current;
	}

	//��������� ��������� �� ��������� ������� ������� ++
	Iterator& operator ++(int i)
	{
		int newCurrent = nextRefs[current];
		current = newCurrent;
		return *this;
	}

	//��������� ��������� �� ���������� ������� ������� 
	Iterator& operator --(int i)
	{
		int newCurrent = prevRefs[current];
		current = newCurrent;
		return *this;
	}

	////������ � �������� �������� �������� �� ������ � ������ *
	int operator *() { return data[current]; }

	//�������� ->
	int operator ->() { return current; }

	//�������� ��������� ���������� ==
	bool operator ==(const Iterator& other)
	{
		if (current == other.current)
			return true;
		else
			return false;
	}

	//�������� ����������� ���������� ! =
	bool operator !=(const Iterator& other) { return !(*this == other); }
};

template <class DataT> class LinkedList
{
public:
	// �����������
	LinkedList() {
		data = new DataT[Size];
		nextRefs = new int[Size];
		prevRefs = new int[Size];

		EmptyHead = 0;

		clearList(Size);
	}
	
	// ����������� �����������
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

	// ����������
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
			// �������� ������� � data
			for (size_t i = 0; i < s; i++)
				data[i] = NULL;

			// ���������� ������� � nextRefs �� ������ ������
			for (size_t i = 0; i < s; i++)
			{
				EmptyCells++;
				if (i < s - 1)
					nextRefs[i] = i + 1;
				else
					nextRefs[i] = -1;
			}

			// �������� ������� � prevRefs
			for (size_t i = 0; i < s; i++)
				prevRefs[i] = NULL;
		}
		else {
			// ������ ������� ������
			// �������� ������� � data
			for (size_t i = 0; i < Size; i++)
				data[i] = NULL;

			// ���������� ������� � nextRefs �� ������ ������
			for (size_t i = 0; i < Size; i++)
			{
				EmptyCells++;
				if (i < Size - 1)
					nextRefs[i] = i + 1;
				else
					nextRefs[i] = -1;
			}

			// �������� ������� � prevRefs
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

	// ��������� ������ ��������
	void InsertToTail(DataT element) {

		int subEmptyHead;

		if (EmptyCells == 0)
			resize();

		if (EmptyHead > -1 && EmptyCells != 0)
		{
			if (EmptyCells == Size)
			{
				data[EmptyHead] = element;

				// �������������� ������� ��������� �� ������ ������
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

				// �������������� ������� ��������� �� ������ ������
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

	// ��������� ������ �������� � ������� � �������� �������
	void InsertByIndex(int position, DataT element) {
		
		int subEmptyHead;

		if (EmptyCells == 0)
			resize();

		if (EmptyHead > -1 && EmptyCells != 0)
		{
			if (EmptyCells == Size)
			{
				data[EmptyHead] = element;

				// �������������� ������� ��������� �� ������ ������
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[EmptyHead] = -1;
				prevRefs[EmptyHead] = -1;
				Head = EmptyHead;
				Tail = EmptyHead;

				EmptyHead = subEmptyHead;
			}
			else if (position >= EmptyHead)
			{
				// ������� � ����� ������
				data[EmptyHead] = element;

				// �������������� ������� ��������� �� ������ ������
				subEmptyHead = nextRefs[EmptyHead];

				nextRefs[Tail] = EmptyHead;
				prevRefs[EmptyHead] = Tail;
				Tail = EmptyHead;
				nextRefs[EmptyHead] = -1;

				EmptyHead = subEmptyHead;
			}
			else if (position == 0)
			{
				// ������� � ������ ������
				data[EmptyHead] = element;

				// �������������� ������� ��������� �� ������ ������
				subEmptyHead = nextRefs[EmptyHead];

				prevRefs[Head] = EmptyHead;
				nextRefs[EmptyHead] = Head;
				Head = EmptyHead;
				prevRefs[EmptyHead] = -1;

				EmptyHead = subEmptyHead;
			}
			else if (position > 0 && position < EmptyHead)
			{
				// ������� � �������� ������
				// ���������� ������ � ��������� ������
				data[EmptyHead] = element;
				// �������������� ������� ��������� �� ������ ������
				subEmptyHead = nextRefs[EmptyHead];
				// ����� ����� �������
				int subPosition = Head;
				int subCounter = 0;
				while (subCounter < position) {
					int s = subPosition;
					subPosition = nextRefs[s];
					subCounter++;
				};
				int a = prevRefs[subPosition];
				int b = subPosition;
				// ������� ������������ �������� � ����� ���������
				prevRefs[b] = EmptyHead;
				nextRefs[a] = EmptyHead;
				// ������� ����� ������� � ������������� ����������
				prevRefs[EmptyHead] = a;
				nextRefs[EmptyHead] = b;

				EmptyHead = subEmptyHead;
			}
			EmptyCells--;
		}
	}

	// �������� ��������� �������� �� ������
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
			std::cout << "| �������� ����������! ������ ����!" << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl << std::endl;
		}
	}

	// �������� �������� �� ������� � �������� �������
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
				// ����� ����� ��������
				int subPosition = Head;
				int subCounter = 0;
				while (subCounter < position) {
					int s = subPosition;
					subPosition = nextRefs[s];
					subCounter++;
				};
				int a = prevRefs[subPosition];
				int b = nextRefs[subPosition];
				// ��������� ����� � ������ ������ �� �������� ������
				nextRefs[a] = b;
				prevRefs[b] = a;
				// ������� ������ ������
				data[subPosition] = NULL;
				nextRefs[subPosition] = EmptyHead;
				EmptyHead = subPosition;
				prevRefs[subPosition] = NULL;
			}

			EmptyCells++;
		}
		else {
			std::cout << "+----------------------------------------------------------------" << std::endl;
			std::cout << "| �������� ����������! ������ ����!" << std::endl;
			std::cout << "+----------------------------------------------------------------" << std::endl << std::endl;
		}
	}

	// ��������� �������� � �������� ������� � ������
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
				// ����� ����� ��������������
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
			std::cout << "�������������� ����������! ������ ����!" << std::endl << std::endl;
	}
	
	// ��������� ������� � ������ ��� ��������� ��������
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

	// ������ �������� � �������� ������� � ������
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
	//�������� ������� ��������� begin()
	Iterator<DataT> begin() {
		return Iterator<DataT>(data, prevRefs, nextRefs, Head);
	}

	//������ ����������������� ��������� end()
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