/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeddi <aeddi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:50:23 by aeddi             #+#    #+#             */
/*   Updated: 2013/11/27 15:42:31 by aeddi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*temp;

	temp = ft_strdup((char *)s2);
	return (ft_strncpy((char *)s1, (const char *)temp, n));
}
