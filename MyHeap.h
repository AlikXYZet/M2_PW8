#pragma once



template <typename T>
class MyVector
{
public:
	using value_type = T;

	MyVector(const size_t in_capacity = 8)
	{
		set_size(in_capacity);
		end = begin;
		end_cap = begin + in_capacity;
	};

	~MyVector()
	{
		free(begin);
		begin = end = end_cap = nullptr;
	}

	/* ---   Elements   --- */
	void push_back(const T& data);
	void pop_back();
	void insert();
	T& front();
	T& back();
	//-----------------------------


	/* ---   Size   --- */
	size_t size();
	size_t capacity();
	void reserve(size_t new_size);
	void shrink_to_fit();
	//-----------------------------



//private:
	// Указатели вектора:
	T* begin = nullptr;		// Первый элемент
	T* end = nullptr;		// Следующий за последним элементом
	T* end_cap = nullptr;	// Следующий за последним доступным участком памяти

private:
	void set_size(const size_t new_size)
	{
		begin = (T*)realloc(begin, sizeof(T) * new_size);
	}
};
//---------------------------------------------------------------------------------------



/* ---   Elements   --- */

template <typename T>
void MyVector<T>::push_back(const T& data)
{
	if (end == end_cap)
	{
		// Буфферная переменная:
		size_t cur_cap = size();

		set_size(cur_cap * 2);

		end = begin + cur_cap;
		end_cap = begin + cur_cap * 2;
	}

	if (begin)
	{
		*end = data;
		++end;
	}
}

template <typename T>
void MyVector<T>::pop_back()
{

}

template <typename T>
void MyVector<T>::insert()
{

}

template<typename T>
inline T& MyVector<T>::front()
{
	return begin;
}

template<typename T>
inline T& MyVector<T>::back()
{
	return end - 1;
}
//---------------------------------------------------------------------------------------



/* ---   Size   --- */

template <typename T>
size_t MyVector<T>::size()
{
	return end - begin;
}

template <typename T>
size_t MyVector<T>::capacity()
{
	return end_cap - begin;
}

template <typename T>
void MyVector<T>::reserve(size_t new_size)
{
	if (new_size > size())
		set_size(new_size);
}

template <typename T>
void MyVector<T>::shrink_to_fit()
{
	set_size(size());
}
//---------------------------------------------------------------------------------------