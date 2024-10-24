#pragma once

#include "Broadcaster.hpp"
#include "Conjunction.hpp"
#include "FlipFlop.hpp"
#include "Types.hpp"
#include <concepts>
#include <unordered_map>
#include <variant>

namespace aoc_2023_20 {

class Mesh {
public:
    /**
     * @brief
     *
     * @tparam ModuleClass
     *
     * @param module
     */
    template <std::derived_from<IModule> ModuleClass>
    void addModule(ModuleClass&& module) noexcept
    {
        mModules.emplace(
            module.getModuleName(), std::forward<ModuleClass>(module));
    }
    /**
     * @brief
     *
     * @pre Have called all the addModule functions.
     */
    void setup() noexcept;
    /**
     *
     * @param input
     *
     * @return
     */
    [[nodiscard]] std::vector<Signal> process(Signal const& input);
    /**
     * @brief
     *
     * @param moduleName
     *
     * @return
     */
    [[nodiscard]] std::vector<ModuleName>
    getModulesConnectedTo(ModuleName const& moduleName) const noexcept;

private:
    /**
     *
     */
    std::unordered_map<
        ModuleName,
        std::variant<Broadcaster, FlipFlop, Conjunction>>
        mModules{};
};

} // namespace aoc_2023_20
