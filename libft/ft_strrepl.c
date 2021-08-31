#include "libft.h"

/*
** Given and input string str and a replacement repl,
** replace the segment of str with repl starting at the start index
** 
** @param char *str		The input string
** @param char *repl	The replacement string
** @param int start		The start index of replacement
** @param int end		The end of replacement
**
** @return char *res	The resultant string
*/
char	*ft_strrepl(char *str, char *repl, int start, int end)
{
	char	*left;
	char	*right;
	char	*temp;

	if (!repl)
		return (str);
	left = ft_substr(str, 0, start);
	right = ft_substr(str, end, ft_strlen(str) - end);
	temp = ft_strjoin(left, repl);
	free(left);
	left = ft_strjoin(temp, right);
	free(right);
	free(temp);
	return (left);
}
