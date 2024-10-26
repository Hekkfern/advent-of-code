#include "Math.hpp"

namespace utils::math {

std::vector<double> getLowestDegreePolynomial(
    std::vector<std::pair<double, double>> const& coords) noexcept
{
    if (coords.empty()) {
        return {};
    }

    std::size_t const n{coords.size()};
    std::vector<double> coefficients(n, 0.0);

    for (std::size_t i = 0; i < n; ++i) {
        double const yi{coords[i].second};
        std::vector<double> term(n, 0.0);
        term[0] = 1.0;

        double denominator = 1.0;
        for (std::size_t j = 0; j < n; ++j) {
            if (i != j) {
                double const xj{coords[j].first};
                denominator *= (coords[i].first - xj);

                // Shift term polynomial by one degree to the right
                for (std::size_t k = n - 1; k > 0; --k) {
                    term[k] = term[k - 1] - xj * term[k];
                }
                term[0] *= -xj;
            }
        }

        // Scale the term by yi / denominator and add it to the coefficients
        double const scale{yi / denominator};
        for (std::size_t k = 0; k < n; ++k) {
            coefficients[k] += term[k] * scale;
        }
    }

    return coefficients;
}

} // namespace utils::math
