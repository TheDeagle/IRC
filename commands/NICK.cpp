/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheDeagle <castlehaitham@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:26:29 by TheDeagle         #+#    #+#             */
/*   Updated: 2024/01/07 06:21:06 by TheDeagle        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server.hpp"

void NICK(Client *Client, std::string message)
{
    std::stringstream data(message);
    std::string NewNick;
    std::string OldNick;

    OldNick = Client->getNick();
    data >> NewNick;
    data >> NewNick;

    Client->setNick(NewNick);
    std::cout << OldNick << " changed his/her nick to > " << Client->getNick() << std::endl;
}