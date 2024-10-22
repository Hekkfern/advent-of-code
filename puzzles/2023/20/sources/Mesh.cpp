#include "Mesh.h"

namespace aoc_2023_20 {

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
