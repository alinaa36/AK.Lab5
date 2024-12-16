// SPDX-License-Identifier: Dual BSD/GPL
#ifndef HELLO1_H
#define HELLO1_H

#include <linux/list.h>
#include <linux/ktime.h>

struct hello_entry {
	struct list_head node;
	ktime_t timestamp;
};

void print_hello(uint count);

#endif // HELLO1_H
