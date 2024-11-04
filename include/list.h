#include <iostream>

using namespace std;

template <typename TELEM>
class List {
protected:
	struct Node {
		Node* next;
		TELEM value;
		Node(TELEM value, Node* next);
	};

	Node* first = nullptr;
public:


	/* --- Итератор --- */
	class Iterator {
	public:
		Node* curr = nullptr;

		// Конструтор
		Iterator(Node* nd)
		{
			curr = nd;
		}

		// Арифметические операции
		Iterator& operator++()
		{
			if (!curr) throw out_of_range("Trying to acces data out of range");
			curr = curr->next;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator res = *this;
			if (!curr) throw out_of_range("Trying to acces data out of range");
			curr = curr->next;
			return res;
		}

		Iterator operator+(int step)
		{
			Iterator res(curr);

			for (int i = 0; i < step; i++) {
				if (!res.curr) throw out_of_range("Trying to acces data out of range");
				res.curr = res.curr->next;
			}

			return res;
		}

		Iterator& operator+=(int step) 
		{
			for (int i = 0; i < step; i++) {
				if (!curr) throw out_of_range("Trying to acces data out of range");

				curr = curr->next;
			}

			return *this;
		}

		// Сравнение
		bool operator!=(const Iterator& it) 
		{
			return !(curr == it.curr);
		}

		bool operator==(const Iterator& it) 
		{
			return curr == it.curr;
		}

		// Разыменование
		TELEM& operator*() 
		{ 
			if (!curr) throw out_of_range("Trying to acces data out of range");
			return curr->value; 
		}


	};


	/* --- Конструкторы и подобное --- */


	// Конструктор
	List(int n = 0) {
		if (n < 0) throw out_of_range("Incorrect List length");
		while (n--) {
			Node* temp = new Node(0, first);
			first = temp;
		}
	}

	// Конструктор копирования
	List(const List& l) {
		if (l.first == nullptr) {
			first = nullptr;
		}
		else {
			Node* curr1 = l.first;
			first = new Node(curr1->value, nullptr);
			Node* curr2 = first;

			while (curr1->next != nullptr) {
				curr1 = curr1->next;
				curr2->next = new Node(curr1->value, nullptr);
				curr2 = curr2->next;
			}
		}
	}

	// Очиститель
	void clear(Node* first) {
		Node* curr;
		while (first != nullptr) {
			curr = first->next;
			delete first;
			first = curr;
		}
	}

	// Деструктор
	~List() {
		clear(first);
	}

	// Оператор присваивания
	List& operator=(const List& l) {
		if (this != &l) {
			// Очищаем имеющуюся память
			clear(first);
			
			// А дальше копия конструктора копирования
			if (l.first != nullptr) {
				Node* curr1 = l.first;
				Node* curr2 = new Node(curr1->value, nullptr);
				first = curr2;
				while (!curr->next) {
					Node* next1 = curr1->next;
					curr2->next = new Node(next1->value, nullptr);
					curr2 = curr2->next;
					curr1 = curr1->next;
				}
			}
		}

		return *this;
	}

	// Конструктор перемещения
	List (List&& l) {
		this->first = l.first;
		l.first = nullptr;
	}

	// Оператор перемещения 
	List& operator=(List&& l) {
		if (this != &l) {
			clear(first);

			this->first = l.first;
			l.first = nullptr;
		}

		return *this;
	}
	
	
	/* --- Методы всякие --- */


	// Вывод
	friend ostream& operator<<(ostream& ostr, const List& bf)  
	{
		for (Node* curr = bf.first; curr; curr = curr->next) {
			ostr << curr->value;
		}
		return ostr;
	}

	// Узнать размер
	size_t size() const {   
		Node* curr = first;
		size_t sz = 0;
		while (curr) {
			sz++;
			curr = curr->next;
		}
		return sz;
	}

	// Проверка на пустоту
	bool empty() {
		return first == nullptr;
	}

	// Скобочки
	Node& operator[](int ind) { 
		Node* curr = first;

		if (ind < 0 || curr == nullptr) {
			throw out_of_range("Index is incorrect");
		}

		for (int i = 0; i < ind; i++) {
			curr = curr->next;
		}
		return *curr;
	}

	// Доступ к 1 элементу
	Node* front() {
		return first;
	}

	// Вставка
	Node* insert_after(TELEM data, Node* prev) {    
		Node* tmp = new Node(data, nullptr);
		tmp->next = prev->next;
		prev->next = tmp;
		return prev->next;
	}

	Node* insert_front(TELEM data) {
		return(first = new Node(data, first));
	}

	// Удаление
	Node* erase_after(Node* prev) {
		Node* tmp = prev->next;
		if (tmp) {
			prev->next = prev->next->next;
			delete tmp;
		}
		return prev->next;
	}

	Node* erase_front() {
		if (first) {
			Node* prevFirst = first;
			first = first->next;
			delete prevFirst;
		}
		return first;
	}

	// Поиск
	Node* find(TELEM key) {
		Node* curr = first;
		while (curr && (curr->value != key)) {
			curr = curr->next;
		}
		return curr;
	}

	// Получение итератора 
	Iterator begin() {
		return Iterator(first);
	}

	Iterator end() {
		return Iterator(nullptr);
	}
};

template <typename TELEM>
List<TELEM>::Node::Node(TELEM value, Node* next) : value(value), next(next){
}
