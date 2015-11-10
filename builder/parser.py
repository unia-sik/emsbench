###############################################################################
# $Id: parser.py 513 2015-11-10 15:38:16Z klugeflo $
###############################################################################

import argparse

import data

###############################################################################

def createDefaultParser():
    parser = argparse.ArgumentParser(description="Building of EMSBench embedded code",
                                     epilog="If a build directory already exists it will be cleaned and all previous data will be removed. If you build with -L or -D options we recommend to use only 'slow' speed (-S slow) both for tg and ems (nevertheless the behaviour of the software may differ from the version withou logging).")

    pfl = []
    for pf in data.PLATFORMS:
        pfl.append(pf.name)

    parser.add_argument("-p",
                        required = True,
                        choices = pfl,
                        help="Build for specified platform",
                        dest = "platform")

    parser.add_argument("-u",
                        action="store",
                        nargs="?",
                        const="",
                        default="0", #action = "store_const", const = 1,
                        help = "Upload to target after building, pass UPLOADOPTS to upload rules",
                        metavar="UPLOADOPTS",
                        dest="upload")

    parser.add_argument("-L",
                        action = "store_const", const = True,
                        default = False,
                        help = "Enable data logging in target",
                        dest = "log")

    parser.add_argument("-D",
                        action = "store_const", const = True,
                        default = False,
                        help = "Enable debug outputs in target",
                        dest = "debug")

    parser.add_argument("-S",
                        choices = data.SPEEDS,
                        action = "store",
                        default = data.DEFAULT_SPEED,
                        help = "Execution speed, use 'slow' for log or debug output (default is '" + data.DEFAULT_SPEED + "')",
                        dest = "speed")
    
    parser.add_argument("-v", action="store_const", const = "",
                        default="> /dev/null",
                        help="Verbose mode for building", dest="verbose")

    return parser

###############################################################################


###############################################################################
