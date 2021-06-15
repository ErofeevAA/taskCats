#include <fstream>
#include <iostream>
#include <vector>

#define START_UPPER_LETTER 65
#define START_LOWER_LETTER 97
#define LEN_ALPHABET 26

using namespace std;

void swap(string &f, string &s) {
    string tmp = s;
    s = f;
    f = tmp;
}

unsigned long partition(vector<string> &bucket, unsigned long left, unsigned long right) {
    string piv = bucket[rand() % (right - left + 1) + left];
    unsigned long i = left;//99 98
    unsigned long j = right;
    while (i <= j) {
        while ((bucket[i][1] < piv[1]) ||
        (bucket[i][1] == piv[1] && bucket[i][2] < piv[2]))
            i++;
        while ((bucket[j][1] > piv[1]) ||
        (bucket[j][1] == piv[1] && bucket[j][2] > piv[2]))
            j--;
        if (i >= j)
            break;
        swap(bucket[i++], bucket[j--]);
    }
    return j;
}

void quick_sort(vector<string> &bucket, unsigned long left, unsigned long right) {
    if (left < right) {
        unsigned long p = partition(bucket, left, right);
        quick_sort(bucket, left, p);
        quick_sort(bucket, p + 1, right);
    }
}

void bucket_sort(string *array, const unsigned long &N) {
    vector<string> buckets[LEN_ALPHABET * 2];
    for (int j = 0; j < N; ++j) {
        int num = (unsigned char) array[j][0];
        if (num < START_LOWER_LETTER - 1) {
            buckets[num - START_UPPER_LETTER].push_back(array[j]);
            continue;
        }
        num = num - START_LOWER_LETTER + LEN_ALPHABET;
        buckets[num].push_back(array[j]);
    }
    for (auto & bucket : buckets) {
        if (bucket.size() > 1) {
            quick_sort(bucket, 0, bucket.size() - 1);
        }
    }
    int k = 0;
    for (auto & bucket : buckets) {
        for (auto & j : bucket) {
            array[k] = j;
            k++;
        }
    }
}

int main()
{
    ifstream  in_file;
    in_file.open("input.txt");
    unsigned long N;
    in_file >> N;
    srand(N);
    auto *array = new string[N];
    for (int i = 0; i < N; ++i) {
        in_file >> array[i];
    }
    in_file.close();
    bucket_sort(array, N);
    ofstream out_file("output.txt");
    for (int i = 0; i < N; ++i) {
        out_file << array[i] << endl;
    }
    out_file.close();
    delete[] array;
    return 0;
}
