// CalTree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include<set>
using namespace std;
struct NodeTree
{
    string data = "";
    NodeTree* right = nullptr;
    NodeTree* left = nullptr;
    NodeTree* prev = nullptr;
    /*
    NodeTree(string data = "", NodeTree* right = nullptr, NodeTree* left = nullptr, NodeTree* prev = nullptr)
    {
        data = data;
        left = left;
        right = right;
        prev = right;

    }
    */
};
void  postfix_print(NodeTree* node) {
	if (node != nullptr) {
		postfix_print(node->left);
		postfix_print(node->right);
		cout << node->data << " ";
	}
	

}
const set<string> operations = { "+","-","*","/","^","(",")" }; // операции доступные сейчас 
const set<string> one_operations = { "sin","cos","tg","sqrt" }; // операции доступные сейчас 
pair<string, int> get_digit(string x, int i = 0) {
	string xi;
	pair<string, int> digit;
	digit.first = "";
	digit.second = 0;
	for (i; i < x.size(); i++) {
		xi = x[i];
		if (isdigit(x[i])) {
			digit.first = digit.first + xi;
			digit.second = digit.second + 1;
		}
		else {
			break;
		}
	}
	return digit;

}
pair<string, int> get_text(string xv, int j = 0) {
	string xi;
	pair<string, int> text;
	//text.first = "fuck";
	text.first = "";
	text.second = 0;
	for (j; j < xv.size(); j++) {
		xi = xv[j];
		if (operations.count(xi) == 1) {
			if (text.first.empty()) {
				text.first = xi;
				text.second = 1;
			}
			break;
		}
		if (!isdigit(xv[j])) {

			text.first = text.first + xi;
			text.second = text.second + 1;

		}
		else {
			//cout << "dfdf" << endl;
			//text.second = j;
			break;
		}
	}
	return text;
}
NodeTree* sort_tree_station(string expression) {
    NodeTree* root = new NodeTree();
	int size = expression.size();
	pair<string, int> digit;
	pair<string, int> text;
	string ops = "";
	NodeTree* p = root;
	for (int i = 0; i < size;)
	{
		if (!isdigit(expression[i])) {
			text = get_text(expression, i);
			string token = text.first;
			if (token == "(") {
				p->left = new NodeTree();
				p->left->prev = p;
				p = p->left;
			}
			else if (token == ")") {
				if (p->prev != nullptr) {
					p = p->prev;
				}
				
			}
			else {
				p->data = token;
				p->right = new NodeTree();
				p->right->prev = p;
				p = p->right;

			}
			i = i + text.second;
		}
		else {
			digit = get_digit(expression, i);
			p->data = digit.first;
			//cout << p->data << endl;
			if (p->prev != nullptr) {
				p = p->prev;
			}
			
			i = i + digit.second;

		}
	}
	return root;
}
string add_m(string x) {
	string ot = "(";
	bool oper = false;
	for (int i=0; i < x.size(); i++) {
		if (isdigit(x[i])) {
			if (oper == false) {
				ot =  ot + "(" + x[i];
			}
			else {
				ot = ot + x[i]+ ")" ;
				oper = false;
			}
		}
		else {
			ot = ot + x[i];
			oper = true;
		}
	}
	return ot;
}

int main()
{
    
    string x;
	x = "1+2*3";
	cout << add_m(x) << endl;
	NodeTree* root;
	root = sort_tree_station(add_m(x));
	postfix_print(root);
	

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
