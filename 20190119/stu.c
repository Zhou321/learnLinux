#include <stdio.h>
#include "func.h"
typedef struct student
{
	int iNum;
	int iScore;
	char *chName;
}stu;

int main(int args,char **argv)
{
	args_check(args,2);
	struct student s[]={{1,90,"xiaoming"},{2,93,"xiaowang"},{3,80,"xiaoli"}};
	FILE *fp = fopen(argv[1],"wb+");
	if(NULL==fp)
	{
		perror("No such file or directory");
		return -1;
	}
	for(int i=0;i<3;i++)
	{
		fprintf(fp,"%d ",s[i].iNum);
		fprintf(fp,"%d ",s[i].iScore);
		fprintf(fp,"%s\n",s[i].chName);
	}
	fseek(fp,0,SEEK_SET);
//	int fd = fileno(fp);
//	lseek(fd,1,SEEK_SET); //set to the begining of the file
	char c;
	while((c=fgetc(fp))!=EOF)
	{
		printf("%c",c);
		fflush(stdout);
	}
	return 0;
}
