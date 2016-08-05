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
import seaborn as sns

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


df=pd.DataFrame.from_csv('dataframe.csv', index_col=None);

sns.set_style("whitegrid")

means=df.groupby('cycle_ix').score.mean()
sns.plt.scatter(y=means.values, x=means.index)

ax=plt.gca()
ax.set_xlabel("Generation iteration")
ax.set_ylabel("Score")
ax.set_title("Mean score over x generations (mutation=??, rebel=??, ...)")

majorLocator   = ticker.MultipleLocator(5)
majorFormatter = ticker.FormatStrFormatter('%d')
minorLocator   = ticker.MultipleLocator(1)

ax.xaxis.set_major_locator(majorLocator)
ax.xaxis.set_major_formatter(majorFormatter)
ax.xaxis.set_minor_locator(minorLocator)

sns.plt.show()