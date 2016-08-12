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
from logger import logger

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

        commits = program.getCommits()
        self.assertTrue(commits,"There were no commits in the repo")
        self.assertTrue(commits[0] == u"b2fae77a55689afdc416a63259a5690e970c2c43")
        self.assertTrue(commits[1] == u"5983a7a2e259f9af698c8bc7b51b58445fac2eef")
        self.assertTrue(commits[2] == u"6818c65c58d066299d582b91de052d846788dcdb")
        self.assertTrue(commits[3] == u"fa928730540c2911f5228d899a86472ac28adee3")

        self.assertTrue(program.versionIndexFromCommit(u'6818c65c58d066299d582b91de052d846788dcdb') == 2)
        self.assertTrue(program.versionIndexFromCommit(u'b2fae77a55689afdc416a63259a5690e970c2c43') == 0)
        self.assertTrue(program.getNoOfCommits() == 59)

    def test_valid_name(self):
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

        self.assertTrue(program.isValidName(repo_name))
        self.assertFalse(program.isValidName("123"))
        self.assertFalse(program.isValidName(""))
