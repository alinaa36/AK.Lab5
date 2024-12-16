// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Kulish Alina <alinakulis8@gmail.com>");
MODULE_DESCRIPTION("Hello1 Module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_entries);

void print_hello(uint count)
{
	int i;
	struct hello_entry *entry;

	if (count == 0) {
		pr_warn("%s: count is 0, skipping printing.\n", __func__);
		return;
	}

	for (i = 0; i < count; i++) {
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);

		entry->timestamp = ktime_get();
		list_add_tail(&entry->node, &hello_entries);
		pr_info("%s: Hello, world! (%d/%u)\n", __func__, i + 1, count);
	}
}
EXPORT_SYMBOL(print_hello);

static void cleanup_list(void)
{
	struct hello_entry *entry, *next;

	list_for_each_entry_safe(entry, next, &hello_entries, node) {
		pr_info("%s: Releasing entry with timestamp: %lld ns\n", __func__, ktime_to_ns(entry->timestamp));
		list_del(&entry->node);
		kfree(entry);
	}
}

static int __init hello1_init(void)
{
	pr_info("%s: Hello1 module loaded.\n", __func__);
	return 0;
}

static void __exit hello1_exit(void)
{
	pr_info("%s: Cleaning up Hello1 module...\n", __func__);
	cleanup_list();
	pr_info("%s: Hello1 module unloaded.\n", __func__);
}

module_init(hello1_init);
module_exit(hello1_exit);
