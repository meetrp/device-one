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
    0xffffffff
