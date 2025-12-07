/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:27:24 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/07 18:51:47 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void	normal_operator(t_lexer *lx, const char *line, size_t *i)
{
	t_token_type	type;
	t_token			*tok;

	if (!lexer_end_word(lx))
		return ;
	type = identify_operator(&line[*i]);
	tok = token_new(type);
	if (!tok)
	{
		lx->error = 1;
		return ;
	}
	if (!lexer_add_token(lx, tok))
	{
		free(tok);
		lx->error = 1;
		return ;
	}
	*i += operator_length(&line[*i]);
}

static void	normal_in_squote(int *state, size_t *i)
{
	*state = IN_SQUOTE;
	(*i)++;
}

static void	normal_in_dquote(int *state, size_t *i)
{
	*state = IN_DQUOTE;
	(*i)++;
}

void	handle_normal(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	if (is_operator_char(line[*i]))
		normal_operator(lx, line, i);
	else if (line[*i] == '\'')
		normal_in_squote(state, i);
	else if (line[*i] == '"')
		normal_in_dquote(state, i);
	else if (line[*i] == ' ' || line[*i] == '\t')
	{
		if (!lexer_end_word(lx))
			return ;
		(*i)++;
	}
	else
	{
		if (!lexer_add_char(lx, line[*i]))
			return ;
		(*i)++;
	}
}
