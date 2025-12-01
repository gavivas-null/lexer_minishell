/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gavivas- <gavivas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:45:58 by gojeda            #+#    #+#             */
/*   Updated: 2025/12/01 19:19:33 by gavivas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <libft.h>

# define NORMAL 0
# define IN_SQUOTE 1
# define IN_DQUOTE 2

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF,
	TOKEN_ERROR,
	TOKEN_UNKNOWN
}	t_token_type;

/* Cada segmento de una palabra: texto y si es expandible */
typedef struct s_segment
{
	char				*str;
	bool				expand;
	struct s_segment	*next;
}	t_segment;

/* 
Un token WORD contiene una lista de segmentos.
Otros tokens usan ->value para información opcional (por ejemplo, filename raw).
*/
typedef struct s_token
{
	t_token_type	type;
	t_segment		*segments;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Resultado del lexer: lista ligada de tokens */
typedef struct s_lexer
{
	t_token	*head;
	t_token	*tail;
	int		error;
	char	*word;
	size_t	word_len;
}	t_lexer;

/* CRUD */
t_lexer			*lexer_create(void);
t_segment		*segment_new(char *str, bool expand);
t_token			*token_new(t_token_type type);
void			token_add_segment(t_token *tok, t_segment *seg);
bool			lexer_add_token(t_lexer *lex, t_token *tok);

/* Funciones para liberar memoria*/
void			lexer_destroy(t_lexer *lex);

/* Operator utils */
int				is_operator_char(char c);
t_token_type	identify_operator(const char *s);
int				operator_length(const char *s);

/* State Machine */
t_lexer			*lexer_tokenize(const char *line);
void			handle_normal(t_lexer *lx, const char *line,
					size_t *i, int *state);
void			handle_in_squote(t_lexer *lx, const char *line,
					size_t *i, int *state);
void			handle_in_dquote(t_lexer *lx, const char *line,
					size_t *i, int *state);

/* Words functions */
void			lexer_start_word(t_lexer *lx);
int				lexer_add_char(t_lexer *lx, char c);
bool			lexer_end_word(t_lexer *lx);

#endif