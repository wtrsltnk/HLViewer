#ifndef STRING_H_
#define STRING_H_

#include <string.h>

class StringList;
class String
{
private:
    char* string;
    int length;
    int allocSize;

public:
    String();
    String(const String &str);
    String(const char *str, ...);
    virtual ~String();

    operator char* ();
    operator const char* () const;

    String& operator =(const String &str);
    String& operator =(const char *szStr);

    String operator +(const String &str);
    String operator +(const char *szStr);

    String& operator +=(const String &str);
    String& operator +=(const char *szStr);

    bool operator ==(const String &str);
    bool operator ==(const char *szStr);

    bool operator !=(const String &str);
    bool operator !=(const char *szStr);

    int Length();
    void ToLower();
    void ToUpper();
    void TrimFrontToChar(char character);
    void TrimEndToChar(char character);
    void TrimEnd(int size);
    bool Contains(const char* str);

    StringList Split(const char chr);

    String CopyMax(int max);
    String Copy(int start, int end);

    int ToInt();

public:
    static int Length(const char* subject);
    static void StringCopy(char* dest, const char* src);
    static void StringCopyMax(char* dest, const char* src, int max);
    static const char* FindCharacter(const char* subject, char c);
    static const char* FindCharacterReverse(const char* subject, char c);
    static int LocateCharacter(const char* subject, char c);
    static int LocateCharacterReverse(const char* subject, char c);
    static int StringCompare(const char* a, const char* b);

};

class StringList
{
public:
    StringList();
    StringList(const StringList &orig);
    virtual ~StringList();

    StringList& operator=(const StringList &orig);
    String operator[] (int index);

    int Length();
    String At(int index);
    int Add(String str);

private:
    typedef struct sStringListItem
    {
        int index;
        String string;
        sStringListItem* prev;
        sStringListItem* next;

    } tStringListItem;

    int length;
    tStringListItem* list;
    tStringListItem* lastItem;
    int lastAccessedIndex;
    tStringListItem* lastAccessed;
};

#endif /*STRING_H_*/
