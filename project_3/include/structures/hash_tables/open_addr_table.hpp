#ifndef OPEN_ADDR_HASHTABLE_HPP_
#define OPEN_ADDR_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <utils/node.hpp>
#include <optional>

template<typename T>
class OpenAddrTable : public HashTable<T>{
private:
    std::vector<std::optional<Pair<T>*>> table;
    HashType method;
    int fibonacciConstant = 2; // Constant used in Fibonacci hashing

    int hashAlgebraic(int key) {
        return key % this->size;
    }

    int hash(int key, int i = 0) {
        switch (method) {
            case HashType::MOD:
                return (key + i) % this->size;
            case HashType::FIB:
                return (key + i * fibonacciConstant) % this->size;
                //?return (a_m * s_int) >> (w - (size_t) log2(size));?
            case HashType::ALG:
                return (hashAlgebraic(key) + i * i) % this->size;
            default:
                std::cerr<<"Invalid hashing method";
        }
    }

public:
    OpenAddrTable(size_t size, HashType method) : HashTable<T>(size, method), table(size) {}

    void insert(std::string key, T value) override {
        int i = 0;
        while (i < this->size) {
            int index = hash(stoi(key), i);
            if (!table[index] || table[index]->isDeleted) {
                table[index] = new Pair<T>(key, value);
                return;
            }
            i++;
        }
        std::cerr << "Hash table overflow";
    }

    void remove(std::string key) override {
        int i = 0;
        while (i < this->size) {
            int index = hash(stoi(key), i);
            if (table[index] && table[index]->key == key && !table[index]->isDeleted) {
                table[index]->isDeleted = true;
                return;
            }
            i++;
        }
        std::cerr << "Key not found";
    }

    T get(std::string key) override {
        int i = 0;
        while (i < this->size) {
            int index = hash(stoi(key), i);
            if (table[index] && table[index]->key == key && !table[index]->isDeleted) {
                return table[index]->value;
            }
            i++;
        }
        std::cerr << "Key not found";
    }

    std::vector<T> get_values() override {
        std::vector<T> values;
        for (int i = 0; i < this->size; i++) {
            if (table[i] && !table[i]->isDeleted) {
                values.push_back(table[i]->value);
            }
        }
        return values;
    }
};

#endif

//Refrence:
//#include <iostream>
//#include <vector>
//#include <string>
//#include <optional>
//
//using namespace std;
//
//const int TABLE_SIZE = 10; // Preferably a prime number
//
//enum class HashingMethod {
//    Algebraic,
//    Fibonacci,
//    Quadratic
//};
//
//struct HashNode {
//    int key;
//    string value;
//    bool isDeleted;
//
//    HashNode(int k, string v) : key(k), value(v), isDeleted(false) {}
//};
//
//class HashTable {
//private:
//    vector<optional<HashNode>> table;
//    HashingMethod method;
//    int fibonacciConstant = 2; // Constant used in Fibonacci hashing
//
//    int hashAlgebraic(int key) {
//        return key % TABLE_SIZE;
//    }
//
//    int hash(int key, int i = 0) {
//        switch (method) {
//            case HashingMethod::Algebraic:
//                return (key + i) % TABLE_SIZE;
//            case HashingMethod::Fibonacci:
//                return (key + i * fibonacciConstant) % TABLE_SIZE;
//            case HashingMethod::Quadratic:
//                return (hashAlgebraic(key) + i * i) % TABLE_SIZE;
//            default:
//                throw invalid_argument("Invalid hashing method");
//        }
//    }
//
//public:
//    HashTable(HashingMethod method) : method(method), table(TABLE_SIZE) {}
//
//    void insert(int key, string value) {
//        int i = 0;
//        while (i < TABLE_SIZE) {
//            int index = hash(key, i);
//            if (!table[index] || table[index]->isDeleted) {
//                table[index] = HashNode(key, value);
//                return;
//            }
//            i++;
//        }
//        cerr << ("Hash table overflow");
//    }
//
//    void remove(int key) {
//        int i = 0;
//        while (i < TABLE_SIZE) {
//            int index = hash(key, i);
//            if (table[index] && table[index]->key == key && !table[index]->isDeleted) {
//                table[index]->isDeleted = true;
//                return;
//            }
//            i++;
//        }
//        cerr << ("Key not found");
//    }
//
//    string search(int key) {
//        int i = 0;
//        while (i < TABLE_SIZE) {
//            int index = hash(key, i);
//            if (table[index] && table[index]->key == key && !table[index]->isDeleted) {
//                return table[index]->value;
//            }
//            i++;
//        }
//        cerr << ("Key not found");
//    }
//
//    void display() {
//        for (int i = 0; i < TABLE_SIZE; i++) {
//            if (table[i] && !table[i]->isDeleted) {
//                cout << "Index " << i << ": Key " << table[i]->key << ", Value " << table[i]->value << endl;
//            }
//        }
//    }
//};
//
//int main() {
//    HashTable htAlgebraic(HashingMethod::Algebraic);
//    HashTable htFibonacci(HashingMethod::Fibonacci);
//    HashTable htQuadratic(HashingMethod::Quadratic);
//
//    htAlgebraic.insert(11, "one");
//    htAlgebraic.insert(21, "two");
//    htAlgebraic.insert(31, "three");
//    htAlgebraic.insert(41, "three");
//
//    htFibonacci.insert(11, "one");
//    htFibonacci.insert(21, "two");
//    htFibonacci.insert(31, "three");
//    htFibonacci.insert(41, "three");
//
//    htQuadratic.insert(11, "one");
//    htQuadratic.insert(21, "two");
//    htQuadratic.insert(31, "three");
//    htQuadratic.insert(41, "three");
//
//    cout << "Algebraic Hash Table:" << endl;
//    htAlgebraic.display();
//
//    cout << "\nFibonacci Hash Table:" << endl;
//    htFibonacci.display();
//
//    cout << "\nQuadratic Hash Table:" << endl;
//    htQuadratic.display();
//
//   htAlgebraic.remove(2);
//   cout << "\nAlgebraic Hash Table after removing key 2:" << endl;
//    htAlgebraic.display();
//
//    return 0;
//}
