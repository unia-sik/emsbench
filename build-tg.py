#!/usr/bin/python
# $Id: build-tg.py 505 2015-11-06 13:50:23Z klugeflo $
################################################################################

################################################################################
# Example call:
# ./build-tg.py -p stm32f4-discovery --car data/cardata.cd --cycle data/urban.ndc
#
################################################################################

import os

from builder import *

################################################################################

app = 'tg'

################################################################################

def createParser():
    myParser = parser.createDefaultParser()
    myParser.add_argument('--car', '-c',
                          #nargs=1,
                          required=True,
                          help="Car data key-value file",
                          dest='cardata')
    myParser.add_argument('--cycle', '-d',
                          #nargs=1,
                          required=True,
                          help="Driving cycle file",
                          dest='cycle')
    return myParser

################################################################################

def checkArgs(args):
    log.info("Building for platform " + args.platform)
    if args.upload == '0':
        log.info("No upload")
    else:
        log.info("Upload using options '" + args.upload + "'")

    if os.path.exists(args.cardata):
        pass
    else:
        log.error("Car data file does not exist: " + args.cardata)
        exit(1)
    log.info("Using car data from " + args.cardata)

    if os.path.exists(args.cycle):
        pass
    else:
        log.error("Driving cycle file does not exist: " + args.cycle)
        exit(1)
    log.info("Using driving cycle from " + args.cycle)
    if (args.log):
        log.info("Building with data logging")
    if (args.debug):
        log.info("Building with debug output")


################################################################################


################################################################################


################################################################################
# Now the actual building starts

# Parse arguments
parser = createParser()
args = parser.parse_args()
checkArgs(args)

# Prepare tgpp
log.status("Building trace generator preprocessor...")
state = os.system("make -C tgpp" + args.verbose);

# build arch-dep
# build BSP for tg
if data.PFMAP[args.platform].hasBsp:
    log.status("Building tg BSP...")
    state = os.system("make -C embedded/arch/" + args.platform + "/bsp" + args.verbose)
else:
    log.info("No BSP necessary")


# create tg build directory
log.status("Creating traceGenerator build directory...")
buildPath = buildpath.ensureBuildPath(args.platform, app)
suppDefs = ["SUPP_C_SRC = trace.c"]
buildpath.writeMakefile(os.path.basename(__file__), args.platform, app, suppDefs, args.log, args.debug, speed=args.speed)

# create tg input data
log.status("Creating input data for traceGenerator...")
state = os.system("tgpp/tgpp -o " + buildPath + "/trace.c " + args.cardata + " " + args.cycle + args.verbose)

# build tg
log.status("Building traceGenerator...")
state = os.system("make -C " + buildPath + args.verbose)


# Upload?
if args.upload != '0':
    log.status("Uploading using options \"" + args.upload + "\"")
    state = os.system("make upload -C " + buildPath + " " + args.upload + args.verbose)
    #...

    
