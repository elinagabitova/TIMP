#include <iostream>

using namespace std;

template <typename T> class list
{
private:

	T* list;
	int size;

public:
	list();
	list(const T& value);
	~list();
	void add(int number, T value);
	void print()const;
	void del(int number);
	T get(int number);
};

template <typename T> list<T>::list()
{
	list = new T[5]();
	size = 5;
}
template<typename T> list<T>::list(const T& value)
{
	list = new T[value]();
	size = value;
}
template <typename T> list<T>::~list()
{
	delete[] list;
}
template<typename T> void list<T>::add(int number, T value)
{
	if (number >= size)
	{
		T* ptr = new T[number + 1]();
		for (int i = 0; i < size; i++)
			ptr[i] = list[i];
		delete[] list;
		list = ptr;
		size = number + 1;
		list[number] = value;
	}
	else
	{
		list[number] = value;
	}
}

template<typename T> void list<T>::print()const
{
	if (size)
	{
		for (int i = 0; i < size; i++)
			cout << list[i] << "\t";
		cout << "\nSIZE *" << size << "*" << "\n\n";
	}
	else
	{
		cout << "list is empty!";
	}
}

template<typename T> void list<T>::del(int number)
{
	if (number < size)
	{
		int j = 0;
		T* ptr = new T[size - 1]();
		for (int i = 0; i < size; i++)
		{
			if (number == i)
				continue;
			ptr[j] = list[i];
			++j;
		}
		delete[] list;
		list = ptr;
		size--;
	}
	else {
		cout << "list is empty!";
	}
}

template<typename T> T list<T>::get(int number)
{
	if (number < size)
		return list[number];
	else
	{
		cout << "Error";
		exit(1);
	}
}
int main()
{
	int _size, value, key;
	char ch = '9';
	cout << "Enter the size: ";
	cin >> _size;
	list<int> test(_size);
	
	while (ch != '0')
	{
		cout << "\n\n--------------------------------------------------------------\n" <<
			"What do you want to do?\nPress:\n\"1\" to add data\n\"2\" to delete data\n\"3\" to show last element\n\"4\" to show the stack\n\"0\" to exit\n"
			<< "--------------------------------------------------------------" << "\n\n";

		cin >> ch;
		cout << "\n";
		switch (ch)
		{
			case '1':
			{
				cout << "Enter the key: ";
				cin >> key;
				cout << "Enter the value: ";
				cin >> value;
				test.add(key, value);
				break;
			}
			case '2':
			{
				cout << "Enter the key: ";
				cin >> key;
				test.del(key);
				break;
			}
			case '3':
			{
				cout << "Enter the key: ";
				cin >> key;
				cout << "Last element: " << test.get(key) << "\n";
				break;
			}

			case '4':
			{
				test.print();
				break;
			}
		}
	}

	system("pause");
	return 0;
}
