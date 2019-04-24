#include <iostream>
#include <cstdlib>
//#include <unistd.h>
//#include <sys/types.h>
#include <cstring> //bzero
#include <sys/socket.h>
#include <netinet/in.h> //htons
using namespace std;

int main(int argc, char** argv){
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256];
	sockaddr_in serv_addr, cli_addr;
	int n; //how much data received
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) exit(1); //socket creation
	
//zero out that many bytes at the address &serv_addr
	bzero((char*)&serv_addr,   sizeof(serv_addr));
	portno = 8000;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY; //any address belongng to host
	serv_addr.sin_port = htons(portno); //convert the int

	if (bind(  sockfd, 
                   (struct sockaddr*)&serv_addr,
	           sizeof(serv_addr)  
                ) < 0
        ){
		cout<<"failed binding\n";
		exit(2);
	}
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	while(1){
		newsockfd=accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
		if(newsockfd <0) {
  		  cout<<"accept() returned, so a client has connected but the socket returned is invalid!\n";  exit(3);
		}

//now read from the new socket
		bzero(buffer, 256);
		n = read(newsockfd, buffer, 255);
		cout<<n<<" bytes read\n";
		if (n < 0) exit(4); //error

		cout<<"client said : "<<buffer<<endl;
		//reading again may hit EOF
		close(newsockfd);
	}
	close(sockfd);
}
