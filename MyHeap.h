#pragma once



template <typename T>
class MyVector
{
public:
	using value_type = T;

	MyVector(const int alloc = 8)
	{
		begin = end = (T*)malloc(sizeof(T) * alloc);
		end_cap = begin + alloc;
	};

	~MyVector()
	{
		free(begin);
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
	void resize(size_t new_size);
	void shrink_to_fit();
	//-----------------------------



//private:
	// Указатели вектора:
	T* begin = nullptr;		// Первый элемент
	T* end = nullptr;		// Следующий за последним элементом
	T* end_cap = nullptr;	// Следующий за последним доступным участком памяти
};
//---------------------------------------------------------------------------------------



/* ---   Elements   --- */

template <typename T>
void MyVector<T>::push_back(const T& data)
{

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
void MyVector<T>::resize(size_t new_size)
{

}

template <typename T>
void MyVector<T>::shrink_to_fit()
{

}
//---------------------------------------------------------------------------------------