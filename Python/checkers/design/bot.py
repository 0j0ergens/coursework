"""
Bots for Checkers
"""
import random

from checkers import Board, Piece, PieceColor

class RandomBot:
    """
    Simple Bot that just picks a move at random
    """
    _board: '<Board object>' #question about this
    _color: PieceColor
    _opponent_color: PieceColor

    def __init__(self, board: '<Board object>' , color: PieceColor,
                 opponent_color: PieceColor):
        """ Constructor
        Args:
            board: Board the bot will play on
            color: Bot's color
            opponent_color: Opponent's color
        """
        self._board = board
        self._color = color
        self._opponent_color = opponent_color

    def suggest_move(self) -> int:
        """ Suggests a move
        Returns: tuple (starting location, suggested end location)
        """
        possible_moves = board.all_possible_moves(self._color).items()
        chosen_piece, possible_moves = random.choice(possible_moves)
        """
        select a random key S (starting location for a random piece), value pair 
        (list of possible ending locations for that piece) from possible moves.
        since values are lists of possible moves, again select a random move M
        and output (key(M), M).
        """
        return (chosen_piece, random.choice(chosen_move))

Class SmartBot:
    """
    Smart bot. It checks if a top priority move is available to the player and 
    chooses randomly from the list of top priority moves. If no move yielding 
    top priority is found, the bot moves down its priority list until it finds
    a move (or moves) which fit that priority, and then outputs a random move 
    of that priority.
    
    Move priority from highest to lowest:
    
    – If there is a jump available, takes the jump which wins 
    the most pieces. (Class Req)
    - If it can induce a positive trade, it induces the trade which wins the 
    most pieces. (The Two For One)
        This entails making a move which forces the other player to jump and win
        x pieces, but ensures on the next move, our player can jump and win at 
        least x + 1 pieces.
    - Protect threatened pieces. (Strong Formation)
        If a piece P could be jumped by the opponent on their next move, will 
        move piece P' if this prevents P from being jumped.

    – Avoid captures. (Strong Formation)
        If a piece P could be jumped by the opponent on their next move, will 
        move P to a location which prevents it from being jumped.

    – If a piece can move and become a king, it moves the piece. (Coronation)

    – Move towards a central position. (Control the Center)

    – Move towards the edge of the board. (Control the Center)
    
    – Otherwise, moves randomly.
    
    The Smart bot strategy was designed via amalgamating the requirements for  
    class with the strategies outlined on the below checkers strategy webpages:
    
    https://holdingthecards.com/checkers-strategy-and-tips/
        – The Two For One, Control the Center
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
    """
    _board: '<Board object>' #question about this
    _color: PieceColor
    _opponent_color: PieceColor

    def __init__(self, board: '<Board object>', color: PieceColor,
                 opponent_color: PieceColor):
        """ Constructor
        Args:
            board: Board the bot will play on
            color: Bot's color
            opponent_color: Opponent's color
        """

        self._board = board
        self._color = color
        self._opponent_color = opponent_color

    def suggest_move(self) -> int:
        """ Suggests a move
        Returns: tuple (starting location, suggested end location) 
        """

        #just need to basically proiritze the moves then i am done lol
        #this was really cake
        #think ab it with an array, yeah this works well
        #hammer tm will be p easy maybe a bit tn


def simulate(board: BoardType, n: int, bots) -> None:
    """ Simulates multiple games between two bots
    Args:
        board: The board to play on
        n: The number of matches to play
        bots: Dictionary mapping piece colors to
            BotPlayer objects (the bots what will
            face off in each match)
    Returns: None
    """
    for _ in range(n):
        # Starts a new game
        board.reset_board()
        board.set_up_board(board._n)

        # The starting player is Black
        current = bots[PieceColor.BLACK]

        # While the game isn't over, make a move
        while board.get_winner is None:
            piece, location = current.bot.suggest_move()
            board.make_move(piece, location)

            # Update the player
            if current.color == PieceColor.BLACK:
                current = bots[PieceColor.RED]
            elif current.color == PieceColor.RED:
                current = bots[PieceColor.BLACK]

        # If there is a winner, add one to that
        # bot's tally
        winner = board.get_winner()
        bots[winner].wins += 1





