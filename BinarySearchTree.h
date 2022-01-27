#pragma once
//Fahad Waheed

using namespace std;

template <typename K, typename V>
class BST
{
	struct Node
	{
		K key;
		V value;
		Node* left, * right;
		Node* parent;

		Node() : key(K()), value(V()), left(NULL), right(NULL), parent(NULL) {};

		Node(K key, V value) : key(key), value(value), left(NULL), right(NULL), parent(NULL) {};
	};

	Node* root;

public:
	BST() : root(NULL) {};

	BST(const BST<K,V>& obj) : root(NULL) 
	{
		if (obj.root)
		{
			BST<K, V>::PreorderIterator it;

			for (it = obj.root; it != NULL; it++)
				Insert((*it).first, (*it).second);
		}
	}

	BST<K, V>& operator=(const BST<K, V>& obj)
	{
		this->clear();
		if (obj.root)
		{
			BST<K, V>::PreorderIterator it;

			for (it = obj.root; it != NULL; it++)
				Insert((*it).first, (*it).second);
		}
		return *this;
	}

	bool isEmpty()
	{
		return root == NULL;
	}

	void Insert(K key, V value)
	{
		if (isEmpty())
			root = new Node(key, value);
		else
		{
			Node* currnode = root;

			while (currnode)
			{
				if (currnode->key > key)
				{
					if (currnode->left)
						currnode = currnode->left;
					else
					{
						currnode->left = new Node(key, value);
						currnode->left->parent = currnode;
						break;
					}
				}
				if (currnode->key < key)
				{
					if (currnode->right)
						currnode = currnode->right;
					else
					{
						currnode->right = new Node(key, value);
						currnode->right->parent = currnode;
						break;
					}
				}
			}
		}
	}

	void Remove(K key, V value = V())
	{
		Node* currnode = root;

		while (currnode)
		{
			if (currnode->key == key)
				break;
			else if (currnode->key < key)
			{
				currnode = currnode->right;
			}
			else if (currnode->key > key)
			{
				currnode = currnode->left;
			}
		}

		if (currnode == NULL)
			return;

		if (currnode->left == NULL)//right child & no child case
		{
			if (currnode->parent == NULL)
			{
				root = currnode->right;
				if (currnode->right)
					currnode->right->parent = NULL;
			}
			else if (currnode->parent->left == currnode)
			{
				currnode->parent->left = currnode->right;
				if (currnode->right)
					currnode->right->parent = currnode->parent;
			}
			else if (currnode->parent->right == currnode)
			{
				currnode->parent->right = currnode->right;
				if (currnode->right)
					currnode->right->parent = currnode->parent;
			}

			delete currnode;
		}

		else if (currnode->right == NULL)//left child case
		{
			if (currnode->parent == NULL)
			{
				root = currnode->left;
				if (currnode->left)
					currnode->left->parent = NULL;
			}
			else if (currnode->parent->left == currnode)
			{
				currnode->parent->left = currnode->left;
				if (currnode->left)
					currnode->left->parent = currnode->parent;
			}
			else if (currnode->parent->right == currnode)
			{
				currnode->parent->right = currnode->left;
				if (currnode->left)
					currnode->left->parent = currnode->parent;
			}

			delete currnode;
		}

		else//both child case
		{
			Node* tempParent = NULL;
			Node* temp = currnode->right;

			while (temp->left)
			{
				tempParent = temp;
				temp = temp->left;
			}

			if (tempParent)
			{
				tempParent->left = temp->right;
				if (temp->right)
					temp->right->parent = tempParent;
			}
			else
			{
				currnode->right = temp->right; // currnode->right = currnode->right->right;
				if (temp->right)
					temp->right->parent = currnode;
			}
				
			currnode->key = temp->key;
			currnode->value = temp->value;

			delete temp;
		}
	}

	class InorderIterator
	{
		Node* it;

		Node* minNode(Node* node)
		{
			if (node)
			{
				Node* currnode = node;
				while (currnode->left)
					currnode = currnode->left;
				return currnode;
			}
			return NULL;
		}

	public:
		InorderIterator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = minNode(node);
		}

		pair<K, V> operator*()
		{
			pair<K, V> P;
			P.first = it->key;
			P.second = it->value;
			return P;
		}

		void operator++()
		{
			if (it == NULL)
				return;
			else if (it->right)
				it = minNode(it->right);
			else
			{
				Node* parent = it->parent;
				while (parent && parent->right == it)
				{
					it = parent;
					parent = parent->parent;
				}
				it = parent;
			}
		}

		void operator++(int)
		{
			++(*this);
		}

		bool operator==(Node* node)
		{
			return it == node;
		}

		bool operator!=(Node* node)
		{
			return it != node;
		}
	};

	class PreorderIterator
	{
		Node* it;

	public:
		PreorderIterator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = node;
		}

		pair<K, V> operator*()
		{
			pair<K, V> P;
			P.first = it->key;
			P.second = it->value;
			return P;
		}

		void operator++()
		{
			if (it == NULL)
				return;
			else if (it->left)
				it = it->left;
			else if (it->right)
				it = it->right;
			else
			{
				Node* parent = it->parent;
				while (parent && parent->right == it)
				{
					it = parent;
					parent = parent->parent;
				}
				if (parent)
					it = parent->right;
				else
					it = NULL;
			}
		}

		void operator++(int)
		{
			++(*this);
		}

		bool operator==(Node* node)
		{
			return it == node;
		}

		bool operator!=(Node* node)
		{
			return it != node;
		}
	};

	class PostorderIterator
	{
		Node* it;

		Node* deepNode(Node* node)
		{
			if (node)
			{
				Node* currnode = node;
				while (currnode->left)
					currnode = currnode->left;
				while (currnode->right)
				{
					currnode = currnode->right;
					while (currnode->left)
						currnode = currnode->left;
				}
				return currnode;
			}
			return NULL;
		}
	public:
		PostorderIterator() : it(NULL) {};

		void operator=(Node* node)
		{
			it = deepNode(node);
		}

		pair<K, V> operator*()
		{
			pair<K, V> P;
			P.first = it->key;
			P.second = it->value;
			return P;
		}

		void operator++()
		{
			if (it == NULL)
				return;
			else if (it->parent && it->parent->right == it)
				it = it->parent;
			else
			{
				Node* parent = it->parent;
				while (parent && parent->right == it)
				{
					it = parent;
					parent = parent->parent;
				}

				if (parent)
				{
					if (parent->right)
						it = deepNode(parent->right);
					else
						it = parent;
				}
				else
					it = NULL;
			}
		}

		void operator++(int)
		{
			++(*this);
		}

		bool operator==(Node* node)
		{
			return it == node;
		}

		bool operator!=(Node* node)
		{
			return it != node;
		}
	};

	Node* begin()
	{
		return root;
	}

	Node* end()
	{
		return NULL;
	}

	void clear()
	{
		if (isEmpty())
		{
			BST<K, V>::PostorderIterator itr;

			for (itr = begin(); itr != end(); itr++)
				Remove((*itr).first, (*itr).second);
		}
	}

	~BST()
	{
		clear();
	}
};
