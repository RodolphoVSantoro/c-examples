#include <stdio.h>
#include <stdlib.h>

typedef char TwoBitMapSet;

TwoBitMapSet* twobit_map_new(int max_number, int* map_size) {
    *map_size = (max_number + 1) / 4;
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
        exit(1);
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

int main() {
    int arr[] = {1, 1, 2, 3, 4, 5, 6, 7, 8, 13, 10, 9, 9, 7, 8};
    int arr_size = sizeof(arr) / sizeof(int);
    int map_size;
    TwoBitMapSet* map = twobit_map_new(maxAbsArr(arr, arr_size), &map_size);
    for (int i = 0; i < arr_size; i++) {
        twobit_map_add(map, map_size, arr[i]);
    }
    for (int i = 0; i < arr_size; i++) {
        printf("%d: %d\n", arr[i], twobit_map_get(map, map_size, arr[i]));
    }
}