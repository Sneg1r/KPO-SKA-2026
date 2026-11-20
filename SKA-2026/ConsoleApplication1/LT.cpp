#include "stdafx.h"
#include "Error.h"

namespace LT
{
	LexTable Create(int size)
	{
		if (size < 1 || size > LT_MAXSIZE)  throw ERROR_THROW(130);

		LexTable newLexTable;
		newLexTable.maxsize = size;
		newLexTable.size = 0;
		newLexTable.table = new Entry[size]{};

		return newLexTable;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.table == nullptr) throw ERROR_THROW(131);
		if (lextable.size == lextable.maxsize) throw ERROR_THROW(130);

		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (lextable.table == nullptr) throw ERROR_THROW(131);
		if (n < 0 || n > lextable.size) throw ERROR_THROW(132);

		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		if (lextable.table == nullptr) return;
		
		delete[] lextable.table;
		lextable.table = nullptr;
		lextable.size = 0;
	}
}