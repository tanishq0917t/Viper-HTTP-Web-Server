<p>
  <center>
  <img src="https://github.com/tanishq-17102001/tanishq-17102001.github.io/blob/main/images/viper.png?" />
  </center>
</p>
![ALT TEXT](https://github.com/tanishq-17102001/tanishq-17102001.github.io/blob/main/images/viper.png?raw=true)
# Viper HTTP Web Server
Viper is an C++ based HTTP Web Server which can serve static and dynamic web applications. Server side programming should be C/C++, which makes it very interesting.
# How to use Viper HTTP Web Server
First of all you need to download the zip file, unzip it and in folder Edition One you can create your own folder for specific web application, as for testing i have made a folder named as webone in which i am developing my web application. 
In webone folder you need to create a cpp file which should **include viper** library and you need to use **namespace viper**.
```
#include<viper>
using namespace viper;
```
> For compiling you need to run the command as
```
//for linux
g++ -static file_name.cpp -o file_name.out -I ../vws/include -L ../vws/lib -lviper
//for winows
g++ -static file_name.cpp -o file_name.exe -I ../vws/include -L ../vws/lib -lviper -lws2_32
// -lws2_32 is used for including the libraries required for the socket libraries
```

> For creating instance of Web Server and starting it
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
## Demonstration Of Request forwarding feature
If application developer wants to forward the request to anyother resource (it can be server side or client side resource), he/she has to use forward() function.
```
void aaa(Request &request,Response &response)
{
//many many lines of code of processing
request.forward("bbb");
//or it can be
// request.forward("abcd.html?x=10");
}
```
# Demonstration of creating Web Application using Viper Web Server
This script contains code to add student's details (roll number and name to file using file handling) and get details of student.
###### serverScript.cpp
These are the header files and namespaces that are required.
```
#include<viper>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
using namespace viper;
```
This is the student class whose objects will be written in file.
```
class Student
{
private:
char name[51];
char roll[4];
public:
Student()
{
name[0]='\0';
roll[0]='\0';
}
void setName(const char *name)
{
strcpy(this->name,name);
}
void setRoll(const char *roll)
{
strcpy(this->roll,roll);
}
void getName(char *name)
{
strcpy(name,this->name);
}
void getRoll(char *roll)
{
strcpy(roll,this->roll);
}
};
```
This addStudent() function will fetch name and roll number from request string and will create a student object and will write it in a file named **student.dat**
```
void addStudent(Request &request,Response &response)
{
cout<<"Student Roll Number: "<<request.get("rl")<<endl;
cout<<"Student Name: "<<request.get("nm")<<endl;
Student student;
student.setName(request.get("nm").c_str());
student.setRoll(request.get("rl").c_str());
ofstream file("student.data",ios::app | ios::binary);
file.write((char *)&student,sizeof(Student));
file.close();
response.write("<!DOCTYPE HTML>");
response.write("<html>");
response.write("<head lang='en'>");
response.write("<title>Add Module</title>");
response.write("</head>");
response.write("<body><center>");
response.write("<h1>Student Add Module</h1>");
response.write("Student Added<br>");
response.write("<a href='/index.html'>Home</a>");
response.write("</center></body>");
response.write("</html>");
response.closeConnection();
}
```
This getStudent() function will open file named **student.dat** and will create a HTML and will send it using write() function using response pointer.
```
void getStudent(Request &request,Response &response)
{
ifstream file;
file.open("student.data",ios::binary);
Student student;
char name[21];
char roll[4];
response.write("<!DOCTYPE HTML>");
response.write("<html>");
response.write("<head lang='en'>");
response.write("<title>Get Module</title>");
response.write("</head>");
response.write("<body>");
response.write("<center>");
response.write("<h1>Student Get Module</h1>");
response.write("Students List<br>");
while(1)
{
file.read((char *)&student,sizeof(student));
if(file.fail()) break;
student.getRoll(roll);
student.getName(name);
response.write(roll);
response.write("    ");
response.write(name);
response.write("<br>");
}
file.close();
response.write("<br><a href='/index.html'>Home</a>");
response.write("</center>");
response.write("</body>");
response.write("</html>");
response.closeConnection();
}
```
This aaa() function is used for demonstrating use of forwarding feature
```
void aaa(Request &request,Response &response)
{
request.forward("getStudent");
}
```
Main function where instance of ViperWebServer is created and request mappings are declared and server is started.
```
int main()
{
ViperWebServer server(5050);
server.onRequest("/addStudent",addStudent);
server.onRequest("/getStudent",getStudent);
server.onRequest("/aaa",aaa);
server.start();
return 0;
}
```
## Screenshots
**index.html**\
![ALT TEXT](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/screenshots/indexPage.png?raw=true)\
**Filling form**\
![Alt Text](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/screenshots/fillingAddForm.png?raw=true)\
**Notification of Student Added**\
![ALT TEXT](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/screenshots/notification.png?raw=true)\
**Get Students (List of students)**\
![ALT TEXT](https://github.com/tanishq-17102001/Viper-HTTP-Web-Server/blob/main/EditionOne/webone/screenshots/getStudents.png?raw=true)
