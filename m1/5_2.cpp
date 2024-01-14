#include <iostream>
#include <cstring>

struct Data
{  
    Data() : day (0), month (0), year (0), dataBirth (true) {} 
    Data (int d, int m, int y, bool f) : day (d), month (m), year (y), dataBirth (f) {} 
    int day, month, year;
    bool dataBirth;
};

class IsLessCmpByData
{
public:
	bool operator()( const Data& l, const Data& r ) { 
        return (l.year != r.year) ? (l.year < r.year) : 
               (l.month != r.month) ? (l.month < r.month) : 
               (l.day != r.day) ? (l.day < r.day) : !l.dataBirth;
    }
};

template<class T>
class IsLessCmpDefault 
{
public:
	bool operator()( const T& l, const T& r ) { return l < r; }
};

template<class T, class Compare = IsLessCmpDefault<T>>
void MergeSort (T*& arr, int n, Compare cmp = IsLessCmpDefault<T>())
{
    for (int step = 1; step < n; step *= 2) {
        for (int i = 0; i < n - step; i += step * 2) {
            
            // ключевые точки
            int left = i, mid = i + step, right = std::min(i + step * 2, n);
            T* tmp = new T[right - left];
            
            // слияние 
            int i1 = left, i2 = mid, j = 0;
            while (i1 < mid && i2 < right) {
                tmp[j++] = cmp(arr[i1], arr[i2]) ? arr[i1++] : arr[i2++];
            }
            // записываем остатки
            while (i1 < mid) {
                tmp[j++] = arr[i1++];
            }
            while (i2 < right) {
                tmp[j++] = arr[i2++];
            }
            
            // копирование
            memcpy(arr + left, tmp, sizeof(T) * j);
            delete[] tmp;
        }
    }
}
int inputDataPerson(Data*& arr, int n)
{
    int count = 0;
    for (int i = 0; i < n; ++i) {
        int d1, m1, y1, d2, m2, y2;
        std::cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;
        
        Data birth(d1, m1, y1, true), old(d1, m1, y1+18, true), death(d2, m2, y2, false), maxDeath(d1, m1, y1+80, false);
        IsLessCmpByData cmp;

        if (cmp(old, death)) {
            arr[count] = old; 
            count++;
            arr[count] = cmp(death, maxDeath) ? death : maxDeath; 
            count++;
        }
    }
    return count;
}

int maxPerson(Data*& arr, int n)
{
    int count = 0, maxCount = 0;
    for (int i = 0; i < n; ++i) {
        arr[i].dataBirth ? count++ : count--;
        maxCount = std::max(maxCount, count);
    }
    return maxCount;
}

int main()
{
    int n;
    std::cin >> n;
    Data *arr = new Data[n * 2];
    int count = inputDataPerson(arr, n);
    
    IsLessCmpByData cmp;
    MergeSort(arr, count, cmp);

    std::cout << maxPerson(arr, count) << std::endl;
    return 0;
}