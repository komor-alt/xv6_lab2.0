#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void find(char *path,char *target)
{
    char buf[512],*p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path,0))<0)
    {
        fprintf(2,"find:canot open %s\n",path);
        return ;
    }
    if(fstat(fd,&st)<0)
    {
        fprintf(2,"find: cannot stat %s\n",path);
        close(fd);
        return;
    }
    switch(st.type)
    {
        case T_FILE;
    }

}
int main(int argc,char ** argv)
{
    if(argc <3)
    {
        exit(0);
    }
    char target[512];
    target[0]= '/';
    strcpy(target+1,argv[2]);
    exit(0);
}