/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel->hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:41:53 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/01/14 08:42:48 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef channels_hpp
#define channels_hpp

#include <iostream>
#include <vector>
#include "../client.hpp"

class Channel
{
    private:
        bool InviteOnly;
        bool Ctopic;
        bool Cpass;
        bool Climit;
        unsigned int Channel_limit;
        unsigned int users;
        std::string Channel_name;
        std::string Channel_topic;
        std::string password;
    public:
        Channel(std::string name);
        std::string server_ip;
        std::vector<Client *> clients;
        std::vector<std::string> ClientsInvited;
        std::string const &getName(void) const;
        std::string const &getTopic(void) const;
        std::string const &getPass(void) const;
        unsigned int getUsers(void) const;
        unsigned int getChannelLimit(void) const;
        bool getInvite(void) const;
        bool getCpass(void) const;
        bool getCtopic(void) const;
        bool getClimit(void) const;
        void setName(std::string const &Name);
        void setTopic(std::string const &Topic);
        void addClient(Client *client);
        void removeClient(Client *client);
        void setInvite(bool n);
        void setCpass(bool n);
        void setCtopic(bool n);
        void setClimit(bool n);
        void setChannelLimit(unsigned int n);
        void setPass(std::string const &password);
        void AddToInvited(std::string nick);
        void UserIncrement(void);
        void UserDecrement(void);
};


#endif