# Viper HTTP Web Server
Viper is an C++ based HTTP Web Server which can server static and dynamic web applications. Server side programming should be C/C++, which makes it very interesting.
# How to use Viper HTTP Web Server
First of all you need to download the zip file, unzip it and in folder Edition One you can create your own folder for specific web application, as for testing i have made a folder named as webone in which i am developing my web application. 
In webone folder you need to create a cpp file which should include viper library and using namespace viper.
```
#include<viper>
using namespace viper;
```
For compiling you need to run the command as
```
//for linux
g++ -static file_name.cpp -o file_name.out -I ../vws/include -L ../vws/lib -lviper
//for winows
g++ -static file_name.cpp -o file_name.exe -I ../vws/include -L ../vws/lib -lviper -lws2_32
// -lws2_32 is used for including the libraries required for the socket libraries
```

For creating instance of Web Server and starting it
```
ViperWebServer server(5050);                  //Creating object
server.onRequest("/addStudent",addStudent);   //mapping request with function
server.onRequest("/getStudent",getStudent);   //mapping request with function
server.start();                               //Starting the server
```
Given below is the image of the server application running on terminal.
![Alt Text](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/Console%20Screenshot.png?raw=true)
