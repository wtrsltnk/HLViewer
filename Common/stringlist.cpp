#include "common.h"

StringList::StringList()
		: list(0), lastItem(0), length(0), lastAccessedIndex(0), lastAccessed(0)
{
}

StringList::StringList(const StringList& orig)
		: list(0), lastItem(0), length(0), lastAccessedIndex(0), lastAccessed(0)
{
	(*this) = orig;
}

StringList::~StringList()
{
	tStringListItem* item = this->list;
	while (item != 0)
	{
		tStringListItem* tmp = item->next;
		delete item;
		item = tmp;
	}
	this->list = 0;
}

StringList& StringList::operator =(const StringList &orig)
{
	tStringListItem* item = orig.list;
	while (item != 0)
	{
		this->Add(item->string);
		item = item->next;
	}
	return (*this);
}

String StringList::At(int index)
{
	if (index >= 0 && index < this->length)
	{
		tStringListItem* item = this->list;
		while (item != 0)
		{
			if (item->index == index)
				return item->string;
			item = item->next;
		}
	}
	return "";
}

String StringList::operator [](int index)
{
	return this->At(index);
}

int StringList::Add(String str)
{
	tStringListItem* newItem = new tStringListItem;

	newItem->index = this->length;
	newItem->string = str;
	newItem->next = 0;
	newItem->prev = this->lastItem;
	if (this->lastItem != 0)
		this->lastItem->next = newItem;
	this->lastItem = newItem;

	if (this->list == 0)
		this->list = newItem;

	return this->length++;
}

int StringList::Length()
{
	return this->length;
}

