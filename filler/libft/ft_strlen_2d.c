int		ft_2dlen(void **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}