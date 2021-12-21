#include<iostream>
using namespace std;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;//объявляем 2 указателя после описания класса
	//эти указатели переменные члены класса List
	size_t size;//размер списка

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
			cout << "BItConstructor:\t" << this << endl;
		}
		~BaseIterator()
		{
			cout << "BItDestructor:\t" << this << endl;
		}

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}
	};

public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
			cout << "ItConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}

		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		/*bool operator==(const Iterator& other)const
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
		const int& operator*()const
		{
			return Temp->Data;
		}*/
		int& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{

		}
		~Iterator()
		{

		}
		int& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	class ConstReversIterator :public BaseIterator
	{
	public:
		ConstReversIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
			cout << "RItConstructor:\t" << this << endl;
		}
		~ConstReversIterator()
		{
			cout << "RItDestructor:\t" << this << endl;
		}

		ConstReversIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReversIterator operator++(int)
		{
			ConstReversIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		ConstReversIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReversIterator operator--(int)
		{
			ConstReversIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

		/*bool operator==(const ReversIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReversIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		operator bool()const
		{
			return Temp;
		}
		const int& operator*()const
		{
			return Temp->Data;
		}*/
		int& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) :ConstReversIterator(Temp)
		{

		}
		~ReversIterator()
		{

		}
		int& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	ConstIterator cbegin() const
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ConstIterator cend() const
	{
		return nullptr;
	}

	ReversIterator rbegin()
	{
		return Tail;
	}
	ConstReversIterator crbegin()const
	{
		return Tail;
	}
	ReversIterator rend()
	{
		return nullptr;
	}
	ConstReversIterator crend()const
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;//Если список пуст, его голова и хвост указывают на ноль
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const List<T>& other) :List()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			this->push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	List(List&& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = other.Tail = nullptr;
		cout << "MoveConstructor:" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//Operators
	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			this->push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}

	//Adding elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//Когда в списке появляется первый элемент он одновременно я вляется и головой и хвостом
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(T Data, int Index)
	{
		if (Index >= size)
		{
			cout << "Error: Выход за пределы списка!" << endl;
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New -> pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	// Removing
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		if (Index == size - 1)
		{
			pop_back();
			return;
		}
		if (Index >= size)return;
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)
				Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	//Methods
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail:\t" << Tail << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail:\t" << Tail << endl;
		for(Element* Temp =Tail; Temp; Temp=Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head:\t" << Head << endl;
	}
};

template<typename T>
void print_list(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		//*it *= 123;
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>
void reverse_print_list(const List<T>& list)
{
	for (typename List<T>::ConstReversIterator rit = list.crbegin(); rit != list.crend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	cout << "\n------------------------\n";
	/*list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List<int> list = { 3,5,8,13,21 };
	list.print();

	List<int> list1;
	list1 = list;
	//list1.print();
	for (int i : list1)cout << i << tab; cout << endl;

	reverse_print_list(list1);
	print_list(list1);
}