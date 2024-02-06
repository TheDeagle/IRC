/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:09:52 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/01/30 11:08:45 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void QUIT(Socket *_socket, Client *client)
{
    std::cout << client->getNick() << " has quited the server" << std::endl;
    close(client->getFd());
    _socket->fds[find_empty_client(_socket)].fd = -1;
    for (int i = 0; i < (int)_socket->clients.size(); i++)
    {
        if (client->getNick() == _socket->clients[i]->getNick())
        {
            _socket->clients.erase(_socket->clients.begin() + i);
            break;
        }
    }
    delete client;
    _socket->BUFFER[0] = '\0';
    client = NULL;
}