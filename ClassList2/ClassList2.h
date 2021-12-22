#pragma once
#include<iostream>
using namespace std;

#define tab "\t"

//#define DEBUG

template<typename T>
class List;
template<typename T>
void print_list(const List<T>& list);
template<typename T>
void reverse_print_list(const List<T>& list);

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;//объ€вл€ем 2 указател€ после описани€ класса
	//эти указатели переменные члены класса List
	size_t size;//размер списка

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
	};

public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
		T& operator*();
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp);
		~Iterator();
		T& operator*();
	};
	class ConstReversIterator :public BaseIterator
	{
	public:
		ConstReversIterator(Element* Temp = nullptr);
		~ConstReversIterator();
		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
		T& operator*();
	};
	class ReversIterator :public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp);
		~ReversIterator();
		T& operator*();
	};
	Iterator begin();
	ConstIterator cbegin() const;
	Iterator end();
	ConstIterator cend() const;
	ReversIterator rbegin();
	ConstReversIterator crbegin()const;
	ReversIterator rend();
	ConstReversIterator crend()const;

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//Operators
	List<T>& operator=(const List<T>& other);

	//Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	// Removing
	void pop_front();
	void pop_back();
	void erase(int Index);

	//Methods
	void print()const;
	void reverse_print()const;
};