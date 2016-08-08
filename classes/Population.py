class Population:
    ## Constructor
    # @param system The System object containing program definitions
    # @param goal Goal object which defines the start and reference SystemState
    def __init__(self, system, goal):
        ## list of Genome objects
        self.individual = []

        ## in the range 0.0 -> 1.0
        self.mutation_rate = 0.1

        ## Definition of the system
        self.system = system

        ## The goal transition
        self.goal = goal

        ## seed for PRNG
        self.random_seed
