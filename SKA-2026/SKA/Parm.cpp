#include "stdafx.h"
#include "Parm.h"


namespace Parm {

    PARM getparam(int argc, wchar_t* argv[])
    {
        PARM newParm;
        newParm.in[0] = L'\0';
        newParm.out[0] = L'\0';
        newParm.log[0] = L'\0';

        for (int i = 1; i < argc; i++) {
            std::wcout << argv[i] << std::endl; 

            if (wcsncmp(argv[i], PARM_IN, wcslen(PARM_IN)) == 0) {
                if (wcslen(argv[i]) > PARM_MAX_SIZE)
                    throw ERROR_THROW(104);

                wcscpy_s(newParm.in, PARM_MAX_SIZE, argv[i] + wcslen(PARM_IN));
            }
            else if (wcsncmp(argv[i], PARM_OUT, wcslen(PARM_OUT)) == 0) {
                if (wcslen(argv[i]) > PARM_MAX_SIZE)
                    throw ERROR_THROW(104);

                wcscpy_s(newParm.out, PARM_MAX_SIZE, argv[i] + wcslen(PARM_OUT));
            }
            else if (wcsncmp(argv[i], PARM_LOG, wcslen(PARM_LOG)) == 0) {
                if (wcslen(argv[i]) > PARM_MAX_SIZE)
                    throw ERROR_THROW(104);

                wcscpy_s(newParm.log, PARM_MAX_SIZE, argv[i] + wcslen(PARM_LOG));
            }
        }

        if (newParm.in[0] == L'\0') {
            throw ERROR_THROW(100);
        }

        if (newParm.out[0] == L'\0') {
            wcscpy_s(newParm.out, PARM_MAX_SIZE, newParm.in);
            wcscat_s(newParm.out, PARM_MAX_SIZE, L".out");
        }

        if (newParm.log[0] == L'\0') {
            wcscpy_s(newParm.log, PARM_MAX_SIZE, newParm.in);
            wcscat_s(newParm.log, PARM_MAX_SIZE, L".log");
        }

        return newParm;
    }
}