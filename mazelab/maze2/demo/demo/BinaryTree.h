#pragma once
#include<vector>
#include<cstdlib>
#include<queue>
#include<iostream>
template<typename T>
class node {
public:
	node() = default;
	node(const T & _arg) :value(_arg) {}
	node(T && _arg) :value(std::move(_arg)) {}
	node &operator=(const node &) = delete;
	node &operator=(node &&) = delete;
protected:
	T value=T();
};
template<typename T>
class BinaryTree {
public:
	using value_type = T;
	template<typename U>
	class BinaryTreeNode :public node<U> {
	public:
		friend class BinaryTree<U>;
		BinaryTreeNode() = default;
		BinaryTreeNode(const U & _arg, BinaryTreeNode *_left = nullptr, BinaryTreeNode * _right = nullptr): node<U>(_arg),
			left(_left), right(_right) {}
		BinaryTreeNode(U && _arg, BinaryTreeNode *_left = nullptr, BinaryTreeNode *_right = nullptr) :node<U>(std::move(_arg)),
			left(_left), right(_right) {}
		BinaryTreeNode & operator=(const BinaryTreeNode &) = delete;
		BinaryTreeNode & operator=(BinaryTreeNode &&) = delete;
		~BinaryTreeNode() {
			if (left != nullptr)
				delete left;
			if (right != nullptr)
				delete right;
		}
	protected:
		BinaryTreeNode *left = nullptr;
		BinaryTreeNode *right = nullptr;
	};

	void geneteRandom() {
		root = new BinaryTreeNode<T>(2);
		std::vector<BinaryTreeNode<T>*>t;
		cur = root;
		status = true;
		t.push_back(root);
		nodes.push_back(t);
		for (int i = 0; i < 4; i++) {
			for (auto &t : nodes[i]) {
				t->left = new BinaryTreeNode<T>(rand() % 3 + 2);
				t->right = new BinaryTreeNode<T>(rand() % 3 + 2);
				std::vector<BinaryTreeNode<T>*>temp;
				temp.push_back(t->left);
				temp.push_back(t->right);
				nodes.push_back(temp);
			}
		}
		for (auto t : nodes.back()) {
			t->left = new BinaryTreeNode<T>(rand() % 2);
			t->right = new BinaryTreeNode<T>(rand() % 2);
		}
	}
	void dreadth() {
		if (root == nullptr)
			return;
		std::queue<BinaryTreeNode<T>*>t;
		t.push(root);
		while (!t.empty()) {
			auto p = t.front();
			std::cout << p->value << std::endl;
			if (p->left != nullptr)
				t.push(p->left);
			if (p->right != nullptr)
				t.push(p->right);
			t.pop();
		}
	}
	value_type step() {
		if (cur != nullptr) {
			if (cur->left == nullptr || cur->right == nullptr)
				status = false;
			else {
				if (rand() % 2)
					cur = cur->left;
				else
					cur = cur->right;
			}
			return cur->value;
		}
		return value_type();
	}
	bool canStep() {
		return status;
	}
	~BinaryTree() {
		if (root != nullptr)
			delete root;
	}
private:
	bool status=false;
	BinaryTreeNode<value_type> *cur=nullptr;
	std::vector<std::vector<BinaryTreeNode<T>*>>nodes;
	BinaryTreeNode<value_type> *root = nullptr;
};