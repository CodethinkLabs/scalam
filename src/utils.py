'''
  Smart search for upgrade paths
  Copyright (C) 2016 Andrew Leeming <andrew.leeming@codethink.co.uk> and
  Bob Mottram <bob.mottram@codethink.co.uk>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
'''

import os
import sys

def unify(somestr, encoding='utf-8'):
    '''
    Makes a unicode version of a (byte) string.
    '''
    
    #If we are running python3.x this shouldn't matter
    if python_version() is 3:
        return somestr
    
    
    #Checks to see if already unicode
    if isinstance(somestr, unicode):
        return somestr
    
    somestr.decode('utf-8')
    
    return somestr.decode(encoding)

def list_dirs(path, abs_path=False):
    '''
    Fetches the list of sub-directories in a path. Only 1 level is searched
    '''
    
    dir_list=[]
    
    #Search the current path. Add any directories to the dir_list
    for f in os.listdir(path):
        if f in ['.','..']:
            continue
        if os.path.isdir(path):
            #If absolute paths are wanted
            if abs_path:
                dir_list.append(os.path.join(os.getcwd(),f))
            #else just record the relative path/directory name
            else:
                dir_list.append(f)
    
    return dir_list            
    
def list2str(lst):
    '''
    Simple helper function to convert a list of objects to a string
    '''
    
    return "[" + (", ".join([str(l) for l in lst])) + "]"

# Lifted from http://stackoverflow.com/a/5377051
def running_inside_ipython():
    '''
    Checks if we are running inside an iPython instance
    '''
    
    try:
        __IPYTHON__
        return True
    except NameError:
        return False
    
def python_version():
    '''
    Helper function to get the major version of pyther, i.e. 2 or 3
    '''
    return sys.version_info[0]
    
def dump_system_info():
    '''
    Dumps information about the system. Helpful for debugging
    '''
    
    to_dump={}
    env_whitelist=['LANGUAGE', 'GDM_LANG', 'PATH', 'PWD', 'LOGNAME', 'DESKTOP_SESSION']

    to_dump['PID']=os.getpid()
    to_dump['argv']=sys.argv
    to_dump['python_version']=sys.version
    to_dump['python_path']=sys.path
    to_dump['iPython']=running_inside_ipython()
    
    #Populate envrironment details from the whitelist
    to_dump['env']={}
    for en in env_whitelist:
        if en in os.environ:
            to_dump['env'][en]=os.environ[en]

    return to_dump

#https://www.python.org/dev/peps/pep-0485/#proposed-implementation
def float_eq(a,b, rel_tol=1e-9, abs_tol=0.0):
    return abs(a-b) <= max( rel_tol * max(abs(a), abs(b)), abs_tol )