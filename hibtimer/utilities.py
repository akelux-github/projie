'''
Created on 2013-11-22

@author: Rong Xiao
'''
from platform import system
from subprocess import call
import os
osname = system()

'''Each system specific module exports:
    sleep()
    hibernate()
    shutdown()
'''
if osname.find('Darwin')>=0: # OSX system
    # from hib_osx import *
    pass
elif osname.find('Linux')>=0:
    sleep = lambda: call(["pm-suspend"])
    hibernate = lambda: call(["pm-hibernate", "/h"])
    shutdown = lambda: call(["shutdown", "-h", "now"])
    admin_run = lambda argv: call(["sudo", os.sys.executable, __file__] + argv)
elif osname.find('Windows')>=0:
    sleep = lambda: call(["Rundll32.exe", "powrprof.dll,SetSuspendState", "0,1,0"]) #"User32.dll,LockWorkStation"])
    hibernate = lambda: call(["shutdown.exe", "/h"])
    shutdown = lambda: call(["shutdown.exe", "/s"])
    elevate = os.path.join(os.path.split(os.path.abspath(__file__))[0], "elevate.exe")
    pythonw = os.path.join(*(os.path.split(os.sys.executable)[0:-1] + ("pythonw.exe",)))
    # admin_run = lambda argv: call([elevate, pythonw, __file__] + argv)
    admin_run = lambda argv: os.execl(elevate, 'hibtimer', pythonw, __file__, *argv)
    # admin_run = lambda argv: check_output(["runas",  "/profile",  "/user:Administrator", "python.exe " + __file__ + " " + " ".join(argv)])
    # admin_run = lambda argv: execl(r"C:\Windows\System32\runas.exe", "/profile",  "/user:Administrator", "python.exe " + __file__ + " " + " ".join(argv))

else:
    raise Exception("Your operating system is not supported")

del osname

import time

def get_sleeptime(at):
    t1 = time.strptime(at, '%H:%M')
    t2 = time.localtime()
    
def run(at_time = '22:00' ): # need admin previlidge, run at_time every day
    from msgaction import showMsgActions
    sleeptime = get_sleeptime(at_time)
    while True:
        

        time.sleep(sleeptime)
        action = showMsgActions("The system is going to sleep now", title="Sleeping reminder", actions = ['OK', 'Hibernate', 'Shutdown', 'Postpone', 'Quit'])
        if action == 'OK':
            sleep()
        elif action == 'Hibernate':
            hibernate()
        elif action == 'Shutdown':
            shutdown()
        elif action == 'Postpone':
            sleeptime = 60 # Postpone for an hour
        else:
            return   
    
if __name__ == '__main__':
    import sys
    if len(sys.argv) > 1:
        at = sys.argv[1]
        for arg in sys.argv[1:]:
            print arg
        run(at_time = at)
    else:
        run()