/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalcort <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:07:27 by sbalcort          #+#    #+#             */
/*   Updated: 2017/11/02 14:31:28 by sbalcort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(const char *s)
{
	if ((s[0] >= 9 && s[0] <= 13) || s[0] == 32)
		return (1);
	return (0);
}
