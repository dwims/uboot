/*
 * (C) Copyright 2013
 * LSI Corporation <www.lsi.com>
 * John Jacques <john.jacques@lsi.com>
 * Configuration settings for the LSI ACP development boards.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIGS_AXXIA_H
#define __CONFIGS_AXXIA_H

#define CONFIG_AXXIA

#define CONFIG_AXXIA_SERIAL

/*
 */

#define CONFIG_LSI_NCR

#ifndef __ASSEMBLY__
void ncr_tracer_enable(void);
void ncr_tracer_disable(void);
int ncr_tracer_is_enabled(void);
void ncr_sysmem_init_mode_enable(void);
void ncr_sysmem_init_mode_disable(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Parameters
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define PARAMETERS_MAGIC 0x12af34ec

#define PARAMETERS_GLOBAL_SET_VOLTAGE      0x00000001
#define PARAMETERS_GLOBAL_SET_CLOCKS       0x00000002
#define PARAMETERS_GLOBAL_SET_PEI          0x00000004
#define PARAMETERS_GLOBAL_SET_SMEM         0x00000008
#define PARAMETERS_GLOBAL_SET_CMEM         0x00000010
#define PARAMETERS_GLOBAL_ENABLE_RETENTION 0x00000020
#define PARAMETERS_GLOBAL_DISABLE_RESET    0x10000000
#define PARAMETERS_GLOBAL_RUN_CMEM_BIST    0x20000000
#define PARAMETERS_GLOBAL_RUN_SMEM_RANGES  0x40000000
#define PARAMETERS_GLOBAL_RUN_SMEM_BIST    0x80000000

#ifdef CONFIG_AXXIA_ARM

typedef struct {
	unsigned version;
	unsigned flags;
	unsigned baud_rate;
	unsigned memory_ranges[16];
	unsigned long sequence;
	char description[128];
} __attribute__((packed)) parameters_global_t;

#else  /* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned version;
	unsigned flags;
} __attribute__((packed)) parameters_global_t;

#endif	/* CONFIG_AXXIA_ARM */

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned char offsets[128];
} __attribute__((packed)) parameters_voltage_t;
#else
typedef struct {
	unsigned checksum;
	unsigned version;
	unsigned vofs;
	unsigned tvid;
	unsigned long long twait;
	unsigned VIDChecks;
	unsigned char vidLT[64];
} __attribute__((packed)) parameters_voltage_t;
#endif

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned version;
	unsigned flags;
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_csw;
	unsigned syspll_div;
	unsigned syspll_psd;
	unsigned cpupll_prms;
	unsigned cpupll_ctrl;
	unsigned cpupll_csw;
	unsigned cpupll_div;
	unsigned cpupll_psd;
	unsigned sm0pll_prms;
	unsigned sm0pll_ctrl;
	unsigned sm0pll_csw;
	unsigned sm0pll_div;
	unsigned sm0pll_psd;
	unsigned sm1pll_prms;
	unsigned sm1pll_ctrl;
	unsigned sm1pll_csw;
	unsigned sm1pll_div;
	unsigned sm1pll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_csw;
	unsigned tmpll_div;
	unsigned tmpll_psd;
	unsigned fabpll_prms;
	unsigned fabpll_ctrl;
	unsigned fabpll_csw;
	unsigned fabpll_div;
	unsigned fabpll_psd;
	unsigned nrcpinput_csw;
	unsigned nrcpinput_div;
	unsigned per_csw;
	unsigned per_div;
	unsigned emmc_csw;
	unsigned emmc_div;
	unsigned debug_csw;
	unsigned stop_csw;
} __attribute__ ((packed)) parameters_clocks_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
#ifdef CONFIG_AXXIA_25xx
	unsigned syspll_prms;
	unsigned syspll_ctrl;
	unsigned syspll_mcgc;
	unsigned syspll_mcgc1;
	unsigned syspll_psd;
	unsigned ppcpll_prms;
	unsigned ppcpll_ctrl;
	unsigned ppcpll_mcgc;
	unsigned ppcpll_mcgc1;
	unsigned ppcpll_psd;
	unsigned smpll_prms;
	unsigned smpll_ctrl;
	unsigned smpll_mcgc;
	unsigned smpll_mcgc1;
	unsigned smpll_psd;
	unsigned tmpll_prms;
	unsigned tmpll_ctrl;
	unsigned tmpll_mcgc;
	unsigned tmpll_mcgc1;
	unsigned tmpll_psd;
	unsigned per_mcgc;
	unsigned per_mcgc1;
#else
	unsigned sys_control;
	unsigned sys_lftune_upper;
	unsigned sys_lftune_lower;
	unsigned sys_fftune;
	unsigned sys_locktune;
	unsigned ppc_control;
	unsigned ppc_lftune_upper;
	unsigned ppc_lftune_lower;
	unsigned ppc_fftune;
	unsigned ppc_locktune;
	unsigned ddr0_control;
	unsigned ddr1_control;
	unsigned ddr_lftune_upper;
	unsigned ddr_lftune_lower;
	unsigned ddr_fftune;
	unsigned ddr_locktune;
#endif
} __attribute__ ((packed)) parameters_clocks_t;
#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	unsigned long version;
	unsigned long control;
} __attribute__((packed)) parameters_pciesrio_t;

typedef unsigned ncp_uint32_t;
typedef void *   ncp_dev_hdl_t;
typedef unsigned ncp_region_id_t;

typedef struct {
    unsigned char sdram_rtt_nom[4];
    unsigned char sdram_rtt_wr[4];
    unsigned char sdram_data_drv_imp[4];
    unsigned long phy_min_cal_delay;
    unsigned long phy_adr_phase_select;
    unsigned long phy_dp_io_vref_set;
    unsigned long phy_adr_io_vref_set;
    unsigned long phy_rdlvl_cmp_even;
    unsigned long phy_rdlvl_cmp_odd;
    unsigned long phy_write_align_finetune;
} __attribute__((packed)) per_mem_parms_t;

typedef struct {
	unsigned long version;
	unsigned long ddr_clock_speed;
	unsigned long auto_detect;
	unsigned long num_interfaces;
	unsigned long num_ranks_per_interface;
	unsigned long primary_bus_width;
	unsigned long topology;
	unsigned long min_ctrl_roundtrip_delay;
	unsigned long phy_rdlat;
	unsigned long added_rank_switch_delay;
	unsigned long zqcs_interval;
	unsigned long enableECC;
	unsigned long enable_runtime_updates;
	unsigned long dramPrechargePolicy;
	unsigned long open_page_size;
	unsigned long syscacheControl;
	unsigned long sdram_device_density;
	unsigned long sdram_device_width;
	unsigned long CAS_latency;
	unsigned long CAS_write_latency;
	unsigned long address_mirroring;
	unsigned long registeredDIMM;
	unsigned long rdimm_ctl_0_0;
	unsigned long rdimm_ctl_0_1;
	unsigned long rdimm_misc;
	unsigned long write_ODT_ctl;
	unsigned long read_ODT_ctl;
	unsigned long single_bit_mpr;
	unsigned long high_temp_dram;

	per_mem_parms_t per_mem[2];

	/* Not part of the parameters, used internally.	*/
	unsigned long ddrRetentionEnable;
	unsigned long ddrRecovery;
	unsigned long num_bytelanes;
 	unsigned long long totalSize;
} __attribute__((packed)) parameters_mem_t;

#ifdef CONFIG_AXXIA_ARM
typedef struct {
	unsigned long magic;
	unsigned long size;
	unsigned long checksum;
	unsigned long version;
	unsigned long chipType;
	unsigned long globalOffset;
	unsigned long globalSize;
	unsigned long voltageOffset;
	unsigned long voltageSize;
	unsigned long clocksOffset;
	unsigned long clocksSize;
	unsigned long pciesrioOffset;
	unsigned long pciesrioSize;
	unsigned long systemMemoryOffset;
	unsigned long systemMemorySize;
	unsigned long classifierMemoryOffset;
	unsigned long classifierMemorySize;
	unsigned long systemMemoryRetentionOffset;
	unsigned long systemMemoryRetentionSize;
} __attribute__((packed)) parameters_header_t;
#else  /* CONFIG_AXXIA_ARM */
typedef struct {
	unsigned sysmemSize;
	unsigned sysmemOffset;
	unsigned clocksSize;
	unsigned clocksOffset;
	unsigned voltageSize;
	unsigned voltageOffset;
	unsigned pciesrioSize;
	unsigned pciesrioOffset;
	unsigned globalSize;
	unsigned globalOffset;
	unsigned version;
	unsigned checksum;
	unsigned size;
	unsigned magic;
} __attribute__((packed)) parameters_header_t;
#endif	/* CONFIG_AXXIA_ARM */

typedef struct {
	parameters_header_t *header;
	parameters_global_t *global;
	parameters_voltage_t *voltage;
	parameters_clocks_t *clocks;
	parameters_pciesrio_t *pciesrio;
	parameters_mem_t *sysmem;
	parameters_mem_t *cmem;
} parameters_t;

extern parameters_header_t *header;
extern parameters_global_t *global;
extern parameters_pciesrio_t *pciesrio;
extern parameters_voltage_t *voltage;
extern parameters_clocks_t *clocks;
extern parameters_mem_t *sysmem;
extern parameters_mem_t *cmem;
#ifdef CONFIG_AXXIA_ARM
extern void *retention;
#endif

int read_parameters(void);
int write_parameters(void);

#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_LSI_PARAMETERS
#endif

#endif	/* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  Networking
  ==============================================================================
  ==============================================================================
*/

#ifndef CONFIG_SPL_BUILD

#if defined(CONFIG_AXXIA_FEMAC) || defined(CONFIG_AXXIA_EIOA)
#define CONFIG_AXXIA_NET
#define CONFIG_CMD_NET
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_LSI_MDIO
#endif

#ifndef MDIO_CLK_OFFSET_DEFAULT
#ifdef CONFIG_AXXIA_EMU
#define MDIO_CLK_OFFSET_DEFAULT 0x10
#else
#define MDIO_CLK_OFFSET_DEFAULT 0x1c
#endif
#endif

#ifndef MDIO_CLK_PERIOD_DEFAULT
#ifdef CONFIG_AXXIA_EMU
#define MDIO_CLK_PERIOD_DEFAULT 0x2c
#else
#define MDIO_CLK_PERIOD_DEFAULT 0xf0
#endif
#endif

#endif	/* CONFIG_SPL_BUILD */

/*
  ==============================================================================
  ==============================================================================
  SSP Access
  ==============================================================================
  ==============================================================================
*/

#define SSP_CR0       0x000
#define SSP_CR1       0x004
#define SSP_DR        0x008
#define SSP_SR        0x00c
#define SSP_CPSR      0x010
#define SSP_IMSC      0x014
#define SSP_RIS       0x018
#define SSP_MIS       0x01c
#define SSP_ICR       0x020
#define SSP_DMACR     0x024
#define SSP_CSR       0x030
#define SSP_PERIPHID0 0xfe0
#define SSP_PERIPHID1 0xfe4
#define SSP_PERIPHID2 0xfe8
#define SSP_PERIPHID3 0xfec
#define SSP_PCELLID0  0xff0
#define SSP_PCELLID1  0xff4
#define SSP_PCELLID2  0xff8
#define SSP_PCELLID3  0xffc

#define SSP_MAXIMUM_CLOCK 25000000

#ifndef __ASSEMBLY__
int ssp_read(void *, unsigned, unsigned);
int ssp_set_speed(unsigned *);
int ssp_init(int);
#endif

/*
  ==============================================================================
  ==============================================================================
  Clocks
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__

#define CLK_REF0 125000000

typedef enum {
	clock_system, clock_core, clock_memory, clock_peripheral,
	clock_fab, clock_treemem, clock_emmc
} acp_clock_t;

int acp_clock_get(acp_clock_t, ncp_uint32_t *);

unsigned int spi_get_per_clk(void);

#endif /* __ASSEMBLY__ */

/*
  ==============================================================================
  ==============================================================================
  System Memory
  ==============================================================================
  ==============================================================================
*/

#ifndef __ASSEMBLY__
int sysmem_reset(void);
unsigned long long sysmem_size(void);
#endif

/*
  ==============================================================================
  ==============================================================================
  Special Test
  ==============================================================================
  ==============================================================================
*/

/*#define CONFIG_SPL_MTEST*/
/*#define SM_PLL_533_MHZ*/
/*#define RUN_UNCACHED*/
/*#define RUN_NONSECURE*/
/*#define SINGLE_SMEM_MODE*/
/*#define DISPLAY_PARAMETERS*/

/*
  ==============================================================================
  ==============================================================================
  Include the Common LSI Header
  ==============================================================================
  ==============================================================================
*/

#include <configs/lsi.h>

#endif /* __CONFIGS_AXXIA_H */