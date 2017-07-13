#include "bitbang.h"
#include "linuxgpio.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	unsigned char buf[4], res[4];
	IOCtrl ctrl;
	linuxgpio_init(&ctrl);
	ctrl.open(&ctrl);
	ctrl.cmd(&ctrl, buf, res);
	for (int i=0; i < 4; i++)
		printf("%d\n", res[i]);
	ctrl.close(&ctrl);
}
