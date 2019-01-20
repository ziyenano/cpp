#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;
const int MaxNum = 100;
const int MaxInsert = 1E9;

typedef struct node {
    int freq;
    string s;
    struct node* l;
    struct node* r;
} HNode; 

typedef pair<string, string> Code;

class Huffman {
public:
    Huffman(HNode* W, int _size);
    void heapify(int p);
    void buildheap();
    void decrease(int p, int freq);
    void insert(HNode* T);
    HNode* extract_min();
    HNode* buildhuffman();
    //递归生成编码
    void gencode(HNode* T, string encode);
    inline void printhuff () {
        for (int i = 0; i < _size; ++i) {
            cout << Q[i]->s << ": " << Q[i]->freq << endl;
        }
    }
    vector<Code> _code;
private:
    HNode* Q[MaxNum];
    int _size;
    inline int Left(int i) {
        return 2 * i + 1;
    }

    inline int Right(int i) {
        return 2 * i + 2;
    }

    inline int Parent(int i) {
        return (i+1) / 2 - 1;
    }
    
    inline void swap(int i, int j) {
        HNode* tmp = Q[i];
        Q[i] = Q[j];
        Q[j] = tmp;
    }
};

Huffman::Huffman(HNode* W, int size) {
    _size = size;
    for (int i = 0; i < size; ++i) {
        Q[i] = W+i;    
    }
}

void Huffman::heapify(int p) {
    int l = Left(p);    
    int r = Right(p);    
    int miniumn = p;
    if (l < _size && Q[l]->freq < Q[p]->freq) {
        miniumn = l; 
    }
    if (r < _size && Q[r]->freq < Q[miniumn]->freq) {
        miniumn = r; 
    }
    if (miniumn != p) {
        swap(p, miniumn);
        heapify(miniumn);    
    }
}

void Huffman::buildheap() {
    for (int i =  _size / 2 - 1; i >= 0; --i) {
        heapify(i); 
    }
}

void Huffman::decrease(int p, int freq) {
    if (freq > Q[p]->freq) {
        cout << "error" << endl;
        return;
    }
    Q[p]->freq = freq;
    while (p > 0 && Q[p]->freq < Q[Parent(p)]->freq) {
        heapify(Parent(p));
        p = Parent(p);
    }
}


void Huffman::insert(HNode* T) {
    int tmp = T->freq;
    T->freq = MaxInsert;
    //需要将_size扩大后执行decrease操作
    _size += 1;
    Q[_size-1] = T;
    decrease(_size - 1, tmp);
}

HNode* Huffman::extract_min() {
    return Q[0];
}

HNode* Huffman::buildhuffman() {
    buildheap();
    int size = _size;
    //huffman tree需要size-1次合并
    for (int i = 0; i < size - 1; ++i) {
        HNode* z = new HNode; 
        HNode* l = extract_min();
        swap(0, _size - 1);
        _size -= 1;
        heapify(0);
        HNode* r = extract_min();
        swap(0, _size - 1);
        _size -= 1;
        heapify(0);
        z->l = l;
        z->r = r;
        z->freq = l->freq + r->freq;
        insert(z);
    }
    return extract_min();
}

void Huffman::gencode(HNode* T, string encode) {
    if (T == NULL) {
       return; 
    }
    if (!T->s.empty()) {
        _code.push_back(make_pair(T->s, encode));
        return; 
    }
    gencode(T->l, encode + "0");
    gencode(T->r, encode + "1");
}

static void midorder(HNode* T) {
    if (T == NULL) {
        return;
    }
    midorder(T->l);
    cout << T->freq << endl;
    midorder(T->r);
}

int main(int argc, char *argv[]) {
    HNode W[10];
    char words[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[] = {45, 13, 12, 16, 9 , 5};
    for (int i = 0; i < 6; ++i) {
        W[i].freq = freqs[i]; 
        W[i].s = string(1, words[i]); 
        W[i].l = NULL;
        W[i].r = NULL;
    }

    Huffman p = Huffman(W, 6);
    cout << "======================" << endl;
    p.printhuff();
    cout << "======================" << endl;
    HNode* T = p.buildhuffman();
    midorder(T);
    cout << "======================" << endl;
    p.gencode(T, "");
    for (auto s: p._code) {
        cout << s.first << ": " << s.second << endl;    
    }
    return 0;
}
