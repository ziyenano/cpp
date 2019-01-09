#include <iostream>
using namespace std;

class InsertSort {
public:
    inline void swap(int* x, int* y) {
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }
    int insertsort(int* arr, int size);
};

int InsertSort::insertsort(int* arr, int size) {
    for (int i = 0; i < size ; ++i) {
        for (int j = 0;  j < i; ++j) {
            if (arr[j] > arr[i]) {
                swap(arr+j, arr+i);
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int a[] = {4, 1, 3, 2, 16, 9 ,10 , 14, 8, 7};    
    InsertSort p = InsertSort();
    p.insertsort(a, 10);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}
