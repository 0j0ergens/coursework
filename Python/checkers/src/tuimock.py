from enum import Enum
import numpy as np

PieceColor = Enum("PieceColor", ["RED", "BLACK"])
"""
Enum type for representing piece colors.
"""

class Piece:
    """
    Class for representing a board piece
    """
    def __init__(self, color: PieceColor):  ##good
        self.is_king = False
        self.color = color
        self.loc = None 


class Board:
    """
    Class for representing a board
    """
    def __init__(self, row, column, n):  ##good
        """
        Constructor for the Board class
        Args:
          n (int): the given amount of rows to fill a color
          row (int): the given row, if checkers board: row = 2 * n + 2
          column (int): the given column, if checkers board: column = 2 * n + 2
        """
        self._n = n 
        self._nrows = row 
        self._ncolumns = column
        self._board = np.full((row, column), None)
        self._winner = None
    
    def __str__(self):  ##good
        """
        Returns:
          a string representation of the board. In this specific stage, it is
          returning a numpy array of zeroes to show that the tui can call upon
          a board construction.
        """
        return np.zeros(shape=(self._nrows, self._ncolumns))
        
        # board_rep = ""

        
        # for row in self._board:
        #     row_string = ""
        #     for col in row:
        #         if col == None:
        #             row_string += " "
        #         elif col.color == "RED":
        #             row_string += "R"
        #         else:
        #             row_string += "B"
        #     board_rep += row_string + "\n"

        # print(board_rep)


    def set_up_board(self, n):  ##good
        """
        This method initializes and sets up the pieces within the board: 
          First, it fills the top [0, n] rows with red
          Second, it fills the bottom [rows, rows - n] rows with black 
          Only insert a piece if square is black: when (row + col) is odd 
        Args:
          n (int): the given amount of rows to fill a color
        returns:
          nothing, just changes the content of the numpy array: self._board
        """ 
        for r, row in enumerate(self._board[0: n]):
          for c, column in enumerate(row):
            if (r + c)%2 != 0:
              new_piece = Piece("RED")
              new_piece.location = (r, c)
              self._board[r, c] = new_piece

        l_bound = self._nrows - n
        for r, row in enumerate(self._board[l_bound:]):
          for c, column in enumerate(row):
            if ((l_bound + r) + c)%2 != 0:
              new_piece = Piece("BLACK")
              new_piece.location = ((l_bound + r), c)
              self._board[(l_bound + r), c] = new_piece
        
        print(self._board)

    def piece_valid_moves(self, start_loc): ## moved this to board
        """
        This method checks all the potenital moves of one piece based on its
        current location:
          First, determine row and column coordiantes from self.loc attribute, as
          well as king status and the color. This will determine direction for 
          the move.
          Second, check diagonal squares for simple moves and record end locations.
          Third, if jumps are valid and record the end location. (For multi jumps,
          record intermediate jumps)
          Note* only include moves of the highest weight
            Ex) if jump is possible, don't include simple moves
        
        Args:
          piece (obj): the given piece object
        
        return:
          WE STILL NEED TO FIGURE THIS OUT
          but one move will be a list of tuple location that demonstarte steps 
          of the move until ending location
          ??
        """
        moves = {(2, 1): [(3, 0), (3, 2)], (2, 3): [(3, 2), (3, 4)], (2, 5): [(3, 4), (3, 6)], (2, 7): [(3, 6)]}

        return moves
       

   

