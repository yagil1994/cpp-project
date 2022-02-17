#pragma once
#include <iostream>
using namespace std;
template <class T>
class DynamicArray
{
protected:
	T* _arr;
	int _logicalSize;
	int _physicalSize;

	void resize()
	{
		_physicalSize *= 2;
		T* temp = nullptr;
		try{
			 temp = new T[_physicalSize];
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
			exit(1);
		}
		for (int i = 0; i < _logicalSize; i++)
			temp[i] = _arr[i];

		delete[] _arr;
		_arr = temp;
	}


	void resizeToAspecificPhy_Size(int newCapacity)
	{
		if(newCapacity < 0)
			throw invalid_argument("Invalid newCapacity");

		if (newCapacity > capacity())
		{
			_physicalSize = newCapacity;
			T* temp = nullptr;
			try {
				 temp = new T[newCapacity];
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
				exit(1);
			}
			for (int i = 0; i < _logicalSize; i++)
				temp[i] = _arr[i];

			delete[] _arr;
			_arr = temp;
		}
	}
public:
	DynamicArray(int size = 2) : _logicalSize(0), _physicalSize(size), _arr(new T[size])
	{	//if alloc for _arr(new T[size]) will fail the one who called for this ctor will catch the bad alloc throw! 

		if(size < 0)
			throw invalid_argument("Invalid size");
	}

	DynamicArray(const DynamicArray& other) : _arr(nullptr) {
		*this = other;
	}
	virtual ~DynamicArray() {
		delete[] _arr;
	}

	const DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			_logicalSize = other._logicalSize;
			_physicalSize = other._physicalSize;
			delete[] _arr;
			try {
				_arr = new T[_physicalSize];
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
			for (int i = 0; i < _logicalSize; i++)
				_arr[i] = other._arr[i];
		}
		return *this;
	}

	const T& operator[](int i) const 
	{ 
		/*if (i < 0 || i >= _logicalSize)
			throw out_of_range("invalid array index");*/
		return _arr[i];
	}
	T& operator[](int i) 
	{ 
		/*if (i < 0 || i >= _logicalSize)
			throw out_of_range("invalid array index");*/
		return _arr[i]; 
	}

	void push_back(const T& value) {
		if (_logicalSize == _physicalSize)
			resize();
		_arr[_logicalSize++] = value;
	}

	const T& front()    const { return _arr[0]; }
	int      size()     const { return _logicalSize; }
	int      capacity() const { return _physicalSize; }
	bool     empty()    const { return _logicalSize == 0; }
	void     clear() { _logicalSize = 0; }

	// standard STL iterator implementation:
	// (no duplication for const)
	template <bool is_const>
	class base_iterator
	{
	public:
		using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = std::conditional_t<is_const, const T, T>;
		using pointer = value_type*;
		using reference = value_type&;

		base_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}

		// we want to use the default constructor
		base_iterator(const base_iterator&) = default;

		// and the default assignment operator
		constexpr base_iterator& operator=(const base_iterator&) = default;

		virtual ~base_iterator(){};
		// we want to allow construction of const_iterator from iterator
		friend class base_iterator<true>;
		template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
		base_iterator(const base_iterator<false>& other) : _da(other._da), _i(other._i) {}

		// comparison with another iterator
		bool operator==(const base_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const base_iterator& other) const {
			return !(*this == other);
		}
		bool operator<(const base_iterator& other)
		{
			return (_i < other._i);
		}
		bool operator<=(const base_iterator& other)
		{
			return (_i <= other._i);
		}
		bool operator>(const base_iterator& other)
		{
			return (_i > other._i);
		}
		bool operator>=(const base_iterator& other)
		{
			return (_i >= other._i);
		}
		// smart-pointer iterator methods
		reference operator*() const {
			return _da->_arr[_i];
		}
		pointer operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods

		 base_iterator& operator++() {
			++_i;
			return *this;
		}
		 base_iterator operator++(int) {
			base_iterator temp(*this);
			++_i;
			return temp;
		}
		 base_iterator& operator--() {
			--_i;
			return *this;
		}
		 base_iterator operator--(int) {
			base_iterator temp(*this);
			--_i;
			return temp;
		}
		 base_iterator operator+(int x)const
		{
			base_iterator itr = *this;
			itr._i += x;
			return itr;
		}
		 difference_type operator+(const base_iterator& other)
		{
			return(_i + other._i);
		}
		 base_iterator operator-(int x)const
		{
			base_iterator itr = *this;
			itr._i -= x;
				return itr;
		}
		  int operator-(const base_iterator& other)const
		{
			 return (this->_i - other._i);
		}

	private:
		ds_type* _da;
		int	_i;
	};

	template <bool is_const>
	class base_reverse_iterator
	{
		private:
		DynamicArray* _da;
		int	_i;
	public:
		using ds_type = std::conditional_t<is_const, const DynamicArray, DynamicArray>;
		using iterator_category = std::bidirectional_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = std::conditional_t<is_const, const T, T>;
		using pointer = value_type*;
		using reference = value_type&;

		base_reverse_iterator(ds_type& arr, int i) : _da(&arr), _i(i) {}
		base_reverse_iterator(const base_reverse_iterator&) = default;

		constexpr base_reverse_iterator& operator=(const base_reverse_iterator&) = default;
		~base_reverse_iterator() {};
		friend class base_reverse_iterator<true>;
		template <bool _is_const = is_const, class = std::enable_if_t<_is_const>>
		base_reverse_iterator(const base_reverse_iterator<false>& other) : _da(other._da), _i(other._i) {}

		// comparison with another iterator
		bool operator==(const base_reverse_iterator& other) const {
			return (_da == other._da) && (_i == other._i);
		}
		bool operator!=(const base_reverse_iterator& other) const {
			return !(*this == other);
		}
		// smart-pointer iterator methods
		reference operator*() const {
			return _da->_arr[_i];
		}
		pointer operator->() {
			return &_da->_arr[_i];
		}

		// increment-decrement iterator methods
		base_reverse_iterator& operator++() {
			--_i;
			return *this;
		}
		base_reverse_iterator operator++(int){
			base_reverse_iterator temp(*this);
			--_i;
			return temp;
		}
		base_reverse_iterator& operator--() {
			++_i;
			return *this;
		}
		base_reverse_iterator operator--(int) {
			base_reverse_iterator temp(*this);
			++_i;
			return temp;
		}
	}; 

	using iterator = base_iterator<false>;
	using const_iterator = base_iterator<true>;

	using reverse_iterator_iterator = base_reverse_iterator<false>;
	using const_reverse_iterator = base_reverse_iterator<true>;


	void insert(const iterator& pos, const T& val) {
		if (_logicalSize == _physicalSize)
			resize();

		iterator itrEnd = end();
		iterator itrCurrent = itrEnd, itrPrev = --itrEnd;
		while (itrCurrent != pos)
		{
			*itrCurrent = *itrPrev;
			itrCurrent = itrPrev--;
		}

		iterator p = pos;
		*p = val;
		++_logicalSize;
	}

	 iterator erase(const iterator& itr)
	{
		if (itr._i < 0 || itr.i >= _logicalSize)
			throw out_of_range("iterator out of range");
		const iterator tmp = itr;
		tmp++;
		return erase(itr,tmp);
	}

	 iterator erase(const iterator& first, const iterator& last)
	{
		if (first._i < 0 || first.i >= _logicalSize)
			throw out_of_range("iterator out of range");
		if (last._i < 0 || last.i >= _logicalSize)
			throw out_of_range("iterator out of range");		
		if (first._i > last._i)
			throw out_of_range("iterator out of range");
		 int delta = last._i - first._i;
		for (auto firstitr = first, lastitr = last; lastitr != end(); ++lastitr, ++firstitr)
			*firstitr = *(lastitr);
		_logicalSize -= delta;
		return first;
	}

	iterator begin()
	{
		return iterator(*this, 0);
	}
	iterator end()
	{
		return iterator(*this, _logicalSize);
	}
	const_iterator cbegin() const
	{
		return const_iterator(*this, 0);
	}
	const_iterator cend() const
	{
		return const_iterator(*this, _logicalSize);
	}
	
	reverse_iterator_iterator rbegin()
	{
		return reverse_iterator_iterator(*this, _logicalSize);
	}

	reverse_iterator_iterator rend()
	{
		return reverse_iterator_iterator(*this, 0);
	}

	const_reverse_iterator crbegin()const
	{
		return const_reverse_iterator(*this, _logicalSize);
	}

	const_reverse_iterator crend()const
	{
		return const_reverse_iterator(*this, 0);
	}

	void print() const
	{
		for (int i = 0; i < _logicalSize; i++)
			cout << _arr[i] << " ";
		cout << endl;
	}

};

