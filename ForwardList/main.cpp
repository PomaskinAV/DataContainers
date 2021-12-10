#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data; // Значение элемента
	Element* pNext;
	static int count; //количество элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	Element()
	{
		count--;
		cout << "EDesstructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0; //статические переменные могут быть принициализированы только за классом

class ForwardList
{
	Element* Head; // Указывает на начальный элемент списка
public:
	ForwardList()
	{
		this->Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDesstructor:\t" << this << endl;
	}

	// Adding element
	void push_front(int Data)
	{
		//1 создаем элемент
		Element* New = new Element(Data);
		//2 присоединяем новый элемент к списку
		New->pNext = Head;
		//3 Переносим Голову на новый элемент
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}
	void pop_front()
	{
		Element* front = Head;
		Head = Head->pNext;
		delete front;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Выход за пределы списка" << endl;
			return;
		}
		if (Index == 0 || Head==nullptr)return push_front(Data);
		//Создаем новый элемент
		Element* New = new Element(Data);
		//Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		//Включаем жлемент в список
		Temp -> pNext = New;
	}
	void erase(int Index)
	{
		if (Index > Head->count)
		{
			cout << "Выход за пределы списка" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* New = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete New;
	}

	// Methods
	void print()const
		{
			Element * Temp = Head; //Temp - итератор
			//Итератор - это указатель, при помощи которого можно получить доступ к элементу
			while (Temp != nullptr)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext; //Переход на следующий элемент
			}
			cout << "Количество элементов списка: " << Head->count << endl;
		}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_front(rand() % 100);
	list.print();
	list.push_back(rand() % 100);
	list.print();
	cout << endl;
	list.pop_front();
	list.print();
	cout << endl;
	list.pop_back();
	list.print();
	cout << endl;
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << endl;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
}