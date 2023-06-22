#include "hash_table.h"

int main(int argc, char const *argv[]) {
    HashTable *table = create_hash_table();
    int data[MAX_ELEMENT] = {10, 22, 13, 11, 24, 7, 14};
    for (int i = 0; i < MAX_ELEMENT; i++) {
        insert_data_into_hash_table(table, data[i]);
    }
    print_hash_table(table);

    datatype_t key = 24;
    int ret = search_data_in_hash_table(table, key);

    if (ret >= 0) {
        printf("Found %d at bukkit %d.\n", key, ret);
    } else {
        printf("Not found %d in hash table.\n", key);
    }

    free_hash_table(table);
    return 0;
}
