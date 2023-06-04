# Bloom Filter

#### Sets

//基本原理

```cpp
/*
* File: setpriv.h
* ---------------
* This file contains the private section for the set.h interface.
*/
/* Instance variables */
Map<ValueType,char> map; 
/*
* Implementation notes: ==
* ------------------------
* Two sets are equal if they are subsets of each other.
*/
template <typename ValueType>
bool Set<ValueType>::operator==(const Set & s2) const {
    return isSubsetOf(s2) && s2.isSubsetOf(*this);
}
/*
* Implementation notes: isSubsetOf
* --------------------------------
* The implementation of the high-level functions does not require knowledge
* of the underlying representation
*/
template <typename ValueType>
bool Set<ValueType>::isSubsetOf(Set & s2) {
    foreach (ValueType value in *this) {
    if (!s2.contains(value)) return false;
}
    return true;
}
/The setimpl.cpp Implementatiosed */
template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const Set & s2) const {
    if (cmpFn != set2.cmpFn) {
        error("Sets have different comparison functions");
    }
    Set<ValueType> set = *this;
    foreach (ValueType value in set2) {
    set.add(value);
}
    return set;
}
template <typename ValueType>
ValueType Set<ValueType>::first() {
    if (isEmpty()) error("first: set is empty");
    return *begin();
}
```

### Bloom filters

//基本原理

![](https://pic2.zhimg.com/80/v2-2ef6904826b4ebc5c68454c953ee0ef9_1440w.webp)

将hash后的值对应的bit位赋值1

#### 假阳率：

错误的认为某一原本不在集合中的元素却被检测为在该集合中

![](C:\Users\BOOK3\AppData\Roaming\marktext\images\2023-06-04-21-17-51-image.png)

//应用：

```cpp
void BloomFilter::add(const uint64_t &key)
{
    uint32_t hashVal[4] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, &hashVal);
    bitSet.set(hashVal[0] % FILTER_SIZE);
    bitSet.set(hashVal[1] % FILTER_SIZE);
    bitSet.set(hashVal[2] % FILTER_SIZE);
    bitSet.set(hashVal[3] % FILTER_SIZE);
}

bool BloomFilter::contains(const uint64_t &key)
{
    uint32_t hashVal[4] = {0};
    MurmurHash3_x64_128(&key, sizeof(key), 1, &hashVal);
    return (bitSet[hashVal[0] % FILTER_SIZE]
            && bitSet[hashVal[1] % FILTER_SIZE]
            && bitSet[hashVal[2] % FILTER_SIZE]
            && bitSet[hashVal[3] % FILTER_SIZE]);
}
```

---

## 

## 样题

现有一种新的 bloom filter 的设计，对于一个值 v，通过四个哈希函数（hash1~hash4）产生四个哈希值。新的 bloom filter 并非将四个哈希值对应的 bit 置为 1，而是采取以下策略：  
第一个哈希值对应的 bit 置为 1；  

只有当值 v 二进制的从右往左数第三个 bit 为 1 时，才将第二个哈希值对应的 bit 置为 1；  只有当值 v 二进制的从右往左数第二个 bit 为 1 时，才将第三个哈希值对应的 bit 置为 1；  只有当值 v 二进制的从右往左数第一个 bit 为 1 时（即最低位） ，才将第四个哈希值对应的 bit 置为 1；  
(1) 请使用 C++语言写出这种 bloom filter 的 insert 和 check 实现，四个哈希函数已给  
出，可直接调用。 buckets 的 index 和哈希值对应。变量声明和函数签名如下:

```cpp
char buckets[MAX_HASH];  
void insert(unsigned v);  
bool check(unsigned v);  
unsigned hash1(unsigned v);  
unsigned hash2(unsigned v);  
unsigned hash3(unsigned v);  
unsigned hash4(unsigned v);

//answer
void insert(unsigned v){
    buckets[hash1(v)%MAX_HASH] = true;
    buckets[hash2(v)%MAX_HASH] = (v>>2) & 1;
    buckets[hash3(v)%MAX_HASH] = (v>>1) & 1;
    buckets[hash4(v)%MAX_HASH] = v & 1;    
}
bool check(unsigned v){
    bool check_1 = buckets[hash1(v)%MAX_HASH];
    bool check_2 = (buckets[hash2(v)%MAX_HASH]&&((v>>2) & 1))||
                    !buckets[hash2(v)%MAX_HASH]&&!((v>>2) & 1))
    bool check_3 = (buckets[hash3(v)%MAX_HASH]&&((v>>1) & 1))||
                    !buckets[hash3(v)%MAX_HASH]&&!((v>>1) & 1))
    bool check_4 = (buckets[hash4(v)%MAX_HASH]&&(v & 1))||
                    !buckets[hash4(v)%MAX_HASH]&&!(v & 1))

    return check_1&&check_2&&check_3&&check_4;
};
```

(2) 应用这种新的设计后，相比原先的 bloom filter（即所有哈希值对应的桶都置  
1），假阳性和假阴性会如何变化？

假阳性概率减小

假阴性不变（概率为0）
