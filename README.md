device-one
==========

A sample character driver which upon read returns a character buffer with bit turned one.


Compilation and Installation
===========================

Assumption: You are a sudoer or a root.

Compilation and installation is handled by this script

    $> install.sh

Check /var/log/messages for:

    Sep 13 20:22:50 rp kernel: [ ONE : one_init            : 038 ] [DBG] registering the character device
    Sep 13 20:22:50 rp kernel: [ ONE : one_init            : 040 ] [DBG] return value: 247
    Sep 13 20:22:50 rp kernel: [ ONE : one_init            : 046 ] [INF] Device registration successful. Major #247
    Sep 13 20:22:50 rp kernel: [ ONE : one_init            : 047 ] [DBG] about to prepare the array


Testing
=======

The sample test code is included & compiled during make

    $> ./test
    0xff


Verification
============

Use 'dd' and 'od' to read & dump to verify the data.

    # read 1 Byte of data from /dev/ones & store it in file 'out'
    $> dd if=/dev/ones of=out bs=1 count=1
    1+0 records in
    1+0 records out
    1 byte (1 B) copied, 0.000142743 s, 7.0 kB/s

    # dump the content of 'out' file in hex mode
    $> od -t x1 out
    0000000 ff
    0000001



Blog Article about this code
============================

http://tech.meetrp.com/blog/simple-character-device-driver/
