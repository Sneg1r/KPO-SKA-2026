#pragma once
#define LEXEMA_FIXSIZE   1             
#define LT_MAXSIZE       8192          
#define LT_TI_NULLIDX    0xffffffff  
#define LEX_ID           'i'           
#define LEX_LITERAL      'l' 

#define LEX_INTEGER      't'           
#define LEX_STRING       't'      
#define LEX_CHAR         't'
       
#define LEX_FUNCTION     'f'   
#define LEX_VOID         '~'               
#define LEX_RETURN       'r' 

#define LEX_IF           '?' 
#define LEX_THEN         '>'
#define LEX_ELSE         '<'
#define LEX_WHILE        'w'
#define LEX_AND          '&'
#define LEX_OR           '|'
#define LEX_NO           '!'
#define LEX_SETTYPE      ':'
#define LEX_SET          '='

#define LEX_INPUT        '#' 
#define LEX_PRINT        'p'           
#define LEX_MAIN         'm' 
#define LEX_TRUE         'l'
#define LEX_FALSE        'l'
#define LEX_FROM         '^'
#define LEX_TO           '%'

#define LEX_SEMICOLON    ';'           
#define LEX_COMMA        ','           
#define LEX_LEFTBRACE    '{'           
#define LEX_BRACELET     '}'           
#define LEX_LEFTHESIS    '('           
#define LEX_RIGHTHESIS   ')'  
#define LEX_LEFTSQUARE   '['           
#define LEX_RIGHTSQUARE  ']' 
          
#define LEX_LESS         'c' 
#define LEX_MORE         'c' 
#define LEX_EQUALLY      'c' 
#define LEX_PLUS         'v'           
#define LEX_MINUS        'v'           
#define LEX_STAR         'v'           
#define LEX_DIRSLASH     'v'           
#define LEX_RESIDUE      'v'  

namespace LT      //расширить позицию 
{
    struct Entry  
    {
        char lexema[LEXEMA_FIXSIZE]{}; 
        int sn;                        
        int idxTI;     

    };

    struct LexTable                    
    {
        int maxsize;                   
        int size;                      
        Entry* table;                  
    };

    LexTable Create(int size);
    void Add(LexTable& lextable, Entry entry);
    Entry& GetEntry(LexTable& lextable, int n);
    void Delete(LexTable& lextable);   
};