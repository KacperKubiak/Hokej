#include "Config.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

std::string trim(std::string const& source, char const* delims = " \t\r\n") {
  std::string result(source);
  std::string::size_type index = result.find_last_not_of(delims);
  if(index != std::string::npos)
    result.erase(++index);

  index = result.find_first_not_of(delims);
  if(index != std::string::npos)
    result.erase(0, index);
  else
    result.erase();
  return result;
}

Config::Config()
{
    res.x = 1280;
    res.y = 720;
    LoadConfig();
}

void Config::LoadConfig()
{
    std::ifstream file("config.cfg");
    if(!file.is_open())
    {
       std::ofstream file;
       file.open("config.cfg");
       file<<"res.x="<<res.x<<std::endl;
       file<<"res.y="<<res.y<<std::endl;
       file.close();
    }
    std::string line;
    std::string name;
    std::string value;
    std::string inSection;
    int posEqual;
    while (std::getline(file, line))
    {
        if (!line.length()) continue;

        if (line[0] == '#') continue;
        if (line[0] == ';') continue;

        posEqual=line.find('=');
        name  = trim(line.substr(0,posEqual));
        value = trim(line.substr(posEqual+1));
        if(name == "res.x")
        {
            res.x = atoi(value.c_str());
        }
        else if(name == "res.y")
        {
            res.y = atoi(value.c_str());
        }
    }
}

resolution Config::GetResolution()
{
    return res;
}
