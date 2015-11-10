###############################################################################
# $Id: data.py 503 2015-11-06 13:07:52Z klugeflo $
###############################################################################

################################################################################

class Platform:
    """Description of an embedded platform"""
    def __init__(self, _name, _hasBsp):
        self.name = _name # Platform name
        self.hasBsp = _hasBsp # set to true, if the platform has an additional BSP


PLATFORMS = [ Platform('default', False), # Host machine, use only for tg
              Platform('stm32f4-discovery', True),
              Platform('nios2', True)]

################################################################################

PFMAP = dict()
for pf in PLATFORMS:
    PFMAP[pf.name] = pf

################################################################################

BUILD_PATH_BASE = 'embedded/build'
# How to reach the embedded directory (embedded) from the build directory (embedded/build/platform-app)
BUILD_PATH_REL_BASE = '../..'

################################################################################

SPEEDS = [ 'slow', 'fast' ]
DEFAULT_SPEED = 'fast'

################################################################################


################################################################################

