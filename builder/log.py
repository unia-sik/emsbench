###############################################################################
# $Id: log.py 247 2015-03-18 14:25:37Z klugeflo $
###############################################################################

# https://pypi.python.org/pypi/colorama
try:
    from colorama import init
    init()
    from colorama import Fore, Back, Style
    MSG_STATUS = Fore.CYAN + Style.BRIGHT
    MSG_ERROR = Fore.RED + Style.BRIGHT
    MSG_RESET = Style.RESET_ALL
except ImportError:
    MSG_STATUS = ""
    MSG_ERROR = ""
    MSG_RESET = ""

################################################################################

def info(str):
    print(str)
    
################################################################################

def status(str):
    print(MSG_STATUS + str + MSG_RESET)

################################################################################

def error(str):
    print(MSG_ERROR + str + MSG_RESET)

################################################################################
