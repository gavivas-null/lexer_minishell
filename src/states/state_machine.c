/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:31:04 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/07 19:40:49 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static bool	finalize_lexer(t_lexer	*lx)
{
	t_token	*eof;

	lexer_end_word(lx);
	if (lx->error)
	{
		lexer_destroy(lx);
		return (true);
	}
	eof = token_new(TOKEN_EOF);
	if (!eof)
	{
		lexer_destroy(lx);
		return (true);
	}
	if (!lexer_add_token(lx, eof))
	{
		free(eof);
		lexer_destroy(lx);
		return (true);
	}
	return (false);
}

static void	run_state_machine(t_lexer *lx, const char *line,
			size_t *i, int *state)
{
	while (line[*i] && !lx->error)
	{
		if (*state == NORMAL)
			handle_normal(lx, line, i, state);
		else if (*state == IN_SQUOTE)
			handle_in_squote(lx, line, i, state);
		else if (*state == IN_DQUOTE)
			handle_in_dquote(lx, line, i, state);
	}
}

t_lexer	*lexer_tokenize(const char *line)
{
	t_lexer	*lx;
	size_t	i;
	int		state;

	lx = lexer_create();
	if (!lx)
		return (NULL);
	i = 0;
	state = NORMAL;
	run_state_machine(lx, line, &i, &state);
	if (state != NORMAL)
	{
		lexer_destroy(lx);
		return (NULL);
	}
	if (finalize_lexer(lx))
		return (NULL);
	return (lx);
}
