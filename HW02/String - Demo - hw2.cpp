#include "String.h" // include definition of class String

string::string()
    : bx(),
    mySize(0),
    myRes(15) {
}

string::string(const char* const ptr, const size_type count)
    : bx(),
    mySize(0),
    myRes(15) {
    if (count > myRes) resize(count);
    for (size_type i = 0; i < count; ++i)
        element(i) = ptr[i];
    mySize = count;
}

string::string(const size_type count, const char ch)
    : bx(),
    mySize(0),
    myRes(15) {
    if (count > myRes) resize(count);
    for (size_type i = 0; i < count; ++i)
        element(i) = ch;
    mySize = count;
}

string::string(const string& right)
    : bx(),
    mySize(0),
    myRes(15) {
    if (right.mySize > myRes) resize(right.mySize);
    for (size_type i = 0; i < right.mySize; ++i)
        element(i) = right.element(i);
    mySize = right.mySize;
}

string::~string() {
    if (myRes > 15)
        delete[] bx.ptr;
}

string::value_type* string::myPtr() {
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

const string::value_type* string::myPtr() const {
    if (myRes < 16)
        return bx.buf;
    else
        return bx.ptr;
}

string& string::assign(const string& right) {
    if (this != &right) {
        if (right.mySize > myRes) resize(right.mySize);
        for (size_type i = 0; i < right.mySize; ++i)
            element(i) = right.element(i);
        mySize = right.mySize;
    }

    return *this;
}

void string::clear() {
    mySize = 0;
    myPtr()[0] = value_type();
}

string::iterator string::begin() {
    return iterator(myPtr());
}

string::const_iterator string::begin() const {
    return const_iterator(myPtr());
}

string::iterator string::end() {
    return iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::const_iterator string::end() const {
    return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::element(const size_type off) {
    return myPtr()[off];
}

string::const_reference string::element(const size_type off) const {
    return myPtr()[off];
}

void string::push_back(char ch) {
    resize(mySize + 1);
    myPtr()[mySize - 1] = ch;
}

void string::pop_back() {
    if (mySize > 0)
        --mySize;
}

string::reference string::front() {
    return myPtr()[0];
}

string::const_reference string::front() const {
    return myPtr()[0];
}

string::reference string::back() {
    return myPtr()[mySize - 1];
}

string::const_reference string::back() const {
    return myPtr()[mySize - 1];
}

const char* string::c_str() const {
    return myPtr();
}

string::size_type string::size() const {
    return mySize;
}

void string::resize(const size_type newSize, const char ch) {
    if (newSize > myRes) {
        size_type new_myRes = ((newSize | 15) > myRes * 1.5) ? (newSize | 15) : (myRes * 1.5);
        pointer newPtr = new value_type[new_myRes]();

        for (size_type i = 0; i < mySize; ++i)
            newPtr[i] = element(i);
        if (myRes > 15) delete[] bx.ptr;
        bx.ptr = newPtr;
        myRes = new_myRes;
    }
    for (size_type i = mySize; i < newSize; ++i)
        element(i) = ch;
    mySize = newSize;
}

string::size_type string::capacity() const {
    return myRes;
}

bool string::empty() const {
    return mySize == 0;
}