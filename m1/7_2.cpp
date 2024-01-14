#include <iostream>
#include <cassert>
#include <cstring>

template<class T, class TGetKey>
void CountingSort( T* a, int n, TGetKey getKey ) {
	int max = getKey( a[0] );
	for( int i = 1; i < n; ++i ) {
		max = std::max(max, static_cast<int>(getKey(a[i])));
	}
	int* c = new int[max + 1];
	memset( c, 0, (max + 1) * sizeof( int ) );

	for( int i = 0; i < n; ++i )
		++c[getKey( a[i] )];

	for( int i = 1; i < max + 1; ++i ) {
		c[i] += c[i - 1];
	}

	T* b = new T[n];
	for( int i = n - 1; i >= 0; --i ) {
		b[--c[getKey( a[i] )]] = a[i];
	}
	delete[] c;
	for( int i = 0; i < n; ++i ) {
		a[i] = b[i];
	}
	memcpy(a, b, n * sizeof(T));
	delete[] b;
}

template<class T>
void LSD(T* arr, int count) {

    for (int byte = 0; byte < sizeof(T); ++byte) {
        CountingSort(arr, count, [byte](T x) { return (x >> (byte * 8)) & 0xFF; });
    }
}


int main()
{
    int count;
    std::cin >> count;
    uint64_t  *arr = new uint64_t[count];
    for (int i = 0; i < count; ++i) {
        std::cin >> arr[i];
    }
	LSD(arr, count);
	
    for (int i = 0; i < count; ++i) {
		std::cout << arr[i] << " ";
	}
    delete[] arr;

	return 0;
}