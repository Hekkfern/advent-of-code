#pragma once

#include "Signal.hpp"
#include "Types.hpp"
#include <utility>
#include <vector>

namespace aoc_2023_20 {

class IModule {
public:
    /**
     *
     * @param name
     */
    explicit IModule(ModuleName const& name) noexcept
        : mModuleName(name)
    {
    }
    /**
     *
     */
    virtual ~IModule() = default;
    /**
     *
     * @param signal
     * @return
     */
    [[nodiscard]] virtual std::vector<Signal>
    process(Signal const& input) noexcept = 0;
    /**
     *
     * @return
     */
    [[nodiscard]] ModuleName getModuleName() const noexcept
    {
        return mModuleName;
    }

protected:
    /**
     *
     */
    ModuleName mModuleName;
};

} // namespace aoc_2023_20
