/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dquote_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:44:00 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/07 19:03:59 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void	escapes_dquote(char next, t_lexer *lx, size_t *i)
{
	if (!next)
	{
		if (!lexer_add_char(lx, '\\'))
			return ;
		(*i)++;
		return ;
	}
	if (next == '"' || next == '\\' || next == '$')
	{
		if (!lexer_add_char(lx, next))
			return ;
		*i += 2;
		return ;
	}
	if (!lexer_add_char(lx, '\\'))
		return ;
	(*i)++;
}

void	handle_in_dquote(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	char	c;

	if (!line[*i])
	{
		lx->error = 1;
		return ;
	}
	c = line[*i];
	if (c == '"')
	{
		*state = NORMAL;
		(*i)++;
		return ;
	}
	if (c == '\\')
	{
		escapes_dquote(line[*i + 1], lx, i);
		return ;
	}
	if (!lexer_add_char(lx, c))
		return ;
	(*i)++;
}
