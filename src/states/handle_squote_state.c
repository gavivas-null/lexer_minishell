/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_squote_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:41:04 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/01 19:15:32 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	handle_in_squote(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	if (!line[*i])
	{
		lx->error = 1;
		return ;
	}
	if (line[*i] == '\'')
	{
		*state = NORMAL;
		(*i)++;
		return ;
	}
	lexer_add_char(lx, line[*i]);
	(*i)++;
}
