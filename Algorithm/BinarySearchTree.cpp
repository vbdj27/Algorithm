#include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>

using namespace std;

enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}

BinarySearchTree::BinarySearchTree()
{
	_nil = new Node(); //Black
	_root = _nil;
}

BinarySearchTree::~BinarySearchTree()
{
	delete _nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == _nil)
	{
		return;
	}

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
	{
		SetCursorColor(ConsoleColor::BLUE);
	}

	else
	{
		SetCursorColor(ConsoleColor::RED);
	}

	cout << node->key;
	Print(node->left, x - (5 / (y+1)), y+1);
	Print(node->right, x + (5 / (y+1)), y+1);

	SetCursorColor(ConsoleColor::WHITE);
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if (node == _nil || key == node->key)
	{
		return node;
	}

	if (key < node->key)
	{
		return Search(node->left, key);
	}

	else
	{
		return Search(node->right, key);
	}
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left != _nil)
	{
		node = node->left;
	}

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right != _nil)
	{
		node = node->right;
	}

	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != _nil)
	{
		return Min(node->right);
	}

	Node* parent = node->parent;

	while (parent != _nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();
	newNode->key = key;

	Node* node = _root;
	Node* parent = _nil;

	while (node != _nil)
	{
		parent = node;

		if (key < node->key)
		{
			node = node->left;
		}

		else
		{
			node = node->right;
		}
	}

	newNode->parent = parent;

	if (parent == _nil)
	{
		_root = newNode;
	}

	else if (key < parent->key)
	{
		parent->left = newNode;
	}

	else
	{
		parent->right = newNode;
	}

	// �˻�
	newNode->left = _nil;
	newNode->right = _nil;
	newNode->color = Color::Red;

	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{
	// 1) p = red, uncle = red
	// -> p = black, uncle = black, pp = red�� �ٲ�
	// 2) p = red, uncle = black (triangle)
	// -> ȸ���� ���� case 3���� �ٲ�
	// 3) p = red, uncle = black (list)
	// -> ���� ���� +  ȸ��

	//       [pp(B)]
	//    [p(R)]    [u(R)]
	//      [n(R)]
	while (node->parent->color == Color::Red)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black; //p
				uncle->color = Color::Black; //u
				node->parent->parent->color = Color::Red; //pp
				node = node->parent->parent;
			}

			else
			{
				//       [pp(B)]
	            //    [p(R)]    [u(B)]
	            //      [n(R)]

				//       [pp(B)]
				//    [n(R)]    [u(B)]
				//      [p(R)]
				if (node == node->parent->right) //triangle Ÿ��
				{
					node = node->parent;
					LeftRotate(node);
				}

				// List Ÿ��
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}

		else
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black; //p
				uncle->color = Color::Black; //u
				node->parent->parent->color = Color::Red; //pp
				node = node->parent->parent;
			}

			else
			{
				if (node == node->parent->left) //triangle Ÿ��
				{
					node = node->parent;
					RightRotate(node);
				}

				// List Ÿ��
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}

	_root->color = Color::Black;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(_root, key);
	Delete(deleteNode);
}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->left == nullptr)
	{
		Replace(node, node->right);
	}

	else if (node->right == nullptr)
	{
		Replace(node, node->left);
	}

	else
	{
		// ���� ������ ã��
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

//u ����Ʈ���� v ����Ʈ���� ��ü
// �׸��� delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == nullptr)
	{
		_root = v;
	}

	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}

	else
	{
		u->parent->right= v;
	}

	if (v)
	{
		v->parent = u->parent;
	}

	delete u;
}

//    [y]
//  [x]  [3]
// [1][2]

//    [x]
//  [1]  [y]
//		[2][3]

void BinarySearchTree::LeftRotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left; // [2];

	if (y->left != _nil)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;

	if (x->parent == _nil)
	{
		_root = y;
	}

	else if (x == x->parent->left)
	{
		x->parent->left = y;
	}

	else
	{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void BinarySearchTree::RightRotate(Node* y)
{
	Node* x = y->left;
	y->left = x->right; // [2];

	if (y->right != _nil)
	{
		y->right->parent = y;
	}

	x->parent = y->parent;

	if (y->parent == _nil)
	{
		_root = x;
	}

	else if (y == y->parent->left)
	{
		y->parent->left = x;
	}

	else
	{
		y->parent->right = x;
	}

	x->right = y;
	y->parent = x;
}
