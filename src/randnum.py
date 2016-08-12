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

class RandNum:
    def __init__(self, seed=111):
        self.seed = seed

    def _lehmer(self, v):
        return v * 279470273 % 4294967291

    def next(self):
        v = self._lehmer(self.seed)

        if v == 0:
            v = self.seed;
            while self._lehmer(v) == 0:
                v = v + 1;
        self.seed = v;
        return abs(v);
