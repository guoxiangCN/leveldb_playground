#pragma once

#include <functional>

namespace tools
{

    class Defer final
    {
    public:
        Defer(std::function<void(void)> &&fn) : fn_(std::move(fn)) {}

        Defer(const Defer &) = delete;
        Defer &operator=(const Defer &) = delete;

        ~Defer()
        {
            if (fn_)
            {
                fn_();
            }
        }

    private:
        std::function<void(void)> fn_;
    };
}