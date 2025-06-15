#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
template <typename T>
class Dynamic_array {
private:
    T* arr;
    int len;
    int cap;

    // Doubles the current capacity when needed
    void double_capacity();

public:
    // Constructors & Destructor
    Dynamic_array();                           // Default constructor
    Dynamic_array(int count, T value);       // Fill constructor
    Dynamic_array(const Dynamic_array& other); // Copy constructor
    ~Dynamic_array();                          // Destructor

    T* begin() { return arr; }
    T* end() { return arr + size(); }
    const T* begin() const { return arr; }
    const T* end() const { return arr + size(); }

    // Operators
    Dynamic_array& operator=(const Dynamic_array& other); // Copy assignment
    T& operator[](int index);                           // Subscript operator
    const T& operator[](int index) const;            // Const subscript operator
    bool operator==(const Dynamic_array& other) const; // Equality comparison
    bool operator!=(const Dynamic_array& other) const; // Inequality comparison
    Dynamic_array operator+(const Dynamic_array& other) const; // Concatenation
    Dynamic_array& operator+=(const Dynamic_array& other);     // Append

    // Modifiers
    void push(T value);                 // Adds an element to the end
    void pop();                           // Removes the last element
    void insert_at(int index, T value); // Inserts value at index
    void delete_at(int index);            // Deletes value at index
    void reserve(int new_capacity);       // Reserves a new capacity
    void clear();                         // Clears all elements
    void swap(Dynamic_array& other);      // Swaps with another array
    void shrink_to_fit();                 // Reduces capacity to match size
    void reverse();                       // Reverses the array elements

    // Accessors
    bool empty() const; // Checks if array is empty
    int size() const;   // Returns current size

    T& at(int index); // Bounds-checked element access
    const T& at(int index) const;

    T& front(); // Returns first element
    const T& front() const;

    T& back(); // Returns last element
    const T& back() const;

    int find(T value) const; // Return index of first instance, or -1 if non-existent
};

#endif //DYNAMICARRAY_H
template <typename T>
void Dynamic_array<T>::double_capacity() {
    cap = cap * 2;
    T* newArr = new T[cap];
    for (int i = 0; i < cap; i++) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
    newArr = nullptr;
}
template <typename T>
Dynamic_array<T>::Dynamic_array() :len(0), cap(1) {
    arr = new T[cap];
}
template <typename T>
Dynamic_array<T>::Dynamic_array(int count, T value) {
    cap = count + 1;
    len = count;
    arr = new T[cap];
    for (int i = 0; i < len; i++)
        arr[i] = value;
}
template <typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array<T>& other) {
    len = other.len;
    cap = other.cap;
    arr = new T[cap];
    for (int i = 0; i < len; i++) {
        arr[i] = other.arr[i];
    }
}
template <typename T>
Dynamic_array<T>::~Dynamic_array() {
    delete[] arr;
    len = 0;
    cap = 0;
    arr = nullptr;
}
template <typename T>
Dynamic_array<T>& Dynamic_array<T>:: operator=(const Dynamic_array<T>& other) {
    if (this == &other) {
        return *this;
    }
    delete[] arr;
    len = other.len;
    cap = other.cap;
    arr = new T[cap];
    for (int i = 0; i < len; i++)
        arr[i] = other.arr[i];
    return *this;
}
template <typename T>
T& Dynamic_array<T>::operator[](int index) {
    return arr[index];
}
template <typename T>
const T& Dynamic_array<T>::operator[](int index) const {
    return arr[index];
}
template <typename T>
bool Dynamic_array<T>:: operator==(const Dynamic_array<T>& other) const {
    if (len != other.len)
        return false;
    for (int i = 0; i < len; i++) {
        if (arr[i] != other.arr[i])
        {
            return false;
        }
    }
    return true;
}
template <typename T>
bool Dynamic_array<T>:: operator!=(const Dynamic_array<T>& other) const {
    return!(*this == other);
}
template <typename T>
Dynamic_array<T> Dynamic_array<T>::operator+(const Dynamic_array<T>& other)const {
    Dynamic_array<T> new_arr(len + other.len, 0);
    for (int i = 0; i < len; i++) {
        new_arr.arr[i] = arr[i];
    }
    for (int i = 0; i < other.len; i++) {
        new_arr.arr[i + len] = other.arr[i];
    }
    new_arr.len = len + other.len;
    new_arr.cap = len + other.len;
    return new_arr;
}
template <typename T>
Dynamic_array<T>& Dynamic_array<T>::operator+=(const Dynamic_array<T>& other) {
    if (len + other.len > cap) {
        T* new_arr = new T[len + other.len];
        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        cap = len + other.len;
    }
    for (int i = 0; i < other.len; i++) {
        arr[i + len] = other.arr[i];
    }
    len += other.len;
    return*this;
}
template <typename T>
void Dynamic_array<T>::push(T value) {
    if (len == cap) {
        this->double_capacity();
    }
    arr[len] = value;
    len++;
}
template <typename T>
void Dynamic_array<T>::pop() {
    if (len > 0) {
        len--;
    }
}
template <typename T>
void Dynamic_array<T>::insert_at(int index, T value) {
    if (index < 0 || index > len) {
        return;
    }

    if (len == cap) {
        double_capacity();
    }

    for (int i = len; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = value;
    len++;
}
template <typename T>
void Dynamic_array<T>::delete_at(int index) {
    if (index < 0 || index >= len) {
        return;
    }

    for (int i = index; i < len - 1; i++) {
        arr[i] = arr[i + 1];
    }

    len--;
}
template <typename T>
void Dynamic_array<T>::clear() {
    len = 0;
}
template <typename T>
void Dynamic_array<T>::swap(Dynamic_array<T>& other) {
    Dynamic_array temp = *this;
    *this = other;
    other = temp;
}
template <typename T>
void Dynamic_array<T>::reverse() {
    int start = 0;
    int end = len - 1;

    while (start < end) {
        T temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}
template <typename T>
void Dynamic_array<T>::shrink_to_fit() {
    if (len < cap) {
        T* new_arr = new T[len];
        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        cap = len;
    }
}
template <typename T>
void Dynamic_array<T>::reserve(int new_capacity) {
    if (new_capacity > cap) {
        T* new_arr = new T[new_capacity];
        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        cap = new_capacity;
    }
}
template <typename T>
bool Dynamic_array<T>::empty() const {
    return len == 0;
}
template <typename T>
int Dynamic_array<T>::size() const {
    return len;
}
template <typename T>
T& Dynamic_array<T>::at(int index) {
    return arr[index];
}
template <typename T>
const T& Dynamic_array<T>::at(int index) const {
    return arr[index];
}
template <typename T>
T& Dynamic_array<T>::front() {
    return arr[0];
}
template <typename T>
const T& Dynamic_array<T>::front() const {
    return arr[0];
}
template <typename T>
T& Dynamic_array<T>::back() {
    return arr[len - 1];
}
template <typename T>
const T& Dynamic_array<T>::back() const {
    return arr[len - 1];
}
template <typename T>
int Dynamic_array<T>::find(T value) const {
    for (int i = 0; i < len; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}