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
import os
import unittest
import shutil
import tempfile
from system import System

sys.path.insert(0, "../src/")
from program import *
from logger import logger

from utils import *

class TestSystem(unittest.TestCase):

    def test_empty(self):
        emptySystem=System()

    def test_from_path(self):
        parent_dir=tempfile.mkdtemp('.scalam')
        repo_dir=parent_dir + "/frepo"
        os.makedirs(repo_dir)
        repo_url="https://github.com/CodethinkLabs/frepo"
        repo_name="frepo"

        # Create the git instance and clone
        gtype=GitType(repo_url, repo_dir)

        sys=System(parent_dir)

        self.assertTrue(sys)
        self.assertTrue(sys.programs)
        self.assertTrue(len(sys.programs) == 1)
        self.assertTrue(sys.programs[0].name == 'frepo')

        # remove the test directory after use
        shutil.rmtree(parent_dir)

    def test_from_definitions(self):
        #TODO
        pass

    def test_from_list(self):
        #TODO
        pass

    def test_from_multiple(self):
        #TODO

        #self.assertRaises(TypeError, System(repo_dir=, definitions=, programs=))
        pass

    def test_add_program(self):
        #TODO
        pass

    def test_dependency_matrix(self):
        #TODO
        pass

    def test_clone(self):
        system1=System()

        self.assertTrue(True)
        pass
