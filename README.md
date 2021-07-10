# HTTP_Parser

C++版本的 HTTP 协议解析器，可自动识别 request 与 response 请求。

### how to use

```c++
#include "HTTP_Parser.h"    //使用前引入头文件
···
···
char buf[1024];    //buf是用于接收socket流的缓存区
read(client_sockfd, buf, sizeof(buf));    //从socket读取到buf
···
···
HTTP_Parser http_package(buf);    //将buf构造成一个HTTP_Parser类
//此时http_package中包含了一个std::unordered_map<std::string, std::string>的字典，保存http报文字段信息
···
···
//返回字段的值(std::string类型)，如找不到则返回空std::string
http_package["Content-Type"];
http_package["User-Agent"];
http_package["body"];
···
···
http_package.show();    //显示http报文，会直接输出到控制台
/*
    body: {
        "name": "sample",
        "time": "Wed, 21 Oct 2015 18:27:50 GMT"
    }

    content-length: 69
    accept-encoding: gzip, deflate
    Host: 127.0.0.1:1234
    method: POST
    protocol: HTTP/1.1
    path: /
    content-type: application/json
    Connection: close
    user-agent: vscode-restclient
*/
```
