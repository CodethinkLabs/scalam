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
import sys
import tempfile

sys.path.insert(0, "../src/")
from program import *

def test_basic_create():
    
    # Empty constructors
    try:
        program=Program()
    except TypeError:
        pass
    
    try:
        gtype=GitType()
    except TypeError:
        pass

    return

def test_init():
    repo_dir=tempfile.mkdtemp('.scalam')
    repo_url="https://github.com/CodethinkLabs/frepo"
    repo_name="frepo"
    
    # Create the git instance and clone
    gtype=GitType(repo_url,repo_dir)
    
    # Missing name param
    try:
        program=Program(repo=gtype)    
    except TypeError:
        pass
    
    program=Program(repo=gtype,name=repo_name)
    
    return

def test_head():
    
    expected_head="36bd65546b7d6b64b69b163c4afdfa726f752033"
    pass

def test_versions_from_git():
    pass

def test_valid_name():
    pass
