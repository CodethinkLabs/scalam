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

import pandas as pd
import numpy as np
import random

c_ix=[]
g_ix=[]
score=[]

for i in xrange(50):
    for j in xrange(100):
        c_ix.append(i)
        g_ix.append(j)
        score.append(random.uniform(i*5,200*(i/10.0)))

df=pd.DataFrame({'cycle_ix':c_ix, 'genome_ix':g_ix, 'score':score});
df.to_csv('dataframe.csv');

