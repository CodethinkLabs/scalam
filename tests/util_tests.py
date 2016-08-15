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
import unittest

sys.path.insert(0, "../src/")

from utils import *

class TestUtils(unittest.TestCase):

    def test_unify(self):
        # If running in python 2.7
        byte_array="Hello world!"

        resp=unify(byte_array)

        # resp should be encoded correctly here
        self.assertTrue(isinstance(resp,str))

        self.assertTrue(resp=="Hello world!")
        
        # Check that higher valued unicode char survive
        unicode_snowman=u"☃"
        self.assertTrue(unify(unicode_snowman)==u"☃")
        
    def test_float_eq(self):
        
        self.assertTrue(float_eq(1/3, 0.333, 1e-3))
        self.assertFalse(float_eq(1/3, 0.333, 1e-4))