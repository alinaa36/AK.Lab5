// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Kulish Alina <alinakulis8@gmail.com>");
MODULE_DESCRIPTION("Hello2 Module");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of 'Hello, world!' messages to print");

static int __init hello2_init(void)
{
	pr_info("Hello2 module loaded. Calling print_hello with count = %u.\n", print_count);
	print_hello(print_count);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
