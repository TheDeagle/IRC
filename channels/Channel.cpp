/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 19:58:32 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/04 19:44:07 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name)
{
    setName(name);
    setInvite(false);
    setCtopic(true);
    setCpass(false);
    setClimit(false);
    UserIncrement();
    users = 0;
}

std::string const &Channel::getName(void) const
{
    return (Channel_name);
}

std::string const &Channel::getTopic(void) const
{
    return (Channel_topic);
}

std::string const &Channel::getPass(void) const
{
    return (password);
}

void Channel::setName(std::string const &Name)
{
    Channel_name = Name;
}

void Channel::setTopic(std::string const &Topic)
{
    Channel_topic = Topic;
}

void Channel::setPass(std::string const &password)
{
    this->password = password;
}

void Channel::addClient(Client *client)
{
    clients.push_back(client);
}

void Channel::removeClient(Client *client)
{
    std::vector<Client *>::iterator itr;

    itr = clients.begin();
    for (int i = 0; i < (int)clients.size(); i++)
    {
        if (clients[i]->getNick() == client->getNick())
        {
            clients.erase(itr);
            return ;
        }
        itr++;
    }
}

void Channel::setInvite(bool n)
{
    InviteOnly = n;
}

void Channel::setCtopic(bool n)
{
    Ctopic = n;
}


void Channel::setCpass(bool n)
{
    Cpass = n;
}

bool Channel::getInvite(void) const
{
    return (InviteOnly);
}

bool Channel::getCpass(void) const
{
    return (Cpass);
}

bool Channel::getCtopic(void) const
{
    return (Ctopic);
}

unsigned int Channel::getChannelLimit(void) const
{
    return (Channel_limit);    
}

unsigned int Channel::getUsers(void) const
{
    return (users);
}

void Channel::setChannelLimit(unsigned int n)
{
    Channel_limit = n;
}

bool Channel::getClimit(void) const
{
    return (Climit);    
}

void Channel::setClimit(bool n)
{
    Climit = n;
}

void Channel::UserIncrement(void)
{
    users++;
}

void Channel::UserDecrement(void)
{
    users--;
}

void Channel::AddToInvited(std::string nick)
{
    ClientsInvited.push_back(nick);
}