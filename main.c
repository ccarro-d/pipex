
#include "pipex.h"

int main(int argc, char **arg, char **envp)
{
    /*if (argc != 5)
    {
        write(1, "error\n", 6);
        return (1);
    }*/
    int i = 1;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}