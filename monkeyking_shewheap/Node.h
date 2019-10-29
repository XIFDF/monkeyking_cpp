#pragma once
//�����������õ��࣬һ���ڵ㼴һ������
#include <iostream>
class Node {
public:
	Node() = default;
	Node(double key, Node *father, Node *left, Node *right) :
		key(key), father(father), left(left), right(right) { }
	Node(double key) : key(key), father(), left(), right() { }

	~Node() {}

	double key = 0.0;
	Node *father = NULL;
	Node *left = NULL;
	Node *right = NULL;

	inline double fight(Node *node);


private:
	inline Node * findRoot();
	Node * merge(Node *n1, Node *n2);
	Node * mergel(Node *n1, Node *n2);
	inline void swapChildren(Node *n);
	inline double deleteMaxAndInsert();
	inline void insert(Node * n);
};

inline double Node::fight(Node * node)
{
	Node *root1 = this->findRoot();
	Node *root2 = node->findRoot();
	double result;
	if (root1 == root2) return -1;
	else {
		result = merge(root1, root2)->deleteMaxAndInsert();
	}
	return result;
}

inline Node * Node::findRoot()
{
	Node *root = this;
	while (root->father != NULL) {
		root = root->father;
	}
	return root;
}

inline void Node::swapChildren(Node * n)
{
	Node *temp = n->left;
	n->left = n->right;
	n->right = temp;
}

inline double Node::deleteMaxAndInsert()
{
	Node * mergeRoot = merge(this->left, this->right);
	if (mergeRoot != NULL) mergeRoot->father = NULL;

	this->key /= 2;
	this->father = NULL;
	this->left = NULL;
	this->right = NULL;
	mergeRoot->insert(this);
	return this->key; //���ر�ɾ���Ľڵ�
}

inline void Node::insert(Node * n)
{
	merge(this, n);
}
