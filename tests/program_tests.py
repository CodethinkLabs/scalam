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

class TestProgram(unittest.TestCase):

    def test_init(self):
        repo_dir=tempfile.mkdtemp('.scalam')
        repo_url="https://github.com/CodethinkLabs/frepo"
        repo_name="frepo"

        # Create the git instance and clone
        gtype=GitType(repo_url,repo_dir)

        # Missing name param
        try:
            program=Program(repo=gtype)
        except TypeError:
            self.assertTrue(False)

        program=Program(repo=gtype,name=repo_name)

    def test_head(self):
        expected_head="5b2a7bffd0a7f564f55977a72429f36d0cdc9eaa"

        repo_dir=tempfile.mkdtemp('.scalam')
        repo_url="https://github.com/CodethinkLabs/frepo"
        repo_name="frepo"

        # Create the git instance and clone
        gtype=GitType(repo_url,repo_dir)

        # Missing name param
        try:
            program=Program(repo=gtype)
        except TypeError:
            self.assertTrue(False)

        program=Program(repo=gtype,name=repo_name)

        # checkout to the expected head
        program.checkout(expected_head)

        # get the head commit
        self.assertTrue(program.getCurrentHead() == expected_head)

    def test_versions_from_git(self):
        expected_head="5b2a7bffd0a7f564f55977a72429f36d0cdc9eaa"
        repo_dir=tempfile.mkdtemp('.scalam')
        repo_url="https://github.com/CodethinkLabs/frepo"
        repo_name="frepo"

        # Create the git instance and clone
        gtype=GitType(repo_url,repo_dir)

        # Missing name param
        try:
            program=Program(repo=gtype)
        except TypeError:
            self.assertTrue(False)

        program=Program(repo=gtype,name=repo_name)

        # checkout to the expected head
        program.checkout(expected_head)

        versions = program.getVersions()
        self.assertTrue(versions[0] == u"5b2a7bffd0a7f564f55977a72429f36d0cdc9eaa")
        self.assertTrue(versions[1] == u"618e913171d2cf8e731bc0c4ab4516f395dddba0")
        self.assertTrue(versions[2] == u"7e251622aaf6bfb85fad018985671c185ceccdd8")
        self.assertTrue(versions[3] == u"a02b369a75fbb20bb79908cbb64447538c2fedec")

    def test_valid_name(self):
        self.assertTrue(True)
