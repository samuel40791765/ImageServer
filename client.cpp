/* a client in the unix domain */
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

void error(const char *);


int main(int argc, char *argv[])
{
   int sockfd, servlen,n;
   struct sockaddr_in  serv_addr;
   char buffer[82];
    
    char *filename =new char[20];
    filename=argv[4];

   bzero((char *)&serv_addr,sizeof(serv_addr));
    int port=stoi(argv[2]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(port);
  // strcpy(serv_addr.sun_path, argv[1]);
   //servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
   if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) < 0)
       error("Creating socket");
   if (connect(sockfd, (struct sockaddr *) 
                         &serv_addr, sizeof(serv_addr)) < 0)
       error("Connecting");
    
    bzero(buffer,82);
    write(sockfd,argv[3],strlen(argv[2]));
    
    
    FILE *image;
    image = fopen(filename, "wb");
    int size,read_size,recv_size = 0;
    read(sockfd, &size, sizeof(int));
    printf("%d\n",size);
    printf("Reading Picture Byte Array\n");
    char p_array[size];
    while(recv_size<size){
        do{
            read_size = read(sockfd,p_array, size);
            fwrite(p_array, 1, read_size, image);
        }while(read_size <0);
        
        recv_size += read_size;
        printf("%d\n",read_size);
    }
    
 //   read(sockfd, p_array, size);
    //printf("Converting Byte Array to Picture\n");
    
    
   
    fclose(image);
    
   
   close(sockfd);
   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
