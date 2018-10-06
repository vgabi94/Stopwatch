#pragma once
#include <chrono>

#ifndef NOT_AUTO_SW
    #include <string>
    #include <iostream>
#endif

#define TYPEDEFS typedef std::chrono::duration<double> sec;         \
        typedef std::chrono::duration<double, std::milli> milisec;  \
        typedef std::chrono::duration<double, std::micro> microsec; \
        typedef std::chrono::duration<double, std::nano> nanosec;

#define DEFAULT_HEADER "Elapsed time: "

#ifdef NOT_AUTO_SW
namespace benchmark
{
    TYPEDEFS
    class Stopwatch
    {
    private:
        std::chrono::steady_clock::time_point mStart;
    
    public:
        Stopwatch() { ReStart(); }

        template<typename T = sec>
        double Elapsed() const
        {
            return std::chrono::duration_cast<T>(std::chrono::steady_clock::now() - mStart).count();
        }    

        void ReStart()
        {
            mStart = std::chrono::steady_clock::now();
        }
    };
} // benchmark
#else
namespace benchmark
{
    TYPEDEFS
    template<typename T = sec>
    class Stopwatch
    {
    private:
        std::chrono::steady_clock::time_point mStart;
        std::string mHeader;
        std::string mUnit;

    public:
        Stopwatch(const std::string& header, const std::string& unit = " s")
        {
            mHeader = header;
            mUnit = unit;
            mStart = std::chrono::steady_clock::now();
        }

        Stopwatch() : Stopwatch(DEFAULT_HEADER) { }
        
        ~Stopwatch()
        {
            double elapsed = std::chrono::duration_cast<T>(
                std::chrono::steady_clock::now() - mStart
            ).count();
            std::cout << mHeader << elapsed << mUnit << '\n';
        }
    };
} // benchmark
#endif

namespace bm = benchmark;

#ifndef NOT_AUTO_SW
    #define STOPWATCH_SEC(header) bm::Stopwatch<> sw(header)
    #define STOPWATCH_MILISEC(header) bm::Stopwatch<bm::milisec> sw(header, " ms")
    #define STOPWATCH_MICROSEC(header) bm::Stopwatch<bm::microsec> sw(header, " microsec")
    #define STOPWATCH_NANOSEC(header) bm::Stopwatch<bm::nanosec> sw(header, " ns")
#endif

#undef TYPEDEFS
#undef DEFAULT_HEADER