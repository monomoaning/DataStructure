#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include<iostream>
#include<queue>
#include<stack>
template<typename T>
class BinaryTree {
public:
	/*the node class*/
	template<typename U>
	class node {
	public:
		friend class BinaryTree<U>;
		node(const U &_arg, node<U>*_left = nullptr, node<U>*_right=nullptr) :value(_arg), left(_left), right(_right) {}
		node() = default;
	private:
		U value{};
		node<U> *left = nullptr;
		node<U> *right = nullptr;
	};
	/*the constructions*/
	BinaryTree() = default;
	/*the insert function*/
	void insert(const T &_arg) {
		if (root == nullptr) {
			root = new node<T>(_arg);
		}
		else {
			auto p = root;
			auto temp = p;
			while (p != nullptr) {
				temp = p;
				if (_arg > p->value)// if the element is greater than the node go right
					p = p->right;
				else
					p = p->left;
			}
			if (_arg<=temp->value)
				temp->left = new node<T>(_arg);
			else
				temp->right = new node<T>(_arg);
		}
	}

	node<T> * getRoot()const {
		return root;
	}
	/*递归前序遍历*/
	void recusivePreTraversal(node<T> * _root) {
		if (_root == nullptr)
			return;
		visit(_root);
		recusivePreTraversal(_root->left);
		recusivePreTraversal(_root->right);
	}
	/*递归中序遍历*/
	void recusiveInTraversal(node<T> * _root) {
		if (_root == nullptr)
			return;
		recusiveInTraversal(_root->left);
		visit(_root);
		recusiveInTraversal(_root->right);
	}
	/*递归后序遍历*/
	void recusivePostTraversal(node<T>* _root) {
		if (_root == nullptr)
			return;
		recusivePostTraversal(_root->left);
		recusivePostTraversal(_root->right);
		visit(_root);
	}
	/*非递归广度遍历*/
	void breadthTraversal(node<T>* _root) {
		if (_root == nullptr)
			return;
		std::queue<node<T>*>temp;
		temp.push(_root);
		while (!temp.empty()) {
			auto t = temp.front();
			temp.pop();
			visit(t);
			if (t->left != nullptr)
				temp.push(t->left);
			if (t->right != nullptr)
				temp.push(t->right);
		}
	}
	/*非递归前序遍历*/
	void preTraversal(node<T>* _root) {
		if (_root == nullptr)
			return;
		std::stack<node<T>*>temp;
		temp.push(_root);
		while (!temp.empty()) {
			auto t = temp.top();
			temp.pop();
			visit(t);
			if (t->right != nullptr)
				temp.push(t->right);
			if (t->left != nullptr)
				temp.push(t->left);

		}
	}
	/*非递归中序遍历*/
	void inTraversal(node<T>* _root) {
		if (_root == nullptr)
			return;
		std::stack<node<T>*>temp;
		while (_root != nullptr || !temp.empty()) {
			while (_root != nullptr) {
				temp.push(_root);
				_root = _root->left;
			}
			if (!temp.empty()) {
				_root = temp.top();
				temp.pop();
				visit(_root);
				_root = _root->right;
			}
		}
	}
	/*非递归后序遍历*/
	void postTraversal(node<T>* _root) {
		if (_root == nullptr)
			return;
		auto cur = _root;
		decltype(cur)last = nullptr;
		std::stack<node<T>*>temp;
		while (cur != nullptr) {
			temp.push(cur);
			cur = cur->left;
		}
		while (!temp.empty()) {
			cur = temp.top();
			temp.pop();
			if (cur->right == nullptr || cur->right == last) {
				visit(cur);
				last = cur;
			}
			else {
				temp.push(cur);
				cur = cur->right;
				while (cur != nullptr) {
					temp.push(cur);
					cur = cur->left;
				}
			}
		}
	}
	/*递归的广度优先遍历*/
	void recusive(std::queue<node<T>*>  _arg) {
		if (_arg.empty())
			return;
		std::queue<node<T>*>temp;
		while(!_arg.empty()){
			auto t = _arg.front();
			if (t->left != nullptr)
				temp.push(t->left);
			if (t->right != nullptr)
				temp.push(t->right);
			visit(_arg.front());
			_arg.pop();
		}
		recusive(_arg=temp);
	}

	std::queue<node<T>*> getRootqueue() {
		std::queue<node<T>*>temp;
		temp.push(root);
		return temp;
	}
private:
	node<T> *root = nullptr;
	void visit(node<T>*_arg) {
		if (_arg == nullptr)
			return;
		std::cout << _arg->value<<std::ends;
	}
};
#endif //!__BINARYTREE_H__