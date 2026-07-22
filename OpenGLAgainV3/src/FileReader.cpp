#include <FileReared.h>
#include<fstream>
#include<iostream>
#include<sstream>

std::string FileReared::ReadFileFromSource(const std::string& source)
{
    std::ifstream file(source, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        std::cout << "COULD NOT OPEN THE FILE" << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    return content;
    
}
