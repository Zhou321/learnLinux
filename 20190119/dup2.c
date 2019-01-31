#include "func.h"

int main()
{
	//  std error out
  	int fde = open("file2",O_RDWR|O_CREAT);
  	if(-1==fde)
  	{
  		perror("openerror");
  		return -1;
  	}
  	printf("\n");
  	dup2(fde,2);
  	int f=open("test",O_RDWR);
  	if(-1==f)
  	{
  		perror("world");
  		return 0;
  	}
  	close(fde);
}
