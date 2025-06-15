#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H
#include "MyString.h"
class GameException {
public:
    virtual MyString getMessage() const = 0;
//protected:
//    MyString msg;
};

class FileIOException : public GameException {
public:
     FileIOException(const MyString& detail): message(detail) {}
     MyString getMessage() const override {
        return MyString("File I/O Error: ").concat(message);  }
private:
    MyString message;
};

class ConfigParseException : public GameException {
public:
     ConfigParseException(const MyString& detail): message(detail) {}

    MyString getMessage() const override {
        return MyString("Config Parse Error: ").concat(message);
    }
private:
    MyString message;
};

class PhysicsException : public GameException {
public:
     PhysicsException(const MyString& detail): message(detail) {}

    MyString getMessage() const override {
        return MyString("Physics Error: ").concat(message);
    }
private:
    MyString message;
};
#endif