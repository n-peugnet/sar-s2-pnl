# PNL TME

## To get a working linux build on a ppti pc

    tar -xvJf /usr/data/sopena/pnl/linux-4.19.3.tar.xz -C /tmp/
    cp /usr/data/sopena/pnl/linux-config-pnl /tmp/linux-4.19.3/.config
    cp /usr/data/sopena/pnl/pnl-tp.img /tmp/
    cd /tmp/linux-4.19.3
    make -j30