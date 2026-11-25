#include "stdafx.h"
#include "In.h"
#include "Error.h"

using namespace std;

namespace In {

	IN getin(wchar_t infile[])
	{
		size_t len = wcslen(infile) + 1;
		char* filename = new char[len];
		size_t converted;
		wcstombs_s(&converted, filename, len, infile, len - 1);

		ifstream fin(infile);

		IN newIn = {};
		newIn.lines = 1;
		newIn.text = new char[IN_MAX_LEN_TEXT] {};

		int temp[256] = IN_CODE_TABLE;
		for (int i = 0; i < 256; i++)
			newIn.code[i] = temp[i];

		if (!fin.is_open())
			throw ERROR_THROW(110);

		unsigned char ch;
		int pos = 0;

		while (fin.get(reinterpret_cast<char&>(ch))) {
			pos++;

			switch (newIn.code[ch]) {
			case newIn.T:
			{
				newIn.text[newIn.size] = ch;
				newIn.size++;

				if (ch == IN_CODE_ENDL || ch == '\r') {
					newIn.lines++;
					pos = 0;
				}

				if (!strchr(IN_TAB_CHARACTERS, ch)) newIn.symbols++;

			} break;
			case newIn.F: throw ERROR_THROW_IN(111, newIn.lines, pos) break;
			case newIn.I:newIn.ignor++; break;
			}
		}

		newIn.posSimbols = new int[newIn.symbols] {};
		ProcessingText(newIn);

		/*for (int i = 0; i < newIn.symbols; i++)
		{
			cout << i << "   " << newIn.posSimbols[i] << endl;
		}*/

		fin.close();
		return newIn;
	}

	void ProcessingText(IN& in) {
		int size = strlen(in.text); int position = 0;
		in.redactedText = new char[size * 2 + 2] {}; in.redactedText[0] = '\r';
		char lastSimbol;

		int currWord = 0;
		int linePos = 1;
		bool isWord = false;
		bool inString = false;
		bool inLineComment = false;
		bool inBlockComment = false;

		for (int i = 0; i < size; i++) {
			char c = in.text[i];

			if (inLineComment) {
				if (c == IN_CODE_ENDL) {
					inLineComment = false;
					linePos = 1;
					in.redactedText[position++] = IN_CODE_ENDL;
				}
				continue;
			}

			if (inBlockComment) {
				if (c == '*' && i+1 < size && in.text[i+1] == '/') {
					inBlockComment = false;
					linePos++;
					i++;

				}
				else if (c == IN_CODE_ENDL) {
					linePos = 1;
					in.redactedText[position++] = IN_CODE_ENDL;
				}
				linePos++;
				continue;
			}

			if (c == '/' && i + 1 < size) {
				if (in.text[i + 1] == '/') {
					inLineComment = true;
					i++;
					linePos += 2;
					continue;
				}
				if (in.text[i + 1] == '*') {
					inBlockComment = true;
					i++;
					linePos += 2;
					continue;
				}
			}

			if (c == IN_CODE_ENDL || c == '\r') {
				if (isWord) {
					isWord = false;
				}
				in.redactedText[position++] = IN_CODE_ENDL;
				linePos = 1; 
				continue;
			}

			if (inString) {
				if (c == '"') {
					inString = false;
					in.redactedText[position++] = c;
					in.redactedText[position++] = SEPARATOR;
				}
				else {
					in.redactedText[position++] = c;
				}
				linePos++;
				continue;
			}

			if (c == '"') {
				if (isWord) {
					isWord = false;
					in.redactedText[position++] = SEPARATOR;
				}
				inString = true;
				in.posSimbols[currWord] = linePos;
				currWord++;
				in.redactedText[position++] = c;
				linePos++;
				continue;
			}

			if (c == ' ' || c == '\t') {
				if (isWord) {
					isWord = false;
					in.redactedText[position++] = SEPARATOR;
				}
				linePos++;
				continue;
			}

			if (IsSeparator(c)) {
				if (isWord) {
					isWord = false;
					in.redactedText[position++] = SEPARATOR;
				}

				in.posSimbols[currWord] = linePos;
				currWord++;

				in.redactedText[position++] = c;
				in.redactedText[position++] = SEPARATOR;
				linePos++;
				continue;
			}

			if (!isWord) {
				isWord = true;
				in.posSimbols[currWord] = linePos;
				currWord++;
			}

			in.redactedText[position++] = c;
			linePos++;
		}

		if (isWord) {
			in.redactedText[position++] = SEPARATOR;
		}
		in.redactedText[position] = '\0';
	}

	bool IsSeparator(char ch) {
		return strchr("(){}[],:;+-/%<>=", ch);
	}
}