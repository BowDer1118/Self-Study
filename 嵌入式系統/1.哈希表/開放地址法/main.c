#include <stdio.h>
#include <stdlib.h>  //malloc free

#define MAX_ELEMENT_SIZE 10  // 元素個數
#define NULL_KEY -1          // 默認初始值

typedef int datatype_t;

typedef struct HashTable {
    datatype_t *elem_p;  // 動態的陣列指標
    int n;               // 當前元素個數
} HashTable;

// 建立哈希表
HashTable *create_hash_table() {
    HashTable *table = NULL;
    table = (HashTable *)malloc(sizeof(HashTable));
    // 動態配置失敗
    if (table == NULL) {
        return NULL;
    }
    table->elem_p = (datatype_t *)malloc(sizeof(datatype_t) * MAX_ELEMENT_SIZE);

    // 動態配置失敗
    if ((table->elem_p) == NULL) {
        // 釋放資源
        free(table);
        return NULL;
    }

    // 初始化elem_p陣列
    for (int i = 0; i < MAX_ELEMENT_SIZE; i++) {
        table->elem_p[i] = NULL_KEY;
    }

    return table;
}

// 釋放資源
void free_hash_table(HashTable *table) {
    if (table) {
        free(table->elem_p);
    }
    free(table);
}

// 判斷表是否滿了
int is_full_hash_table(HashTable *table) {
    return (table->n) == MAX_ELEMENT_SIZE;
}

// 將key插入hash_table中
void insert_data_into_hash_table(HashTable *table, datatype_t key) {
    // 檢查是否還有空間
    if (is_full_hash_table(table)) {
        printf("Hash table is full!\n");
        return;
    }
    // 利用hash function 計算雜湊值
    int index = key % MAX_ELEMENT_SIZE;
    while (table->elem_p[index] != NULL_KEY) {
        index = (index + 1) % MAX_ELEMENT_SIZE;
    }
    // 插入資料
    table->elem_p[index] = key;
    (table->n) += 1;
    printf("Data: %d is inserted into hash_table[%d].\n", key, index);
}

// 輸出哈希表
void print_hash_table(HashTable *table) {
    for (int i = 0; i < MAX_ELEMENT_SIZE; i++) {
        printf("%d ", table->elem_p[i]);
    }
    printf("\n");
}

// 查找資料
int search_hash_table(HashTable *table, datatype_t key) {
    int index = key % MAX_ELEMENT_SIZE;

    while (table->elem_p[index] != key) {
        index = (index + 1) % MAX_ELEMENT_SIZE;
        // 若陣列沒有填滿或找一圈沒找到
        if (table->elem_p[index] == NULL_KEY || index == key % MAX_ELEMENT_SIZE) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    // 要排序的陣列
    datatype_t data[MAX_ELEMENT_SIZE] = {13, 39, 27, 28, 26, 30, 38, 16, 14, 19};
    // 建立哈希表
    HashTable *hash_table = create_hash_table();

    // 插入所有數據
    for (int i = 0; i < MAX_ELEMENT_SIZE; i++) {
        insert_data_into_hash_table(hash_table, data[i]);
    }

    print_hash_table(hash_table);

    int d = 15;
    int ret = search_hash_table(hash_table, d);

    if (ret < 0) {
        printf("Data %d is not found in hash table.\n", d);
    } else {
        printf("Data %d is found at position %d in hash table.\n", d, ret);
    }

    // 釋放哈希表
    free_hash_table(hash_table);
    return 0;
}
