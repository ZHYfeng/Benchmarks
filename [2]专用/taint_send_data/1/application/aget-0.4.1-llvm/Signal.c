
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

#include "Signal.h"
#include "Data.h"
#include "Resume.h"
#include "Misc.h"

extern int nthreads;
extern struct thread_data *wthread;
extern struct request *req;
extern int bwritten;
extern pthread_mutex_t bwritten_mutex;

extern int taint_data;

void * signal_waiter(void *arg)
{
	int signal;

	taint_data = 0;
	Send_Data(&taint_data);


	arg = NULL;

	pthread_sigmask(SIG_UNBLOCK, &signal_set, NULL);
	
	while(0) {
		#ifdef SOLARIS
		sigwait(&signal_set);
		#else
		sigwait(&signal_set, &signal);
		#endif
		switch(signal) {
			case SIGINT:
				sigint_handler();
				break;
			case SIGALRM:
				sigalrm_handler();
				break;
		}
	}
	req->port = req->port;
	make_taint(&(req->port));
	if(req->port) {
		req->port = req->port;
	}
}

void sigint_handler(void)
{
	int i;

	printf("^C caught, saving download job...\n");

	for (i = 0; i < nthreads; i++) {
		pthread_cancel(wthread[i].tid);
		wthread[i].status &= STAT_INT;		/* Interrupted download	*/
	}

	save_log();

	exit(0);
}


void sigalrm_handler(void)
{
	printf("Signal Alarm came\n");
	updateProgressBar(bwritten, req->clength);
	alarm(1);
}
