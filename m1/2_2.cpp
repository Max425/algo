/*2_2. Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
а на интервале [m, n-1] строго убывают. Найти m за O(log m). Требования:  Время работы O(log m). Внимание!
В этой задаче сначала нужно определить диапазон для бинарного поиска размером порядка m с помощью экспоненциального поиска,
а потом уже в нем делать бинарный поиск.*/

#include <iostream>
#include <cassert>

void fillArray(int* array, int size);
void findInterval(int* array, int size, int* left, int* right);
int binarySearchInInterval(int* array, int left, int right);
int findMIndex(int* array, int size);

int main() {
    unsigned int size;
    std::cin >> size;

    int* array = new int[size];
    fillArray(array, size);

    std::cout << findMIndex(array, size) << std::endl;

    delete[] array;
    return 0;
}

void fillArray(int* array, int size) {
    assert(array != nullptr);
    assert(size >= 0);

    for (int i = 0; i < size; ++i)
        std::cin >> array[i];
}

int findMIndex(int* array, int size) {
    if (array[0] > array[1])
        return 0;

    if (array[size - 1] > array[size - 2])
        return size - 1;

    int left = 1, right = 2;
    findInterval(array, size, &left, &right);

    return binarySearchInInterval(array, left, right);
}

void findInterval(int* array, int size, int* left, int* right) {
    while (true) {
        if (array[*left - 1] < array[*left] && array[*right - 1] > array[*right])
            break;

        if (*right * 2 < size){
            *left <<= 1;
            *right <<= 1;
        } else {
            *left = *right;
            *right = size - 1;
        }
    }
}

int binarySearchInInterval(int* array, int left, int right) {
    int median = 0;

    while (left <= right) {
        median = (left + right) / 2;

        if (array[median - 1] < array[median] && array[median] > array[median + 1])
            break;

        array[median] > array[median + 1] ? right = median - 1 : left = median + 1;
    }

    return median;
}