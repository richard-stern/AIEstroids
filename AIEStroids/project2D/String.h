#ifndef STRING_H
#define STRING_H

#include <ostream> // must have this because we would like std::ostream to work. @cleanup when we have our own console, we can get rid of this

enum ASCII {
    NUL             =   0,
    BACK_SPACE      =   8,
    TAB             =   9,
    CANCEL          =  24,
    ESC             =  27,
    SPACE           =  32,
    DELETE          = 127,
    CARRIAGE_RETURN =  13,
    LINE_FEED       =  10,   // windows returns CR followed by LINE_FEED when enter is pressed. linux only returns LINE_FEED. Mac only returns CR. <!> double check this
};

struct String {
    char* data = nullptr; // <!> Please use init_string_with_terminator() when initialize this variable to anything. This makes sure to add a null terminator at the end of the string
    size_t size = 0; // <!> don't remove this. Because there could be a string of characters without \0 at the end of them. We use can use size to get around this problem
    
    //
    // STATIC METHODS
    //
    static size_t string_length(const char* _data);
    static void string_copy(const char* _source, char* _destination, size_t _length = 0);
    
    String();
    String(char _data);
    String(const char* _data);
    // String(const String& _other);

    // <!> calls clear and cleans up memory
    ~String();

    // append is safe when data is nullptr, because we check size
    void append(const char* _data, size_t _length); 
    void append(const String& _data, size_t _length); 

    // get a char from string
    char& operator[](size_t _index) const;
    String& operator=(const String& _other);

    //  delete string and set size to 0
    void clear();

    //
    // OPERATORS
    //

    friend std::ostream& operator<<(std::ostream& _os, const String& _data);
    String& operator+(const String& _other);
};

#endif // STRING_H