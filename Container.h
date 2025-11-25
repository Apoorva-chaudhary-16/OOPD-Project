#pragma once

template <typename T>
class Container {
private:
    T* data;
    int capacity;
    int length;
public:
    Container(int cap = 8) : capacity(cap), length(0) {
        data = new T[capacity];
    }
    ~Container() { delete[] data; }
    void push(const T& item) {
        if (length >= capacity) {
            int newCap = capacity * 2;
            T* newData = new T[newCap];
            for (int i = 0; i < length; ++i) newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCap;
        }
        data[length++] = item;
    }
    T& operator[](int index) {
        if (index < 0 || index >= length) {
            return data[0];
        }
        return data[index];
    }
    int size() const { return length; }
    bool empty() const { return length == 0; }
};
