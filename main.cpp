/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 04:49:43 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/02/04 20:53:06 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include <cstring>
#include <fstream>
#include <sstream>

int main(int ac, char **av)
{
    if (ac < 3 || ac > 4)
    {
        std::cerr << "Error: bad arguments" << std::endl;
        return (1);
    }
    Socket *_socket = new Socket;
    init_structs(_socket, av);
    if (init_socket(_socket) || bind_socket(_socket) || listening(_socket))
        return (1); 
    _socket->client_fd = -1;
    while (1)
    {
        // BOT(_socket);
        set_nonblocking(_socket);
        if (polling(_socket))
            return (1);
        accept_connections(_socket);
        receiving(_socket);
    }
}
