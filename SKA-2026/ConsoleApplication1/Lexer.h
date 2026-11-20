#pragma once

#include "LT.h"
#include "IT.h"
#include "FST.h"
#include "Error.h"
#include "FSTFactory.h"

namespace LEXER
{
	struct Lexer
	{
		enum LexState{
			NORMAL,
			AFTER_FUNCTION,
			IN_PARAMS,
		};

		enum DataTypeState {
			NONE,    
			INT,     
			STR      
		};
		
		LexState state;
		DataTypeState dataState;

		LT::LexTable lexTable;
		IT::IdTable idTable;

		int line;

		Lexer();
		
		void Processing(char* source);
		void FindFST(char* lexema, int pos);
		void AddLexema(char code, int line, int idxTI);
		void AddIdentifier(char* lexema);
		void AddIntLiteral(char* lexema, int pos);
		void AddStrLiteral(char* lexema, int pos);
		void FlushLexema(char* lexema, int& lexemaLen, int pos);
		int ParseInt(char* s, int line, int pos);
	};
}

