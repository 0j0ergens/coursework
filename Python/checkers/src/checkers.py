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
        Constructor for the Board class 
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
        for r, row in enumerate(self._board[0: n]):
          for c, column in enumerate(row):
            if (r + c)%2 != 0:
              new_piece = Piece("RED")
              new_piece.loc = (r, c)
              self._board[r, c] = new_piece

        l_bound = self._nrows - n
        for r, row in enumerate(self._board[l_bound:]):
          for c, column in enumerate(row):
            if ((l_bound + r) + c)%2 != 0:
              new_piece = Piece("BLACK")
              new_piece.loc = ((l_bound + r), c)
              self._board[(l_bound + r), c] = new_piece


    def reset_board(self):  
      """
      This method resets the board by removing all the pieces
      Args: None
      Returns: None
      """
      self._board = np.full((self._nrows, self._ncolumns), None)


    def __str__(self):  
        """
        Returns:
          a string representation of the board
        """
        board_rep = ""

        for row in self._board:
            row_string = ""
            for col in row:
                if col == None:
                    row_string += " "
                elif col.color == "RED":
                    row_string += "R"
                else:
                    row_string += "B"
            board_rep += row_string + "\n"

        return board_rep


    def quit_game(self, color, quit):
        """
        determines if a current player quits the game

        Args:
          color (str): the given color of the player, either "RED" or "BLACK"
          quit (bool): True or False

        Returns:
            None, just changes the self._winner attribute
        """
        col = "BLACK"
        if color == "BLACK":
            col  = "RED"
            
        if quit:
            self._winner = col


    def make_move(self, color: PieceColor, starting_loc, ending_loc):
        """
        This method takes in a starting location and determines if a valid move 
        can be made to the ending location. If move possible, the method 
        executes the move:
          First, check if the location contains a piece with the _get method. 
          If not, raise an error.
          Second, determine the attributes of piece: (color, king status) and 
          check if the color matches the given color and if the ending_location 
          exists in the colors all_possible_moves method. If not, raise an error: 
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
        piece = self._get(starting_loc)
        if piece == None or piece.color != color:
          raise Exception("not valid starting location")
        
        valid_moves = self.all_possible_moves(piece.color)
    
        if valid_moves[starting_loc] == None:
          raise Exception("no valid moves for this piece")

        check = True
        move = []
        for moves in valid_moves[starting_loc]:
          if moves[-1] == ending_loc:
            check = False
            move = moves

        if check:
          raise Exception("not a valid move")

        if self._is_jump(starting_loc, ending_loc):
          for inx, step in enumerate(move):
            if inx == 0:
              captured_loc = ((starting_loc[0] + step[0]) / 2, (starting_loc[1] + step[1]) / 2)
            else:
              captured_loc = ((move[inx -1][0] + step[0]) / 2, (move[inx -1][1] + step[1]) / 2)
            self._board[int(captured_loc[0]), int(captured_loc[1])] = None

        king = False      
        if piece.is_king:
            king = True
        
        self._board[starting_loc] = None
        moved_piece = Piece(color)
        moved_piece.loc = ending_loc
        self._board[ending_loc] = moved_piece

        ##coronate
        direction = "DOWN"
        if color == "BLACK":
          direction = "UP"

        if ((direction =="UP" and ending_loc[0] == 0) or\
        (direction == "DOWN" and ending_loc[0] == (self._nrows - 1)) or king == True):
          moved_piece.is_king = True

        ##checks if someone won
        c = "RED"
        if color == "RED":
          c = "BLACK"
        self._check_for_winner(c)


    def get_winner(self):
        """
        This method returns the winner (if any) in the board
        Returns:
            Optional[PieceColor]: If there is a winner,
            return its color. Otherwise, return None.
        """
        return self._winner


    def piece_valid_moves(self, piece): 
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
            Ex) if piece can jump three times, don't include a two jump move
        
        Args:
          piece (obj): the given piece object
        
        return:
          move_list (list of list of tuples): the list of piece moves with each
          move being a list of the squares navigated in that move. Square 
          locations are represented as tuples.
          returns None if no moves are possible
        """
        jumps = []
        simple_moves = []

        if not piece.is_king:
            direction = "DOWN"
            if piece.color == "BLACK":
                direction = "UP"
            jumps = self._multi_jump_recursion(piece.loc, direction, piece.color, [], [])
            simple_moves = self._get_simple_moves(piece.loc, direction)
        else:
            jumps = self._king_jumps(piece.loc, piece.color, [], [], set())
            simple_moves = self._get_simple_moves(piece.loc, "UP")
            simple_moves += self._get_simple_moves(piece.loc, "DOWN")
        
        if jumps == None:
            if len(simple_moves) == 0:
                return None
            return simple_moves

        longest_jump = 0
        valid_moves = []
        for j in jumps:
            if len(j) > longest_jump:
                longest_jump = len(j)
                valid_moves = []
                valid_moves.append(j)
            elif len(j) == longest_jump:
                valid_moves.append(j)
        
        return valid_moves

 
    def all_possible_moves(self, color: PieceColor): 
        """
        This method determines all the possible moves for a given color.
        Iterate through the array: self._board, and for each piece with the same
        color as the given color, add the piece and its possible moves:
        (piece.get_valid_moves()), to the list of all possible moves.
        If a jump is possible for one piece, only jump moves are deemed valid
        and included in the dictionary.
        
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
        jump_possible = False
        possible_moves = {}

        for r, row in enumerate(self._board):
          for c, sqr in enumerate(row):
            if sqr != None and sqr.color == color:
                possible_moves[(r,c)] = self.piece_valid_moves(sqr)
                if self.piece_valid_moves(sqr) != None and self._is_jump(sqr.loc, self.piece_valid_moves(self._get((r,c)))[0][-1]):
                    jump_possible = True
        
        if jump_possible:
            for start, move in possible_moves.items():
                if move != None and not self._is_jump(start, move[0][-1]):
                    possible_moves[start] = None

        return possible_moves


##private methods below##


    def _check_for_winner(self, color: PieceColor): 
        """
        This method checks if possible_moves method is empty for the given color. 
        If it is, the method updates the winner attribute to reflect the winner.

        Args:
          color (str): the given color of the player, either "RED" or "BLACK"

        returns:
          nothing, just updates self._winner to reflect winning color if needed
        """
        moves = self.all_possible_moves(color)
        winner = True
        for move in moves:
          if move != None:
            winner = False

        if winner:
          c = "RED"
          if color == "RED":
            c = "BLACK"
          self._winner = c


    def _is_jump(self, starting_loc, ending_loc):
        """
        determine if a move is a jump

        Args:
            starting loc (int, int): the given start Row index and Column index
            ending loc (int, int): the given end Row index and Column index
        
        Returns:
            (bool) True if jump, false if a simple move
        """
        return abs(starting_loc[0] - ending_loc[0]) > 1


    def _get_simple_moves(self, location, direction): 
        """
        This method takes in a location and a direction and outputs the valid 
        simple moves

        Args:
            location (int, int): the given Row index and Column index
            direction (str): either "UP" or "DOWN"
        
        Returns:
            returns a List of list. Each inner list represents a move, and
            within that move their should only be one tuple to represent the
            starting location.

            if no valid moves: will return an empty list
        """
        simple_moves = []

        left_neighbor, right_neighbor = self._get_neighbors(location, direction)
        
        if left_neighbor != None:
            if self._board[left_neighbor] == None:
                simple_moves.append([left_neighbor])
        if right_neighbor != None:
            if self._board[right_neighbor] == None:
                simple_moves.append([right_neighbor])

        return simple_moves


    def _multi_jump_recursion(self, starting_loc, direction, color, path, moves): 
        """
        recursivly move through potential jumps and provides all possible jump
        sequences a (non-king) piece could make

        Args:
            starting_loc (int, int): the given Row index and Column index
            direction (str): either "UP" or "DOWN"
            color (str): the given color of the player, either "RED" or "BLACK"
            path (lst): input given from piece_valid_moves, will start as []

        Returns:
            [[(r,c),(r,c)], [(r,c), (r,c)]]
            a list of lists, the inner lists represent one possible sequence of 
            jumps that would constitute a move
        """
        left, right = self._get_neighbors(starting_loc, direction)
        left_jump = self._valid_jump(starting_loc, left, (direction, "LEFT"), color)
        right_jump = self._valid_jump(starting_loc, right, (direction, "RIGHT"), color)

        if left_jump == None and right_jump == None:
          return moves.append(path)

        else:
            if left_jump != None:
                self._multi_jump_recursion(left_jump, direction, color, path + [left_jump], moves)
            if right_jump != None:
                self._multi_jump_recursion(right_jump, direction, color, path + [right_jump], moves)
        
        return moves


    def _king_jumps(self, starting_loc, color, path, moves, previous): 
        """
        recursivly move through potential jumps and provides all possible jump
        sequences a king could make. Ensures that King does not jump to where it 
        had previously been

        Args:
            starting_loc (int, int): the given Row index and Column index
            color (str): the given color of the player, either "RED" or "BLACK"
            path (lst): input given from piece_valid_moves, will start as []

        Returns:
            [[(r,c),(r,c)], [(r,c), (r,c)]]
            a list of lists, the inner lists represent one possible sequence of 
            jumps that would constitute a move

        previous will be given as None
        """
        ##setting up the potential jumps
        up_left, up_right = self._get_neighbors(starting_loc, "UP")
        down_left, down_right = self._get_neighbors(starting_loc, "DOWN")
        u_left_jump = self._valid_jump(starting_loc, up_left, ("UP", "LEFT"), color)
        u_right_jump = self._valid_jump(starting_loc, up_right, ("UP", "RIGHT"), color)
        d_left_jump = self._valid_jump(starting_loc, down_left, ("DOWN", "LEFT"), color)
        d_right_jump = self._valid_jump(starting_loc, down_right, ("DOWN", "RIGHT"), color)

        ##base case
        if (d_left_jump == None or d_left_jump in previous) and\
         (d_right_jump == None or d_right_jump in previous) and\
          (u_left_jump == None or u_left_jump in previous) and\
          (u_right_jump == None or u_right_jump in previous):
          return moves.append(path)
                                                                 
        ##recursion
        else:
            if u_left_jump != None and u_left_jump not in previous:
                previous.add(starting_loc)
                self._king_jumps(u_left_jump, color, path + [u_left_jump], moves, previous)
            if u_right_jump != None and u_right_jump not in previous:
                previous.add(starting_loc)
                self._king_jumps(u_right_jump, color, path + [u_right_jump], moves, previous)
            if d_left_jump != None and d_left_jump not in previous:
                previous.add(starting_loc)
                self._king_jumps(d_left_jump, color, path + [d_left_jump], moves, previous)
            if d_right_jump != None and d_right_jump not in previous:
                previous.add(starting_loc)
                self._king_jumps(d_right_jump, color, path + [d_right_jump], moves, previous)

        return moves


    def _valid_jump(self, starting_loc, neighbor, direction, color): 
        """
        This method takes in a starting location, a neighbor, and a direction,
        and determines if jump over that neighbor is possible

        Args:
            location (int, int): the given Row index and Column index
            neighbor (int, int): the given Row index and Column index
            direction (str,str): the first part of tuple is "UP" or "DOWN",
            the second is either "LEFT" or "RIGHT"

        returns:
            (int, int) tuple representing end location of a valid jump. 
            if jump is not valid return None
        """
        if neighbor == None:
            return None
       
        neighbor_piece = self._get(neighbor)

        if neighbor_piece == None:
            return None

        opposite_color = "RED"
        if color == "RED":
            opposite_color = "BLACK"
        
        if direction[0] == "DOWN":
            potential_jump_loc = self._get_downward_neihbors(neighbor)
        else:
            potential_jump_loc = self._get_upward_neihbors(neighbor)

        if direction[1] == "RIGHT":
            jump_loc = potential_jump_loc[1]
        else:
            jump_loc = potential_jump_loc[0]

        if  jump_loc != None and neighbor_piece.color == opposite_color:
            if self._get(jump_loc) == None:
                return jump_loc
        
        return None


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
        r, c = location
        return self._board[r, c]
    

    def _get_neighbors(self, location, direction): 
        """
        Arg:
            location (int, int): the given Row index and Column index
            direction (str): either "UP" or "DOWN"

        returns:
            tuple of the neighbors (left, right)
            each neighbor is a tuple in itself
        """
        if direction == "UP":
            return self._get_upward_neihbors(location)
        else:
            return self._get_downward_neihbors(location)


    def _get_downward_neihbors(self, location): 
        """
        This method takes in a location and returns the valid downward neighbors 
        for that location. Returns None if the desired neighbor is not on the 
        board.

        Arg:
            location (int, int): the given Row index and Column index

        return: tuple (down_left, down_right) 
            down_left (int, int): the left neighbor in tuple form
            down_right (int, int): the right neighbor in tuple form
        """
        r, c = location

        if r == self._nrows - 1 or c == 0:
            down_left = None
        else: 
            down_left = (r + 1, c - 1)

        if r == self._nrows - 1 or c == self._ncolumns - 1:
            down_right = None
        else:
            down_right = (r + 1, c + 1)
        
        return (down_left, down_right)


    def _get_upward_neihbors(self, location):
        """
        This method takes in a location and returns the valid upward neighbors 
        for that location. Returns None if the desired neighbor is not on the 
        board.

        Arg:
            location (int, int): the given Row index and Column index

        return: tuple (up_left, up_right) 
            up_left (int, int): the left neighbor in tuple form
            up_right (int, int): the right neighbor in tuple form
        """
        r, c = location

        if r == 0 or c == 0:
            up_left = None
        else: 
            up_left = (r - 1, c - 1)

        if r == 0 or c == self._ncolumns - 1:
            up_right = None
        else:
            up_right = (r - 1, c + 1)
        
        return (up_left, up_right)   