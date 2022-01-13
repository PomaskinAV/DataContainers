#include<iostream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "   "

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
	} *Root; //Корень дерева
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}
	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:" << this << endl;
	}
	~Tree()
	{
		clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
	}
	Tree& operator=(const Tree& other)
	{
		if (this == &other)return *this;
		clear();
		copy(other.Root);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int depth()const
	{
		return depth(this->Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	void print(int depth)const
	{
		print(this->Root, depth);
		cout << endl;
	}
	void tree_print()
	{
		tree_print(0);
	}

	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return avg(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
private:
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	void insert(int Data, Element* Root)
	{
		//Root - корень под дерева
		//this->Root корень всего дерева
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)//Если есть место для добавления элемента,
				Root->pLeft = new Element(Data);//добавляем элемент прямо сюда.
			else// в противном случае
				insert(Data, Root->pLeft);//идем на левом и ищем место куда добавить элемент.
		}
		else //if(Data>Root->Data) - уникальное дерево
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf()) //Если элемент является листком
			{
				//то его можно удалять
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))//Если в левой ветке больше элементов чем в правой ветке
				{
					Root->Data = maxValue(Root->pLeft); // То заменяем значение удаляемого элемента максимальным значением в левой ветке
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else//В противном случае
				{
					Root->Data = minValue(Root->pRight);//заменяем значение удаляемого элемента минимальным значением в правой ветке
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);*/
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root ? sum(Root->pLeft) + sum(Root->pRight) + Root->Data : 0;
	}
	double avg(Element* Root)const
	{
		return (double)sum(Root) / count(Root);
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void print(Element* Root, int depth)const
	{
		if (Root == nullptr || depth == -1)return;
		if (depth == 1 && Root->pLeft == nullptr)cout << " " << tab;
		print(Root->pLeft, depth - 1);
		cout << tab;

		if (depth == 0)cout << Root->Data /*<< tab*/;
		//for (int i = 0; i < this->depth() - depth; i++)cout << tab;
		int min_distance = 4;
		cout.width(min_distance * (this->depth() - depth));
		if (depth == 1 && Root->pRight == nullptr)cout << " " << tab;
		print(Root->pRight, depth - 1);
		//cout << tab;
	}
	void tree_print(int depth)
	{
		if (depth == this->depth())return;
		int min_distance = 4;
		cout.width(min_distance * (this->depth() - depth));
		//for (int i = 0; i < (this->depth() - depth)*4; i++)cout << tab;
		print(depth);
		//for (int i = 0; i < (this->depth() - depth)*4; i++)cout << tab;
		cout << endl;
		tree_print(depth + 1);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве:  " << tree.count() << endl;
	cout << "Сумма элементов в дереве: " << tree.sum() << endl;
	cout << "Среднее арифметическое элементов в дереве:" << tree.avg() << endl;
	tree.clear();
	tree.print();
#endif // BASE_CHECK
	
	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 8, 18, 48, 77, 85 };
	tree.print();
	int value;
	/*cout << "Введите удаляемое значение: "; cin >> value;
	tree.erase(value);
	tree.print();*/
	cout << "Глубина дерева: " << tree.depth() << endl;
	//tree.print(3);
	tree.tree_print();
}