#include <string>
#include <map>
#include <sstream>

class HttpParser{
private:
    std::map<std::string, std::string> http;
    std::string format_key(std::string &str);
public:
    HttpParser(char *buf);
    ~HttpParser();
    void show();
    std::string operator[](std::string str);
};

HttpParser::HttpParser(char *msg){
    std::string buf(msg);
    std::istringstream buf_stream(buf);
    enum parts{
        start_line,
        headers,
        body
    };
    parts part = start_line;
    std::string line;
    std::string body_string;
    while(getline(buf_stream, line)){
        switch (part)
        {
        case start_line:
        {
            std::istringstream line_stream(line);
            std::string tmp;
            line_stream >> tmp;
            if(tmp.find("HTTP") == std::string::npos){
                http.insert(std::make_pair("method", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("path", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("version", tmp));
            } else{
                http.insert(std::make_pair("version", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("status", tmp));
                line_stream >> tmp;
                http.insert(std::make_pair("status_text", tmp));
            }
            part = headers;
            break;
        }
        case headers:
        {
            if(line.size() == 1){
                part = body;
                break;
            }
            auto pos = line.find(":");
            if(pos == std::string::npos)
                continue;
            std::string tmp1(line, 0, pos);
            std::string tmp2(line, pos + 2);
            http.insert(std::make_pair(format_key(tmp1), tmp2));
            break;
        }
        case body:
        {
            body_string.append(line);
            body_string.push_back('\n');
            break;
        }
        default:
            break;
        }
    }
    http.insert(std::make_pair("body", body_string));
}

HttpParser::~HttpParser(){}

void HttpParser::show(){
    for(auto it = http.cbegin(); it != http.cend(); ++it){
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

std::string HttpParser::operator[](std::string str){
    auto it = http.find(format_key(str));
    return it != http.end() ? it->second : "";
}

HttpParser::format_key(std::string &str){
    if(str[0] >= 'a' && str[0] <= 'z'){
        str[0] = str[0] + 'A' - 'a';
    }
    int position = 0;
    while((position = str.find("-", position)) != std::string::npos){
        if(str[position + 1] >= 'a' && str[position + 1] <= 'z'){
            str[position + 1] = str[position + 1] + 'A' - 'a';
        }
        position++;
    }
    return str;
}