#include <iostream>
#include "b-tree.h"

int main() {
    std::ios_base::sync_with_stdio(false);

    TBTree btree;
    char input[257]; //Also serves as key and file pathway reader
    unsigned long long value;
	char file_name[1000];

	while(std::cin >> input) {
		switch (input[0]) {
		case '+' :
			std::cin >> input;
			std::cin >> value;
			btree.Insert(input, value);
			break;
		
		case '-' :
			std::cin >> input;
			btree.Delete(input);
			break;
		
		case '!' :
			std::cin >> input;
			std::cin >> file_name;
			if (input[0] == 'S') {
				btree.Save(file_name);
			} else if (input[0] == 'L') {
				btree.Load(file_name);
			}
			break;
		
		default :
			btree.Search(input);
			break;	
		}
	}

	return 0;
}