/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:31:40 by gavivas-          #+#    #+#             */
/*   Updated: 2025/12/07 19:28:15 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lexer.h>

static char	*g_inputs[] = {
	"echo hola",
	"echo $USER",
	"echo \"$USER\"",
	"echo 'literal $USER'",
	"echo \"hola '$USER'\"",
	"echo    hello   world",
	"echo \"hola",
	"echo 'hola",
	"\"hola",
	"'hola",
	"",
	"    ",
	"|",
	"<",
	">",
	">>",
	"<<",
	"echo |",
	"| echo",
	"echo || echo",
	"echo >>> file",
	"echo \"hola \\\"mundo\\\"\"",
	"echo \"hola \\$USER\"",
	NULL
};

static void	print_word_token(t_token *tok)
{
	t_segment	*seg;

	printf("WORD: ");
	seg = tok->segments;
	if (seg)
	{
		while (seg)
		{
			printf("(%s|", seg->str);
			if (seg->expand)
				printf("exp");
			else
				printf("lit");
			printf(") ");
			seg = seg->next;
		}
	}
	else if (tok->value)
		printf("%s", tok->value);
	printf("\n");
}

static void	print_other_token(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		printf("PIPE |\n");
	else if (tok->type == TOKEN_REDIR_IN)
		printf("REDIR_IN <\n");
	else if (tok->type == TOKEN_REDIR_OUT)
		printf("REDIR_OUT >\n");
	else if (tok->type == TOKEN_HEREDOC)
		printf("HEREDOC <<\n");
	else if (tok->type == TOKEN_APPEND)
		printf("APPEND >>\n");
	else if (tok->type == TOKEN_EOF)
		printf("EOF\n");
	else
		printf("UNKNOWN\n");
}

void	lexer_print(t_lexer *lx)
{
	t_token	*tok;
	int		index;

	if (!lx)
	{
		printf("lexer: NULL\n");
		return ;
	}
	index = 0;
	tok = lx->head;
	while (tok)
	{
		printf("[%02d] ", index);
		if (tok->type == TOKEN_WORD)
			print_word_token(tok);
		else
			print_other_token(tok);
		tok = tok->next;
		index++;
	}
}

int	main(void)
{
	t_lexer	*lx;
	char	**inputs;
	int		i;

	inputs = g_inputs;
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
