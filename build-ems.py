#!/usr/bin/python
# $Id: build-ems.py 503 2015-11-06 13:07:52Z klugeflo $
################################################################################

################################################################################
# Example call:
# ./build-ems.py -p stm32f4-discovery 
#
################################################################################

import os

from builder import *

################################################################################

app = 'ems'

################################################################################


################################################################################

def createParser():
    myParser = parser.createDefaultParser()
    myParser.add_argument("-P",
                        action = "store_const", const = True,
                        default = False,
                        help = "Enable performance logging in target",
                        dest = "perf")

    return myParser

################################################################################

def checkArgs(args):
    log.info("Building for platform " + args.platform)
    if args.upload == '0':
        log.info("No upload")
    else:
        log.info("Upload using options '" + args.upload + "'")

################################################################################
# Now the actual building starts

parser = createParser()
args = parser.parse_args()
checkArgs(args)

# create ems build directory
log.status("Creating EMS build directory...")
buildPath = buildpath.ensureBuildPath(args.platform, app)
buildpath.writeMakefile(os.path.basename(__file__), args.platform, app, "", args.log, args.debug, args.perf, args.speed)

# build arch-dep
# build BSP for ems
if data.PFMAP[args.platform].hasBsp:
    log.status("Building tg BSP...")
    state = os.system("make -C embedded/arch/" + args.platform + "/bsp" + args.verbose)
else:
    log.info("No BSP necessary")

# build ems
log.status("Building EMS...")
state = os.system("make -C " + buildPath + args.verbose)


# Upload?
if args.upload != '0':
    log.status("Uploading using options \"" + args.upload + "\"")
    state = os.system("make upload -C " + buildPath + " " + args.upload + args.verbose)
    #...
