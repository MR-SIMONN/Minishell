#include "../Minishell.h"

char	*ft_strdup(char *s1, t_data *d)
{
	int     i;
	int     len;
	char    *str;

	i = 0;
	len = ft_strlen(s1);
	str = ft_malloc (len + 1, d));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}