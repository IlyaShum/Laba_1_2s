#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue>

using namespace std;

// Структура узла дерева
template <typename T>
struct TreeNode {
T value; // Значение узла
TreeNode* left; // Указатель на левого потомка
TreeNode* right; // Указатель на правого потомка

TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева
template <typename T>
class CompleteBinaryTree {
private:
TreeNode<T>* root; // Корень дерева
int capacity; // Максимальный размер дерева
int size; // Текущий размер дерева

void printTree(TreeNode<T>* node, int indent) const; // Вспомогательная функция для печати дерева
void deleteTree(TreeNode<T>* node); // Рекурсивное удаление дерева

public:
CompleteBinaryTree(int capacity); // Конструктор
~CompleteBinaryTree(); // Деструктор

void Tinsert(const T& value); // Вставка элемента
bool Tsearch(const T& value) const; // Поиск элемента
bool TisComplete() const; // Проверка на полноту дерева
void Tprint() const; // Вывод дерева
void TreadFromFile(const string& filename); // Чтение из файла
void TwriteToFile(const string& filename) const; // Запись в файл
};

// Конструктор
template <typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(int capacity) : capacity(capacity), size(0), root(nullptr) {}

// Деструктор
template <typename T>
CompleteBinaryTree<T>::~CompleteBinaryTree() {
deleteTree(root); // Рекурсивно удаляем все узлы
}

// Рекурсивное удаление дерева
template <typename T>
void CompleteBinaryTree<T>::deleteTree(TreeNode<T>* node) {
if (node) {
deleteTree(node->left); // Удаляем левое поддерево
deleteTree(node->right); // Удаляем правое поддерево
delete node; // Удаляем текущий узел
}
}

// Вставка элемента
template <typename T>
void CompleteBinaryTree<T>::Tinsert(const T& value) {
if (size >= capacity) {
cout << "Дерево переполнено!\n";
return;
}

TreeNode<T>* newNode = new TreeNode<T>(value); // Создаем новый узел
if (!root) {
root = newNode; // Если дерево пустое, новый узел становится корнем
} else {
// Используем очередь для нахождения первого свободного места
queue<TreeNode<T>*> q;
q.push(root);

while (!q.empty()) {
TreeNode<T>* current = q.front();
q.pop();

if (!current->left) {
current->left = newNode; // Добавляем в левого потомка
break;
} else if (!current->right) {
current->right = newNode; // Добавляем в правого потомка
break;
} else {
// Если оба потомка заняты, добавляем их в очередь для дальнейшего обхода
q.push(current->left);
q.push(current->right);
}
}
}
size++; // Увеличиваем размер дерева
}

// Поиск элемента
template <typename T>
bool CompleteBinaryTree<T>::Tsearch(const T& value) const {
if (!root) return false;

queue<TreeNode<T>*> q;
q.push(root);

while (!q.empty()) {
TreeNode<T>* current = q.front();
q.pop();

if (current->value == value) {
return true; // Элемент найден
}

if (current->left) q.push(current->left); // Добавляем левого потомка
if (current->right) q.push(current->right); // Добавляем правого потомка
}
return false; // Элемент не найден
}

// Проверка на полноту дерева
template <typename T>
bool CompleteBinaryTree<T>::TisComplete() const {
if (!root) return true;

queue<TreeNode<T>*> q;
q.push(root);
bool mustBeLeaf = false; // Флаг, указывающий, что все последующие узлы должны быть листьями

while (!q.empty()) {
TreeNode<T>* current = q.front();
q.pop();

if (mustBeLeaf && (current->left || current->right)) {
return false; // Если узел не лист, дерево не полное
}

if (current->left) {
q.push(current->left);
} else {
mustBeLeaf = true; // Все последующие узлы должны быть листьями
}

if (current->right) {
q.push(current->right);
} else {
mustBeLeaf = true; // Все последующие узлы должны быть листьями
}
}
return true; // Дерево полное
}

// Вывод дерева
template <typename T>
void CompleteBinaryTree<T>::Tprint() const {
if (!root) {
cout << "Дерево пустое.\n";
return;
}
printTree(root, 0); // Начинаем с корня дерева
}

// Вспомогательная функция для печати дерева
template <typename T>
void CompleteBinaryTree<T>::printTree(TreeNode<T>* node, int indent) const {
if (node) {
printTree(node->right, indent + 4); // Правое поддерево
if (indent) {
cout << setw(indent) << ' '; // Выравнивание
}
cout << node->value << "\n"; // Печатаем узел
printTree(node->left, indent + 4); // Левое поддерево
}
}

// Чтение из файла
template <typename T>
void CompleteBinaryTree<T>::TreadFromFile(const string& filename) {
ifstream file(filename);
if (!file.is_open()) {
cout << "Не удалось открыть файл для чтения!" << endl;
return;
}

T value;
while (file >> value) {
if (value != T()) { // Предположим, что значение по умолчанию обозначает пустое значение
Tinsert(value); // Вставляем элемент в дерево
}
}

file.close();
}

// Запись в файл
template <typename T>
void CompleteBinaryTree<T>::TwriteToFile(const string& filename) const {
ofstream file(filename);
if (!file.is_open()) {
cout << "Не удалось открыть файл для записи!" << endl;
return;
}

if (!root) return;

queue<TreeNode<T>*> q;
q.push(root);

while (!q.empty()) {
TreeNode<T>* current = q.front();
q.pop();

file << current->value << "\n"; // Записываем значение узла

if (current->left) q.push(current->left); // Добавляем левого потомка
if (current->right) q.push(current->right); // Добавляем правого потомка
}

file.close();
}

