/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 05:39:05 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/01 20:47:45 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef client_hpp
#define client_hpp

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <vector>


class Client
{
    private:
        std::string nickname;
        std::string username;
        int *fd;
        bool Oper;
        bool Access;
    public:
        Client();
        void setOper(bool state);
        bool getOper(void);
        void setFd(int *fd);
        void setNick(std::string nick);
        void setUser(std::string user);
        void setAccess(bool n);
        int getFd(void) const;
        bool getAccess(void) const;
        std::string getNick(void);
        std::string getUser(void);
};


#endif