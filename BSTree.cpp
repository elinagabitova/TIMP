#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T> struct Node
{
	T element;
	Node* pLeft;
	Node* pRight;
	Node* pParent;
};

template <class T> class BSTree
{
private:
	Node<T>* root;
	unsigned int count;
public:

	BSTree()
	{
		root = nullptr;
		count = 0;
	}

	BSTree(initializer_list<T> elements) : BSTree()
	{

		for (int i = 0; i < elements.size(); i++)
		{
			insert(*(elements.begin() + i));
		}
	}

	BSTree(vector<T> data) : BSTree()
	{
		for (int i = 0; i < data.size(); i++)
		{
			insert(data.at(i));
		}
	}

	~BSTree()
	{
		delNode(root);
	}

	void delNode(Node<T>* temp)
	{
		if (!temp)
			return;
		if (temp->pLeft)
		{
			delNode(temp->pLeft);
			temp->pLeft = nullptr;
		}

		if (temp->pRight)
		{
			delNode(temp->pRight);
			temp->pRight = nullptr;
		}
		delete temp;
	}


	void insert(const T& added)
	{
		try
		{
			if (search_result(added))
				throw 5;
			Node<T>* daughter = new Node<T>;
			daughter->element = added;
			daughter->pLeft = daughter->pRight = daughter->pParent = nullptr;
			Node<T>* parent = root;
			Node<T>* temp = root;
			while (temp)
			{
				parent = temp;
				if (added < temp->element)
					temp = temp->pLeft;
				else
					temp = temp->pRight;
			}
			if (!parent)
				root = daughter;
			else
			{
				if (added < parent->element)
				{
					parent->pLeft = daughter;

				}
				else
				{
					parent->pRight = daughter;

				}
				daughter->pParent = parent;
			}
			count++;
		}
		catch (int i)
		{
			cout << "This number \"" << added << "\" has already added in the tree!\nError #5\n";
		}
	}

	void display(const Node<T>* temp, unsigned int level)const
	{
		try
		{
			if (!root)
			{
				throw 2;
			}
			if (temp)
			{
				display(temp->pLeft, level + 1);
				for (int i = 0; i < level; i++)
					cout << "__";
				cout << temp->element << "\n";
				display(temp->pRight, level + 1);
			}
		}
		catch (int i)
		{
			cout << "There is nothing to print\nError #2\n";
		}
	}

	int get_count()const
	{
		return count;
	}

	Node<T>* get_point(const T& value, Node<T>* temp)const
	{
		if (temp == 0 || value == temp->element)
			return temp;
		if (value > temp->element)
			return get_point(value, temp->pRight);
		else return get_point(value, temp->pLeft);
	}

	bool search_result(const T& value)const
	{
		return get_point(value, root);
	}

	Node<T>* root_()const
	{
		return root;
	}

	void reading(const string& filename)
	{
		try
		{
			ifstream fin(filename);
			if (!fin)
				throw 1;
			T temp;
			fin >> count;
			for (int i = 0; i < count; ++i)
			{
				fin >> temp;
				insert(temp);
				count--;
			}
			fin.close();
		}
		catch (int i)
		{
			cout << "File doesn't exist!\nError #1\n";
		}
	}


	void output(ostream& ost, const Node<T>* temp)const
	{
		if (temp == nullptr)
		{
			return;
		}
		else
		{
			ost << temp->element << "	";
			output(ost, temp->pLeft);
			output(ost, temp->pRight);
		}
	}


	void writing(const string& filename)const
	{
		ofstream fout(filename);
		fout << count;
		output(fout, root);
		fout.close();
	}

	Node<T>* minVal(Node<T>* cur)
	{
		if (cur->pLeft == nullptr)
			return cur;
		else
			return minVal(cur->pLeft);
	}

	void remove(const T value)
	{
		try
		{
			Node<T>* delNode = get_point(value, root);
			if (!search_result(value))
				throw 6;

			if (delNode->pLeft && delNode->pRight)
			{
				delNode->element = minVal(delNode->pRight)->element;
				delNode = minVal(delNode->pRight);
			}


			if (!delNode->pLeft && !delNode->pRight)
			{
				if (delNode->pParent == nullptr)
				{
					root = nullptr;
					delete delNode;
					--count;
					return;
				}
				if (delNode->pParent->pLeft == delNode)
				{
					delNode->pParent->pLeft = nullptr;
					delete delNode;
					--count;
					return;
				}
				if (delNode->pParent->pRight == delNode)
				{
					delNode->pParent->pRight = nullptr;
					delete delNode;
					--count;
					return;
				}
			}
			if (delNode->pParent&&delNode->pLeft)
			{
				delNode->pParent->pLeft = delNode->pLeft;
				delNode->pLeft->pParent = delNode->pParent;
				delete delNode;
				--count;
				return;
			}
			if (delNode->pParent&&delNode->pRight)
			{
				if (delNode == delNode->pParent->pLeft)
				{
					delNode->pParent->pLeft = delNode->pRight;
				}
				else delNode->pParent->pRight = delNode->pRight;
				delNode->pRight->pParent = delNode->pParent;
				delete delNode;
				--count;
				return;
			}
			if (delNode->pLeft)
			{
				root = delNode->pLeft;
				delNode->pLeft = nullptr;
				delete delNode;
				--count;
				return;
			}
			if (delNode->pRight)
			{
				root = delNode->pRight;
				delNode->pRight = nullptr;
				delete delNode;
				--count;
				return;
			}
			if (!delNode->pParent && !delNode->pLeft && !delNode->pRight)
			{
				root = nullptr;
				delete delNode;
				--count;
				return;
			}

		}

		catch (int i)
		{
			cout << "There isnt element \"" << value << "\" in the tree!\nError#6\n";
		}
	}

	bool compare(const Node<T>* temp1, const Node<T>* temp2)const
	{
		bool x = true;
		x = temp1->element == temp2->element;
		if (x)
		{

			if (temp1->pLeft&&temp2->pLeft)
				return compare(temp1->pLeft, temp2->pLeft);
			if (!temp1->pLeft&&temp2->pLeft)
				return false;
			if (temp1->pLeft&&!temp2->pLeft)
				return false;
			if (temp1->pRight&&temp2->pRight)
				return compare(temp1->pRight, temp2->pRight);
			if (!temp1->pRight&&temp2->pRight)
				return false;
			if (temp1->pRight&&!temp2->pRight)
				return false;
			return true;
		}
		else return false;
	}


	bool operator == (const BSTree<T>& tree)const
	{
		return (compare(root, tree.root_()));
	}


	void preorder(Node<T>* node)
	{
		if (node)
		{
			cout << node->element << "\t";
			preorder(node->pLeft);
			preorder(node->pRight);
		}
	}


	void inorder(Node<T>* node)
	{
		if (node)
		{
			preorder(node->pLeft);
			cout << node->element << "\t";
			preorder(node->pRight);
		}
	}


	void postorder(Node<T>* node)
	{
		if (node)
		{
			preorder(node->pLeft);
			preorder(node->pRight);
			cout << node->element << "\t";
		}
	}
};



int main()
{
	char ch = 'y';
	int val;
	vector<int> data;
	cout << "Enter the data: \n";
	while (ch == 'y')
	{
		cin >> val;
		data.push_back(val);
		cout << "Press 'y' to continue\n";
		cin >> ch;
	}
	cout << "------------------------------------------------\n\n";
	BSTree<int> tree(data);
	cout << "Preorder travers: ";
	tree.preorder(tree.root_());
	cout << "\nInorder travers:  ";
	tree.inorder(tree.root_());
	cout << "\nPostrder travers: ";
	tree.postorder(tree.root_());
	system("pause");
	return 0;
}
