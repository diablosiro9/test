/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imac21 <imac21@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:00:53 by imac21            #+#    #+#             */
/*   Updated: 2023/02/18 19:04:43 by imac21           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/include.h"

char    *ft_sub(char const *s, unsigned int start, size_t len)
{
    char *str = NULL;
    size_t i;

    i = 0;
    // if (!s)
    //     return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    while (i < len)
    {
        str[i] = s[start + i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

t_env	*ft_envnew(char *name, char *content, int i)
{
	(void)i;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
	
}

void	ft_envadd(t_env **lst, t_env *new)
{
	t_env	*tmp = NULL;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (*lst)
		tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}


t_env *get_env(char **env)
{
    int i = 0;
    t_env *list = NULL;
    
    // list = malloc(sizeof(t_env *) * 1000);
    // if (!list)
    // {
    //     printf("malloc error\n");
    //     exit(-127);
    // }
    while (env[i])
    {
		// list = ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		// ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i);
        ft_envadd(&list, ft_envnew(ft_sub(env[i], 0, ft_strchr(env[i], '=') - env[i]), \
		ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i])), i));
		// list[i].content =  ft_sub(env[i], starter_env(env[i]), ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i]));
		// list[i].next = NULL;
		i++;
    }
	list->num_vars = i;
    return (list);
}

void	ft_env(char	*s)
{
	t_env	*tmp = NULL;

	tmp = g_data.env;
	if (tmp != NULL)
	{
		if (s == NULL)
		{
			while (tmp != NULL)
			{
				printf("%s%s\n", tmp->name, tmp->content);
				tmp = tmp->next;
			}
		}
		else
		{
			while (tmp != NULL)
			{
				if (ft_strncmp(s, tmp->content, ft_strlen(s)) == 0)
				{
					printf("%s\n", tmp->content);
					return ;
				}
				else
				{
					if (tmp->next != NULL)
						tmp = tmp->next;
				}
			}
		}
	}
}
