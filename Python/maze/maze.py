from cell import Cell

WALL = "#"
CELL = "·"
PATH = " "
TRAIL = "o"
CURN = "^"
CURE = ">"
CURS = "v"
CURW = "<"



class Maze:
    """
    A class for representing mazes
    """

    def __init__(self, height, width, seed=None):

        self.height = height
        self.width = width 
        self.grid = [[Cell(x, y) for y in range(width)] for x in range(height)]
        self.seed = seed
        if seed != None: 
            self._random_dfs(self.grid[0][0], set())
       
            

    def to_string(self, cursor, trail):
        """
        Returns a string representation of the maze

        Parameters:
            cursor : tuple[Cell, str]
            trail : list[Cell]

        Returns: str
        """

        grid_lst = [ [] for _ in range(len(self.grid) * 2)]
        grid_str = []
        
      
        for i, row in enumerate(self.grid):  
            for cell in row: 
                c_row = i*2+1
                n_row = i*2
                if cell.north == None: 
                    grid_lst[n_row].append(WALL + WALL)
                else: 
                    grid_lst[n_row].append(WALL + PATH)
                if not grid_lst[c_row]:
                    grid_lst[c_row].append(WALL)
                if cell.east == None:
                    grid_lst[c_row].append(CELL + WALL)
                else: 
                    grid_lst[c_row].append(CELL + PATH)
            grid_lst[n_row].append(WALL)

        grid_lst.append(WALL * (self.width * 2 - 1) + PATH + WALL + "\n")
        grid_lst[1][0] = PATH
        for row in grid_lst: 
            grid_str.append("".join(row))
        
        return("\n".join(grid_str))

    
    def __str__(self):
        return self.to_string(None, set())

    def find_neighbors(self, cell): 
        '''
        find the neighboring cells within the graph

        Parameter:
        cell: Cell

        Returns: list of randomized directions 
        '''
        directions = []
        col = cell.column 
        row = cell.row 
        grid = self.grid

        if row - 1 >= 0: 
            directions.append(('N',grid[row-1][col]))
        if col + 1 < self.width:
            directions.append(('E',grid[row][col+1]))
        if row + 1 < self.height:
            directions.append(('S',grid[row+1][col]))
        if col - 1 >= 0: 
            directions.append(('W',grid[row][col-1]))
       
        return cell.shuffle_directions(directions, self.seed)

    def _random_dfs(self, start, visited):
        """
        Uses DFS to generate a random maze.

        Parameters:
            start : Cell
            visited : set[Cell]

        Returns: (does not return a value)
        """
        
        directions = self.find_neighbors(start)
  
        for dir in directions:
            visited.add(start)
            cell = dir[1]
            if cell not in visited:        
                if dir[0] == 'N':
                    start.north = cell
                    cell.south = start
                elif dir[0] == 'E':
                    start.east = cell
                    cell.west = start
                elif dir[0] == 'S':
                    start.south = cell
                    cell.north = start
                elif dir[0] == 'W':
                    start.west = cell
                    cell.east = start
                self._random_dfs(cell, visited)
    
    def directions_to_trail(self, dir_string):
        """
        Takes a direction string, and produces the list of Cell objects
        that would be visited following those directions. If the
        directions are not valid, returns None.

        Always starts at Cell (0,0)

        Parameters:
            dir_string : str

        Returns: list[Cell] or None
        """

        dir_lst = list(dir_string)
        grid = self.grid
        start = grid[0][0]
        c_lst = [start] 
    
        for dir in dir_lst: 
            if dir == 'N':
                direction = start.north
            if dir == 'E':
                direction = start.east
            if dir == 'S':
                direction = start.south
            if dir == 'W':
                direction = start.west
            if direction == None: 
                return None
            else: 
                c_lst.append(direction)
                start = direction
    
        if len(c_lst) == len(dir_lst) + 1:
            return c_lst
  
      
    def left_navigate(self, start, current_direction, str_lst):
        grid = self.grid

        while start != grid[-1][-1]:
            if start == grid[0][0]:
                str_lst = []
                if start.east:
                    current_direction = 'E'
                    start = start.east    
                elif start.south:
                    current_direction = 'S'
                    start = start.south
                str_lst.append(current_direction)
        
            elif current_direction == 'E':
                if start.north:
                    start = start.north
                    current_direction = 'N'
                    str_lst.append(current_direction)
                elif start.east:
                    start = start.east
                    str_lst.append(current_direction)
                else: 
                    current_direction = 'W'
            
            elif current_direction == 'W':
                if start.south:
                    start = start.south
                    current_direction = 'S'
                    str_lst.append(current_direction)
                elif start.west:
                    start = start.west
                    str_lst.append(current_direction)
                else:
                    current_direction = 'E'
            
            elif current_direction == 'S':
                if start.east:
                        start = start.east
                        current_direction = 'E'
                        str_lst.append(current_direction)
                elif start.south:
                    start = start.south
                    str_lst.append(current_direction)
                else: 
                    current_direction = 'N'
            
            elif current_direction == 'N':
                if start.west:
                    start = start.west
                    current_direction = 'W'
                    str_lst.append(current_direction)
                elif start.north:
                    start = start.north
                    str_lst.append(current_direction)
                else:
                    current_direction = 'S'

            return self.left_navigate(start, current_direction, str_lst)
            
        
        return("".join(str_lst))
        
      
    def solve_lefthand(self):
        """
        Uses the left-hand algorithm to find a path from the
        entrance of the maze to its exit.

        Parameters: None

        Returns: str
        """
        return(self.left_navigate(self.grid[0][0], None, []))
         
    def animate(self, delay):
        """
        Display an animation of the left-hand algorithm

        Parameters:
            delay : float

        Returns: (does not return a value)
        """
        raise NotImplementedError("todo: Maze.animate")
