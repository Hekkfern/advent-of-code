#pragma once

#include "Interval.hpp"
#include <vector>

namespace utils::interval {

class MultiInterval {
public:
    MultiInterval() = default;
    explicit MultiInterval(std::vector<Interval>&& intervals);
    std::vector<std::pair<int32_t, int32_t>> get() const;
    void add(const Interval& interval);
    MultiInterval join(const Interval& other) const;
    std::optional<MultiInterval> intersect(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    bool subsumes(const MultiInterval& other) const;
    /**
     * @brief      Checks if another interval includes completely the range of
     *             this one.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if the other interval includes this one. False,
     *             otherwise.
     */
    bool subsumes(const Interval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    bool overlaps(const MultiInterval& other) const;
    /**
     * @brief      Checks if both intervals overlap partial or totally.
     *
     * @param[in]  other  The other object.
     *
     * @return     True if they overlap in any way. False, otherwise.
     */
    bool overlaps(const Interval& other) const;

private:
    void reduce();

    /**
     * @brief List of intervals.
     *
     * @note No interval is overlapped.
     * @note All the intervals are sorted by ascending order of its minimal
     * value.
     * @note Two contiguous intervals mean that there is a gap between them of,
     * at least, one value.
     */
    std::vector<Interval> mIntervals{};
};

} // namespace utils::interval
