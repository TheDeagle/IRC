/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 04:45:59 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/05 22:58:33 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

void NotOperMsg(Socket *_socket, Client *client, std::string channel)
{
    std::string msg;
    msg = ":" + _socket->server_ip + " 482 " + client->getNick() + " " + channel + " :You'r not a channel operator\n";
    sender(client, msg);
}

void NoSuchNickMsg(Socket *_socket, Client *client, std::string name)
{
    std::string msg;
    msg = ":" + _socket->server_ip + " 401 " + client->getNick() + " " + name + " :No such nick\n";
    sender(client, msg);
}

void init_structs(Socket *_socket, char **av)
{
    _socket->port = atoi(av[1]);
    _socket->server_password = av[2];
    _socket->server.sin_family = AF_INET;
    _socket->server.sin_port = htons(_socket->port);
    _socket->server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    _socket->server_ip = inet_ntoa(_socket->server.sin_addr);
    _socket->length = sizeof(_socket->client);
    _socket->OperPass = "123";
    _socket->operators.push_back("mehdi");
    _socket->operators.push_back("haitham");
    _socket->operators.push_back("yassmin");
}

bool init_socket(Socket *_socket)
{
    _socket->Server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket->Server_fd < 0)
    {
        std::cerr << "Error: couldn't create a socket" << std::endl;
        delete _socket;
        _socket = NULL;
        return (1);
    };
    std::cout << "Socket created successfully" << std::endl;
    return (0);
}

bool bind_socket(Socket *_socket)
{
    if (bind(_socket->Server_fd, (struct sockaddr*)&_socket->server, sizeof(_socket->server)) < 0)
    {
        std::cerr << "Error: coulnd't bind socket" << std::endl;
        delete _socket;
        _socket = NULL;
        return (1);
    }
    std::cout << "Socket binded successfully" << std::endl;
    return (0);
}

bool listening(Socket *_socket)
{
    if (listen(_socket->Server_fd, 20) < 0)
    {
        std::cerr << "Error: couldn't listen for connections" << std::endl;
        delete _socket;
        _socket = NULL;
        return (1);
    }
    std::cout << "Server is listening on port " << _socket->port << std::endl;
    return (0);
}

void set_nonblocking(Socket *_socket)
{
    fcntl(_socket->Server_fd, F_SETFL, O_NONBLOCK);
    fcntl(0, F_SETFL, O_NONBLOCK);
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (_socket->fds[i].fd != -1)
            fcntl(_socket->fds[i].fd, F_SETFL, O_NONBLOCK);
    }
}

int find_empty_client(Socket *_socket)
{
    int i;

    for (i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (!_socket->clients[i])
            break;
    }
    return (i);
}

bool check_pass(Socket *_socket, Client *client, int *fd)
{
    std::stringstream data(_socket->BUFFER);
    std::string pass;
    std::stringstream data1(_socket->BUFFER);
    std::string name;

    while (data1 >> name)
    {
        if (name == "NICK")
        {
            data1 >> name;
            break;
        }
    }
    while (data >> pass)
    {
        if (pass == "PASS")
        {
            data >> pass;
            break;
        }
    }
    
    if (pass != _socket->server_password)
    {
        std::string error_msg;
        error_msg = (std::string)"Password incorrect" + (std::string)"\n";
        send(*fd, error_msg.c_str(), error_msg.length(), 0);
        return (1);
    }
    client->setAccess(true);
    return (0);
}

void accept_connections(Socket *_socket)
{
    int empty = find_empty_client(_socket);
    
    int fd = accept(_socket->Server_fd, (struct sockaddr*)&_socket->client, &_socket->length);
    if (fd != -1)
    {
        _socket->BUFFER[0] = '\0';
        _socket->fds[empty].fd = fd;
        _socket->fds[empty].events = POLLIN;
        
        int end = recv(fd, _socket->BUFFER, sizeof(_socket->BUFFER), 0);
        _socket->BUFFER[end] = '\0';
        
        _socket->clients.push_back(new Client);
        _socket->clients.back()->setFd(&_socket->fds[empty].fd);
        _socket->clients.back()->setAccess(false);
        client_info(_socket->BUFFER, _socket->clients[empty], &_socket->fds[empty].fd);
        fcntl(_socket->fds[empty].fd, F_SETFL, O_NONBLOCK);
        check_pass(_socket, _socket->clients[empty], &fd);
        std::cout << "A client connected" << std::endl;
    }
}

bool polling(Socket *_socket)
{
    if (poll(_socket->fds, (int)_socket->clients.size() + 1, 100) == -1)
    {
        std::cerr << "Error: poll error" << std::endl;
        return (1);
    }
    return (0);
}

void receiving(Socket *_socket)
{
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        _socket->BUFFER[0] = '\0';
        if (_socket->clients[i] && _socket->clients[i]->getFd() != -1)
        {
            int end = recv(_socket->fds[i].fd, _socket->BUFFER, sizeof(_socket->BUFFER), 0);
            _socket->BUFFER[end] = '\n';
            _socket->BUFFER[end + 1] = '\0';
            commands(_socket, _socket->clients[i], _socket->BUFFER);
        }
    }
}

void commands(Socket *_socket, Client *client, std::string message)
{
    int trigger = 0;
    std::stringstream data(message);
    if (sstream_length(message) <= 3)
        trigger = 1;
    std::string command;
    std::string after_command;

    data >> command;
    data >> after_command;
    

    if (command == "NICK")
        NICK(client, message);
    else if (command == "PRIVMSG" && after_command[0] == '#')
        SAY(_socket, client, message);
    else if (command == "PASS")
        PASS(_socket, client);
    if (client->getAccess())
    {
        if (command == "PRIVMSG")
            MSG(_socket, client, message);
        else if (command == "JOIN")
            JOIN(_socket, client, message);
        else if (command == "QUIT")
            QUIT(_socket, client);
        else if (command == "INVITE")
            INVITE(_socket, client, message);
        else if (command == "OPER")
            OPER(_socket, client, message);
        else if (command == "TOPIC")
            TOPIC(_socket, client);
        else if (command == "MODE")
            MODE(_socket, client);
        else if (command == "DCC")
            DCC(_socket, client);
        else if (command == "KICK")
        {
            if (!trigger)
                KICK(_socket, client, message);
            else
                KICK2(_socket, client, message);
        }
    }
    if (_socket->BUFFER[0])
        std::cout << _socket->BUFFER << std::endl;
    _socket->BUFFER[0] = '\0';
}


std::string names(Channel *channel)
{
    std::string ret;
    std::vector<std::string> names;

    for (int i = 0; i < (int)channel->clients.size(); i++)
    {
        if (channel->clients[i]->getOper())
            names.push_back("@" + channel->clients[i]->getNick());
        else
            names.push_back(channel->clients[i]->getNick());
    }

    ret = join_strings(names);
    return (ret);
}

void list_names(Channel *channel)
{
    std::string msg;

    for (int k = 0; k < (int)channel->clients.size(); k++)
    {
        msg = ":" + channel->server_ip + " 353 " + channel->clients[k]->getNick() + " @ " + channel->getName() + " :" + names(channel) + "\n";
        send(channel->clients[k]->getFd(), msg.c_str(), msg.length(), 0);
    }
}

int sstream_length(std::string str)
{
    int i = 0;
    std::stringstream data(str);
    std::string info;

    while (data >> info)
        i++;
    return (i);
}