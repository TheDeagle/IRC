# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hben-bou <hben-bou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/23 05:15:17 by hben-bou          #+#    #+#              #
#    Updated: 2024/02/05 00:14:24 by hben-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

server = server
client = client

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g -pthread 

S_SRC = main.cpp server.cpp utils.cpp ./commands/MSG.cpp ./commands/NICK.cpp ./commands/QUIT.cpp ./commands/JOIN.cpp ./commands/KICK.cpp ./commands/OPER.cpp ./commands/SAY.cpp ./commands/INVITE.cpp ./commands/WHO.cpp ./commands/TOPIC.cpp ./commands/MODE.cpp ./commands/PASS.cpp ./commands/DCC.cpp ./channels/Channel.cpp client.cpp parse.cpp
S_OBJ = main.o server.o utils.o ./commands/MSG.o ./commands/NICK.o ./commands/QUIT.o ./commands/JOIN.o ./commands/KICK.o ./commands/OPER.o ./commands/SAY.o ./commands/INVITE.o ./commands/WHO.o ./commands/TOPIC.o ./commands/MODE.o ./commands/PASS.o ./commands/DCC.o ./channels/Channel.o client.o parse.o

C_SRC = ./bot/BOT.cpp
C_OBJ = ./bot/BOT.o

all: $(server) #$(client)

client: $(client)

$(server): $(S_OBJ)
	@$(CXX) $(CXXFLAGS) $(S_SRC) -o $(server)

$(client): $(C_OBJ)
	@$(CXX) $(CXXFLAGS) $(C_SRC) -o $(client)

# $(client): $(C_OBJ)
# 	$(CPP) $(CPPFLAGS) $(C_SRC) -o $(client)

clean:
	rm -rf $(S_OBJ) $(C_OBJ)

fclean: clean
	rm -rf $(server) $(client)

re: fclean all
