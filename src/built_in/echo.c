/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:21:13 by imac21            #+#    #+#             */
/*   Updated: 2023/02/20 15:25:13 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"


int	ft_isquote(int c)
{
	if (c == '"' || c == 39)
		return (1);
	return (0);
}

int	ft_isequal(int c)
{
	if (c == '=')
		return (1);
	return (0);
}

int	ft_iswspace(char c)
{
	while (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

// int	skip_echo(int *o, int *i, t_token **tmp, int redir)
// {
// 	while (*i < ft_strlen("echo"))
// 		*i += 1;
// 	if (!g_data.token)
// 	{
// 		ft_putchar_fd('\n', redir);
// 		return (1);
// 	}
// 	while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
// 		*i += 1;
// 	if ((*tmp)->next)
// 		(*tmp) = (*tmp)->next;
// 	while (!ft_strncmp((*tmp)->token->value, "-n", ft_strlen("-n")))
// 	{
// 		(*tmp) = (*tmp)->next;
// 		*o = 1;
// 		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
// 			*i += 1;
// 		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
// 			*i += 1;
// 	}
// 	return (0);
// }

int	handle_quote(char *cmd, t_token **tmp, int *i, int redir)
{
	while ((*tmp) && ft_isquote((*tmp)->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1)
		*i += 1;
	while (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		*i += 1;
	ft_putstr_fd((*tmp)->value, redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	while ((*tmp) && ft_isquote((*tmp)->value[0]) == 1)
	{
		ft_putstr_fd((*tmp)->value, redir);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		else
			return (1);
	}
	return (0);
}

int	handle_string(char *cmd, t_token **tmp, int *i, int redir)
{
	ft_putstr_fd((*tmp)->value, redir);
	if ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	else
		return (1);
	while (cmd[*i] && ft_isquote(cmd[*i]) != 1 && ft_iswspace(cmd[*i]) != 1
		&& ft_isprint(cmd[*i]) > 1 && cmd[*i] != '=')
		*i += 1;
	if (cmd[*i] == '=')
		*i += 1;
	return (0);
}

int	loop_echo(char *cmd, t_token **tmp, int *i, int redir)
{
    // printf("debut loop\n");
	while (cmd[*i] && (*tmp) && (*tmp)->t_type != 5
		&& (*tmp)->t_type != 6 && (*tmp)->t_type != 8
		&& (*tmp)->t_type != 7)
	{
		if (cmd[*i] && ft_isquote(cmd[*i]) == 1)
		{
			if (handle_quote(cmd, tmp, i, redir) == 1)
				return (1);
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
		{
			ft_putchar_fd(' ', redir);
			*i += 1;
			while (cmd[*i] && ft_iswspace(cmd[*i]) == 1)
				*i += 1;
		}
		else if (cmd[*i] && ft_iswspace(cmd[*i]) != 1)
		{
			if (handle_string(cmd, tmp, i, redir) == 1)
				return (1);
		}

        // printf("milieu loop\n");
    }
    // printf("fin loop\n");
	return (0);
}

int	ft_echo(char **option, int redir)
{
	t_token 	*tmp;
	char		*cmd;
	int			i;
	int			start;

(void)option;
	start = -1;
	i = 0;
	tmp = g_data.token;
    cmd = g_data.cmd;
    // (void)cmd;
    printf("entre dans echo baby\n");
	if (redir == -1)
		redir = 1;
    while (i < ft_strlen("echo"))
		i += 1;
    printf("meme pas la\n");
	// if (!option[1])
	// {
    //     printf("entre bizarrement \n");
	// 	ft_putchar_fd('\n', redir);
	// 	return (1);
	// }
    printf("la\n");
	while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
		i += 1;
	if (tmp->next)
		tmp = tmp->next;
    printf("dis moi quelle est la valeur de tmp = %s     %d\n", tmp->value, !ft_strncmp(tmp->value, "-n", ft_strlen("-n")));
	while (!ft_strncmp(tmp->value, "-n", ft_strlen("-n")))
	{
        printf("cbn le frero stp\n");
		tmp = tmp->next;
		start = 1;
		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) != 1)
			i += 1;
		while (g_data.cmd[i] && ft_iswspace(g_data.cmd[i]) == 1)
			i += 1;
       
    }
    printf("avant loop\n");
	if (loop_echo(cmd, &tmp, &i, redir) == 1)
    {
        printf("ui\n");
		;
    }
    printf("apres loop\n");
	if (start == -1)
		ft_putchar_fd('\n', redir);
    printf("sors comme un fou furieux\n");
	return (1);
}