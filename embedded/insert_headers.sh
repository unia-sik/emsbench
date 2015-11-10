#!/bin/bash
# $Id: insert_headers.sh 502 2015-11-05 14:18:19Z klugeflo $

# Usage: ${0} header file

if [ -z "${1}" -o -z "${2}" ]
then
    echo "${0} needs two arguments!"
    exit -1
fi

if [ ! -e ${1} ]
then
    echo "Header template file ${1} not found!"
    exit -1
fi

if [ ! -e ${2} ]
then
    echo "Work file ${2} not found!"
    exit -1
fi

HEADER=${1}
FILE=${2}
BACKUP="${FILE}.orig"
FILE_SHORT=`basename ${FILE}`

echo "Work file ${2} short is ${FILE_SHORT}, backup to ${BACKUP}"

mv ${FILE} ${BACKUP}
cat ${HEADER} | sed -e "s/FILE/${FILE_SHORT}/" > ${FILE}
cat ${BACKUP} >> ${FILE}

# Execution:
# for f in `cat src-ems.txt`; do ./insert_headers.sh ../header-ems.c ${f}; done
# for f in `cat src-uau.txt`; do ./insert_headers.sh ../header.c ${f}; done
