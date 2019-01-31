#include <func.h>

int main()
{
	int fds[2];
	int ret = pipe(fds);
	char buf[128]={0};
	if(!fork())
	{
		close(fds[0]);
		strcpy(buf,"hello");
		write(fds[1],buf,5);
	}else{
		close(fds[1]);
		read(fds[0],buf,5);
		printf("parent output:%s\n",buf);
	}
}
