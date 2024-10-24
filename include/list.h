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


	/* --- ������������ � �������� --- */


	// �����������
	List(int n = 0) {
		if (n < 0) throw out_of_range("Incorrect List length");
		while (n--) {
			Node* temp = new Node(0, first);
			first = temp;
		}
	}

	// ����������� �����������
	List(const List& l) {
		if (l.first == nullptr) {
			first = nullptr;
		}
		else {
			/*
			Node* curr1 = l.first;
			Node* curr2 = new Node(curr1->value, nullptr);
			first = curr2;
			while (!curr1->next) {
				Node* next1 = curr1->next;
				curr2->next = new Node(next1->value, nullptr);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
			*/
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

	// ����������
	void clear(Node* first) {
		Node* curr;
		while (first != nullptr) {
			curr = first->next;
			delete first;
			first = curr;
		}
	}

	// ����������
	~List() {
		clear(first);
	}

	// �������� ������������
	List& operator=(const List& l) {
		if (this != &l) {
			// ������� ��������� ������
			clear(first);
			
			// � ������ ����� ������������ �����������
			if (l->first != nullptr) {
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

	// ����������� �����������
	List (List&& l) {
		this->first = l.first;
		l.first = nullptr;
	}

	// �������� ����������� 
	List& operator=(List&& l) {
		if (this != &l) {
			clear(first);

			this->first = l.first;
			l.first = nullptr;
		}

		return *this;
	}
	
	
	/* --- ������ ������ --- */


	// �����
	friend ostream& operator<<(ostream& ostr, const List& bf)  
	{
		for (Node* curr = bf.first; curr; curr = curr->next) {
			ostr << curr->value;
		}
		return ostr;
	}

	// ������ ������
	size_t size() const {   
		Node* curr = first;
		size_t sz = 0;
		while (curr) {
			sz++;
			curr = curr->next;
		}
		return sz;
	}

	// �������� �� �������
	bool empty() {
		return first == nullptr;
	}

	// ��������
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

	// ������ � 1 ��������
	Node* front() {
		return first;
	}

	// �������
	Node* insert_after(TELEM data, Node* prev) {    
		Node* tmp = new Node(data, nullptr);
		tmp->next = prev->next;
		prev->next = tmp;
		return prev->next;
	}

	Node* insert_front(TELEM data) {
		return(first = new Node(data, first));
	}

	// ��������
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

	// �����
	Node* find(TELEM key) {
		Node* curr = first;
		while (curr && (curr->value != key)) {
			curr = curr->next;
		}
		return curr;
	}
};

template <typename TELEM>
List<TELEM>::Node::Node(TELEM value, Node* next) : value(value), next(next){
}
