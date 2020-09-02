/* A small Temperature monitor and logger daemon written for my raspberry Pi 4
 * Copyright 2020 onwards, Samveen Gulati.
 */

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <signal.h>

volatile sig_atomic_t done = 0;

char term_msg[]="Received SIGTERM. Terminating\n";
void handler(int signum) {
    if(signum==SIGTERM) {
        done = 1;
        write(2,term_msg,sizeof(term_msg));
    }
}

int main(int argc, char* argv[]) {
    int readfd=-1;

    char buf[512];
    char val[128];
    char source[]="/sys/class/thermal/thermal_zone0/temp";

    ssize_t bufsize=0, valsize=0;

    time_t t;
    uint64_t secs=10u;

    // Graceful termination with SIGTERM
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_handler = handler;
    sigaction(SIGTERM, &action, NULL);

    // Close stdin
    close(0);

    // Open source
    readfd=open((const char *)source, O_RDONLY);

    // main loop
    while(!done) {
        // Always read from the beginning.
        valsize=pread(readfd,val,sizeof(val)-1,0u);
        val[valsize]='\0';

        // We're assuming a whitespace in the read, no whitespace added.
        bufsize=snprintf((char *)buf, 512u,"%lu: %s",time(&t), val);
        write(1,(char *) buf,bufsize);

        sleep(secs);
    }

    close(readfd);
    return(0);
}

/* vim: set ts=4 sw=4 expandtab cin: */
