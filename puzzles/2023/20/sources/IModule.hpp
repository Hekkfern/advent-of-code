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
    /**
     *
     * @param destination
     */
    void addDestination(ModuleName const& destination) noexcept
    {
        mDestinations.push_back(destination);
    }
    /**
     *
     * @param destination
     */
    [[nodiscard]] std::vector<ModuleName> getDestinations() const noexcept
    {
        return mDestinations;
    }

protected:
    /**
     *
     */
    ModuleName mModuleName;
    /**
     *
     */
    std::vector<ModuleName> mDestinations{};
};

} // namespace aoc_2023_20
