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
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_srvs/Trigger.h>
#include <trajectory_msgs/JointTrajectory.h>

using namespace std;

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
    tcp_client();
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
};

tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}

/**
Connect to a host on a certain port number
*/
bool tcp_client::conn(string address, int port)
{
    // create socket if it is not already created
    if(sock == -1) {
        // Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock == -1) {
            perror("Could not create socket");
        }

        cout << "Socket created\n";
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
            cout << "Failed to resolve hostname\n";

            return false;
        }

        // Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr**)he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++) {
            // strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];

            cout << address << " resolved to " << inet_ntoa(*addr_list[i]) << endl;

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

    cout << "Connected\n";
    return true;
}

/**
Send data to the connected host
*/
bool tcp_client::send_data(string data)
{
    // Send some data
    if(send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
        perror("Send failed : ");
        return false;
    }
    cout << "Data send\n";

    return true;
}

/**
Receive data from the connected host
*/
string tcp_client::receive(int size = 512)
{
    char buffer[size];
    string reply;

    // Receive a reply from the server
    if(recv(sock, buffer, sizeof(buffer), 0) < 0) {
        puts("recv failed");
    }

    reply = buffer;
    return reply;
}

int main(int argc, char* argv[])
{

    int param;
    ros::init(argc, argv, "vision_system_name");
    ros::NodeHandle nh("~");
    nh.getParam("param", param);
    ROS_INFO("Got parameter : %d", param);

    tcp_client c;
    string host;

    //cout << "Enter hostname : ";
    //cin >> host;
    //host = "agility.el.nist.gov";
    //int port = 5002;

    //-- connection to the gripper
    host = "optimus.el.nist.gov";
    int port = 1234;

    // connect to host
    c.conn(host, port);

    // send some data
    //c.send_data("GET / HTTP/1.1\r\n\r\n");
    //c.send_data("1");

    if(param == 1)
        {
          //cout << check << endl;
          c.send_data("1");
          //blue();
        }
         else if(param == 0)
        {
          //cout << check << endl;
          c.send_data("0");
        }
        else
        {
          cout << "Wrong parameter to control the gripper!!! " << endl;
        }  

    // receive and echo reply
    //cout << "----------------------------\n\n";
    //cout << c.receive(2560);
    //cout << "\n\n----------------------------\n\n";

    // done
    return 0;
}
