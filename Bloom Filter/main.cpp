#include <bitset>
#include <iostream>
#include <functional>

#include <iomanip>

using namespace std;
class BloomFilter {
public:
    BloomFilter(int size, int hash_num) : size(size), hash_num(hash_num),bit_array(size){}

    void insert(int n) {
        for (int i = 0; i <hash_num; i++) {
            int index = hash(n, i) % size;
            bit_array.set(index);
        }
    }

    bool contains(int n) const {
        for (int i = 0; i < hash_num; i++) {
            int index = hash(n, i) % size;
            if (!bit_array.test(index)) {
                return false;
            }
        }
        return true;
    }

private:
    std::bitset <10000>bit_array;
    int hash_num;
    int size;
    size_t hash(int key, int seed) const {
            key = (key << seed) + key*seed;
            key = ~key + (key << 15); // key = (key << 15) - key - 1;
            key = key ^ (key >>12);
            key = key + (key << 2);
            key = key ^ (key >>4);
            key = key * 2057; // key = (key + (key << 3)) + (key << 11);
            key = key ^ (key >>16);
            return key;
    }
};

int main() {
    int m, k;
    for(int i=1;i<=5;i++){
        std::cout<<"\t"<<i;
    }
    std::cout<<std::endl;
    for(m=2;m<6;m++){
        std::cout<<m<<":\t";
        for(k=1;k<=5;k++){
            BloomFilter filter(m*200, k);
            // 插入n个0-99随机数
            for (int i = 0; i < 200; i++) {
                filter.insert(i);
            }
            // 测试误报率
            int false_positives = 0;
            for (int i =200; i < 400; i++) {
                if (filter.contains(i)) {
                    false_positives++;
                }
            }
            double false_positive_rate = (double)false_positives / 200.00;
            std::cout<< false_positive_rate << "\t";
        }
        std::cout<<std::endl;
    }
    return 0;
}
