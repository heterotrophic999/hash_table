#include <iostream>
#include "hash_table.h"
#include <gtest/gtest.h>


class HashTableTest : public testing::Test{
protected:
    void SetUp() override{
        t1.insert("Ivan Jopchenko", {.age = 20, .weight = 60});
        t1.insert("Alexey Navalnii", {.age = 22, .weight = 75});

        t2.insert("Vladimir Putin", {.age = 28, .weight = 70});
        t2.insert("Miron Yanovich", {.age = 28, .weight = 70});
        t2.insert("Studentka Mechti", {.age = 19, .weight = 58});
    }
    HashTable t0;
    HashTable t1;
    HashTable t2;

};
TEST_F(HashTableTest, SwapWorks){
    t1.swap(t2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t2.size(), 2);
    EXPECT_EQ(t2["Alexey Navalnii"].weight, 75);
}
TEST_F(HashTableTest, EraseWorks){
    bool r = t2.erase("Vladimir Putin");
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, EmptyWorks){
    bool r = t1.empty();
    EXPECT_EQ(r, false);
    r = t0.empty();
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, ContainsWorks){
    bool r = t1.contains("Ivan Jopchenko");
    EXPECT_EQ(r, true);
    r = t1.contains("Kurt Cobain");
    EXPECT_EQ(r, false);
}
TEST_F(HashTableTest, AtWorks){
    Value& s = t1.at("Ivan Jopchenko");
    EXPECT_EQ(s.weight, 60);
    ASSERT_ANY_THROW(t1.at("try_to_break_my_table"));
}
TEST_F(HashTableTest, OperatorsWork){
    bool r1 = t1 == t2;
    EXPECT_EQ(r1, false);
    bool r2 = t1 != t2;
    EXPECT_EQ(r2, true);
    unsigned int r3 = t2["Miron Yanovich"].weight;
    EXPECT_EQ(r3, 70);
    t1 = t2;
    r1 = t1 == t2;
    EXPECT_EQ(r1, true);
}
TEST_F(HashTableTest, CopyConstructWorks){
    HashTable t3 = t1;
    EXPECT_EQ(t3.size(), 2);
    bool r0 = t3.contains("Alexey Navalnii");
    EXPECT_EQ(r0, true);
    bool r2 = t3.contains("Vladimir Putin");
    EXPECT_EQ(r2, false);

}
TEST_F(HashTableTest, MoveConstructWorks){
    HashTable t4 = std::move(t2);

    bool r0 = t4.contains("Vladimir Putin");
    bool r1 = t4.contains("Miron Yanovich");
    bool r2 = t4.contains("Studentka Mechti");
    bool r3 = t2.empty();
    EXPECT_EQ(r0, true);
    EXPECT_EQ(r1, true);
    EXPECT_EQ(r2, true);
    EXPECT_EQ(r3, true);
}