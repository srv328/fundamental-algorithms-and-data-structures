#include <iostream>
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename KEY>;
struct list_elem {
	KEY key;
	int index;
	list_elem* next, * prev;
	int count;
};

list_elem* list_init()
{
	list_elem* root = nullptr;
	return root;
}

template <typename KEY>;
void list_insert(list_elem*& head, KEY data)
{
	list_elem* insert = new(list_elem);
	insert->count = 1;
	insert->data = data;
	insert->next = insert;
	insert->prev = insert;
	if (head == nullptr) head = insert;
	else head->count++;
}


template <typename KEY>;
void list_erase(list_elem*& head, KEY data) {
	if (head != nullptr) {
		if (head->count == 1) {
			head->count--;
			delete head;
			head = nullptr;
		}
		else head->count--;
	}
}

void set_color(char a) {
	if (a == 'R') SetConsoleTextAttribute(hConsole, 12);
	else SetConsoleTextAttribute(hConsole, 15);
}

void print_list(list_elem* root, bool color)
{
	if (root != nullptr) {
		if (color) set_color('B');
		else set_color('R');
		list_elem* temp = root;
		while (temp->next != root) {
			std::cout << temp->data.sym << temp->data.num << " (" << temp->count << ")";
			temp = temp->next;
		}
		std::cout << temp->data.sym << temp->data.num << " (" << temp->count << ")";
	}
	SetConsoleTextAttribute(hConsole, 15);
}

struct tree_elem {
	list_elem* list;
	tree_elem* left, * right, * parent;
	bool color; // True - Black
};

tree_elem* root_init(tree_elem* nullnode) {
	tree_elem* root = nullnode;
	return root;
}

tree_elem* null_init() {
	tree_elem* nullnode = new tree_elem;
	nullnode->left = nullptr;
	nullnode->right = nullptr;
	nullnode->list = nullptr;
	nullnode->color = true;
	return nullnode;
}

tree_elem* nullnode = null_init();

template <typename KEY>;
int compare(KEY data1, KEY data2) {
	if (data1 > data2) return 1;
	if (data1 < data2) return -1;
	return 0;
}


template <typename KEY>;
bool search(tree_elem* root, tree_elem* nullnode, KEY data) {
	tree_elem* temp = root;
	while (temp != nullnode) {
		if (compare(temp->list->data, data) == 0) return true;
		if (compare(data, temp->list->data) == 1) temp = temp->right;
		else temp = temp->left;
	}
	return false;
}


void rightRotate(tree_elem* element, tree_elem*& root, tree_elem* nullnode) {
	tree_elem* y = element->left;
	element->left = y->right;
	if (y->right != nullnode) y->right->parent = element;
	y->parent = element->parent;
	if (element->parent == nullptr) root = y;
	else if (element == element->parent->right) element->parent->right = y;
	else element->parent->left = y;
	y->right = element;
	element->parent = y;
}

void leftRotate(tree_elem* element, tree_elem*& root, tree_elem* nullnode) {
	tree_elem* y = element->right;
	element->right = y->left;
	if (y->left != nullnode) y->left->parent = element;
	y->parent = element->parent;
	if (element->parent == nullptr) root = y;
	else if (element == element->parent->left) element->parent->left = y;
	else element->parent->right = y;
	y->left = element;
	element->parent = y;
}

void insert_balance(tree_elem*& element, tree_elem*& root, tree_elem* nullnode) {
	tree_elem* uncle;
	while (element->parent->color == false) {
		if (element->parent == element->parent->parent->left) {
			uncle = element->parent->parent->right;
			if (uncle->color == false) {
				uncle->color = true;
				element->parent->color = true;
				element->parent->parent->color = false;
				element = element->parent->parent;
			}
			else {
				if (element == element->parent->right) {
					element = element->parent;
					leftRotate(element, root, nullnode);
				}
				element->parent->color = true;
				element->parent->parent->color = false;
				rightRotate(element->parent->parent, root, nullnode);

			}
		}
		else {
			uncle = element->parent->parent->left;
			if (uncle->color == false) {
				uncle->color = true;
				element->parent->color = true;
				element->parent->parent->color = false;
				element = element->parent->parent;
			}
			else {
				if (element == element->parent->left) {
					element = element->parent;
					rightRotate(element, root, nullnode);
				}
				element->parent->color = true;
				element->parent->parent->color = false;
				leftRotate(element->parent->parent, root, nullnode);
			}
		}
		if (element == root) { break; }
	}
	root->color = true;

}


template <typename KEY>;
tree_elem* insert(tree_elem*& root, tree_elem* nullnode, KEY data) {
	KEY key = data;
	if (!search(root, nullnode, key)) {
		tree_elem* element = new tree_elem;
		element->parent = nullptr;
		element->left = nullnode;
		element->right = nullnode;
		element->color = false;
		element->list = list_init();
		list_insert(element->list, key);
		tree_elem* parent_buffer = nullptr;
		tree_elem* runner = root;
		while (runner != nullnode) {
			parent_buffer = runner;
			if (compare(element->list->data, runner->list->data) == -1) runner = runner->left;
			else runner = runner->right;
		}
		element->parent = parent_buffer;
		if (parent_buffer == nullptr) root = element;
		else if (compare(element->list->data, parent_buffer->list->data) == -1) parent_buffer->left = element;
		else { parent_buffer->right = element; }
		if (element->parent == nullptr) {
			element->color = true;
			return root;
		}
		if (element->parent->parent == nullptr) return root;
		insert_balance(element, root, nullnode);
	}
	else {
		tree_elem* temp = root;
		while (temp != nullnode) {
			if (compare(temp->list->data, key) == 0) { list_insert(temp->list, key); break; }
			if (compare(key, temp->list->data) == 1) { temp = temp->right; }
			else { temp = temp->left; }
		}
		return root;
	}
	return nullnode;
}

void replace_node(tree_elem*& root, tree_elem* nullnode, tree_elem* n, tree_elem* child) {
	if ((n->parent == nullnode) || (n->parent == nullptr)) root = child;
	else if (n == n->parent->left) n->parent->left = child;
	else n->parent->right = child;
	child->parent = n->parent;
}

void erase_balance(tree_elem*& root, tree_elem* nullnode, tree_elem* element) {
	tree_elem* brother;
	while ((element != root) && (element->color == 1)) {
		if (element == element->parent->left) {
			brother = element->parent->right;
			if (brother->color == false) {
				brother->color = true;
				element->parent->color = false;
				leftRotate(element->parent, root, nullnode);
				brother = element->parent->right;
			}
			if ((brother->left->color == true) && (brother->right->color == true)) {
				brother->color = false;
				element = element->parent;
			}
			else {
				if (brother->right->color == true) {
					brother->left->color = true;
					brother->color = false;
					rightRotate(brother, root, nullnode);
					brother = element->parent->right;
				}
				brother->color = element->parent->color;
				element->parent->color = true;
				brother->right->color = true;
				leftRotate(element->parent, root, nullnode);
				element = root;
			}
		}
		else {
			brother = element->parent->left;
			if (brother->color == false) {
				brother->color = true;
				element->parent->color = false;
				rightRotate(element->parent, root, nullnode);
				brother = element->parent->left;
			}
			if ((brother->left->color == true) && (brother->right->color == true)) {
				brother->color = false;
				element = element->parent;
			}
			else {
				if (brother->left->color == true) {
					brother->right->color = true;
					brother->color = false;
					leftRotate(brother, root, nullnode);
					brother = element->parent->left;
				}
				brother->color = element->parent->color;
				element->parent->color = true;
				brother->left->color = true;
				rightRotate(element->parent, root, nullnode);
				element = root;
			}
		}
	}
	element->color = true;
}

tree_elem* left_max(tree_elem* element, tree_elem* nullnode) {
	while (element->right != nullnode) element = element->right;
	return element;
}


template <typename KEY>;
tree_elem* erase(tree_elem*& root, tree_elem* nullnode, KEY data) {
	if (root != nullptr) {
		KEY key = data;
		tree_elem* temp = root;
		tree_elem* z = nullnode;
		tree_elem* element;
		tree_elem* y;
		while (temp != nullnode) {
			if (compare(temp->list->data, key) == 0) { z = temp; }
			if ((compare(temp->list->data, key) == 0) || (compare(temp->list->data, key) == -1)) { temp = temp->right; }
			else { temp = temp->left; }
		}
		if (z == nullnode) return root;
		if (z->list->count > 1) list_erase(z->list, key);
		else {
			y = z;
			bool y_original_color = y->color;
			if (z->left == nullnode) {
				element = z->right;
				replace_node(root, nullnode, z, z->right);
			}
			else if (z->right == nullnode) {
				element = z->left;
				replace_node(root, nullnode, z, z->left);
			}
			else {
				y = left_max(z->left, nullnode);
				y_original_color = y->color;
				element = y->left;
				if (y->parent == z) {
					element->parent = y;
				}
				else {
					replace_node(root, nullnode, y, y->left);
					y->left = z->left;
					y->left->parent = y;
				}
				replace_node(root, nullnode, z, y);
				y->right = z->right;
				y->right->parent = y;
				y->color = z->color;
			}
			list_erase(z->list, key);
			delete z;
			if (y_original_color == true) erase_balance(root, nullnode, element);
		}
		return root;
	}
	return nullptr;
}


template <typename KEY>;
void delete_list(tree_elem*& root, tree_elem* nullnode, KEY key) {
	tree_elem* temp = root;
	if (temp != nullnode) {
		while (temp->list->count > 1) list_erase(temp->list, key);
		list_erase(temp->list, key);
		temp->left = nullptr;
		temp->right = nullptr;
		temp->parent = nullptr;
		temp->list = nullptr;
		delete temp;
		temp = nullptr;
	}
}

void delete_node(tree_elem*& root, tree_elem* nullnode) {
	if (root->left != nullnode) delete_node(root->left, nullnode);
	if (root->right != nullnode) delete_node(root->right, nullnode);
	delete_list(root, nullnode, root->list->data);
}

tree_elem* delete_tree(tree_elem*& root, tree_elem* nullnode)
{
	delete_node(root, nullnode);
	root = nullptr;
	return nullnode;
}

void print(tree_elem* root, tree_elem* nullnode, int h, int ln) {
	if (root != nullptr) {
		if ((root != nullnode) && (root != nullptr)) {
			print(root->right, nullnode, h + 4, ln);
			for (int i = 1; i <= h; i++) std::cout << ' ';
			print_list(root->list, root->color);
			for (int i = 0; i < ln; i++) std::cout << '\n';
			print(root->left, nullnode, h + 4, ln);
		}
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	tree_elem* root = root_init(nullnode);
	
}
