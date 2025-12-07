/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:51:29 by gavivas-          #+#    #+#             */
/*   Updated: 2025/10/27 19:47:08 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	totalsize;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	totalsize = count * size;
	arr = (void *)malloc(totalsize);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, totalsize);
	return (arr);
}
