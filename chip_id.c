#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/io.h>

#define DBGU_BASE_ADDR 		0xFFFFF200 // Debug Unit Base Address on Sam9x75
#define CHIP_ID_OFFSET 		0x40       // Offset for Chip ID
#define EXTENDED_ID_OFFSET 	0x44       // Offset for Extended ID

static void __iomem *reg_base;        // Virtual address for the base address

static ssize_t chip_id_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    uint32_t chip_id = readl(reg_base + CHIP_ID_OFFSET);       // Read Chip ID
    uint32_t extended_id = readl(reg_base + EXTENDED_ID_OFFSET); // Read Extended ID
    return sprintf(buf, "Chip ID: %#x, Extended ID: %#x\n", chip_id, extended_id);
}

static struct kobj_attribute chip_id_attr = __ATTR_RO(chip_id);

static struct kobject *chip_kobj;

static int __init chip_id_init(void) {
    int error;

    // Map the base physical address to virtual address space
    reg_base = ioremap(DBGU_BASE_ADDR, 0x300);  // Map enough memory to cover all necessary offsets
    if (!reg_base) {
        pr_err("Failed to map base address\n");
        return -ENOMEM;
    }

    // Create sysfs entry
    chip_kobj = kobject_create_and_add("chip_info", kernel_kobj);
    if (!chip_kobj) {
        iounmap(reg_base);  // Unmap on failure
        return -ENOMEM;
    }

    error = sysfs_create_file(chip_kobj, &chip_id_attr.attr);
    if (error) {
        kobject_put(chip_kobj);
        iounmap(reg_base);  // Unmap on failure
    }

    return error;
}

static void __exit chip_id_exit(void) {
    sysfs_remove_file(chip_kobj, &chip_id_attr.attr);
    kobject_put(chip_kobj);
    iounmap(reg_base);  // Unmap the register base address
}

module_init(chip_id_init);
module_exit(chip_id_exit);
MODULE_LICENSE("GPL");
