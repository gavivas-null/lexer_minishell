/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:27:24 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/01 19:13:43 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static void	normal_operator(t_lexer *lx, const char *line, size_t *i)
{
	t_token_type	type;
	t_token			*tok;

	lexer_end_word(lx);
	type = identify_operator(&line[*i]);
	tok = token_new(type);
	lexer_add_token(lx, tok);
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
	{
		normal_operator(lx, line, i);
		return ;
	}
	if (line[*i] == '\'')
	{
		normal_in_squote(state, i);
		return ;
	}
	if (line[*i] == '"')
	{
		normal_in_dquote(state, i);
		return ;
	}
	if (line[*i] == ' ' || line[*i] == '\t')
	{
		lexer_end_word(lx);
		(*i)++;
		return ;
	}
	lexer_add_char(lx, line[*i]);
	(*i)++;
}
