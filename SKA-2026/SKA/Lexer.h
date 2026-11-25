#pragma once

#include "LT.h"
#include "IT.h"
#include "In.h"
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
		
		LexState state;

		LT::LexTable lexTable;
		IT::IdTable idTable;

		int line;
		int lastFuncIdx;

		Lexer();
		
		void Processing(In::IN in);
		void FindFST(char* lexema, int pos);
		void AddLexema(char code, int line, int idxTI);
		void AddIdentifier(char* lexema);
		void AddIntLiteral(char* lexema, int pos);
		void AddCharLiteral(char* lexema, int pos);
		void AddStrLiteral(char* lexema, int pos);
		void FlushLexema(char* lexema, int& lexemaLen, int pos);
		int ParseInt(char* s, int line, int pos);
		void SetTypeLastIT(IT::IDDATATYPE type);
	};
}

