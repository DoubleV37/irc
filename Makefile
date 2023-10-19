# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 14:50:08 by gazzopar          #+#    #+#              #
#    Updated: 2023/10/19 17:11:56 by gazzopar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= ircserv

#-----------------------------------------------------------------------------#
#									INGREDIENTS								  #
#-----------------------------------------------------------------------------#

SRC			:=	srcs/main.cpp \
				srcs/User.cpp \
				srcs/Server.cpp \
				srcs/Channel.cpp \
				srcs/ACommand.cpp \
				srcs/exceptions/InvalidPortException.cpp \
				srcs/exceptions/InvalidPasswordException.cpp \
				srcs/exceptions/NotNullException.cpp \
				srcs/commands/Invite.cpp \
				srcs/commands/Kick.cpp \
				srcs/commands/Mode.cpp \
				srcs/commands/Topic.cpp \
				srcs/commands/Join.cpp		
				
OBJ			:= $(SRC:.cpp=.o)

CXXFLAGS	:= -Wall -Wextra -Werror -ggdb3 -std=c++98

RM			:= rm -rf

CXX			:= c++

#-----------------------------------------------------------------------------#
#									RECIPES									  #
#-----------------------------------------------------------------------------#

%.o: %.cpp
			$(CXX) $(CXXFLAGS) -c $< -o $@ $(FLAGS)

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:		
			$(RM) $(OBJ)
			@echo "Suppression des fichiers .o"

fclean:		
			$(RM) $(OBJ) $(NAME)
			@echo "Supression des fichiers .o et .a"

re:			fclean all

.PHONY:		all clean fclean re
