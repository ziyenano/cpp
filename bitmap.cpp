#include <iostream>
using namespace std;

class BitMap {
public:
    BitMap(int map_size, int size);
    ~BitMap() {
        delete _bmap;
    }
    void set_bit(int x);
    bool get_bit(int x);
private:
    inline int word_offset(int x) {
       return x / _size; 
    }
    inline int bit_offset(int x) {
       return x % _size; 
    }
    int _size;
    uint32_t* _bmap;
};

BitMap::BitMap(int map_size, int size) {
    _size = size;
    _bmap = new uint32_t[map_size];
}

void BitMap::set_bit(int x) {
    _bmap[word_offset(x)] |= (1 << bit_offset(x));
}

bool BitMap::get_bit(int x) {
    int ret = _bmap[word_offset(x)] >> bit_offset(x) & 1;
    if (ret == 0) {
       return false; 
    }
    return true;
}

int main(int argc, char *argv[]) {
    //bitmap 类似于直接寻址
    //可用于(特定情况)快速查找, 排序, 统计重复(非重复)元素
    int arr[] = {10, 200, 500, 30, 35, 72};
    int Max = 500;
    int size = 32;
    BitMap obj = BitMap(Max / size + 1, size);       
    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i) {
       obj.set_bit(arr[i]); 
    }
    cout << obj.get_bit(200) << endl;
    cout << obj.get_bit(100) << endl;
    return 0;
}
