# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 14:50:08 by gazzopar          #+#    #+#              #
#    Updated: 2023/10/19 15:46:09 by gazzopar         ###   ########.fr        #
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
				srcs/Command.cpp \
				srcs/exceptions/InvalidPortException.cpp \
				srcs/exceptions/InvalidPasswordException.cpp \
				srcs/exceptions/NotNullException.cpp
				
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
