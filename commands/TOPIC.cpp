/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:24:57 by hben-bou          #+#    #+#             */
/*   Updated: 2024/01/30 12:00:12 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

int ChannelIndex(Socket *_socket, std::string channel)
{
    for (int i = 0; i < (int)_socket->channels.size(); i++)
    {
        if (channel == _socket->channels[i]->getName())
            return (i);
    }
    return (-1);
}

void TOPIC(Socket *_socket, Client *client)
{
    int channel_index;
    std::stringstream data(_socket->BUFFER);
    std::string channel;
    std::string topic;
        
    data >> topic;
    data >> channel;
    data >> topic;
    
    if ((channel_index = ChannelIndex(_socket, channel)) == -1)
        return;
    if (client->getOper() || !_socket->channels[channel_index]->getCtopic())
    {
        std::string msg;
        _socket->channels[channel_index]->setTopic(topic);
        msg = ":" + client->getNick() + "! " + _socket->BUFFER + "\n";
        for (int k = 0; k < (int)_socket->channels[ChannelIndex(_socket, channel)]->clients.size(); k++)
            sender(_socket->channels[ChannelIndex(_socket, channel)]->clients[k], msg);
    }
    else
        NotOperMsg(_socket, client, channel);
}