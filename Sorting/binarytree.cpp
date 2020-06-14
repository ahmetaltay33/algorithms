#include "binarytree.h"

#include <iostream>
#include <string>

using namespace std;

node* NewNode(node* p, int k)
{
	node* x = new node();
	x->key = k;
	x->parent = p;
	x->right = nullptr;
	x->left = nullptr;
	return x;
}

node* TreeSearch(node* x, int k)
{
	if(x == nullptr || x->key == k)
		return x;
	if (k < x->key)
		return TreeSearch(x->left, k);
	return TreeSearch(x->right, k);
}

node* TreeMinimum(node* x)
{
	if (x == nullptr || x->left == nullptr)
		return x;
	return TreeMinimum(x->left);
}

node* TreeMaximum(node* x)
{
	if (x == nullptr || x->right == nullptr)
		return x;
	return TreeMaximum(x->right);
}

node* TreeSuccessor(node* x)
{
	if (x->right != nullptr)
		return TreeMinimum(x->right);
	node* y = x->parent;
	while(y != nullptr && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

node* TreeInsert(node* x, int k)
{
	if (x == nullptr)
		return NewNode(nullptr, k);
	node* n;
	if (k < x->key)
	{
		n = TreeInsert(x->left, k);
		n->parent = x;
		x->left = n;
	}
	if (k > x->key)
	{
		n = TreeInsert(x->right, k);
		n->parent = x;
		x->right = n;
	}
	return x;
}

node* TreeDelete(node* x, int k)
{
	if (x == nullptr)
		return x;
	if (k < x->key)
		x->left = TreeDelete(x->left, k);
	else if (k > x->key)
		x->right = TreeDelete(x->right, k);
	else
	{
		if(x->left == nullptr)
		{
			node* temp = x->right;
			if(temp != nullptr)
				temp->parent = x->parent;
			free(x);
			return temp;
		}
		else if(x->right == nullptr)
		{
			node* temp = x->left;
			if (temp != nullptr)
				temp->parent = x->parent;
			free(x);
			return temp;
		}
		node* temp = TreeMinimum(x->right);
		x->key = temp->key;
		x->right = TreeDelete(x->right, temp->key);
	}
	return x;
}

void TreePrint(node* x, string& s)
{
	if (x != nullptr)
	{
		TreePrint(x->left, s);
		if (!s.empty())
			s += ", ";
		s += to_string(x->key);
		TreePrint(x->right, s);
	}
}