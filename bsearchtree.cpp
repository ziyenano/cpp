#include <iostream>
using namespace std;
const int NIL = -1; 

//加入parent指针
typedef struct node {
    int key;
    struct node* l;
    struct node* r;
    struct node* p;
} BsNode;

class BsearchTree {
public:
    BsearchTree() {}
    void midorder(BsNode* T);
    //满二叉树形式构造树
    BsNode* createtree(BsNode* P, int* arr, int idx, int size);
    //利用insert函数构造
    BsNode* createtree(int* arr, int size);
    BsNode* search(BsNode* T, int key);
    BsNode* miniumn(BsNode* T);
    BsNode* maxiumn(BsNode* T);
    BsNode* successor(BsNode* T);
    int insert(BsNode* T, BsNode* z);
    int del(BsNode* T, BsNode* z);
private:
    //用root为v的子树替换root为u的子树
    int transplant(BsNode* T, BsNode* u, BsNode* v);
};

void BsearchTree::midorder(BsNode* T) {
    if (T != NULL) {
        midorder(T->l);
        cout << T->key << endl;
        midorder(T->r);
    }
}

BsNode* BsearchTree::createtree(BsNode* P, int* arr, int idx, int size) {
    if (arr[idx] == NIL || idx >= size) {
        return NULL;
    }
    BsNode* T = new BsNode;
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    T-> key = arr[idx];
    T->p = P; 
    T->l = createtree(T, arr, l, size);
    T->r = createtree(T, arr, r, size);
    return T;
}

BsNode* BsearchTree::createtree(int* arr, int size) {
   BsNode* T = NULL; 
   if (arr == NULL) {
      return NULL; 
   } 
   for (int i = 0; i < size; ++i) {
       BsNode* z = new BsNode; 
       z->key = arr[i];
       z->l = NULL;
       z->r = NULL;
       if (insert(T, z) == 1) {
           T = z;
       }  
   }
   return T; 
}

BsNode* BsearchTree::search(BsNode* T, int key) {
    while (T != NULL && T->key != key) {
        if (key < T->key) {
            T = T->l; 
        } else {
            T = T->r; 
        }
    }
    return T;
}

BsNode* BsearchTree::maxiumn(BsNode* T) {
    while (T->r != NULL) {
        T = T->r;
    }
    return T;
}

BsNode* BsearchTree::miniumn(BsNode* T) {
    while (T->l != NULL) {
        T = T->l;
    }
    return T;
}

BsNode* BsearchTree::successor(BsNode* T) {
    if (T->r != NULL) {
       return maxiumn(T->r); 
    }
    BsNode* P = T->p;
    //如果右孩子节点为空, 后继是T的最底层祖先节点R, 
    //且R的左孩子也是T的祖先节点
    //因此, 沿着T往上找, 找到一个节点是父节点(R)的左孩子.
    while (P != NULL && T == P->r) {
        T = P;
        P = P->p;
    }
    return P;
}

int BsearchTree::insert(BsNode* T, BsNode* z) {
    BsNode* tmp = NULL;
    while (T != NULL) {
        tmp = T;
        if (z->key < T->key) {
            T = T->l; 
        } else {
            T = T->r;
        }
    }
    //链接上父节点指针
    z->p = tmp;
    //空树的情况
    if (tmp == NULL) {
        return 1;
    }

    if (z->key < tmp->key) {
        tmp->l = z; 
    } else {
        tmp->r = z;
    }
    return 0;
}

int BsearchTree::transplant(BsNode* T, BsNode* u, BsNode* v) {
    //u为树T的根节点
    if (u->p == NULL) {
       T = v; 
       return 0;
    } else if (u == u->p->l) {
       u->p->l = v; 
    } else {
       u->p->r = v; 
    }
    //还需要替换父节点
    if (v != NULL) {
       v->p = u->p; 
    }
    return 0;
}

int BsearchTree::del(BsNode* T, BsNode* z) {
    //1.左子树为空, 直接替换
    if (z->l == NULL) {
        transplant(T, z, z->r); 
    } else if (z->r == NULL) {
    //2.左子树不为空, 右子树为空
        transplant(T, z, z->l); 
    } else {
        //找到后继(右子树不为空)
        BsNode* y = miniumn(z->r); 
        //如果y不是z的右孩子(y的左孩子一定为空)
        //用y的右孩子替换y; y的右孩子变为z的右孩子
        if (y->p != z) {
            transplant(T, y, y->r); 
            y->r = z->r;
            z->r->p = y;
        }
        //用y节点替换z节点
        transplant(T, z, y);
        y->l = z->l;
        z->l->p = y;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    BsearchTree obj = BsearchTree();
    int arr[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9}; 
    int size = sizeof(arr) / sizeof(int);
    //insert方式生成二叉树
    BsNode* T = obj.createtree(arr, size); 
    obj.midorder(T);
    cout << "=========" << endl;
    cout << obj.maxiumn(T)->key <<endl;
    cout << obj.miniumn(T)->key <<endl;
    cout << "successor of key 13: " << obj.successor(obj.search(T, 13))->key <<endl;
    cout << "=========" << endl;
    BsNode* z = new BsNode;
    z->key = 10;
    z->l = NULL;
    z->r = NULL;
    obj.insert(T, z); 
    obj.midorder(T);
    cout << "=========" << endl;
    obj.del(T, obj.search(T, 13)); 
    obj.midorder(T);
    cout << "=========" << endl;
    return 0;
}
