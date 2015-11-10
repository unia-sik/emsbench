#!/bin/bash
# $Id: adjust_style.sh 473 2015-10-26 13:02:06Z klugeflo $
# Format all source files of the project
# Call this script before committing anything!

if [ ! -d embedded ]
then
    echo "It seems we're not in the root of an emsbench project, exiting!"
    exit -1
fi

for f in `find embedded/ -iname '*.c' -or -iname '.h' | grep -v bsp`
do
    astyle --options=codingstyle $f
done
