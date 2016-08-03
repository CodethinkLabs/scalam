/*
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
*/

#include <assert.h>
#include "../src/scalam.h"

void test_plot_create_dataframe()
{
    printf("test_plot_create_dataframe...");

    sc_dataframe df;
    sc_population population;
    test_population_dummy(&population);
    
    plot_create_dataframe(&df, &population);

    /* Check that there are no slices yet */
    assert(df.slice_no == 0);
    
    /* Check that simulation params were copied correctly */
    assert(df.population_size == population.size);
    assert(df.mutation_rate == population.mutation_rate);
    assert(df.crossover == population.crossover);
    assert(df.rebels == population.rebels);
    assert(df.random_seed == population.random_seed);
    
    printf("Ok\n");
}

void test_plot_dataframe_slice()
{
    printf("test_plot_dataframe_slice...");

    sc_dataframe df;
    sc_population population;
    test_population_dummy(&population);
    
    plot_create_dataframe(&df, &population);
    
    /* Create 5 slices */
    plot_create_df_slice(&df, &population);
    plot_create_df_slice(&df, &population);
    plot_create_df_slice(&df, &population);
    plot_create_df_slice(&df, &population);
    plot_create_df_slice(&df, &population);
    
    assert(df.slice_no==5);
    
    int i;
    for(i=0; i<5; i++)
    {
        /* Cycle number corresponds to generation index */
        assert(df.slice[i].cycle_no==i);
        
        /* Population should remain the same as before */
        assert(df.slice[i].population_size==population.size);
        
        /* Check that all the scores are correct */
        int j;
        for(j=0; j<population.size; j++)
        {
            assert(df.slice[i].scores[j]==population_get_score(&population, j));
        }
    }

    printf("Ok\n");
}

void test_plot_save()
{
    printf("test_plot_save...");

    sc_dataframe df;
    sc_population population;
    test_population_dummy(&population);
    
    plot_create_dataframe(&df, &population);
    
    /* Create 5 slices */
    int i;
    for(i=0; i<5; i++)
    {
        plot_create_df_slice(&df, &population);
    }
  
    plot_dataframe_save(&df);
    
    printf("Manual check required\n");
    printf("\t* run : python tools/generate_plot_generation_scores.py\n");
}

void run_plot_tests()
{
    test_plot_create_dataframe();
    test_plot_dataframe_slice();
    test_plot_save();
}
