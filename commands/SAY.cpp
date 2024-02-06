/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SAY.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:37:57 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/05 22:54:37 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void SAY(Socket *_socket, Client *client, std::string message)
{
    std::string sender = ":" + client->getNick() + "! ";
    std::string msg;
    
    std::cout << "hada msg: " << message << std::endl;
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (_socket->clients[i] && _socket->clients[i]->getNick() != client->getNick())
        {
            msg = sender + message;
            send(_socket->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
        }
    }
}