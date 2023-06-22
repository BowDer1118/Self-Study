#include "hash_table.h"

HashTable *create_hash_table() {
    HashTable *table = NULL;

    table = (HashTable *)malloc(sizeof(HashTable));

    if (!table) {
        printf("Hash table allocation failed.\n");
        return NULL;
    }

    table->bukket = (Node **)malloc(MAX_ELEMENT * sizeof(Node *));
    table->bukket_number = MAX_ELEMENT;

    if (!(table->bukket)) {
        free(table);  // 釋放記憶體
        printf("Hash table allocation failed.\n");
        return NULL;
    }

    // 初始化array中的linked-list
    for (int i = 0; i < MAX_ELEMENT; i++) {
        table->bukket[i] = NULL;  // 都設定為空的linked-list
    }

    printf("Hash table allocation success.\n");

    return table;
}

void free_hash_table(HashTable *table) {
    if (table) {
        // 釋放所有linked-list的所有節點
        for (int i = 0; i < MAX_ELEMENT; i++) {
            if (table->bukket[i] != NULL) {
                // 釋放linked-list裡面的所有節點
                Node *node = table->bukket[i];
                Node *next_node;

                while (node != NULL) {
                    next_node = node->next;
                    free(node);
                    node = next_node;
                }
            }
        }
    }
}

int hash_function(datatype_t key) {
    return key % MAX_ELEMENT;
}

// 插入資料到table中
void insert_data_into_hash_table(HashTable *table, datatype_t key) {
    // 準備Node
    Node *new_node = malloc(sizeof(Node));
    new_node->data = key;
    new_node->next = NULL;

    // 計算要插入的位置
    int index = hash_function(key);
    // 插入Node
    if (table->bukket[index] == NULL) {  // linked-list是空的
        table->bukket[index] = new_node;
    } else {  // 找到適當的位置(保持linked-list中的元素小到大排序)
        Node *before = table->bukket[index];
        Node *after = before;

        while ((after->data) < key) {
            before = after;
            after = after->next;
            if (after == NULL) {
                break;
            }
        }

        // 將new_node插入到before和after之間
        before->next = new_node;
        new_node->next = after;
    }
}

void print_hash_table(HashTable *table) {
    for (int i = 0; i < MAX_ELEMENT; i++) {
        printf("Bukkit %d: ", i);
        // 輸出所有元素的linked-list
        Node *node = table->bukket[i];
        while (node != NULL) {
            printf("%d ", node->data);
            node = node->next;
        }
        printf("\n");
    }
}

int search_data_in_hash_table(HashTable *table, datatype_t key) {
    int index = hash_function(key);
    Node *node = table->bukket[index];
    // 查找數值
    while ((node != NULL)) {
        if ((node->data) == key) {
            return index;
        } else if ((node->data) > key) {
            return -1;
        }
        node = node->next;
    }
    return -1;
}