#include <iostream>
#include "hash_table.h"
#include <vector>
#include <list>

using namespace std;

int hash_func(const Key& s, int table_size){
    int hash_result = 0;
    for (char i : s)
        hash_result = (hash_result + i);
    hash_result = (hash_result * 2) % table_size;
    return hash_result;
}

HashTable::HashTable(){
    average_student.weight = 70;
    average_student.age = 20;
    ultimate_size = 10;
    current_size = 0;
    list<pair<Key, Value>>* k = nullptr;
    arr.resize(ultimate_size, k);
}

HashTable::~HashTable() {
    arr.clear();
    ultimate_size = 0;
    current_size = 0;
}

HashTable::HashTable(const HashTable& b): HashTable(){ // ? копирование
    current_size = b.current_size;
    ultimate_size = b.ultimate_size;
    arr = vector<list<pair<Key, Value>>*>(ultimate_size);

    for (int i=0; i<b.arr.size(); i++)
        arr[i] = b.arr[i];
}

HashTable::HashTable(HashTable &&b) noexcept{ // ? перемещение
    arr = b.arr;
    current_size = b.current_size;
    ultimate_size = b.ultimate_size;

    for(auto & i : b.arr){
        i = nullptr;
    }
    b.ultimate_size = 0;
    b.current_size = 0;
}

HashTable& HashTable::operator=(const HashTable& b) {
    if (this == &b){
        return *this;
    }
    current_size = b.current_size;
    ultimate_size = b.ultimate_size;
    arr.clear();
    arr = b.arr;
    return *this;
}

HashTable& HashTable::operator=(HashTable &&b){
    if (this == &b){
        return *this;
    }
    current_size = b.current_size;
    ultimate_size = b.ultimate_size;
    arr.clear();
    arr = b.arr;
    for(auto & i : b.arr){
        i = nullptr;
    }
}

void HashTable::swap(HashTable &b){
    int tmp = current_size;
    current_size = b.current_size;
    b.current_size = tmp;
    tmp = ultimate_size;
    ultimate_size = b.ultimate_size;
    b.ultimate_size = tmp;
    arr.swap(b.arr);
}

void HashTable::clear(){
    list<pair<Key, Value>>* emList = nullptr;
    arr.clear();
    arr.resize(ultimate_size, emList);
}

bool HashTable::erase(const Key& k) {
    if (!contains(k))
        return false;

    int hash = hash_func(k, ultimate_size);
    for (auto it = arr[hash]->begin(); it != arr[hash]->end(); it++){
        if (it->first == k) {
            arr[hash]->erase(it);
            current_size--;
            return true;
        }
    }
}

bool HashTable::insert(const Key& k, const Value& v){
    if (contains(k))
        return false;
    int hash = hash_func(k, ultimate_size);
    if (arr[hash] == nullptr){
        arr[hash] = new list<pair<Key, Value>>;
    }
    arr[hash]->push_front(make_pair(k, v));
    if(arr[hash]->size() > 5){
        resize();
    }
    current_size++;
    return true;
}

void HashTable::resize(){
    vector<list<pair<Key, Value>>*> copy = arr;
    arr.clear();
    ultimate_size *= 2;
    list<pair<Key, Value>>* emList = nullptr;
    arr.resize(ultimate_size, emList);
    for (int i = 0; i < ultimate_size / 2; i++){
        if (!copy[i]->empty()){
            for (auto & it : *copy[i]){
                insert(it.first, it.second);
            }
        }
    }
}

bool HashTable::contains(const Key& k) const{
    int hash = hash_func(k, ultimate_size);
    if(arr[hash] == nullptr){
        return false;
    }
    for (const auto & it : *arr[hash]) {
        if (it.first == k){
            return true;
        }
    }
    return false;
}
Value& HashTable::operator[](const Key &k) {
    if (contains(k)){
        int hash = hash_func(k, ultimate_size);
        for (auto & it : *arr[hash]){
            if (it.first == k){
                return it.second;
            }
        }
    }
    insert(k, average_student);
    return average_student;
}

Value& HashTable::at(const Key &k) {
    if (contains(k)){
        int hash = hash_func(k, ultimate_size);
        for (auto & it : *arr[hash]){
            if (it.first == k){
                return it.second;
            }
        }
    }
    else{
        throw invalid_argument("Can't find element on this position");
    }
}

size_t HashTable::size() const{
    return current_size;
}

bool HashTable::empty() const{
    for (const auto it : arr){
        if(it!= nullptr){
            return false;
        }
    }
    return true;
}

bool operator==(const HashTable& a, const HashTable& b){
    return a.arr == b.arr;
}

bool operator!=(const HashTable& a, const HashTable& b){
    return a.arr != b.arr;
}

