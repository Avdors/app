// lbr_SDP_2.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;


int* m;

struct vertex
{
	vertex* left;
	vertex* right;
	int data;
};

vertex* root1 = NULL, * root2 = NULL;

//
vertex* ISDP(int, int);
//
int recSDP(int, vertex*&);
//
int SDP(int, vertex*&);
//Вычисление размера дерева
int size(vertex*);
//Вычисление высоты дерева
int height(vertex*);
//Выбор максимальной
int max(int, int);
//Вычисление средней высоты
int sdp(vertex*, int);
//Вычисление контрольной суммы
int summ(vertex*);
//Обход слева направо
void LR(vertex* x);
//
int delTree(vertex*&);

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int N;
	cout << "Input n:\n";
	cin >> N;
	m = new int[N];

	for (int i = 0; i < N; i++) {
		m[i] = i;
	}
	root1 = ISDP(0, N - 1);

	for (int i = 0; i < N; i++) {
		m[i] = rand() % 2000;
	}
	for (int i = 0; i < N; i++) {
		recSDP(m[i], root2);
	}


	printf("+------+----------+----------------+----------+----------------+\n");
	printf("|%6d|  Размер  |  Контр. сумма  |  Высота  |  Сред. высота  |\n", N);
	printf("+------+----------+----------------+----------+----------------+\n");
	printf("| ИСДП |%10d|%16d|%10d|%16.2f|\n", size(root1), summ(root1), height(root1), (double)sdp(root1, 1) / size(root1));
	printf("|  СДП |%10d|%16d|%10d|%16.2f|\n", size(root2), summ(root2), height(root2), (double)sdp(root2, 1) / size(root2));
	printf("+------+----------+----------------+----------+----------------+\n");

	return 0;
}

vertex* ISDP(int l, int r)
{
	if (l > r) {
		return NULL;
	}
	else {
		int k = (l + r) / 2;
		vertex* p;
		p = new vertex;
		p->data = m[k];
		p->left = ISDP(l, k - 1);
		p->right = ISDP(k + 1, r);
		return p;
	}
}

int recSDP(int data, vertex*& p)
{
	if (!p) {
		p = new vertex;
		p->data = data;
		p->left = NULL;
		p->right = NULL;

	}
	else if (data < p->data) {
		recSDP(data, p->left);
	}
	else if (data > p->data) {
		recSDP(data, p->right);
	}
	else {
		return 0;
	}
}

int SDP(int data, vertex*& point)
{
	vertex** p = &point;

	while (*p) {
		if (data < (*p)->data) {
			p = &((*p)->left);
		}
		else if (data > (*p)->data) {
			p = &((*p)->right);
		}
		else break;
	}

	if (*p == NULL) {
		*p = new vertex;
		(*p)->data = data;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}

	return 0;
}

void LR(vertex* x)
{
	if (x == NULL) return;
	LR(x->left);
	cout << x->data << ' ';
	LR(x->right);
}

int size(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + size(x->left) + size(x->right);
	}
}

int max(int x, int y)
{
	if (x > y) return x;
	return y;
}

int height(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return 1 + max(height(x->left), height(x->right));
	}
}

int sdp(vertex* x, int l)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return l + sdp(x->left, l + 1) + sdp(x->right, l + 1);
	}
}

int summ(vertex* x)
{
	if (x == NULL) {
		return 0;
	}
	else {
		return x->data + summ(x->left) + summ(x->right);
	}
}
