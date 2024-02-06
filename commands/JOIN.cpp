/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 04:48:34 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/05 00:34:28 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

bool CheckIfInvited(Channel *channel, std::string name)
{
    for (int i = 0; i < (int)channel->ClientsInvited.size(); i++)
    {
        if (name == channel->ClientsInvited[i])
            return (1);    
    }
    return (0);
}

void CreateNewChannel(Socket *_socket, Client *client, std::string channel_name)
{
    Channel *channel = new Channel(channel_name);
    std::string msg;

    channel->addClient(client);
    channel->UserIncrement();
    channel->server_ip = _socket->server_ip;
    client->setOper(true);
    _socket->channels.push_back(channel);
    msg = ":" + client->getNick() + "! " + _socket->BUFFER;
    send(client->getFd(), msg.c_str(), msg.length(), 0);
    std::cout << client->getNick() << " has joined " << channel_name << std::endl;
    list_names(channel);
}

void JOIN(Socket *_socket, Client *client, std::string message)
{
    std::stringstream data(message);
    std::string channel_name;
    std::string msg;
    std::string pass;

    data >> channel_name;
    data >> channel_name;
    data >> pass;

    for (int i = 0; i < (int)_socket->channels.size(); i++)
    {
        if (channel_name ==_socket->channels[i]->getName())
        {
            if (!_socket->channels[i]->getInvite() || CheckIfInvited(_socket->channels[i], client->getNick()))
            {
                if (!_socket->channels[i]->getCpass() || _socket->channels[i]->getPass() == pass)
                {
                    if (!_socket->channels[i]->getClimit() || _socket->channels[i]->getUsers() < _socket->channels[i]->getChannelLimit())
                    {
                        _socket->channels[i]->UserIncrement();
                        _socket->channels[i]->addClient(client);
                        msg = ":" + client->getNick() + "! " + message;
                        std::cout << client->getNick() << " has joined " << channel_name << std::endl;
                        sender(client, msg);
                        list_names(_socket->channels[i]);
                    }
                    else
                    {
                        msg = ":" + _socket->server_ip + " 471 " + client->getNick() + " " + channel_name + " :Cannot join channel (User limit reached)\n";
                        sender(client, msg);
                        return;
                    }
                }
                else
                {
                    msg = ":" + _socket->server_ip + " 475 " + client->getNick() + " " + channel_name + " " + ":Cannot join channel (+k)\n";
                    sender(client, msg);
                    return;
                }
            }
            else
            {
                msg = ":" + _socket->server_ip + " 473 " + client->getNick() + " " + channel_name + " " + ":Cannot join channel (+i)\n";
                sender(client, msg);
            }
            return;
        }
    }
    CreateNewChannel(_socket, client, channel_name);
}