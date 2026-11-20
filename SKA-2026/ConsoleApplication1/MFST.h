#pragma once
#include <stack>
#include <iomanip>
#include "GRB.h"
#include "Lexer.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

class MFSTSTSTACK : public std::stack<short> {        // стек автомата
public:
	using std::stack<short>::c;
};

namespace MFST
{
	struct MfstState                     // состояние автомата (для сохранения)
	{
		short lenta_position;            // позиция на ленте
		short nrule;                     // номер текущего правила
		short nrulechain;                // номер текущей цепочки, текущего правила
		MFSTSTSTACK st;                  // стек автомата
		MfstState();
		MfstState(
			short pposition,             // позиция на ленте
			MFSTSTSTACK pst,             // стек автомата
			short pnrulechain            // номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,			 // позиция на ленте
			MFSTSTSTACK pst,
			short pnrule,                // номер текущего правила
			short pnrulechain            // номер текущей цепочки, текущего правила
		);
	};

	class MFSTSTATE : public std::stack<MfstState> {  // стек автомата
	public:
		using std::stack<MfstState>::c;
	};

	struct Mfst                          // магазинный автомат
	{
		enum RC_STEP {
			NS_OK,                       // код возврата функции step
			NS_NORULE,                   // найдено правило и цепочка, цепочка записана в стек
			NS_NORULECHAIN,              // не найдено правило грамматики (ошибка в грамматике)
			NS_ERROR,                    // не найдена подходящая цепочка правила (ошибка в исходном коде)
			TS_OK,                       // неизвестный нетерминальный символ грамматики
			TS_NOK,                      // тек. символ ленты == вершине стека, продвинулась лента, pop стека
			LENTA_END,                   // тек. символ ленты != вершине стека, восстановлено состояние
			SURPRISE                     // текущая позиция ленты >= lenta_size
										 // неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis             // диагностика
		{
			short lenta_position;        // позиция на ленте
			RC_STEP rc_step;             // код завершения шага
			short nrule;                 // номер правила
			short nrule_chain;           // номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(               // диагностика
				short plenta_position,   // позиция на ленте
				RC_STEP prc_step,        // код завершения шага
				short pnrule,            // номер правила
				short pnrule_chain       // номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];  // последние самые глубокие сообщения

		GRBALPHABET* lenta;              // перекодированная (TS/NS) лента (из LEX)
		short lenta_position;            // текущая позиция на ленте
		short nrule;                     // номер текущего правила
		short nrulechain;                // номер текущей цепочки, текущего правила
		short lenta_size;                // размер ленты
		GRB::Greibach greibach;          // грамматика Грейбах
		LEXER::Lexer lex;                    // результат работы лексического анализатора
		MFSTSTSTACK st;                  // стек автомата
		MFSTSTATE storestate;            // стек для сохранения состояний
		Mfst();
		Mfst(
			LEXER::Lexer plex,               // результат работы лексического анализатора
			GRB::Greibach pgreibach      // грамматика Грейбах
		);

		char* getCSt(char* buf);         // получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25); // лента: n символов с pos
		char* getDiagnosis(short n, char* buf); // получить n-ую строку диагностики или 0x00
		bool savestate();                // сохранить состояние автомата
		bool reststate();                // восстановить состояние автомата
		bool push_chain(                 // поместить цепочку правила в стек
			GRB::Rule::Chain chain       // цепочка правила
		);

		RC_STEP step();                  // выполнить шаг автомата
		bool start();                    // запустить автомат
		bool savediagnosis(
			RC_STEP pprc_step            // код завершения шага
		);

		void printrules();               // вывести последовательность правил

		struct Deduction                 // вывод
		{
			short size;                  // количество шагов в выводе
			short* nrules;               // номера правил грамматики
			short* nrulechains;          // номера цепочек правил грамматики (nrules)
			Deduction() { size = 0; nrules = 0; nrulechains = 0; };
		} deduction;
		bool savededuction();            // сохранить дерево вывода
	};
}