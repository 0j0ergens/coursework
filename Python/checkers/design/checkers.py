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
    def __init__(self, color: PieceColor):
        self.is_king = False
        self.color = color
        self.loc = None 


class Board:
    """
    Class for representing the board
    """
    def __init__(self, row, column):
        """
        Constructor for the Board class
        Args:
          row (int): the given row
          column (int): the given column
        """
        self._board = np.full((row, column), None)


class Checkers: 
    """
    Class for representing the game checkers
    """
    def __init__(self, n):
        """
        Constructor for the Checkers class
        Args:
          n (int): the given amount of rows to fill a color
        """
        self._n = n
        self._nrows = 2 * n + 2 
        self._ncolumns = 2 * n + 2
        self._board = Board(self._nrows, self._ncolumns)._board
        self._winner = None


    def set_up_board(self, n):
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
        raise NotImplementedError


    def reset_board(self):
        """
        This method resets the board by removing all the pieces

        Args: None

        Returns: None
        """
        raise NotImplementedError


    def __str__(self):
        """
        Returns:
          a string representation of the board
        """
        raise NotImplementedError


    def make_move(self, color: PieceColor, starting_loc, ending_loc):
        """
        This method takes in a starting location and determines if a valid move 
        can be made to the ending location. If move possible, the method 
        executes the move:
          First, check if the location contains a piece with the _get method. 
          If not, raise an error.
          Second, determine the attributes of piece: (color, king status) and 
          check if the color matches the given color and if the ending_location 
          exists in the pieces get_valid_moves method. If not, raise an error: 
          "not valid move".
          Third, move the piece to the location and if jump occurs, remove
          opponents "jumped over" pieces.
          Fourth, if ending location is on pieces opposite edge, coronate the 
          piece.
          Fifth, call on get_winner with the opposite color to account for if
          this was a winning move.
        
        Args:
          color (str): the given color of the player, either "RED" or "BLACK"
          starting_loc (int, int): the given row and column coordinates of the 
            starting board square of the move
          ending_loc (int, int): the given row and column coordinates of the 
            ending board sqaure of the move 

        returns:
          nothing, just changes the content of the numpy array: self._board and 
          the moving piece attributes to reflect the move
        """
        raise NotImplementedError


    def get_winner(self): 
        """
        This method returns the winner (if any) in the board
        Returns:
            Optional[PieceColor]: If there is a winner,
            return its color. Otherwise, return None.
        """
        raise NotImplementedError
    

    def piece_valid_moves(self, piece): ## moved this to board
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
          move_list (list of list of tuples): the list of piece moves with each
          move being a list of the squares navigated in that move. Square 
          locations are represented as tuples.
        """
        raise NotImplementedError


    def all_possible_moves(self, color: PieceColor):
        """
        This method determines all the possible moves for a given color.
        Iterate through the array: self._board, and for each piece with the same
        color as the given color, add the piece and its possible moves:
        (piece.get_valid_moves()), to the list of all possible moves.
        If jumps are possible moves for a player, only shows possible moves

        Args:
          color (str): the given color of the player, either "RED" or "BLACK"

        Returns:
          moves (dict): the keys in the dictionary are tuples corresponding to 
          the start location for each piece given the inputted color. The values
          are a list of all possible moves for a given piece. Each possible move
          is a list of the steps taken to reach the end location (this accounts
          for jumps). all locations are represented as tuples so the keys are 
          a list of lists of tuples.
        """
        raise NotImplementedError


    def quit_game(self, color, quit):
        """
        determines if a current player quits the game
        Args:
          color (str): the given color of the player, either "RED" or "BLACK"
          quit (bool): True or False
        Returns:
            None, just changes the self._winner attribute
        """
        raise NotImplementedError

## some private methods below##

    def _get(self, location): 
        """
        This method gets a piece (if any) at the given location.
        
        Args:
            location (int, int): the given Row index and Column index

        Returns:
            Optional[PieceColor]: If there is a piece in the provided
            location, returns the PieceColor object at that location.
            Otherwise, returns None. 
            Also returns None if the (row, col) coordinates are not valid.
        """
        raise NotImplementedError


    def _check_for_winner(self, color: PieceColor):
        """
        This method checks if possible_moves method is empty for the given color. 
        If it is, the method updates the winner attribute to reflect the winner.

        Args:
          color (str): the given color of the player, either "RED" or "BLACK"

        returns:
          nothing, just updates self._winner to reflect winning color if needed
        """
        raise NotImplementedError



### EXAMPLES ###
"""
1. Setting up a checkers board:
    board = Checkers(n)
    board.set_up_board(n)

2. Checking for feasible move, given a piece:
    if Checkers.piece_valid_moves(piece) is not None:
        return True
    else:
        return False

3. List of all valid moves, given a color:
    return Checkers.all_possible_moves(color)

4. Getting a winner:
    return Checkers._winner()
"""