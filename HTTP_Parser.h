#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

class HTTP_Parser
{
private:
    std::unordered_map<std::string, std::string> http_package;

public:
    HTTP_Parser();
    HTTP_Parser(char *buf);
    ~HTTP_Parser();
    void show();
    std::string operator[](std::string str);
    void set(std::string key, std::string value);
};

HTTP_Parser::HTTP_Parser(char *buf)
{
    std::string buf_string = buf;
    std::istringstream buf_stream(buf_string);
    std::string line;
    for (int i = 0; getline(buf_stream, line); ++i)
    {
        if (i == 0)
        {
            std::istringstream line_stream(line);
            std::string tmp;
            line_stream >> tmp;
            http_package.insert(std::make_pair("Method", tmp));
            line_stream >> tmp;
            http_package.insert(std::make_pair("Path", tmp));
            line_stream >> tmp;
            http_package.insert(std::make_pair("Protocol", tmp));
        }
        else
        {
            auto pos = line.find(": ");
            if (pos == std::string::npos)
                continue;
            std::string tmp1(line, 0, pos);
            std::string tmp2(line, pos + 2);
            http_package.insert(std::make_pair(tmp1, tmp2));
        }
    }
}
HTTP_Parser::~HTTP_Parser()
{
}

void HTTP_Parser::show()
{
    for (auto it = http_package.cbegin(); it != http_package.cend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

std::string HTTP_Parser::operator[](std::string str)
{
    auto it = http_package.find(str);
    return it != http_package.end() ? it->second : "";
}

void HTTP_Parser::set(std::string key, std::string value)
{
    auto it = http_package.find(key);
    if (it == http_package.end())
    {
        http_package.insert(std::make_pair(key, value));
    }
    else
    {
        it->second = value;
    }
}