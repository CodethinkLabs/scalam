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
import unittest

sys.path.insert(0, "../src/")
from program import *
from genome import *
from system import *
from logger import logger

class TestGenome(unittest.TestCase):
    def test_createRandom(self):
        parent_dir=tempfile.mkdtemp('.scalam')
        repo_dir=parent_dir + "/frepo"
        os.makedirs(repo_dir)
        repo_url="https://github.com/CodethinkLabs/frepo"
        repo_name="frepo"

        # Create the git instance and clone
        gtype=GitType(repo_url, repo_dir)

        # in this test the start and goal are the same
        # since we are only interested in whether
        # the genome initialises
        systemStart=System(parent_dir)
        systemGoal=systemStart.clone()
        seed = 64687
        upgradeSteps=2
        genome=Genome(systemStart, systemGoal, seed, steps=upgradeSteps)
        self.assertTrue(genome)
        self.assertTrue(genome.steps == upgradeSteps)
