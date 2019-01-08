#include <iostream>
using namespace std;

class QuickSort {
public:
    QuickSort() {};
    inline void swap(int* x, int* y) {
        int tmp = *x;
        *x = *y;
        *y = tmp;
    }
    int pivot(int* arr, int l, int r);
    int quicksort(int* arr, int l, int r);
};

//随机选取第一个元素, 需要从后往前遍历
int QuickSort::pivot(int* arr, int l, int r) {
    int cursor = r;
    for (int i = r; i > l; --i) {
       if (arr[i] > arr[l]) {
          swap(arr+i, arr+cursor); 
          cursor -= 1;
       } 
    }
    swap(arr+l, arr+cursor);
    return cursor;
}

int QuickSort::quicksort(int* arr, int l, int r) {
    if (l < r) { 
        int cursor = pivot(arr, l, r);
        quicksort(arr, l, cursor - 1);
        quicksort(arr, cursor + 1, r);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    QuickSort p = QuickSort();    
    int a[] = {4, 1, 3, 2, 16, 9 ,10 , 14, 8, 7};    
    p.quicksort(a, 0, 9);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}
