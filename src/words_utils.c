/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:03:06 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/07 18:15:11 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

// Inicializamos la palabra
void	lexer_start_word(t_lexer *lx)
{
	free(lx->word);
	lx->word = NULL;
	lx->word_len = 0;
}

// Agregamos un caracter a la palabra
int	lexer_add_char(t_lexer *lx, char c)
{
	char	*new;

	new = malloc(lx->word_len + 2);
	if (!new)
	{
		lx->error = 1;
		return (0);
	}
	if (lx->word)
	{
		ft_memcpy(new, lx->word, lx->word_len);
		free(lx->word);
	}
	new[lx->word_len] = c;
	new[lx->word_len + 1] = '\0';
	lx->word = new;
	lx->word_len++;
	return (1);
}

// Cerramos la palabra
bool	lexer_end_word(t_lexer *lx)
{
	t_token	*tok;

	if (lx->word_len == 0)
		return (true);
	tok = token_new(TOKEN_WORD);
	if (!tok)
		return (lx->error = 1, false);
	tok->value = ft_strndup(lx->word, lx->word_len);
	if (!tok->value)
	{
		free(tok);
		lx->error = 1;
		return (false);
	}
	if (!lexer_add_token(lx, tok))
	{
		free(tok->value);
		free(tok);
		lx->error = 1;
		return (false);
	}
	lx->word_len = 0;
	return (true);
}
