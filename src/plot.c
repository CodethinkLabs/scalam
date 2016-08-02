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

#include "scalam.h"

/**
 * @brief Creates a slice(chunk) of records for the current generation cycle
 * @param df The dataframe that the slice will be associated with
 * @param population Reference to the current population in this generation
 * @returns
 */
void plot_create_df_slice(sc_dataframe * df, sc_population * population)
{
    sc_dataframe_slice slice;

    /* Dataframe Fields */
    slice.population_size=population->size;
    /*slice.cycle_no=population->history_index;*/

    int i;
    /* Get the current scores for all the genomes */
    for (i=0; i<population->size; i++)
    {
        slice.scores[i]=population_get_score(population, i);
    }
    slice.cycle_no=df->slice_no;
    
    df->slice[df->slice_no]=slice;
    df->slice_no++;
}


/**
 * @brief Creates a template dataframe that is ready to be populated with results
 * @param df The dataframe reference to populate
 * @param population Reference to the current population for setting up the df
 * @returns
 */
void plot_create_dataframe(sc_dataframe * df, sc_population * population)
{
    df->slice_no=0;
    /* Dataframe params */
    df->population_size=population->size;
    df->mutation_rate=population->mutation_rate;
    df->crossover=population->crossover;
    df->rebels=population->rebels;
    df->random_seed=population->random_seed;
}


/**
 * @brief Saves the contents of the dataframe to an CSV file
 * @param df The dataframe to produce the CSV file from
 * @returns
 */
void plot_dataframe_save(sc_dataframe * df)
{
    int i,j;

    FILE * fp;
    char *filename="dataframe.csv";
    fp = fopen(filename, "r");
    if (fp)
    {
        /* Dataframe headers */
        fprintf(fp, "cycle_ix,genome_ix,score");

        /* Each cycle */
        for( i=0; i< df->slice_no; i++)
        {
            /* Each genome score for this cycle */
            for( j=0; j< df->slice[i].population_size; j++)
            {
                fprintf(fp, "%d,%d,%f\n", i, j, df->slice[i].scores[j]);
            }
        }

        fclose(fp);
    }


}
