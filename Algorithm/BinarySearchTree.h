#pragma once

enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int key = {};
	bool external;
	Color color = Color::Black;
};

//Red-Black Tree
// 1) ��� ���� Red or Black
// 2) Root�� Black
// 3) Leaf(NIL)�� Black
// 4) Red ����� �ڽ��� Black(�����ؼ� Red-Red �Ұ�)
// 5) �� ���κ��� �������� ���� ��ε��� ��� ���� ���� Black��带 ������.

class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
	
	void Print() { Print(_root, 10, 0); }
	void Print(Node* node, int x, int y);
	
	

	Node* Search(Node* node, int key);
	
	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);

	void Insert(int key);
	void InsertFixup(Node* node);

	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u, Node* v);

	// Red-Black Tree
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

private:
	Node* _root = nullptr;
	Node* _nil = nullptr;
};

