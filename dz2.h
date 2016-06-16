#pragma once
#pragma once
#include <iostream>


template<class Key, class Compare = std::less<Key>>
class set
{
public:

	// Конструктор по умолчанию 
	set(const Compare& c = Compare()) : _root(nullptr), _size(0), comp(c)
	{}

	template<class Iterator>
	set(Iterator begin, Iterator end, const Compare& c = Compare()) : comp(c), _root(nullptr)
	{
		for (Iterator it = begin; it != end; it++)
			this->insert(it._pointer->_val);
	}

	// Конструктор копирования 
	set(set& obj) : _size(0), _maxSize(obj.max_size()), comp(obj.comp), _root(nullptr)
	{
		for (set::iterator it = obj.begin(); it != obj.end(); ++it)
		{
			insert(it._pointer->_val);
		}

	}

	// диструктор 
	~set()
	{
		this->clear();
	}

	class iterator
	{
	public:
		setlocale(LC_ALL, "rus");
		friend class set<Key>;
		iterator(const Compare& c = Compare()) : _pointer(nullptr), comp(c)
		{}

		iterator(key_type<Key> * ptr, const Compare& c = Compare()) : _pointer(ptr), comp(c)
		{}

		iterator(const iterator & it) :_pointer(it._pointer)
		{}

		key_type<Key> & operator*()
		{
			if (_pointer == nullptr || _pointer->_nullflag)
				throw std::invalid_argument("Неправильный итератор");
			return (*_pointer);
		}

		key_type<Key> * operator->()
		{
			if (_pointer == nullptr)
				throw std::invalid_argument("Неправильный итератор");
			return (_pointer);
		}

		bool operator==(const iterator & it)
		{
			return (it._pointer == _pointer);
		}

		bool operator!=(const iterator & it)
		{
			return (it._pointer != _pointer);
		}

		iterator operator=(const iterator & it)
		{
			if (_pointer == it._pointer)
				return *this;
			_pointer = it._pointer;
			return (*this);
		}

		iterator operator++()
		{

			if (!_pointer)
				return *this;
			if (_pointer->_nullflag == true)
				return *this;


			if (_pointer->_parent == nullptr)
			{

				_pointer = _pointer->_right;
				while (_pointer->_left != nullptr)
					_pointer = _pointer->_left;
				return *this;
			}

			if (comp(_pointer->_val, _pointer->_parent->_val))
			{
				if (_pointer->_right != nullptr)
				{
					_pointer = _pointer->_right;
					while (_pointer->_left != nullptr)
						_pointer = _pointer->_left;

					return *this;
				}
				_pointer = _pointer->_parent;
				return *this;
			}

			if (!comp(_pointer->_val, _pointer->_parent->_val))
			{
				if (_pointer->_right == nullptr)
				{

					key_type<Key> * pi = _pointer;
					while (!comp(_pointer->_val, pi->_parent->_val)) 
					{

						pi = pi->_parent;
						if (pi->_parent == nullptr)
						{
							_pointer = pi->_right;
							break;
							return *this;
						}
					}

					_pointer = pi->_parent;
					return *this;
				}

				_pointer = _pointer->_right;
				while (_pointer->_left != nullptr)
					_pointer = _pointer->_left;
				return *this;

			}


		}

		iterator operator--()
		{
			if (_pointer == nullptr)
			{
				return *this;
			}
			if (_pointer->_nullflag)
			{
				_pointer = _pointer->_parent;
				return *this;
			}
			if (_pointer->_parent == nullptr)
			{
				_pointer = _pointer->_left;
				while (_pointer->_right != nullptr)
					_pointer = _pointer->_right;
				return *this;
			}

			if (_pointer->_val >= _pointer->_parent->_val) 
			{
				if (_pointer->_left != nullptr)
				{
					_pointer = _pointer->_left;
					while (_pointer->_right != nullptr)
						_pointer = _pointer->_right;

					return *this;
				}
				_pointer = _pointer->_parent;
				return *this;
			}

			if (_pointer->_val < _pointer->_parent->_val)
			{
				if (_pointer->_left == nullptr)
				{

					key_type<Key> * pi = _pointer;
					while (_pointer->_val < pi->_parent->_val)
					{

						pi = pi->_parent;
						if (pi->_parent == nullptr)
						{
							_pointer = pi->_left;
							break;
						}
					}

					_pointer = pi->_parent;
					return *this;
				}

				_pointer = _pointer->_left;
				while (_pointer->_right != nullptr)
					_pointer = _pointer->_right;
				return *this;

			}
		}

		iterator operator++(int)
		{
			iterator it(*this);
			++(it);
			_pointer = it._pointer;
			return (*this);
		}

		iterator operator--(int)
		{
			iterator it(*this);
			--(it);
			_pointer = it._pointer;
			return (*this);
		}

		~iterator() = default;

	private:
		key_type<Key> * _pointer;
		Compare comp;
	};

	struct key_compare
	{
		bool operator()(const Key& a, const Key& b) const
		{
			std::less<T> less;
			return less(a, b);
		}
	};

	iterator begin()
	{
		key_type<Key> * pi = _root;
		while (pi->_left != nullptr)
			pi = pi->_left;
		return iterator(pi);
	}

	iterator end()
	{
		key_type<Key> * pi = _root;
		while (pi->_right != nullptr)
			pi = pi->_right;
		if (!(pi->_nullflag))
		{
			pi->_right = new key_type<Key>(NULL, nullptr, nullptr, pi, true);
			return iterator(pi->_right);
		}
		else
			return iterator(pi);

	}

	iterator lower_bound(const Key& key)
	{
		iterator it = find(key);
		if (it == end())
		{
			insert(key);
			it = find(key);
			it++;
			erase(key);
			return it;
		}
		return it;
	}

	const iterator lower_bound(const Key& key) const
	{
		iterator it = find(key);
		if (it == end())
		{
			insert(key);
			it = find(key);
			it++;
			erase(key);
			return it;
		}

		return it;

	}

	iterator upper_bound(const Key& key)
	{

		iterator it = find(key);
		if (it == end())
		{
			insert(key);
			it = find(key);
			while (it._pointer->_val == key)
				it++;
			erase(key);
			return it;
		}

		if (it == --end())
		{
			return end();
		}
		while (it._pointer->_val == key)
			it++;
		return it;

	}

	const iterator upper_bound(const Key& key) const
	{
		iterator it = find(key);
		if (it == end())
		{
			insert(key);
			it = find(key);
			while (it._pointer->_val == key)
				it++;
			erase(key);
			return it;
		}

		if (it == --end())
		{
			return end();
		}
		while (it._pointer->_val == key)
			it++;
		return it;

	}

	template<class Key> // Этот класс включает в себя ключи, которые включает в себя набор
class key_type
{
public:
	key_type() : _val(0), _left(nullptr), _right(nullptr), _parent(nullptr), _nullflag(false)
	{}

	key_type(Key val, key_type * left = nullptr, key_type * right = nullptr, key_type * parent = nullptr, bool nullflag = false)
		: _val(val), _left(left), _right(right), _parent(parent), _nullflag(nullflag)
	{}

	key_type(const key_type & obj) : _val(obj._val), _left(nullptr), _right(nullptr), _parent(nullptr), _nullflag(obj._nullflag)
	{}

	key_type & operator=(const key_type & obj)
	{
		if (this == &obj)
			return (*this);
		_val = obj._val;
		_nullflag = obj._nullflag;
		return (*this);
	}

	bool operator!=(const key_type & obj)
	{
		return (_val != obj._val);
	}

	friend std::ostream& operator<<(std::ostream& f, const key_type<Key>& a)
	{
		f << a._val;
		return f;
	}

	~key_type() {}

	key_type * _left;
	key_type * _right;
	key_type * _parent;
	bool _nullflag;
	Key _val;
};


template<class Key> // Этот класс включает в себя ключи, которые включает в себя набор
class key_type
{
public:
	key_type() : _val(0), _left(nullptr), _right(nullptr), _parent(nullptr), _nullflag(false)
	{}

	key_type(Key val, key_type * left = nullptr, key_type * right = nullptr, key_type * parent = nullptr, bool nullflag = false)
		: _val(val), _left(left), _right(right), _parent(parent), _nullflag(nullflag)
	{}

	key_type(const key_type & obj) : _val(obj._val), _left(nullptr), _right(nullptr), _parent(nullptr), _nullflag(obj._nullflag)
	{}

	key_type & operator=(const key_type & obj)
	{
		if (this == &obj)
			return (*this);
		_val = obj._val;
		_nullflag = obj._nullflag;
		return (*this);
	}

	bool operator!=(const key_type & obj)
	{
		return (_val != obj._val);
	}

	friend std::ostream& operator<<(std::ostream& f, const key_type<Key>& a)
	{
		f << a._val;
		return f;
	}

	~key_type() {}

	key_type * _left;
	key_type * _right;
	key_type * _parent;
	bool _nullflag;
	Key _val;
};


	
	template<class Iterator>
	void insert(Iterator begin, Iterator end)
	{
		for (Iterator it = begin; it != end; it++)
			insert(it._pointer->_val);
	}

	void insert(const Key val)
	{
		if (_size == _maxSize)
			return;

		++_size;

		if (_root == nullptr)
		{
			_root = new key_type<Key>(val);
			return;
		}
		key_type<Key> * pi = _root;
		while (1)
		{
			if (val == pi->_val)
			{
				return;
				--_size;
			}

			if (!comp(val, pi->_val))
			{
				if (pi->_right == nullptr)
				{
					key_type<Key> * k = new key_type<Key>(val, nullptr, nullptr, pi);
					pi->_right = k;
					return;
				}
				pi = pi->_right;
			}

			if (comp(val, pi->_val))
			{
				if (pi->_left == nullptr)
				{
					key_type<Key> * k = new key_type<Key>(val, nullptr, nullptr, pi);
					pi->_left = k;
					return;
				}
				pi = pi->_left;
			}
		}

	}

	key_type<Key> * erase(const Key& val)
	{
		--_size;
		if (_size == 0)
		{
			_root = nullptr;
			return _root;
		}
		key_type<Key> * pi = _root;
		while (1)
		{
			if (val == pi->_val)
			{

				if (pi == _root)
				{
					if (pi->_left != nullptr)
					{
						_root = pi->_left;
						while (pi->_left->_right != nullptr)
							pi->_left = pi->_left->_right;
						pi->_left->_right = pi->_right;
						_root->_parent->_left = nullptr;
						_root->_parent = nullptr;
						return pi;
					}
					else
					{
						_root = pi->_right;
						while (pi->_right->_left != nullptr)
							pi->_right = pi->_right->_left;
						pi->_right->_left = pi->_left;
						_root->_parent = nullptr;
						return pi;
					}
				}


				if (!comp(pi->_val, pi->_parent->_val))
				{
					if (pi->_left == nullptr && pi->_right == nullptr)
					{
						pi = pi->_parent;
						pi->_parent->_right = nullptr;
						return pi;
					}

					if (pi->_left == nullptr && pi->_right != nullptr)
					{
						pi->_parent->_right = pi->_right;
						pi->_right->_parent = pi->_parent;
						return pi;
					}

					if (pi->_left != nullptr && pi->_right != nullptr)
					{
						pi->_parent->_right = pi->_right;
						pi->_right->_parent = pi->_parent;
						while (pi->_right->_left != nullptr)
							pi->_right = pi->_right->_left;
						pi->_right->_left = pi->_left;
						pi->_left->_parent = pi->_right->_left;
						return pi;
					}
				}

				if (comp(pi->_val, pi->_parent->_val))
				{

					if (pi->_left == nullptr && pi->_right == nullptr)
					{
						pi->_parent->_left = nullptr;
						return pi;
					}

					if (pi->_left != nullptr && pi->_right == nullptr)
					{
						pi->_parent->_left = pi->_left;
						pi->_left->_parent = pi->_parent;
						return pi;
					}
					if (pi->_left != nullptr && pi->_right != nullptr)
					{
						pi->_parent->_left = pi->_left;
						pi->_left->_parent = pi->_parent;
						while (pi->_left->_right != nullptr)
							pi->_left = pi->_left->_right;
						pi->_left->_right = pi->_right;
						pi->_right->_parent = pi->_left->_right;
						return pi;
					}
				}


			}
			if (comp(val, pi->_val))
			{
				if (pi->_left == nullptr)
					return nullptr;
				pi = pi->_left;
			}
			else
			{
				if (!comp(val, pi->_val))
				{
					if (pi->_right == nullptr && pi->_nullflag)
						return nullptr;
					pi = pi->_right;
				}
			}
		}
	}

	void print()
	{
		inOrderPrint(_root);
		std::cout << std::endl;
	}

	size_t size() const
	{
		return _size;
	}

	size_t count(const Key & val)
	{
		size_t _count = 0;
		int flag = 0;
		key_type<Key> * pi = _root;
		while (1)
		{
			if (val == pi->_val)
			{
				_count++;
				flag = 1;
			}

			if (val != pi->_val && flag == 1)
			{
				return _count;
			}

			if (!comp(val, pi->_val))
			{
				if (pi->_right == nullptr)
				{
					if (flag == 1)
						return _count;
					return 0;
				}
				pi = pi->_right;

			}

			if (comp(val, pi->_val))
			{
				if (pi->_left == nullptr)
				{
					if (flag == 1)
						return _count;
					return 0;
				}
				pi = pi->_left;

			}

		}
		return _count;
	}

	size_t max_size() const
	{
		return _maxSize;
	}

	void clear()
	{
		_size = 0;
		postOrderDelete(_root);
		_root = nullptr;
	}

	iterator find(const Key& val)
	{
		key_type<Key> * pi = _root;
		while (1)
		{
			if (val == pi->_val)
			{
				return iterator(pi);
			}

			if (!comp(val, pi->_val))
			{
				if (pi->_right == nullptr)
				{
					return end();
				}
				pi = pi->_right;
			}

			if (comp(val, pi->_val))
			{
				if (pi->_left == nullptr)
				{
					return end();
				}
				pi = pi->_left;
			}
		}
	}

	bool empty() const
	{
		return (_size == 0);
	}

	set & operator=(const set & obj)
	{
		if (this == &obj)
			return *this;
		if (!empty)
			clear();
		for (set::iterator it = obj.begin(); it != obj.end(); ++it)
			insert(it._pointer->_val);
		return *this;
	}

	void swap(set & obj)
	{
		set buf(*this);
		clear();
		for (set::iterator it = obj.begin(); it != obj.end(); ++it)
			insert(it._pointer->_val);
		obj.clear();
		for (set::iterator it = buf.begin(); it != buf.end(); ++it)
			obj.insert(it._pointer->_val);

	}

private:
	key_type<Key> * _root;
	size_t _size;
	size_t _maxSize = 214748364;
	Compare comp;

	// Функтор вокруг всего дерева 
	void inOrderPrint(key_type<Key> * root)
	{
		if (root)
		{
			if (!(root->_nullflag))
			{
				inOrderPrint(root->_left);
				std::cout << root->_val << " ";
				inOrderPrint(root->_right);
			}
		}
	}

	// Функтор вокруг всего дерева для удаления набора 
	void postOrderDelete(key_type<Key> * root)
	{
		if (root)
		{
			postOrderDelete(root->_left);
			postOrderDelete(root->_right);
			delete root;
		}
	}

};

template<class Key>
bool operator==(set<Key>& lhs, set<Key>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	set<Key>::iterator it1 = rhs.begin();
	for (set<Key>::iterator it = lhs.begin(); it != lhs.end(); ++it)
	{
		if (*it != *it1)
			return false;
		++it1;
	}
	return true;
}

template<class Key>
bool operator!=(set<Key>& lhs, set<Key>& rhs)
{
	return (!(lhs == rhs));
}

