#include <iostream>
using namespace std;

class HeapSort {
public:
    int* _arr;
    int _size;
    HeapSort(int* arr, int size) {
        _arr = arr;
        _size = size;
    }
    void swap(int i, int j);
    int heapify(int i);
    void build_heap();
    void heapsort();

private:
    inline int Left(int i) {
        return 2*i + 1;
    }

    inline int Right(int i) {
        return 2 * i + 2;
    }

    inline int Parent(int i) {
        return (i - 1) / 2;
    }

};

void HeapSort::swap(int i, int j) {
    int tmp = _arr[i];
    _arr[i] = _arr[j];
    _arr[j]  = tmp;  
}

int HeapSort::heapify(int i) {
    int l = Left(i); 
    int r = Right(i); 
    int largest = 0;
    if (l < _size && _arr[l] > _arr[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < _size && _arr[r] > _arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(largest, i);        
        heapify(largest);
    }
    //cout << largest << " " << l << " " << r << endl;
    return 0;
}

void HeapSort::build_heap() {
    for (int i = _size / 2 - 1; i >= 0; --i) {
       heapify(i); 
    }     
}

void HeapSort::heapsort() {
    build_heap();
    for (int i = _size - 1; i >= 1; --i) {
        swap(0, i);
        _size -= 1;
        heapify(0);
    }
}

int main(int argc, char *argv[]) {
    int a[] = {4, 1, 3, 2, 16, 9 ,10 , 14, 8, 7};    
    HeapSort p = HeapSort(a, sizeof(a) / sizeof(int));
    p.heapsort();
    for (int i = 0; i < 10; ++i) {
        cout << p._arr[i] << endl;
    }
    return 0;
}
