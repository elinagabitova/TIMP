#include <iostream>

using namespace std;

template <typename T> class stack
{
private:
	T* stptr;
	int size;
	T top;
public:
	stack();
	stack(const T& size);
	~stack();

	void print()const;
	T operator[] (const T& num)const;
	void add(const T& value);
	bool isFull()const;
	void p_back();
	T get()const;

};

template <typename T> stack<T>::stack()
{
	stptr = new T[5]();
	top = 0;
	size = 5;
}

template<typename T> stack<T>::stack(const T& _size)
{
	stptr = new T[_size]();
	top = 0;
	size = _size;
}

template <typename T> stack<T>::~stack()
{
	delete[] stptr;
}

template<typename T> T stack<T>::operator[](const T& num)const
{
	return stptr[num];
}

template<typename T> bool stack<T>::isFull()const
{
	return (top >= size);
}

template<typename T> void stack<T>::add(const T& value)
{
	if (size == 0)
	{
		delete[] stptr;
		stptr = new T[1]();
		stptr[0] = value;
		++size;
		return;
	}

	if (!top && !stptr[0])
	{
		stptr[0] = value;
		return;
	}

	++top;

	if (isFull())
	{
		T* ptr = new T[size + 1]();
		for (int i = 0; i < size; i++)
			ptr[i] = stptr[i];
		delete[] stptr;
		stptr = ptr;
		++size;
		stptr[top] = value;
	}
	else
	{
		stptr[top] = value;
	}
}

template<typename T> void stack<T>::print()const
{
	if (size)
	{

		for (int i = 0; i < size; i++)
			cout << stptr[i] << "\t";
		cout << "\n";
	}
	else cout << "stack is empty!";
}

template<typename T> void stack<T>::p_back()
{
	if (top)
	{
		T* ptr = new T[size - 1];
		for (int i = 0; i < size - 1; i++)
			ptr[i] = stptr[i];
		delete[] stptr;
		stptr = ptr;
		--size;
		--top;
	}
	else
	{
		cout << "Now stack is empty!\n";
		if (top == 0)
		{
			delete[] stptr;
			stptr = nullptr;
			size = 0;
		}
	}
}

template<typename T> T stack<T>::get()const
{
	return stptr[top];
}

int main()
{
	int _size, value;
	char ch = '9';
	cout << "Enter the size: ";
	cin >> _size;
	stack<int> test(_size);
	while (ch != '0')
	{
		cout << "\n\n-----------------------------------------\n" <<
			"What do you want to do?\nPress:\n\"1\" to add data\n\"2\" to delete data\n\"3\" to show last element\n\"4\" to show the stack\n\"0\" to exit\n"
			<< "--------------------------------------------------------------" << "\n\n";

		cin >> ch;
		cout << "\n";
		switch (ch)
		{
		case '1':
		{
			cout << "Enter the value: ";
			cin >> value;
			test.add(value);
			break;
		}
		case '2':
		{
			test.p_back();
			break;
		}
		case '3':
		{
			cout << "Last element: " << test.get() << "\n";
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
