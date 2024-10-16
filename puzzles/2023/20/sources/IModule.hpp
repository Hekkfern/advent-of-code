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
    explicit IModule(ModuleName name) noexcept
        : mModuleName(std::move(name))
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
    /**
     *
     * @param destination
     */
    virtual void addDestination(ModuleName destination) noexcept = 0;

protected:
    /**
     *
     */
    ModuleName mModuleName;
};

} // namespace aoc_2023_20
