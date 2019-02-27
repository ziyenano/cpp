#include <iostream>
using namespace std;

struct node {
    node* next;
    int data;
};

class List {
public:
    List() {}
    node* create(int* arr, int size);
    node* reverse(node* P);
    void print(node* P);
};

node* List::create(int* arr, int size) {
    node* P = new node;
    node* P0 = P; 
    for (int i = 0; i < size-1; ++i) {
        P->data = arr[i];        
        node* Pn = new node;
        P->next = Pn;
        P = Pn;
    }
    P->data = arr[size-1];
    P->next = NULL;
    return P0;
}

node* List::reverse(node* P) {
    node* pb = NULL;
    //若改为P!=NULL, 最后返回pb即可
    while (P->next != NULL) {
        node* pn = P->next;
        P->next = pb;
        pb = P;
        P = pn;
    } 
    P->next = pb;
    return P;
}

void List::print(node* P) {
    while (P!= NULL) {
        cout << P->data << endl;
        P = P->next;
    }
}

int main(int argc, char *argv[]) {
    int arr[] = {3, 6, 10, 20, 5, 3}; 
    List obj = List();
    node* P = obj.create(arr, sizeof(arr) / sizeof(int));
    obj.print(P);
    cout << "==============" << endl;
    node* Pr = obj.reverse(P);
    obj.print(Pr);
    return 0;
}
