/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 21:06:12 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/01 12:03:14 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

std::string kick_helper(std::string str)
{
    std::string ret;
    
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ':')
            ret += str[i];
    }
    return (ret);
}


void KICK(Socket *_socket, Client *client, std::string message)
{
    int trigger = 0;
    std::stringstream data(message);
    std::string channel;
    std::string name;
    std::string reason;
    std::string info;
    std::string msg;

    data >> channel;
    data >> channel;
    data >> channel;
    data >> name;
    name = kick_helper(name);
    while (data >> info)
        reason += info + " ";
    
    if (client->getOper())
    {
        for (int i = 0; i < (int)_socket->channels.size(); i++)
        {
            if (_socket->channels[i]->getName() == channel)
            {
                for (int k = 0; k < (int)_socket->channels[i]->clients.size(); k++)
                {
                    if (name == _socket->channels[i]->clients[k]->getNick())
                    {
                        msg = ":" + client->getNick() + "! KICK " + channel + " " + name + " :" + reason + "\n";
                        sender(_socket->channels[i]->clients[k], msg);
                        _socket->channels[i]->clients.erase(_socket->channels[i]->clients.begin() + k);
                        list_names(_socket->channels[i]);
                        trigger = 1;
                        break; 
                    }
                }
                if (!trigger)
                {
                    NoSuchNickMsg(_socket, client, name);
                    list_names(_socket->channels[i]);
                    return;
                }
            }
        }
    }
    else
        NotOperMsg(_socket, client, channel);
}

void KICK2(Socket *_socket, Client *client, std::string message)
{
    int trigger = 0;
    std::stringstream data(message);
    std::string name;
    std::string channel;
    std::string msg;
    
    data >> channel;
    data >> channel;
    data >> name;

    if (client->getOper())
    {
        for (int i = 0; i < (int)_socket->channels.size(); i++)
        {
            if (_socket->channels[i]->getName() == channel)
            {
                for (int k = 0; k < (int)_socket->channels[i]->clients.size(); k++)
                {
                    if (_socket->channels[i]->clients[k]->getNick() == name)
                    {
                        msg = ":" + client->getNick() + "! KICK " + channel + " " + name + " " + client->getNick() + "\n";
                        sender(_socket->channels[i]->clients[k], msg);
                        _socket->channels[i]->clients.erase(_socket->channels[i]->clients.begin() + k);
                        trigger = 1;
                        list_names(_socket->channels[i]);
                        return;
                    }
                }
                if (!trigger)
                {
                    NoSuchNickMsg(_socket, client, name);
                    list_names(_socket->channels[i]);
                    return;
                }
            }
        }
    }
    else
        NotOperMsg(_socket, client, channel);
}