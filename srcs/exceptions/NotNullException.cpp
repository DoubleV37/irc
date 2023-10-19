/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotNullException.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gazzopar <gazzopar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:21:32 by gazzopar          #+#    #+#             */
/*   Updated: 2023/10/19 15:47:02 by gazzopar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NotNullException.hpp"

const char* NotNullException::what() const throw() {
    
    return "Cannot be <null>";
}
