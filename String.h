/*#################################################################
# Copyright (c) 1991 AT&T Bell Laboratories, All Rights Reserved   
# Published in ``A C++ Primer''  by Stanley Lippman, Addison-Wesley
#################################################################*/

#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string>

class String;
class StringIterator {
public:
	StringIterator(String& s) { 
		ps = &s; index = 0; }
	char operator()();
private:
	String *ps;
	int index;
};

const int String_size = 1024; // arbitrary constant

class String {
    friend ostream& operator <<(ostream&,String&);
    friend istream& operator >>(istream&,String&);
    friend String operator+(String&,String&);
    friend class StringIterator;
public:
    String(int);
    String(const char*);
    String(const String&);
    String();
    ~String() { delete str; }

    String& operator()(int,int);
    char& operator[](int);
    String& operator=(const char*);
    String& operator=(const String&);
    String& operator+=(const String&);
    int operator==(const String &s); 

    int operator==(const char *s) { 
        return (strcmp(str,s)==0); }
    void print() { 
         cout<< "< " << len << ", " << str << " >\n";}

    int operator!() { return( len == 0 ); } 
    inline void checkBounds(int);
    length() { return len; }
    operator <( String& s);
    operator >( String& s);
    void set(char*);
private:
    int len;
    char *str;
};

#endif
