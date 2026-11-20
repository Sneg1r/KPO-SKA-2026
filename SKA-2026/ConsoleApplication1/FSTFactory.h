#pragma once
#include "FST.h"

#define CHECK_FST(FACTORY, TOKEN)				\
fst = FSTFactory::FACTORY(lexema);				\
if (FST::execute(fst)) {						\
	AddLexema(TOKEN, line, LT_TI_NULLIDX);	\
	return;										\
}

#define CHECK_FST_STATE(FACTORY, TOKEN, NEWSTATE)    \
    fst = FSTFactory::FACTORY(lexema);             \
    if (FST::execute(fst)) {                       \
        AddLexema(TOKEN, line, LT_TI_NULLIDX);     \
        state = NEWSTATE;                          \
        return;                                     \
    }

#define CHECK_FST_DATA(FACTORY, TOKEN, TYPE)    \
    fst = FSTFactory::FACTORY(lexema);             \
    if (FST::execute(fst)) {                       \
        AddLexema(TOKEN, line, LT_TI_NULLIDX);     \
        dataState = TYPE;                          \
        return;                                     \
    }

#define CHECK_FST_OPERATOR(FACTORY, TOKEN, ID)    \
    fst = FSTFactory::FACTORY(lexema);             \
    if (FST::execute(fst)) {						\
		char lexCode = TOKEN == LEX_EQUALLY ? LEX_EQUALLY : LEX_PLUS;	\
        AddLexema(lexCode, line, ID);                 \
        return;                                     \
    }



namespace FSTFactory
{
	FST::FST Integer(char* lexema);
	FST::FST String(char* lexema);
	FST::FST Function(char* lexema);
	FST::FST Declare(char* lexema);
	FST::FST Return(char* lexema);
	FST::FST Print(char* lexema);
	FST::FST Main(char* lexema);
	FST::FST Semicolon(char* lexema);
	FST::FST Comma(char* lexema);
	FST::FST Leftbrace(char* lexema);
	FST::FST Bracelet(char* lexema);
	FST::FST Leftthesis(char* lexema);
	FST::FST Righthesis(char* lexema);
	FST::FST Equally(char* lexema);
	FST::FST Plus(char* lexema);
	FST::FST Minus(char* lexema);
	FST::FST Star(char* lexema);
	FST::FST Directslash(char* lexema);
	FST::FST Integer_Literal(char* lexema);
	FST::FST Identifier(char* lexema);
}
