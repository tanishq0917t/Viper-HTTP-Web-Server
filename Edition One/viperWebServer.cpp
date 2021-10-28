#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

typedef struct _request
{
char *method;
char *resource;
char isClientSideTechnologyResource;
char *mimeType;
}REQUEST;

int extensionEquals(const char *left,const char *right)
{
char a,b;
while(*left && *right)
{
a=*left;
b=*right;
if(a>=65 && a<=90)a+=32;
if(b>=65 && b<=90)b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}


char *getMimeType(char *resource)
{
char *mimeType;
mimeType=NULL;
int len=strlen(resource);
if(len<4) return mimeType;
int lastIndexOfDot=len-1;
while(lastIndexOfDot>0 && resource[lastIndexOfDot]!='.')lastIndexOfDot--;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*12);
strcpy(mimeType,"image/x-png");
}
return mimeType;
}


char isClientSideResource(char *bytes)
{
return 'Y';
}


REQUEST * parseRequest(char *bytes)
{
char method[11];
char resource[1001];
int i,j;
for(i=0;bytes[i]!=' ';i++) method[i]=bytes[i];  //Finding 1st space to get METHOD type
method[i]='\0';
i+=2;
for(j=0;bytes[i]!=' ';i++,j++) resource[j]=bytes[i]; // Find 2nd space to get RESOURCE for which request has arrived
resource[j]='\0';
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST)); //Creating REQUEST type structure
request->method=(char *)malloc((sizeof(char)*strlen(method))+1);
strcpy(request->method,method);
if(resource[0]=='\0') //if RESOURCE is '/' 
{
request->resource=NULL;
request->isClientSideTechnologyResource='Y';
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc((sizeof(char)*strlen(resource))+1);
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMimeType(resource);
}
return request;
}


int main()
{
FILE *f;
char g;
int i;
char requestBuffer[8193];
char responseBuffer[1025];
int bytesExtracted;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int len;
int length;
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);	//creating a server socket
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket at port: 5050\n");
return 0;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1)
{
printf("Viper Web Server is ready to accept request on port: 5050\n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,(socklen_t *)&len); //accept returns a number which denotes client socket
if(clientSocketDescriptor<0)
{
printf("Unable to accept client's connection\n");
return 0;
}
bytesExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0); //recieving request
if(bytesExtracted<0)
{
//what to do is yet not decided
}
else if(bytesExtracted==0)
{
//what to do is yet not decided
}
else
{
requestBuffer[bytesExtracted]='\0';
printf("%s\n",requestBuffer);
REQUEST *request=parseRequest(requestBuffer);		//parsing request
if(request->isClientSideTechnologyResource)		//is RESOURCE is of client side technology 
{
if(request->resource==NULL)				//if request is for RESOURCE='/'
{
printf("No Resource\n");
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
}
if(f==NULL) //send 404 ERROR
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:164\n\n<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Viper Web Server</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else //servering the resource (index.html or index.htm)
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nKeep-Alive: timeout=5,max=1000\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(1)
{
g=getc(f);
if(feof(f))
{
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
}
}
fclose(f);
}
}
else
{
f=fopen(request->resource,"rb");
if(f==NULL) // resource not found
{
char temp[501];
sprintf(temp,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>Viper Web Server</title></head><body><h2 style='color:red'>Resource \%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",static_cast<int>(strlen(temp)));
strcat(responseBuffer,temp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\nKeep-Alive: timeout=5,max=1000\n\n",length);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
while(1)
{
g=getc(f);
if(feof(f))
{
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
break;
}
responseBuffer[i++]=g;
if(i==1024)
{
responseBuffer[i]='\0';
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
i=0;
}
}
fclose(f);
}
}
}

else
{
//what to do for server side resource is yet not decided
}
}
}
close(clientSocketDescriptor);
close(serverSocketDescriptor);
return 0;
}
