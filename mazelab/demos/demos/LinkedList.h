#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
#include<initializer_list>
#include<iostream>
#include<functional>
#define new new(std::nothrow)

namespace mono {
	template<typename T>
	class list {
	public:
		template<typename U>
		class node {
		public:
			friend class list<U>;
			typedef U value_type;
			node() :value(value_type()), next(nullptr) {}
			node(const value_type & _arg, const node<value_type> *_next = nullptr) :value(_arg), next(const_cast<node<value_type>*>(_next)) {}
			template<typename...Args>
			node(const Args&...args, const node<value_type> *_next = nullptr) : value(args...), next(const_cast<node<value_type>*>(_next)) {}
			node(value_type && _arg, const node<value_type>*_next = nullptr) :value(std::move(_arg)), next(const_cast<node<value_type>*>(_next)) {}
		private:																				
			value_type value;
			node<value_type>*next;
		};

		typedef T value_type;
		list() = default;
		list(const value_type & _arg) {
			head = new node<value_type>(_arg);
			tail = head;
			_size++;
		}
		list(std::initializer_list<value_type> _arg) {
			if (_arg.size()==0)
				return;
			auto q = _arg.begin();
			head = new node<value_type>(*q++);
			auto p = head;
			_size++;
			while (_size != _arg.size()) {
				p->next = new node<value_type>(*q);
				p = p->next;
				tail = p;
				q++;
				_size++;
			}
		}
		template<typename iterator>
		list(iterator first, iterator end) {
			try {
				if (first == end)
					throw std::runtime_error("fitsr is equal to end");
				head = new node<value_type>(*first++);
				_size++;
				auto p = head;
				while (first != end) {
					p->next = new node<value_type>(*first++);
					tail = p;
					_size++;
					p = p->next;
				}
			}
			catch (std::runtime_error &a) {
				std::cout << a.what() << std::endl;
			}
		}
		list(value_type && _arg) {
			head = new node<value_type>(std::move(_arg));
			tail = head;
			_size++;
		}
		template<typename ...Args>
		list(const Args&...args) {
			head = new node<value_type>(args...);
			tail = head;
			_size++;
		}

		bool empty()const {
			return _size == 0;
		}
		size_t size()const {
			return _size;
		}
		void addToTail(const value_type & _arg) {
			if (empty()) {
				head = new node<value_type>(_arg);
				tail = head;
				_size++;
			}
			else {
				tail->next = new node<value_type>(_arg);
				tail = tail->next;
				_size++;
			}
		}
		void delFromTail() {
			if (head == tail&&head!=nullptr) {
				delete head;
				head = tail = nullptr;
				_size = 0;
			}
			else {
				auto p = head;
				while (p->next != tail)
					p = p->next;
				delete tail;
				tail = p;
				_size--;
			}
		}
		value_type operator[](const uint32_t &_arg)const {
			try {
				if (_arg + 1 > _size)
					throw std::runtime_error("overflow on list");
				auto p = head;
				for (uint32_t i = 1; i <= _arg; ++i)
					p = p->next;
				return p->value;
			}
			catch (std::runtime_error & arg) {
				std::cout << arg.what() << std::endl;
				return value_type();
			}
	}
		void writeToFileByBinary(std::fstream & _arg) {  //for file
			auto func = [this,&_arg](node<T> *__arg) {
				_arg.write(reinterpret_cast<char *>(&__arg->value), sizeof(T));
			};
				if (empty())
					return;
				else {
					auto p = head;
					while (p != nullptr) {
						func(p);
						p = p->next;
					}
				}
		}
		void writeToFileByText(std::fstream & _arg) {  //for file
			auto func = [this, &_arg](node<T> *__arg) {
				_arg << __arg->value<<std::endl;
			};
			if (empty())
				return;
			else {
				auto p = head;
				while (p != nullptr) {
					func(p);
					p = p->next;
				}
			}
		}
		void clear() {
			if (empty()) {
				return;
			}
			auto p = head;
			while (p != nullptr) {
				head = p->next;
				delete p;
				p = head;
			}
			head = tail = nullptr;
			_size = 0;
		}
	private:
		size_t _size=0;
		node<value_type> *head=nullptr;
		node<value_type> *tail=nullptr;
	};
}
#endif //! __LINKEDLIST_H__