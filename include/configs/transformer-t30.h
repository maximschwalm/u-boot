/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra30-common.h"
#include "transformer-common.h"

/* VDD core PMIC */
#define CONFIG_TEGRA_VDD_CORE_TPS62361B_SET3

#ifdef CONFIG_TRANSFORMER_SPI_BOOT
#define TRANSFORMER_VOLDOWN_ACTION \
	"setenv gpio_vol_down 132;" \
	"if run check_button;" \
	"then echo Starting Fastboot protocol ...;" \
		"fastboot usb 0;"
#else
#define TRANSFORMER_VOLDOWN_ACTION \
	"setenv gpio_vol_down 131;" \
	"if run check_button;" \
	"then bootmenu;"
#endif

#define BOARD_EXTRA_ENV_SETTINGS \
	TRANSFORMER_T30_EMMC_LAYOUT \
	TRANSFORMER_DEFAULT_FILESET \
	TRANSFORMER_BOOTZ \
	TRANSFORMER_BUTTON_CHECK \
	TRANSFORMER_BOOTMENU

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	TRANSFORMER_VOLDOWN_ACTION \
	"else echo Loading from uSD...;" \
		"setenv bootdev 1;" \
		"setenv rootpart 2;" \
		TRANSFORMER_LOAD_KERNEL \
		"else echo Loading from uSD failed!;" \
			"echo Loading from eMMC...;" \
			"setenv bootdev 0;" \
			"setenv rootpart 8;" \
			TRANSFORMER_LOAD_KERNEL \
			"else echo Loading Kernel FAILED! Turning power off;" \
				"poweroff; fi;" \
		"fi;" \
	"fi;"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTA
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTA_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_CARDHU

#include "tegra-common-post.h"
#include "tegra-common-usb-gadget.h"

#endif /* __CONFIG_H */