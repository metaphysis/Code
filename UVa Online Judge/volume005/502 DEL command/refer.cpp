#include <stdio.h>
#include <string.h>

struct FileInfo
{
	char name[9];
	char ext[4];
	int name_len;
	int ext_len;
};

int nkeep, ndel;
FileInfo kfiles[1000], dfiles[1000];

char result_name[9], result_ext[4];

bool feasible()
{
	int i, j;
	bool matched;
	
	for(i = 0; i < nkeep; i++)
	{
		matched = true;
		
		for(j = 0; result_name[j] != '\0'; j++)
		{
			if(result_name[j] == '*')
				break;
			if(kfiles[i].name_len <= j || (result_name[j] != '?' && result_name[j] != kfiles[i].name[j]))
			{
				matched = false;
				break;
			}
		}
		
		if(!matched || (result_name[j] != '*' && kfiles[i].name_len > j))
			continue;
		
		if(result_ext[0] == '\0' && kfiles[i].ext[0] != '\0')
			continue;
		
		for(j = 0; result_ext[j] != '\0'; j++)
		{
			if(result_ext[j] == '*')
				break;
			if(kfiles[i].ext_len <= j || (result_ext[j] != '?' && result_ext[j] != kfiles[i].ext[j]))
			{
				matched = false;
				break;
			}
		}
		
		if(!matched || (result_ext[j] != '*' && kfiles[i].ext_len > j))
			continue;
		
		if(matched)
			return false;
	}
	
	return true;
}

bool generate()
{
	int i, j, min_dname_len = 8, max_dname_len = 1, min_dext_len = 3, max_dext_len = 0;
	
	memset(result_name, '\0', sizeof(result_name));
	memset(result_ext, '\0', sizeof(result_ext));
	
	for(i = 0; i < ndel; i++)
	{
		if(dfiles[i].name_len < min_dname_len)
			min_dname_len = dfiles[i].name_len;
		if(dfiles[i].name_len > max_dname_len)
			max_dname_len = dfiles[i].name_len;
		if(dfiles[i].ext_len < min_dext_len)
			min_dext_len = dfiles[i].ext_len;
		if(dfiles[i].ext_len > max_dext_len)
			max_dext_len = dfiles[i].ext_len;
	}
	
	for(i = 0; i < min_dname_len; i++)	// for name part
	{
		for(j = 0; j < ndel; j++)
		{
			if(result_name[i] == '\0')
			{
				result_name[i] = dfiles[j].name[i];
			}
			else if(result_name[i] != dfiles[j].name[i])
			{
				result_name[i] = '?';
			}
		}
	}
	if(min_dname_len < 8 && min_dname_len < max_dname_len)
		result_name[i++] = '*';
	
	for(i = 0; i < min_dext_len; i++)	// for ext part
	{
		for(j = 0; j < ndel; j++)
		{
			if(result_ext[i] == '\0')
			{
				result_ext[i] = dfiles[j].ext[i];
			}
			else if(result_ext[i] != dfiles[j].ext[i])
			{
				result_ext[i] = '?';
			}
		}
	}
	if(min_dext_len < 3 && min_dext_len < max_dext_len)
		result_ext[i] = '*';
	
	return feasible();
}

int main()
{
	int tc;
	bool first = true;
	char input[20], *ptr;
	scanf("%d", &tc);
	fgets(input, 20, stdin);
	fgets(input, 20, stdin);
	while(tc--)
	{
		nkeep = ndel = 0;
		while(fgets(input, 20, stdin))
		{
			if(input[0] == '\n')
				break;
			if(input[0] == '+')
			{
				strcpy(kfiles[nkeep].name, strtok(&input[1], ".\n"));
				ptr = strtok(NULL, "\n");
				if(ptr)
					strcpy(kfiles[nkeep].ext, ptr);
				else
					kfiles[nkeep].ext[0] = '\0';
				kfiles[nkeep].name_len = (int)strlen(kfiles[nkeep].name);
				kfiles[nkeep].ext_len = (int)strlen(kfiles[nkeep].ext);
				nkeep++;
			}
			else
			{
				strcpy(dfiles[ndel].name, strtok(&input[1], ".\n"));
				ptr = strtok(NULL, "\n");
				if(ptr)
					strcpy(dfiles[ndel].ext, ptr);
				else
					dfiles[ndel].ext[0] = '\0';
				dfiles[ndel].name_len = (int)strlen(dfiles[ndel].name);
				dfiles[ndel].ext_len = (int)strlen(dfiles[ndel].ext);
				ndel++;
			}
		}
		
		if(first)
			first = false;
		else
			printf("\n");
		
		if(generate())
		{
			printf("DEL %s.%s\n", result_name, result_ext);
		}
		else
		{
			printf("IMPOSSIBLE\n");
		}
	}
	return 0;
}
