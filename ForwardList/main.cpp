#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data; // �������� ��������
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	Element()
	{
		cout << "EDesstructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head; // ��������� �� ��������� ������� ������
	int size;
public:
	int get_size()const
	{
		return this->size;
	}
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
		//1 ������� �������
		Element* New = new Element(Data);
		//2 ������������ ����� ������� � ������
		New->pNext = Head;
		//3 ��������� ������ �� ����� �������
		Head = New;
	}
	void push_back(int Data)
	{
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (true)
		{
			if (Temp->pNext == nullptr)break;
			else Temp = Temp->pNext;
		}
		Temp->pNext = New;
	}
	void pop_front()
	{
		Element* del = Head;
		Head = Head->pNext;
		delete del;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	// Methods
	void print()const
		{
			Element * Temp = Head; //Temp - ��������
			//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ��������
			while (Temp != nullptr)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext; //������� �� ��������� �������
			}
		}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
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
}