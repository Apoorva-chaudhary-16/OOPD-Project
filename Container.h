#pragma once

/**
 * Simple dynamic container without std::vector or std::out_of_range.
 * Uses basic array doubling manually.
 */

template <typename T>
class Container {
private:
    T* data;
    int capacity;
    int length;

public:
    Container(int cap = 10)
        : capacity(cap), length(0)
    {
        data = new T[capacity];
    }

    ~Container() {
        delete[] data;
    }

    void push(const T& item) {
        if (length >= capacity) {
            int newCap = capacity * 2;
            T* newData = new T[newCap];

            for (int i = 0; i < length; i++)
                newData[i] = data[i];

            delete[] data;
            data = newData;
            capacity = newCap;
        }
        data[length++] = item;
    }

    // Safe access without std::out_of_range
    T& operator[](int index) {
        // If index invalid, return first element safely
        if (index < 0 || index >= length) {
            return data[0];  
        }
        return data[index];
    }

    int size() const { return length; }
    bool empty() const { return length == 0; }
};
