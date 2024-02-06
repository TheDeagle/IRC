/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:44:23 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/05 00:20:32 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void PASS(Socket *_socket, Client *client)
{
    std::stringstream data(_socket->BUFFER);
    std::string pass;
    std::stringstream data1(_socket->BUFFER);
    std::string name;

    while (data1 >> name)
    {
        if (name == "NICK")
        {
            data1 >> name;
            break;
        }
    }
    while (data >> pass)
    {
        if (pass == "PASS")
        {
            data >> pass;
            break;
        }
    }
    
    if (pass != _socket->server_password)
    {
        std::string error_msg;

        error_msg = (std::string)"Password incorrect" + (std::string)"\n";
        sender(client, error_msg);
        return;
    }
    client->setAccess(true);
    return;
}