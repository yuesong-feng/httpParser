# httpParser

C++版本的 HTTP 协议解析器，可自动识别 request 与 response 请求

使用了 C++ 11 标准，编译时需要添加`-std=c++11`

## api

`HTTP_Parser http_package()` 构造一个空 http 报文类

`HTTP_Parser http_package(char buf*)` 解析存储在数组 buf 里的 http 报文

`http_package.show()` 显示 http 报文，会直接输出到控制台

`http_package[std::string str]` 查找字段并返回值(std::string 类型)，不区分字段中的大小写，如找不到则返回空 std::string

## usage example

```c++
#include "HTTP_Parser.h"    //使用前引入头文件
···
···
char buf[1024];    //buf是用于接收socket流的缓存区
read(client_sockfd, buf, sizeof(buf));    //从socket读取到buf
···
···
HTTP_Parser http_package(buf);    //将buf构造成一个HTTP_Parser类
//此时http_package中包含了一个std::unordered_map<std::string, std::string>的字典，保存http报文字段信息。字典中的所有key大小写不敏感，但都按照标准规则命名（单词首字符大写，单词之间用'-'连接）。
···
···
//查找字段并返回值(std::string类型)，不区分字段中的大小写，如找不到则返回空std::string
http_package["content-Type"];
http_package["user-agent"];
http_package["Accept-encoding"];
http_package["body"];
···
···
http_package.show();    //显示http报文，会直接输出到控制台
/*
    body: {
        "name": "sample",
        "time": "Wed, 21 Oct 2015 18:27:50 GMT"
    }

    Content-Length: 69
    Accept-Encoding: gzip, deflate
    Host: 127.0.0.1:1234
    method: POST
    version: HTTP/1.1
    path: /
    Content-Type: application/json
    Connection: close
    User-Agent: vscode-restclient
*/
```
