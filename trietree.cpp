#include <iostream>
#include <string>
using namespace std;
const int SIZE = 26;

struct node {
    char word;
    struct node* child[SIZE];
    bool isend;
    node() {
        for (int i = 0; i < SIZE; ++i) {
            child[i] = NULL; 
        }
        isend = false;
    }
};

typedef struct node TRnode;

class TrieTree {
public:
    TrieTree() {}
    TRnode* init() {
        TRnode* root = new TRnode;
        return root;
    }
    int insert(TRnode* T, string s);
    TRnode* search(TRnode* T, string s);
    int rec_print(TRnode* T, string s);
    int search_prefix(TRnode* T, string s);
};

int TrieTree::insert(TRnode* T, string s) {
    for (int i = 0; i < s.size(); ++i) {
        int idx = s[i] - 'a';
        if (T->child[idx] == NULL) {
            TRnode* P = new TRnode;
            T->child[idx] = P;
            P->word = s[i]; 
        }
        T = T->child[idx];
    }    
    T->isend = true;
    return 0;
}

TRnode* TrieTree::search(TRnode* T, string s) {
    for (int i = 0; i < s.size(); ++i) {
        int idx = s[i] - 'a';
        if (T->child[idx] != NULL) {
            T = T->child[idx];
        } else {
            return NULL;
        }
    }
    return T;
}

int TrieTree::search_prefix(TRnode* T, string s) {
    TRnode* P = search(T, s);
    if (P == NULL) {
       cout << "no prefix " << s << endl; 
       return -1;
    }
    rec_print(P, s);
    return 0;
}

int TrieTree::rec_print(TRnode* T, string s) {
    if (T->isend) {
       cout << s << endl; 
       return 0;
    }      
    //递归打印字符串, 效率有问题
    for (int i = 0; i < SIZE; ++i) {
       if (T->child[i] != NULL) {
          rec_print(T->child[i], s + T->child[i]->word);
       } 
    }
    return 0;
}

int main(int argc, char *argv[]) {
    TrieTree obj = TrieTree();        
    TRnode* R = obj.init();
    obj.insert(R, "apple");
    obj.insert(R, "apart");
    obj.insert(R, "add");
    obj.insert(R, "cash");
    obj.insert(R, "cat");
    obj.search_prefix(R, "ap");
    return 0;
}
