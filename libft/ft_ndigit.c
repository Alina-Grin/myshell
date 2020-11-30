/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ndigit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:41:38 by szeftyr           #+#    #+#             */
/*   Updated: 2020/10/07 16:20:05 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ndigit(unsigned int nbr)
{
	int	n_digit;

	n_digit = 1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		n_digit++;
	}
	return (n_digit);
}
