#include <iostream>
#include <cstdio>
//#include <sys/types.h>
#include <unistd.h>
#include <cstdlib> //exit()
#include <cstring> //bzero
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> //gethostbyname()
using namespace std;

int main(int argc, char** argv){
	int sockfd, n, portno;
	char buffer[256];
	sockaddr_in serv_addr; //a struct
	portno = 8000;
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //the fd used in client process
	if (sockfd < 0){
		cout<<"error creating socket\n";
		exit(1);
	}
	//tmp variable
	hostent* _server = gethostbyname("localhost");
	if (_server == NULL) exit(2);

// init serv_addr:
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	bcopy(  (char*)_server->h_addr,
	        (char*)&serv_addr.sin_addr.s_addr,
		_server->h_length);

	if (connect(sockfd, 
		   (struct sockaddr*)&serv_addr,
		   sizeof(serv_addr)) < 0
  	) exit(3);

	char pidstr[8];
	sprintf(pidstr, "%d", getpid());

	strcpy(buffer, "hello from PID ");
	strcat(buffer, pidstr);
	cout<<"buffer contains: "<<buffer<<endl;

	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) exit(4);
	close(sockfd);
}
