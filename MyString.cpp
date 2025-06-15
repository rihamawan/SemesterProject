#include "MyString.h"
#include <string>
int MyString::mystrlen(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
 int MyString:: mystrlen(const MyString str) {
     int i = 0;
     while (str[i] != '\0') {
         i++;
     }
     return i;
}
void MyString::mystrcpy(char* dest, const char* src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
char* MyString::returnArray()const {
    return str;
}
void MyString::reverse(char* str, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
MyString::MyString() :len(0), capacity(1) {
    str = new char[capacity] {};
    str[0] = '\0';
}
MyString::MyString(char* _str) {
    len = mystrlen(_str);
    capacity = len + 1;
    str = new char[capacity];
    mystrcpy(str, _str);
}
MyString::MyString(const char* s) {
    len = mystrlen(s);
    capacity = len + 1;
    str = new char[capacity];
    mystrcpy(str, s);
}
MyString::MyString(const char* a, int length) {
    len = length;
    capacity = length + 1;
    str = new char[capacity] {};
    mystrcpy(str, a);
}
MyString::MyString(int value) {
    len = 0;
    capacity = 1;
    this->str = itos(value);
    len = mystrlen(str);
    capacity = len + 1;
}
MyString::MyString(const MyString& s) {
    len = s.len;
    capacity = s.capacity;
    str = new char[capacity] {};
    mystrcpy(str, s.str);
}
MyString& MyString:: operator=(const MyString& s) {
    delete[] str;
    len = s.len;
    capacity = s.capacity;
    str = new char[capacity] {};
    mystrcpy(str, s.str);
    return *this;
}
void MyString::insert_at(int i, char ch) {
    if (i < 0 || i > len) {
        cout << "Invalid index" << endl;
        return;
    }
    if (len == capacity - 1) {
        capacity *= 2;
        char* temp = new char[capacity] {};
        for (int j = 0; j < i; j++) {
            temp[j] = str[j];
        }
        temp[i] = ch;
        for (int j = i; j < len; j++) {
            temp[j + 1] = str[j];
        }
        temp[len + 1] = '\0';
        delete[] str;
        str = temp;
        len++;
    }
    else {
        for (int j = len; j > i; j--) {
            str[j] = str[j - 1];
        }
        str[i] = ch;
        len++;
    }
}
void MyString::insert_at(int i, const MyString strObj) {
    if (i < 0 || i > len) {
        cout << "Invalid index" << endl;
        return;
    }
    if (len + strObj.len >= capacity - 1) {
        capacity = len + strObj.len + 1;
        char* temp = new char[capacity];
        for (int j = 0; j < i; j++) {
            temp[j] = str[j];
        }
        for (int j = 0; j < strObj.len; j++) {
            temp[i + j] = strObj.str[j];
        }
        for (int j = i; j < len; j++) {
            temp[j + strObj.len] = str[j];
        }
        temp[len + strObj.len] = '\0';
        delete[] str;
        str = temp;
        len += strObj.len;
    }
    else {
        for (int j = len; j >= i; j--) {
            str[j + strObj.len] = str[j];
        }
        for (int j = 0; j < strObj.len; j++) {
            str[i + j] = strObj.str[j];
        }
        len += strObj.len;
    }
}
void MyString::replace_first(char c) {
    if (str != nullptr && len > 0) {
        str[0] = c;
    }
}
 char* MyString::itos(int integer) {
    if (integer == 0) {
        char* string = new char[2];
        string[0] = '0';
        string[1] = '\0';
        return string;
    }

    // Count digits
    int temp = integer;
    int count = 0;
    while (temp != 0) {
        count++;
        temp /= 10;
    }

    char* string = new char[count + 1];
    string[count] = '\0';

    // Convert digits
    int i = count - 1;
    while (integer != 0) {
        string[i] = (integer % 10) + '0';
        integer /= 10;
        i--;
    }

    return string;
}
int MyString::stoi() const {
    int result = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        else {
            cout << "Invalid number format" << endl;
            return 0;
        }
    }
    return result;
}
MyString& MyString::trim() {
    // Find first nom-textual character
    int start = 0;
    while (start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) {
        start++;
    }

    // Find last non-textual character
    int end = len - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }

    // If string is all non-textual
    if (start > end) {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        len = 0;
        capacity = 1;
        return *this;
    }
    int newLen = end - start + 1;
    char* newStr = new char[newLen + 1];
    for (int i = 0; i < newLen; i++) {
        newStr[i] = str[start + i];
    }
    newStr[newLen] = '\0';

    delete[] str;
    str = newStr;
    len = newLen;
    capacity = newLen + 1;

    return *this;
}
char& MyString:: operator[](int i) {
    return str[i];
}
const char& MyString:: operator[](int i)const {
    return str[i];
}
bool MyString::is_equal(const MyString& M) const {
    if (len != M.len) return false;

    for (int i = 0; i < len; i++) {
        if (str[i] != M.str[i]) return false;
    }
    return true;
}

bool MyString::is_less(const MyString& M) const {
    int minLen = (len < M.len) ? len : M.len;

    for (int i = 0; i < minLen; i++) {
        if (str[i] < M.str[i]) return true;
        if (str[i] > M.str[i]) return false;
    }
    return len < M.len;
}

bool MyString::is_greater(const MyString& M) const {
    int minLen = (len < M.len) ? len : M.len;

    for (int i = 0; i < minLen; i++) {
        if (str[i] > M.str[i]) return true;
        if (str[i] < M.str[i]) return false;
    }
    return len > M.len;
}
float MyString::toFloat() const {
    return std::stof(str); 
}


MyString* MyString::split(char delimiter, int& partCount) const {
    partCount = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            partCount++;
        }
    }
    partCount++;  // Add one for the last part

    MyString* parts = new MyString[partCount];

    int currentPart = 0;
    int substringStart = 0;

    for (int currentPos = 0; currentPos <= len; currentPos++) {
        if (currentPos == len || str[currentPos] == delimiter) {
            int substringLength = currentPos - substringStart;
            parts[currentPart].str = new char[substringLength + 1];

            // Copy substring
            for (int j = 0; j < substringLength; j++) {
                parts[currentPart].str[j] = str[substringStart + j];
            }
            parts[currentPart].str[substringLength] = '\0';
            parts[currentPart].len = substringLength;
            parts[currentPart].capacity = substringLength + 1;

            currentPart++;
            substringStart = currentPos + 1;
        }
    }
    return parts;
}
int* MyString::all_sub_strings(const char* substring, int& count) const {
    MyString searchStr(substring);
    return find_all(searchStr, count);
}
MyString MyString::concat(const MyString& s2) const {
    MyString result;
    result.len = len + s2.len;
    result.capacity = result.len + 1;
    result.str = new char[result.capacity];

    for (int i = 0; i < len; i++) {
        result.str[i] = str[i];
    }
    for (int i = 0; i < s2.len; i++) {
        result.str[len + i] = s2.str[i];
    }
    result.str[result.len] = '\0';
    return result;
}

MyString& MyString::append(const MyString& s2) {
    int newLen = len + s2.len;
    if (newLen >= capacity) {
        capacity = newLen + 1;
        char* temp = new char[capacity];
        mystrcpy(temp, str);
        delete[] str;
        str = temp;
    }

    for (int i = 0; i < s2.len; i++) {
        str[len + i] = s2.str[i];
    }
    str[newLen] = '\0';
    len = newLen;
    return *this;
}

/* MyString operator+(const MyString& s2) const {
     return concat(s2);
 }*/

MyString& MyString::operator+=(const MyString& s2) {
    return append(s2);
}
int MyString::find_first(char ch) const {
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) return i;
    }
    return -1;
}

int MyString::find_first(const MyString& s) const {
    if (s.len > len) return -1;

    for (int i = 0; i <= len - s.len; i++) {
        bool found = true;
        for (int j = 0; j < s.len; j++) {
            if (str[i + j] != s.str[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

int MyString::find_last(char ch) const {
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ch) return i;
    }
    return -1;
}

int MyString::find_last(const MyString& s) const {
    if (s.len > len) return -1;

    for (int i = len - s.len; i >= 0; i--) {
        bool found = true;
        for (int j = 0; j < s.len; j++) {
            if (str[i + j] != s.str[j]) {
                found = false;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

int* MyString::find_all(char ch, int& count) const {
    count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) count++;
    }

    int* indices = new int[count];
    int currentIndex = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            indices[currentIndex++] = i;
        }
    }
    return indices;
}

int* MyString::find_all(const MyString& s, int& count) const {
    count = 0;
    if (s.len > len) return nullptr;

    for (int i = 0; i <= len - s.len; i++) {
        bool found = true;
        for (int j = 0; j < s.len; j++) {
            if (str[i + j] != s.str[j]) {
                found = false;
                break;
            }
        }
        if (found) count++;
    }

    int* indices = new int[count];
    int currentIndex = 0;

    for (int i = 0; i <= len - s.len; i++) {
        bool found = true;
        for (int j = 0; j < s.len; j++) {
            if (str[i + j] != s.str[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            indices[currentIndex++] = i;
        }
    }
    return indices;
}
void MyString::remove_at(int i) {
    if (i < 0 || i >= len) {
        cout << "Invalid index" << endl;
        return;
    }
    for (int j = i; j < len - 1; j++) {
        str[j] = str[j + 1];
    }
    len--;
    str[len] = '\0';
}
void MyString::remove_first(char ch) {
    int pos = find_first(ch);
    if (pos != -1) {
        remove_at(pos);
    }
}

void MyString::remove_last(char ch) {
    int pos = find_last(ch);
    if (pos != -1) {
        remove_at(pos);
    }
}

void MyString::remove_all(char ch) {
    int writePos = 0;
    for (int readPos = 0; readPos < len; readPos++) {
        if (str[readPos] != ch) {
            str[writePos] = str[readPos];
            writePos++;
        }
    }
    len = writePos;
    str[len] = '\0';
}
MyString& MyString::to_upper() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
    return *this;
}

//static MyString to_upper(const MyString& s) {
//    MyString result(s);
//    for(int i = 0; i < result.len; i++) {
//        if(result.str[i] >= 'a' && result.str[i] <= 'z') {
//            result.str[i] = result.str[i] - 32;
//        }
//    }
//    return result;
//}

MyString& MyString::to_lower() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
    return *this;
}

/* static MyString MyString::to_lower(const MyString& s) {
    MyString result(s);
    for(int i = 0; i < result.len; i++) {
        if(result.str[i] >= 'A' && result.str[i] <= 'Z') {
            result.str[i] = result.str[i] + 32;
        }
    }
    return result;
}*/
MyString* MyString::tokenize(const char* delim, int& count) const {
    count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = 0; delim[j] != '\0'; j++) {
            if (str[i] == delim[j]) {
                count++;
                break;
            }
        }
    }
    count++;

    MyString* tokens = new MyString[count];
    int currentToken = 0;
    int substringStart = 0;

    for (int currentPos = 0; currentPos <= len; currentPos++) {
        bool isDelimiter = false;
        if (currentPos == len) {
            isDelimiter = true;
        }
        else {
            for (int j = 0; delim[j] != '\0'; j++) {
                if (str[currentPos] == delim[j]) {
                    isDelimiter = true;
                    break;
                }
            }
        }

        if (isDelimiter) {
            int substringLength = currentPos - substringStart;
            tokens[currentToken].str = new char[substringLength + 1];
            tokens[currentToken].len = substringLength;
            tokens[currentToken].capacity = substringLength + 1;

            for (int j = 0; j < substringLength; j++) {
                tokens[currentToken].str[j] = str[substringStart + j];
            }
            tokens[currentToken].str[substringLength] = '\0';

            currentToken++;
            substringStart = currentPos + 1;
        }
    }
    return tokens;
}
void MyString::print() const {
    for (int i = 0; i < len; i++) {
        cout << str[i];
    }
    cout << endl;
}
void MyString::clear() {
    delete[] str;
    len = 0;
    capacity = 1;
    str = new char[capacity];
    str[0] = '\0';
}
MyString:: ~MyString() {
    delete[] str;
    str = nullptr;
    len = 0;
    capacity = 1;
}
MyString operator+(MyString s1, MyString s2) {
    return s1.concat(s2);
}
ostream& operator<<(ostream& cout, const MyString& s) {
    for (int i = 0; i < s.len; i++) {
        cout << s.str[i];
    }
    return cout;
}
 istream& operator>>(istream& in, MyString& s) {
    char buffer[1024];
    in >> buffer;
    s = MyString(buffer);
    return in;
}
