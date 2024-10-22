#pragma once

#include "Broadcaster.hpp"
#include "Conjunction.hpp"
#include "FlipFlop.hpp"
#include "Types.hpp"
#include <concepts>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>
#include <unordered_map>
#include <variant>

namespace aoc_2023_20 {

namespace {
std::string getModuleNameFromVariant(
    std::variant<Broadcaster, FlipFlop, Conjunction> const& var) noexcept
{
    return std::visit(
        [](auto&& var) -> std::string { return var.getModuleName(); }, var);
}
} // namespace

class Mesh {
public:
    /**
     * @brief
     *
     * @tparam ModuleClass
     * @param module
     */
    template <std::derived_from<IModule> ModuleClass>
    void addModule(ModuleClass&& module) noexcept
    {
        mModules.emplace(module.getName(), std::forward<ModuleClass>(module));
    }
    /**
     * @brief
     *
     * @pre Have called all the addModule functions.
     */
    void setup() noexcept;

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
