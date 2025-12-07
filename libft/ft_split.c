/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:53:21 by gavivas-          #+#    #+#             */
/*   Updated: 2025/10/27 19:48:38 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_copywords(char const *s, char c, int *i)
{
	char	*new;
	int		j;

	while (s[*i] != '\0' && s[*i] == c)
		(*i)++;
	j = *i;
	while (s[j] != '\0' && s[j] != c)
		j++;
	new = ft_substr(s, *i, j - *i);
	if (!new)
		return (NULL);
	*i = j;
	return (new);
}

static void	ft_free(char **new, int count)
{
	while (count >= 0)
	{
		free(new[count]);
		count--;
	}
	free(new);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		count;
	char	**new;

	count = ft_countwords(s, c);
	new = ft_calloc(sizeof(char *), count + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		new[j] = ft_copywords(s, c, &i);
		if (!new[j])
			return (ft_free(new, j - 1), NULL);
		j++;
	}
	return (new);
}
