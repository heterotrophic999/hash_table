//
// Created by Admin on 11.10.2021.
//
#include <vector>
#include <list>

#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H

#endif //UNTITLED_MAIN_H

using namespace std;

struct Student {
    unsigned age;
    unsigned weight;
};

typedef std::string Key;
typedef Student Value;


class HashTable
{
    vector<list<pair<Key, Value>>*> arr;
    int current_size;
    int ultimate_size;
    Value average_student{};
public:
    HashTable();
    ~HashTable();

    HashTable(const HashTable& b); // копирует таблицу
    HashTable(HashTable&& b) noexcept ; // обнуляет таблицу


    HashTable& operator=(const HashTable& b);
    HashTable& operator=(HashTable&& b);


    // Обменивает значения двух хэш-таблиц.
    void swap(HashTable& b);

    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    size_t size() const;
    bool empty() const;

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);

    void resize();
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);

