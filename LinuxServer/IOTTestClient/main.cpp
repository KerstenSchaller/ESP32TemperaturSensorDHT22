/*
	Simple udp client
*/
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include <chrono>
#include <thread>

//#define SERVER "192.168.1.116"
#define SERVER "255.255.255.255"
#define BUFLEN 512	//Max length of buffer
#define PORT 4444	//The port on which to send data

               using namespace std::this_thread; // sleep_for, sleep_until
               using namespace std::chrono; // nanoseconds, system_clock, seconds


void die(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in si_other;
	int s, i, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];

	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	int broadcastEnable=1;
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	
	if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	while(1)
	{
		//printf("Enter message : ");
		//gets(message);
		
		//send the message
		if (sendto(s, argv[1], strlen(argv[1]) , 0 , (struct sockaddr *) &si_other, slen)==-1)
		{
			die("sendto()");
		}
/*		
		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf,'\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
		{
			die("recvfrom()");
		}
		
		puts(buf);
*/

               sleep_for(seconds(1));
	}

	//close(s);
	return 0;
}
