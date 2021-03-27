#include <stdio.h>
#include <stdlib.h>

long long g_num_inversion = 0;

void merge_blocks(long long *array, long left, long right) {
    long long block_max = right - left + 1;
    long long *block_array = malloc(block_max * sizeof(long long));
    long l = left;
    long mid = left + (right - left) / 2;
    long r = mid + 1;
    long k = 0;
    while(l <= mid && r <= right) {
        if (array[l] <= array[r]) {
            block_array[k++] = array[l++];
            continue;
        }
        g_num_inversion += (mid - l) + 1;
        block_array[k++] = array[r++];
    }
    while(l <= mid) {
        block_array[k++] = array[l++];
    }
    while(r <= right) {
        block_array[k++] = array[r++];
    }
    for(int i = 0; i < block_max; i++) {
        array[left + i] = block_array[i];
    }
    free(block_array);
}

void merge_sort(long long *array, long left,  long right) {
    if (left >= right) {
        return ;
    }
    long middle = left + (right - left) / 2;
    merge_sort(array, left, middle);
    merge_sort(array, middle + 1, right);
    merge_blocks(array, left, right);
}

int main(void) {
    long N;
    FILE *file_in = fopen("input.txt", "r");
    fscanf(file_in, "%ld", &N);
    long long *array = malloc(N * sizeof(long long));
    for (long i = 0; i < N; i++) {
        long long tmp;
        fscanf(file_in, "%lld", &tmp);
        array[i] = tmp;
    }
    fclose(file_in);
    merge_sort(array, 0, N - 1);
    FILE *file_out = fopen("output.txt", "w");
    fprintf(file_out, "%lld", g_num_inversion);
    fclose(file_out);
    free(array);
    return 0;
}