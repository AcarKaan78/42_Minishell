/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenel <asenel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 10:57:52 by asenel            #+#    #+#             */
/*   Updated: 2024/06/01 12:34:04 by asenel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <termios.h>
# include "libft/libft.h"

typedef struct s_red
{
	char	*str;
	char	*type;
}	t_red;

typedef struct s_parse
{
	char	**str;
	char	*type;
	t_red	*red;
}	t_parse;

typedef struct s_lastpars
{
	int		i;
	int		z;
	int		j;
	t_parse	*last;
	int		fpi;
	int		tru;
	char	**str;
}	t_lastparse;

typedef struct s_data
{
	t_parse		*parts;
	t_red		*red;
	int			exitstatus;
	char		*commandline;
	char		*templine;
	char		**path;
	char		*foundedpath;
	char		**arguments;
	char		*simplestarttext;
	char		*starttext;
	char		**envp;
	char		**exportp;
	int			errorstatus;
	int			exportlen;
	int			commandcount;
	int			fderr;
	int			parsererrorcode;
	int			pipe_pos;
}	t_data;

typedef struct s_global
{
	int	error;
	int	heredoc;
	int	execstatus;
}	t_global;

t_global	g_global;

char	*ft_getpc(void);
void	ft_fndsrttxt(char *pcname, t_data *data);
int		ft_findpth(char *searchedpath, t_data *data);
void	ft_initfunc(char **envp, int argc, char **argv, t_data *data);
void	ft_ifsigint(int signal);
void	ft_error(char *a);
char	**ft_cpyenvo(char **env);
void	ft_ifsend(t_data *data);
int		ft_quote(char *line, int control);
void	ft_parsermain(t_data *data);
void	ft_prnttw_str(char **str, int flagcontrol);
int		ft_prsrlngcntr(int i, t_data *data);
int		ft_ifmorequote(char *a, int i, int *j, t_data *data);
int		ft_squot(char *a, int i, int *j, t_data *data);
int		ft_pipcont(char *a, int i, t_data *data);
t_parse	*ft_endpars(char **str, int tru, int i, t_data *data);
void	ft_quoterr(t_data *data);
int		ft_cmdpnterl(char **d);
void	ft_cd(char **a, t_data *data);
void	ft_pwd(t_data *data);
int		ft_pathind(char *searchedpath, t_data *data);
int		ft_fndindvp(char *searchedenvp, int searchindex, t_data *data);
int		ft_findvnpind2(char *searchedenvp, t_data *data);
void	ft_envcmd(t_data *data);
void	ft_expcmd(char **str, int i, int error, t_data *data);
char	**ft_addbpoi(char **dp, char *add);
char	**ft_rmvdbpoi(char **dp, int i);
void	ft_echocmd(char **str);
char	*ft_getpath(char **env, char *str, t_data *data);
int		ft_exppar(char *str);
int		ft_fndexpind(char *searchedexportp, int searchindex, t_data *data);
void	ft_unsetcmd(char **str, t_data *data);
void	ft_exitcmd(t_data *data);
char	*ft_smpincmd(int i, t_data *data);
char	*ft_smpoutcmd(int i, t_data *data);
void	ft_trndol(t_data *data, int quote);
void	ft_sndquit(int signal);
void	ft_ppcmd(t_parse *part1, t_parse *part2, int i, t_data *data);
void	ft_chiledfpi(t_parse *part1, t_parse *part2, t_data *data);
void	ft_chiled(char **str, t_data *data);
void	ft_dscnmmkng(char **str, t_data *data);
void	ft_odd_right_redirection(char *str, t_data *data, t_parse *part);
void	ft_odd_left_redirection(char *str, t_data *data, t_parse *part);
char	*ft_rmvquo2(char *str);
void	ft_rmvquo(t_data *data);
int		ft_echoflgcnt(char *str);
void	ft_multiple_right_redirection(char *str, t_data *data, t_parse *part);
void	ft_multiple_left_redirection(char *str, t_data *data, t_parse *part);
int		ft_endpp(t_data *data, int i);
void	ft_pprawhile(t_data *data);
void	ft_frdblpoi(char **str);
void	ft_erctl(t_data *data, int err);
void	ft_dscnmmkng(char **str, t_data *data);
void	ft_cmdfndv2(t_data *data);
void	ft_prntexp(t_data *data);
int		ft_dbleinp(t_data *data);
void	ft_input_all(t_parse *part, t_data *data);
void	ft_output_all(t_parse *part, t_data *data);
int		ft_chckred(char **str);
int		ft_redlen(t_red *red);
void	ft_cmdfndpipe(t_data *data);
int		ft_cntred(char **str);
char	**ft_outred(char **str, int x);
int		ft_wordpartsout_red(char **argu);
void	del_ctr(void);
void	ft_sub_output(t_parse *part, int i);
int		ft_wordsparts(char **argu);
char	**ft_twdcpy(char **src);
int		ft_cntpars(t_data *data, int i, int count, int tru);
char	*ft_lstpardef_typ(char *str);
void	ft_addquo(char **arguments, int i);
void	ft_adstrhelp2(t_data *data, char *firststr,
			int argi, int startindex);
void	ft_addstrhelp3(t_data *data, char *thirdstr, int argi, int endindex);
void	ft_updthelpexp(t_data *data, char *str);

#endif