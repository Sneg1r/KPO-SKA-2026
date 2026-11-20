#include "stdafx.h"

#include "Error.h"    
#include "Parm.h"     
#include "Log.h"     
#include "In.h"   
#include "Out.h"
#include "Lexer.h"
#include "LT.h"
#include "IT.h"
#include "MFST.h"

#define MFST_TRACE_START std::cout<<std::setw( 4)<<std::left<<"Шаг" <<":" \
                    <<std::setw(20)<<std::left<<" Правило" \
                    <<std::setw(30)<<std::left<<" Входная лента" \
                    <<std::setw(20)<<std::left<<" Стек" \
                    <<std::endl;

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "");
	std::locale::global(std::locale(""));


	Log::LOG log = Log::INITLOG;

	try
	{
		Parm::PARM parm = Parm::getparam(argc, argv);

		log = Log::getlog(parm.log);

		Log::WriteLine(log, "Тест: ", "без ошибок", "\n", "");

		Log::WriteLine(log, L"Тест: ", L"без ошибок", L"\n", L"");

		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		In::IN in = In::getin(parm.in);

		LEXER::Lexer lexer;
		lexer.Processing(in.text);

		In::ProcessingText(in);
		Log::WriteIn(log, in);

		Out::OUT out = Out::getOut(parm.out);
		Out::WriteWorkProtocol(lexer.lexTable, lexer.idTable, out);
		Out::Close(out);

		Log::Close(log);

		MFST_TRACE_START
		MFST::Mfst mfst(lexer, GRB::getGreibach());
		mfst.start();

		mfst.savededuction();

		mfst.printrules();
	}
	catch (Error::ERROR err)
	{
		Log::WriteError(log, err);

		std::cout << "Ошибка: " << err.message << std::endl;

		if (err.next.line != -1)
		{
			std::cout << "  строка " << err.next.line
				<< ", позиция " << err.next.col << std::endl;
		}
	}

	system("pause");
	return 0;
}



//
//
//#include <iostream>
//#include <locale>
//#include <stack>
//#include <vector>
//#include "LT.h"        
//#include "IT.h"        
// 
//
//using namespace std;
//
//bool PolishNotation(
//	int lexTable_pos,
//	LT::LexTable& lexTable,
//	IT::IdTable& idtable
//);
//
//int GetPriority(char ch);
//
//
//int wmain(int argc, wchar_t* argv[])
//{
//	setlocale(LC_ALL, "rus");
//
//	LT::LexTable lexTable = LT::Create(100);
//	IT::IdTable idTable = IT::Create(100);
//
//	// 2. Заполняем ТАБЛИЦУ ИДЕНТИФИКАТОРОВ (IT)
//	IT::Entry idEntry = {}; // Обнуляем!
//
//	// Индекс 0: z
//	strcpy_s(idEntry.id, "z");
//	idEntry.idtype = IT::IDTYPE::V;
//	idEntry.iddatatype = IT::IDDATATYPE::INT;
//	IT::Add(idTable, idEntry);
//
//	// Индекс 1: fi
//	strcpy_s(idEntry.id, "fi");
//	idEntry.idtype = IT::IDTYPE::F;
//	idEntry.iddatatype = IT::IDDATATYPE::INT;
//	IT::Add(idTable, idEntry);
//
//	// Индекс 2: x
//	strcpy_s(idEntry.id, "x");
//	idEntry.idtype = IT::IDTYPE::P;
//	idEntry.iddatatype = IT::IDDATATYPE::INT;
//	IT::Add(idTable, idEntry);
//
//	// Индекс 3: y
//	strcpy_s(idEntry.id, "y");
//	idEntry.idtype = IT::IDTYPE::P;
//	idEntry.iddatatype = IT::IDDATATYPE::INT;
//	IT::Add(idTable, idEntry);
//
//	// 3. Заполняем ТАБЛИЦУ ЛЕКСЕМ (LT)
//	int pos = 0; // Стартовая позиция выражения
//
//	LT::Entry lexEntry = {}; // Обнуляем перед каждым добавлением (или один раз и меняем поля)
//
//	// 1. i(z)
//	lexEntry.lexema[0] = 'i'; lexEntry.idxTI = 0; LT::Add(lexTable, lexEntry);
//
//	// 2. v(=)
//	lexEntry.lexema[0] = 'v'; lexEntry.idxTI = (int)'='; LT::Add(lexTable, lexEntry);
//
//	// 3. i(fi)
//	lexEntry.lexema[0] = 'i'; lexEntry.idxTI = 1; LT::Add(lexTable, lexEntry);
//
//	// 4. (
//	lexEntry.lexema[0] = '('; lexEntry.idxTI = LT_TI_NULLIDX; LT::Add(lexTable, lexEntry);
//
//	// 5. i(x)
//	lexEntry.lexema[0] = 'i'; lexEntry.idxTI = 2; LT::Add(lexTable, lexEntry);
//
//	// 6. ,
//	lexEntry.lexema[0] = ','; lexEntry.idxTI = LT_TI_NULLIDX; LT::Add(lexTable, lexEntry);
//
//	// 7. i(y)
//	lexEntry.lexema[0] = 'i'; lexEntry.idxTI = 3; LT::Add(lexTable, lexEntry);
//
//	// 8. )
//	lexEntry.lexema[0] = ')'; lexEntry.idxTI = LT_TI_NULLIDX; LT::Add(lexTable, lexEntry);
//
//	// 9. ;
//	lexEntry.lexema[0] = ';'; lexEntry.idxTI = LT_TI_NULLIDX; LT::Add(lexTable, lexEntry);
//
//	// 4. Вызов функции PolishNotation
//	bool result = PolishNotation(pos, lexTable, idTable);
//
//	if (result) {
//		std::cout << "УСПЕШНО! Польская запись построена." << std::endl;
//	}
//	else {
//		std::cout << "ОШИБКА! Не удалось построить запись." << std::endl;
//	}
//
//
//	std::cout << "\n--- Результат (ПОЛИЗ) ---" << std::endl;
//	for (int i = pos; i < lexTable.size; i++) {
//		if (lexTable.table[i].lexema[0] == ';') {
//			std::cout << ";";
//			break;
//		}
//		if (lexTable.table[i].lexema[0] == '#') {
//			std::cout << "#";
//			continue;
//		}
//
//		if (lexTable.table[i].lexema[0] == 'i') {
//			std::cout << idTable.table[lexTable.table[i].idxTI].id;
//		}
//
//		if (lexTable.table[i].lexema[0] == '@') {
//			std::cout << lexTable.table[i].lexema;
//		}
//		std::cout << " ";
//	}
//
//	std::cin.get();
//	return 0;
//};
//
//bool PolishNotation(int lexTable_pos, LT::LexTable& lexTable, IT::IdTable& idtable) 
//{
//
//	int startPos = lexTable_pos;
//	int argCounts = 0;
//
//	stack<int> operation;
//	vector<LT::Entry> output;
//
//	while (true) {
//		LT::Entry lexEntry = lexTable.table[lexTable_pos++];
//		switch (lexEntry.lexema[0]) {
//
//		case 'l':  output.push_back(lexEntry); continue;
//
//		case 'i': {
//			IT::Entry idEntry = idtable.table[lexEntry.idxTI];
//
//			if (idEntry.idtype == IT::IDTYPE::F) {
//				LT::Entry nextLexEntry = lexTable.table[lexTable_pos];
//
//				if (nextLexEntry.lexema[0] == '(')
//				{
//					operation.push(lexTable_pos - 1);
//					continue;
//				}
//			}
//
//			output.push_back(lexEntry);
//
//		}; continue;
//
//		case '(': operation.push(lexTable_pos - 1); argCounts = 0; continue;
//
//		case ')': {
//			while (!operation.empty()) {
//				int currLexTable_pos = operation.top(); operation.pop();
//				LT::Entry currentLexEntry = lexTable.table[currLexTable_pos];
//
//				if (currentLexEntry.lexema[0] == '(') {
//					if (!operation.empty()) {
//						LT::Entry nextLexEntry = lexTable.table[operation.top()];
//
//						if (nextLexEntry.lexema[0] == 'i' && idtable.table[nextLexEntry.idxTI].idtype == IT::IDTYPE::F) {
//							output.push_back(nextLexEntry); operation.pop();
//
//							LT::Entry funcMarker;
//							char funcText[ID_MAXSIZE]{};
//
//							sprintf_s(funcText, "@ %d", argCounts+1);
//							strncpy_s(funcMarker.lexema, ID_MAXSIZE, funcText, _TRUNCATE);
//
//							argCounts = 0;
//							output.push_back(funcMarker);
//						}
//					}
//					break;
//				}
//
//
//				output.push_back(currentLexEntry);
//			}
//		} continue;
//
//		case ',':
//		{
//			
//			argCounts = argCounts == 0 ? 2 : argCounts++;
//			while (!operation.empty()) {
//				int currLexTable_pos = operation.top(); 
//				LT::Entry currentLexEntry = lexTable.table[currLexTable_pos];
//
//				if (currentLexEntry.lexema[0] == '(') {
//					break;
//				}
//				operation.pop();
//				output.push_back(currentLexEntry);
//			}
//		} continue;
//
//		case 'v': {
//			char oper = (char)lexEntry.idxTI;
//			int operPriority = GetPriority(oper);
//
//			while (!operation.empty()) {
//				int currLexTable_pos = operation.top();
//				LT::Entry currentLexEntry = lexTable.table[currLexTable_pos];
//
//				if (currentLexEntry.lexema[0] == '(') {
//					break;
//				}
//
//				if (currentLexEntry.lexema[0] != 'v')
//					break;
//
//				char secondOper = (char)currentLexEntry.idxTI;
//				if (GetPriority(secondOper) >= operPriority) {
//					output.push_back(currentLexEntry);
//					operation.pop();
//					continue;
//				}
//				break;
//			}
//			operation.push(lexTable_pos - 1);
//		} continue;
//
//		case ';':
//		{
//			int endPos = lexTable_pos - 1;
//			int currOutput = 0;
//			int outputSize = output.size();
//
//			int i = startPos;
//			for (; i < endPos && currOutput < outputSize; ++i) {
//				lexTable.table[i] = output[currOutput++];
//			}
//
//
//			for (; i < endPos; ++i) {
//				LT::Entry emptyEntry;
//				emptyEntry.lexema[0] = '#';
//				emptyEntry.idxTI = LT_TI_NULLIDX;
//				emptyEntry.sn = lexTable.table[i].sn;
//				lexTable.table[i] = emptyEntry;
//			}
//
//			return true;
//		}
//
//		}
//	}
//}
//
//int GetPriority(char ch) {
//
//	if (ch == '*' || ch == '/') return 3;
//	if (ch == '+' || ch == '-') return 2;
//	if (ch == '=') return 1;
//	return 0;
//}