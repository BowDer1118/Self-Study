#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 7
typedef int datatype_t;

// HashTable中的linked-list的node
typedef struct Node {
    datatype_t data;
    struct Node *next;
} Node;

// Hash table
typedef struct HashTable {
    Node **bukket;      // 裝linked-list的array
    int bukket_number;  // array的元素數量
} HashTable;

// 建立hash_table
HashTable *create_hash_table();

void free_hash_table(HashTable *table);

// hash function
int hash_function(datatype_t key);

// 插入資料到table中
void insert_data_into_hash_table(HashTable *table, datatype_t key);

// 輸出Hash table
void print_hash_table(HashTable *table);

// 查詢資料，查到回傳bukkit索引值，查找不到則-1
int search_data_in_hash_table(HashTable *table, datatype_t key);

#endif