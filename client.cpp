/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 05:40:06 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/01 20:50:23 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.hpp"

Client::Client()
{
    Oper = false;
}

void Client::setFd(int *fd)
{
    if (fd)
        this->fd = fd;
}

void Client::setNick(std::string nick)
{
    this->nickname = nick;
}

void Client::setUser(std::string user)
{
    this->username = user;
}

int Client::getFd(void) const
{
    return (*this->fd);
}

std::string Client::getNick(void)
{
    return (this->nickname);
}

std::string Client::getUser(void)
{
    return (this->username);
}

bool Client::getOper(void)
{
    return (Oper);
}

void Client::setOper(bool state)
{
    Oper = state;
}

bool Client::getAccess(void) const
{
    return (Access);
}

void Client::setAccess(bool n)
{
    Access = n;
}

// int main(int ac, char **av)
// {
//     if (ac < 3 || ac > 4)
//     {
//         std::cerr << "Error: No ip or no port was specified" << std::endl;
//         return (1);
//     }
//     int client_fd;
//     struct sockaddr_in server_addr;
//     struct pollfd fds[1];

//     fds[0].fd = 0;
//     fds[0].events = POLLIN;
//     server_addr.sin_family = PF_INET;
//     server_addr.sin_port = htons(atoi(av[2]));
//     server_addr.sin_addr.s_addr = inet_addr(av[1]);
    
//     client_fd = socket(PF_INET, SOCK_STREAM, 0);
//     if (client_fd < 0)
//     {
//         std::cerr << "Error: couldn't create a socket" << std::endl;
//         return (1);
//     }
//     std::cout << "Client socket has been created successfuly" << std::endl;
//     if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
//     {
//         std::cerr << "Error: coulnd't connect to server";
//         return (1);
//     }
//     while (1)
//     {
//         if (poll(fds, 1, 100) == -1)
//         {
//             std::cerr << "Error: poll error" << std::endl;
//             return (1);
//         }
//         char BUFFER[2048];
//         BUFFER[0] = '\0';
//         fcntl(0, F_SETFL, O_NONBLOCK);
//         fcntl(client_fd, F_SETFL, O_NONBLOCK);
//         int length = read(0, BUFFER, sizeof(BUFFER));
//         BUFFER[length] = '\0';
//         send(client_fd, BUFFER, sizeof(BUFFER), 0);
//         BUFFER[0] = '\0';
//         recv(client_fd, BUFFER, sizeof(BUFFER), 0);
//         if (BUFFER[0] != '\0')
//             std::cout << BUFFER;
//         BUFFER[0] = '\0';
//     }
//     close(client_fd);
// }