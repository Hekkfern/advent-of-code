#pragma once

#include "IModule.hpp"
#include "Types.hpp"
#include <unordered_map>

namespace aoc_2023_20 {

class Conjunction : public IModule {
public:
    /**
     *
     */
    explicit Conjunction(ModuleName name) noexcept;
    /**
     *
     * @param destination
     */
    void addDestination(ModuleName destination) noexcept override;
    /**
     * @copydoc IModule::process
     */
    std::vector<Signal> process(Signal const& input) noexcept override;

private:
    /**
     *
     */
    std::unordered_map<ModuleName, SignalValue> mLastValues{};
    /**
     *
     */
    std::vector<ModuleName> mDestinations{};
};

} // namespace aoc_2023_20
