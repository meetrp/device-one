/**
 * Copyright 2013 Rp (www.meetrp.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *       http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

static int open_count = 0;      // useful to keep trace of opens
static int major = 0;           // Major # of the device
static int one_arr[PAGE_SIZE];  // array to store the '1's

// prototypes for the structure initialization succeeds below
static int one_open(struct inode *, struct file *);
static int one_close(struct inode *, struct file *);
static ssize_t one_read(struct file *, char *, size_t, loff_t *);


// structure containing the callbacks
static struct file_operations fops = {
    .owner = THIS_MODULE,       // pointer to the module struct
    .open = one_open,           // address of one_open
    .release = one_close,       // address of one_close
    .read = one_read,           // address of one_read
};


// logging
#define debug(fmt, arg...)                                          \
    printk(KERN_DEBUG "[ ONE : %-20.20s: %-3.3d ] [DBG] " fmt "\n", \
        __FUNCTION__, __LINE__, ##arg)
#define error(fmt, arg...)                                          \
    printk(KERN_ERR "[ ONE : %-20.20s: %-3.3d ] [ERR] " fmt "\n",   \
        __FUNCTION__, __LINE__, ##arg)
#define info(fmt, arg...)                                           \
    printk(KERN_INFO "[ ONE : %-20.20s: %-3.3d ] [INF] " fmt "\n",  \
        __FUNCTION__, __LINE__, ##arg)


// called when the module is loaded (through insmod or during boot process)
// very similar to main() (or a constructor in OOP)
static int __init
one_init(void)
{
    debug("registering the character device");

    major = register_chrdev(0, "one", &fops);
    if (major < 0) {
        error("Device registration failed - %d!!", major);
        return -EFAULT;
    }
    info("Device registration successful. Major #%d", major);

    debug("about to prepare the array");
    memset(one_arr, 0xFF, PAGE_SIZE);

    return 0;
}

// called when module is unloaded, similar to destructor in OOP
static void __exit
one_exit(void)
{
    if (open_count) {
        error("Unregistering the device even with #%d open files",
                open_count);
    }

    info("Unregistering the device. Major #%d", major);
    unregister_chrdev(major, "one");
    debug("done. Unregistered Successfully");
}

// caled when 'open' system call is invoked
static int
one_open(struct inode *in, struct file *fp)
{
    open_count++;
    debug("Count of open dev files #%d", open_count);

    return 0;
}

// called when 'close' is invoked
static int
one_close(struct inode *in, struct file *fp)
{
    if (! open_count) {
        error("Device close attempted while count is #%d", open_count);
        return -EFAULT;
    }

    debug("Device closed. count is #%d", open_count);
    open_count--;
    return 0;
}

// called when the 'read' system call is done on the device file
static ssize_t
one_read(struct file *fp, char *buf, size_t buf_size, loff_t *off)
{
    size_t count = 0;

    if (! buf_size) {
        debug("buf_size is ZERO!!");
        return 0;
    }

    debug("requested size #%ld", buf_size);
    while (buf_size) {
        size_t chunk = buf_size;

        if (chunk > PAGE_SIZE)
            chunk = PAGE_SIZE;

        debug("about to copy #%ld size of data", chunk);
        debug("data: 0x%x", (unsigned char)one_arr[0]);
        if (copy_to_user(buf, one_arr, chunk))
            return -EFAULT;

        buf += chunk;
        count += chunk;
        buf_size -= chunk;
    }

    debug("return #%ld", count);
    return count;
}


// module entry points
module_init(one_init);
module_exit(one_exit);

// module attributes
MODULE_LICENSE("GPL");          // This avoids 'kernel taint' warning
MODULE_DESCRIPTION("This device driver turns on every bit to '1'");
MODULE_AUTHOR("Rp <rp@meetrp.com>");
