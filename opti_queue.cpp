#include <iostream>
#include <limits>
using namespace std;


class OptQueue {
public:
    OptQueue() {}
    int heapify(int* arr, int size, int i);
    void buildheap(int* arr, int size);
    inline int getmax(int* heap) {
        return heap[0];
    }
    int extract_max(int* heap, int* size);
    int increase(int* arr, int size, int x, int k);  
    int insert(int* arr, int* size, int k);
private:
    inline int Left(int i) {
        return 2*i + 1;
    }

    inline int Right(int i) {
        return 2*i + 2;
    }

    inline int Parent(int i) {
        return (i+1) / 2 - 1;
    }

    inline void swap(int* arr, int i, int j) {
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
};

int OptQueue::heapify(int* arr, int size, int i) {
    int l = Left(i);
    int r = Right(i);
    int largest = 0;
    if (l < size && arr[l] > arr[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < size && arr[r] > arr[largest]) {
        largest = r;
    }
    
    if (largest != i) {
        swap(arr, i, largest);
        heapify(arr, size, largest);
    }
    return 0;
}

void OptQueue::buildheap(int* arr, int size) {
    for (int i = size / 2 - 1;  i >= 0; --i) {
       heapify(arr, size, i); 
    }
}

int OptQueue::extract_max(int* heap, int* size) {
    int max = getmax(heap);
    swap(heap, 0, *size - 1);
    *size -= 1;
    heapify(heap, *size, 0);
    return max;
}

int OptQueue::increase(int* arr, int size, int x, int k) {
    if (arr[x] > k) {
        cout << "error" << endl;
        return -1;
    }
    arr[x] = k;
    while (x > 0 && arr[Parent(x)] < arr[x]) {
        heapify(arr, size, Parent(x));
        x = Parent(x);
    }
    return 0;
}

int OptQueue::insert(int* arr, int* size, int k) {
    *size += 1;
    arr[*size - 1] = -1 * std::numeric_limits<int>::infinity();
    increase(arr, *size, *size - 1, k);
    return 0;
}

int main(int argc, char *argv[]) {
    int a[] = {4, 1, 3, 2, 16, 9 ,10 , 14, 8, 7, 0, 0};    
    int size = 10;
    OptQueue p = OptQueue();
    p.buildheap(a, size);
    //p.increase(a, size, 5, 20);
    //cout << p.extract_max(a, &size) << endl;
    p.insert(a, &size, 15);
    p.insert(a, &size, 20);
    for (int i = 0; i < size; ++i) {
        cout << a[i] << endl;
    }
    return 0;
}
