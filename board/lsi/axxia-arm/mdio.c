/*
 * mdio.c
 *
 * Basic MDIO access using the custom LSI controller.
 *
 * Copyright (C) 2009 LSI Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>

/*
  ======================================================================
  ======================================================================
  Local
  ======================================================================
  ======================================================================
*/

#undef BZ33327_WA
#define BZ33327_WA

/*
  ======================================================================
  ======================================================================
  Global
  ======================================================================
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  mdio_initialize
*/

int
mdio_initialize(void)
{
	writel(0x10, MDIO_CLK_OFFSET);
	writel(0x2c, MDIO_CLK_PERIOD);

	return 0;
}

/*
  ----------------------------------------------------------------------
  mdio_read
*/

unsigned short
mdio_read(int phy, int reg)
{
	unsigned long command = 0;
	unsigned long status;

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit. */
	status = readl(MDIO_STATUS_RD_DATA);
	status |= 0x40000000;
	writel(status, MDIO_STATUS_RD_DATA);
#endif /* BZ33327_WA */

	/* Write the command.*/
	command = 0x10000000;	/* op_code: read */
	command |= (phy & 0x1f) << 16; /* port_addr (target device) */
	command |= (reg & 0x1f) << 21; /* device_addr (target register) */
	writel(command, MDIO_CONTROL_RD_DATA);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear. */
	do {
		status = readl(MDIO_STATUS_RD_DATA);
	} while(0 != (status & 0x40000000));
#endif /* BZ33327_WA */
	/* Wait for the mdio_busy (control) bit to clear. */
	do {
		command = readl(MDIO_CONTROL_RD_DATA);
	} while(0 != (command & 0x80000000));

	return (unsigned short)(command & 0xffff);
}

/*
  ----------------------------------------------------------------------
  mdio_write
*/

void
mdio_write(int phy, int reg, unsigned short value)
{
	unsigned long command = 0;
	unsigned long status;

	/* Wait for mdio_busy (control) to be clear. */

	do {
		command = readl(MDIO_CONTROL_RD_DATA);
	} while (0 != (command & 0x80000000));

#if defined(BZ33327_WA)
	/* Set the mdio_busy (status) bit. */
	status = readl(MDIO_STATUS_RD_DATA);
	status |= 0x40000000;
	writel(status, MDIO_STATUS_RD_DATA);
#endif /* BZ33327_WA */

	/* Write the command. */
	command = 0x08000000;	/* op_code: write */
	command |= (phy & 0x1f) << 16; /* port_addr (target device) */
	command |= (reg & 0x1f) << 21; /* device_addr (target register) */
	command |= (value & 0xffff); /* value */
	writel(command, MDIO_CONTROL_RD_DATA);

#if defined(BZ33327_WA)
	/* Wait for the mdio_busy (status) bit to clear. */
	do {
		status = readl(MDIO_STATUS_RD_DATA);
	} while (0 != (status & 0x40000000));
#endif /* BZ33327_WA */

	/* Wait for the mdio_busy (control) bit to clear. */
	do {
		command = readl(MDIO_CONTROL_RD_DATA);
	} while (0 != (command & 0x80000000));

	return;
}