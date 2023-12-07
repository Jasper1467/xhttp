#include "Config.h"

#include <json/json.h>

void Config::Refresh()
{
    Json::Value jsonConfig;
    Json::Reader jsonReader;

    if (jsonReader.parse(m_szConfigFileContent, jsonConfig))
    {
        for (auto& individual : jsonConfig["individual"])
        {
            IndivisualData_t data;
            data.m_nPort = individual["port"].asInt();
            data.m_szFileToExecute = individual["file"].asString();
        }
    }
}

