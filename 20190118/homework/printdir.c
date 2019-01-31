#include "func.h"
//judge the permission of the object
char *getPmis(unsigned int mode)
{
	char *strRes=calloc(1,sizeof(char)*10);
	int i=8,tmp=1;
	//judge from the tail of mask
	for(;i>=0;i--)
	{
		if(mode & tmp<<(8-i))
		{
			switch(i%3)
			{
				case 0:
					strRes[i]='r';
					break;
				case 1:
					strRes[i]='w';
					break;
				case 2:
					strRes[i]='x';
					break;
			}
		}else{
			strRes[i]='-';
		}
	}
}
//judge the type of the object
char getType(unsigned int mode)
{
	if(S_ISDIR(mode)){
		return 'd';
	}	
	if(S_ISREG(mode) || S_ISLNK(mode)){
		return '-';
	}
}
//traversal the directory and print the file
void travDir(char *path)
{
	struct dirent *p;
	struct tm *pTime;
	struct stat buf;
	//initialize
	DIR *pdir=opendir(path);
	char *strTmp=calloc(1,strlen(path)+500);
	char *chMon[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nev","Dec"};
	if(NULL==pdir)
	{
		perror("No such directory\n");
		return ;
	}
	while((p=readdir(pdir))!=NULL)
	{
		strcpy(strTmp,path);
		if(0==strcmp(p->d_name,".") || 0==strcmp(p->d_name,"..")){
			continue;
		}
		strcat(strTmp,"/");
		strcat(strTmp,p->d_name);	
		stat(strTmp,&buf);	//get file information
		pTime=localtime(&(buf.st_mtime)); //get local time
		printf("%c%s %lu %s %s %5ld %s %d %02d:%02d %s\n",getType(buf.st_mode),getPmis(buf.st_mode),buf.st_nlink,(getpwuid(buf.st_uid))->pw_name,(getgrgid(buf.st_uid))->gr_name,buf.st_size,chMon[pTime->tm_mon],pTime->tm_mday,pTime->tm_hour,pTime->tm_min,p->d_name);
		//reset
		memset(&buf,0,sizeof(buf));
		memset(strTmp,0,strlen(path)+500);
	}
}
int main(int args,char **argv)
{
	args_check(args,2);
	travDir(argv[1]);
}

