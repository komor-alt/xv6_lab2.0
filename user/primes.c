#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int pleft[2])
{
  int p;
  read(pleft[0],&p,sizeof(p));
  if( p == -1)
  {
    exit(0); // end the process
  }
  printf("prime %d\n",p);

  int pright[2];
  pipe(pright);

  if(fork() == 0)
  {
     close(pright[1]);
     close(pleft[0]);
     sieve(pright);
  }else{
    close(pright[0]);

    int buf;
    while(read(pleft[0],&buf,sizeof(buf)) && buf!=-1)
    {
        if(buf % p != 0)
        {
            write(pright[1],&buf,sizeof(buf));
        }
    }
    buf = -1;
    write(pright[1],&buf,sizeof(buf));
    wait(0);
    exit(0);
  }
}
int main(int argc, char **argv) {
    // 创建初始管道
    int input_pipe[2];pipe(input_pipe); 
    if(fork() == 0) {
        // 右邻居
        close(input_pipe[1]); 
        // 右邻居用不到这个管道的写端，关闭右邻居的管道写文件描述符
        sieve(input_pipe);
        // 调用筛选函数
        exit(0);
        }else {
            // 父进程
            close(input_pipe[0]); 
            // 父进程只会向管道中给右邻居写数据，关闭父进程的管道读文件描述符
            int i;
            for(i=2;i<=35;i++){
                write(input_pipe[1], &i, sizeof(i));
                // 向管道写入2~35的整数
                }
                // 写入结束标志
                i = -1;
                write(input_pipe[1], &i, sizeof(i)); 
            }
                wait(0);
                 // 等待子进程结束
                 // 注意：这里无法等待子进程的子进程，只能等待直接子进程，无法等待间接子进程。
                 // 在 sieve() 中再各自执行 wait(0)，形成等待链
                 exit(0);// 退出进程
}