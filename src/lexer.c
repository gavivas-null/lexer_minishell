/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:31:40 by gavivas-          #+#    #+#             */
/*   Updated: 2025/12/01 20:57:07 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

void	lexer_print(t_lexer *lx)
{
	t_segment	*s;
	t_token		*tok;
	int			i;

	i = 0;
	if (!lx)
	{
		printf("lexer: NULL\n");
		return ;
	}
	for (tok = lx->head; tok; tok = tok->next)
	{
		printf("[%02d] ", i++);
		switch (tok->type)
		{
			case TOKEN_WORD:
			{
				printf("WORD: ");
				s = tok->segments;
				while (s)
				{
					printf("(%s|%s) ", s->str, s->expand ? "exp" : "lit");
					s = s->next;
				}
				printf("\n");
				break ;
			}
			case TOKEN_PIPE: printf("PIPE |\n"); break ;
			case TOKEN_REDIR_IN: printf("REDIR_IN <\n"); break ;
			case TOKEN_REDIR_OUT: printf("REDIR_OUT >\n"); break ;
			case TOKEN_HEREDOC: printf("HEREDOC <<\n"); break ;
			case TOKEN_APPEND: printf("APPEND >>\n"); break ;
			case TOKEN_EOF: printf("EOF\n"); break ;
			default: printf("UNKNOWN\n"); break ;
		}
	}
}

int	main(void)
{
	t_lexer	*lx;
	int		i;
	char	*inputs[] = {"echo hola", "echo $USER", "echo \"$USER\"",
		"echo 'literal $USER'", "echo \"hola '$USER'\"",
		"echo    hello   world", NULL};

	i = 0;
	while (inputs[i])
	{
		printf("Input: %s\n", inputs[i]);
		lx = lexer_tokenize(inputs[i]);
		lexer_print(lx);
		lexer_destroy(lx);
		printf("\n");
		i++;
	}
	return (0);
}
