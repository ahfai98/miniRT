/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjien-ji <tjien-ji@42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 02:48:47 by tjien-ji          #+#    #+#             */
/*   Updated: 2024/09/13 03:23:25 by tjien-ji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

unsigned int	ft_swap_endianness(unsigned int value)
{
	int	ret_val;

	ret_val = ((value >> 24) & 0xff)
		| ((value >> 8) & 0xff00)
		| ((value << 8) & 0xff0000)
		| ((value << 24) & 0xff000000);
	return (ret_val);
}
