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
    explicit FlipFlop(ModuleName const& name) noexcept;
    /**
     * @copydoc IModule::process
     */
    [[nodiscard]] std::vector<Signal>
    process(Signal const& input) noexcept override;

private:
    /**
     *
     */
    SignalValue mLastValue{SignalValue::Low};
};

} // namespace aoc_2023_20
