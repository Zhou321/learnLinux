#include <stdio.h>
#include <string.h>

int main(int argc,char *args[])
{
	FILE *fp;
	char buff[100]="3.1415926\n";
	fp=fopen(args[1],"ab+");
	if(NULL==fp)
	{
		perror("./ELF filename");
		return -1;
	}
	fwrite(buff,sizeof(char),strlen(buff),fp);
	return 0;
}
