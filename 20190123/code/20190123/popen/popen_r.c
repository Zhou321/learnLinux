#include <func.h>

int main()
{
	FILE *fp;
	fp=popen("./print","r");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	fgets(buf,sizeof(buf),fp);
	printf("%s",buf);
	pclose(fp);
	return 0;
}
