#pragma once

#include <bitset>
#include <deque>

template <uint32_t WindowSize> class CharSlidingWindow {
public:
    void addChar(char newChar)
    {
        // add
        mChars.emplace_back(newChar);
        mSlidingBinary ^= std::bitset<AlphabetSize>().set(
            static_cast<size_t>(newChar - 'a'));
        // remove
        if (mChars.size() > WindowSize) {
            mSlidingBinary ^= std::bitset<AlphabetSize>().set(
                static_cast<size_t>(mChars.front() - 'a'));
            mChars.pop_front();
        }
    }
    bool areUnique() const
    {
        if (mChars.size() < WindowSize) {
            return false;
        }
        if (mSlidingBinary.count() < WindowSize) {
            return false;
        }
        return true;
    }

private:
    static constexpr uint32_t AlphabetSize{ 26U };

    std::deque<char> mChars;
    std::bitset<AlphabetSize> mSlidingBinary;
};