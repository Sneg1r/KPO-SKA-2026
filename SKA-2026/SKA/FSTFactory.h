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
        SetTypeLastIT(TYPE);			           \
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
	FST::FST Char(char* lexema);

	FST::FST Function(char* lexema);
	FST::FST Void(char* lexema);
	FST::FST Return(char* lexema);

	FST::FST If(char* lexema);
	FST::FST Then(char* lexema);
	FST::FST Else(char* lexema);
	FST::FST While(char* lexema);
	FST::FST And(char* lexema);
	FST::FST Or(char* lexema);
	FST::FST No(char* lexema);
	FST::FST SetType(char* lexema);
	FST::FST Set(char* lexema);

	FST::FST Input(char* lexema);
	FST::FST Print(char* lexema);
	FST::FST Main(char* lexema);
	FST::FST True(char* lexema);
	FST::FST False(char* lexema);

	FST::FST From(char* lexema);
	FST::FST To(char* lexema);

	FST::FST Semicolon(char* lexema);
	FST::FST Comma(char* lexema);
	FST::FST Leftbrace(char* lexema);
	FST::FST Bracelet(char* lexema);
	FST::FST Leftthesis(char* lexema);
	FST::FST Righthesis(char* lexema);
	FST::FST Leftsquare(char* lexema);
	FST::FST Rightsquare(char* lexema);

	FST::FST Less(char* lexema);
	FST::FST More(char* lexema);
	FST::FST Equally(char* lexema);
	FST::FST Plus(char* lexema);
	FST::FST Minus(char* lexema);
	FST::FST Star(char* lexema);
	FST::FST Directslash(char* lexema);
	FST::FST Residue(char* lexema);

	FST::FST Integer_Literal(char* lexema);
	FST::FST Identifier(char* lexema);
}
