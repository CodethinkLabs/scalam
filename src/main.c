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

int main(int argc, char **argv)
{
    int i;

    /* If there are no arguments then show help */
    if (argc <= 1) {
        show_help();
        return 0;
    }

    /* Parse the arguments */
    for (i = 1; i < argc; i++) {
        /* show help */
        if ((strcmp(argv[i],"-h")==0) ||
            (strcmp(argv[i],"--help")==0)) {
            show_help();
            return 0;
        }
        if ((strcmp(argv[i],"-t")==0) ||
            (strcmp(argv[i],"--tests")==0)) {
            run_tests();
            return 0;
        }
        if ((strcmp(argv[i],"-r")==0) ||
            (strcmp(argv[i],"--run")==0)) {
            run_simulation();
            return 0;
        }
    }

    return 0;
}


void run_simulation()
{
    /* Possible fn args */
    int population_size=100;
    char * repos_dir = "../test-sys";
    int generation_max=10000;

    /* Init System */
    sc_system sys;
    system_create_from_repos(&sys, repos_dir);

    /* Init Goal */
    sc_goal goal;
    goal_create_latest_versions(&sys, &goal);
    float goal_score=goal_max_score(&goal);



    /* Init population */
    sc_population population;
    population_create(population_size, &population, &sys, &goal);

    /* Init Dataframe for recording output */
    sc_dataframe df;
    plot_create_dataframe(&df, &population);

    /* Start simulation */
    /* TODO init scores already set? */
    int i;
    int ret;
    for(i=0; i<generation_max; i++)
    {
        /* Record data about the population before any changes */
        plot_create_df_slice(&df, &population);

        int j;
        for(j=0; j<population.size; j++)
        {
            /* TODO
             *
             * evaluate score
             * - Run in container
             * - Record which programs instal/run/pass tests
             */
            float score=system_build(&population, j);
            printf("[%d,%d] Score = %f",i,j,score);
            
			plot_create_df_slice(&df, &population);
        }

        float highest_score = population_best_score(&population);
        if(highest_score == goal_score) /* FIXME float cmp */
        {
            /* TODO
             *
             * End condition once we have found a successful candidate.
             * Exit or keep going?
             */
            printf("A possible solution found");
        }

        ret=population_next_generation(&population);
        if(ret!=0)
        {
            /* TODO
             *
             * Handle the error condition when the next generation fails
             */
        }
    }

    /* Make sure we have a copy of the data to analyse */
    plot_dataframe_save(&df);
}
