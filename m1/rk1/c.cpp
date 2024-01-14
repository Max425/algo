#include <iostream>
#include <vector>

struct Box
{
    Box(int x, int y, int z, int number) : x_(x), y_(y), z_(z), number_(number) {}
    int x_;
    int y_;
    int z_;
    int number_;
};

class IsLessCmpForBox
{
public:
    bool operator()(const Box& l, const Box& r) {
return l.x_ < r.x_ && l.y_ < r.y_ && l.z_ < r.z_ ||
           l.x_ < r.x_ && l.y_ < r.z_ && l.z_ < r.y_ ||
           l.x_ < r.y_ && l.y_ < r.z_ && l.z_ < r.x_ ||
           l.x_ < r.y_ && l.y_ < r.x_ && l.z_ < r.z_ ||
           l.x_ < r.z_ && l.y_ < r.x_ && l.z_ < r.y_ ||
           l.x_ < r.z_ && l.y_ < r.y_ && l.z_ < r.x_;

    }
};

template<class T>
class IsLessCmpDefault
{
public:
    bool operator()(const T& l, const T& r) { return l < r; }
};

template<class T, class Compare = IsLessCmpDefault<T>>
void insertSort(std::vector<T>& arr, Compare cmp = IsLessCmpDefault<T>())
{
    for (int i = 1; i < arr.size(); ++i) {
        T temp = arr[i];
        int j = i - 1;
        while (j >= 0 && cmp(temp, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

int main()
{
    int k;
    std::cin >> k;

    std::vector<Box> boxes;
    for (int i = 0; i < k; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        boxes.push_back({ x, y, z, i });
    }
    IsLessCmpForBox cmp;
    insertSort<Box, IsLessCmpForBox>(boxes, cmp);

    for (auto& box : boxes) {
        std::cout << box.number_ << ' ';
    }

    return 0;
}