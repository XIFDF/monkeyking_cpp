#include "Node.h"

Node * Node::merge(Node * n1, Node * n2)
{
	if (n1 == NULL) return n2;
	if (n2 == NULL) return n1;

	if (n1->key > n2->key) {
		return mergel(n1, n2);
	}
	else return mergel(n2, n1);
}

Node * Node::mergel(Node * n1, Node * n2)
{
	if (n1->left == NULL) {
		n1->left = n2;
		n2->father = n1;
	}
	else {
		Node * m = merge(n1->right, n2);
		n1->right = m;
		m->father = n1;
		swapChildren(n1);
	}
	return n1;
}