// Author: Matin Kamali

#include "String.h"
#include "Math.h"
#include <iostream>
//
// STATIC METHODS
//

// inits _string to new char[_size + 1] and sets the end of it to '\0'
static void init_string_with_terminator(char*& _string, unsigned int _size) {
    _string = new char[_size + 1];
    (_string[_size]) = '\0';
}

size_t String::string_length(const char* _data) {
    size_t result = 0;
    static unsigned int max_length = 9999999;
    for (int i = 0; i < max_length; ++i) {
        if (_data[i] == '\0') {
            result =  i;
            break;
        }
    }
    return result;
}

void String::string_copy(const char* _source, char* _destination,  size_t _length) {
    for (int i = 0; i < _length; ++i) {
        _destination[i] = _source[i];
    }
}

std::ostream& operator<<(std::ostream& _os, const String& _data) {
    for (size_t i = 0; i < _data.size; ++i) {
        _os << _data[i];       
    }
	return _os;
}

String& String::operator+(const String& _other) {
    String* new_string = new String(*this);
    new_string->append(_other, _other.size);
    return *new_string;
}

//
// STRING DEFINITION
//
void init(String* _string, const char* _data) {
    _string->size = String::string_length(_data);
    init_string_with_terminator(_string->data, _string->size);
    // {   //@temp remove this and use init_string_with_terminator instead
    //     _string->data = new char[_string->size + 1];
    //     _string->data[_string->size] = '\0';
    // }
    _string->string_copy(_data, _string->data, _string->size);
}

String& String::operator=(const String& _other) {
    init(this, _other.data);
    return *this;    
}

String::String() {
    size = 0;
    data = nullptr;
}

String::String(char _data) {
    size = 1;
    init_string_with_terminator(data, 1);
    *data = _data;
}

String::String(const char* _data) {
    init(this, _data);
}

String::~String() {
    clear();
}

void String::append(const char* _data, size_t _length) {
    size_t new_size = size + _length;

    char* new_data = nullptr;
    init_string_with_terminator(new_data, new_size);

    if (size > 0) // copy current data to the new_data if data exists
        string_copy(data, new_data, size);

    // copy _data at the end of new_data
    for (int i = size ; i < new_size; ++i) {
        new_data[i] = _data[i - size];
    }

    // update size and data
    clear();    // <!> clear data
    size = new_size;
    data = new_data;
}

void String::append(const String& _data, size_t _length) {
    append(_data.data, _length);
}

char& String::operator[](size_t i) const {
    return data[i];
}

void String::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
}