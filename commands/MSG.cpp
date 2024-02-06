/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSG.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 21:12:09 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/05 22:54:04 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void parse(std::string name, std::string &string)
{
    std::stringstream Data(string);
    std::string tmp;
    
    Data >> tmp;
    string = tmp;
    Data >> tmp;
    string += " " + tmp;
    string += " :" + name + ":";
    while (Data >> tmp)
        string += " " + tmp;
    string += "\n";
    // std::string parse;
    // int i = 0;
    // while (_socket->clients[i])
    //     i++;
    // while (getline(Data, parse, ' '))
    // {
    //     if (parse == "NICK")
    //     {
    //         getline(Data, parse, ' ');
    //         _socket->clients[i]->setNick(parse);
    //         _socket->clients[i]->setFd(fd);
    //         return ;
    //     }

}


void MSG_HELPER(Socket *_socket, std::string message)
{
    std::stringstream data(message);
    std::string info;
    while (getline(data, info, ' '))
        _socket->message_info.push_back(info);
    std::vector<std::string>::iterator itr;
}

void MSG(Socket *_socket, Client *client, std::string message)
{
    MSG_HELPER(_socket, message);
    int trigger = 0;
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (_socket->clients[i] && _socket->clients[i]->getNick() == _socket->message_info[1])
        {
            std::string msg = ":" + client->getNick() + "! " + message;
            std::cout << client->getNick() << " has sent a private message to " << _socket->clients[i]->getNick() << std::endl;
            send(_socket->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
            trigger = 1;
            break;
       }
    }
    if (trigger)
    {
        std::string NOT_FOUND = "PRIVMSG :user is not found!\n";
        std::cout << client->getNick() << " could't find user " << _socket->message_info[1] << std::endl;
        send(client->getFd(), NOT_FOUND.c_str(), NOT_FOUND.length(), 0);
    }
    _socket->message_info.clear();
}