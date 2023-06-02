// kr1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
#include <ctime>
#include <string>
#include <chrono>
#include <queue> 
using namespace chrono;
struct Node
{
	int data;       
	Node* left;    //указатель на левого потомка
	Node* right;   //указатель на правого потомка
};
struct Trunk
{
	Trunk *prev;
	string str;

	Trunk(Trunk *prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};
int tabs = 0;
void Add(int value, Node*& root)              
{
	
	if (root==NULL)
	{
		root = new Node;
		root->left = NULL;
		root->right = NULL;
		root->data = value;
		return;
	}
	else                         // если узел инициализирован
	{
		if (value < root->data)             // иначе, если искомое ключевое значение меньше ключевого значения узла
			Add(value, root->left);    // вызывается эта же функция для левого потомка.
		else if (value > root->data)                                  // иначе
			Add(value, root->right);   // вызывается эта же функция для правого потомка.
	}
}



void showTrunks(Trunk *p)//функция вывода связей дерева
{
	if (p == nullptr)//если нет поддеревьев
		return;
	showTrunks(p->prev);//выводим предыдущий узел
	cout << p->str;//выводим отступы и связи
}

void printTree(Node* root, Trunk *prev, bool isRight)
{
	if (root == nullptr)//пустое дерево
		return;
	string prev_str = "    ";//отступ по уровням (длина как для стрелки)
	Trunk *trunk = new Trunk(prev, prev_str);//новая связь
	printTree(root->right, trunk, true);//правое поддерево
	if (!prev)//если нет предыдущего узла (предка) -> корень дерева
		trunk->str = "———";//связь корня дерева
	else if (isRight)//если правое поддерево
	{
		trunk->str = ".———";//связь правого поддерева
		prev_str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
	}
	else {//в противном случае - левое поддерево
		trunk->str = "`———";//левое поддерево
		prev->str = prev_str;//отступ по уровням не меняется
	}
	showTrunks(trunk);//выводим связи дерева - стебли
	cout << " " << root->data << endl;//выводим значение узла
	if (prev) //задаем строку отступов для узла, если есть поддеревья
		prev->str = prev_str;
	trunk->str = "   |";//в отступ по уровням добавляем черту (дерево идет вширь)
	printTree(root->left, trunk, false);//левое поддерево
}

void Insert(Node *(&root), int value)
{
	if (root == NULL) {
		root = new Node;
		root->data = value;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (root->data == value) return;
		if (value < root->data) {
			Insert(root->left, value);
		}
		else if (value > root->data) {
			Insert(root->right, value);
		}
	}
}
Node* GetMax(Node* root) {
	while (root->right) {
		root = root->right;
	}
	return root;
}
int k;
void Del(Node* (&root), int data) {
	if (root == NULL)
	{
		cout << "Значение не найдено\n";
		return;
	}
	if (data < root->data) 
		Del(root->left, data);
	else if (data > root->data) 
		Del(root->right, data);
	else if (data==root->data) {
		if (root->left == NULL and root->right == NULL) {
			delete root;
			root = NULL;
		}
		else if (root->right == NULL) {
			Node* del= root;
			root = root->left;
			delete del;
		}
		else if (root->left == NULL) {
			Node* del = root;
			root = root->right;
			delete del;
		}
		else {
			Node *max = GetMax(root->left);
			root->data = max->data;
			Del(root->left, max->data);
		}
	}
}
void Get(Node* (&root), int data) {
	if (root == NULL)
	{
		k = 100;
		cout << "Значение не найдено\n";
		return;
	}
	if (data < root->data)
		Get(root->left, data);
	else if (data > root->data)
		Get(root->right, data);
	if (data == root->data)
		k = root->data;
}
void Direct(Node* root) {
	if (root) {
		cout << root->data << " ";
		Direct(root->left);
		Direct(root->right);
	}
}
void Reverse(Node* root) {
	if (root) {
		Reverse(root->left);
		Reverse(root->right);
		cout << root->data << " ";
	}
}
void Wide(Node* root)
{
	queue <Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node *tmp = q.front();
		q.pop();
		cout << tmp->data << " ";
		//Если есть левый наследник, то помещаем его в очередь для дальнейшей обработки
		if (tmp->left) {
			q.push(tmp->left);
		}
		//Если есть правый наследник, то помещаем его в очередь для дальнейшей обработки
		if (tmp->right) {
			q.push(tmp->right);
		}
	}
}
void FreeTree(Node* root)
{
	if (!root) return;
	FreeTree(root->left);
	FreeTree(root->right);
	delete root;
	return;
}
int main()
{
	setlocale(0, "");
	srand(time(NULL));
	time_point<steady_clock> start;
	time_point<steady_clock> end;
	time_point<steady_clock> start1;
	time_point<steady_clock> end1;
	time_point<steady_clock> start2;
	time_point<steady_clock> end2;
	time_point<steady_clock> start3;
	time_point<steady_clock> end3;
	time_point<steady_clock> start4;
	time_point<steady_clock> end4;
	Node* Root = NULL;
	while (true)
	{
		int choose;
		
		int level = 0;
		cout << "\n1)Создать дерево\n2)Вставить элемент\n3)Удалить элемент\n4)Получить элемент\n5)Прямой обход\n6)Обратный обход\n7)Обход в ширину\n0)Выход\n";
		cout << "Ваш выбор: ";
		cin >> choose;
		if (choose == 0)
			break;
		switch (choose)
		{
			case 1:
				int choose1;
				cout << "\n1)Ввести количество элементов\n2)Ввести с клавиатуры\n";
				cout << "Ваш выбор: ";
				cin >> choose1;
				switch (choose1)
				{
				case 1:
					FreeTree(Root);
					Root = NULL;
					int n;
					cout << "\nВведите кол-во элементов: ";
					cin >> n;
					int a;
					start = chrono::steady_clock::now();
					for (int i = 0; i < n; i++)
					{
						Add(rand() % 199 - 99, Root);
					}
					end = chrono::steady_clock::now();
					printTree(Root, nullptr, false);
					cout << "\nЗатраченное время: " << duration_cast<microseconds>(end - start).count() << " мкс.\n";
					break;
				case 2:
					FreeTree(Root);
					Root = NULL;
					cout << "\nЧтобы прекратить введите 00";
					cout << endl;
					string data;
					
					cin >> data;
					while (data != "00" )
					{
						start1 = chrono::steady_clock::now();
						Add(stoi(data), Root);
						end1 = chrono::steady_clock::now();
						cin >> data;
						
					}
					
					printTree(Root, nullptr, false);
					cout << "\nЗатраченное время: " << duration_cast<microseconds>(end1 - start1).count() << " мкс.\n";
					break;
				}
				break;
			case 2:
			{
				int value;
				cout << "\nВведите значение элемента, который хотите вставить: ";
				cin >> value;
				start2 = chrono::steady_clock::now();
				Insert(Root, value);
				end2 = chrono::steady_clock::now();
				printTree(Root, NULL, false);
				cout << "\nЗатраченное время: " << duration_cast<microseconds>(end2 - start2).count() << " мкс.\n";
				break;
			}
			case 3:
			{
				int value;
				cout << "\nВведите значение элемента, который хотите удалить: ";
				cin >> value;
				start4 = chrono::steady_clock::now();
				Del(Root, value);
				end4 = chrono::steady_clock::now();
				printTree(Root, NULL, false);
				cout << "\nЗатраченное время: " << duration_cast<microseconds>(end4 - start4).count() << " мкс.\n";
				break;
			}
			case 4:
			{
				int value;
				cout << "\nВведите значение элемента: ";
				cin >> value;
				start3 = chrono::steady_clock::now();
				Get(Root, value);
				end3 = chrono::steady_clock::now();
				if (k!=100)
					cout << "Значение найдено: " << k<<"\n";
				k = 0;
				cout << "Затраченное время: " << duration_cast<microseconds>(end3 - start3).count() << " мкс.\n";
				break;
			}
			case 5:
			{
				Direct(Root);
				break;
			}
			case 6:
			{
				Reverse(Root);
				break;
			}
			case 7:
			{
				Wide(Root);
				break;
			}
		}
	}
	cout << endl;
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
