#include "libraries.h"

int main(int argc, char* argv[])
{

    /*
    *
    * int status - Variable to capture WSAStartup() return value. Returns 0 for success, non-zero integer for failure.
    *
    * WSADATA winsock_info - Struct value to store information about the version of winsock library. Also includes network system information.
    *
    * SOCKET clientSocket - Struct value that accepts a numeric file descriptor to represent an I/O network resource.
    *
    * struct sockaddr_in serverAddress - Struct value that stores IPv4 address and socket information of connection endpoint.
    *
    */

    int status;
    WSADATA winsock_info;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


          // Windows Sockets API initializer function //
          /*
          * WSAStartup() - Communictaes with Windows Kernel that NIC card will be used for socket connections.
          *  - MAKEWORD(2,2): Paramater to specify version used (2.2).
          *  - &winsock_info: Passing in winsock library information.
          *
          * WSAGetLastError() - Function to return diagnostic error codes for debugging.
          *
          */


    if ((status = WSAStartup(MAKEWORD(2, 2), &winsock_info)) != 0) {

        printf("WinSock API Error: Error Code %d", WSAGetLastError());

        return -1;

    }
    else {

        system("cls");

        printf("WinSock API Success: Ready to create Client socket.\n\n");

        system("pause");
        system("cls");

    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


       // Server socket initializer function //
          /*
          * socket() - Returns a network file descriptor. Creates an instance of an endpoint for connection.
          *  - AF_INET: Macro for address family. Represents IPv4.
          *  - SOCK_STREAM: Macro for the socket communication type. Represents TCP which is connection-oriented.
          *  - IPPROTO_TCP: Macro for transport layer (L4) protocol used. Represents Transmission Control Protocol.
          *  - INVALID_SOCKET: Macro for detecting failures in creating of socket file descriptor.
          *
          * WSACleanup() - Cleans up all resources allocated for the Winsock library.
          *
          * htons() - Converts port integer to 16-bit binary representation.
          *
          * INADDR_ANY - Accepts all connections from any IPv4 address.
          *
          */


    if ((clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {

        printf("Client Socket Error: Error Code %d", WSAGetLastError());
        WSACleanup();

        return -1;

    }
    else {

        printf("Client Socket Success: Configuring server endpoint information...\n\n");

        serverAddress.sin_family = AF_INET;
        printf("Address Family Scheme: IPv4\n");

        serverAddress.sin_port = htons(8080);
        printf("Virtual Network Port (Server): 8080\n");

        inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));
        printf("Server IPv4 Address: 127.0.0.1 (localhost)\n\n");

        printf("Ready to connect...\n\n");

        system("pause");
        system("cls");

    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if ((connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))) == SOCKET_ERROR) {

        printf("Connection Error: Error Code %d ", WSAGetLastError());

        return -1;

    }
    else {

        printf("Connection Success: Connected to server.\n\n");

        char io_choice[10];

        printf("Type 'FILE' to send a file, 'MSG' for instant messaging: ");
        fgets(io_choice, 10, stdin);
        io_choice[strcspn(io_choice, "\n")] = '\0';

        system("cls");

        if (strcmp(io_choice, "MSG") == 0)
        {
            printf("<INSTANT MESSAGING MODE>\n");
            printf("Type 'exit' to leave <INSTANT MESSAGING MODE>\n\n\n");

            send(clientSocket, "MSG", 4, 0);

            while (1)
            {
                int serverMsgSize = 0;
                char message[1024];

                printf("Enter a message to send to server: ");
                fgets(message, 1024, stdin);

                message[strcspn(message, "\n")] = '\0';

                if (strcmp(message, "exit") == 0) {
                    printf("Exiting message mode.\n");

                    system("pause");
                    system("cls");
                    break;
                }

                if ((send(clientSocket, message, strlen(message), 0)) == SOCKET_ERROR) {

                    printf("Client Message Send Error: Error Code %d", WSAGetLastError());

                    return -1;

                }
                else {

                    printf("Client Message Sent. Waiting for server reponse...\n\n");

                    if ((serverMsgSize = recv(clientSocket, message, 1024, 0)) <= 0) {

                        printf("Server Message Receive Error: Error Code %d ", WSAGetLastError());

                        return -1;

                    }
                    else {

                        message[serverMsgSize] = '\0';

                        printf("Message recieved from server: %s\n", message);

                    }

                }




            }


        }
        else if (strcmp(io_choice, "FILE") == 0) {

            printf("<FILE TRANSFER MODE>\n");

            send(clientSocket, "FILE", 4, 0);

            char choice[10];
            char filepath[256];
            FILE* infile;

            printf("Please provide the path of the file you would like to send: ");
            fgets(filepath, 256, stdin);
            filepath[strcspn(filepath, "\n")] = '\0';
            printf("\n\n");

            if (!(infile = fopen(filepath, "rb"))) {

                printf("File Error: File or path not valid");
                return -1;

            }
            else {

                char filebuf[1024];
                size_t filebytes;

                int fileSize = 0;
                fseek(infile, 0, SEEK_END);
                fileSize = ftell(infile);
                rewind(infile);

                send(clientSocket, (char*) &fileSize, sizeof(fileSize), 0);

                char ACK_msg[4];

                while ((filebytes = fread(filebuf, 1, sizeof(filebuf), infile)) > 0)
                {
                    send(clientSocket, filebuf, filebytes, 0);
                }

                fclose(infile);

                printf("File sent to server. Waiting for ACK.\n\n");

                recv(clientSocket, ACK_msg, 3, 0);
                ACK_msg[3] = '\0';

                if (strcmp(ACK_msg, "ACK") == 0)
                {
                    printf("ACK recieved.\n\n");

                    printf("Type 'GET' to retrieve a file from the server. Type 'exit' otherwise: ");
                    fgets(choice, 10, stdin);

                    choice[strcspn(choice, "\n")] = '\0';

                    if (strcmp(choice, "exit") == 0)
                    {
                        printf("Exiting file transfer mode.\n");

                        closesocket(clientSocket);
                        WSACleanup();

                        return 0;

                    }
                    else if (strcmp(choice, "GET") == 0)
                    {
                        send(clientSocket, "GET", 3, 0);

                        char newFileName[256] = { 0 };

                        int fileByteSize = 0;
                        FILE* outfile;

                        printf("Save file as: ");
                        fgets(newFileName, 256, stdin);
                        newFileName[strcspn(newFileName, "\n")] = '\0';


                        if (!(outfile = fopen(newFileName, "wb")))
                        {

                            printf("Error opening file for writing\n");
                            fflush(stdout);

                            return -1;

                        }

                        while ((fileByteSize = recv(clientSocket, filebuf, sizeof(filebuf), 0)) > 0)
                        {
                            fwrite(filebuf, 1, fileByteSize, outfile);
                        }

                        if (fileByteSize < 0)
                        {
                            printf("File Receive Error: %d\n", WSAGetLastError());
                            fflush(stdout);
                        }
                        else
                        {
                            printf("File transfer complete! File saved as: %s\n", newFileName);
                            fflush(stdout);
                        }

                        fclose(outfile);

                        closesocket(clientSocket);
                        WSACleanup();


                        return 0;


                    }

                }









            }

        }
    }




    return 0;
}