#ifndef DIFFENGINE_H
#define DIFFENGINE_H

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>

class DiffEngine
{
public:
    std::vector<std::string> compare(const std::string& file_name1, const std::string& file_name2);
};

#endif // DIFFENGINE_H
