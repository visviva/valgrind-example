#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <string_view>

using namespace std;

void print(int* array, string_view const rem)
{
    for (size_t i = 0; i < sizeof(array); ++i)
    {
        cout << array[i] << ' ';
    }
    cout << ": " << rem << '\n';
};

tuple<int*, int*> randomArray(size_t size)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    auto a = new int[size];

    for (size_t i = 0; i <= sizeof(a); ++i)
    {
        a[i] = rand() % 100;
    }

    auto e = a;
    advance(e, size + 1);

    return {a, e};
}

int main()
{
    int* arrayStart;
    int* arrayEnd;

    tie(arrayStart, arrayEnd) = randomArray(10);
    sort(arrayStart, arrayEnd);
    print(arrayStart, "sorted with the default operator<");

    tie(arrayStart, arrayEnd) = randomArray(10);
    sort(arrayStart, arrayEnd, std::greater<int>());
    print(arrayStart, "sorted with the standard library compare function object");

    struct
    {
        bool operator()(int a, int b) const { return a < b; }
    } customLess;

    tie(arrayStart, arrayEnd) = randomArray(10);
    sort(arrayStart, arrayEnd, customLess);
    print(arrayStart, "sorted with a custom function object");

    tie(arrayStart, arrayEnd) = randomArray(10);
    sort(arrayStart, arrayEnd, [](int a, int b) { return a > b; });
    print(arrayStart, "sorted with a lambda expression");
}