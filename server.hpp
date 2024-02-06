/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 05:09:11 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/04 20:39:26 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef server_hpp
#define server_hpp

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cerrno>
#include <climits>
#include <sstream>
#include "client.hpp"
#include "./channels/Channel.hpp"
#include "./bot/BOT.hpp"
#include <cstring>

typedef struct SocketsData
{

//-----------CHANNELS------------//
    std::vector<Channel *> channels;
//-------------------------------//

//---------BANNED_USERS--------//
    std::vector<std::string> banned;
//-----------------------------//

//---------MESSAGES_INFO-------//
    std::vector<std::string> message_info;
//-----------------------------//

//---------OPERATORS-----------//
    std::vector<std::string> operators;
//-----------------------------//

    Bot *server_bot;

    std::string server_password;
    std::string OperPass;
    std::string server_ip;
    int port;
    int Server_fd;
    int client_fd;
    socklen_t length;
    char BUFFER[2048];
    struct pollfd fds[INT_MAX];
    struct sockaddr_in server;
    struct sockaddr_in client;
    std::vector<Client *> clients;
} Socket;

void Broadcast(std::string message, Socket *_socket);
void init_structs(Socket *_socket, char **av);
bool init_socket(Socket *_socket);
bool bind_socket(Socket *_socket);
bool listening(Socket *_socket);
void set_nonblocking(Socket *_socket);
void accept_connections(Socket *_socket);
bool polling(Socket *_socket);
void receiving(Socket *_socket);
int find_empty_client(Socket *_socket);
std::string join_strings(std::vector<std::string> &strings);
void sender(Client *client, std::string message);
void NotOperMsg(Socket *_socket, Client *client, std::string channel);
void NoSuchNickMsg(Socket *_socket, Client *client, std::string name);
void list_names(Channel *channel);
std::string names(Channel *channel);
int sstream_length(std::string data);
int ChannelIndex(Socket *_socket, std::string channel);

//--COMMANDS--
void PASS(Socket *_socket, Client *client);
void MSG(Socket *_socket, Client *client, std::string message);
void NICK(Client *Client, std::string message);
void QUIT(Socket *_socket, Client *client);
void JOIN(Socket *_socket, Client *client, std::string message);
void KICK(Socket *_socket, Client *client, std::string message);
void KICK2(Socket *_socket, Client *client, std::string message);
void OPER(Socket *_socket, Client *client, std::string message);
void SAY(Socket *_socket, Client *client, std::string message);
void INVITE(Socket *_socket, Client *client, std::string message);
void WHO(Socket *_socket, Client *client, std::string message);
void TOPIC(Socket *_socket, Client *client);
void MODE(Socket *_socket, Client *client);
void DCC(Socket *_socket, Client *client);
void commands(Socket *_socket, Client *client, std::string message);
//------------


//--BOT--
void init_bot(Socket *_socket);
void BOT(Socket *_socket);
//-------

//--parsing--
void client_info(std::string message_info, Client *client, int *fd);
//-----------

#endif