// Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.

#include <iostream>
#include <cassert>
#include <cstring>

struct Elem
{
	int Value;
	int ValueIndex;
	int ArrayIndex;
};

class IsLessMinHeapCmpElem
{
public:
	bool operator()(Elem& l, Elem& r) { return l.Value > r.Value; }
};

template<class T>
class IsLessMinHeapCmpDefault
{
public:
	bool operator()(const T& l, const T& r) { return l > r; }
};

template<class T>
class IsLessCmpDefault
{
public:
	bool operator()(const T& l, const T& r) { return l < r; }
};

template <class T, class Compare = IsLessCmpDefault<T>>
class Heap
{
public:
    Heap(Compare cmp = IsLessCmpDefault<T>()) : _cmp(cmp), _size(0), _buffer(nullptr) {}
    Heap(T* buffer, size_t size, Compare cmp = IsLessCmpDefault<T>()) : _cmp(cmp), _size(size), _buffer(buffer)
    {
        buildHeap();
    }

    void Insert(const T& element)
    {
        T* new_buffer = new T[_size * 2];
        memcpy(new_buffer, _buffer, sizeof(T) * _size);
        new_buffer[_size] = element;
        delete[] _buffer;
        _buffer = new_buffer;
        siftUp(_size);
        _size++;
    }

    T ExtractMax()
    {
        assert(_size > 0);
        T elem = _buffer[0];
        _size--;
        std::swap(_buffer[0], _buffer[_size]);
        siftDown(0);

        return elem;
    }

    const T& PeekMax() const
    {
        assert(_size > 0);
        return _buffer[0];
    }

    size_t Size() const
    {
        return _size;
    }

    ~Heap()
    {
        delete[] _buffer;
    }

private:
    Compare _cmp;
    T* _buffer;
    size_t _size;

    void buildHeap()
    {
        for (int i = _size / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    void siftDown(int index)
    {
        assert(index >= 0);
        while (index < _size) {
            int left = 2 * index + 1, right = 2 * index + 2;

            // Ищем большего сына, если такой есть.
            int largest = index;
            if (left < _size && _cmp(_buffer[index], _buffer[left])) {
                largest = left;
            }
            if (right < _size && _cmp(_buffer[largest], _buffer[right])) {
                largest = right;
            }
            // Если сыновья меньше 
            if (largest == index) {
                return;
            }

            std::swap(_buffer[index], _buffer[largest]);
            index = largest;
        }
    }

    void siftUp(int index)
    {
        assert(index >= 0);
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (_cmp(_buffer[index], _buffer[parent])) {
                return;
            }
            std::swap(_buffer[index], _buffer[parent]);
            index = parent;
        }
    }
};

template <class T>
int fillArrays(T** arrays, int countArrays, int*& lengths)
{
	int countElements = 0;
	for (int i = 0; i < countArrays; ++i) {
		int countNumbers;
		std::cin >> countNumbers;
		arrays[i] = new T[countNumbers];
		lengths[i] = countNumbers;
		countElements += countNumbers;
		for (int j = 0; j < countNumbers; ++j) {
			T number;
			std::cin >> number;
			arrays[i][j] = number;
		}
	}
	return countElements;
}

template <class T, class Compare = IsLessMinHeapCmpDefault<T>>
void KWayMergeSort(T** arrays, int countArrays, int*& lengths, int*& result)
{
	assert(countArrays > 0 && lengths[0] > 0);
	Heap<Elem, IsLessMinHeapCmpElem> heap(IsLessMinHeapCmpElem{});
	for (int i = 0; i < countArrays; ++i) {
		heap.Insert(Elem{ arrays[i][0], 0, i });
	}
	int i = 0;
	while (heap.Size() > 0) {
		Elem value = heap.ExtractMax();
		result[i] = value.Value;
		i++;
		if (value.ValueIndex + 1 < lengths[value.ArrayIndex]) {
			heap.Insert(Elem{ arrays[value.ArrayIndex][value.ValueIndex + 1],value.ValueIndex + 1 ,value.ArrayIndex });
		}
	}
}


int main()
{
	int countArrays;
	std::cin >> countArrays;
	int **arrays = new int*[countArrays];
	int *lengths = new int[countArrays];
	int countElements = fillArrays<int>(arrays, countArrays, lengths);
	int *result = new int[countElements];
	KWayMergeSort<int, IsLessMinHeapCmpElem>(arrays, countArrays, lengths, result);

	for (int i = 0; i < countElements; ++i) {
		std::cout << result[i] << ' ';
	}
	std::cout << '\n';

	delete[] lengths;
	for (int i = 0; i < countArrays; ++i) {
		delete[] arrays[i];
	}
	delete[] arrays;
	delete[] result;

	return 0;
}