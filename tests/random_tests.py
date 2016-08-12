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
import math
import unittest

sys.path.insert(0, "../src/")

from randnum import *

class TestRandom(unittest.TestCase):

    def test_rand(self):
        r = RandNum(30)

        self.assertTrue(r.next() == 4089140899)
        self.assertTrue(r.next() == 1526564672)
        self.assertTrue(r.next() == 2339728728)
        self.assertTrue(r.next() == 2611462746)
        self.assertTrue(r.next() == 2685376303)
        self.assertTrue(r.next() == 3747470155)

    def test_distribution(self):
        r = RandNum(31)

        buckets = 16
        bucket = [0] * buckets

        for i in range(10000):
            index=r.next()%buckets
            bucket[index] = bucket[index] + 1

        # check that each bucket has some hits
        min_hits=bucket[0]
        for i in range(1, buckets):
            if bucket[i] < min_hits:
                min_hits = bucket[i]
        self.assertTrue(min_hits > 200)

        # get the mean
        mean = 0
        for i in range(buckets):
            mean = mean + bucket[i]
        mean = mean / buckets
        self.assertTrue(mean > 300)

        # get the variance as a percentage of the mean
        variance = 0
        for i in range(buckets):
            variance = variance + ((bucket[i] - mean)*(bucket[i] - mean))
        variance = math.sqrt(variance / buckets) * 100 / mean
        self.assertTrue(variance < 5)
