#include "func.h"

//try to print a file,if the file doesn't exist,return -1
int tryprint(char *pathname)
{
	int fd = open(pathname,O_RDWR|O_CREAT|O_EXCL);
	if(-1==fd)
	{
		char c;
		FILE *fp = fopen(pathname,"rb");
		//print file
		while((c=fgetc(fp))!=EOF)
		{
			printf("%c",c);
		}
		return 0;
	}else{
		//delete temp file
		remove(pathname);
		return -1;
	}
}

//traversal the directory and print the file
void travDir(char *path,char *pfile)
{
	struct dirent *p;
	DIR *pdir=opendir(path);
	if(NULL==pdir)
	{
		perror("No such directory\n");
		return ;
	}
	char *pathTmp;
	while((p=readdir(pdir))!=NULL)
	{
		//	printf("d_ino=%ld,d_reclen=%d,d_type=%d,d_name=%s\n",p->d_ino,p->d_reclen,p->d_type,p->d_name);
		if(0==strcmp(p->d_name,".") || 0==strcmp(p->d_name,"..")){
			continue;
		}
		pathTmp=(char *)calloc(1,sizeof(char)*strlen(path));
		strcpy(pathTmp,path);
		if(DT_DIR==p->d_type){
			strcat(pathTmp,"/");
			strcat(pathTmp,p->d_name);
			travDir(pathTmp,pfile);
		}else if(NULL!=strstr(pfile,p->d_name)){
			strcat(pathTmp,"/");
			strcat(pathTmp,pfile);
			tryprint(pathTmp);
			break;
		}
		free(pathTmp);
		pathTmp=NULL;
	}
}
int main(int argc, char **argv)
{
	args_check(argc,3);
	char *p_path = argv[1];
	char *p_file = argv[2];
	travDir(p_path,p_file);
}
