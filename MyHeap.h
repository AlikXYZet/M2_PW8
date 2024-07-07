#pragma once
#include <functional>
#include <iostream>


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
	void bubble_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// Сортировка выбором
	void selection_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// Сортировка вставками
	void insertion_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// "Быстрая" сортировка
	void quick_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// Сортировка слиянием
	void merge_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// Сортировка Шелла
	void shell_sort(const std::function<const bool(T&, T&)>& b_predicate);

	// Сортировка кучей (Пирамидальная)
	void heap_sort(const std::function<const bool(T&, T&)>& b_predicate);
	//-----------------------------



	/* ---   Finding and checking   --- */

	// Поиск элемента по значению
	size_t find(T& in_elem);

	// Поиск элемента по условию
	size_t find_if(const std::function<const bool(T&)>& b_predicate);

	// Проверка на перестановку (все ли элементы in_V есть в текущем векторе)
	bool is_permutation(MyVector<T>& in_V);
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
	void recur_quick_sort(T* first, T* last, const std::function<const bool(T&, T&)>& b_predicate);

	// Рекурсивная функция для сортировки слиянием
	void recur_merge_sort(T* first, T* last, const std::function<const bool(T&, T&)>& b_predicate);

	// Рекурсивная функция для сортировки кучей
	void recur_heap_sort(T* node, T* last, const std::function<const bool(T&, T&)>& b_predicate);
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
	try
	{
		// Вывод ошибки, аналогичной для std::vector
		//_STL_VERIFY(in_pos < size(), "(MyVector) vector subscript out of range");
		if (in_pos >= size())
			throw;

		return *(begin + in_pos);
	}
	catch (...)
	{
		std::cout
			<< "ERROR: (MyVector) vector subscript out of range!\n"
			<< "( in_pos = " << in_pos
			<< ", size() = " << size()
			<< ", return: Last element"
			<< " )\n" << std::endl;

		return *(end - 1);
	}
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
inline void MyVector<T>::bubble_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	// Буфферные переменные
	size_t buf_size = size() - 1;
	T* end_1 = end - 1;

	for (size_t j = 0; j < buf_size; ++j)
		for (T* i = begin; i < end_1 - j; ++i)
			if (b_predicate(*i, *(i + 1)))
				castle(i, i + 1);
}

template<typename T>
inline void MyVector<T>::selection_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	// Буфферные указатели
	T* check;
	T* end_1 = end - 1;

	for (T* j = begin; j < end_1; ++j)
	{
		check = j;

		for (T* i = j + 1; i < end; ++i)
			if (b_predicate(*j, *i))
				check = i;

		if (check != j)
			castle(j, check);
	}
}

template<typename T>
inline void MyVector<T>::insertion_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	for (T* j = begin + 1; j < end; ++j)
		for (T* i = j; i != begin; --i)
			if (b_predicate(*(i - 1), *i))
				castle(i - 1, i);
}

template<typename T>
inline void MyVector<T>::quick_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	recur_quick_sort(begin, end - 1, b_predicate);
}

template<typename T>
inline void MyVector<T>::merge_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	recur_merge_sort(begin, end - 1, b_predicate);
}

template<typename T>
inline void MyVector<T>::shell_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	for (size_t step = size() / 2; step != 0; step /= 2)
		for (T* j = begin + step; j < end; ++j)
			for (T* i = j; i - begin >= step && b_predicate(*i, *(i - step)); i -= step)
				castle(i, i - step);
}

template<typename T>
inline void MyVector<T>::heap_sort(const std::function<const bool(T&, T&)>& b_predicate)
{
	// Проверка каждого узла, начиная от крайних к корневому
	// (с проверкой дочерних при изменении)
	for (size_t i = size() / 2; i > 0; --i)
	{
		// Определить элемент и переместить его в начало
		recur_heap_sort(begin + i - 1, end - 1, b_predicate);
	}

	// Буфферный указатель
	T* begin_i_1;

	// Проверка корневого узла с уменьшением размера проверяемой зоны
	// (с проверкой дочерних при изменении)
	for (size_t i = size(); i > 0; --i)
	{
		begin_i_1 = begin + i - 1;
		// Перенос элемента уже определённого элемента в крайнюю позицию
		castle(begin, begin_i_1);

		// Определить элемент и переместить его в начало
		recur_heap_sort(begin, begin_i_1, b_predicate);
	}
}
//---------------------------------------------------------------------------------------



/* ---   Finding and checking   --- */

template<typename T>
inline size_t MyVector<T>::find(T& in_elem)
{
	for (T* i = begin; i < end; ++i)
		// Сравнение содержимого в ячейках памяти
		if (!memcmp(&in_elem, i, sizeof(T)))
			return i - begin;

	return size();
}

template<typename T>
inline size_t MyVector<T>::find_if(const std::function<const bool(T&)>& b_predicate)
{
	for (T* i = begin; i < end; ++i)
		if (b_predicate(*i))
			return i - begin;

	return size();
}

template<typename T>
inline bool MyVector<T>::is_permutation(MyVector<T>& in_V)
{
	bool check = true;

	if (in_V.size() <= size())
		for (T* i = in_V.begin; i < in_V.end; ++i)
			if (find(*i) == size())
				check = false;

	return check;
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
inline void MyVector<T>::recur_quick_sort(T* first, T* last, const std::function<const bool(T&, T&)>& b_predicate)
{
	if (first < last)
	{
		// Буфферные переменные
		T buf;
		T* pivot = last;
		T* j = first;

		while (j < pivot)
			if (b_predicate(*j, *pivot))
			{
				buf = *j;

				for (T* i = j; i < pivot; ++i)
					*i = *(i + 1);

				*pivot = buf;
				--pivot;
			}
			else
				++j;

		recur_quick_sort(first, pivot - 1, b_predicate);
		recur_quick_sort(pivot + 1, last, b_predicate);
	}
}

template<typename T>
inline void MyVector<T>::recur_merge_sort(T* first, T* last, const std::function<const bool(T&, T&)>& b_predicate)
{
	if (first < last)
	{
		// Буфферные переменные
		T* mid = first + (last - first) / 2;
		T* mid_1 = mid + 1;
		T* j_1;
		T buf;

		// Сортировка половин данного куска
		recur_merge_sort(first, mid, b_predicate);
		recur_merge_sort(mid + 1, last, b_predicate);

		// Сортировка куска
		for (T* j = mid_1; j <= last; ++j)
		{
			j_1 = j - 1;

			for (T* i = first; i <= j_1; ++i)
				if (b_predicate(*j, *i))
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

template<typename T>
inline void MyVector<T>::recur_heap_sort(T* node, T* last, const std::function<const bool(T&, T&)>& b_predicate)
{
	// Искомый (выявленный) элемент
	T* ident = node;

	// Левая ветвь узла
	T* l = begin + (2 * (node - begin)) + 1;

	// Найти элемент по указанному условию
	// Если нет левой ветви, то и нет правой
	if (l < last)
	{
		// Проверка левого
		if (b_predicate(*l, *ident))
			ident = l;

		// Правая ветвь узла
		T* r = l + 1;

		// Если есть правая ветвь
		if (r < last)
			// Проверка правого
			if (b_predicate(*r, *ident))
				ident = r;
	}

	// Если выявленный элемент не узел
	if (ident != node)
	{
		// Рокировка узла с выявленным элементов ветви
		castle(node, ident);

		// Рекурсия для изменённой ветви
		recur_heap_sort(ident, last, b_predicate);
	}
}
//---------------------------------------------------------------------------------------