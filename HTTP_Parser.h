#include <string>
#include <unordered_map>
#include <sstream>

class HTTP_Parser
{
private:
    std::unordered_map<std::string, std::string> http;

public:
    HTTP_Parser(char *buf);
    ~HTTP_Parser();
    void show();
    std::string operator[](std::string str);
};

HTTP_Parser::HTTP_Parser(char *buf)
{
    std::string buf_string = buf;
    std::istringstream buf_stream(buf_string);
    std::string line;
    enum parts
    {
        request_response,
        header,
        body
    };
    parts part = request_response;
    std::string body_string;
    while (getline(buf_stream, line))
    {
        switch (part)
        {
        case request_response:
        {
            std::istringstream line_stream(line);
            std::string tmp;
            line_stream >> tmp;
            if (tmp.find("HTTP") == std::string::npos)
            {
                http.insert(std::make_pair("method", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("path", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("protocol", tmp));
            }
            else
            {
                http.insert(std::make_pair("protocol", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("status", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("status_msg", tmp));
            }
            part = header;
            break;
        }
        case header:
        {
            if (line.size() == 1)
            {
                part = body;
                break;
            }
            auto pos = line.find(":");
            std::string tmp1(line, 0, pos);
            std::string tmp2(line, pos + 2);
            http.insert(std::make_pair(tmp1, tmp2));
            break;
        }
        case body:
            body_string.append(line);
            body_string.append("\n");
            break;
        default:
            break;
        }
    }
    http.insert(std::make_pair("body", body_string));
}

HTTP_Parser::~HTTP_Parser()
{
}

void HTTP_Parser::show()
{
    for (auto unordered_map_it = http.cbegin(); unordered_map_it != http.cend(); ++unordered_map_it)
    {
        std::cout << unordered_map_it->first << ": " << unordered_map_it->second << std::endl;
    }
}

std::string HTTP_Parser::operator[](std::string str)
{
    auto it = http.find(str);
    return it != http.end() ? it->second : "";
}
