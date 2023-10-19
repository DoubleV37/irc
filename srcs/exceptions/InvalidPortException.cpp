/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InvalidPortException.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:32 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 15:47:00 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InvalidPortException.hpp"

const char* InvalidPortException::what() const throw() {
    
    return "Invalid Port";
}