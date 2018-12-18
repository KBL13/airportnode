template <typename T>
BST<T>::BST(int th)
{

	threshold = th;
	root = nullptr;
}

template <typename T>
BST<T>::BST(const string input, int th)
{
	threshold = th;
	root = nullptr;
	buildFromInputString(input);
}

template <typename T>
BST<T>::~BST()
{
	makeEmpty();
}

template <typename T>
BST<T>::BST(const BST& rhs)
{
	root = nullptr;
	*this = rhs;
}

template <typename T>
BST<T>::BST(BST&& rhs)
{
	root = rhs.root;
	threshold = rhs.threshold;
	rhs.root = nullptr;
	rhs.threshold = 0;
}

template <typename T>
void BST<T>::buildFromInputString(const string input)
{
	if(!empty())	makeEmpty();
	T temp;
	stringstream ss(input);
	while (ss >> temp)
	{
		insert(temp);
	}
}

template <typename T>
const BST<T> & BST<T>::operator= (const BST & rhs)
{
	if (this != &rhs)
	{
		makeEmpty(root);
		root = clone(rhs.root);
	}
	return *this;
}

template <typename T>
const BST<T> & BST<T>::operator=(BST && rhs)
{
	if (this != &rhs)
	{
		std::swap(root, rhs.root);
		std::swap(threshold, rhs.threshold);
	}
	return *this;
}
template <typename T>
bool BST<T>::empty()
{
	if (root == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
void BST<T>::printInOrder() const
{
	printInOrder(root);
	cout << endl;
}

template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder(root);
	cout << endl;
}

template <typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes(root);
	cout << endl;
}

template <typename T>
int BST<T>::height() const
{
	return height(root);
	cout << endl;
}

template <typename T>
void BST<T>::makeEmpty()
{
	makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T& v)
{
	insert(v, root);
}

template <typename T>
void BST<T>::insert(T &&v)
{
	insert(v, root);
}

template <typename T>
void BST<T>::remove(const T& v)
{
	remove(v, root);
}

template <typename T>
bool BST<T>::contains(const T& v)
{
	return contains(v, root, root);
}

