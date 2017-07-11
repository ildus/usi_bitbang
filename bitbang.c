/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2000, 2001, 2002, 2003  Brian S. Dean <bsd@bsdhome.com>
 * Copyright (C) 2005 Michael Holzt <kju-avr@fqdn.org>
 * Copyright (C) 2011 Darell Tan <darell.tan@gmail.com>
 * Copyright (C) 2017 Ildus Kurbangaliev <i.kurbangaliev@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* $Id: bitbang.c 1321 2014-06-13 20:07:40Z awachtler $ */


#include "bitbang.h"

/*
 * transmit and receive a byte of data to/from the AVR device
 */
static unsigned char
bitbang_txrx(IOCtrl *ctrl, unsigned char byte)
{
	int i;
	unsigned char r, b, rbyte;

	rbyte = 0;
	for (i=7; i>=0; i--)
	{
		/*
		* Write and read one bit on SPI.
		* Some notes on timing: Let T be the time it takes to do
		* one ctrl->setpin()-call resp. par clrpin()-call, then
		* - SCK is high for 2T
		* - SCK is low for 2T
		* - MOSI setuptime is 1T
		* - MOSI holdtime is 3T
		* - SCK low to MISO read is 2T to 3T
		* So we are within programming specs (expect for AT90S1200),
		* if and only if T>t_CLCL (t_CLCL=clock period of target system).
		*
		* Due to the delay introduced by "IN" and "OUT"-commands,
		* T is greater than 1us (more like 2us) on x86-architectures.
		* So programming works safely down to 1MHz target clock.
		*/

    		b = (byte >> i) & 0x01;

		/* set the data input line as desired */
		ctrl->setpin(ctrl, ctrl->pins[MOSI], b);
		ctrl->setpin(ctrl, ctrl->pins[SCK], 1);

		/*
		* read the result bit (it is either valid from a previous falling
		* edge or it is ignored in the current context)
		*/
		r = ctrl->getpin(pgm, ctrl->pins[MISO]);
		ctrl->setpin(pgm, ctrl->pins[SCK], 0);
		rbyte |= r << i;
	}

	return rbyte;
}


/*
 * transmit an AVR device command and return the results; 'cmd' and
 * 'res' must point to at least a 4 byte data buffer
 */
int
bitbang_cmd(IOCtrl *ctrl, const unsigned char *cmd, unsigned char *res)
{
	int i;

	for (i=0; i<4; i++)
		res[i] = bitbang_txrx(pgm, cmd[i]);

	return 0;
}

