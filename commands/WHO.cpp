/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 05:00:46 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/01/12 05:46:23 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void WHO(Socket *_socket, Client *client, std::string message)
{
    (void)_socket;
    (void)message;
    (void)client;
    // std::string msg = ":127.0.0.1 352 your-nickname #programming username 127.0.0.1 server nick H :1 RealName\n\n";
    // std::cout << msg << std::endl;
    // send(client->getFd(), msg.c_str(), msg.length(), 0);
}