#include<iostream>
using namespace std;

#define tab "\t"
#define DEBUG

class Element
{
	int Data; // Значение элемента
	Element* pNext;
	static int count; //количество элементов
public:
	const Element* getpNext()const
	{
		return pNext;
	}
	int getData()const
	{
		return Data;
	}
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
	friend class Iterator;
};

int Element::count = 0; //статические переменные могут быть принициализированы только за классом

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//Operators
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp=Temp->pNext;
		return old;
	}
	int& operator*()const
	{
		return Temp->Data;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}
};

class ForwardList
{
	Element* Head; // Указывает на начальный элемент списка
	size_t size;
public:
	Element* getHead()const
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ForwardList()
	{
		this->Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDesstructor:\t" << this << endl;
		cout << "\n-------------------------\n";
	}
	// Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}

	// Adding element
	void push_front(int Data)
	{
		//1 создаем элемент
		//Element* New = new Element(Data);
		//2 присоединяем новый элемент к списку
		//New->pNext = Head;
		//3 Переносим Голову на новый элемент
		//Head = New;
		Head = new Element(Data, Head);
		size++;
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
		size++;
	}
	void pop_front()
	{
		Element* front = Head;
		Head = Head->pNext;
		delete front;
		size--;
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
		size--;
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
		//Element* New = new Element(Data);
		//Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		//New->pNext = Temp->pNext;
		//Включаем жлемент в список
		//Temp -> pNext = New;
		Temp->pNext = new Element(Data, Temp -> pNext);
		size++;
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
		size--;
	}

	// Methods
	void print()const
		{
			/*Element* Temp = Head; //Temp - итератор
			//Итератор - это указатель, при помощи которого можно получить доступ к элементу
			while (Temp != nullptr)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext; //Переход на следующий элемент
			}*/
		//for(Element* Temp = Head; Temp; Temp=Temp->pNext)
		//cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			for (Iterator Temp = Head; Temp !=nullptr; Temp++)
			cout << *Temp << tab;
			cout << endl;
			cout << "Количество элементов в списке: " << size << endl;
			cout << "Общее количество элементов: " << Head->count << endl;
		}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList plus = left;
	//for (const Element* Temp = right.getHead(); Temp; Temp = Temp->getpNext())
		//plus.push_back(Temp->getData());
	for (Iterator Temp = right.getHead(); Temp; Temp++)
	{
		plus.push_back(*Temp);
	}
	return plus;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define COPY_METHODS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARR

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2 = list1; //CopyConstroctor
	list2.print();
#endif // COPY_METHODS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	/*int arr[] = { 3,5,8,13,21 };
for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	cout << arr[i] << tab;
cout << endl;*/

/*ForwardList list = { 3,5,8,13,21 };
list.print();*/

	ForwardList list1 = { 3,5,8,13,21 };
	ForwardList list2 = { 34,55,89 };
	ForwardList list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARR
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;

	//Range-based for:
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARR

	ForwardList list = { 3,5,8,13,21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}