class Genome:
    def __init__(self):
        """ The list of SystemState program versions at each step """
        self.change = []

        """ score for this sequence after evaluation """
        self.score

        """ the probability of reproduction when creating the next generation """
        self.spawning_probability

        """ seed for PRNG """
        self.random_seed
