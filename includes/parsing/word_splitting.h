#ifndef WORD_SPLITTING_H
# define WORD_SPLITTING_H

# include "../minishell.h"
# include "../structures.h"

t_parse_error	word_splitting(t_main *shell);
bool			contains_ifs_chars(char *str);
void			replace_split_token(t_token **tokens, t_token *new_tokens,
					t_token *token);

#endif
