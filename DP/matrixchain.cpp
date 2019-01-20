#include <iostream>
using namespace std;

class MatrixChain {
public:
    MatrixChain() {}
    int matrixchain(int* P, int size, int s, int n);  
};

int MatrixChain::matrixchain(int* P, int l, int r) {
    int q = 1000000000000;  
    if (l == r) {
        return 0;
    }
    for (int k = l+1; k <= r; ++k) {
        q = min(q, matrixchain(P, l, k) + matrixchain(P, k+1, r)
                +P[l-1] * P[k] * P[r]);
    } 
    return q;
}

int main(int argc, char *argv[])
{
    
    return 0;
}
