#include "stdafx.h"
#include "Out.h"


namespace Out
{
	OUT getOut(wchar_t outfile[])
	{
		setlocale(LC_ALL, "Russian");
		std::locale::global(std::locale("Russian"));

		OUT out;
		wcscpy_s(out.logfile, PARM_MAX_SIZE, outfile);
		out.stream = new std::ofstream(outfile, std::ios::out | std::ios::trunc);
		out.stream->imbue(std::locale(""));
		if (!out.stream->is_open())
		{
			delete out.stream;
			out.stream = nullptr;
			throw Error::geterror(112);
		}
		out.stream->flush();
		return out;
	}

	void WriteLine(OUT out, const char* text) {
		*out.stream << text << std::endl;
	}

	void WriteIn(OUT out, char* text)
	{
		if (!out.stream || !out.stream->is_open())
		{
			return;
		}

		*out.stream << text;
		out.stream->flush();

	}

	void WriteLexTable(LT::LexTable& lextable, OUT out) {
		*out.stream << "ТАБЛИЦА ЛЕКСЕМ:" << std::endl;
		int lastLine = LT::GetEntry(lextable,0).sn - 1;

		for (int i = 0; i < lextable.size; i++) {

			LT::Entry e = LT::GetEntry(lextable, i);

			if (e.sn != lastLine)
				*out.stream << std::endl << lastLine + 1 << ": " << e.lexema[0];
			else *out.stream << e.lexema[0];

			lastLine = e.sn;
		}
		*out.stream << std::endl;
	}
	void WriteIdentificatorTable(IT::IdTable& idTable, OUT out) {
		*out.stream << "ТАБЛИЦА ИДЕНТИФИКАТОРОВ:" << std::endl;

		for (int i = 0; i < idTable.size; i++) {

			IT::Entry e = IT::GetEntry(idTable, i);
			const char* dataType, *idType;
			dataType = idType = nullptr;
			char value[256]{};
			
			switch (e.iddatatype) {
			case IT::IDDATATYPE::INT:
				dataType = "INT";
				sprintf_s(value, 256, "%d", e.value.vint);
				break;
			case IT::IDDATATYPE::STR:
				dataType = "STR";
				{
					int len = e.value.vstr.len;
					if (len > 255) len = 255;
					memcpy(value, e.value.vstr.str, len);
					value[len] = '\0';
				}
				break;
			default:
				dataType = "UNKNOWN";
				sprintf_s(value, 256, "?");
				break;
			}

			switch (e.idtype) {
				case IT::IDTYPE::V: idType = "V"; break;
				case IT::IDTYPE::F: idType = "F"; break;
				case IT::IDTYPE::P: idType = "P"; break;
				case IT::IDTYPE::L: idType = "L"; break;
				default: idType = "?"; break;
			}

			*out.stream << e.idxfirstLE << ": " << e.id
				<< " = '" << value << "'"
				<< "(Тип данных: " << dataType 
				<< ", Тип идентификатора: " << idType
				<< ")" << std::endl;
		}
	}

	void WriteWorkProtocol(LT::LexTable& lextable, IT::IdTable& idTable, OUT out)
	{
		WriteLine(out, "ПРОТОКОЛ РАБОТЫ");
		WriteLine(out, "");
		WriteLexTable(lextable, out);
		WriteLine(out, "");
		WriteIdentificatorTable(idTable, out);
	}

	void Close(OUT out)
	{
		if (out.stream)
		{
			if (out.stream->is_open())
			{
				out.stream->flush();
				out.stream->close();
			}
			delete out.stream;
			out.stream = nullptr;
		}
	}
}


