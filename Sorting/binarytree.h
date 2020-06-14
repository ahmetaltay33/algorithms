#pragma once
#include <string>

struct node
{
	int key;
	node* left;
	node* right;
	node* parent;
};

node* TreeInsert(node* x, int k);
node* TreeDelete(node* x, int k);
void TreePrint(node* x, std::string& s);
