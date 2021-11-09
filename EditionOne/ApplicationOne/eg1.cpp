#include<viper>
#include<iostream>
using namespace std;
using namespace viper;
void doSomething()
{
cout<<"doSomething() got called and processing done\n";
}
int main()
{
ViperWebServer server(5050);
server.onRequest("/kkk",doSomething);
server.start();
return 0;
}
