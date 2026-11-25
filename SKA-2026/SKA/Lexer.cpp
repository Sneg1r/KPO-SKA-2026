#include "stdafx.h"
#include "Lexer.h"

namespace LEXER
{
	Lexer::Lexer()
	{
		lexTable = LT::Create(LT_MAXSIZE);
		idTable = IT::Create(TI_MAXSIZE);
		line = 0; lastFuncIdx = -1;
		state = NORMAL;
	}

	void Lexer::Processing(In::IN in)
	{
		line = 1;
		state = LexState::NORMAL;

		int size = strlen(in.redactedText);
		char lexema[TI_STR_MAXSIZE + 1]{};
		int lexemaLen = 0;
		int currWord = -1;

		for (int i = 0; i < size; i++)
		{
			char ch = in.redactedText[i];

			switch (ch) {
			case '\n': line++;
			case SEPARATOR: FlushLexema(lexema, lexemaLen, in.posSimbols[currWord]); break;
			case '\"': {
				FlushLexema(lexema, lexemaLen, in.posSimbols[currWord]);

				int j = i + 1;
				char strBuf[TI_STR_MAXSIZE + 1] = {};
				int strLen = 0;
				while (j < size && in.redactedText[j] != '\"') {

					if (strLen >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(151, line, in.posSimbols[currWord]);

					strBuf[strLen++] = in.redactedText[j++];
				}
				strBuf[strLen] = '\0';
				AddStrLiteral(strBuf, in.posSimbols[currWord]);
				i = j;
			} break;
			case '\'': {
				FlushLexema(lexema, lexemaLen, in.posSimbols[currWord]);

				int j = i + 1;
				char strBuf[TI_STR_MAXSIZE + 1] = {};
				int strLen = 0;
				while (j < size && in.redactedText[j] != '\'') {

					if (strLen >= TI_STR_MAXSIZE)
						throw ERROR_THROW_IN(151, line, in.posSimbols[currWord]);

					strBuf[strLen++] = in.redactedText[j++];
				}
				strBuf[strLen] = '\0';
				AddCharLiteral(strBuf, in.posSimbols[currWord]);
				i = j;
			} break;
			case '=': {
				if (i + 2 < size && in.redactedText[i + 2] == '=') {
					lexema[0] = '='; lexema[1] = '='; lexema[2] = '\0';
					FlushLexema(lexema, lexemaLen, in.posSimbols[currWord]);
					i++;
				}
			}
			default: {
				if (lexemaLen >= TI_STR_MAXSIZE)
					throw ERROR_THROW_IN(127, line, in.posSimbols[currWord]);

				if (lexemaLen == 0) currWord++;

				lexema[lexemaLen++] = ch;
			} break;
			}
		}
		if (lexemaLen > 0) {
			lexema[lexemaLen] = '\0';
			FindFST(lexema, in.posSimbols[currWord]);
		}
	}

	void Lexer::FindFST(char* lexema, int pos)
	{
		FST::FST fst = FSTFactory::Integer(lexema);

		CHECK_FST_DATA(Integer, LEX_INTEGER, IT::INT)
		CHECK_FST_DATA(String, LEX_STRING, IT::STR)
		CHECK_FST_DATA(Char, LEX_CHAR, IT::CHAR)
		CHECK_FST_DATA(Void, LEX_VOID, IT::VOID)

		CHECK_FST_STATE(Function, LEX_FUNCTION, AFTER_FUNCTION)
		CHECK_FST(Return, LEX_RETURN)

		CHECK_FST(If, LEX_IF)			CHECK_FST(Then, LEX_THEN)			CHECK_FST(Else, LEX_ELSE)
		CHECK_FST(While, LEX_WHILE)
		CHECK_FST(And, LEX_AND)			CHECK_FST(Or, LEX_OR)				CHECK_FST(No, LEX_NO)
		CHECK_FST(Set, LEX_SET)			CHECK_FST(SetType, LEX_SETTYPE)

		CHECK_FST(Input, LEX_INPUT)		CHECK_FST(True, LEX_TRUE)		CHECK_FST(From, LEX_FROM)
		CHECK_FST(Print, LEX_PRINT)		CHECK_FST(False, LEX_FALSE)		CHECK_FST(To, LEX_TO)
		CHECK_FST(Main, LEX_MAIN)

		CHECK_FST(Semicolon, LEX_SEMICOLON)
		CHECK_FST(Comma, LEX_COMMA)
		CHECK_FST(Leftbrace, LEX_LEFTBRACE)		CHECK_FST(Bracelet, LEX_BRACELET)
		CHECK_FST(Leftsquare, LEX_LEFTSQUARE)	CHECK_FST(Rightsquare, LEX_RIGHTSQUARE)

		fst = FSTFactory::Leftthesis(lexema);
		if (FST::execute(fst)) {
			AddLexema(LEX_LEFTHESIS, line, LT_TI_NULLIDX);

			if (state == LexState::AFTER_FUNCTION) state = LexState::IN_PARAMS;
			return;
		}

		fst = FSTFactory::Righthesis(lexema);
		if (FST::execute(fst)) {
			AddLexema(LEX_RIGHTHESIS, line, LT_TI_NULLIDX);
			state = LexState::NORMAL;

			return;
		}

		CHECK_FST(Less, LEX_LESS)
			CHECK_FST(More, LEX_MORE)
			CHECK_FST(Equally, LEX_EQUALLY)
			CHECK_FST_OPERATOR(Plus, LEX_PLUS, (int)LEX_PLUS)
			CHECK_FST_OPERATOR(Minus, LEX_MINUS, (int)LEX_MINUS)
			CHECK_FST_OPERATOR(Star, LEX_STAR, (int)LEX_STAR)
			CHECK_FST_OPERATOR(Directslash, LEX_DIRSLASH, (int)LEX_DIRSLASH)
			CHECK_FST_OPERATOR(Residue, LEX_RESIDUE, (int)LEX_RESIDUE)

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
		}

		else if (state == LexState::IN_PARAMS) {
			idtype = IT::IDTYPE::P;
		}

		if (idx == TI_NULLIDX)
		{
			IT::Entry idEntry{};
			strncpy_s(idEntry.id, ID_MAXSIZE, lexema, _TRUNCATE);

			idEntry.idtype = idtype;
			idEntry.iddatatype = IT::NONE;
			idEntry.idxfirstLE = lexTable.size;
			IT::Add(idTable, idEntry);
			idx = idTable.size - 1;
		}

		if (idtype == IT::IDTYPE::F) lastFuncIdx = idx;
		AddLexema(LEX_ID, line, idx);
	}

	void Lexer::AddIntLiteral(char* lexema, int pos) {
		if (lexema == nullptr || lexema[0] == '\0') {
			throw ERROR_THROW_IN(122, line, pos);
		}

		int value = ParseInt(lexema, line, pos);

		if (value > INT_MAX || value < INT_MIN)
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

	void Lexer::AddCharLiteral(char* lexema, int pos) {
		if (lexema == nullptr || lexema[1] != '\0') {
			throw ERROR_THROW_IN(126, line, pos);
		}

		IT::Entry idEntry{};

		idEntry.idxfirstLE = lexTable.size;
		idEntry.iddatatype = IT::IDDATATYPE::CHAR;
		idEntry.idtype = IT::IDTYPE::L;
		idEntry.value.vchar = lexema[0];

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
			FindFST(lexema, pos);
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

	void Lexer::SetTypeLastIT(IT::IDDATATYPE type)
	{
		int n = lexTable.size;

		// [n-1] = тип, [n-2] = ':', [n-3] = id или ')'
		if (n < 3 || lexTable.table[n - 2].lexema[0] != LEX_SETTYPE) return;

		const LT::Entry& before = lexTable.table[n - 3];
		int idx = -1;
		if (before.lexema[0] == LEX_ID) idx = before.idxTI;
		else if (before.lexema[0] == LEX_RIGHTHESIS) idx = lastFuncIdx;

		if (idx >= 0) IT::GetEntry(idTable, idx).iddatatype = type;
	}
}