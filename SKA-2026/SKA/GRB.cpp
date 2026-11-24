#include "stdafx.h"
#include "GRB.h"

#define GRB_ERROR_SERIES 600

namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)
    Greibach greibach(NS('S'), TS('$'),               
        6,                                            
        Rule(NS('S'), GRB_ERROR_SERIES + 0,           
            7,      // S->m{NrE;} | fi(F):t{NrE;}S | fi():~{N}S | m{NrE;}S | fi(F):t{NrE;} | fi():~{N} | fi():~{N}S
            Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
            Rule::Chain(14, TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(':'), TS('t'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
            Rule::Chain(10, TS('f'), TS('i'), TS('('), TS(')'), TS(':'), TS('~'), TS('{'), NS('N'), TS('}'), NS('S')),
            Rule::Chain(8, TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
            Rule::Chain(13, TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(':'), TS('t'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
            Rule::Chain(9, TS('f'), TS('i'), TS('('), TS(')'), TS(':'), TS('~'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(10, TS('f'), TS('i'), TS('('), TS(')'), TS(':'), TS('~'), TS('{'), NS('N'), TS('}'), NS('S'))
        ),
        Rule(NS('N'), GRB_ERROR_SERIES + 1, // Ошибочный оператор
            29,      // N-> i(); | i(W); | i:t; | i:t[E]; | i:t=E; | rE; | i=E; | i[E]=E; | dtfi(F) | ?(E)>{N} | ?(E)>{N}<{N} | i();N | i(W);N | i:t;N | i:t[E];N | rE;N | i=E;N  | i[l]=E;N | dtfi(F);N | p(E); |  p(E);N | #(W); | #(W);N |?(E)>{N}N;
            Rule::Chain(4, TS('i'), TS('('), TS(')'), TS(';')),
            Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), TS(';')),
            Rule::Chain(4, TS('i'), TS(':'), TS('t'), TS(';')),
            Rule::Chain(7, TS('i'), TS(':'), TS('t'), TS('['), NS('E'), TS(']'), TS(';')),
            Rule::Chain(6, TS('i'), TS(':'), TS('t'), TS('='), NS('E'), TS(';')),
            Rule::Chain(3, TS('r'), NS('E'), TS(';')),
            Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
            Rule::Chain(7, TS('i'), TS('['), NS('E'), TS(']'), TS('='), NS('E'), TS(';')),
            Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
            Rule::Chain(7, TS('w'), TS('('), NS('E'), TS(')'),TS('{'), NS('N'), TS('}')),
            Rule::Chain(8, TS('?'), TS('('), NS('E'), TS(')'), TS('>'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(12, TS('?'), TS('('), NS('E'), TS(')'), TS('>'), TS('{'), NS('N'), TS('}'), TS('<'), TS('{'), NS('N'), TS('}')),
            Rule::Chain(5, TS('p'), TS('('), NS('E'), TS(')'), TS(';')),
            Rule::Chain(5, TS('#'), TS('('), NS('W'), TS(')'), TS(';')),

            Rule::Chain(5, TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
            Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(5, TS('i'), TS(':'), TS('t'), TS(';'), NS('N')),
            Rule::Chain(8, TS('i'), TS(':'), TS('t'), TS('['), NS('E'), TS(']'), TS(';'), NS('N')),
            Rule::Chain(7, TS('i'), TS(':'), TS('t'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(4, TS('r'), NS('E'), TS(';'), NS('N')),
            Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(8, TS('i'), TS('['), NS('E'), TS(']'), TS('='), NS('E'), TS(';'), NS('N')),
            Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(8, TS('w'), TS('('), NS('E'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(6, TS('p'), TS('('), NS('E'), TS(')'), TS(';'), NS('N')),
            Rule::Chain(9, TS('?'), TS('('), NS('E'), TS(')'), TS('>'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(13, TS('?'), TS('('), NS('E'), TS(')'), TS('>'), TS('{'), NS('N'), TS('}'), TS('<'), TS('{'), NS('N'), TS('}'), NS('N')),
            Rule::Chain(6, TS('#'), TS('('), NS('W'), TS(')'), TS(';'), NS('N'))
        ),
        Rule(NS('E'), GRB_ERROR_SERIES + 2, // Ошибка в выражении
            11,      // E->i|i[E]|l|!E|(E)|i(W)|iM|i[E]M|lM|(E)M|i(W)M
            Rule::Chain(1, TS('i')),
            Rule::Chain(4, TS('i'), TS('['), NS('E'), TS(']')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(2, TS('!'), NS('E')),
            Rule::Chain(3, TS('('), NS('E'), TS(')')),
            Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
            Rule::Chain(2, TS('i'), NS('M')),
            Rule::Chain(5, TS('i'), TS('['), NS('E'),TS(']'),NS('M')),
            Rule::Chain(2, TS('l'), NS('M')),
            Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
            Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
        ),
        Rule(NS('M'), GRB_ERROR_SERIES + 3, // Ошибка в хвосте операции
            6, // M → vE|cE|&E||E|vEM|vEM|cEM
            Rule::Chain(2, TS('v'), NS('E')),
            Rule::Chain(2, TS('c'), NS('E')),
            Rule::Chain(2, TS('&'), NS('E')),
            Rule::Chain(2, TS('|'), NS('E')),
            Rule::Chain(3, TS('v'), NS('E'), NS('M')),
            Rule::Chain(3, TS('c'), NS('E'), NS('M'))
        ),
        Rule(NS('F'), GRB_ERROR_SERIES + 4, // Ошибка в списке параметров
            4, // F → i:t|i:t[E]|i:t,F|i:t[E],F|
            Rule::Chain(3, TS('i'), TS(':'), TS('t')),
            Rule::Chain(6, TS('i'), TS(':'), TS('t'), TS('['), NS('E'), TS(']')),
            Rule::Chain(5, TS('i'), TS(':'), TS('t'), TS(','), NS('F')),
            Rule::Chain(8, TS('i'), TS(':'), TS('t'), TS('['), NS('E'), TS(']'), TS(','), NS('F'))
        ),
        Rule(NS('W'), GRB_ERROR_SERIES + 5, // Ошибка в списке аргументов
            6, // W → i|l|i,W|l,W
            Rule::Chain(1, TS('i')),
            Rule::Chain(1, TS('l')),
            Rule::Chain(4, TS('i'), TS('['), NS('E'), TS(']')),
            Rule::Chain(3, TS('i'), TS(','), NS('W')),
            Rule::Chain(3, TS('l'), TS(','), NS('W')),
            Rule::Chain(6, TS('i'), TS('['), NS('E'), TS(']'), TS(','), NS('W'))
        )
    );

    Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
    {
        nt = new GRBALPHABET[size = psize];
        int* p = (int*)&s;
        for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
    };

    Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
    {
        nn = pnn;
        iderror = piderror;
        chains = new Chain[size = psize];
        Chain* p = &c;
        for (int i = 0; i < size; i++) chains[i] = p[i];
    };

    Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
    {
        startN = pstartN;
        stbottomT = pstbottom;
        rules = new Rule[size = psize];
        Rule* p = &r;
        for (int i = 0; i < size; i++) rules[i] = p[i];
    };

    Greibach getGreibach() { return greibach; };

    short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
    {
        short rc = -1;
        short k = 0;
        while (k < size && rules[k].nn != pnn) k++;
        if (k < size) prule = rules[rc = k];
        return rc;
    };

    Rule Greibach::getRule(short n)
    {
        Rule rc;
        if (n < size) rc = rules[n];
        return rc;
    };

    char* Rule::getCRule(char* b, short nchain) // получить правило в виде N->цепочка
    {
        char bchain[200];
        b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00;
        chains[nchain].getCChain(bchain);
        strcat_s(b, sizeof(bchain) + 5, bchain);
        return b;
    };

    short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
    {
        short rc = -1;
        while (j < size && chains[j].nt[0] != t) ++j;
        rc = (j < size ? j : -1);
        if (rc >= 0) pchain = chains[rc];
        return rc;
    };

    char* Rule::Chain::getCChain(char* b) // получить правую сторону правила
    {
        for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
        b[size] = 0x00;
        return b;
    };
}