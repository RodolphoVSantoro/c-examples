#include <stdio.h>
#include <stdlib.h>

typedef char TwoBitMapSet;

TwoBitMapSet* twobit_map_new(int max_number, int* map_size) {
    *map_size = max_number / 4 + 1;
    return (TwoBitMapSet*)calloc(*map_size, sizeof(TwoBitMapSet));
}

char twobit_map_get(TwoBitMapSet* map, int map_size, int num) {
    int index = num >> 2;
    int offset = (num - (index << 2)) * 2;
    return (map[index] >> offset) & 0b00000011;
}

void twobit_map_add(TwoBitMapSet* map, int map_size, int num) {
    int index = num >> 2;
    int offset = (num - (index << 2)) * 2;

    char bits = twobit_map_get(map, map_size, num);
    bits++;
    if (bits > 3) {
        printf("TwoBit set overflow\n");
        return;
    }
    char mask1 = !bits << offset;
    char mask2 = bits << offset;
    map[index] &= ~mask1;
    map[index] |= mask2;
}

int maxAbsArr(int* nums, int numsSize) {
    int max_abs = abs(nums[0]);
    for (int i = 1; i < numsSize; i++) {
        int abs_num = abs(nums[i]);
        if (abs_num > max_abs) {
            max_abs = abs_num;
        }
    }
    return max_abs;
}

typedef struct INT_SET {
    TwoBitMapSet* positive;
    TwoBitMapSet* negative;
} IntSet;

IntSet int_set_new(int maxNumber, int* bit_set_size) {
    IntSet set;
    int positive_size, negative_size;
    set.positive = twobit_map_new(maxNumber, &positive_size);
    set.negative = twobit_map_new(maxNumber, &negative_size);
    if (positive_size != negative_size) {
        printf("Positive and negative set size mismatch\n");
        exit(1);
    }
    *bit_set_size = positive_size;
    return set;
}

int abs(int num) {
    return num >= 0 ? num : -num;
}

void int_set_add(IntSet set, int set_size, int num) {
    int abs_num = abs(num);
    if (abs_num > set_size) {
        printf("Set %d out of bounds(%d)\n", num, set_size);
        exit(1);
    }
    if (num < 0) {
        twobit_map_add(set.negative, set_size, abs_num);
        return;
    }
    twobit_map_add(set.positive, set_size, abs_num);
}

char int_set_get(IntSet set, int set_size, int num) {
    int abs_num = abs(num);
    if (abs_num > set_size) {
        return 0;
    }

    if (num < 0) {
        return twobit_map_get(set.negative, set_size, abs_num);
    }
    return twobit_map_get(set.positive, set_size, abs_num);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* res = (int*)calloc(2, sizeof(int));
    int set_size = maxAbsArr(nums, numsSize), bit_set_size;
    IntSet int_set = int_set_new(set_size, &bit_set_size);

    int i = 0, remains;
    for (i = 0; i < numsSize; i++) {
        int num = nums[i];
        int_set_add(int_set, set_size, num);
        remains = target - num;
        if (num != remains && int_set_get(int_set, set_size, remains) == 1) {
            break;
        }
        if (num == remains && int_set_get(int_set, set_size, remains) == 3) {
            break;
        }
    }

    if (i == numsSize) {
        free(int_set.negative);
        free(int_set.positive);
        *returnSize = 0;
        return res;
    }

    int j;
    for (j = 0; j < numsSize; j++) {
        if (nums[j] == remains) {
            break;
        }
    }

    free(int_set.negative);
    free(int_set.positive);
    res[0] = i;
    res[1] = j;
    *returnSize = 2;
    return res;
}
int main() {
    int arr[] = {3, 2, 4, 5, 6, 13, 14};
    int target = 6;
    int returnSize;
    int* res = twoSum(arr, 7, target, &returnSize);
    printf("Result %d, %d", res[0], res[1]);
    free(res);
    return 0;
}