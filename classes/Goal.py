class Goal:
    ## Constructor
    # @param start The starting SystemState
    # @param reference The SystemState to get to
    def __init__(self, start, reference):
        ## What SystemState to begin at
        self.start = start

        ## What SystemState to get to
        self.reference = reference
