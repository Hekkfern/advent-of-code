#pragma once

#include <iterator>
#include <list>
#include <ostream>

namespace utils::containers {

/**
 * @brief      This class describes a circular list, i.e., it has wrap-around
 *             capabilities.
 *
 * @tparam     T     Type of the contained items.
 */
template <typename T = int32_t>
class CircularList {
public:
    /**
     * @brief      Default constructor
     */
    CircularList() = default;
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  list  A list.
     */
    CircularList(std::list<T> const& list)
        : mList{list}
    {
    }
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  list  A list.
     */
    CircularList(std::list<T>&& list)
        : mList{std::forward<T>(list)}
    {
    }
    /**
     * @brief      Adds a new item to the beginning of the list.
     *
     * @param[in]  value  The value to add.
     */
    void pushFront(T const& value) { mList.push_front(value); }
    /**
     * @brief      Adds a new item to the end of the list.
     *
     * @param[in]  value  The value to add.
     */
    void pushBack(T const& value) { mList.push_back(value); }
    /**
     * @brief      Remove the last element from the list
     */
    void popBack()
    {
        if (!mList.empty()) {
            mList.pop_back();
        }
    }
    /**
     * @brief      Remove the first element from the list
     */
    void popFront()
    {
        if (!mList.empty()) {
            mList.pop_front();
        }
    }
    /**
     * @brief      Adds a new item in the selected position.
     *
     * @param[in]  it     The iterator of the position to insert to.
     * @param[in]  value  The value to add.
     */
    void insert(std::list<T>::iterator it, T const& value)
    {
        mList.insert(it, value);
    }
    /**
     * @brief      Deletes the selected item from the list.
     *
     * @param[in]  it    The iterator of the position to delete its item.
     */
    void erase(std::list<T>::iterator it) { mList.erase(it); }
    /**
     * @brief      Gets the number of elements of the list.
     *
     * @return     Number of items.
     */
    [[nodiscard]] std::size_t size() const { return mList.size(); }
    /**
     * @brief      Checks if the list is empty, i.e., has no items.
     *
     * @return     True if it is empty. False, otherwise.
     */
    [[nodiscard]] bool empty() const { return mList.empty(); }
    /**
     * @brief      Get the value of the first element in the list.
     *
     * @return     First element of the list.
     */
    [[nodiscard]] T& front() const { return mList.front(); }
    /**
     * @brief      Get the value of the last element in the list.
     *
     * @return     Last element of the list.
     */
    [[nodiscard]] T& back() const { return mList.back(); }
    /**
     * @brief      Swaps the values of the items in the selected positions.
     *
     * @param[in]  pos1  The position 1.
     * @param[in]  pos2  The position 2.
     */
    bool swap(std::size_t pos1, std::size_t pos2)
    {
        if (mList.size() < 2U) {
            return false;
        }
        if (pos1 >= mList.size() || pos2 >= mList.size()) {
            return false;
        }
        if (pos1 == pos2) {
            return true;
        }
        // Swap the values at the two positions
        auto iter1{mList.begin() + pos1};
        auto iter2{mList.begin() + pos2};
        std::swap(*iter1, *iter2);
        return true;
    }
    /**
     * @brief      Deletes all the items.
     */
    void clear() { mList.clear(); }
    /**
     * @brief      Moves the item from one position to another, and slides all
     * the other items accordingly.
     *
     * @param[in]  oldIndex  The old index.
     * @param[in]  newIndex  The new index.
     */
    bool move(std::size_t const oldIndex, std::size_t const newIndex)
    {
        if (oldIndex >= mList.size() || newIndex >= mList.size()) {
            return false;
        }
        if (oldIndex == newIndex) {
            return true;
        }
        // Get the iterators to the elements at the specified positions
        auto iter1{mList.begin() + oldIndex};
        auto iter2{mList.begin() + newIndex};
        // Determine the direction of the move and adjust the positions of all
        // elements in between
        if (oldIndex < newIndex) {
            mList.splice(std::next(iter2), mList, iter1);
        } else {
            mList.splice(iter2, mList, iter1);
        }
        return true;
    }
    /**
     * @brief      Rotate the list some positions to the left.
     *
     * @param[in]  amount  The amount of positions to rotate.
     */
    void rotateLeft(std::size_t const amount = 1U)
    {
        if (!empty() && amount > 0U) {
            T val = mList.front();
            mList.pop_front();
            mList.splice(mList.end(), mList, mList.begin());
        }
    }
    /**
     * @brief      Rotate the list some positions to the right.
     *
     * @param[in]  amount  The amount of positions to rotate.
     */
    void rotateRight(std::size_t const amount = 1U)
    {
        if (mList.size() < 2) {
            return;
        }
        amount %= mList.size();
        if (amount == 0) {
            return;
        }
        auto it = mList.end();
        // point to the last element
        --it;
        // move the iterator to the selected position
        std::advance(it, -static_cast<int>(amount));
        // move the selected elements to the front
        mList.splice(mList.begin(), mList, it, mList.end());
        // move the iterator to the position after the selected position
        std::advance(it, amount);
        // move the elements from the beginning to the selected position to the
        // end
        mList.splice(mList.end(), mList, mList.begin(), it);
    }
    /**
     * @brief      { function_description }
     *
     * @param[in]  reverse  The reverse
     */
    void sort(bool reverse = false)
    {
        if (size() < 2U) {
            return;
        }

        bool swapped = false;
        Node* last = nullptr;
        do {
            swapped = false;
            Node* node = head;
            while (node->next != head) {
                if ((!reverse && node->value > node->next->value)
                    || (reverse && node->value < node->next->value)) {
                    std::swap(node->value, node->next->value);
                    swapped = true;
                    last = node->next;
                }
                node = node->next;
            }
        } while (swapped && last != head);
    }
    /**
     * @brief      { function_description }
     */
    void reverse()
    {
        if (size() < 2U)
            return;

        Node* current = head;
        do {
            std::swap(current->next, current->prev);
            current = current->prev;
        } while (current != head);

        std::swap(head->prev, head->next);
        head = head->prev;
    }
    /**
     * @brief      Equality operator.
     *
     * @param[in]  other  The other object.
     *
     * @return     The result of the equality.
     */
    [[nodiscard]] bool operator==(CircularList const& other) const
    {
        return mList == other.mList;
    }
    /**
     * @brief      Pre-increment operator.
     *
     * @return     *this by reference.
     */
    [[nodiscard]] T& operator++()
    {
        // perform operation
        rotateRight();
        return *this;
    }
    /**
     * @brief      Post-increment operator to rotate the list right
     *
     * @param[in]  <unnamed>  { parameter_description }
     *
     * @return     Unmodified copy by value.
     */
    [[nodiscard]] T operator++(int)
    {
        T copy(*this);
        ++(*this); // or operator++();
        return copy;
    }
    /**
     * @brief      Pre-decrement operator to rotate the list right
     *
     * @return     *this by reference
     */
    [[nodiscard]] T& operator--()
    {
        // perform operation
        rotateLeft();
        return *this;
    }
    /**
     * @brief     Post-decrement operator.
     *
     * @param[in]  <unnamed>  { parameter_description }
     *
     * @return     Unmodified copy by value.
     */
    [[nodiscard]] T operator--(int)
    {
        T copy(*this);
        ++(*this); // or operator++();
        return copy;
    }
    /**
     * @brief      Advance an iterator by the given amount, with wrap-around.
     *
     * @param      it      The iterator
     * @param[in]  amount  The amount
     *
     * @return     { description_of_the_return_value }
     */
    [[nodiscard]] std::list<T>::iterator
    next(std::list<T>::iterator& it, std::size_t const amount = 1U) const
    {
        if (mList.empty()) {
            throw std::out_of_range("CircularList is empty");
        }
        typename std::list<T>::iterator nextIt{it};
        std::size_t counter{amount};
        while (counter > 0) {
            nextIt = std::next(it) == std::end(mList)
                ? std::begin(mList)
                : std::next(it);
            --counter;
        }
        return nextIt;
    }
    /**
     * @brief      Advance an iterator by the given amount, with wrap-around.
     *
     * @param      it      The iterator
     * @param[in]  amount  The amount
     *
     * @return     { description_of_the_return_value }
     */
    [[nodiscard]] std::list<T>::iterator
    prev(std::list<T>::iterator& it, std::size_t const amount = 1U) const
    {
        if (_list.empty()) {
            throw std::out_of_range("CircularList is empty");
        }
        for (int i = 0; i < amount; i++) {
            if (_current == _list.begin()) {
                _current = _list.end();
            }
            _current = std::prev(_current);
        }
        return *_current;
    }

private:
    /**
     * @brief      Stores the container of the values.
     */
    std::list<T> mList{};
};

} // namespace utils::containers
