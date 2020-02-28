	#ifndef SOCKET_NODE_H
	#define SOCKET_NODE_H
	/**
	C++ client example using sockets
	*/
	#include <ros/ros.h>
	#include <arpa/inet.h>  //inet_addr
	#include <iostream>     //cout
	#include <netdb.h>      //hostent
	#include <stdio.h>      //printf
	#include <string.h>     //strlen
	#include <string>       //string
	#include <sys/socket.h> //socket

	/**
	TCP Client class
	*/
	class tcp_client
	{
	private:
	    int sock;
	    std::string address;
	    int port;
	    struct sockaddr_in server;

	public:
	    tcp_client(){
	    	sock = -1;
	    	port = 0;
	    	address = "";
		}


		/**
		Connect to a host on a certain port number
		*/
	    bool conn(std::string address, int port)
		{
	    // create socket if it is not already created
	    if(sock == -1) {
	        // Create socket
	        sock = socket(AF_INET, SOCK_STREAM, 0);
	        if(sock == -1) {
	            perror("Could not create socket");
	        }

	        std::cout << "Socket created\n";
	    } else { /* OK , nothing */
	    }

	    // setup address structure
	    if(inet_addr(address.c_str()) == -1) {
	        struct hostent* he;
	        struct in_addr** addr_list;

	        // resolve the hostname, its not an ip address
	        if((he = gethostbyname(address.c_str())) == NULL) {
	            // gethostbyname failed
	            herror("gethostbyname");
	            std::cout << "Failed to resolve hostname\n";

	            return false;
	        }

	        // Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
	        addr_list = (struct in_addr**)he->h_addr_list;

	        for(int i = 0; addr_list[i] != NULL; i++) {
	            // strcpy(ip , inet_ntoa(*addr_list[i]) );
	            server.sin_addr = *addr_list[i];

	            std::cout << address << " resolved to " << inet_ntoa(*addr_list[i]) << std::endl;

	            break;
	        }
	    }

	    // plain ip address
	    else {
	        server.sin_addr.s_addr = inet_addr(address.c_str());
	    }

	    server.sin_family = AF_INET;
	    server.sin_port = htons(port);

	    // Connect to remote server
	    if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
	        perror("connect failed. Error");
	        return 1;
	    }

	    std::cout << "Connected\n";
	    return true;
	}



	/**
	Send data to the connected host
	*/
	bool send_data(std::string data)
	{
	    // Send some data
	    if(send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
	        perror("Send failed : ");
	        return false;
	    }
	    std::cout << "Data send\n";

	    return true;
	}

	/**
	Receive data from the connected host
	*/
	std::string receive(int size = 512)
	{
	    char buffer[size];
	    std::string reply;

	    // Receive a reply from the server
	    if(recv(sock, buffer, sizeof(buffer), 0) < 0) {
	        puts("recv failed");
	    }

	    reply = buffer;
	    return reply;
	}
};
	#endif /* SOCKET_NODE_H */