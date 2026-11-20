#include "stdafx.h"
#include "Error.h"
using namespace std;

namespace Error
{

	// серии ошибок: 0 - 99 - системные ошибки
	// 100 - 109 - ошибки параметров
	// 110 - 119 - ошибки открытия и чтения файлов
	ERROR errors[ERROR_MAX_ENTRY] = // таблица ошибок
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),    // код ошибки вне диапазона 0 - ERROR_MAX_ENTRY
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2),
		ERROR_ENTRY_NODEF(3),
		ERROR_ENTRY_NODEF(4),
		ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),
		ERROR_ENTRY_NODEF(7),
		ERROR_ENTRY_NODEF(8),
		ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),
		ERROR_ENTRY_NODEF10(20),
		ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40),
		ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),
		ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),
		ERROR_ENTRY_NODEF(102),
		ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола(-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),

		// 120-129: ошибки лексера
		ERROR_ENTRY(120, "Недопустимая лексема"),
		ERROR_ENTRY(121, "Идентификатор слишком длинный (макс. 5 символов)"),
		ERROR_ENTRY(122, "Незакрытая строковая константа"),
		ERROR_ENTRY(123, "Пустая строковая константа"),
		ERROR_ENTRY(124, "Недопустимый символ в идентификаторе"),
		ERROR_ENTRY(125, "Недопустимый символ в литерале"),
		ERROR_ENTRY(126, "Недопустимое значение литерала"),
		ERROR_ENTRY(127, "Лексема слишком длинная (макс. 255 символов)"),
		ERROR_ENTRY_NODEF(128), ERROR_ENTRY_NODEF(129),

		// 130-139: ошибки таблицы лексем (ТЛ)
		ERROR_ENTRY(130, "Переполнение таблицы лексем"),
		ERROR_ENTRY(131, "Таблица лексем не создана"),
		ERROR_ENTRY(132, "Строка таблицы лексем не существует"),
		ERROR_ENTRY_NODEF(133), ERROR_ENTRY_NODEF(134), ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136), ERROR_ENTRY_NODEF(137), ERROR_ENTRY_NODEF(138), ERROR_ENTRY_NODEF(139),

		// 140-149: ошибки таблицы идентификаторов (ТИ)
		ERROR_ENTRY(140, "Недопустимый размер таблицы идентификаторов"),
		ERROR_ENTRY(141, "Таблица идентификаторов не создана"),
		ERROR_ENTRY(142, "Строка таблицы идентификаторов не существует"),
		ERROR_ENTRY(143, "Идентификатор не найден"),
		ERROR_ENTRY(144, "Пустой идентификатор"),
		ERROR_ENTRY_NODEF(145), ERROR_ENTRY_NODEF(146), ERROR_ENTRY_NODEF(147),
		ERROR_ENTRY_NODEF(148), ERROR_ENTRY_NODEF(149),

		// 150-159: ошибки литералов
		ERROR_ENTRY(150, "Числовой литерал вне диапазона int"),
		ERROR_ENTRY(151, "Строковый литерал слишком длинный (макс. 255)"),
		ERROR_ENTRY_NODEF(152), ERROR_ENTRY_NODEF(153), ERROR_ENTRY_NODEF(154),
		ERROR_ENTRY_NODEF(155), ERROR_ENTRY_NODEF(156), ERROR_ENTRY_NODEF(157),
		ERROR_ENTRY_NODEF(158), ERROR_ENTRY_NODEF(159),

		// 160-199: зарезервировано
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибочный оператор"),
		ERROR_ENTRY(602, "Ошибка в выражении"),
		ERROR_ENTRY(603, "Ошибка в хвосте операции"),
		ERROR_ENTRY(604, "Ошибка в параметрах функции"),
		ERROR_ENTRY(605, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(606),ERROR_ENTRY_NODEF(607),ERROR_ENTRY_NODEF(608),ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		ERROR err;

		if (id < 0 || id >= ERROR_MAX_ENTRY)
		{
			err.id = errors[0].id;
			strcpy_s(err.message, ERROR_MAXSIZE_MESSAGE, errors[0].message);
			err.next.line = -1;
			err.next.col = -1;
		}
		else
		{
			err.id = errors[id].id;
			strcpy_s(err.message, ERROR_MAXSIZE_MESSAGE, errors[id].message);
			err.next.line = -1;
			err.next.col = -1;
		}

		return err;
	}

	ERROR geterrorin(int id, int line, int col)
	{
		ERROR err;

		if (id < 0 || id >= ERROR_MAX_ENTRY)
		{
			err.id = errors[0].id;
			strcpy_s(err.message, ERROR_MAXSIZE_MESSAGE, errors[0].message);
		}
		else
		{
			err.id = errors[id].id;
			strcpy_s(err.message, ERROR_MAXSIZE_MESSAGE, errors[id].message);
		}

		err.next.line = (short)line;
		err.next.col = (short)col;

		return err;
	}
}