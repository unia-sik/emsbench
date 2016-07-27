#!/bin/bash
# $Id: adjust_style.sh 564 2016-07-27 10:59:18Z klugeflo $
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
