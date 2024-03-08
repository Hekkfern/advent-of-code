#pragma once

#include <map>
#include <mutex>
#include <tuple>

namespace utils::cache {

namespace detail {
class null_param { };
} // namespace detail

template <class Sig, class F>
class memoize_helper;

template <class Result, class... Args, class F>
class memoize_helper<Result(Args...), F> {
private:
    using function_type = F;
    using args_tuple_type = std::tuple<std::decay_t<Args>...>;
    function_type f;
    mutable std::map<args_tuple_type, Result> mCache;
    mutable std::recursive_mutex mCacheMutex;

public:
    template <typename Function>
    memoize_helper(Function&& f, detail::null_param)
        : f(f)
    {
    }
    memoize_helper(memoize_helper const& other)
        : f(other.f)
    {
    }
    template <class... InnerArgs>
    Result operator()(InnerArgs&&... args) const
    {
        std::unique_lock<std::recursive_mutex> lock{mCacheMutex};
        auto const args_tuple = std::make_tuple(args...);
        auto const cached = mCache.find(args_tuple);

        if (cached != mCache.end()) {
            return cached->second;
        } else {
            auto&& result = f(*this, std::forward<InnerArgs>(args)...);
            mCache[args_tuple] = result;
            return result;
        }
    }
};

} // namespace utils::cache
