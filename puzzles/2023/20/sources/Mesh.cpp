#include "Mesh.h"

#include <range/v3/algorithm/find.hpp>
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

bool containsDestinationFromVariant(
    std::variant<Broadcaster, FlipFlop, Conjunction> const& var,
    ModuleName const& destination) noexcept
{
    return std::visit(
        [&destination](auto&& var) -> bool {
            auto const destinations{var.getDestinations()};
            return ranges::find(destinations, destination)
                != destinations.cend();
        },
        var);
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
                         return containsDestinationFromVariant(
                             item, conjunctionName);
                     })) {
            conjunction.addInput(getModuleNameFromVariant(connectedModule));
        }
    }
}

std::vector<Signal> Mesh::process(Signal const& input)
{
    auto const module{mModules.find(input.destination)};
    if (module == mModules.cend()) {
        return {};
    }
    return std::visit(
        [&input](auto&& var) -> std::vector<Signal> {
            return var.process(input);
        },
        module->second);
}

} // namespace aoc_2023_20
