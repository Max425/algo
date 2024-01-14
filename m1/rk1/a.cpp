/*
Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1].
На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A,
если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.*/

#include <iostream>

int binarySearch(int* arr, int countElem, int k) {
    int left = 0, right = countElem - 1;
    int med = 0;

    while (left <= right) { 
        med = (left + right) / 2;

        if (arr[med] == k)
            return med;

        arr[med] > k ? right = med - 1 : left = med + 1;
    }

    return arr[med] > k ? med : med + 1;
}

int main()
{
    int countElem;
    std::cin >> countElem;

    int* arr = new int[countElem];
    for (int i = 0; i < countElem; ++i)
        std::cin >> arr[i];

    int k;
    std::cin >> k;

    std::cout << binarySearch(arr, countElem, k);

    delete[] arr;
    return 0;
}