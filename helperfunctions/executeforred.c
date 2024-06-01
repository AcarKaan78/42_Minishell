/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeforred.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:12:02 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:30:29 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_outred(char **str, int c)
{
	char	**new;
	int		a;
	int		b;

	b = 0;
	c = 0;
	a = 0;
	new = (char **)malloc(sizeof(char *) * ft_wordpartsout_red(str) + 1);
	while (str[a] && str[a][0] != '|')
	{
		if (str[a][0] != '<' && str[a][0] != '>')
		{
			new[b] = ft_strdup(str[a]);
			b++;
		}
		else
			a++;
		a++;
	}
	new[b] = NULL;
	return (new);
}

int	ft_chckred(char **str)
{
	int	a;

	a = 0;
	while (str[a] && str[a][0] != '|')
	{
		if (str[a][0] == '<' || str[a][0] == '>'
			|| !ft_strcmp(str[a], "simpleoutput")
			|| !ft_strcmp(str[a], "simpleinput")
			|| !ft_strcmp(str[a], "multipleoutput")
			|| !ft_strcmp(str[a], "multipleinput"))
			return (1);
		a++;
	}
	return (0);
}

void	ft_input_all(t_parse *part, t_data *data)
{
	int	a;

	if (ft_chckred(data->arguments) && part->red)
	{
		a = ft_redlen(part->red);
		while (a + 1)
		{
			if (part->red[a].str[0] == '<' && part->red[a].str[1] == '<')
			{
				ft_multiple_left_redirection(&(part->red[a].str[2]),
					data, part);
				return ;
			}
			else if (part->red[a].str[0] == '<')
			{
				ft_odd_left_redirection(&(part->red[a].str[1]), data, part);
				return ;
			}
			a--;
		}
	}
	ft_dscnmmkng(part[0].str, data);
}

void	ft_output_all(t_parse *part, t_data *data)
{
	int	a;

	if (ft_chckred(data->arguments) && part->red)
	{
		a = ft_redlen(part->red);
		while (a + 1)
		{
			if (part->red[a].str[0] == '>' && part->red[a].str[1] == '>')
			{
				ft_multiple_right_redirection(&(part->red[a].str[2]),
					data, part);
				ft_sub_output(part, a - 1);
				return ;
			}
			else if (part->red[a].str[0] == '>')
			{
				ft_odd_right_redirection(&(part->red[a].str[1]), data, part);
				ft_sub_output(part, a - 1);
				return ;
			}
			a--;
		}
	}
	ft_input_all(part, data);
}
