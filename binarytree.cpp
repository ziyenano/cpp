#include <iostream>
#include <stack>
#include <queue>
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
    //层次遍历二叉树
    void inorder(BTNode* T);
    //按层次遍历计算二叉树高
    int calc_height1(BTNode* T);
    //递归求解二叉树高
    int calc_height2(BTNode* T);
    //反转二叉树
    void reverse(BTNode* T);
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

void BinaryTree::inorder(BTNode* T) {
    if (T == NULL) {
        return;
    } 
    queue<BTNode*> qu;
    qu.push(T); 
    while(!qu.empty()) { 
        BTNode* P = qu.front();
        qu.pop();
        cout << P->data << endl;
        if(P->l != NULL) {
            qu.push(P->l); 
        }
        if(P->r != NULL) {
            qu.push(P->r); 
        }
    }
}

int BinaryTree::calc_height1(BTNode* T) {
    if (T == NULL) {
        return 0;
    } 
    int depth = 0;
    queue<BTNode*> qu;
    qu.push(T); 
    BTNode* level = T;
    while(!qu.empty()) { 
        BTNode* P = qu.front(); 
        qu.pop();
        if(P->l != NULL) {
            qu.push(P->l); 
        }
        if(P->r != NULL) {
            qu.push(P->r); 
        }
        if (P == level) {
            depth += 1;
            level = qu.back();
        }
    }
    return depth;
}

int BinaryTree::calc_height2(BTNode* T) {
    if (T == NULL) {
        return 0;
    } 
    int a = calc_height2(T->l);  
    int b = calc_height2(T->r);  
    return a > b ? (a+1) : (b+1);
}

void BinaryTree::reverse(BTNode* T) {
    if (T == NULL) {
       return; 
    }
    stack<BTNode*> st;
    st.push(T);
    while(!st.empty()) {
        BTNode* P = st.top();
        st.pop();
        BTNode* tmp = P->l;
        P->l = P->r;
        P->r = tmp;
        if (P->l != NULL) {
           st.push(P->l); 
        }
        if (P->r != NULL) {
           st.push(P->r); 
        }
    }
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
    cout << "=========" << endl;
    p.inorder(T);
    cout << "=========" << endl;
    cout << p.calc_height1(T) << endl;
    cout << "=========" << endl;
    cout << p.calc_height2(T) << endl;
    cout << "=========" << endl;
    p.reverse(T);
    p.inorder(T);
    return 0;
}
