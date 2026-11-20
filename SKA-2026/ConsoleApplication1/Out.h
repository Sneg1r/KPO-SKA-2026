#pragma once
#include <fstream>
#include "In.h" 
#include "Parm.h"  
#include "Error.h"      
#include "LT.h"
#include "IT.h"

namespace Out 
{
	struct OUT
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	OUT getOut(wchar_t logfile[]);
	void WriteLine(OUT out, const char* text);
	void WriteLexTable(LT::LexTable& lextable, OUT out);
	void WriteIdentificatorTable(IT::IdTable& idTable, OUT out);
	void WriteWorkProtocol(LT::LexTable& lextable, IT::IdTable& idTable, OUT out);
	void WriteIn(OUT out, char* text);
	void Close(OUT out);
}
