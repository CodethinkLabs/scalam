class System:
    def __init__(self):
        """ programs within the system """

        self.program = []

        """
        2D array of log probabilities
        program X depends on program Y
        """
        self.dependency_probability = []
