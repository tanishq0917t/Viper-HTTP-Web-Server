#include<viper>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;
using namespace viper;
class Student
{
private:
char name[21];
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
response.write("<body>");
response.write("<h1>Student Add Module</h1>");
response.write("Student Added<br>");
response.write("<a href='/index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
response.closeConnection();
}


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
response.write("</body>");
response.write("</html>");
response.closeConnection();
}
int main()
{
ViperWebServer server(5050);
server.onRequest("/addStudent",addStudent);
server.onRequest("/getStudent",getStudent);
server.start();
return 0;
}
