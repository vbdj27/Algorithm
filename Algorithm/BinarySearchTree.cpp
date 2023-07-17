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

void ShowConsoleCursor(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
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

void BinarySearchTree::Print()
{
	::system("cls");
	ShowConsoleCursor(false);
	{ Print(_root, 10, 0); }
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

//���� BST ���� ����
void BinarySearchTree::Delete(Node* node)
{
	if (node == _nil)
	{
		return;
	}

	if (node->left == _nil)
	{
		Color color = node->color;
		Node* right = node->right;
		Replace(node, node->right);

		if (color == Color::Black)
		{
			DeleteFixup(right);
		}
	}

	else if (node->right == _nil)
	{	
		Color color = node->color;
		Node* right = node->left;
		Replace(node, node->left);

		if (color == Color::Black)
		{
			DeleteFixup(right);
		}
	}

	else
	{
		// ���� ������ ã��
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

// ���� BST ���� ����...
// - Case1) ������ ��尡 Red -> �׳� ����! ��!
// - Case2) root�� DB -> �׳� �߰� Black ����! ��!
// - Case3) DB�� sibling ��尡 Red
// -- s = black, p = red (s <-> p ���� ��ȯ)
// -- DB �������� rotate(p)
// goto other case
// - Case4) DB�� sibling ��尡 Black && sibling�� ���� �ڽĵ� Black
// --�߰� Black�� parent���� ����
// --- p�� Red�̸� Black ��.
// --- p�� Black�̸� DB��.
// -- s = red
// -- p�� ������� �˰��� �̾ ���� (DB�� ������ �����ϸ�)
// - Case5) DB�� sibling ��尡 Black && sibling�� near child = red, far child = black
// -- s <-> near ���� ��ȯ
// -- far �������� rotate(s)
// -- goto case 6
// - Case6) DB�� sibling ��尡 Black && sibling�� far child = red
// - p <-> s ����ȯ
// - far = black
// - rotate(p) (DB ��������)
// - �߰� Black ����
void BinarySearchTree::DeleteFixup(Node* node)
{
	Node* x = node;

	// [Case1][Case2]
	while (x != _root && x->color == Color::Black)
	{	
		if (x == x->parent->left)
		{
			// [Case3]
			Node* s = x->parent->right;
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;
				LeftRotate(x->parent);
				s = x->parent->right;
			}

			// [Case4]
			if (s->left->color == Color::Black && s->right->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}

			else
			{
				 // [Case5]
				if (s->right->color == Color::Black)
				{
					s->left->color = Color::Black;
					s->color = Color::Red;
					RightRotate(s);
					s = x->parent->right;
				}

				// [Case6]
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->right->color = Color::Black;
				LeftRotate(x->parent);
				x = _root;
			}
		}

		else
		{
			// [Case3]
			Node* s = x->parent->left;
			if (s->color == Color::Red)
			{
				s->color = Color::Black;
				x->parent->color = Color::Red;
				RightRotate(x->parent);
				s = x->parent->left;
			}

			// [Case4]
			if (s->right->color == Color::Black && s->left->color == Color::Black)
			{
				s->color = Color::Red;
				x = x->parent;
			}

			else
			{
				// [Case5]
				if (s->left->color == Color::Black)
				{
					s->right->color = Color::Black;
					s->color = Color::Red;
					LeftRotate(s);
					s = x->parent->left;
				}

				// [Case6]
				s->color = x->parent->color;
				x->parent->color = Color::Black;
				s->left->color = Color::Black;
				RightRotate(x->parent);
				x = _root;
			}
		}
	}

	x->color = Color::Black;
}

//u ����Ʈ���� v ����Ʈ���� ��ü
// �׸��� delete u
void BinarySearchTree::Replace(Node* u, Node* v)
{
	if (u->parent == _nil)
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

	v->parent = u->parent;
	
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
