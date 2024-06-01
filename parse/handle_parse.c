/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:21:03 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:31:22 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_redirection(t_lastparse *lp)
{
	lp->last[lp->j - 1].red[lp->z].str = ft_strjoin2(lp->str[lp->i],
			lp->str[lp->i + 1]);
	lp->last[lp->j - 1].red[lp->z].type = ft_lstpardef_typ(lp->str[lp->i]);
	lp->z++;
}

void	handle_pipe(t_lastparse *lp)
{
	if (ft_chckred(&(lp->str[lp->fpi])))
	{
		lp->last[lp->j - 1].red[lp->z].type = NULL;
	}
	lp->fpi = lp->i + 1;
	lp->tru = 1;
	lp->last[lp->j].red = NULL;
	lp->last[lp->j].str = ft_twdcpy(&(lp->str[lp->i]));
	lp->last[lp->j++].type = ft_lstpardef_typ(lp->str[lp->i]);
}

void	handle_redirection(t_lastparse *lp)
{
	if (lp->tru == 1 && !ft_chckred(&(lp->str[lp->fpi])))
	{
		lp->tru = 0;
		lp->last[lp->j].red = NULL;
		lp->last[lp->j].str = ft_twdcpy(&(lp->str[lp->i]));
		lp->last[lp->j++].type = ft_strdup("word");
	}
}

void	last_parse_init(t_lastparse *lp)
{
	while (lp->str[++(lp->i)])
	{
		if (lp->str[lp->i][0] == '|')
			handle_pipe(lp);
		else if ((lp->str[lp->i][0] == '>' || lp->str[lp->i][0] == '<')
					&& lp->str[lp->i + 1] && ft_chckred(&(lp->str[lp->fpi])))
		{
			if (lp->tru == 1)
			{
				lp->last[lp->j].red = malloc(sizeof(t_red)
						* (ft_cntred(&(lp->str[lp->fpi])) + 1));
				lp->tru = 0;
				lp->z = 0;
				lp->last[lp->j].str
					= ft_outred(&(lp->str[lp->fpi]), lp->i);
				lp->last[lp->j++].type = ft_strdup("word");
			}
			join_redirection(lp);
		}
		else
			handle_redirection(lp);
	}
	lp->last[lp->j].type = NULL;
	if (ft_chckred(&(lp->str[lp->fpi])))
		lp->last[lp->j - 1].red[lp->z].type = NULL;
}

t_parse	*ft_endpars(char **str, int tru, int i, t_data *data)
{
	t_lastparse	lp;
	t_parse		*last;

	lp.last = malloc(sizeof(t_parse) * (ft_cntpars(data, -1, 0, 1) + 1));
	lp.i = i;
	lp.j = 0;
	lp.z = 0;
	lp.fpi = 0;
	lp.tru = tru;
	lp.str = str;
	last_parse_init(&lp);
	last = lp.last;
	return (last);
}
