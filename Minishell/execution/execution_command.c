#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    if(pid == 0)
    {
        printf("%d", pid);
    }
    else
    {
        printf("%d", pid);
        printf("parent");
    }
}