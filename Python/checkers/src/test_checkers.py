from checkers import Board, Piece, Checkers

def test_str_representation_set_up_board_1():
    """
    check that the string representation of a set up board is correct with an
    8 x 8 board and an n value of 3.
    """
    game = Checkers(3)
    game.set_up_board(3)

    expected = " R R R R\nR R R R \n R R R R\n        \n        \nB B B B \n B B B B\nB B B B \n"

    assert print(game) == print(expected), "checks that str representation works for set up board"

def test_recursive_possible_jumps_1():
    """
    check that a given board with different possible jumpp sequences, returns 
    the proper list of paths

    this is what board looks like:
     R R R R R
    R R R R R 
     R R R R R
    R B R R R 
          
      B B     
       B   B B
    B B B B B 
     B B B B B
    B B B B B 
    """
    board = Checkers(4)
    board.set_up_board(4)
    board._board[3,2] = Piece("BLACK")
    board._board[5,2] = Piece("BLACK")
    board._board[5, 4] = Piece("BLACK")
    board._board[6, 1] = None
    board._board[6, 5] = None

    expected = [[(4, 3), (6, 1)], [(4, 3), (6, 5)]]

    assert board._multi_jump_recursion((2,1), "DOWN", "RED", [], []) == expected

def test_simple_moves_1():
    """
    check that a the simple move works for a piece on the first line of a starting 
    chekers board, 
    
    chosen piece: (2, 4)
    """
    board = Checkers(3)
    board.set_up_board(3)

    expected = [[(3, 3)], [(3, 5)]] 

    assert board._get_simple_moves((2,4), "DOWN") == expected

def test_simple_moves_2():
    """
    check that a the simple move works for a piece on the first line of a starting 
    chekers board, BUT in the corner -> so should only have one valid number
    
    chosen piece: (5, 0)
    """
    board = Checkers(3)
    board.set_up_board(3)

    expected = [[(4, 1)]] 

    assert board._get_simple_moves((5,0), "UP") == expected

def test_simple_moves_3():
    """
    check that a the simple move works for a piece on the first line of a starting 
    chekers board, BUT in the on the egde -> so no possible moves
    
    chosen piece: (0,1)
    """
    board = Checkers(3)
    board.set_up_board(3)

    expected = []

    assert board._get_simple_moves((0,1), "DOWN") == expected

def test_king_jumps_1():
    """
    check that the method provides all the possible jumps for the king. given a
    king in the middle of the board who has different potential jump routes in 
    different directions.

    chosen piece: (7,4)
    
    board:
     R R R R R R
    R R R R R R 
     R R R R R R
    R R   R R R 
     R R B R R R
            
         B B    
    B B R B   B 
     B B B B B B
    B B B B B B 
     B B B B B B
    B B B B B B    
    """
    board = Checkers(5)
    board.set_up_board(5)
    board._board[4,5] = Piece("BLACK")
    board._board[6, 5] = Piece("BLACK")
    board._board[6, 7] = Piece("BLACK")
    board._board[8, 3] = Piece("BLACK")
    board._board[7, 4] = Piece("RED")
    board._board[7, 8] = None
    board._board[3, 4] = None

    expected = [[(5, 6), (3, 4)], [(5, 6), (7, 8)]]

    assert board._king_jumps((7,4), "RED", [], [], set()) == expected

def test_piece_valid_moves_1():
    """
    test that the starting board will give the proper moves for a piece on the 
    front line
    """
    board = Checkers(3)
    board.set_up_board(3)
    piece = board._board[2,1]

    expected = [[(3,0)], [(3,2)]]

    assert board.piece_valid_moves(piece) == expected

def test_piece_valid_moves_2():
    """
    test that if given a piece which can do multiple jumps of different lengths 
    that it will only return the longest jump

    starting piece: (1,2)

    board:
     R R R R R
    R R R R R 
     R B R R R
    R R   R R 
       B B    
          
     B B B B B
    B B B B   
     B B B B B
    
    """
    board = Checkers(4)
    board.set_up_board(4)
    board._board[2, 3] = Piece("BLACK")
    board._board[4, 5] = Piece("BLACK")
    board._board[4, 3] = Piece("BLACK")
    board._board[3, 4] = None
    board._board[7, 8] = None

    piece = board._get((1,2))
    expected = [[(3, 4), (5, 6), (7, 8)]]

    assert board.piece_valid_moves(piece) == expected

def test_all_possible_moves_1():
    """
    test that if you set up a board with n: 3, the all possible moves method
    will provide the proper starting moves for red pieces
    """
    board = Checkers(3)
    board.set_up_board(3)

    expected = {(0, 1): None, (0, 3): None, (0, 5): None, (0, 7): None, (1, 0): None,
    (1, 2): None, (1, 4): None, (1, 6): None, (2, 1): [[(3, 0)], [(3, 2)]],
    (2, 3): [[(3, 2)], [(3, 4)]], (2, 5): [[(3, 4)], [(3, 6)]], 
    (2, 7): [[(3, 6)]]}

    assert board.all_possible_moves("RED") == expected, "checks that all possible works for starting position"

def test_all_possible_moves_2():
    """
    test that if you a piece can jump, the all possible moves method
    will provide only jumping movements even if single moves look possible

    Board:
     R R R
    R R R 
       B  
      
     B B B
    B B B 

    The red piece, (1, 0) should not have any moves
    """
    board = Checkers(2)
    board.set_up_board(2)
    board._board[2, 3] = Piece("BLACK")

    expected = {(0, 1): None, (0, 3): None, (0, 5): None, (1, 0): None,
    (1, 2): [[(3, 4)]], (1, 4): [[(3, 2)]]}

    assert board.all_possible_moves("RED") == expected

def test_make_move_1():
    """
    test the make move of a very simple board and ensure that it makes the
    moved peice a king

    starting board ():
       R
      B 
    
    B B 
    """
    board = Checkers(1)
    board.set_up_board(1)
    new_piece = Piece("BLACK")
    board._board[1, 2] = new_piece
    new_piece.loc = (1, 2)
    board._board[0, 1] = None
    print(board)
    board.make_move("BLACK", (1, 2), (0, 1))
    print("made move")
    print(board)

    moved_piece = board._get((0, 1))

    assert moved_piece.is_king == True