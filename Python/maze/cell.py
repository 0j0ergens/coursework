import random

class Cell:
    """
    Class for representing an individual cell.
    """

    def __init__(self, row, column):
        self.row = row
        self.column = column

        self.north = None
        self.east = None
        self.south = None
        self.west = None

    def __repr__(self):
        dirs = []
        dirs.append("N" if self.north else " ")
        dirs.append("E" if self.east else " ")
        dirs.append("S" if self.south else " ")
        dirs.append("W" if self.west else " ")
        dir_str = f"<{''.join(dirs)}>"

        return f"Cell({self.row:2}, {self.column:2}){dir_str}"

    def shuffle_directions(self, directions, seed):
        """
        Takes a list of directions and a seed, and shuffles them.

        Parameters:
         - directions: list of tuples, where each tuple contains
           a string representing a direction ("N", "E", "S", "W")
           and a Cell object.
         - seed: an integer representing a random seed

        Returns: a randomly shuffled copy of the directions list.
        """
    
        assert 1 <= len(directions) <= 4, \
            "directions parameter should have between 1 and 4 elements"

        actual_seed = self.row * 1000000 + self.column * 1000 + seed
        random.seed(actual_seed)

        rv = directions[:]
        random.shuffle(rv)

        return rv

# pylint: disable=R0903
