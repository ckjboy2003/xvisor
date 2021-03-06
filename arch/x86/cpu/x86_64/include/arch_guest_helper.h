/*
 * Copyright (c) 2014 Himanshu Chauhan.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @author: Himanshu Chauhan <hschauhan@nulltrace.org>
 * @brief: Architecture specific guest handling.
 */

#ifndef __ARCH_GUEST_HELPER_H_
#define __ARCH_GUEST_HELPER_H_

#include <cpu_vm.h>
#include <emu/rtc/mc146818rtc.h>
#include <emu/i8259.h>

#define GUEST_HALT_SW_CODE	0x80
/* When CPU exited from VM mode for VMM to handle */
#define GUEST_VM_EXIT_SW_CODE	0x81

/*! \brief x86 Guest private information
 *
 * This contains the private information for x86
 * specific guest.
 */
struct x86_guest_priv {
	/**< List of all PICs associated with guest. Guest code is not directly
	 * know about any of the fields. PIC emulator will set this and query
	 * when required.
	 */
	void *pic_list;
	struct page_table *g_npt; /**< Guest's nested page table */
	struct cmos_rtc_state *rtc_cmos;
	struct i8259_state *master_pic;
	u64 tot_ram_sz;
};

/*!def x86_guest_priv(guest) is to access guest private information */
#define x86_guest_priv(guest) ((struct x86_guest_priv *)(guest->arch_priv))

extern int gva_to_gpa(struct vcpu_hw_context *context, virtual_addr_t vaddr, physical_addr_t *gpa);
extern int gpa_to_hpa(struct vcpu_hw_context *context, physical_addr_t vaddr, physical_addr_t *hpa);
extern int realmode_map_memory(struct vcpu_hw_context *context, virtual_addr_t vaddr,
			       physical_addr_t paddr, size_t size);
extern int realmode_unmap_memory(struct vcpu_hw_context *context, virtual_addr_t vaddr,
				 size_t size);
extern void arch_guest_halt(struct vmm_guest *guest);
extern void arch_guest_handle_vm_exit(struct vcpu_hw_context *context);

#endif /* __ARCH_GUEST_HELPER_H_ */
