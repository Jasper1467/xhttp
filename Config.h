#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace Config
{
    struct IndivisualData_t
    {
        int m_nPort;
        std::string m_szFileToExecute;
    };

    void Refresh();
}

#endif //CONFIG_H
