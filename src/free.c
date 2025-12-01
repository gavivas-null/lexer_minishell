/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:10:47 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/01 22:05:50 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

// Liberamos los segmentos
static void	free_segments(t_segment *seg)
{
	t_segment	*tmp;

	while (seg)
	{
		tmp = seg->next;
		free(seg->str);
		free(seg);
		seg = tmp;
	}
}

// Liberamos todos los tokens del lexer
void	lexer_destroy(t_lexer *lex)
{
	t_token	*tmp;

	if (!lex)
		return ;
	if (lex->word)
		free(lex->word);
	while (lex->head)
	{
		tmp = lex->head->next;
		if (lex->head->value)
			free(lex->head->value);
		if (lex->head->segments)
			free_segments(lex->head->segments);
		free(lex->head);
		lex->head = tmp;
	}
	free(lex);
}
