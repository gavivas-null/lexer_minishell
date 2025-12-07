/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:53:07 by gavivas-          #+#    #+#             */
/*   Updated: 2025/10/27 19:47:27 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprime(int n)
{
	int	i;
	int	limit;

	if (n <= 1)
		return (0);
	if (n == 2)
		return (1);
	if (n % 2 == 0)
		return (0);
	i = 3;
	limit = ft_sqrt(n);
	while (i <= limit)
	{
		if (n % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}
