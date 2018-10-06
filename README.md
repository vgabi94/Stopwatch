# Stopwatch
Header-only simple utility class that wraps std::chrono to measure execution time in C++11.
To use this, just include `Stopwatch.hpp` it to your cpp file.

# How to use
### Method 1.
Measures time in the current block of code. Just declare a `Stopwatch` object in the current scope.
```cpp
#include "Stopwatch.hpp"

int main()
{
    constexpr int SIZE = 10000 * 10000;
    int* x = new int[SIZE];
    
    {
        STOPWATCH_SEC("forloop: ");
        for(size_t i = 0; i < SIZE; i++)
        {
            x[i] = i*i + 2*i + 1;
        }
    }
    
    delete[] x;
    return 0;
}
```
### Output
```
forloop: 0.282177 s
```

### Method 2.
Define `NOT_AUTO_SW` before including the library. Measures portions of the code.
```cpp
#define NOT_AUTO_SW
#include "Stopwatch.hpp"
#include <iostream>

int main()
{
    constexpr int SIZE = 10000 * 10000;
    int* x = new int[SIZE];
    
    bm::Stopwatch sw;

    for(size_t i = 0; i < SIZE; i++)
    {
        x[i] = i*i + 2*i + 1;
    }

    std::cout << "Elapsed time: " << sw.Elapsed<bm::milisec>() << " ms";
    
    delete[] x;
    return 0;
}
```
### Output
```
Elapsed time: 274.453 ms
```
