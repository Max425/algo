// Очередь с динамическим буфером

#include <iostream>
#include <cassert>

template <typename T>
class Queue 
{
private:
    T* buffer;
    int capacity, head, tail, size;
public:
    Queue() : capacity(10), head(0), tail(0), size(0) 
    {
        buffer = new T[capacity];
    }
    ~Queue() 
    {
        delete[] buffer;
    }

    Queue (Queue&) = delete;
	Queue& operator= (const Queue&) = delete;
    
    bool IsEmpty() const 
    {
        return size == 0;
    }
    
    void push_back(const T& value) 
    {
        if (size == capacity) {
            recapacity(capacity * 2);
        }
        buffer[tail] = value;
        tail = (tail + 1) % capacity;
        size++;
    }
    
    T pop_front() 
    {    
        assert(!IsEmpty());

        T value = buffer[head];
        head = (head + 1) % capacity;
        size--;
        return value;
    }
    
private:
    void recapacity(int newCapacity) 
    {
        T* temp = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            temp[i] = buffer[(head + i) % capacity];
        }
        head = 0;
        tail = size;
        capacity = newCapacity;
        delete[] buffer;
        buffer = temp;
    }
};

int main() 
{
    Queue<int> queue;
	int n = 0;
	std::cin >> n;
	bool result = true;
	for( int i = 0; i < n; ++i ) {
		int command = 0;
		int data = 0;
		std::cin >> command >> data;
		switch (command) {
			case 2:
				if (queue.IsEmpty()) {
					result = result && data == -1;
				} else {
					result = result && queue.pop_front() == data;
				}
				break;
			case 3:
				queue.push_back(data);
				break;
		}
	}

	std::cout << (result ? "YES" : "NO");

    return 0;
}