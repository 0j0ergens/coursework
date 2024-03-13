import pygame 
import numpy as np 
from checkers import Board
from checkers import Checkers
pygame.init()

RED = (116, 32, 27)
LRED = (225, 3, 0)
BLACK = (20, 0, 3)
GREEN = (27, 54, 31)
JUMPED = (189, 206, 161)
HIGHLIGHT = (61, 0, 9)

WHITE = (116, 32, 27)
SCREEN_EDGE = 800
BOARD_EDGE = 500
clock = pygame.time.Clock()
screen = pygame.display.set_mode(size=(SCREEN_EDGE, SCREEN_EDGE))
title_f = pygame.font.Font(None, 200)
stitle_f= pygame.font.Font(None, 150)
text_f = pygame.font.Font(None, 75)
rc_f = pygame.font.Font(None, 50)
q_f = pygame.font.Font(None, 40)
start_f = pygame.font.Font(None, 100)

class Game:
    """ 
    Class for representing Game object 
    """
    def __init__(self, n):
        """
        constructor for Game class
        Args: 
        n (int): the number of rows of pieces 
        """

        self.board = Checkers(n) 
        self.board.set_up_board(n)
        self.turn_red = True
        self.nrows = self.board._nrows
        self.ncols = self.board._ncolumns 
        self.sqedge = BOARD_EDGE // self.nrows
        self.board_bounds = pygame.Rect(0, 0, SCREEN_EDGE, self.sqedge*self.nrows) 
        self.dest_squares = []
        self.selected = None
        self.r_captured = 0
        self.b_captured = 0

def start(n = None):
    """
    If no n is inputted, creates start screen on which user inputs "n" (n must
    be inputted and > 0 in order for start button to work). If n is inputted, 
    skips start screen and generates board accordingly. 
    
    Call on this to start the entire game.

    Input 
    n (int): number of rows of pieces (optional)
    """
    if n: 
        game = Game(n) 
        drawBoard(game)

    else: 
        title = title_f.render('CHECKERS', True, BLACK, RED)
        give_dim = rc_f.render('define your board size (click textbox to type):'\
        , True, WHITE)
        n_txt = rc_f.render('# rows of pieces: ', True, WHITE)
        start_txt = start_f.render('start', True, BLACK, RED)

        n_input = ''
        text_box3 = pygame.Rect(285, 375, 100, 50)
        active3 = False

        titleRect = title.get_rect()
        titleRect.center = (SCREEN_EDGE // 2, SCREEN_EDGE // 5)
        dimRect = give_dim.get_rect()
        dimRect.bottomleft = (0, 350)
        nRect = n_txt.get_rect()
        nRect.bottomleft = (0, 415)
        startRect = start_txt.get_rect()
        startRect.center = (SCREEN_EDGE // 2, 700)

        while True: 
            screen.fill(BLACK)
            pygame.draw.rect(screen, WHITE, text_box3, 2)
            for event in pygame.event.get(): 
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()
            
                if event.type == pygame.MOUSEBUTTONDOWN: 
                    if text_box3.collidepoint(event.pos):
                        active3 = True
                    
                    if startRect.collidepoint(event.pos): 
                        n = int(n_input) 
                        if n and n > 0: 
                            game = Game(n)          
                            drawBoard(game)
                        
                if event.type == pygame.KEYDOWN:
                    if active3: 
                        if event.key == pygame.K_BACKSPACE: 
                            n_input = n_input[:-1]
                        elif len(n_input) < 2:
                            n_input += event.unicode

            screen.blit(title, titleRect)
            screen.blit(give_dim, dimRect)
            screen.blit(n_txt, nRect)
            text_surface3 = text_f.render(n_input,True,WHITE)
            screen.blit(text_surface3, (290, 375))
            screen.blit(start_txt, startRect)

            pygame.display.update()

def drawBoard(self, r_captured=0, b_captured=0, highlighted = None, greened=[],\
 jumped=[]):
    """
    Updates board graphics with current state of board

    Input
    r_captured/b_captured (int): number of pieces of each color captured
    highlighted (tuple): tuple containing (x,y) coords of the selected square
    greened (list): list containing the possible moves (coord tuples) a player can
    make given the selected square (these squares turn green)
    jumped (list): list containing the squares that will be jumped over during
    a move (these squares turn different color to signify that they are not 
    a valid end move)
    """
    sqedge = self.sqedge 
    board = self.board 
    nrows = self.nrows
    ncols = self.ncols

    rturn = text_f.render('turn', True, RED)
    rquit = q_f.render("abortmission", True, BLACK)
    bquit = q_f.render("abortmission", True, RED)
    red_turn = text_f.render('red', True, BLACK)
    bturn = text_f.render("black's", True, RED)
    black_turn = text_f.render('turn', True, BLACK)
    
    self.rqtext = rquit.get_rect()
    rqtext = self.rqtext
    rturntext = rturn.get_rect()
    redtext = red_turn.get_rect()
    redtext.topleft = (BOARD_EDGE+50, BOARD_EDGE)
    rturntext.topright = (BOARD_EDGE, BOARD_EDGE)
    rqtext.topleft = (BOARD_EDGE, 0)

    self.bqtext = bquit.get_rect()
    bqtext = self.bqtext
    btext = bturn.get_rect()
    blacktext = black_turn.get_rect()
    btext.topright = (BOARD_EDGE, BOARD_EDGE)
    blacktext.topleft = (BOARD_EDGE+50, BOARD_EDGE)
    bqtext.topleft = (0, BOARD_EDGE)

    self.pieces = board._board[(board._board != None)]
    screen.fill(BLACK)
    pygame.draw.rect(screen, RED, self.board_bounds)
    pygame.draw.polygon(screen, RED, [[BOARD_EDGE-10, BOARD_EDGE-10], \
    [SCREEN_EDGE, BOARD_EDGE-10], [SCREEN_EDGE, SCREEN_EDGE]])
    pygame.draw.line(screen, RED, (SCREEN_EDGE, SCREEN_EDGE), \
    (BOARD_EDGE-25, BOARD_EDGE-25), width=10)

    for rows in range(nrows):
        for cols in range(ncols): 
            x = cols * sqedge
            y = rows * sqedge
            if (rows + cols) % 2 != 0: 
                pygame.draw.rect(screen, BLACK, [x, y, sqedge, sqedge])
            if highlighted: 
                hloc = highlighted.loc
                pygame.draw.rect(screen, HIGHLIGHT, pygame.Rect(hloc[1]*sqedge,\
                hloc[0]*sqedge, sqedge, sqedge))
            if greened: 
                for sq in greened: 
                    pygame.draw.rect(screen, GREEN, pygame.Rect(sq[1]*sqedge, \
                    sq[0]*sqedge, sqedge, sqedge))
            if jumped: 
                for sq in jumped: 
                    pygame.draw.rect(screen, JUMPED, pygame.Rect(sq[1]*sqedge, \
                    sq[0]*sqedge, sqedge, sqedge))
            if r_captured > 0 or b_captured > 0: 
                for i in range(r_captured): 
                    pygame.draw.circle(screen, RED, (self.sqedge*i+sqedge/1.75, \
                    720), sqedge-sqedge/1.75, 0)
                for i in range(b_captured): 
                    pygame.draw.circle(screen, BLACK, (720, self.sqedge*i+sqedge\
                    /1.75), sqedge-sqedge/1.75, 0)
                
    for piece in self.pieces: 
        x = piece.loc[1]*sqedge
        y = piece.loc[0]*sqedge  
        if piece.color == 'RED':
            
            if piece.is_king:
                pygame.draw.circle(screen, RED, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.75, 0)
                pygame.draw.circle(screen, BLACK, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.25, 5) 

            else: 
                pygame.draw.circle(screen, RED, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.75, 0)
        else:
            if piece.is_king:
                pygame.draw.circle(screen, RED, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.75, 5) 
                pygame.draw.circle(screen, RED, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.25, 5) 
            else:
                pygame.draw.circle(screen, RED, (x+sqedge/2, y+sqedge/2), \
                sqedge-sqedge/1.75, 5)

    while True: 
        if board._winner: 
            winScreen(board._winner)
            
        if self.turn_red: 
            screen.blit(rturn, rturntext)
            screen.blit(red_turn, redtext)
            screen.blit(rquit, rqtext)
            pygame.draw.rect(screen, BLACK, rqtext, 2)

        else: 
            screen.blit(bturn, btext)
            screen.blit(black_turn, blacktext)
            screen.blit(bquit, bqtext)
            pygame.draw.rect(screen, RED, bqtext, 2)
        
        for event in pygame.event.get():
            if pygame.mouse.get_pressed(): 
                clicked(self, r_captured, b_captured, highlighted, greened, \
                jumped)
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
        pygame.display.update()

def clicked(self, r_captured, b_captured, highlighted=None, greened=[], \
jumped=[]): 
    """
    Registers user input (in the form of clicks)

    Input
    r_captured/b_captured (int): number of pieces of each color captured
    highlighted (tuple): tuple containing (x,y) coords of the selected square
    greened (list): list containing the possible moves (coord tuples) a player can
    make given the selected square (these squares turn green)
    jumped (list): list containing the squares that will be jumped over during
    a move (these squares turn different color to signify that they are not 
    a valid end move)
    """
    pieces = self.pieces 
    board = self.board
    selected = self.selected
    sqedge = self.sqedge
  
    while True: 
        if self.turn_red:
                cur_pieces = pieces[np.array([piece.color == 'RED' for piece in\
                                                pieces])]
        else:
            cur_pieces = pieces[np.array([piece.color == 'BLACK' for piece \
                                            in pieces])]

        for event in pygame.event.get():
            left, middle, right = pygame.mouse.get_pressed()
            
            if left: 
                for piece in cur_pieces:
                    x = piece.loc[1]*self.sqedge
                    y = piece.loc[0]*self.sqedge
                    square = pygame.Rect(x, y, self.sqedge, self.sqedge)
                    if square.collidepoint(pygame.mouse.get_pos()): 
                        selected = piece
                        greened = []
                        jumped = []
                        if selected.loc in Checkers.all_possible_moves(board, \
                        selected.color):
                            if Checkers.all_possible_moves(board, \
                            selected.color)[selected.loc]:
                                for move in Checkers.all_possible_moves(board, \
                                selected.color)[selected.loc]:
                                    if len(move) > 1: 
                                        for j in move[:-1]: 
                                            jumped.append(j)
                                    greened.append(move[-1])
                            drawBoard(self, r_captured, b_captured, selected,\
                             greened, jumped)
                    else: 
                        print("No available moves for this piece")

                for sq in greened: 
                    msq = pygame.Rect(sq[1]*sqedge, sq[0]*sqedge, sqedge, sqedge)
                    if msq.collidepoint(pygame.mouse.get_pos()):
                        Checkers.make_move(board, highlighted.color, \
                        highlighted.loc, sq)
                        if Checkers._is_jump(board, highlighted.loc, sq): 
                            num_cap = abs((highlighted.loc[0] - sq[0])//2)
                            if self.turn_red: 
                                b_captured += num_cap
                            else: 
                                r_captured += num_cap

                        self.turn_red = not self.turn_red
                        drawBoard(self, r_captured, b_captured)
                for sq in jumped: 
                    jsq = pygame.Rect(sq[1]*sqedge, sq[0]*sqedge, sqedge, sqedge)
                    if jsq.collidepoint(pygame.mouse.get_pos()):
                        print("Must pick end square")

            
                if self.bqtext.collidepoint(pygame.mouse.get_pos()) and not \
                self.turn_red: 
                    winScreen("RED")
                
                if self.rqtext.collidepoint(pygame.mouse.get_pos()) and \
                self.turn_red: 
                    winScreen("BLACK")
        
            if event.type == pygame.QUIT: 
                pygame.quit()
                quit()

            pygame.display.update()  

def winScreen(color): 
    """
    Generates the screen announcing a player's win.

    Input
    color (str): the winning color 
    """
    red_wins = title_f.render('RED WINS', True, BLACK)
    black_wins = stitle_f.render('BLACK WINS', True, RED)
    textRect = red_wins.get_rect()
    textRect.center = (SCREEN_EDGE//2, SCREEN_EDGE//2)

        
    while True: 
        for event in pygame.event.get(): 
                if event.type == pygame.QUIT:
                    pygame.quit()
                    quit()

        if color == "RED": 
            screen.fill(RED)
            screen.blit(red_wins, textRect)
        else: 
            screen.fill(BLACK)
            screen.blit(black_wins, textRect)
        
        pygame.display.update()
        
start()