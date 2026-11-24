#include "FSTFactory.h"

namespace FSTFactory {

	FST::FST Integer(char* lexema) {
		return FST::FST(
			lexema,
			6,
			FST::NODE(1, FST::RELATION('÷', 1)), // 0
			FST::NODE(1, FST::RELATION('è', 2)), // 1
			FST::NODE(1, FST::RELATION('ñ', 3)), // 2
			FST::NODE(1, FST::RELATION('ë', 4)), // 4
			FST::NODE(1, FST::RELATION('î', 5)), // 5
			FST::NODE()
		);
	}
	FST::FST String(char* lexema) {
		return FST::FST(
			lexema,
			7,
			FST::NODE(1, FST::RELATION('ñ', 1)), // 0
			FST::NODE(1, FST::RELATION('ò', 2)), // 1
			FST::NODE(1, FST::RELATION('ð', 3)), // 2
			FST::NODE(1, FST::RELATION('î', 4)), // 4
			FST::NODE(1, FST::RELATION('ê', 5)), // 5
			FST::NODE(1, FST::RELATION('à', 6)), // 6
			FST::NODE()
		);
	}
	FST::FST Char(char* lexema)
	{
		return FST::FST(
			lexema,
			7,
			FST::NODE(1, FST::RELATION('ñ', 1)), // 0
			FST::NODE(1, FST::RELATION('è', 2)), // 1
			FST::NODE(1, FST::RELATION('ì', 3)), // 2
			FST::NODE(1, FST::RELATION('â', 4)), // 4
			FST::NODE(1, FST::RELATION('î', 5)), // 5
			FST::NODE(1, FST::RELATION('ë', 6)), // 6
			FST::NODE()
		);
	}
	FST::FST Function(char* lexema) {
		return FST::FST(
			lexema,
			8,
			FST::NODE(1, FST::RELATION('ô', 1)), // 0
			FST::NODE(1, FST::RELATION('ó', 2)), // 1
			FST::NODE(1, FST::RELATION('í', 3)), // 2
			FST::NODE(1, FST::RELATION('ê', 4)), // 3
			FST::NODE(1, FST::RELATION('ö', 5)), // 4
			FST::NODE(1, FST::RELATION('è', 6)), // 5
			FST::NODE(1, FST::RELATION('ÿ', 7)), // 6
			FST::NODE()
		);
	}
	FST::FST Void(char* lexema) {
		return FST::FST(
			lexema,
			6,
			FST::NODE(1, FST::RELATION('ï', 1)), // 0
			FST::NODE(1, FST::RELATION('ó', 2)), // 1
			FST::NODE(1, FST::RELATION('ñ', 3)), // 2
			FST::NODE(1, FST::RELATION('ò', 4)), // 3
			FST::NODE(1, FST::RELATION('î', 5)), // 4
			FST::NODE()
		);
	}
	FST::FST Return(char* lexema) {
		return FST::FST(
			lexema,
			8,
			FST::NODE(1, FST::RELATION('â', 1)), // 0
			FST::NODE(1, FST::RELATION('å', 2)), // 1
			FST::NODE(1, FST::RELATION('ð', 3)), // 2
			FST::NODE(1, FST::RELATION('í', 4)), // 3
			FST::NODE(1, FST::RELATION('ó', 5)), // 4
			FST::NODE(1, FST::RELATION('ò', 6)), // 5
			FST::NODE(1, FST::RELATION('ü', 7)), // 6
			FST::NODE()                          // 7
		);
	}
	FST::FST If(char* lexema)
	{
		return FST::FST(
			lexema,
			5,
			FST::NODE(1, FST::RELATION('å', 1)),
			FST::NODE(1, FST::RELATION('ñ', 2)),
			FST::NODE(1, FST::RELATION('ë', 3)),
			FST::NODE(1, FST::RELATION('è', 4)),
			FST::NODE()
		);
	}
	FST::FST Then(char* lexema)
	{
		return FST::FST(
			lexema,
			3,
			FST::NODE(1, FST::RELATION('ò', 1)),
			FST::NODE(1, FST::RELATION('î', 2)),
			FST::NODE()
		);
	}
	FST::FST Else(char* lexema)
	{
		return FST::FST(
			lexema,
			6,
			FST::NODE(1, FST::RELATION('è', 1)),
			FST::NODE(1, FST::RELATION('í', 2)),
			FST::NODE(1, FST::RELATION('à', 3)),
			FST::NODE(1, FST::RELATION('÷', 4)),
			FST::NODE(1, FST::RELATION('å', 5)),
			FST::NODE()
		);
	}
	FST::FST While(char* lexema)
	{
		return FST::FST(
			lexema,
			5,
			FST::NODE(1, FST::RELATION('ï', 1)),
			FST::NODE(1, FST::RELATION('î', 2)),
			FST::NODE(1, FST::RELATION('ê', 3)),
			FST::NODE(1, FST::RELATION('à', 4)),
			FST::NODE()
		);
	}
	FST::FST And(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('è', 1)),
			FST::NODE()
		);
	}
	FST::FST Or(char* lexema)
	{
		return FST::FST(
			lexema,
			4,
			FST::NODE(1, FST::RELATION('è', 1)),
			FST::NODE(1, FST::RELATION('ë', 2)),
			FST::NODE(1, FST::RELATION('è', 3)),
			FST::NODE()
		);
	}
	FST::FST No(char* lexema)
	{
		return FST::FST(
			lexema,
			3,
			FST::NODE(1, FST::RELATION('í', 1)),
			FST::NODE(1, FST::RELATION('å', 2)),
			FST::NODE()
		);
	}

	FST::FST SetType(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION(':', 1)),
			FST::NODE()
		);
	}
	FST::FST Set(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE()
		);
	}
	FST::FST Less(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('<', 1)),
			FST::NODE()
		);
	}

	FST::FST More(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('>', 1)),
			FST::NODE()
		);
	}

	FST::FST Input(char* lexema)
	{
		return FST::FST(
			lexema,
			7,
			FST::NODE(1, FST::RELATION('â', 1)),
			FST::NODE(1, FST::RELATION('â', 2)),
			FST::NODE(1, FST::RELATION('å', 3)),
			FST::NODE(1, FST::RELATION('ñ', 4)),
			FST::NODE(1, FST::RELATION('ò', 5)),
			FST::NODE(1, FST::RELATION('è', 6)),
			FST::NODE()
		);
	}
	FST::FST Print(char* lexema) {
		return FST::FST(
			lexema,
			11,
			FST::NODE(1, FST::RELATION('í', 1)), // 0
			FST::NODE(1, FST::RELATION('à', 2)), // 1
			FST::NODE(1, FST::RELATION('ï', 3)), // 2
			FST::NODE(1, FST::RELATION('å', 4)), // 3
			FST::NODE(1, FST::RELATION('÷', 5)), // 4
			FST::NODE(1, FST::RELATION('à', 6)), // 4
			FST::NODE(1, FST::RELATION('ò', 7)), // 4
			FST::NODE(1, FST::RELATION('à', 8)), // 4
			FST::NODE(1, FST::RELATION('ò', 9)), // 4
			FST::NODE(1, FST::RELATION('ü', 10)), // 4
			FST::NODE()
		);

	}
	FST::FST Main(char* lexema) {
		return FST::FST(
			lexema,
			8,
			FST::NODE(1, FST::RELATION('ã', 1)), // 0
			FST::NODE(1, FST::RELATION('ë', 2)), // 1
			FST::NODE(1, FST::RELATION('à', 3)), // 2
			FST::NODE(1, FST::RELATION('â', 4)), // 3
			FST::NODE(1, FST::RELATION('í', 5)), // 4
			FST::NODE(1, FST::RELATION('à', 6)), // 5
			FST::NODE(1, FST::RELATION('ÿ', 7)), // 6
			FST::NODE()                          // 7
		);

	}
	FST::FST Semicolon(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION(';', 1)), // 0
			FST::NODE()                          // 1
		);

	}
	FST::FST Comma(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION(',', 1)),
			FST::NODE()
		);

	}
	FST::FST Leftbrace(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('{', 1)),
			FST::NODE()
		);

	}
	FST::FST Bracelet(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('}', 1)),
			FST::NODE()
		);

	}
	FST::FST Leftthesis(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('(', 1)),
			FST::NODE()
		);
	}
	FST::FST Righthesis(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION(')', 1)),
			FST::NODE()
		);
	}
	FST::FST Leftsquare(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('[', 1)),
			FST::NODE()
		);
	}
	FST::FST Rightsquare(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION(']', 1)),
			FST::NODE()
		);
	}
	FST::FST Equally(char* lexema)
	{
		return FST::FST(
			lexema,
			3,
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE(1, FST::RELATION('=', 1)),
			FST::NODE()
		);
	}
	FST::FST Plus(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('+', 1)),
			FST::NODE()
		);
	}
	FST::FST Minus(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('-', 1)),
			FST::NODE()
		);

	}
	FST::FST Star(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('*', 1)),
			FST::NODE()
		);
	}
	FST::FST Directslash(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('/', 1)),
			FST::NODE()
		);
	}
	FST::FST Residue(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
			FST::NODE(1, FST::RELATION('%', 1)),
			FST::NODE()
		);
	}
	FST::FST Integer_Literal(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(11,
				FST::RELATION('-', 1),
				FST::RELATION('0', 1),
				FST::RELATION('1', 1),
				FST::RELATION('2', 1),
				FST::RELATION('3', 1),
				FST::RELATION('4', 1),
				FST::RELATION('5', 1),
				FST::RELATION('6', 1),
				FST::RELATION('7', 1),
				FST::RELATION('8', 1),
				FST::RELATION('9', 1)
			), // 0
			FST::NODE(10,
				FST::RELATION('0', 1),
				FST::RELATION('1', 1),
				FST::RELATION('2', 1),
				FST::RELATION('3', 1),
				FST::RELATION('4', 1),
				FST::RELATION('5', 1),
				FST::RELATION('6', 1),
				FST::RELATION('7', 1),
				FST::RELATION('8', 1),
				FST::RELATION('9', 1)
			)  // 1
		);
	}
	FST::FST Identifier(char* lexema) {
		return FST::FST(
			lexema,
			2,
			FST::NODE(66,
				FST::RELATION('à', 1), FST::RELATION('á', 1), FST::RELATION('â', 1),
				FST::RELATION('ã', 1), FST::RELATION('ä', 1), FST::RELATION('å', 1),
				FST::RELATION('¸', 1), FST::RELATION('æ', 1), FST::RELATION('ç', 1),
				FST::RELATION('è', 1), FST::RELATION('é', 1), FST::RELATION('ê', 1),
				FST::RELATION('ë', 1), FST::RELATION('ì', 1), FST::RELATION('í', 1),
				FST::RELATION('î', 1), FST::RELATION('ï', 1), FST::RELATION('ð', 1),
				FST::RELATION('ñ', 1), FST::RELATION('ò', 1), FST::RELATION('ó', 1),
				FST::RELATION('ô', 1), FST::RELATION('õ', 1), FST::RELATION('ö', 1),
				FST::RELATION('÷', 1), FST::RELATION('ø', 1), FST::RELATION('ù', 1),
				FST::RELATION('ú', 1), FST::RELATION('û', 1), FST::RELATION('ü', 1),
				FST::RELATION('ý', 1), FST::RELATION('þ', 1), FST::RELATION('ÿ', 1),

				FST::RELATION('À', 1), FST::RELATION('Á', 1), FST::RELATION('Â', 1),
				FST::RELATION('Ã', 1), FST::RELATION('Ä', 1), FST::RELATION('Å', 1),
				FST::RELATION('¨', 1), FST::RELATION('Æ', 1), FST::RELATION('Ç', 1),
				FST::RELATION('È', 1), FST::RELATION('É', 1), FST::RELATION('Ê', 1),
				FST::RELATION('Ë', 1), FST::RELATION('Ì', 1), FST::RELATION('Í', 1),
				FST::RELATION('Î', 1), FST::RELATION('Ï', 1), FST::RELATION('Ð', 1),
				FST::RELATION('Ñ', 1), FST::RELATION('Ò', 1), FST::RELATION('Ó', 1),
				FST::RELATION('Ô', 1), FST::RELATION('Õ', 1), FST::RELATION('Ö', 1),
				FST::RELATION('×', 1), FST::RELATION('Ø', 1), FST::RELATION('Ù', 1),
				FST::RELATION('Ú', 1), FST::RELATION('Û', 1), FST::RELATION('Ü', 1),
				FST::RELATION('Ý', 1), FST::RELATION('Þ', 1), FST::RELATION('ß', 1)
			), // 0
			FST::NODE(76,
				FST::RELATION('à', 1), FST::RELATION('á', 1), FST::RELATION('â', 1),
				FST::RELATION('ã', 1), FST::RELATION('ä', 1), FST::RELATION('å', 1),
				FST::RELATION('¸', 1), FST::RELATION('æ', 1), FST::RELATION('ç', 1),
				FST::RELATION('è', 1), FST::RELATION('é', 1), FST::RELATION('ê', 1),
				FST::RELATION('ë', 1), FST::RELATION('ì', 1), FST::RELATION('í', 1),
				FST::RELATION('î', 1), FST::RELATION('ï', 1), FST::RELATION('ð', 1),
				FST::RELATION('ñ', 1), FST::RELATION('ò', 1), FST::RELATION('ó', 1),
				FST::RELATION('ô', 1), FST::RELATION('õ', 1), FST::RELATION('ö', 1),
				FST::RELATION('÷', 1), FST::RELATION('ø', 1), FST::RELATION('ù', 1),
				FST::RELATION('ú', 1), FST::RELATION('û', 1), FST::RELATION('ü', 1),
				FST::RELATION('ý', 1), FST::RELATION('þ', 1), FST::RELATION('ÿ', 1),

				FST::RELATION('À', 1), FST::RELATION('Á', 1), FST::RELATION('Â', 1),
				FST::RELATION('Ã', 1), FST::RELATION('Ä', 1), FST::RELATION('Å', 1),
				FST::RELATION('¨', 1), FST::RELATION('Æ', 1), FST::RELATION('Ç', 1),
				FST::RELATION('È', 1), FST::RELATION('É', 1), FST::RELATION('Ê', 1),
				FST::RELATION('Ë', 1), FST::RELATION('Ì', 1), FST::RELATION('Í', 1),
				FST::RELATION('Î', 1), FST::RELATION('Ï', 1), FST::RELATION('Ð', 1),
				FST::RELATION('Ñ', 1), FST::RELATION('Ò', 1), FST::RELATION('Ó', 1),
				FST::RELATION('Ô', 1), FST::RELATION('Õ', 1), FST::RELATION('Ö', 1),
				FST::RELATION('×', 1), FST::RELATION('Ø', 1), FST::RELATION('Ù', 1),
				FST::RELATION('Ú', 1), FST::RELATION('Û', 1), FST::RELATION('Ü', 1),
				FST::RELATION('Ý', 1), FST::RELATION('Þ', 1), FST::RELATION('ß', 1),

				FST::RELATION('0', 1), FST::RELATION('1', 1), FST::RELATION('2', 1),
				FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1),
				FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1),
				FST::RELATION('9', 1)
			) // 1
		);
	}

}
