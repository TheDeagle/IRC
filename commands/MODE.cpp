/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:35:19 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/01 12:18:44 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void InviteOnlyChannel(Channel *channel, Client *client, int mode)
{
    std::string msg; 
    
    if (mode == 0)
    {
        channel->setInvite(true);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " +i \n";
    }
    else
    {
        channel->setInvite(false);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " -i \n";
    }
    for (int i = 0; i < (int)channel->clients.size(); i++)
        send(channel->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
}

void setTopic(Channel *channel, Client *client, int mode)
{
    std::string msg; 
    
    if (mode == 0)
    {
        channel->setCtopic(true);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " +t \n";
    }
    else
    {
        channel->setCtopic(false);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " -t \n";
    }
    for (int i = 0; i < (int)channel->clients.size(); i++)
        send(channel->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
}

void setChannelPassword(Channel *channel, Client *client, int mode, std::string pass)
{
    std::string msg; 
    
    if (mode == 0)
    {
        channel->setCpass(true);
        channel->setPass(pass);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " +k " + pass + "\n";
    }
    else
    {
        channel->setCpass(false);
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " -k\n";
    }
    for (int i = 0; i < (int)channel->clients.size(); i++)
        send(channel->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
}

void setChannelOperator(Channel *channel, Client *client, std::string message, int mode)
{
    std::stringstream data(message);
    std::string msg;
    std::string userName;

    data >> userName;
    data >> userName;
    data >> userName;
    data >> userName;

    if (mode == 0)
    {
        for (int i = 0; i < (int)channel->clients.size(); i++)
        {
            if (userName == channel->clients[i]->getNick())
            {
                channel->clients[i]->setOper(true);
                break;
            }
        }
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " +o " + userName + "\n";
    }
    else
    {
        for (int i = 0; i < (int)channel->clients.size(); i++)
        {
            if (userName == channel->clients[i]->getNick())
            {
                channel->clients[i]->setOper(false);
                break;
            }
        }
        msg = ":" + client->getNick() + " MODE " + channel->getName() + " -o " + userName + "\n";
    }
    for (int i = 0; i < (int)channel->clients.size(); i++)
        send(channel->clients[i]->getFd(), msg.c_str(), msg.length(), 0);
}

void setLimit(Channel *channel, Client *client, std::string message)
{
    int limit;
    std::stringstream data(message);
    std::string info;
    std::string msg;
    std::string mode;
    
    data >> info;
    data >> info;
    data >> mode;
    data >> info;

    limit = atoi(info.c_str());
    if (mode == "l" || mode == "+l")
    {
        msg = ":" + client->getNick() + " " + message;
        channel->setClimit(true);
        channel->setChannelLimit(limit);  
    }
    else
    {
        channel->setClimit(false);
        channel->setChannelLimit(INT_MAX);
    }
    for (int i = 0; i < (int)channel->clients.size(); i++)
        sender(channel->clients[i], msg);
}

void MODE(Socket *_socket, Client *client)
{
    std::stringstream data(_socket->BUFFER);
    std::string channel;
    std::string mode;
    std::string pass;

    data >> channel;
    data >> channel;
    data >> mode;
    data >> pass;
    
    if (client->getOper())
    {
        for (int i = 0; i < (int)_socket->channels.size(); i++)
        {
            if (channel == _socket->channels[i]->getName())
            {
                if (mode == "i" || mode == "+i")
                    InviteOnlyChannel(_socket->channels[i], client, 0);
                else if (mode == "-i")
                    InviteOnlyChannel(_socket->channels[i], client, 1);
                else if (mode == "t" || mode == "+t")
                    setTopic(_socket->channels[i], client, 0);
                else if (mode == "-t")
                    setTopic(_socket->channels[i], client, 1);
                else if (mode == "k" || mode == "+k")
                    setChannelPassword(_socket->channels[i], client, 0, pass);
                else if (mode == "-k")
                    setChannelPassword(_socket->channels[i], client, 1, pass);
                else if (mode == "l" || mode == "+l" || mode == "-l")
                    setLimit(_socket->channels[i], client, _socket->BUFFER);
                else if (mode == "o" || mode == "+o")
                    setChannelOperator(_socket->channels[i], client, _socket->BUFFER, 0);
                else if (mode == "-o")
                    setChannelOperator(_socket->channels[i], client, _socket->BUFFER, 1);
                list_names(_socket->channels[i]);
                break;
            }
        }
    }
    else
        NotOperMsg(_socket, client, channel);
}