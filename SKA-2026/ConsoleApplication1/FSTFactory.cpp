#include "FSTFactory.h"

namespace FSTFactory {

	FST::FST Integer(char* lexema) {
		return FST::FST(
			lexema,
			8,
			FST::NODE(1, FST::RELATION('i', 1)), // 0
			FST::NODE(1, FST::RELATION('n', 2)), // 1
			FST::NODE(1, FST::RELATION('t', 3)), // 2
			FST::NODE(1, FST::RELATION('e', 4)), // 4
			FST::NODE(1, FST::RELATION('g', 5)), // 5
			FST::NODE(1, FST::RELATION('e', 6)), // 6
			FST::NODE(1, FST::RELATION('r', 7)), // 7
			FST::NODE()
		);
	}
	FST::FST String(char* lexema) {
		return FST::FST(
			lexema,
			7,
			FST::NODE(1, FST::RELATION('s', 1)), // 0
			FST::NODE(1, FST::RELATION('t', 2)), // 1
			FST::NODE(1, FST::RELATION('r', 3)), // 2
			FST::NODE(1, FST::RELATION('i', 4)), // 4
			FST::NODE(1, FST::RELATION('n', 5)), // 5
			FST::NODE(1, FST::RELATION('g', 6)), // 6
			FST::NODE()
		);
	}
	FST::FST Function(char* lexema) {
		return FST::FST(
			lexema,
			9,
			FST::NODE(1, FST::RELATION('f', 1)), // 0
			FST::NODE(1, FST::RELATION('u', 2)), // 1
			FST::NODE(1, FST::RELATION('n', 3)), // 2
			FST::NODE(1, FST::RELATION('c', 4)), // 3
			FST::NODE(1, FST::RELATION('t', 5)), // 4
			FST::NODE(1, FST::RELATION('i', 6)), // 5
			FST::NODE(1, FST::RELATION('o', 7)), // 6
			FST::NODE(1, FST::RELATION('n', 8)), // 7
			FST::NODE()
		);
	}
	FST::FST Declare(char* lexema) {
		return FST::FST(
			lexema,
			8,
			FST::NODE(1, FST::RELATION('d', 1)), // 0
			FST::NODE(1, FST::RELATION('e', 2)), // 1
			FST::NODE(1, FST::RELATION('c', 3)), // 2
			FST::NODE(1, FST::RELATION('l', 4)), // 3
			FST::NODE(1, FST::RELATION('a', 5)), // 4
			FST::NODE(1, FST::RELATION('r', 6)), // 5
			FST::NODE(1, FST::RELATION('e', 7)), // 6
			FST::NODE()
		);
	}
	FST::FST Return(char* lexema) {
		return FST::FST(
			lexema,
			7,
			FST::NODE(1, FST::RELATION('r', 1)), // 0
			FST::NODE(1, FST::RELATION('e', 2)), // 1
			FST::NODE(1, FST::RELATION('t', 3)), // 2
			FST::NODE(1, FST::RELATION('u', 4)), // 3
			FST::NODE(1, FST::RELATION('r', 5)), // 4
			FST::NODE(1, FST::RELATION('n', 6)), // 5
			FST::NODE()                          // 6
		);
	}
	FST::FST Print(char* lexema) {
		return FST::FST(
			lexema,
			6,
			FST::NODE(1, FST::RELATION('p', 1)), // 0
			FST::NODE(1, FST::RELATION('r', 2)), // 1
			FST::NODE(1, FST::RELATION('i', 3)), // 2
			FST::NODE(1, FST::RELATION('n', 4)), // 3
			FST::NODE(1, FST::RELATION('t', 5)), // 4
			FST::NODE()
		);

	}
	FST::FST Main(char* lexema) {
		return FST::FST(
			lexema,
			5,
			FST::NODE(1, FST::RELATION('m', 1)), // 0
			FST::NODE(1, FST::RELATION('a', 2)), // 1
			FST::NODE(1, FST::RELATION('i', 3)), // 2
			FST::NODE(1, FST::RELATION('n', 4)), // 3
			FST::NODE()                          // 4
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
	FST::FST Equally(char* lexema)
	{
		return FST::FST(
			lexema,
			2,
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
			FST::NODE(26,
				FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1),
				FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),
				FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1),
				FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),
				FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1),
				FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),
				FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1),
				FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),
				FST::RELATION('y', 1), FST::RELATION('z', 1)
			), // 0
			FST::NODE(26,
				FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1),
				FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),
				FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1),
				FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),
				FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1),
				FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),
				FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1),
				FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),
				FST::RELATION('y', 1), FST::RELATION('z', 1)
			) // 1
		);
	}

}
