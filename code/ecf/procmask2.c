#include "csapp.h"
#include <time.h>

void getNowTime()
{
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);  //获取相对于1970到现在的秒数
    struct tm nowTime;
    localtime_r(&time.tv_sec, &nowTime);
    printf("%04d%02d%02d%02d:%02d:%02d\n", nowTime.tm_year + 1900,
            nowTime.tm_mon+1, nowTime.tm_mday,      
            nowTime.tm_hour, nowTime.tm_min,
            nowTime.tm_sec);
}

void initjobs()
{
}

void addjob(int pid)
{
    printf("addjod(pid=%d)\n",pid);
    getNowTime();
}

void deletejob(int pid)
{
}

/* $begin procmask2 */
void handler(int sig)
{
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;

    Sigfillset(&mask_all);
    while ((pid = waitpid(-1, NULL, 0)) > 0) { /* Reap a zombie child */
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid); /* Delete the child from the job list */
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    errno = olderrno;
}
    
int main(int argc, char **argv)
{
    int pid;
    sigset_t mask_all, mask_one, prev_one;

    Sigfillset(&mask_all);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);
    Signal(SIGCHLD, handler);
    initjobs(); /* Initialize the job list */

    while (1) {
        Sigprocmask(SIG_BLOCK, &mask_one, &prev_one); /* Block SIGCHLD */
        if ((pid = Fork()) == 0) { /* Child process */
            Sigprocmask(SIG_SETMASK, &prev_one, NULL); /* Unblock SIGCHLD */
            Execve("/bin/date", argv, NULL);
        }
        Sigprocmask(SIG_BLOCK, &mask_all, NULL); /* Parent process */  
        getNowTime();
        addjob(pid);  /* Add the child to the job list */
        sleep(3);
        getNowTime();
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);  /* Unblock SIGCHLD */
    }
    exit(0);
}
/* $end procmask2 */
