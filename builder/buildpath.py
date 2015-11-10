###############################################################################
# $Id: buildpath.py 504 2015-11-06 13:31:24Z klugeflo $
###############################################################################

import data
import os
import shutil

from log import *

###############################################################################

def ensureDirectoryExists(path):
    if os.path.exists(path):
        pass
    else:
        os.mkdir(path)

###############################################################################

def ensureCleanDirectoryExists(path):
    if os.path.exists(path):
        shutil.rmtree(path)
    os.mkdir(path)

###############################################################################

def makePath(platform, app):
    return data.BUILD_PATH_BASE + '/' + platform + '-' + app

###############################################################################


###############################################################################


###############################################################################


###############################################################################

def ensureBuildPath(platform, app):
    path = makePath(platform, app)
    ensureCleanDirectoryExists(path)
    ensureDirectoryExists(path + '/hal')
    ensureDirectoryExists(path + '/hal-' + app)
    ensureDirectoryExists(path + '/' + app)
    # TODO: write Makefile
    return path

###############################################################################

def writeMakefile(prog, platform, app, suppDefs, log=False, debug=False, perf=False, speed=data.DEFAULT_SPEED):
    """Create the Makefile
    platform -- Platform name
    app -- application name
    suppDefs -- list with additional definitions
    """
    pMakefile = makePath(platform, app) + '/Makefile'
    info("Write Makefile to " + pMakefile)
    with open(pMakefile, 'w') as makefile:
        makefile.write("# Makefile for building " + app + " on platform "
                       + platform + "\n")
        makefile.write("# This file was created by " + prog + "\n")
        makefile.write("\n")
        makefile.write("ARCH = " + platform + "\n")
        makefile.write("APP = " + app + "\n")
        makefile.write("BASE = " + data.BUILD_PATH_REL_BASE + "\n")
        makefile.write("CPPFLAGS += -D__SPEED__" + speed + "\n")
        if (log):
            makefile.write("CPPFLAGS += -D__LOG__\n")
        if (debug):
            makefile.write("CPPFLAGS += -D__DEBUG__\n")
        if (perf):
            makefile.write("CPPFLAGS += -D__PERF__\n")
        makefile.write("\n")
        for suppDef in suppDefs:
            makefile.write(suppDef + "\n")
        makefile.write("\n")
        makefile.write("include $(BASE)/conf/build.mk\n")
        

    

###############################################################################
