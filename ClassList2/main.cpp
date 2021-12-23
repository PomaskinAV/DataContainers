#include"ClassList2.h"
#include"ClassList2.cpp"
#include<string>

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

	List<double> d_list = { 2.7, 3.14, 5.2, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "Happy", "New", "Year" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}