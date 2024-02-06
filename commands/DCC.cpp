/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DCC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:02:09 by hben-bou          #+#    #+#             */
/*   Updated: 2024/02/02 21:08:10 by hben-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void DCC(Socket *_socket, Client *client)
{
    (void)_socket;
    (void)client;
    std::cout <<  _socket->BUFFER << std::endl;
    
}