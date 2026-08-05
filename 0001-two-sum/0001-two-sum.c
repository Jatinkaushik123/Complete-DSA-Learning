#include <stdlib.h>

typedef struct {
    int key;
    int index;
    int used;
} HashEntry;

int hash(int key, int size) {
    unsigned int value = (unsigned int)key;
    return value % size;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int tableSize = numsSize * 2 + 1;

    HashEntry* table = calloc(tableSize, sizeof(HashEntry));
    int* result = malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int position = hash(complement, tableSize);

        while (table[position].used) {
            if (table[position].key == complement) {
                result[0] = table[position].index;
                result[1] = i;

                *returnSize = 2;
                free(table);
                return result;
            }

            position = (position + 1) % tableSize;
        }

        position = hash(nums[i], tableSize);

        while (table[position].used) {
            position = (position + 1) % tableSize;
        }

        table[position].key = nums[i];
        table[position].index = i;
        table[position].used = 1;
    }

    free(table);
    free(result);

    *returnSize = 0;
    return NULL;
}