from checkers import Checkers
import bot

import os
import time
from colorama import Fore

class Player:
    """
    Class to represent player in the game. 
    """
    def __init__(
        self, 
        n: int, 
        color: str,
        bot=None
        ):
        """ 
        Constructor for a player class.

        Inputs:
            n : int, identifies the player
            color: str, either red or black.
            bot: either Smartbot class, Randombot class, or None.   
        """
        self._name = f"Player {n}"
        self._color = color
        self._bot = bot

def board_str(board):
    """
    Takes a board from the checkers class, and uses it to build a string
    representation in the TUI.

    Inputs:
        board: board class

    Returns:
        string of board
    """
    board_rep = " _" * (board._nrows) + " \n"

    for row in board._board:
        row_string = "|"
        for col in row:
            if col == None:
                row_string += "_|"
            elif col.color == "RED":
                if col.is_king:
                    row_string += "R|"
                else:
                    row_string += "r|"
            else:
                if col.is_king:
                    row_string += "B|"
                else:
                    row_string += "b|"
        board_rep += row_string + "\n"
    
    return board_rep

def change_value(board: str, n: int, loc: tuple, replacement: str):
    """
    This method takes a string representation of a board and replaces an item
    at a given location with a given value.

    Inputs:
        board: string representation of board
        n: number of rows in checkers board
        loc: tuple location of value to be replaced
        replacement: string that replaces existing value in specified location

    Returns:
        string of board
    """
    pos = ((loc[0] + 1) * 2 * (n + 1)) + (loc[1] * 2) + 1
    board = board[:pos] + replacement + board[(pos + 1):]
    return board

def play_checkers():
    """
    Function that begins a game of checkers.
    """
    # Create the board
    while True:
        n_rows = input("Rows of pieces:\n")
        try:
            n_rows = int(n_rows)
            break
        except:
            print("\nInput integer values only")
            time.sleep(1.5)
            continue
    b = Checkers(n_rows)
    b.set_up_board(n_rows)
    
    #Choose players
    while True:
        with_bot = input("\nHow many players? (1 or 2)\n")
        if with_bot == '1' or with_bot == '2':
            break
        else:
            print("\nPlease choose either 1 or 2")
            time.sleep(1.5)
            continue
    if with_bot == "1":
        player1 = Player(1, "BLACK")
        while True:
            level = input("\nPlay against Random Bot (r) or Smart Bot (s)?\n")
            if level == "r":
                player2 = Player(1, "RED", bot.RandomBot(b, "RED"))
                break
            elif level == "s":
                player2 = Player(1, "RED", bot.SmartBot(b, "RED"))
                break
            else:
                print("\nPlease choose either \"r\" or \"s\"")
                time.sleep(1.5)
                continue
        print(
            "Player 1 (you): " + Fore.BLACK + "BLACK" + 
            Fore.WHITE + "\nPlayer 2 (bot): " + Fore.RED + "RED"
            )
        time.sleep(2)
        print(Fore.WHITE + "GAME START")
        time.sleep(2)
    else:
        player1 = Player(1, "BLACK")
        player2 = Player(2, "RED")
        print(
            "Player 1: " + Fore.BLACK + "BLACK" + 
            Fore.WHITE + "\nPlayer 2: " + Fore.RED + "RED"
            )
        time.sleep(2)
        print(Fore.WHITE + "GAME START")
        time.sleep(2)
   
    # The starting player is BLACK, and the number of turns are initialized.
    player = player1
    turn = 1

    # Keep playing until there is a winner:
    while True:
        os.system('clear')
        print(f"Turn {turn}")
        if player._color == "RED":
            print(Fore.RED + "RED's" + Fore.WHITE + " move")
        else:
            print(Fore.BLACK + "BLACK's" + Fore.WHITE + " move")
        time.sleep(2)
        temp_board = board_str(b)

        #Bot move
        if player._bot:
            start, end = player._bot.suggest_move()
            b.make_move(player._color, start, end)
            print(board_str(b))
            
            #Check if winner
            if b.get_winner() is not None:
                break

            print(f"Bot moved from ({start[0] + 1}, {start[1] + 1})")
            print(f"to ({end[0] + 1}, {end[1] + 1})")
            time.sleep(6)
            player = player1
            turn += 1
            continue
        
        #Show pieces that can move
        n = 1
        locs = {}
        for piece, moves in b.all_possible_moves(player._color).items():
            if moves:
                temp_board = change_value(temp_board, b._nrows, piece, str(n))
                locs[str(n)] = piece
                n += 1
        print(temp_board)
        
        #Choose piece to move
        while True:    
            p = input("Which piece would you like to move?\n")
            if p in locs.keys():
                start_loc = locs[p]
                pos_move = set()
                for square in b.all_possible_moves(player._color)[locs[p]]:
                    temp_board = change_value(
                        temp_board, b._nrows, square[-1], '?'
                        )
                    pos_move.add((square[-1][0] + 1, square[-1][1] + 1))
                print(temp_board)
                break
            else:
                print("\nPlease choose a valid piece")
                time.sleep(1.5)
                continue
        
        #Move piece
        print("Where do you want to move this piece?")
        time.sleep(1)
        while True:
            if len(pos_move) == 1:
                print("Your only choice is:")
            else:
                print("Your choices are:")
            for i in pos_move:
                print(i)
            
            choose = input("Answer in the form (<row>, <column>)\n")
            try:
                row = int(choose[1:3])
                col = int(choose[5:7])
            except:
                try:
                    row = int(choose[1:3])
                    col = int(choose[5])
                except:
                    try:
                        row = int(choose[1])
                        col = int(choose[4:6])
                    except:
                        try:
                            row = int(choose[1])
                            col = int(choose[4])
                        except:
                            print(
                                "\nMake sure your answer is in the proper form."
                                )
                            time.sleep(1.5)
                            continue            
            
            if (row, col) in pos_move:
                break
            else:
                print("\nPlease choose valid move.")
                time.sleep(1.5)
                continue
        b.make_move(player._color, start_loc, ((row - 1), (col - 1)))
        print(board_str(b))
        print("Move complete")
        time.sleep(4)

        # If there is a winner, break out of the loop
        if b.get_winner() is not None:
            break

        # Change the player for the next move
        if player._color == "BLACK":
            player = player2
        elif player._color == "RED":
            player = player1

        turn += 1

    #Print winner with winning board
    print(board_str(b))
    print(f"The winner is {player._color}!\n")
    time.sleep(1.5)

    #Replay option
    replay = input("Play again? (Y or N)\n")
    if replay == "Y":
        os.system('clear')
        play_checkers()

play_checkers()
