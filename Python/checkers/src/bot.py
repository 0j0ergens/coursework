"""
Bots for Checkers !
"""
import random

from checkers import Board, Piece, PieceColor, Checkers

class RandomBot:
    """
    Simple Bot –– makes a jump if a jump is possible (game parameters)
    otherwise picks a move at random
    """
    _board: Checkers
    _color: PieceColor

    def __init__(self, board: Checkers, color: PieceColor):
        """ Constructor
        Args:
            board: Board the bot will play on
            color: Bot's color
            opponent_color: Opponent's color
        """
        self._board = board
        self._color = color
        if self._color == 'RED':
            self._opponent_color = 'BLACK'
        else:
            self._opponent_color = 'RED'

    def suggest_move(self) -> tuple:
        """ Suggests a move
       Returns: tuple (starting location, suggested end location)

       Selects random key S (starting location for a random piece), value pair
       (list of possible ending locations for that piece) from possible moves.
       since values are lists of possible moves, again select a random move M
       and output (key(M), M). Takes a jump if it has to.
       """

        simple_bot_moves = []
        max_jump_length, max_jump = check_for_jumps(self._board, self._color, simple_bot_moves)
        if max_jump_length > 1:
            starting_loc, jump_steps = max_jump
            ending_loc = jump_steps[-1]
            return (starting_loc, ending_loc)
        else:
            chosen_piece, piece_moves = random.choice(simple_bot_moves)
            return (chosen_piece, random.choice(piece_moves))


class SmartBot:
    """
    Smart bot. It checks if a top priority move is available to the player and
    chooses randomly from the list of top priority moves. If no move yielding
    top priority is found, the bot moves down its priority list until it finds
    a move (or moves) which fit that priority, and then outputs a random move
    of that priority.

    Move priority from highest to lowest:

    – If there is a jump available, takes the jump which wins
    the most pieces. (Class Req)

    - Protect threatened pieces. (Strong Formation)
        If a piece P could be jumped by the opponent on their next move, will
        move piece P' if this prevents P from being jumped.

    – Avoid captures. (Strong Formation)
        If a piece P could be jumped by the opponent on their next move, will
        move P to a location which prevents it from being jumped by that piece.

    – If a piece can move and become a king, it moves the piece. (Coronation)

    – Move to a square in the board's central columns which cannot be captured
    on opponent's next move. (Control the Center)

    – Move to a square not in the board's central columns which
    cannot be captured on opponent's next move. (Control the Center)

    – Move to a square not in the board's central columns which
    cannot be captured on opponent's next move. (Control the Center)

    – Move to a square in the board's edge columns. (Control the Center)

    – Otherwise, moves randomly into danger (a square which the opponent could
    jump on its next).

    The Smart bot strategy was designed via amalgamating the requirements for
    class with the strategies outlined on the below checkers strategy webpages:

    https://holdingthecards.com/checkers-strategy-and-tips/
        – Control the Center
    https://www.ultraboardgames.com/checkers/tips.php
        – Coronation, Control the Center, Strong Formation

        *I slightly modified 'Strong Formation'*

        Rationale:

        By prioritizing reinforcing threatened piece P by moving P' such that P
        cannot be jumped over moving P out of the way, we aim to keep a compact
        structure but are flexible enough to
        abandon a possible 'stronger', more compact formation in service of
        keeping as many our of pieces on the board as possible by moving P to a
        square where it cannot be jumped if P cannot be reinforced.

        How it works:

        Our method iterates over each element in a list of n moves and
        classifies that element's move type. It then concatenates classified moves into a
        palatable move list with moves indexed in decreasing order of priority. It then suggests
        a player take the move at [0]. If there are no palatable moves, it will move randomly.

    """
    _board: Checkers
    _color: PieceColor

    def __init__(self, board: Checkers, color: PieceColor):
        """ Constructor
        Args:
            board: Board the bot will play on
            color: Bot's color
            opponent_color: Opponent's color
        """

        self._board = board
        self._color = color
        if self._color == 'RED':
            self._opponent_color = 'BLACK'
        else:
            self._opponent_color = 'RED'

    def suggest_move(self) -> tuple:
        """ Suggests a move
        Returns: tuple (starting location, suggested end location)
        """
        smart_bot_moves = []
        opponent_moves = []
        opponent_future_captures = []
        block_jumps = []
        move_away = []
        king_moves = []
        center_moves = []
        semi_periphery_moves = []
        edge_moves = []
        danger_moves = []

        max_jump_length, max_jump = check_for_jumps(self._board, self._color, smart_bot_moves)
        if max_jump_length > 1:
            jump_start, jump_steps = max_jump
            jump_end = jump_steps[-1]
            return (jump_start, jump_end)

        opponent_jumps = check_for_jumps(self._board, self._opponent_color, opponent_moves)
        opponent_max_jump_length, opponent_max_jump = opponent_jumps
        if opponent_max_jump_length > 1:
            _, jump_steps = opponent_max_jump
            first_square_jumped = jump_steps[0]
        else:
            first_square_jumped = None

        for opponent_move in opponent_moves:
            opponent_start_loc, opponent_end_loc = opponent_move
            opponent_future_captures.append(find_future_captures(opponent_start_loc, opponent_end_loc))
        future_capture_start = [new_start_loc for new_start_loc, _ in opponent_future_captures]
        future_capture_end = [new_end_loc for _, new_end_loc in opponent_future_captures]
        for move in smart_bot_moves:
            start_loc, end_loc = move
            end_row = end_loc[0][0]
            end_column = end_loc[0][1]
            if end_loc == first_square_jumped:
                block_jumps.append((start_loc, first_square_jumped))
            elif start_loc == first_square_jumped:
                move_away.append((start_loc, end_loc))
            elif end_row == 0 and self._color == "BLACK" \
                    or end_row == self._board._nrows and self._color == "RED":
                king_moves.append((start_loc, end_loc))
            elif end_column == [0] or end_column == self._board._ncolumns:
                edge_moves.append((start_loc, end_loc))
            elif start_loc not in future_capture_end or end_loc not in future_capture_start:
                if self._board._n - 3 <= end_column <= self._board._n + 3:
                    center_moves.append((start_loc, end_loc))
                else:
                    semi_periphery_moves.append((start_loc, end_loc))
            else:
                danger_moves.append((start_loc, end_loc))
        best_moves = block_jumps + move_away + king_moves 
        ok_moves = center_moves + semi_periphery_moves + edge_moves
        ranked_moves = best_moves + ok_moves + danger_moves
        if ranked_moves == []: #no moves available
            return 'resign'
        else:
            return (ranked_moves[0][0], ranked_moves[0][1][0]) 
            #since end loc is stored in a list, had to use creative indexing...


def check_for_jumps(board, color, moves) -> tuple:
    """
    Builds a list of tuples pairing each starting location
    with the path to its end location. Also returns the maximum length
    move with that move path if a maximum length move exists.

    Inputs:
        board: Board
        color: PieceColor
        moves: list

    Returns:
        tuple: (int, list) or (int, None)
    """
    max_length = (1, None)

    for piece, move_list in board.all_possible_moves(color).items():
        if move_list is not None:
            for move in move_list:
                if len(move) > max_length[0]:
                    max_length = (len(move), (piece, move))
                elif len(move) == 1:
                    moves.append((piece, move))
    return max_length

def find_future_captures(start_loc, end_loc) -> tuple:
    """
    Given an opponent's piece's start and end locations, calculates what
    square the opponent's piece would move to if its original move
    to square X in direction D was extended 1 step in direction D
    to square X'. SmartBot stores these positions in a tuple.
    SmartBot uses this stored info in suggest_move
    to avoid suggesting moving from X' to X.

    Inputs:
        start_loc: tuple
        end_loc: tuple

    Returns:
        2-tuple of tuples: ((int, int), (int, int))
    """
    start_row, start_col = start_loc
    end_row, end_col = end_loc[0]
    if end_row > start_row:
        if end_col > start_col:
            return (end_loc, (end_row + 1, end_col + 1))
        else:
            return (end_loc, (end_row + 1, end_col - 1))
    else:
        if end_col > start_col:
            return (end_loc, (end_row - 1, end_col + 1))
        else:
            return (end_loc, (end_row - 1, end_col - 1))