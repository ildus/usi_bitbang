#include "bitbang.h"
#include "linuxgpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int stop = 0;

void int_handler(int dummy)
{
	stop = 1;
}

int main(void)
{
	signal(SIGINT, int_handler);

	unsigned char buf[4], res[4];
	IOCtrl ctrl;
	linuxgpio_init(&ctrl);
	ctrl.open(&ctrl);
	while (!stop)
	{
		ctrl.cmd(&ctrl, buf, res);
		for (int i=0; i < 4; i++)
			printf("%d\n", res[i]);
		sleep(1);
	}
	ctrl.close(&ctrl);
}
