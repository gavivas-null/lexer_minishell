/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crud.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:47:36 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/01 19:13:52 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

// Creamos el lexer vacio
t_lexer	*lexer_create(void)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	if (!lex)
		return (NULL);
	lex->head = NULL;
	lex->tail = NULL;
	lex->error = 0;
	lex->word = NULL;
	lex->word_len = 0;
	return (lex);
}

// Creamos un segmento (parte de una WORD)
t_segment	*segment_new(char *str, bool expand)
{
	t_segment	*seg;

	seg = malloc(sizeof(t_segment));
	if (!seg)
		return (NULL);
	seg->str = str;
	seg->expand = expand;
	seg->next = NULL;
	return (seg);
}

// Creamos un token
t_token	*token_new(t_token_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->segments = NULL;
	tok->value = NULL;
	tok->next = NULL;
	return (tok);
}

// Agregamos un segmento a un token WORD
void	token_add_segment(t_token *tok, t_segment *seg)
{
	t_segment	*tmp;

	if (!tok || !seg)
		return ;
	if (!tok->segments)
		tok->segments = seg;
	else
	{
		tmp = tok->segments;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = seg;
	}
}

// Agregamos un token al lexer
bool	lexer_add_token(t_lexer *lex, t_token *tok)
{
	if (!lex || !tok)
		return (false);
	if (!lex->head)
	{
		lex->head = tok;
		lex->tail = tok;
	}
	else
	{
		lex->tail->next = tok;
		lex->tail = tok;
	}
	return (true);
}
