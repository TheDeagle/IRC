/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:21:53 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/01 10:47:01 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void INVITE(Socket *_socket, Client *client, std::string message)
{
    std::stringstream info(message);
    std::string channel;
    info >> channel;
    info >> channel;
    info >> channel;
    
    std::string msg;
    if (!client->getOper())
    {
        NotOperMsg(_socket, client, channel);
        return;
    }
    std::stringstream data(message);
    std::string client_name;
    
    data >> client_name;
    data >> client_name;
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (_socket->clients[i]->getNick() == client_name)
        {
            for (int i = 0; i < (int)_socket->channels.size(); i++)
            {
                if (_socket->channels[i]->getName() == channel)
                {
                    _socket->channels[i]->AddToInvited(client_name);
                    break;
                }
            }
            msg = ":" + client->getNick() + "! " + message;
            send(_socket->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
            break;
        }
    }
}