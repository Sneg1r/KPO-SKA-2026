#include "stdafx.h"

namespace IT    
{
    IdTable Create(int size)
    {
		if (size < 1 || size > TI_MAXSIZE) throw ERROR_THROW(140);

		IdTable newIdTable;
		newIdTable.maxsize = size;
		newIdTable.size = 0;
		newIdTable.table = new Entry[size]{};

		return newIdTable;
    }

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.table == nullptr) throw ERROR_THROW(141);
		if(idtable.size >= idtable.maxsize) throw ERROR_THROW(140);
		
		idtable.table[idtable.size++] = entry;
	}

	Entry& GetEntry(IdTable &idtable, int n)
	{
		if (idtable.table == nullptr) throw ERROR_THROW(141);
		if (n < 0 || n >= idtable.size) throw ERROR_THROW(142);

		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		if (idtable.table == nullptr) throw ERROR_THROW(141);
		if (strlen(id) == 0) throw ERROR_THROW(144);
	
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0) return i;
		}

		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		if (idtable.table == nullptr) return;
		
		delete[] idtable.table;
		idtable.table = nullptr;
		idtable.size = 0;
	}
}
