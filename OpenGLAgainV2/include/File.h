#pragma once 
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>

class File
{
 
public:
  static  std::string  readTextFileToCString(const std::string& filepath);
};

 

