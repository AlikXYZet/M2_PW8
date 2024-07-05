﻿#pragma once
#include <functional>


template <typename T>
class MyVector
{
public:
	using value_type = T;

	MyVector(const size_t& in_capacity = 8)
	{
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

	// Дружественная ф-ция для вывода на консоль
	friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& in_MyV)
	{
		for (size_t i = 0; i < in_MyV.size(); ++i)
			out << in_MyV[i];

		out << std::endl;

		return out;
	}
	//-----------------------------



	/* ---   Sorting   --- */

	// Пузырьковая сортировка
	void bubble_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка выбором
	void selection_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка вставками
	void insertion_sort(const std::function<const bool(T&, T&)>& f);

	// "Быстрая" сортировка
	void quick_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка слиянием
	void merge_sort(const std::function<const bool(T&, T&)>& f);

	// Сортировка Шелла
	void shell_sort(const std::function<const bool(T&, T&)>& f);

	/* ---   Sorting (не реализовано)   --- */

	// Сортировка кучей (Пирамидальная)
	void heap_sort(const std::function<const bool(T&, T&)>& f);
	//-----------------------------



//private:
	// Указатели вектора:
	T* begin = nullptr;		// Первый элемент
	T* end = nullptr;		// Следующий за последним элементом
	T* end_cap = nullptr;	// Следующий за последним доступным участком памяти

private:

	/* ---   Private   --- */

	// Изменение ёмкости
	const bool set_cap(const size_t& new_size);

	// Поменять местами два элемента по указателю
	void castle(T* first, T* second);
	//-----------------------------



	/* ---   Recursive   --- */

	// Рекурсивная функция для "быстрой" сортировки
	void recur_quick_sort(T* first, T* last, const std::function<const bool(T&, T&)>& f);

	// Рекурсивная функция для сортировки слиянием
	void recur_merge_sort(T* first, T* last, const std::function<const bool(T&, T&)>& f);
	//-----------------------------
};
//---------------------------------------------------------------------------------------



/* ---   Elements   --- */

template <typename T>
inline void MyVector<T>::push_back(const T& data)
{
	if (end == end_cap)
		set_cap(capacity() * 2);

	if (begin) {
		*end = data;
		++end;
	}
}

template <typename T>
inline void MyVector<T>::pop_back()
{
	if (end != begin)
		--end;
}

template <typename T>
inline size_t MyVector<T>::insert(const size_t& in_pos, const T& data)
{
	// Проверка диапазона массива
	if (in_pos <= size())
	{
		// Дублирование последнего элемента в конец 
		push_back(*(end - 1));

		// Буфферная переменная
		T* new_pos = begin + in_pos;

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
inline void MyVector<T>::erase(const size_t& in_pos)
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
inline T& MyVector<T>::front() const
{
	return *begin;
}

template<typename T>
inline T& MyVector<T>::back() const
{
	return *(end - 1);
}
//---------------------------------------------------------------------------------------



/* ---   Size   --- */

template <typename T>
inline size_t MyVector<T>::size() const
{
	return end - begin;
}

template <typename T>
inline size_t MyVector<T>::capacity() const
{
	return end_cap - begin;
}

template <typename T>
inline void MyVector<T>::reserve(const size_t& in_cap)
{
	if (in_cap > size())
		set_cap(in_cap);
}

template <typename T>
inline void MyVector<T>::shrink_to_fit()
{
	set_cap(size());
}
//---------------------------------------------------------------------------------------



/* ---   Operators   --- */

template<typename T>
inline T& MyVector<T>::operator[](const size_t& in_pos) const
{
	// Вывод ошибки, аналогичной для std::vector
	_STL_VERIFY(in_pos < size(), "(MyVector) vector subscript out of range");

	return *(begin + in_pos);
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& in_MyV)
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
inline void MyVector<T>::bubble_sort(const std::function<const bool(T&, T&)>& f)
{
	// Буфферные переменные
	size_t buf_size = size() - 1;
	T* end_1 = end - 1;

	for (size_t j = 0; j < buf_size; ++j)
		for (T* i = begin; i < end_1 - j; ++i)
			if (f(*i, *(i + 1)))
				castle(i, i + 1);
}

template<typename T>
inline void MyVector<T>::selection_sort(const std::function<const bool(T&, T&)>& f)
{
	// Буфферные указатели
	T* check;
	T* end_1 = end - 1;

	for (T* j = begin; j < end_1; ++j)
	{
		check = j;

		for (T* i = j + 1; i < end; ++i)
			if (f(*j, *i))
				check = i;

		if (check != j)
			castle(j, check);
	}
}

template<typename T>
inline void MyVector<T>::insertion_sort(const std::function<const bool(T&, T&)>& f)
{
	for (T* j = begin + 1; j < end; ++j)
		for (T* i = j; i != begin; --i)
			if (f(*(i - 1), *i))
				castle(i - 1, i);
}

template<typename T>
inline void MyVector<T>::quick_sort(const std::function<const bool(T&, T&)>& f)
{
	recur_quick_sort(begin, end - 1, f);
}

template<typename T>
inline void MyVector<T>::merge_sort(const std::function<const bool(T&, T&)>& f)
{
	recur_merge_sort(begin, end - 1, f);
}

template<typename T>
inline void MyVector<T>::shell_sort(const std::function<const bool(T&, T&)>& f)
{
	for (size_t step = size() / 2; step != 0; step /= 2)
		for (T* j = begin + step; j < end; ++j)
			for (T* i = j; i - begin >= step && f(*i, *(i - step)); i -= step)
				castle(i, i - step);
}

template<typename T>
inline void MyVector<T>::heap_sort(const std::function<const bool(T&, T&)>& f)
{

}
//---------------------------------------------------------------------------------------



/* ---   Private   --- */

template<typename T>
inline const bool MyVector<T>::set_cap(const size_t& new_size)
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

template<typename T>
inline void MyVector<T>::castle(T* first, T* second)
{
	// Буфферная переменная
	T* buf = new T;

	*buf = *first;
	*first = *second;
	*second = *buf;
}
//---------------------------------------------------------------------------------------



/* ---   Recursive   --- */

template<typename T>
inline void MyVector<T>::recur_quick_sort(T* first, T* last, const std::function<const bool(T&, T&)>& f)
{
	if (first < last)
	{
		// Буфферные переменные
		T buf;
		T* pivot = last;
		T* j = first;

		while (j < pivot)
			if (f(*j, *pivot))
			{
				buf = *j;

				for (T* i = j; i < pivot; ++i)
					*i = *(i + 1);

				*pivot = buf;
				--pivot;
			}
			else
				++j;

		recur_quick_sort(first, pivot - 1, f);
		recur_quick_sort(pivot + 1, last, f);
	}
}

template<typename T>
inline void MyVector<T>::recur_merge_sort(T* first, T* last, const std::function<const bool(T&, T&)>& f)
{
	if (first < last)
	{
		// Буфферные переменные
		T* mid = first + (last - first) / 2;
		T* mid_1 = mid + 1;
		T* j_1;
		T buf;

		// Сортировка половин данного куска
		recur_merge_sort(first, mid, f);
		recur_merge_sort(mid + 1, last, f);

		// Сортировка куска
		for (T* j = mid_1; j <= last; ++j)
		{
			j_1 = j - 1;

			for (T* i = first; i <= j_1; ++i)
				if (f(*j, *i))
				{
					buf = *j;

					for (T* k = j; k > i; --k)
					{
						*k = *(k - 1);
					}

					*i = buf;
				}
		}
	}
}
//---------------------------------------------------------------------------------------