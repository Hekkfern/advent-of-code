#pragma once

#include "Part.h"
#include "Rule.h"
#include <string>
#include <unordered_map>

namespace aoc_2023_19 {

class Workflow {
public:
    enum class Result { Accepted, Rejected, GoTo };

    struct RunResult {
        Result result;
        std::string goToWorkflow{""};
    };

    Workflow(std::string_view const name)
        : mName{name}
    {
    }
    void addRule(Rule const& rule) { mRules.emplace_back(rule); }
    [[nodiscard]] RunResult run(Part const& part) const noexcept
    {
        for (auto const& rule : mRules) {
            Rule::RunResult const ruleResult{rule.run(part)};
            switch (ruleResult.result) {
            case Rule::Result::Accepted:
                return RunResult{Result::Accepted};
            case Rule::Result::Rejected:
                return RunResult{Result::Rejected};
            case Rule::Result::Skip:
                continue;
            case Rule::Result::GoTo:
                return RunResult{Result::GoTo, ruleResult.goToWorkflow};
            }
        }
        /* impossible */
        return RunResult{Result::Rejected};
    }

private:
    std::string mName;
    std::vector<Rule> mRules{};
};

} // namespace aoc_2023_19
