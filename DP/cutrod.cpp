#include <iostream>
using namespace std;

class CutRod {
public:
    CutRod() {};
    int cutrod_rec(int* price, int n);
    int cutrod_memo(int* price, int* r, int n);
    int cutrod_botup(int* price, int n);
};

int CutRod::cutrod_rec(int* price, int n) {
    if (n == 0) {
        return 0;
    }
    int q = -100;
    for (int i = 1; i <= n; ++i) {
        q = max(q, price[i-1] + cutrod_rec(price, n-i));        
    }
    return q;
}

int CutRod::cutrod_memo(int* price, int* r, int n) {
    if (n == 0) {
        return 0;
    }
    if (r[n-1] >= 0) { 
        return r[n-1];
    }
    //int q = n == 0 ? 0 : -100; 
    int q = -100;
    for (int i = 1; i <= n; ++i) {
        q = max(q, price[i-1] + cutrod_memo(price, r, n-i));
    }
    r[n-1] = q;
    return q;
}

int CutRod::cutrod_botup(int* price, int n) {
    if (n == 0) {
        return 0;
    }
    int* r = new int[n];
    r[0] = 0;
    int q = 0;
    for (int i = 1; i <= n; ++i) {
        q = -100;
        for (int j = 1; j <= i; ++j) {
           q = max(q, price[j-1] + r[i-j]);
        }    
        r[i] = q;
    }
    int maxq = r[n];
    delete [] r;
    return maxq;
}

int main(int argc, char *argv[]) {
    CutRod p = CutRod(); 
    int price[10] = {1, 5, 8, 9, 10 ,17, 17, 20 , 24, 22};
    int n = sizeof(price) / sizeof(int);
    cout << p.cutrod_rec(price, n) << endl;
    int r[10];
    for (int i = 0; i < 10; ++i) {
       r[i] = -10; 
    }
    cout << p.cutrod_memo(price, r, n) << endl;
    cout << p.cutrod_botup(price, n) << endl;
    return 0;
}


