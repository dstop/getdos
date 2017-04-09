#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <netdb.h>

int i=0;
char ip[16];
char data[500];


void* senddata()
{
    int sockfd;
    struct sockaddr_in my_addr;
    char buf[4096];
    my_addr.sin_family = AF_INET;                 
    my_addr.sin_port = htons(80);             
    my_addr.sin_addr.s_addr = inet_addr(ip);  
    memset(my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));

    while (1) {
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
    if (connect(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) != -1)
        {
            send(sockfd, data, strlen(data), 0);
            i++;
            read(sockfd, buf, 4090);
            printf("%s\n", buf);
            //sleep(3);
            memset(buf, 0, sizeof(buf));
            
        }
    else{
            printf("connect fail.\r\n");
            sleep(2);
        }

    close(sockfd);
    }
}


int main(int argc,char *argv[])
{
    int thread=5,i1=0;
    struct hostent *hptr;
    char   str[32];
    char *url;
    char data1[500];
    char *host;


    if (argc>1)
    {
        strtok(argv[1],"/");
        host=strtok(NULL,"/");
        url=strtok(NULL,"/");
        sprintf(data1,"GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\nAccept: text/html\r\nAccept-Language: en-US\r\nAccept-Encoding: compress\r\nConnection: keep-alive\r\nCache-Control: no-cache\r\n\r\n",url,host);
        memcpy(data,data1,sizeof(data));
    } else {
        printf("not have a url.\r\n");
    }

    if (argc>2)
    {
        printf("Thread is %s \r\n", argv[2]);
        thread=atoi(argv[2]);
    }

    if((hptr = gethostbyname(host)) == NULL) {
        printf("  gethostbyname error\r\n");
    }
    inet_ntop(hptr->h_addrtype, hptr->h_addr_list[0], str, sizeof(str));
    sprintf(ip, "%s", str); 
    printf("ip:%s\n", ip);

    pthread_t a_thread[thread];
    for (i1 = 0; i1 < thread; i1++)
    {
        printf("%d\n", i1+1);
        pthread_create(&a_thread[i1], NULL, senddata, NULL);
        usleep(300000);
    }
    
    while(1){
        printf("  Send number : %d\r", i);
        fflush(stdout);
        usleep(100000);
    }
}

