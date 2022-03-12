
#ifndef _STRING_
#define _STRING_

class String
{
private:
    char* data;
    unsigned int _size;
public:
    String() : data(nullptr), _size(0) {}
    ~String() { delete [] data; }
    unsigned int size() { return _size; }
    unsigned int length() { return _size; }
    bool set(const char* c) { return set(const_cast<char*>(c)); }
    bool set(char* c);
    char operator[](unsigned int idx);
    bool operator+=(String* s);
    bool operator+=(String s) { return operator+=(&s); }
    bool operator==(String* s);
    bool operator==(String s) { return operator==(&s); }
    bool operator==(char* c);
    bool operator==(const char* c) { return operator==(const_cast<char *>(c)); }
    bool strncmp(char* c, unsigned int n);
    bool strncmp(const char* c, unsigned int n) { return strncmp(const_cast<char *>(c), n); }
    bool strncmp(String* s, unsigned int n);
    bool strncmp(String s, unsigned int n) { return strncmp(&s, n); }
    void release();
    void PRINT();
};

#endif