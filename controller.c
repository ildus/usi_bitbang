#include "bitbang.h"
#include "linuxgpio.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	IOCtrl ctrl;
	linuxgpio_init(&ctrl);
	ctrl.open(&ctrl);
	ctrl.close(&ctrl);
}
