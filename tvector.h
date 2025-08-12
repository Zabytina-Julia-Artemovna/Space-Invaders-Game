// Copyright 2025 Zabytina Julia. All rights reserved.
#pragma once
#include <cstddef> 
#include <stdexcept>
#include <vector>
#include <exception>
#include <random>
#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>
template <class T>
class Tvector {
public:
    enum State {
        empty, busy, deleted
    };
private:
    static constexpr size_t RESERVE_MEMORY = 15;
    static constexpr size_t MAX_PERCENT_DELETED = 15;

    size_t _size;
    size_t _capacity;
    T* _data;
    State* _states;
    size_t _deleted;

    size_t get_real_position(size_t busy_index) const noexcept;
    void resize(size_t new_size);
    void resize(size_t new_size, const T& value);
    void shrink_to_fit();
    void reserve(size_t new_capacity);
    void compact_storage();
    inline bool is_full() const noexcept {
        return _size == _capacity;
    }
public:
    Tvector() noexcept;
    Tvector(size_t size);
    Tvector(T* data, size_t size);
    Tvector(const Tvector<T>& other_vector);
    ~Tvector() noexcept;

    inline bool is_empty() const noexcept {
        return _size == 0;
    }
    inline const T* get_data() const noexcept {
        return _data;
    }
    inline T* get_data() noexcept {
        return _data;
    }
    inline const State* get_states() const noexcept {
        return _states;
    }
    inline State* get_states() noexcept {
        return _states;
    }
    inline T& front();
    inline T& back();
    inline const T& front() const;
    inline const T& back() const;
    size_t get_size() const noexcept {
        return _size;
    }
    size_t get_deleted() const noexcept {
        return _deleted;
    }
    size_t get_capacity() const noexcept {
        return _capacity;
    }
    inline T* begin() const noexcept {
        return _data;
    }
    inline T* end() const noexcept {
        return _data + _size;
    }
    bool operator==(const Tvector<T>& vector) const;
    bool operator!=(const Tvector<T>& vector) const;
    Tvector<T>& operator=(const Tvector<T>& vector);
    inline const T& operator[](size_t index) const;
    inline T& operator[](size_t index);
    T& at(size_t index);
    const T& at(size_t index) const;
    void assign(const Tvector<T>& vector);
    void clear();
    void emplace(size_t index, const T& value);
    void push_front(const T& value);
    void insert(const T& value, size_t position);
    void push_back(const T& value);
    void pop_back();
    void erase(size_t position);
    void pop_front();

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Tvector<U>& vector);
    template <class U> friend void shell_sort(Tvector<U>& object) noexcept;
    template <class U> friend void shuffle(Tvector<U>& object) noexcept;
    template <class U> friend size_t find_first_element(const Tvector<U>& object, const U& value);
    template <class U> friend size_t find_last_element(const Tvector<U>& object, const U& value);
    template <class U> friend size_t find_count_of_all_suitable_elements(const Tvector<U>& object, const U& value);
};
template <class T>
size_t Tvector<T>::get_real_position(size_t busy_index) const noexcept {
    size_t busy_count = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == busy) {
            if (busy_count == busy_index) {
                return i;
            }
            ++busy_count;
        }
    }
    return _size;
}
template <class T>
void Tvector<T>::resize(size_t new_size) {
    if (new_size == _size) {
        return;
    }
    else if (new_size < _size) {
        for (size_t i = new_size; i < _size; ++i) {
            if (_states[i] == State::deleted) {
                _deleted--;
            }
            _data[i].~T();
            _states[i] = State::empty;
        }
        _size = new_size;
    }
    else {
        size_t new_capacity = new_size + RESERVE_MEMORY;
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        State* new_states = new State[new_capacity];
        for (size_t i = new_size; i < new_capacity; ++i) {
            new_states[i] = State::empty;
        }
        try {
            for (size_t i = 0; i < _size; ++i) {
                new (new_data + i) T(std::move(_data[i]));
                new_states[i] = _states[i];
            }
            for (size_t i = _size; i < new_size; ++i) {
                new (new_data + i) T();
                new_states[i] = State::busy;
            }
            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            ::operator delete(_data);
            delete[] _states;

            _data = new_data;
            _states = new_states;
            _capacity = new_capacity;
            _size = new_size;
        }
        catch (...) {
            for (size_t i = 0; i < new_size; ++i) {
                new_data[i].~T();
            }
            ::operator delete(new_data);
            delete[] new_states;
            throw;
        }
    }
}
template <class T>
void Tvector<T>::resize(size_t new_size, const T& value) {
    if (new_size == _size) {
        return;
    }
    else if (new_size < _size) {
        for (size_t i = new_size; i < _size; ++i) {
            if (_states[i] == State::deleted) {
                _deleted--;
            }
            _data[i].~T();
            _states[i] = State::empty;
        }
        _size = new_size;
    }
    else {
        size_t new_capacity = new_size + RESERVE_MEMORY;
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        State* new_states = new State[new_capacity];
        for (size_t i = new_size; i < new_capacity; ++i) {
            new_states[i] = State::empty;
        }
        try {
            for (size_t i = 0; i < _size; ++i) {
                new (new_data + i) T(std::move(_data[i]));
                new_states[i] = _states[i];
            }
            for (size_t i = _size; i < new_size; ++i) {
                new (new_data + i) T(value);
                new_states[i] = State::busy;
            }
            for (size_t i = 0; i < _size; ++i) {
                _data[i].~T();
            }
            ::operator delete(_data);
            delete[] _states;

            _data = new_data;
            _states = new_states;
            _capacity = new_capacity;
            _size = new_size;
        }
        catch (...) {
            for (size_t i = 0; i < new_size; ++i) {
                new_data[i].~T();
            }
            ::operator delete(new_data);
            delete[] new_states;
            throw;
        }
    }
}
template <class T>
void Tvector<T>::shrink_to_fit() {
    if (_size >= _capacity) {
        return;
    }
    else if (_size == 0) {
        delete[] _data;
        delete[] _states;
        _data = nullptr;
        _states = nullptr;
        _capacity = 0;
        _deleted = 0;
    }
    else {
        T* new_data = new T[_size];
        State* new_states = new State[_size];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
            new_states[i] = _states[i];
        }
        delete[] _data;
        delete[] _states;
        _data = new_data;
        _states = new_states;
        _capacity = _size;
    }
}
template <class T>
void Tvector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];
    std::fill_n(new_states, new_capacity, State::empty);
    for (size_t i = 0; i < _size; ++i) {
        new_data[i] = std::move(_data[i]);
        new_states[i] = _states[i];
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
}
template <class T>
void Tvector<T>::compact_storage() {
    size_t busy_count = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy) {
            busy_count++;
        }
    }
    std::cout << "compact_storage(): busy_count = " << busy_count << "\n";
    size_t new_capacity = busy_count + RESERVE_MEMORY;
    T* new_data = new T[new_capacity];
    State* new_states = new State[new_capacity];
    size_t new_index = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy) {
            new_data[new_index] = std::move(_data[i]);
            new_states[new_index] = State::busy;
            new_index++;
        }
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] != State::empty) {
            _data[i].~T();
        }
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = new_capacity;
    _size = busy_count;
    _deleted = 0;
}
template <class T>
Tvector<T>::Tvector() noexcept {
    _size = 0;
    _capacity = 0;
    _data = nullptr;
    _states = nullptr;
    _deleted = 0;
}
template <class T>
Tvector<T>::Tvector(size_t size) {
    _size = size;
    _capacity = size + RESERVE_MEMORY;
    _data = new T[_capacity];

    try {
        _states = new State[_capacity];
    }
    catch (const std::bad_alloc&) {
        delete[] _data;
        throw;
    }
    _deleted = 0;

    for (size_t i = 0; i < _capacity; ++i) {
        _states[i] = i < _size ? State::busy : State::empty;
    }
}
template <class T>
Tvector<T>::Tvector(T* data, size_t size) {
    if (size > 0 && data == nullptr) {
        throw std::invalid_argument("Null data pointer with non-zero size");
    }
    _size = size;
    _capacity = _size + RESERVE_MEMORY;
    _data = new T[_capacity];
    try {
        _states = new State[_capacity];
    }
    catch (const std::bad_alloc&) {
        delete[] _data;
        throw;
    }
    for (size_t i = 0; i < _capacity; ++i) {
        if (i < _size) {
            _data[i] = data[i];
            _states[i] = State::busy;
        }
        else {
            _states[i] = State::empty;
        }
    }
    _deleted = 0;
}
template <class T>
Tvector<T>::Tvector(const Tvector<T>& other_vector) {
    _size = other_vector._size;
    _capacity = other_vector._capacity;
    _data = nullptr;
    _states = nullptr;
    try {
        _data = new T[_capacity];
    }
    catch (const std::bad_alloc&) {
        throw;
    }
    try {
        _states = new State[_capacity];
    }
    catch (const std::bad_alloc&) {
        delete[] _data;
        throw;
    }
    _deleted = other_vector._deleted;

    for (size_t i = 0; i < other_vector._size; ++i) {
        _data[i] = other_vector._data[i];
        _states[i] = other_vector._states[i];
    }
    for (size_t i = other_vector._size; i < other_vector._capacity; ++i) {
        _states[i] = State::empty;
    }
}
template <class T>
Tvector<T>::~Tvector() noexcept {
    delete[] _data;
    delete[] _states;
}
template <class T>
inline T& Tvector<T>::front() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[0];
}
template <class T>
inline T& Tvector<T>::back() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[_size - 1];
}
template <class T>
inline const T& Tvector<T>::front() const {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[0];
}
template <class T>
inline const T& Tvector<T>::back() const {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    return _data[_size - 1];
}
template <class T>
bool Tvector<T>::operator==(const Tvector<T>& vector) const {
    if (this->_size != vector._size)
        return false;

    for (size_t i = 0; i < _size; ++i) {
        if ((*this)[i] != vector[i])
            return false;
    }
    return true;
}
template <class T>
bool Tvector<T>::operator!=(const Tvector<T>& vector) const {
    return !(*this == vector);
}
template <class T>
Tvector<T>& Tvector<T>::operator=(const Tvector<T>& vector) {
    if (this == &vector) {
        return *this;
    }
    T* new_data = new T[vector._capacity];
    State* new_states = new State[vector._capacity];
    for (size_t i = 0; i < vector._size; ++i) {
        new_data[i] = vector._data[i];
        new_states[i] = vector._states[i];
    }
    for (size_t i = vector._size; i < vector._capacity; ++i) {
        new_states[i] = empty;
    }
    delete[] _data;
    delete[] _states;
    _data = new_data;
    _states = new_states;
    _capacity = vector._capacity;
    _size = vector._size;
    _deleted = vector._deleted;

    return *this;
}
template <class T>
inline const T& Tvector<T>::operator[](size_t index) const {
    size_t real_index = get_real_position(index);
    return _data[real_index];
}
template <class T>
inline T& Tvector<T>::operator[](size_t index) {
    size_t real_index = get_real_position(index);
    return _data[real_index];
}
template <class T>
T& Tvector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    if (_states[index] != busy) {
        throw std::logic_error("Element at this index is not available (deleted or empty)");
    }
    size_t real_index = get_real_position(index);
    return _data[real_index];
}
template <class T>
const T& Tvector<T>::at(size_t index) const {
    size_t real_index = get_real_position(index);
    return const_cast<Tvector*>(this)->at(real_index);
}
template <class T>
void Tvector<T>::assign(const Tvector<T>& vector) {
    if (this == &vector) {
        return;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy) {
            _data[i].~T();
        }
    }
    delete[] _data;
    delete[] _states;
    _capacity = vector._capacity;
    _size = vector._size;
    _deleted = vector._deleted;

    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        if (vector._states[i] == State::busy) {
            new (&_data[i]) T(vector._data[i]);
        }
        _states[i] = vector._states[i];
    }
    std::fill(_states + _size, _states + _capacity, State::empty);
}
template <class T>
void Tvector<T>::clear() {
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy) {
            _states[i] = State::empty;
        }
    }
    _size = 0;
    _deleted = 0;
}
template <class T>
void Tvector<T>::emplace(size_t index, const T& value) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    size_t real_index = get_real_position(index);
    if (_states[real_index] == State::deleted) {
        --_deleted;
    }
    _data[real_index] = value;
    _states[real_index] = State::busy;
}
template <class T>
void Tvector<T>::push_front(const T& value) {
    if (_size >= _capacity) {
        reserve(_capacity + RESERVE_MEMORY);
    }
    for (size_t i = _size; i > 0; --i) {
        _data[i] = std::move(_data[i - 1]);
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = State::busy;
    _size++;
}
template <class T>
void Tvector<T>::insert(const T& value, size_t position) {
    if (_size == 0) {
        resize(RESERVE_MEMORY);
    }
    if (position >= _size) {
        throw std::out_of_range("Insert position out of range");
    }
    size_t real_pos = get_real_position(position);
    for (size_t i = _size; i > real_pos; --i) {
        _data[i] = std::move(_data[i - 1]);
        _states[i] = _states[i - 1];
    }
    _data[real_pos] = value;
    _states[real_pos] = State::busy;
    _size++;
}
template <class T>
void Tvector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        reserve(_capacity + RESERVE_MEMORY);
    }
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}
template <class T>
void Tvector<T>::pop_back() {
    if (_size == 0) {
        throw std::out_of_range("Vector has size = 0");
    }
    _states[_size - 1] = State::empty;
    _size--;
}
template <class T>
void Tvector<T>::erase(size_t position) {
    if (position >= _size) {
        throw std::out_of_range("Invalid position");
    }
    size_t real_pos = get_real_position(position);
    _states[real_pos] = State::deleted;
    _deleted++;
    if (_deleted * 100 > _size * MAX_PERCENT_DELETED) {
        compact_storage();
    }
}
template <class T>
void Tvector<T>::pop_front() {
    if (_size == 0) {
        throw std::out_of_range("Vector has size = 0");
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_states[i] == State::busy) {
            _states[i] = State::deleted;
            _deleted++;
            if (_deleted * 100 > _size * MAX_PERCENT_DELETED) {
                compact_storage();
            }
            return;
        }
    }
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Tvector<U>& vector) {
    out << "[";
    bool first = true;
    for (size_t i = 0; i < vector._size; ++i) {
        if (vector._states[i] == Tvector<U>::State::busy) {
            if (!first) out << ", ";
            out << vector._data[i];
            first = false;
        }
    }
    out << "]";
    return out;
}
template <class U>
void shell_sort(Tvector<U>& object) noexcept {
    if (object._size < 2 || object._data == nullptr
        || object._states == nullptr) {
        return;
    }
    size_t h = 1;
    while (h < object._size / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (size_t i = h; i < object._size; ++i) {
            for (size_t j = i; j >= h; j -= h) {
                size_t previous = j - h;
                if (object._data[j] < object._data[previous]) {
                    std::swap(object._data[j], object._data[previous]);
                    std::swap(object._states[j], object._states[previous]);
                }
                else {
                    break;
                }
            }
        }
        h /= 3;
    }
}
template <class U>
void shuffle(Tvector<U>& object) noexcept {
    if (object._size < 2 || object._data == nullptr || object._states == nullptr) {
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    for (size_t i = object._size - 1; i > 0; --i) {
        std::uniform_int_distribution<size_t> dist(0, i);
        size_t j = dist(gen);
        std::swap(object._data[i], object._data[j]);
        std::swap(object._states[i], object._states[j]);
    }
}
template <class U>
size_t find_first_element(const Tvector<U>& object, const U& value) {
    size_t result = 0;
    for (size_t i = 0; i < object._size; i++) {
        if (object._states[i] == object.State::deleted) {
            continue;
        }
        else if (object._data[i] == value && object._states[i] == object.State::busy) {
            return result + 1;
        }
        result++;
    }
    return 0;
}
template <class U>
size_t find_last_element(const Tvector<U>& object, const U& value) {
    size_t last_pos = 0;
    size_t current_pos = 0;
    for (size_t i = 0; i < object._size; i++) {
        if (object._states[i] == object.State::deleted) {
            continue;
        }
        current_pos++;
        if (object._data[i] == value && object._states[i] == object.State::busy) {
            last_pos = current_pos;
        }
    }
    return last_pos;
}
template <class U>
size_t find_count_of_all_suitable_elements(const Tvector<U>& object, const U& value) {
    size_t count = 0;
    for (size_t i = 0; i < object._size; ++i) {
        if (object._data[i] == value && object._states[i] == object.State::busy) {
            count++;
        }
    }
    return count;
}
