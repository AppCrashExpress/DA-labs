#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

bool equal(const char *str1, const char *str2){
	if(str1 == nullptr || str2 == nullptr){
		return false;
	}
	int i = 0;
	while(str1[i] != '\0' && str2[i] != '\0'){
		if(str1[i] != str2[i]){
			return false;
		}
		i++;
	}
	if(str1[i] == '\0' && str2[i] != '\0'){
		return false;
	}
	if(str2[i] == '\0' && str1[i] != '\0'){
		return false;
	}
	return true;
}

void to_lower_case(char *str){
	if(str == nullptr){
		return;
	}
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = 'a' + str[i] - 'A';
		}
	}
}

struct myStructure{
	char word[257];
	unsigned long long number;
};

std::ostream &operator<<(std::ostream &os, myStructure* &st){
    os << st->word << ": " << st->number;
    return os;
}

std::istream &operator>>(std::istream &is, myStructure* &st){
	st = new myStructure;
    is >> st->word;
    is >> st->number;
    return is;
}

struct node{
	node *left;
	node *right;
	node *parent;

	myStructure *key;
	int height;
};

class avl_tree{
public:
	avl_tree(): root(nullptr){}

	~avl_tree(){
		destroy_tree(root);
		root = nullptr;
	}

	void add(myStructure* &st){
		to_lower_case(st->word);
		if(root != nullptr){
			rebalance(add(st, root));
		}else{
			root = new node;
			root->left = root->right = nullptr;
			root->parent = nullptr;
			root->key = st;
			root->height = 1;
			std::cout << "OK\n";
		}
	}

	void find(char *str){
		to_lower_case(str);
		find(root, str);
	}

	void remove(char *str){
		to_lower_case(str);
		remove(root, str);
	}

	void save(char *file){
		std::ofstream ostr(file);
		if(ostr.is_open()){
			save(root, ostr);
			ostr.close();
			std::cout << "OK\n";
		}else{
			std::cout << "ERROR: can not open file to save tree\n";
		}

	}
	void load(char *file){
		std::ifstream istr(file);
		if(istr.is_open()){
			destroy_tree(root);
			root = load(istr);
			istr.close();
			std::cout << "OK\n";
		}else{
			std::cout << "Error: can not open file to load tree\n";
		}
	}

	void print(){
		print_tree(root);
		std::cout << "\n";
	}

private:
	node *root;

	node *add(myStructure* &st, node *n){
		int string_diff = strcmp(st->word, n->key->word);
		if(string_diff < 0){
			if(n->left == nullptr){
				n->left = new node;
				n->left->left = n->left->right = nullptr;
				n->left->parent = n;
				n->left->key = st;
				n->left->height = 1;
				std::cout << "OK\n";
				return n->left;
			}else{
				return add(st, n->left);
			}
		}else if(string_diff > 0){
			if(n->right == nullptr){
				n->right = new node;
				n->right->left = n->right->right = nullptr;
				n->right->parent = n;
				n->right->key = st;
				n->right->height = 1;
				std::cout << "OK\n";
				return n->right;
			}else{
				return add(st, n->right);
			}
		}else{
			delete st;
			std::cout << "Exist\n";
			return nullptr;
		}
	}

	void print_tree(node *n){
		static int l = 0;

		if(n != NULL){
			l++;
			print_tree(n->right);
			for(int i = 1; i < l; i++){
				std::cout << "\t";
			}
			std::cout << "\\__" <<  n->key << std::endl;
			print_tree(n->left);
			l--;
		}
	}

	void destroy_tree(node *n){
		if(n != nullptr){
			destroy_tree(n->left);
			n->left = nullptr;
			destroy_tree(n->right);
			n->right = nullptr;
			n->parent = nullptr;
			delete n->key;
			delete n;
		}
	}

	void rebalance(node *n){
		while(n != nullptr){
			n->height = get_max_height(n->left, n->right)+1;
			int diff = get_diff(n->left, n->right);
			if(diff == -2){
				switch(get_diff(n->right->left, n->right->right)){
					case -1:
					case 0:
						left_rotate(n, n->right, n->right->left);
						break;
					case 1:
						big_left_rotate(n, n->right, n->right->left, n->right->left->left, n->right->left->right);
						break;
				}
			}else if(diff == 2){
				switch(get_diff(n->left->left, n->left->right)){
					case 0:
					case 1:
						right_rotate(n, n->left, n->left->right);
						break;
					case -1:
						big_right_rotate(n, n->left, n->left->right, n->left->right->left, n->left->right->right);
						break;
				}
			}
			root = n;
			n = n->parent;
		}
	}

	void left_rotate(node *x, node *y, node *beta){
		if(x->parent != nullptr){
			if(x->parent->left == x){
				x->parent->left = y;
			}else{
				x->parent->right = y;
			}
		}
		y->parent = x->parent;
		x->right = beta;
		if(beta != nullptr){
			beta->parent = x;
		}
		y->left = x;
		x->parent = y;
		x->height = get_max_height(x->left, x->right)+1;
		y->height = get_max_height(y->left, y->right)+1;
	}

	void right_rotate(node *x, node *y, node *beta){
		if(x->parent != nullptr){
			if(x->parent->left == x){
				x->parent->left = y;
			}else{
				x->parent->right = y;
			}
		}
		y->parent = x->parent;
		x->left = beta;
		if(beta != nullptr){
			beta->parent = x;
		}
		y->right = x;
		x->parent = y;
		x->height = get_max_height(x->left, x->right)+1;
		y->height = get_max_height(y->left, y->right)+1;
	}

	void big_left_rotate(node *x, node *y, node *z, node *beta, node *gamma){
		z->left = x;
		z->right = y;
		
		if(x->parent != nullptr){
			if(x->parent->left == x){
				x->parent->left = z;
			}else{
				x->parent->right = z;
			}
		}
		z->parent = x->parent;
		x->right = beta;
		if(beta != nullptr){
			beta->parent = x;
		}
		y->left = gamma;
		if(gamma != nullptr){
			gamma->parent = y;
		}
		x->parent = z;
		y->parent = z;
		x->height = get_max_height(x->left, x->right)+1;
		y->height = get_max_height(y->left, y->right)+1;
		z->height = get_max_height(z->left, z->right)+1;
	}

	void big_right_rotate(node *x, node *y, node *z, node *beta, node *gamma){
		z->left = y;
		z->right = x;
		if(x->parent != nullptr){
			if(x->parent->left == x){
				x->parent->left = z;
			}else{
				x->parent->right = z;
			}
		}
		z->parent = x->parent;
		y->right = beta;
		if(beta != nullptr){
			beta->parent = y;
		}
		x->left = gamma;
		if(gamma != nullptr){
			gamma->parent = x;
		}
		y->parent = z;
		x->parent = z;
		x->height = get_max_height(x->left, x->right)+1;
		y->height = get_max_height(y->left, y->right)+1;
		z->height = get_max_height(z->left, z->right)+1;
	}

	int get_max_height(const node *left, const node *right){
		if(left == nullptr && right == nullptr){
			return 0;
		}
		if(left == nullptr){
			return right->height;
		}
		if(right == nullptr){
			return left->height;
		}
		return std::max(left->height, right->height);
	}

	int get_diff(const node *left, const node *right){
		if(left == nullptr && right == nullptr){
			return 0;
		}
		if(left == nullptr){
			return -(right->height);
		}
		if(right == nullptr){
			return left->height;
		}
		return left->height - right->height;
	}

	void find(const node *n, char *str){
		if(n == nullptr){
			std::cout << "NoSuchWord\n";
			return;
		}
		int string_diff = strcmp(str, n->key->word);
		if(string_diff < 0){
			find(n->left, str);
		}else if(string_diff > 0){
			find(n->right, str);
		}else{
			std::cout << "OK: " << n->key->number << '\n';
		}
	}

	void remove(node *n, char *str){
		if(n == nullptr){
			std::cout << "NoSuchWord\n";
			return;
		}
		int string_diff = strcmp(str, n->key->word);
		if(string_diff < 0){
			remove(n->left, str);
		}else if(string_diff > 0){
			remove(n->right, str);
		}else{
			if(n->left == nullptr && n->right == nullptr){
				if(n->parent == nullptr){
					delete n->key;
					delete n;
					root = nullptr;
				}else{
					if(n->parent->left == n){
						n->parent->left = nullptr;
					}else{
						n->parent->right = nullptr;
					}
					rebalance(n->parent);
					delete n->key;
					delete n;
				}
				
			}else if(n->left == nullptr){
				node *temp = n->right;
				while(temp->left != nullptr){
					temp = temp->left;
				}
				if(temp->right != nullptr){
					temp->right->parent = temp->parent;	
				}
				if(temp->parent->left  == temp){
					temp->parent->left = temp->right;
				}else{
					temp->parent->right = temp->right;
				}
				std::swap(temp->key, n->key);
				rebalance(temp->parent);
				delete temp->key;
				delete temp;
			}else{
				node *temp = n->left;
				while(temp->right != nullptr){
					temp = temp->right;
				}
				if(temp->left != nullptr){
					temp->left->parent = temp->parent;
				}
				if(temp->parent->left  == temp){
					temp->parent->left = temp->left;
				}else{
					temp->parent->right = temp->left;
				}
				std::swap(temp->key, n->key);
				rebalance(temp->parent);
				delete temp->key;
				delete temp;
			}
			std::cout << "OK\n";
		}
	}

	void save(node *n, std::ofstream &os){
		if(n == nullptr){
			return;
		}
		
		os << n->key->word << '\t';
		os << n->key->number << '\t';
		os << n->height << '\t';

		bool has_left = (n->left != nullptr);
		bool has_right = (n->right != nullptr);

		os << has_left << '\t';
		os << has_right << '\t';

		if(has_left){
			save(n->left, os);
		}

		if(has_right){
			save(n->right, os);
		}
	}

	node *load(std::ifstream &is){
		node *n = new node;
		n->key = new myStructure;

		if(!(is >> n->key->word)){
			return n;
		}

		is >> n->key->number;
		is >> n->height;

		bool has_left = false;
		bool has_right = false;

		is >> has_left;
		is >> has_right;

		if(has_left){
			n->left = load(is);
			n->left->parent = n;
		}else{
			n->left = nullptr;
		}

		if(has_right){
			n->right = load(is);
			n->right->parent = n;
		}else{
			n->right = nullptr;
		}

		n->parent = nullptr;
		return n;
	}
};

int main(){
	std::ios_base::sync_with_stdio(false);

	avl_tree tree;
	myStructure *st;
	char action[257];
	char file_name[1000];
	/*
	int k;
	std::cin >> k;
	for(int i = 0; i < k; i++){
		std::cin >> st;
		tree.add(st);
	}
	//tree.print();
	for(int i = 0; i < k; i++){
		std::cin >> action;
		tree.remove(action);
	}
	return 0;
	*/
	while(std::cin >> action){
		switch(action[0]){
			case '+':
				std::cin >> st;
				tree.add(st);
				break;
			case '-':
				std::cin >> action;
				tree.remove(action);
				break;
			case '!':{
				std::cin >> action;
				std::cin >> file_name;
				if(action[0] == 'S'){
					//Save
					tree.save(file_name);
				}else{
					//Load
					tree.load(file_name);
				}
				break;
			}
			default:
				tree.find(action);
				break;	
		}
	}
}