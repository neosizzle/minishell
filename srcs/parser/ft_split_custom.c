#include "minishell.h"
//custom ft_split func, does the same thing as normal ft_split 
//except that this version ignores quotes

static void	ft_strcpy(char *dst, char *begin, char *end)
{
	while (begin < end)
		*(dst++) = *(begin++);
	*dst = 0;
}

static int	handle_quotes_tw(char **s)
{
	char	quote;
	char	cancel;

	quote = **s;
	cancel = *(*s + 1);
	if (quote && quote == '\\' && (cancel == '\"' || cancel == '\''))
	{
		(*s)+=2;
		return (0);
	}
	if (!(quote == '\"' || quote == '\''))
		return (0);
	(*s)++;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
		(*s)++;
	return (1);
}

static int	get_tw(char *s, char c)
{
	int		res;

	res = 0;
	while (*s)
	{
		if (!(*s == c))
		{
			res++;
			if (handle_quotes_tw(&s))
				continue ;
			while (*s && !(*s == c))
				s++;
		}
		else
			s++;
	}
	return (res);
}

static int	handle_quotes(char **res, char *start, int *i, char **s)
{
	char	quote;
	char	cancel;

	quote = **s;
	cancel = *(*s + 1);
	if (quote && quote == '\\' && (cancel == '\"' || cancel == '\''))
	{
		(*s)+=2;
		return (0);
	}
	if (!(quote == '\"' || quote == '\''))
		return (0);
	(*s)++;
	while (**s && **s != quote)
	{
		if (**s == '\\')
			(*s)++;
		(*s)++;
	}
	if (**s == quote)
		(*s)++;
	res[*i] = (char *)malloc((char *)*s - start + 1);
	ft_strcpy(res[(*i)++], start, (char *)*s);
	return (1);
}

char	**ft_split_custom(char *s, char c)
{
	char	*start;
	char	**res;
	int		i;

	if (!s)
		return (0);
	res = (char **)malloc((sizeof(char *) * (get_tw((char *)s, c) + 1)));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			if (handle_quotes(res, start, &i, &s))
				continue ;
			while (*s && *s != c)
				s++;
			res[i] = (char *)malloc((char *)s - start + 1);
			ft_strcpy(res[i++], start, (char *)s);
		}
		else
			s++;
	}
	res[i] = 0;
	return (res);
}
