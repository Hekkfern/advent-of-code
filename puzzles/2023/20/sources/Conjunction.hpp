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
    explicit Conjunction(ModuleName const& name) noexcept;
    /**
     *
     * @param destination
     */
    void addDestination(ModuleName const& destination) noexcept;
    /**
     *
     * @param input
     */
    void addInput(ModuleName const& input) noexcept;
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
