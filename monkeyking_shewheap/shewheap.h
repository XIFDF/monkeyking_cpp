#pragma once

#include <iostream>
#include <stack>
using namespace std;

//斜堆实现类定义
template <typename T> class ShewHeap {

public:
	template <typename T> class Node {
	public:
		Node() = default;
		Node(T key, Node<T> &left, Node<T> &right) :
			key(key), left(left), right(right) { }
		Node(T key) : key(key), left(), right() { }

		~Node() {}

		T key = 0.0;
		Node<T> *left = NULL;
		Node<T> *right = NULL;
	};

	ShewHeap() = default;
	~ShewHeap() { }

	inline bool isEmpty();
	inline T getMaxKey();

	stack<Node<T>*> stk;
	int merge(ShewHeap<T> *other);
	void insert(T key);
	T deleteMax();

private:
	Node<T> *root = NULL;
	Node<T> * merge(Node<T> *root1, Node<T> *root2);
};

template<typename T>
inline bool ShewHeap<T>::isEmpty()
{
	return root == NULL;
}

template<typename T>
inline T ShewHeap<T>::getMaxKey()
{
	return root->key;
}

//斜堆的合并
template<typename T>
int ShewHeap<T>::merge(ShewHeap<T> *other) {
	if (this == other) return -1;

	this->root = merge(this->root, other->root);
	delete(other); //此处只delete两个斜堆合并时被合并的那个，且这个被合并的堆中的节点的内存不会被delete
	other->root = NULL;
	return 1;
}

//斜堆(节点和节点)的合并，斜堆的基本操作
template<typename T>
ShewHeap<T>::Node<T> * ShewHeap<T>::merge(Node<T> *root1, Node<T> *root2) {
	if (root1 == NULL) return root2;
	if (root2 == NULL) return root1;
	Node<T> *r1 = root1, *r2 = root2;
	while (r1 != NULL && r2 != NULL) {
		if (r1->key > r2->key) {
			stk.push(r1);
			r1 = r1->right;
		}
		else {
			stk.push(r2);
			r2 = r2->right;
		}
	}
	Node<T> *r = (r1 != NULL) ? r1 : r2;
	while (!stk.empty()) {
		Node<T> *node = stk.top();
		stk.pop();
		node->right = node->left;
		node->left = r;
		r = node;
	}
	return r;
}

//插入
template<typename T>
void ShewHeap<T>::insert(T key) {
	root = merge(new Node<T>(key), root);
}

//删除堆中值最大节点，返回值为此最大值
template<typename T>
T ShewHeap<T>::deleteMax() {
	if (this->isEmpty()) return -1;
	Node<T> * release = root;
	root = merge(root->left, root->right);
	delete(release);
	return this->root->key;
}
