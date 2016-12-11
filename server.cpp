/* a server in the unix domain.  The pathname of 
   the socket address is passed as an argument */
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

void error(const char *);
std::ifstream::pos_type filesize(const char* filename);

int main(int argc, char *argv[])
{
   int sockfd, newsockfd, servlen, n,stat,read_size;
   socklen_t clilen;
   struct sockaddr_in cli_addr, serv_addr;
   char buf[80];
    
    FILE *picture;
    int size;
    
    char *first=new char[20];
    char *second=new char[20];
    

    first=argv[2];
    second=argv[3];
    
   if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
       error("creating socket");
   bzero((char *) &serv_addr, sizeof(serv_addr));
    int port=stoi(argv[1]);
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr=INADDR_ANY;
    printf("%d\n",port);
   serv_addr.sin_port=htons(port);
 //  strcpy(serv_addr.sun_path, argv[1]);
   //servlen=strlen(serv_addr.sun_path) + sizeof(serv_addr.sin_family);
   if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
       error("binding socket"); 

   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
    if (newsockfd < 0) {
        error("accepting");
    }
    n=read(newsockfd,buf,80);
    write(1,buf,n);
    printf("A connection has been established\n");
    if(strncmp(buf,"1",1)==0){
        picture = fopen(first, "rb");
        size=filesize(argv[2]);
        fseek(picture, 0, SEEK_SET);
    }
    else if(strncmp(buf,"2",1)==0){
        picture = fopen(second, "rb");
        size=filesize(argv[3]);
        fseek(picture, 0, SEEK_SET);
    }
    write(newsockfd, &size, sizeof(size));
    
    //FILE *out;
    //out=fopen("out.jpg","wb+");
    char send_buffer[size];
    while(!feof(picture)) {
        read_size = fread(send_buffer, 1, sizeof(send_buffer), picture);
        do{
            stat = write(newsockfd, send_buffer, read_size);
          //  fwrite(send_buffer, 1, sizeof(send_buffer), out);
        }while (stat < 0);
        bzero(send_buffer,sizeof(send_buffer));
    }
    
   // fclose(out);
    
   //write(newsockfd,"I got your message\n",19);
    
   close(newsockfd);
   close(sockfd);
   return 0;
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}


void error(const char *msg)
{
    perror(msg);
    exit(0);
}
