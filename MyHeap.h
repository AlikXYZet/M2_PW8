#pragma once
#include <functional>


template <typename T>
class MyVector
{
public:
	using value_type = T;

	MyVector(const size_t& in_capacity = 8)
	{
		//begin = end = new T;
		set_cap(in_capacity);
	}

	MyVector(const MyVector& in_MyV)
	{
		*this = in_MyV;
	}

	~MyVector()
	{
		free(begin);
		begin = end = end_cap = nullptr;
	}



	/* ---   Elements   --- */

	// Добавить элемент в конец
	void push_back(const T& data);

	// Удалить последний элемент
	void pop_back();

	// Добавить элемент в указанное место
	size_t insert(const size_t& in_pos, const T& data);

	// Удалить элемент в указанном месте
	void erase(const size_t& in_pos);

	// Получить данные первого элемента
	T& front() const;

	// Получить данные последнего элемента
	T& back() const;
	//-----------------------------



	/* ---   Size   --- */

	// Получение размера
	size_t size() const;

	// Получение ёмкости
	size_t capacity() const;

	// Задать минимальную ёмкость
	void reserve(const size_t& new_size);

	// Убрать излишнюю ёмкость
	void shrink_to_fit();
	//-----------------------------



	/* ---   Operators   --- */

	// Получение данных указанного элемента
	T& operator[](const size_t& in_pos) const;

	// Оператор копирования контейнера
	MyVector<T>& operator=(const MyVector<T>& in_MyV);
	//-----------------------------



	/* ---   Sorting   --- */

	// Пузырьковая сортировка
	void bubble_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка выбором
	void selection_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка вставками
	void insertion_sort(const std::function<const bool(T&, T&)>& f);
	//-----------------------------



//private:
	// Указатели вектора:
	T* begin = nullptr;		// Первый элемент
	T* end = nullptr;		// Следующий за последним элементом
	T* end_cap = nullptr;	// Следующий за последним доступным участком памяти

private:
	// Изменение ёмкости
	const bool set_cap(const size_t& new_size)
	{
		if (T* rebegin = (T*)realloc(begin, sizeof(T) * new_size))
		{
			if (begin != rebegin)
			{
				// Буфферная переменная
				size_t cur_size = size();

				begin = rebegin;
				end = begin + cur_size;
			}
			end_cap = begin + new_size;
			return true;
		}
		return false;
	}

	// Рокировка двух элементов по указателю
	const bool castle(T* first, T* second)
	{
		if (first != second)
		{
			// Буфферная переменная
			T* buf = new T;

			*buf = *first;
			*first = *second;
			*second = *buf;

			return true;
		}
		return false;
	}
};
//---------------------------------------------------------------------------------------



/* ---   Elements   --- */

template <typename T>
void MyVector<T>::push_back(const T& data)
{
	if (end == end_cap)
		set_cap(capacity() * 2);

	if (begin) {
		*end = data;
		++end;
	}
}

template <typename T>
void MyVector<T>::pop_back()
{
	if (end != begin)
		--end;
}

template <typename T>
size_t MyVector<T>::insert(const size_t& in_pos, const T& data)
{
	// Проверка диапазона массива
	if (in_pos <= size())
	{
		// Буфферная переменная
		T* new_pos = begin + in_pos;

		// Дублирование последнего элемента в конец 
		push_back(*(end - 1));

		// Смещение текущих данных (кроме нового последнего элемента-дубликата)
		for (T* i = begin + size() - 2; i > new_pos; --i)
			*i = *(i - 1);

		// Запись новых данных в выбранную позицию
		*new_pos = data;

		return in_pos;
	}
	return 0;
}

template<typename T>
void MyVector<T>::erase(const size_t& in_pos)
{
	// Проверка диапазона массива
	if (in_pos <= size())
	{
		for (T* i = begin + in_pos + 1; i < end; ++i)
			*(i - 1) = *i;

		--end;
	}
}

template<typename T>
T& MyVector<T>::front() const
{
	return *begin;
}

template<typename T>
T& MyVector<T>::back() const
{
	return *(end - 1);
}
//---------------------------------------------------------------------------------------



/* ---   Size   --- */

template <typename T>
size_t MyVector<T>::size() const
{
	return end - begin;
}

template <typename T>
size_t MyVector<T>::capacity() const
{
	return end_cap - begin;
}

template <typename T>
void MyVector<T>::reserve(const size_t& in_cap)
{
	if (in_cap > size())
		set_cap(in_cap);
}

template <typename T>
void MyVector<T>::shrink_to_fit()
{
	set_cap(size());
}
//---------------------------------------------------------------------------------------



/* ---   Operators   --- */

template<typename T>
T& MyVector<T>::operator[](const size_t& in_pos) const
{
	// Вывод ошибки, аналогичной для std::vector
	_STL_VERIFY(in_pos < size(), "(MyVector) vector subscript out of range");

	return *(begin + in_pos);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& in_MyV)
{
	if (begin != in_MyV.begin)
	{
		end = begin;
		this->reserve(in_MyV.capacity());

		for (T* i = in_MyV.begin; i < in_MyV.end; ++i)
			this->push_back(*i);
	}
	return *this;
}
//---------------------------------------------------------------------------------------



/* ---   Sorting   --- */

template<typename T>
void MyVector<T>::bubble_sort(const std::function<const bool(T&, T&)>& f)
{
	if (size() > 1)
	{
		// Буфферные переменные
		T* check_i;
		size_t buf_size = size() - 1;

		for (size_t j = 0; j < buf_size; ++j)
			for (size_t i = 0; i < buf_size - j; ++i)
			{
				check_i = begin + i;

				if (f(*(check_i), *(check_i + 1)))
					castle(check_i, check_i + 1);
			}
	}
}

template<typename T>
void MyVector<T>::selection_sort(const std::function<const bool(T&, T&)>& f)
{
	if (size() > 1)
	{
		// Буфферные переменные
		T* check_j, * check_i;
		size_t buf_size = size();

		for (size_t j = 0; j < buf_size - 1; ++j)
		{
			check_j = begin + j;

			for (size_t i = j + 1; i < buf_size; ++i)
			{
				check_i = begin + i;

				if (f(*(check_j), *(check_i)))
					check_j = check_i;
			}

			castle(begin + j, check_j);

		}
	}
}

template<typename T>
void MyVector<T>::insertion_sort(const std::function<const bool(T&, T&)>& f)
{
	if (size() > 1)
	{
		// Буфферные переменные
		T* check_i;
		size_t buf_size = size();

		for (size_t j = 1; j < buf_size; ++j)
			for (size_t i = j; i != 0; --i)
			{
				check_i = begin + i;

				if (f(*(check_i - 1), *(check_i)))
					castle(check_i - 1, check_i);
			}
	}
}
//---------------------------------------------------------------------------------------