/*
 * i2c.c
 *
 * Basic I2C access using the custom LSI controller.
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
#include <i2c.h>
#include <asm/io.h>

/*
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
*/

#define SWAP32(value) ((((value) & 0x000000ff) << 24) | \
                      (((value) & 0x0000ff00) <<  8)  | \
                      (((value) & 0x00ff0000) >>  8)  | \
                      (((value) & 0xff000000) >> 24))

#define I2C_STATUS_READ_DELAY 10000
#define I2C_MAX_TX_RETRIES 20
#define I2C_SINGLE_WRITE_SIZE 7

static unsigned long bus_speed = 1;
static unsigned long mcc_value = 1;
static int initialized = -1;
static int i2c_bus_num = -1;

/*
  -------------------------------------------------------------------------------
  _i2c_write
*/

static int
_i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr;
	unsigned int bus_num;

	debug("chip=0x%x/%d addr=%u alen=%d len=%d\n",
	      chip, chip, addr, alen, len);
	i2c_addr = I2C0;

#ifdef CONFIG_I2C_MULTI_BUS
	bus_num = i2c_get_bus_num();
	if (bus_num == 0) {
		i2c_addr = I2C0;
	} else if (i2c_get_bus_num == 1) {
		i2c_addr = I2C1;
	} else {
		printf("Unsupport bus num = %d, only 0 and 1 are supported\n");
		return -1;
	}
#endif

	while (0 < len) {
		unsigned long status;
		unsigned long control;
		unsigned long value[2] = {0, 0};
		uchar *input = (uchar *)value;
		int this_len;
		int i;
		int retries;

		if (I2C_SINGLE_WRITE_SIZE <= len)
			this_len = I2C_SINGLE_WRITE_SIZE;
		else
			this_len = len;

		++this_len;
		debug("len=%d this_len=%d addr=%d buffer=0x%p\n",
			    len, this_len, addr, buffer);

		/* stop, moc, mma */
		if (2 == alen)
			writel(0x20000580, i2c_addr + I2C_MTC);
		else
			writel(0x20000500, i2c_addr + I2C_MTC);

		/* constants for clocks... */
		writel(mcc_value, i2c_addr + I2C_MCC);
		writel(0x00800000, i2c_addr + I2C_MSTSHC);
		writel(0x00000080, i2c_addr + I2C_MSPSHC);
		writel(0x00140014, i2c_addr + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			writel(0x20000100, i2c_addr + I2C_MTC);
		else
			writel(0x20000180, i2c_addr + I2C_MTC);

		writel(chip, i2c_addr + I2C_MSLVADDR);

		memset(input, 0, sizeof(input));
		debug("buffer[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "input[]  = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
			    buffer[0], buffer[1], buffer[2], buffer[3],
			    buffer[4], buffer[5], buffer[6], buffer[7],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7]);
		input[(8 - this_len)] = addr;
		debug("this_len=%d input[%d]=0x%x\n",
			    this_len, (8 - this_len), input[(8 - this_len)]);

		for (i = (8 - this_len + 1); i < 8; ++i) {
			input[i] = *buffer++;
			debug("input[%d]=0x%x\n", i, input[i]);
		}

		debug("buffer[] = "
		      "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
		      "input[]  = "
		      "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
		      "value[] = "
		      "{0x%08lx 0x%08lx}\n",
		      buffer[0], buffer[1], buffer[2], buffer[3],
		      buffer[4], buffer[5], buffer[6], buffer[7],
		      input[0], input[1], input[2], input[3],
		      input[4], input[5], input[6], input[7],
		      value[0], value[1]);
		writel(value[1], i2c_addr + I2C_TXD0);
		writel(value[0], i2c_addr + I2C_TXD1);

		/* stop, mma, this_len bytes, tr */
		if (2 == alen)
			control = 0x20000181 | (this_len << 1);
		else
			control = 0x20000101 | (this_len << 1);

		writel(control, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = readl(i2c_addr + I2C_MTS);
			--retries;
		} while ((0 == status) && (0 < retries));

		if ((1 != status) || (0 == retries))
			return -1;

		--this_len;
		len -= this_len;
		addr += this_len;
	}

	return 0;
}

/*
  ===============================================================================
  ===============================================================================
  Global
  ===============================================================================
  ===============================================================================
*/

/*
  -------------------------------------------------------------------------------
  i2c_init
*/

void
i2c_init(int speed, int slaveadd)
{
	i2c_set_bus_speed(speed);
	initialized = 1;

	return;
}

#ifdef CONFIG_I2C_MULTI_BUS
int i2c_set_bus_num(unsigned int bus)
{
	unsigned long load_value;

	load_value = 49;

	if (bus < CONFIG_SYS_MAX_I2C_BUS) {
		i2c_bus_num = bus;
		i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
	} else {
		return -1;
	}
	return 0;
}

unsigned int i2c_get_bus_num(void)
{
	if (i2c_bus_num == -1) {
		i2c_bus_num = 0;
	}
	return i2c_bus_num;
}
#endif
                                 


/*
  -------------------------------------------------------------------------------
  i2c_set_bus_speed
*/

int
i2c_set_bus_speed(unsigned int speed)
{
	unsigned long per_clock;
	unsigned long divisor;
	unsigned long load_value;

	load_value = 49;

#ifdef CONFIG_I2C_MULTI_BUS
	if (i2c_get_bus_num() == 0) {
		printf("setting TIMER0\n");
		writel(0, (TIMER0 + TIMER_CONTROL));
		writel(load_value, (TIMER0 + TIMER_LOAD));
		writel(load_value, (TIMER0 + TIMER_VALUE));
		writel(0xc0, (TIMER0 + TIMER_CONTROL));
	} else if (i2c_get_bus_num() == 1) {
		printf("setting TIMER1\n");
		writel(0, (TIMER1 + TIMER_CONTROL));
		writel(load_value, (TIMER1 + TIMER_LOAD));
		writel(load_value, (TIMER1 + TIMER_VALUE));
		writel(0xc0, (TIMER1 + TIMER_CONTROL));
	}
#else
	printf("setting TIMER1\n");
	writel(0, (TIMER1 + TIMER_CONTROL));
	writel(load_value, (TIMER1 + TIMER_LOAD));
	writel(load_value, (TIMER1 + TIMER_VALUE));
	writel(0xc0, (TIMER1 + TIMER_CONTROL));
#endif

	do {
		for (;;) {
			int rc;

			rc = acp_clock_get(clock_peripheral, &per_clock);

			if (0 == rc) {
				per_clock *= 1000;
				break;
			}
		}
	} while (0 == per_clock);

	divisor = per_clock / speed;

	/*
	  High and low clocks can each last up to 1023 input clocks.
	  So, the maximum divisor would be 2046 (BUT, 2044 is the
	  highest value that works...).
	*/

#define I2C_MAXIMUM_DIVISOR 2044

	if ((I2C_MAXIMUM_DIVISOR < divisor) ||
	    (0 == speed)) {
		printf("Minimum Available Speed is %lu\n",
		       (per_clock / I2C_MAXIMUM_DIVISOR));
		return -1;
	}

	mcc_value = (divisor / 2);
	mcc_value |= ((divisor - mcc_value) << 16);
	bus_speed = per_clock /
		((mcc_value & 0x3ff) + ((mcc_value & 0x03ff0000) >> 16));
	debug("per_clock=%lu divisor=%lu mcc_value=0x%x bus_speed=%lu\n",
		    per_clock, divisor, mcc_value, bus_speed);

	return 0;
}

/*
  -------------------------------------------------------------------------------
  i2c_get_bus_speed
*/

unsigned int
i2c_get_bus_speed(void)
{
	if (0 == initialized) {
		printf("I2C has not been initialized!\n");
		return 0;
	}

	return bus_speed;
}

/*
  -------------------------------------------------------------------------------
  i2c_probe
*/

int
i2c_probe(uchar chip)
{
	uchar buffer[8];
	int rc;

	if (0 == initialized)
		return -1;

	memset(buffer, 0, sizeof(buffer));
	rc = i2c_read(chip, 0, 1, buffer, 4);

	if (0 == rc)
		return 0;

	return -1;
}

/*
  -------------------------------------------------------------------------------
  i2c_read
*/

int
i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr;
	unsigned int bus_num;

	if (0 == initialized)
		return -1;

	if (0 == alen) {
		printf("Unsupported address length!  "
		       "Only .1 and .2 are supported.\n");
		return -1;
	}

	i2c_addr = I2C0;

#ifdef CONFIG_I2C_MULTI_BUS
	bus_num = i2c_get_bus_num();
	if (bus_num == 0) {
		i2c_addr = I2C0;
	} else if (bus_num == 1) {
		i2c_addr = I2C1;
	} else {
		printf("Unsupported bus num = %d, only 0 and 1 are supported\n", bus_num);
		return -1;
	}
#endif
	
	

	debug("chip=0x%x/%d addr=%u alen=%d len=%d\n",
		    chip, chip, addr, alen, len);

	while (0 < len) {
		unsigned long status;
		unsigned long value[2];
		uchar *input = (uchar *)value;
		int this_len;
		int retries;

		if (8 <= len)
			this_len = 8;
		else
			this_len = len;

		/* stop, moc, mma */
		if (2 == alen)
			writel(0x20000580, i2c_addr + I2C_MTC);
		else
			writel(0x20000500, i2c_addr + I2C_MTC);

		/* constants for clocks... */
		writel(mcc_value, i2c_addr + I2C_MCC);
		writel(0x00800000, i2c_addr + I2C_MSTSHC);
		writel(0x00000080, i2c_addr + I2C_MSPSHC);
		writel(0x00140014, i2c_addr + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			writel(0x20000180, i2c_addr + I2C_MTC);
		else
			writel(0x20000100, i2c_addr + I2C_MTC);

		writel(chip, i2c_addr + I2C_MSLVADDR);

		writel(addr, i2c_addr + I2C_TXD0);
		writel(0x00000000, i2c_addr + I2C_TXD1);

		/* stop, mma, one byte, tr */
		if (2 == alen)
			writel(0x20000183, i2c_addr + I2C_MTC);
		else
			writel(0x20000103, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = readl(i2c_addr + I2C_MTS);
			--retries;
		} while ((0 == status) && (0 < retries));

		if ((1 != status) || (0 == retries))
			return -1;

		if (2 == alen)
			writel(0x20000580, i2c_addr + I2C_MTC);
		else
			writel(0x20000500, i2c_addr + I2C_MTC);

		writel(mcc_value, i2c_addr + I2C_MCC);
		writel(0x00800000, i2c_addr + I2C_MSTSHC);
		writel(0x00000080, i2c_addr + I2C_MSPSHC);
		writel(0x00140014, i2c_addr + I2C_MDSHC);
		writel(0x00000000, i2c_addr + I2C_MIE);

		if (2 == alen)
			writel(0x20000180, i2c_addr + I2C_MTC);
		else
			writel(0x20000100, i2c_addr + I2C_MTC);

		writel(chip, i2c_addr + I2C_MSLVADDR);
		writel((this_len << 1) | 1, i2c_addr + I2C_MRC);
		writel(0x20000301, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		do {
			udelay(I2C_STATUS_READ_DELAY);
			status = readl(i2c_addr + I2C_MRS);
		} while (1 != (status & 1));

		if (1 != (status & 0x3))
			return -1;

		value[1] = readl(i2c_addr + I2C_RXD0);
		value[0] = readl(i2c_addr + I2C_RXD1);
		debug("value[] = {0x%lx 0x%lx}\n"
			    "input[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
			    value[0], value[1],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7]);
		input += (8 - this_len);
		memcpy(buffer, input, this_len);
		len -= this_len;
		buffer += this_len;
		addr += this_len;
	}

	return 0;
}

/*
  -------------------------------------------------------------------------------
  i2c_write
*/

#define CHUNK_SIZE 4

int
i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	int rc;

	if (0 == initialized)
		return -1;

	while (CHUNK_SIZE < len) {
		rc = _i2c_write(chip, addr, alen, buffer, CHUNK_SIZE);

		if (0 != rc)
			return rc;

		addr += CHUNK_SIZE;
		buffer += CHUNK_SIZE;
		len -= CHUNK_SIZE;
	}

	return _i2c_write(chip, addr, alen, buffer, len);
}