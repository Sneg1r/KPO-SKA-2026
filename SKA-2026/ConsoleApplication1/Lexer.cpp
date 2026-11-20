#include "stdafx.h"
#include "Lexer.h"

namespace LEXER
{
	Lexer::Lexer()
	{
		lexTable = LT::Create(LT_MAXSIZE);
		idTable = IT::Create(TI_MAXSIZE);

		line = 0;

		state = NORMAL;
		dataState = NONE;
	}

	void Lexer::Processing(char* source)
	{
		line = 1;
		state = LexState::NORMAL;

		int size = strlen(source);
		char lexema[TI_STR_MAXSIZE + 1]{};
		int lexemaLen = 0;
		int pos = 0;

		for (int i = 0; i < size; i++)
		{
			char ch = source[i];
			pos++;

			if (ch == ' ' || ch == '\t') { FlushLexema(lexema, lexemaLen, pos); continue; }

			if (ch == '\n' || ch == '\r') {
				FlushLexema(lexema, lexemaLen, pos);
				pos = 0;
				line++;
				continue;
			}

			if (strchr(";,{}()+-*/=", ch)) {
				FlushLexema(lexema, lexemaLen, pos);
				lexema[lexemaLen++] = ch;
				FlushLexema(lexema, lexemaLen, pos);
				continue;
			}

			//Cтрока
			if (ch == '\'') {
				FlushLexema(lexema, lexemaLen, pos);

				int j = i + 1;
				char strBuf[TI_STR_MAXSIZE + 1] = {};
				int strLen = 0;
				while (j < size && source[j] != '\'') {

					if (strLen >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(151, line, pos);

					strBuf[strLen++] = source[j++];
				}
				strBuf[strLen] = '\0';
				AddStrLiteral(strBuf, pos);
				i = j;
				continue;
			}
			//Буквы и цифры
			if (lexemaLen >= TI_STR_MAXSIZE)
				throw ERROR_THROW_IN(127, line, pos);

			lexema[lexemaLen++] = ch;
		}

		if (lexemaLen > 0) {
			lexema[lexemaLen] = '\0';
			FindFST(lexema, pos - lexemaLen);
		}
	}

	void Lexer::FindFST(char* lexema, int pos)
	{
		FST::FST fst = FSTFactory::Integer(lexema);

		CHECK_FST_DATA(Integer, LEX_INTEGER, INT)
		CHECK_FST_DATA(String, LEX_STRING, STR)
		CHECK_FST_STATE(Function, LEX_FUNCTION, AFTER_FUNCTION)
		CHECK_FST(Declare, LEX_DECLARE)
		CHECK_FST(Return, LEX_RETURN)
		CHECK_FST(Print, LEX_PRINT)
		CHECK_FST(Main, LEX_MAIN)
		CHECK_FST(Semicolon, LEX_SEMICOLON)
		CHECK_FST(Comma, LEX_COMMA)
		CHECK_FST(Leftbrace, LEX_LEFTBRACE)
		CHECK_FST(Bracelet, LEX_BRACELET)

		fst = FSTFactory::Leftthesis(lexema);
		if (FST::execute(fst)) {
			AddLexema(LEX_LEFTHESIS, line, LT_TI_NULLIDX);

			state = LexState::IN_PARAMS;
			return;
		}

		fst = FSTFactory::Righthesis(lexema);
		if (FST::execute(fst)) {
			AddLexema(LEX_RIGHTHESIS, line, LT_TI_NULLIDX);
			state = LexState::NORMAL;

			return;
		}

		CHECK_FST_OPERATOR(Equally, LEX_EQUALLY, (int)LEX_EQUALLY)
		CHECK_FST_OPERATOR(Plus, LEX_PLUS, (int)LEX_PLUS)
		CHECK_FST_OPERATOR(Minus, LEX_MINUS, (int)LEX_MINUS)
		CHECK_FST_OPERATOR(Star, LEX_STAR, (int)LEX_STAR)
		CHECK_FST_OPERATOR(Directslash, LEX_DIRSLASH, (int)LEX_DIRSLASH)

		fst = FSTFactory::Integer_Literal(lexema);
		if (FST::execute(fst)) {
			AddIntLiteral(lexema, pos);
			return;
		}

		fst = FSTFactory::Identifier(lexema);
		if (FST::execute(fst)) {
			AddIdentifier(lexema);
			return;
		}

		throw ERROR_THROW_IN(120, line, pos);
	}

	void Lexer::AddLexema(char code, int line, int idxTI)
	{
		LT::Entry entry;
		entry.lexema[0] = code;
		entry.sn = line;
		entry.idxTI = idxTI;

		LT::Add(lexTable, entry);
	}

	void Lexer::AddIdentifier(char* lexema)
	{
		int idx = IT::IsId(idTable, lexema);

		IT::IDTYPE idtype = IT::IDTYPE::V;

		if (state == LexState::AFTER_FUNCTION) {
			idtype = IT::IDTYPE::F;
			state = LexState::NORMAL;
		}

		else if (state == LexState::IN_PARAMS) {
			idtype = IT::IDTYPE::P;
		}

		if (idx == TI_NULLIDX)
		{
			IT::Entry idEntry{};
			strncpy_s(idEntry.id, ID_MAXSIZE, lexema, _TRUNCATE);

			switch (dataState) 
			{
				case INT: idEntry.iddatatype = IT::IDDATATYPE::INT; break;
				case STR: idEntry.iddatatype = IT::IDDATATYPE::STR;break;
				default: idEntry.iddatatype = IT::IDDATATYPE::INT;
			}

			dataState = NONE;

			idEntry.idtype = idtype;
			idEntry.idxfirstLE = lexTable.size;
			IT::Add(idTable, idEntry);
			idx = idTable.size - 1;
		}
		AddLexema(LEX_ID, line, idx);
	}

	void Lexer::AddIntLiteral(char* lexema, int pos) {
		if (lexema == nullptr || lexema[0] == '\0') {
			throw ERROR_THROW_IN(122, line, pos);
		}

		int value = ParseInt(lexema, line, pos);

		if(value > INT_MAX || value < INT_MIN)
			throw ERROR_THROW_IN(126, line, pos);
	
		IT::Entry idEntry{};
		
		idEntry.idxfirstLE = lexTable.size;
		idEntry.iddatatype = IT::IDDATATYPE::INT;
		idEntry.idtype = IT::IDTYPE::L;
		idEntry.value.vint = value;

		strncpy_s(idEntry.id, sizeof(idEntry.id), lexema, _TRUNCATE);
		IT::Add(idTable, idEntry);
		AddLexema(LEX_LITERAL, line, idTable.size - 1);
	}

	void Lexer::AddStrLiteral(char* lexema, int pos) {
		if (lexema == nullptr || lexema[0] == '\0') {
			throw ERROR_THROW_IN(122, line, pos);
		}

		IT::Entry idEntry{};

		idEntry.idxfirstLE = lexTable.size;
		idEntry.iddatatype = IT::IDDATATYPE::STR;
		idEntry.idtype = IT::IDTYPE::L;
		idEntry.value.vstr.len = (unsigned char)strlen(lexema);

		strncpy_s(idEntry.value.vstr.str, TI_STR_MAXSIZE, lexema, _TRUNCATE);
		strncpy_s(idEntry.id, sizeof(idEntry.id), lexema, _TRUNCATE);

		IT::Add(idTable, idEntry);
		AddLexema(LEX_LITERAL, line, idTable.size - 1);
	}

	void Lexer::FlushLexema(char* lexema, int& lexemaLen, int pos)
	{
		if (lexemaLen > 0) {
			lexema[lexemaLen] = '\0';
			FindFST(lexema, pos - lexemaLen);
			lexemaLen = 0;
		}
	}
	
	int Lexer::ParseInt(char* s, int line, int pos)
	{
		errno = 0;
		char* end = nullptr;
		long v = strtol(s, &end, 10);
		if (errno == ERANGE || v > INT_MAX || v < INT_MIN)
			throw ERROR_THROW_IN(126, line, pos);

		return (int)v;
	}
}