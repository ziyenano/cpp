#include <iostream>
#include <stack>
using namespace std;

const char NA = '?';
typedef struct node {
    char data;
    struct node* l;
    struct node* r;
} BTNode; 

class BinaryTree {
public:
    BinaryTree() {}
    BTNode* createtree(char arr[], int idx, int size); 
    void midorder(BTNode* T);
    void preorder(BTNode* T);
    void postorder(BTNode* T);
    void midorder_norec(BTNode* T);
};

BTNode* BinaryTree::createtree(char arr[], int idx, int size) {
    if (arr[idx] == NA || idx >= size) {
        return NULL;
    }
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    BTNode* T = new BTNode;
    T->data = arr[idx];
    T->l = createtree(arr, l, size);
    T->r = createtree(arr, r, size);
    return T;
}

void BinaryTree::midorder(BTNode* T) {
    if (T == NULL) {
        return;
    }
    midorder(T->l);
    cout << T->data << endl;
    midorder(T->r);
}

void BinaryTree::midorder_norec(BTNode* T) {
    stack<BTNode*> st;
    BTNode* P = T;
    bool status = true;
    while (status) {
        while (P != NULL) {
           st.push(P); 
           P = P->l;
        }
        if (st.empty()) {
            status = false;
        } else {
            P = st.top();
            st.pop();
            cout << P->data << endl; 
            P = P->r;
        }
    }
}

void BinaryTree::preorder(BTNode* T) {
    if (T == NULL) {
        return;
    }
    cout << T->data << endl;
    preorder(T->l);
    preorder(T->r);
}

void BinaryTree::postorder(BTNode* T) {
    if (T == NULL) {
        return;
    }
    postorder(T->l);
    postorder(T->r);
    cout << T->data << endl;
}

int main(int argc, char *argv[]) {
    //数组为满二叉树
    char arr[] = {'a', 'b', 'c', NA, 'd', 'e', NA, NA, NA, 'f', 'g'}; 
    BinaryTree p = BinaryTree();
    BTNode* T = p.createtree(arr, 0, sizeof(arr) / sizeof(char));
    p.midorder(T);
    cout << "=========" << endl;
    p.midorder_norec(T);
    cout << "=========" << endl;
    p.preorder(T);
    cout << "=========" << endl;
    p.postorder(T);
    return 0;
}
