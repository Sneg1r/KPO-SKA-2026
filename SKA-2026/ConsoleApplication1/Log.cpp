#include "stdafx.h"
#include "Log.h"

namespace Log
{
    LOG getlog(wchar_t logfile[])
    {
        setlocale(LC_ALL, "Russian");
        std::locale::global(std::locale("Russian"));

        LOG log;
        wcscpy_s(log.logfile, PARM_MAX_SIZE, logfile);
        log.stream = new std::ofstream(logfile, std::ios::out | std::ios::trunc);
        log.stream->imbue(std::locale(""));
        if (!log.stream->is_open())
        {
            delete log.stream;
            log.stream = nullptr;
            throw Error::geterror(112);
        }
        log.isOpen = true;
        log.stream->flush();
        return log;
    }
    void WriteLine(LOG log, const char* c, ...)
    {
        if (!log.isOpen || !log.stream || !log.stream->is_open())
        {
            return;
        }
        va_list args;
        va_start(args, c);
        const char* s = c;
        while (s && *s)
        {
            *log.stream << s;
            s = va_arg(args, char*);
        }
        va_end(args);
        *log.stream << std::endl;
        log.stream->flush();
    }
    void WriteLine(LOG log, const wchar_t* c, ...)
    {
        if (!log.isOpen || !log.stream || !log.stream->is_open())
        {
            return;
        }

        va_list args;
        va_start(args, c);
        const wchar_t* s = c;
        std::string result;
        while (s && *s)
        {
            size_t size_needed = 0;
            errno_t err = wcstombs_s(&size_needed, nullptr, 0, s, _TRUNCATE);
            if (err == 0 && size_needed > 0)
            {
                std::vector<char> buffer(size_needed);
                err = wcstombs_s(&size_needed, buffer.data(), size_needed, s, _TRUNCATE);
                if (err == 0)
                {
                    result.append(buffer.data());
                }
                else
                {
                    result.append("[ошибка преобразования]");
                }
            }
            else
            {
                result.append("[ошибка преобразования]");
            }
            s = va_arg(args, wchar_t*);
        }
        va_end(args);
        *log.stream << result << std::endl;
        log.stream->flush();
    }

    void WriteLog(LOG log)
    {
        time_t now = time(nullptr);
        struct tm timeinfo;
        localtime_s(&timeinfo, &now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
        WriteLine(log, (char*)"---- Протокол ------ ", buffer, (char*)" -----", (char*)"");
    }

    void WriteParm(LOG log, Parm::PARM parm)
    {
        WriteLine(log, (char*)"---- Параметры ------", (char*)"");
        char in_buf[1024];
        size_t converted = 0;
        errno_t err = wcstombs_s(&converted, in_buf, sizeof(in_buf), parm.in, _TRUNCATE);
        if (err == 0 && converted > 0)
        {
            std::string line = "-in:  " + std::string(in_buf);
            WriteLine(log, (char*)line.c_str(), (char*)"");
        }
        else
        {
            WriteLine(log, (char*)"-in:  [ошибка преобразования]", (char*)"");
        }
        char out_buf[1024];
        err = wcstombs_s(&converted, out_buf, sizeof(out_buf), parm.out, _TRUNCATE);
        if (err == 0 && converted > 0)
        {
            std::string line = "-out: " + std::string(out_buf);
            WriteLine(log, (char*)line.c_str(), (char*)"");
        }
        else
        {
            WriteLine(log, (char*)"-out: [ошибка преобразования]", (char*)"");
        }
        char log_buf[1024];
        err = wcstombs_s(&converted, log_buf, sizeof(log_buf), parm.log, _TRUNCATE);
        if (err == 0 && converted > 0)
        {
            std::string line = "-log: " + std::string(log_buf);
            WriteLine(log, (char*)line.c_str(), (char*)"");
        }
        else
        {
            WriteLine(log, (char*)"-log: [ошибка преобразования]", (char*)"");
        }
    }

    void WriteIn(LOG log, In::IN in)
    {
        WriteLine(log, (char*)"---- Содержимое входного файла ------", (char*)"");
        if (in.text && strlen(in.text) > 0)
        {
            WriteLine(log, in.text, (char*)"");
        }
        else
        {
            WriteLine(log, (char*)"[пусто или null]", (char*)"");
        }
        WriteLine(log, (char*)"---- Исходные данные ------", (char*)"");
        std::string line_size = "Количество символов: " + std::to_string(in.size);
        WriteLine(log, (char*)line_size.c_str(), (char*)"");
        std::string line_ignor = "Проигнорировано    : " + std::to_string(in.ignor);
        WriteLine(log, (char*)line_ignor.c_str(), (char*)"");
        std::string line_lines = "Количество строк   : " + std::to_string(in.lines + 1);
        WriteLine(log, (char*)line_lines.c_str(), (char*)"");
        if (log.stream && log.stream->is_open())
        {
            log.stream->flush();
        }
    }

    void WriteError(LOG log, Error::ERROR err)
    {
        if (log.isOpen && log.stream && log.stream->is_open())
        {
            WriteLine(log, (char*)"Ошибка: ", err.message, (char*)"");
            if (err.next.line != -1)
            {
                std::string line_col = "  строка " + std::to_string(err.next.line + 1) +
                    ", позиция " + std::to_string(err.next.col);
                WriteLine(log, (char*)line_col.c_str(), (char*)"");
            }
            log.stream->flush();
        }
    }

    void Close(LOG log)
    {
        if (log.isOpen && log.stream)
        {
            if (log.stream->is_open())
            {
                log.stream->flush();
                log.stream->close();
            }
            delete log.stream;
            log.stream = nullptr;
            log.isOpen = false;
        }
    }
}