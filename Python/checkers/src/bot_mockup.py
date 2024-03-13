from bot import RandomBot, SmartBot
"""
Tests to show smart_bot is superior to random_bot!
This integrates with Game Logic.
"""

board_record = []

def test_smart(board, red, black):
    """
    Tests the smart bot by initializing a game where
    moves are made based off smart bot and simple bot
    suggestions.

    Inputs:
        board: Checkers
        red: str
        black: str

    Returns:
        string
    """
    for i in range(1000):
        if i == 999: #maximum amount of steps so call game draw
            return board.get_winner()
        elif board._winner is None:
            try:
                start, end = red.suggest_move()
                board.make_move("RED", start, end)
            except (IndexError, TypeError):
                """
                this handles the situation when red has no moves left
                (it lost) but game logic hasn't updated until the 
                end of a turn...
                """
                board._winner = "BLACK"
                return board.get_winner()
            try:
                start2, end2 = black.suggest_move()
                board.make_move("BLACK", start2, end2)
            except (IndexError, TypeError):
                """
                this handles the situation when black has no moves left
                (it lost) but game logic hasn't updated until the 
                end of a turn...
                """
                board._winner = "RED"
                return board.get_winner()
            i += 1
        else:
            return board.get_winner()

def test_multiple_games(games, board_size):
    '''
    Given an amount of games to play and a board size,
    plays that many games between smart and random while
    alternating colors while storing the winner and smart's
    color for each game

    Inputs:
        games: int
        board size: int

    Returns:
         2-tuple: (str, str)
    '''
    for i in range(games):
        board = Checkers(board_size)
        board.set_up_board(board_size)
        if i % 2 == 0: #smart is black
            red = RandomBot(board, "RED")
            black = SmartBot(board, "BLACK")
            smart = "BLACK"
        else: #smart is red
            red = SmartBot(board, "RED")
            black = RandomBot(board, "BLACK")
            smart = "RED"
        board_record.append(((test_smart(board, red, black), smart)))
        board.reset_board()
        i += 1

def win_pct(board_record):
    '''
    Given a record of games. Computes the percentage won by SmartBot.

    Input:
        board_record: list of 2-tuples

    Returns:
        2-tuple: (str, int)
    '''
    smart_wins = 0
    games = len(board_record)
    for match in board_record:
        winner, smart_color = match
        if winner == smart_color:
            smart_wins += 1
    return 'smart win pct:', smart_wins/games

x = test_multiple_games(100,3) #edit values for preferred (games, board size)

print(win_pct(board_record))



