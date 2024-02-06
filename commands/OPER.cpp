/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:10:49 by hben-bou          #+#    #+#             */
/*   Updated: 2024/01/30 09:47:05 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"
#include <cstring>

void OPER(Socket *_socket, Client *client, std::string message)
{
    int trigger = 0;
    std::stringstream data(message);
    std::string name;
    std::string password;
    std::string error;
    
    data >> name;
    data >> name;
    data >> password;
    if (password == _socket->OperPass)
    {
        for (int i = 0; i < (int)_socket->operators.size(); i++)
        {
            if (name == _socket->operators[i])
            {
                client->setOper(true);
                std::string msg = ":" + _socket->server_ip + " 381 " + client->getNick() + " :You are now an IRC operator\n";
                send(client->getFd(), msg.c_str(), msg.length(), 0);
                trigger = 1;
                break;
            }
        }
        if (!trigger)
        {
            error = ":" + _socket->server_ip + " 481 " + client->getNick() + " :Permission Denied - You are not an IRC operator\n";
            send(client->getFd(), error.c_str(), error.length(), 0);
            return;
        }
    }
    else
    {
        error = ":" + _socket->server_ip + " 464 " + client->getNick() + " :Password incorrect\n";
        send(client->getFd(), error.c_str(), error.length(), 0);
    }
}