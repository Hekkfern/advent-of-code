#include "Mesh.h"

#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>

namespace aoc_2023_20 {

namespace {
std::string getModuleNameFromVariant(
    std::variant<Broadcaster, FlipFlop, Conjunction> const& var) noexcept
{
    return std::visit(
        [](auto&& var) -> std::string { return var.getModuleName(); }, var);
}
} // namespace

void Mesh::setup() noexcept
{
    /* Post-process step, ensure that all conjunctions are correctly
     * initialized */
    for (auto& module :
         mModules | ranges::views::filter([](auto const& item) -> bool {
             return std::holds_alternative<Conjunction>(item.second);
         })) {
        auto& conjunction{std::get<Conjunction>(module.second)};
        for (auto const& connectedModule :
             mModules | ranges::views::values
                 | ranges::views::filter(
                     [conjunctionName
                      = conjunction.getModuleName()](auto const& item) -> bool {
                         return getModuleNameFromVariant(item)
                             == conjunctionName;
                     })) {
            conjunction.addInput(getModuleNameFromVariant(connectedModule));
        }
    }
}

} // namespace aoc_2023_20
