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

def unify(somestr, encoding='utf-8'):
    '''
    Makes a unicode version of a (byte) string.
    '''
    
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
    return "[" + (", ".join([unicode(l) for l in lst])) + "]"