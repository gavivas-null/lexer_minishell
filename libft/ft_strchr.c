/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:53:25 by gavivas-          #+#    #+#             */
/*   Updated: 2025/10/27 19:48:45 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				a;
	unsigned char	l;

	l = c;
	a = 0;
	while (s[a] != '\0' && s[a] != l)
	{
		a++;
	}
	if (s[a] == l)
		return ((char *)&s[a]);
	return (NULL);
}
