#include "common.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int blockSize = 32;

String::String()
{
	this->length = 0;
	this->allocSize = blockSize;
	this->string = new char[blockSize];
	memset(this->string, 0, this->allocSize);
}

String::String(const String &str)
{
	this->length = 0;
	this->allocSize = blockSize;
	this->string = new char[blockSize];
	memset(this->string, 0, this->allocSize);

	(*this) = str;
}

String::String(const char *szStr, ...)
{
	char *text = new char[1024+strlen(szStr)*2];
	va_list argp;

	va_start(argp, szStr);
	vsprintf(text, szStr, argp);
	va_end(argp);

	this->length = 0;
	this->allocSize = blockSize;
	this->string = new char[blockSize];
	memset(this->string, 0, this->allocSize);

	(*this) = text;
	delete []text;
}

String::~String()
{
	if (this->allocSize > 0 && this->string != 0)
	{
		delete [] this->string;
		this->string = 0;
		this->allocSize = 0;
		this->length = 0;
	}
}

String::operator char* ()
{
	return this->string;
}

String::operator const char* () const
{
	return this->string;
}

String& String::operator =(const String &str)
{
	if (str.allocSize > this->allocSize)
	{
		delete [] this->string;
		this->string = new char[str.allocSize];
		this->allocSize = str.allocSize;
	}
	memset(this->string, 0, this->allocSize);
	memcpy(this->string, str.string, str.length);
	this->length = str.length;

	return (*this);
}

String& String::operator =(const char *szStr)
{
	if (szStr != 0)
	{
		int strLength = strlen(szStr);
		if (strLength >= this->allocSize)
		{
			delete [] this->string;
			this->string = new char[strLength + 1];
			this->allocSize = strLength + 1;
		}
		memset(this->string, 0, this->allocSize);
		memcpy(this->string, szStr, strLength);
		this->length = strLength;
	}

	return (*this);
}

String String::operator +(const String &str)
{
	int newSize = this->length + str.length + 1;
	char* newString = new char[newSize];
	memset(newString, 0, newSize);

	strcpy(newString, this->string);
	strcat(newString, str.string);

	return String(newString);
}

String String::operator +(const char *szStr)
{
	if (szStr != 0)
	{
		int newSize = this->length + strlen(szStr) + 1;
		char* newString = new char[newSize];
		memset(newString, 0, newSize);

		strcpy(newString, this->string);
		strcat(newString, szStr);

		return String(newString);
	}
	return (*this);
}

String& String::operator +=(const String &str)
{
	int newSize = this->length + str.length + 1;
	char* newString = new char[newSize];
	memset(newString, 0, newSize);

	strcpy(newString, this->string);
	strcat(newString, str.string);

	(*this) = String(newString);

	return (*this);
}

String& String::operator +=(const char *szStr)
{
	if (szStr != 0)
	{
		int newSize = this->length + strlen(szStr) + 1;
		char* newString = new char[newSize];
		memset(newString, 0, newSize);

		strcpy(newString, this->string);
		strcat(newString, szStr);

		(*this) = String(newString);
	}
	return (*this);
}

bool String::operator ==(const String &str)
{
	if (this->length == str.length)
	{
		for(int i = 0; i < str.length; i++)
		{
			if (this->string[i] != str.string[i]) return false;
		}
		return true;
	}
	return false;
}

bool String::operator ==(const char *szStr)
{
	if (szStr != 0)
	{
		int strLength = strlen(szStr);

		if (this->length == strLength)
		{
			for(int i = 0; i < strLength; i++)
			{
				if (this->string[i] != szStr[i]) return false;
			}
			return true;
		}
	}
	return false;
}

bool String::operator !=(const String &str)
{
	return !((*this) == str);
}

bool String::operator !=(const char *szStr)
{
	return !((*this) == szStr);
}

int String::Length()
{
	return this->length;
}

void String::ToLower()
{
	for (int i = 0; i < this->length; i++)
	{
		this->string[i] = tolower(this->string[i]);
	}
}

void String::ToUpper()
{
}

void String::TrimFrontToChar(char character)
{
	for (int i = 0; i < this->length; i++)
	{
		if (this->string[i] == character)
		{
			(*this) = (String)(this->string+i+1);
			return;
		}
	}
}

void String::TrimEndToChar(char character)
{
	for (int i = this->length-1; i >= 0; i--)
	{
		if (this->string[i] == character)
		{
			this->string[i] = '\0';
			this->length -= i;
			return;
		}
	}
}

void String::TrimEnd(int size)
{
	for (int i = 0; i < size; i++)
	{
		this->string[this->length-1-i] = '\0';
	}
	this->length -= size;
}

bool String::Contains(const char* str)
{
	int len = strlen(str);
	for (int i = 0; i < this->length; i++)
	{
		if ((i + len) > this->length)
			return false;

		if (this->string[i] == str[0])
		{
			if (strncmp(this->string+i, str, len) == 0)
				return true;
		}
	}
	return false;
}

StringList String::Split(const char chr)
{
	StringList result;

	int lastSplit = 0;

	for (int i = 0; i < this->length; i++)
	{
		if (this->string[i] == chr)
		{
			result.Add(this->Copy(lastSplit, i-lastSplit));

			lastSplit = i+1;
		}
	}

	if (lastSplit < this->length)
	{
		result.Add(this->Copy(lastSplit, this->length-lastSplit));
	}
	return result;
}

String String::CopyMax(int max)
{
	String tmp = this->string;
	tmp[max] = 0;
	return (const char*)tmp;
}

String String::Copy(int start, int end)
{
	String tmp = this->string + start;
	tmp[end] = 0;
	return (const char*)tmp;
}

int String::ToInt()
{
	return atoi(this->string);
}


/* STATIC METHODS */


int String::Length(const char* subject)
{
	int r = 0;

	if (subject != 0)
		while (subject[r] != '\0') r++;

	return r;
}

void String::StringCopy(char* dest, const char* src)
{
	int len = String::Length(src);
	int i = 0;

	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

void String::StringCopyMax(char* dest, const char* src, int max)
{
	int len = String::Length(src);
	int i = 0;

	if (len > max) len = max;

	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

const char* String::FindCharacter(const char* subject, char c)
{
	while (subject[0] != '\0')
	{
		if (subject[0] == c)
			return subject;
		subject++;
	}
	return 0;
}

const char* String::FindCharacterReverse(const char* subject, char c)
{
	int len = String::Length(subject);

	for (int i = len; i >= 0; i--)
	{
		if (subject[i] == c)
			return subject + i;
	}
	return 0;
}

int String::LocateCharacter(const char* subject, char c)
{
	int len = String::Length(subject);

	for (int i = 0; i < len; i++)
	{
		if (subject[i] == c)
			return i;
	}
	return -1;
}

int String::LocateCharacterReverse(const char* subject, char c)
{
	int len = String::Length(subject);

	for (int i = len - 1; i >= 0; i--)
	{
		if (subject[i] == c)
			return i;
	}
	return 0;
}

int String::StringCompare(const char* a, const char* b)
{
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0')
	{
		if (a[i] > b[i])
			return 1;
		if (a[i] < b[i])
			return -1;
		i++;
	}
	return 0;
}
