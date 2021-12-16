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
Whenever a request is arrived at server end, it checked that it is a client side resource or server side resource that means there has to be processing on server side or directly the resouce has to be served.\
\
Such as request arrived for a.jpeg (this is a **client side resource**, no processing is required) so directly contents of the resource are served.\
\
Request arrived for **/addStudent** (this is a **server side script**, that needs to be processed) after processing, necessary actions are taken such as forwarding request to another resource or sending contents of response.\
\
Given below is the image of the server application running on terminal.
![Alt Text](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/Console%20Screenshot.png?raw=true)
\
You can see in the above image, against Client Side Resource: **N** is written, that means it is server side script, which will be processed and all actions will be taken.
