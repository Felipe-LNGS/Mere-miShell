/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:04:33 by louismdv          #+#    #+#             */
/*   Updated: 2024/08/23 13:13:37 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// copier chars entre dollars ex: $$HOME$PWD
char	*ft_strndup_dol(char *s)
{
	int		i;
	char	*dst;

	i = 0;
	if (s[0] == '$')
		i++;
	while (s[i] && s[i] != '$')
		i++;
	dst = ft_calloc((i + 1), sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	if (s[0] == '$')
	{
		dst[0] = '$';
		i++;
	}
	while (s[i] && s[i] != '$')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	count_dols(char *word, int i)
{
	int	n;
	int	dols;

	n = i;
	dols = 0;
	while (word[n] == '$')
	{
		dols++;
		n--;
		if (n <= 0)
			break ;
	}
	return (dols);
}

char	*find_excode(char *str, t_shell *shell)
{
	if (!ft_strncmp(str, "$?", 2) || !ft_strncmp(str, "$?$", 3))
		str = ft_itoa(shell->tmpexit_code);
	else
		return (NULL);
	return (str);
}

char	*find_pwd(char *str, t_shell *shell)
{
	if (!ft_strncmp(str, "$0", 2) || !ft_strncmp(str, "$0$", 3))
		str = shell->av;
	else
		return (NULL);
	return (str);
}
