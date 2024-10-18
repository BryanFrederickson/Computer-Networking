
#include "libraries.h"

int main(int argc, char* argv[])
{
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       // Variables //
       /*
       *
       * int status - Variable to capture WSAStartup() return value. Returns 0 for success, non-zero integer for failure.
       *
       * WSADATA winsock_info - Struct value to store information about the version of winsock library. Also includes network system information.
       *
       * SOCKET serverSocket - Struct value that accepts a numeric file descriptor to represent an I/O network resource.
       *
       * SOCKET clientSocket - Struct value to represent a socket for an accepted client connection.
       *
       * struct sockaddr_in serverAddress - Struct value that stores IPv4 address and socket information of server endpoint.
       *
       * struct sockaddr_in clientAddress - Struct value that stores information about the client socket connection.
       *
       */

    int status;
    WSADATA winsock_info;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    int clientAddressSize = sizeof(clientAddress);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
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

    if ((status = WSAStartup(MAKEWORD(2, 2), &winsock_info)) != 0)
    {

        printf("WinSock API Error: Error Code %d", WSAGetLastError());

        return -1;

    }
    else
    {

        system("cls");

        printf("WinSock API Success: Ready to create Server socket.\n\n");

        system("pause");
        system("cls");

    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
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

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {

        printf("Server Socket Error: Error Code %d", WSAGetLastError());
        WSACleanup();

        return -1;

    }
    else
    {

        printf("Server Socket Success: Configuring client endpoint information...\n\n");

        serverAddress.sin_family = AF_INET;
        printf("Address Family Scheme: IPv4\n");

        serverAddress.sin_port = htons(8080);
        printf("Virtual Network Port (Client): 8080\n");

        serverAddress.sin_addr.s_addr = INADDR_ANY;
        printf("Client IPv4 Address: Any\n\n");

        printf("Ready to bind...\n\n");

        system("pause");
        system("cls");

    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       // Server bind function //
       /*
       * bind() - Assigns the address and port to the server socket.
       *
       * WSAGetLastError() - Function to return diagnostic error codes for debugging.
       *
       */

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {

        printf("Bind Error: Error Code %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();

        return -1;
    }
    else
    {

        printf("Bind Success: Ready to receive client connections.\n\n");

        system("pause");
        system("cls");

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {

        printf("Listen Error: Error Code %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();

        return -1;
    }
    else
    {

        printf("Server is listening on port 8080...\n\n");

    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /********************************************************************************************************************************************************/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize)) == INVALID_SOCKET)
    {

        printf("Accept Error: Error Code %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();

        return -1;

    }
    else
    {

        system("cls");

        printf("Connection Success: Connected to client.\n\n");

        char command[5];
        recv(clientSocket, command, 4, 0);
        command[4] = '\0';

        system("cls");

        if (strcmp(command, "MSG") == 0)
        {

            printf("<INSTANT MESSAGING MODE>\n");
            printf("Type 'exit' to leave <INSTANT MESSAGING MODE>\n\n\n");
            printf("Waiting for message sent from client...\n\n");

            while (1)
            {
                int clientMsgSize = 0;
                char message[1024] = { 0 };

                if ((clientMsgSize = recv(clientSocket, message, sizeof(message), 0)) <= 0)
                {

                    printf("Client Message Receive Error: Error Code %d\n", WSAGetLastError());

                    return -1;

                }
                else
                {

                    message[clientMsgSize] = '\0';

                    printf("Message recieved from client: %s\n", message);

                }

                printf("Enter a message to send to client: ");
                fgets(message, 1024, stdin);

                message[strcspn(message, "\n")] = '\0';

                if (strcmp(message, "exit") == 0)
                {
                    printf("Exiting message mode.\n");

                    system("pause");
                    system("cls");
                    break;
                }

                if ((send(clientSocket, message, strlen(message), 0)) == SOCKET_ERROR)
                {

                    printf("Message Send Error: Error Code %d\n", WSAGetLastError());

                    return -1;

                }

                printf("Server Message Sent. Waiting for client reponse...\n\n");

            }


        }
        else if (strcmp(command, "FILE") == 0)
        {

            char filebuf[1024];
            char newFileName[256] = { 0 };

            int fileByteSize = 0;
            FILE* outfile;


            printf("File transfer initiated...\n\n");

            printf("Save file as: ");
            fgets(newFileName, 256, stdin);
            newFileName[strcspn(newFileName, "\n")] = '\0';


            if (!(outfile = fopen(newFileName, "wb")))
            {

                printf("Error opening file for writing\n");

                return -1;

            }

            int fileSize = 0;
            recv(clientSocket, (char*)& fileSize, sizeof(fileSize), 0);

            int totalReceivedBytes = 0;

            while (totalReceivedBytes < fileSize)
            {
                int bytesReceived = recv(clientSocket, filebuf, sizeof(filebuf), 0);

                if (bytesReceived <= 0)
                {
                    break;
                }

                fwrite(filebuf, 1, bytesReceived, outfile);
                totalReceivedBytes += bytesReceived;
            }


            fclose(outfile);

            if (fileByteSize < 0)
            {
                printf("File Receive Error: %d\n", WSAGetLastError());
            }
            else
            {
                printf("File transfer complete! File saved as: %s\n", newFileName);
                send(clientSocket, "ACK", 3, 0);
            }

            char file_req[4];
            recv(clientSocket, file_req, 3, 0);
            file_req[3] = '\0';

            FILE* infile;
            char sentfile[1024];

            if (strcmp(file_req, "GET") == 0)
            {
                printf("Enter path of file you would like to send to the client: ");
                fgets(sentfile, 1024, stdin);
                sentfile[strcspn(sentfile, "\n")] = '\0';

                printf("\n\n");

                if (!(infile = fopen(sentfile, "rb"))) {

                    printf("File Error: File or path not valid");
                    return -1;

                }
                else
                {

                    char filebuf[1024];
                    size_t filebytes;

                    while ((filebytes = fread(filebuf, 1, sizeof(filebuf), infile)) > 0)
                    {
                        send(clientSocket, filebuf, filebytes, 0);
                    }

                    fclose(infile);

                    printf("File sent to client.\n\n");
                }




            }

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /********************************************************************************************************************************************************/
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();

        return 0;

    }
}




