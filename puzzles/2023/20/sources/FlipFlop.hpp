#pragma once

#include "IModule.hpp"
#include "Signal.hpp"
#include "Types.hpp"

namespace aoc_2023_20 {

class FlipFlop : public IModule {
public:
    /**
     *
     * @param name
     * @param destination
     */
    FlipFlop(ModuleName name, ModuleName destination) noexcept;
    /**
     * @copydoc IModule::process
     */
    std::vector<Signal> process(Signal const& input) noexcept override;

private:
    /**
     *
     */
    SignalValue mLastValue{SignalValue::Low};
    /**
     *
     */
    ModuleName mDestination;
};

} // namespace aoc_2023_20
