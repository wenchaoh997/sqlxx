#include<iostream>
#include "../include/string.h"

bool String::set(char* c){
    unsigned int len = 0, idx;
    while (c[len] != 0) len++;
    char* oldData = data;
    data = new char[len+1];
    if (data == nullptr){
        data = oldData;
        return false;
    }
    _size = len;
    for (idx = 0; idx < len; idx++)
        data[idx] = c[idx];
    data[idx] = '\0';
    delete [] oldData;
    return true;
}

char String::operator[](unsigned int idx){
    return data[idx];
}

bool String::operator+=(String* s){
    unsigned int idx;
    char* oldData = data;
    unsigned int oldSize = _size;
    data = new char[this->_size + s->_size + 1];
    if (data == nullptr){
        data = oldData;
        return false;
    }
    _size = this->_size + s->_size;
    for (idx = oldSize; idx < _size; idx++)
        data[idx] = s->data[idx-oldSize];
    delete [] oldData;
    return true;
}

bool String::operator==(String* s){
    if (this->_size != s->_size) return false;
    unsigned int idx;
    for (idx = 0; idx < _size; idx++)
        if (data[idx] != s->data[idx]) return false;
    return true;
}

bool String::operator==(char* c){
    unsigned int len = 0, idx;
    while (c[len] != '\0') len++;
    if (this->_size != len) return false;
    for (idx = 0; idx < len; idx++)
        if (data[idx] != c[idx]) return false;
    return true;
}

bool String::strncmp(char* c, unsigned int n){
    unsigned int idx = 0;
    while (idx < n && data[idx] != '\0'){
        if (data[idx] != c[idx]) return false;
        idx++;
    }
    return true;
}

bool String::strncmp(String* s, unsigned int n){
    return strncmp(s->data, n);
}

void String::release(){
    char* oldData = data;
    data = nullptr;
    _size = 0;
    delete [] oldData;
}

void String::PRINT(){
    std::cout << data;
}