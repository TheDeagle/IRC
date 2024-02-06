/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:25:03 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/05 19:47:50 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <stdio.h>

void client_info(std::string message_info, Client *client, int *fd)
{
    std::vector<std::string> info;
    std::vector<std::string>::iterator itr;
    std::stringstream data(message_info);
    std::string pusher;
    while (data >> pusher)
        info.push_back(pusher);
    for (itr = info.begin(); itr != info.end(); itr++)
    {
        if (*itr == "NICK")
            client->setNick(*(itr + 1));
        if (*itr == "USER")
            client->setUser(*(itr + 1));
    }
    client->setFd(fd);
}

std::string join_strings(std::vector<std::string> &strings)
{
    std::string ret;
    
    for (int i = 0; i < (int)strings.size(); i++)
    {
        if (i != (int)strings.size() - 1)
            ret += strings[i] + " ";
        else
            ret += strings[i];
    }
    return ret;
}


void sender(Client *client, std::string message)
{
    send(client->getFd(), message.c_str(), message.length(), 0);
}