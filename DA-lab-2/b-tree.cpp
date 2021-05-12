#include "b-tree.h"

#include <fstream>
#include <cstring>
#include <exception>

const short CHAR_OFFSET = 32;
void ToLower(char *str) {
    if (str == nullptr) throw std::logic_error("ERROR: Empty string recieved in ToLower");

    for(int i = 0; str[i] != '\0'; ++i) {
        if( str[i] >= 'A' && str[i] <= 'Z' )
            { str[i] += CHAR_OFFSET; }
    }
}

TBTreeNode::TBTreeNode(TPair firstAdd) {
    keys[0] = firstAdd;
    keysLast = 0;
}

void TBTree::Search (char *key) {
    ToLower(key);
    if (root->keysLast == -1) {
        std::cout << "NoSuchWord" << std::endl;
        return;
    }
    root->Search(key);
}

void TBTreeNode::Search(char *key) {
    int i = 0;
    char *current = keys[i].key;
    while ((strcmp(key, current)) > 0) {
        ++i; 
        if (i > keysLast) break;
        current = keys[i].key;
    }

    if (strcmp(key, current) == 0) {
        std::cout << "OK: " << keys[i].data << std::endl;
    }

    else if (leaf) {
        std::cout << "NoSuchWord" << std::endl;
    }

    else child[i]->Search(key);

    return;
}

void TBTreeNode::Split(int index) {
    if (keysLast == -1) {
        throw std::logic_error("ERROR: Entered a node with no elements");
    }

    leaf = false;
        
    TBTreeNode* left  = child[index];
    TBTreeNode* right = new TBTreeNode;

    left->keysLast = right->keysLast = T_COEF - 2;
    right->leaf = left->leaf;

    for (int i = 0; i < T_COEF - 1; ++i) {
        right->keys[i]  = left->keys[i + T_COEF]; 
        right->child[i] = left->child[i + T_COEF]; 
    }
    right->child[T_COEF - 1] = left->child[2*T_COEF - 1];

    for (int j = keysLast + 1; j > index; --j) {
        keys[j] = keys[j - 1];
        child[j + 1] = child[j];
    }
    keys[index] = left->keys[T_COEF - 1];
    ++keysLast;
    child[index + 1] = right;           
}

void TBTreeNode::Insert (char *key, unsigned long long data) {
    if (keysLast == -1) {
        throw std::logic_error("ERROR: Entered a node with no elements");
    }

    int i = 0;
    char *current = keys[i].key;
    while ((strcmp(key, current)) > 0) {
        ++i; 
        if (i > keysLast) {
            break;
        }
        current = keys[i].key;
    }

    if (strcmp(key, current) == 0) {
        std::cout << "Exist" << std::endl;

    } else if (leaf) {
        for (int j = keysLast + 1; j > i; --j) {
            keys[j] = keys[j - 1];
        }

        memcpy(keys[i].key, key, sizeof(char[MAX_LENGTH]));
        keys[i].data = data;
        ++keysLast;
        std::cout << "OK" << std::endl;

    } else if (child[i]->keysLast == 2 * T_COEF - 2) {
        Split(i);
        
        if ((strcmp(key, keys[i].key)) == 0) {
            std::cout << "Exist" << std::endl;

        } else if ((strcmp(key, keys[i].key)) > 0) {
            child[i + 1]->Insert(key, data);
        
        } else child[i]->Insert(key, data);

    } else child[i]->Insert(key, data);

    return;
}

void TBTreeNode::MergePremature(int &index) {
    TBTreeNode *kid = child[index];
    int &kidKeys = kid->keysLast;

    if (index > 0) {
        //Pick a left sibling of child[i]
        TBTreeNode *left = child[index - 1];
        int &leftKeys = left->keysLast;

        if (leftKeys + 1 > T_COEF - 1) {
            for (int i = kidKeys + 1; i > 0; --i) {
                kid->keys[i] = kid->keys[i - 1];
                kid->child[i + 1] = kid->child[i];
            }
            kid->child[1] = kid->child[0];
            ++kidKeys;
            kid->keys[0] = keys[index - 1];
            kid->child[0] = left->child[leftKeys + 1];

            keys[index - 1] = left->keys[leftKeys];
            --leftKeys;

        } else {
            --index; // When we delete left key of root, index moves left as well

            ++leftKeys;
            left->keys[leftKeys] = keys[index];

            for (int i = 0; i < T_COEF - 1; ++i) {
                ++leftKeys;
                left->keys[leftKeys] = kid->keys[i];
                left->child[leftKeys] = kid->child[i];
            }
            left->child[leftKeys + 1] = kid->child[kidKeys + 1];
            delete kid;

            for (int i = index; i < keysLast; ++i) {
                keys[i] = keys[i + 1];
                child[i + 1] = child[i + 2];
            }
            --keysLast;
        }
    } else {
        //Pick a right sibling of child[i]
        TBTreeNode* right = child[index + 1];
        int &rightKeys = right->keysLast;

        if (rightKeys + 1 > T_COEF - 1) {
            ++kidKeys;
            kid->keys[kidKeys] = keys[index];
            kid->child[kidKeys + 1] = right->child[0];
            keys[index] = right->keys[0];

            for (int i = 0; i < rightKeys; ++i) {
                right->keys[i] = right->keys[i + 1];
                right->child[i] = right->child[i + 1];
            }
            right->child[rightKeys] = right->child[rightKeys + 1];
            --rightKeys;
        }
        else {
            ++kidKeys;
            kid->keys[kidKeys] = keys[index];

            for (int i = 0; i < T_COEF - 1; ++i) {
                ++kidKeys;
                kid->keys[kidKeys] = right->keys[i];
                kid->child[kidKeys] = right->child[i];
            }
            kid->child[kidKeys + 1] = right->child[rightKeys + 1];
            delete right;

            for (int i = index; i < keysLast; ++i) {
                keys[i] = keys[i + 1];
                child[i + 1] = child[i + 2];
            }
            --keysLast;
        }
    }
}

TPair TBTreeNode::PredecessorKey() {
    if (leaf) {
        return keys[keysLast];        
    }
    return child[keysLast + 1]->PredecessorKey();
}

TPair TBTreeNode::SuccessorKey() {
    if (leaf) {
        return keys[0];        
    }
    return child[0]->SuccessorKey();
}

void TBTreeNode::Merge(int index, char *key) {
    if (child[index]->keysLast + 1 > T_COEF - 1) {
        TPair predecessor = child[index]->PredecessorKey();
        keys[index] = predecessor;
        child[index]->Delete(predecessor.key);

    } else if (child[index + 1]->keysLast + 1 > T_COEF - 1) {
        TPair successor = child[index + 1]->SuccessorKey();
        keys[index] = successor;
        child[index + 1]->Delete(successor.key);

    } else {
        TBTreeNode *left  = child[index];
        TBTreeNode *right = child[index + 1];
        int &leftKeys  = left->keysLast;
        int &rightKeys = right->keysLast;

        ++leftKeys;
        left->keys[leftKeys] = keys[index];

        for (int i = 0; i < T_COEF - 1; ++i) {
            ++leftKeys;
            left->keys[leftKeys] = right->keys[i];
            left->child[leftKeys] = right->child[i];
        }
        left->child[leftKeys + 1] = right->child[rightKeys + 1];
        delete right;

        for (int i = index; i < keysLast; ++i) {
            keys[i] = keys[i + 1];
            child[i + 1] = child[i + 2];
        }
        --keysLast;

        left->Delete(key);
    }
}

bool TBTreeNode::Delete(char *key) {
    int i = 0;
    char *current = keys[i].key;
    while ((strcmp(key, current)) > 0) {        
        ++i; 
        if (i > keysLast) break;
        current = keys[i].key;
    }

    if (strcmp(key, current) == 0) {
        if (leaf) {
            for (int j = i; j < keysLast; ++j) {
                keys[j] = keys[j + 1];
            }
        --keysLast;
        } else {
            Merge(i, key);
        }
        return true;
    }

    else {
        if (leaf) {
            return false;
        } else {
            if (child[i]->keysLast + 1 == T_COEF - 1) {
                MergePremature(i);
            }
            return child[i]->Delete(key);
        }
    }
}

void TBTree::Insert (char *key, unsigned long long data) {
    ToLower(key);
    //There are 2 * T_COEF - 1 keys, and keysLast points to the last key in the array of keys in a computer presentation, so max index is (2 * T_COEF - 1) - 1
    if (root->keysLast == 2 * T_COEF - 2) {
        TBTreeNode* newRoot = new TBTreeNode(root->keys[T_COEF - 1]); //I need an [(2 * T_COEF - 1)/2] element, which has the same result (after experimenting)
        TBTreeNode* right   = new TBTreeNode;

        root->keysLast = right->keysLast = T_COEF - 2;
        right->leaf = root->leaf;

        for (int i = T_COEF, j = 0, maxKeys = 2 * T_COEF - 1; i < maxKeys; ++i, ++j) {
            right->keys[j]  = root->keys[i]; 
            right->child[j] = root->child[i]; 
        }
        //j goes down to (2 * T_COEF - 1) - T_COEF = (T_COEF - 1), so the last index is T_COEF - 1
        right->child[T_COEF - 1] = root->child[2*T_COEF - 1];

        newRoot->child[0] = root;
        newRoot->child[1] = right;
        root = newRoot;
        root->leaf = false;
    } else if (root->keysLast == -1) {
        memcpy(root->keys[0].key, key, sizeof(char[MAX_LENGTH]));
        root->keys[0].data = data;
        ++root->keysLast;
        std::cout << "OK" << std::endl;
        return;
    }
    
    //We are ensured that we have at least one element with previous "else if"
    root->Insert(key, data);
}

void TBTree::Delete(char *key) {
    ToLower(key);

    if (root->keysLast == -1) {
        std::cout << "NoSuchWord" << std::endl;
        return;
    }

    if (root->Delete(key)) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "NoSuchWord" << std::endl;
    }

    if (root->keysLast == -1 && !root->leaf) {
        TBTreeNode *trash = root;
        root = root->child[0];
        delete trash;
    }
}

void TBTree::Save(char *path) {
    std::ofstream outfile;
    outfile.open(path, std::ios::out);
    if (!outfile.is_open()) {
        std::cout << "ERROR: Failed to open file" << std::endl;
        return;
    }
    Save(outfile);
    outfile.close();
    std::cout << "OK" << std::endl;
}

void TBTree::Save(std::ofstream &os) {
    if (root == nullptr || root->keysLast == -1) {
        os << '0' << '\t';
        return;
    }
    
    os << '1' << '\t';
    root->Save(os);
}

void TBTreeNode::Save(std::ofstream &os) {
    os << leaf << '\t';
    os << keysLast << '\t';

    for (int i = 0; i <= keysLast; ++i) {
        os << keys[i].key << '\t';
        os << keys[i].data << '\t';
    }

    if (!leaf) {
        for (int i = 0; i <= keysLast + 1; ++i) {
            child[i]->Save(os);
        }
    }
}

void TBTree::Load(char *path) {
    std::ifstream infile;
    infile.open(path, std::ios::in);
    if (!infile.is_open()) {
        std::cout << "ERROR: Failed to open file" << std::endl;
        return;
    }
    if (infile.peek() == EOF) {
        std::cout << "ERROR: File empty" << std::endl;
        infile.close();
        return;
    }
    Load(infile);
    infile.close();
    std::cout << "OK" << std::endl;
}

void TBTree::Load(std::ifstream &is) {
    Destroy();
    root = new TBTreeNode;

    int hasRoots;
    is >> hasRoots;
    if (hasRoots != 1) { 
         return;
    }

    root->Load(is);
}

void TBTreeNode::Load(std::ifstream &is) {
    is >> leaf;
    is >> keysLast;

    int i;
    for (i = 0; i <= keysLast; ++i) {
        is >> keys[i].key;
        is >> keys[i].data;
    }

    if (!leaf) {
        for (i = 0; i <= keysLast + 1; ++i) {
            child[i] = new TBTreeNode;
            child[i]->Load(is);
        }
    }
}

void TBTree::Destroy() {
    if (root != nullptr) {
        root->Wipe();
        root = nullptr;
    }
}

void TBTreeNode::Wipe() {
    if (!leaf) {
        for (int i = 0; i <= keysLast + 1; ++i) {
            child[i]->Wipe();
        }
    }
    delete this;
}