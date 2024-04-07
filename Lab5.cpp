/*Написать программу, преобразующую арифметическое выражение, допускающее скобочную запись, операции +, -, *,/ , 
вещественные числа и переменную x, в бинарное дерево, структурно эквивалентное выражению. 
Реализовать функцию вычисления выражения по дереву для заданного x
*/


#include<iostream>
#include<math.h>
#include<vector>
#include <string>
using namespace std;

struct  TreeNode
{
	double data; // ключ/данные
	char oper;
	TreeNode* left; // указатель на левого потомка
	TreeNode* right; // указатель на правого потомка
};
int prioritet(char c)
{
	if (c == '+' || c == '-')
		return 1;
	else
		return 2;
}

double char2double(string S)
{
	int i, l, k = 1;
	double r = 0, p = 1;
	for (i = 0; i < S.size(); i++)
	{
		if (k < 0) p = p * 10;
		if (S[i] == '.')
			k = -k;
		else
			r = r * 10 + (S[i] - '0');
	}
	return r / p;
}
bool IsNumber(string S)
{

	for (int i = 0; i < S.size(); i++)
		if (S[i] != '0' && S[i] != '1' && S[i] != '2' && S[i] != '3' && S[i] != '4' && S[i] != '5' && S[i] != '6' && S[i] != '7' && S[i] != '8' && S[i] != '9' && S[i] != '.')
			return false;
	return true;
}
class Tree
{
public:
	TreeNode* root;

	Tree()
	{
		root = new TreeNode();
	}

	void Build(string input, TreeNode* root)
	{
		int index = FindOper(input);
		bool x = false;
		bool number = false;
		while (index < 0)
		{
			if (IsNumber(input))
			{
				number = true;
				break;
			}
			if (input == "x")
			{
				x = true;
				break;
			}
			input.erase(input.begin());
			input.erase(input.begin() + input.size() - 1);
			index = FindOper(input);
		}

		if (x || number)
		{
			if (x)
			{
				root->oper = 'x';
			}
			else
			{
				root->data = char2double(input);
			}
		}
		else
		{//x + 5
			root->left = new TreeNode();
			Build(input.substr(0, index), &(*root->left));
			root->right = new TreeNode();
			Build(input.substr(index + 1), &(*root->right));
			root->oper = input[index];
		}

	}

	int FindOper(string input)
	{
		int index = -1;
		int prior = 3;
		int inside = 0;

		for (int i = 0; i < input.size(); i++)
		{
			if (input[i] == '(')
				inside++;
			if (input[i] == ')')
				inside--;
			if ((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') && inside == 0)
			{
				if (prioritet(input[i]) <= prior)
				{
					prior = prioritet(input[i]);
					index = i;
				}
			}
		}

		return index;
	}

	double Rez(TreeNode* root, double x)
	{
		if (root->oper == '+')
			return Rez(root->left, x) + Rez(root->right, x);
		if (root->oper == '-')
			return Rez(root->left, x) - Rez(root->right, x);
		if (root->oper == '*')
			return Rez(root->left, x) * Rez(root->right, x);
		if (root->oper == '/')
			return Rez(root->left, x) / Rez(root->right, x);
		if (root->oper == 'x')
			return x;

		return root->data;
	}
};
struct TreeNode* addnode(int x, TreeNode* tree) {
	if (tree == NULL) { // Если дерева нет, то формируем корень
		tree = new TreeNode; // память под узел
		tree->data = x;   // поле данных
		tree->left = NULL;
		tree->right = NULL; // ветви инициализируем пустотой
	}
	else  if (x < tree->data)   // условие добавление левого потомка
		tree->left = addnode(x, tree->left);
	else    // условие добавление правого потомка
		tree->right = addnode(x, tree->right);
	return(tree);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Tree* t = new Tree();
	string s;
	cout << "Введите выражение: ";
	getline(cin, s);
	cout << "Введите x: ";
	double x;
	cin >> x;
	t->Build(s, &(*t->root));
	cout << "Ответ: " << t->Rez(t->root, x) << endl;
	return 0;
}
