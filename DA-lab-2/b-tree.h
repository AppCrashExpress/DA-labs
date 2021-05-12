#ifndef B_TREE_H
#define B_TREE_H

#include <iostream>

const short MAX_LENGTH = 257;
struct TPair {
    char key[MAX_LENGTH] = {};
    unsigned long long data;
};

const int T_COEF = 3; //This is the 't' coefficient of B-Tree
//Picking 't' < 2 will result in undefined behaviour

class TBTreeNode {
    friend class TBTree;

    TBTreeNode() { }
    TBTreeNode(TPair);

    void Search(char*);

    void Split(int);
    void Insert(char*, unsigned long long);

    TPair PredecessorKey();
    TPair SuccessorKey();
    void MergePremature(int&);
    void Merge(int, char*);
    bool Delete(char*);

    void Save(std::ofstream&);
    void Load(std::ifstream&);

    void Wipe(void);

    TPair keys[2 * T_COEF - 1];
    TBTreeNode *child[2 * T_COEF];

    bool leaf = true;
    int keysLast = -1;
};


class TBTree {
public:
    TBTree() {
        root = new TBTreeNode;
    }

    ~TBTree() {
        Destroy();
    }

    void Search(char*);
    void Insert(char*, unsigned long long);
    void Delete(char*);

    void Save(char*);
    void Load(char*);
    
    void Destroy();

private:
    void Save(std::ofstream&);
    void Load(std::ifstream&);
    TBTreeNode *root;
};


#endif
