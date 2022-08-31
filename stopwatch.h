#pragma once

#include <chrono>
#include <iostream>
#include <sys/time.h>

namespace tools
{

    class StopWatch
    {
    public:
        StopWatch()
        {
            start_ = nowUs();
        }

        virtual ~StopWatch()
        {
            uint64_t now = nowUs();
            std::cout << "StopWatch elapsed " << (now - start_) / 1000 << "ms" << std::endl;
        }

    private:
        uint64_t nowUs()
        {
            ::timeval tv;
            ::gettimeofday(&tv, NULL);
            return tv.tv_sec * 1000 * 1000 + tv.tv_usec;
        }

        uint64_t start_;
    };
}