#include <iostream>
#include <random>	
#include <cassert>

std::random_device dev;
std::mt19937 rng(dev());

template<class T>
class IsLessCmpDefault
{
public:
	bool operator()(const T& l, const T& r) const { return l < r; }
};

template<class T, class Compare>
int Partition(T* a, int n, Compare cmp) {
	if (n <= 1) {
		return 0;
	}
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, n);
	int randIndex = dist6(rng) % n;
	T pivot = a[randIndex];
	std::swap(a[randIndex], a[0]);

	int i = n - 1, j = n - 1;
	while (j > 0) {
		if (cmp(a[j], pivot)) {
			--j;
		}
		else {
			std::swap(a[i], a[j]);
			--i; --j;
		}
	}
	std::swap(a[0], a[i]);
	return i;
}

template<class T, class Compare = IsLessCmpDefault<T>>
T FindKStat(T* a, int n, int k, Compare cmp = IsLessCmpDefault<T>()) {
	assert(k < n);
	int pivotPos = Partition(a, n, cmp);
	if (pivotPos == k)
		return a[k];

	return k < pivotPos ? FindKStat(a, pivotPos, k, cmp) : FindKStat(a + pivotPos + 1, n - pivotPos - 1, k - pivotPos - 1, cmp);
}

int main() {
	int n;
	std::cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	std::cout << FindKStat(a, n, n / 10) << std::endl;
	std::cout << FindKStat(a, n, n / 2) << std::endl;
	std::cout << FindKStat(a, n, n * 9 / 10) << std::endl;

	delete[] a;
	return 0;
}