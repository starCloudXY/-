#include <iostream>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
template<typename T>
struct SkipNode{
    SkipNode<T> **forward;//存储指向下一层节点的指针
    T val;//节点的值
    int key=0;//节点的键值
    ~SkipNode(){
        delete []forward;
    }
public:
    SkipNode<T>(int lvl,int searchKey,T val){
        forward = new SkipNode<T>*[lvl];
        for(int i=0;i<lvl;i++){
            forward[i]= nullptr;
        }
        this->val=val;
        this->key=searchKey;
    }
};
template<typename T>
class SkipList {
public:
    SkipList(int n, double p) : MAX_LEVEL(int(log2(n))), p(p) {
        _level = 0;
        tail = new SkipNode<T>(MAX_LEVEL, std::numeric_limits<int>::max(), T());
        header = new SkipNode<T>(MAX_LEVEL, -1, T());
        for (int i = 0; i < MAX_LEVEL; i++)header->forward[i] = tail;
    }

    ~SkipList() {
        SkipNode<T> *current = header->forward[0];
        while (current != nullptr) {
            SkipNode<T> *next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    int MAX_LEVEL;
private:
    double p = 0;
    int _level;
    SkipNode<T> *header;//header 指向 Skip List 的头节点
    SkipNode<T> *tail;

    int randomValue() {
        int lvl = 1;
        double min = 0, max = 1000;
        random_device seed;//硬件生成随机数种子
        ranlux48 engine(seed());//利用种子生成随机数引擎
        uniform_int_distribution<> distrib(min, max);//设置随机数范围，并为均匀分布
        while ((distrib(engine)) * 0.001 < p && lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }

public:
    int SearchNode(int searchKey) {
        int len = 0;
        if (header == nullptr)return 0;
        SkipNode<T> *x = header;
        for (int i = _level - 1; i >= 0; i--) {
            while (x->forward[i]->key < searchKey) {
                x = x->forward[i];
                len++;
            }
        }
        x = x->forward[0];
        if (x->key == searchKey)return len;
        else return len;
    }

    void Insert(int searchKey, T newValue) {
        SkipNode<T> *update[MAX_LEVEL];
        SkipNode<T> *x = header;
        for (int i = _level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];
        if (x->key == searchKey) {
            x->val = newValue;
            return;
        } else {
            int lvl = randomValue();
            if (lvl > _level) {
                for (int i = _level; i < lvl; i++)update[i] = header;
                _level = lvl;
            }
            SkipNode<T> *new_node = new SkipNode<T>(lvl, searchKey, newValue);
            for (int i = lvl - 1; i >= 0; i--) {
                new_node->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = new_node;
            }
        }
    }

    bool Delete(int searchKey) {
        SkipNode<T> *update[MAX_LEVEL];
        SkipNode<T> *x = header;
        if (x == nullptr)return false;
        for (int i = _level - 1; i >= 0; i--) {
            while (x->forward[i] != nullptr && x->forward[i]->key < searchKey) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];
        if (x->key == searchKey) {
            for (int i = 0; i < _level; i++) {
                if (update[i]->forward[i] != x)break;
                update[i]->forward[i] = x->forward[i];
            }
            delete x;
            while (_level >= 0 && header->forward[_level - 1] == nullptr) {
                _level--;
            }
            return true;
        }
        return false;
    }
};

double test(int n,double p){
    SkipList<char> testlist(n,p);
    for(int i=1;i<=n;i++){
        testlist.Insert(i,'A');
    }
    double sum=0;
    int min = 1,max = n;
    random_device seed;//硬件生成随机数种子
    ranlux48 engine(seed());//利用种子生成随机数引擎
    uniform_int_distribution<> distrib(min, max);//设置随机数范围，并为均匀分布
    for(int i=0;i<100000;i++){
        sum+=testlist.SearchNode(distrib(engine));
    }
    for(int i=1;i<=n;i++){
        testlist.Delete(i);
    }
    return double(sum/100000);
}

int main() {
    cout<<"Testcase_50:"<<
        test(50,0.9)<<" "<<test(50,0.875)<<" "<<
        test(50,0.75)<<" "<<test(50,0.5)<<endl;
    cout<<"Testcase_100:"<<
        test(100,0.9)<<" "<<test(100,0.875)<<" "<<
        test(100,0.75)<<" "<<test(100,0.5)<<endl;
    cout<<"Testcase_200:"<<
        test(200,0.9)<<" "<<test(200,0.875)<<" "<<
        test(200,0.75)<<" "<<test(200,0.5)<<endl;
    cout<<"Testcase_500:"<<
        test(500,0.9)<<" "<<test(500,0.875)<<" "<<
        test(500,0.75)<<" "<<test(500,0.5)<<endl;
    cout<<"Testcase_1000:"<<
        test(1000,0.9)<<" "<<test(1000,0.875)<<" "<<
        test(1000,0.75)<<" "<<test(1000,0.5);
    return 0;
}