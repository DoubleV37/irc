/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InvalidPasswordException.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:32 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 15:47:04 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InvalidPasswordException.hpp"

const char* InvalidPasswordException::what() const throw() {
    
    return "Invalid Password";
}
