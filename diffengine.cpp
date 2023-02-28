#include "diffengine.h"

std::vector<std::string> DiffEngine::compare(const std::string& file_name1, const std::string& file_name2)
{
    std::vector<std::string> diff;
    std::ifstream file1(file_name1);
    std::ifstream file2(file_name2);

    std::string line1, line2;
    int lineNumber = 1;
    while (getline(file1, line1) && getline(file2, line2)) {
        if (line1 != line2) {
            diff.push_back("Line " + std::to_string(lineNumber) + ": " + line1 + " != " + line2);
        }
        lineNumber++;
    }
    if (getline(file1, line1)) {
        diff.push_back("File 1 has more lines than File 2");
    }
    else if (getline(file2, line2)) {
        diff.push_back("File 2 has more lines than File 1");
    }
    return diff;
}
