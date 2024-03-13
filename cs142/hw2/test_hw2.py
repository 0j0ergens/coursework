import sys
import os
import random
import json

# Handle the fact that the test code may not
# be in the same directory as the solution code
sys.path.insert(0, os.getcwd())

from maze import Maze
from cell import Cell


def test_task1_construct_1():
    do_test_construct_nonrandom(height=2, width=3)


def test_task1_construct_2():
    do_test_construct_nonrandom(height=10, width=15)


def test_task1_construct_3():
    do_test_construct_nonrandom(height=20, width=20)


def test_task2_str_allwalls_1():
    do_test_str(height=2, width=3, seed=None)


def test_task2_str_allwalls_2():
    do_test_str(height=10, width=15, seed=None)


def test_task2_str_allwalls_3():
    do_test_str(height=20, width=20, seed=None)


def test_task3_construct_1():
    do_test_construct(height=2, width=3, seed=7)


def test_task3_construct_2():
    do_test_construct(height=10, width=15, seed=7)


def test_task3_construct_3():
    do_test_construct(height=20, width=20, seed=7)


def test_task3_construct_4():
    do_test_construct(height=2, width=3, seed=42)


def test_task3_construct_5():
    do_test_construct(height=10, width=15, seed=42)


def test_task3_construct_6():
    do_test_construct(height=20, width=20, seed=42)


def test_task3_str_1():
    do_test_str(height=2, width=3, seed=7)


def test_task3_str_2():
    do_test_str(height=10, width=15, seed=7)


def test_task3_str_3():
    do_test_str(height=20, width=20, seed=7)


def test_task3_str_4():
    do_test_str(height=2, width=3, seed=42)


def test_task3_str_5():
    do_test_str(height=10, width=15, seed=42)


def test_task3_str_6():
    do_test_str(height=20, width=20, seed=42)


def test_task4_trail_1():
    do_test_trail(height=2, width=3, seed=7)


def test_task4_trail_2():
    do_test_trail(height=10, width=15, seed=7)


def test_task4_trail_3():
    do_test_trail(height=10, width=15, seed=7)


def test_task4_trail_4():
    do_test_trail(height=2, width=3, seed=7, interpose="-impossible")

def test_task4_trail_5():
    do_test_trail(height=10, width=15, seed=7, interpose="-impossible")

def test_task4_trail_6():
    do_test_trail(height=10, width=15, seed=7, interpose="-impossible")

def test_task5_solve_1():
    do_test_solve(height=2, width=3, seed=7)

def test_task5_solve_2():
    do_test_solve(height=10, width=15, seed=7)

def test_task5_solve_3():
    do_test_solve(height=20, width=20, seed=7)

def test_task5_solve_4():
    do_test_solve(height=2, width=3, seed=42)

def test_task5_solve_5():
    do_test_solve(height=10, width=15, seed=42)

def test_task5_solve_6():
    do_test_solve(height=20, width=20, seed=42)


def test_task6_str_1():
    m = Maze(4, 4, 0)
    actual = m.to_string((m.grid[0][0], "E"), {})
    do_test_to_string(actual, "frame1.str")

def test_task6_str_2():
    m = Maze(4, 4, 0)
    actual = m.to_string((m.grid[1][3], "S"), [m.grid[0][1], m.grid[0][2],
                                               m.grid[0][0], m.grid[0][3]])
    do_test_to_string(actual, "frame2.str")

def test_task6_str_3():
    m = Maze(4, 4, 0)
    actual = m.to_string((m.grid[1][2], "W"), [m.grid[0][3], m.grid[0][2],
                                               m.grid[0][0], m.grid[1][3],
                                               m.grid[0][1]])
    do_test_to_string(actual, "frame3.str")

def test_task6_str_4():
    m = Maze(4, 4, 0)
    actual = m.to_string((m.grid[2][2], "N"), [m.grid[0][3], m.grid[2][0],
                                               m.grid[0][2], m.grid[0][0],
                                               m.grid[1][3], m.grid[2][1],
                                               m.grid[1][2], m.grid[3][1],
                                               m.grid[0][1], m.grid[1][1],
                                               m.grid[3][0], m.grid[3][2]])
    do_test_to_string(actual, "frame4.str")


# # #
#
# HELPER FUNCTIONS
#
# # #

def gen_recreate_msg(module, function, *params):
    params_str = ", ".join([str(p) for p in params])

    recreate_msg = "To recreate this test in ipython3 run:\n"
    recreate_msg += "  {}.{}({})".format(module, function, params_str)

    return recreate_msg


def check_none(actual, recreate_msg=None):
    msg = "The function returned None."
    msg += " Did you forget to replace the placeholder value we provide?"
    if recreate_msg is not None:
        msg += "\n" + recreate_msg

    assert actual is not None, msg


def check_type(actual, expected, recreate_msg=None):
    actual_type = type(actual)
    expected_type = type(expected)

    msg = "The function returned a value of the wrong type.\n"
    msg += "  Expected return type: {}.\n".format(expected_type.__name__)
    msg += "  Actual return type: {}.".format(actual_type.__name__)
    if recreate_msg is not None:
        msg += "\n" + recreate_msg

    assert isinstance(actual, expected_type), msg


def check_equals(actual, expected, recreate_msg=None):
    msg = "Actual ({}) and expected ({}) values do not match.".format(actual, expected)
    if recreate_msg is not None:
        msg += "\n" + recreate_msg

    assert actual == expected, msg


def check_list_unmodified(param_name, before, after, recreate_msg=None):
    msg = "You modified the contents of {} (this is not allowed).\n".format(param_name)
    msg += "  Value before your code: {}\n".format(before)
    msg += "  Value after your code:  {}".format(after)
    if recreate_msg is not None:
        msg += "\n" + recreate_msg

    assert before == after, msg

# # #
#
# TEST HELPERS
#
# # #

def do_test_construct_nonrandom(height, width):
    m = Maze(height, width)

    assert hasattr(m, "grid"), f"The Maze object does not have a grid attribute"
    assert isinstance(m.grid, list), f"The Maze object has a grid attribute but it is not a list"
    assert all(isinstance(row, list) for row in m.grid), f"The Maze object has a grid attribute and it is a list, but it does not contain lists."
    assert len(m.grid) == height, f"The grid attribute of the Maze has the wrong height (actual={len(m.grid)}, expected={height})"
    assert all(len(row) == width for row in m.grid), \
        f"The grid attribute of the Maze has rows whose length is not {width}"

    for row in range(height):
        for col in range(width):
            cell = m.grid[row][col]
            assert cell is not None, f"m.get_cell({row}, {col}) returned None instead of a Cell object"
            assert isinstance(cell, Cell), f"m.get_cell({row}, {col}) returned something other than a Cell object"

            assert cell.row == row, f"m.get_cell({row}, {col}) returned a Cell with an incorrect row ({cell.row})"
            assert cell.column == col, f"m.get_cell({row}, {col}) returned a Cell with an incorrect column ({cell.column})"

            assert cell.north is None, f"m.get_cell({row}, {col}) returned a Cell with north set to something other than None ({cell.north})"
            assert cell.south is None, f"m.get_cell({row}, {col}) returned a Cell with south set to something other than None ({cell.south})"
            assert cell.east is None, f"m.get_cell({row}, {col}) returned a Cell with east set to something other than None ({cell.east})"
            assert cell.west is None, f"m.get_cell({row}, {col}) returned a Cell with west set to something other than None ({cell.west})"


def do_test_construct(height, width, seed):
    m = Maze(height, width, seed)
    filename = "tests/maze-{}-{}-{}.json".format(height, width, seed)
    with open(filename) as f:
        expected = json.load(f)
    assert(len(m.grid) == len(expected))
    for expected_row, actual_row in zip(expected, m.grid):
        assert(len(expected_row) == len(actual_row))
        for expected_cell, actual_cell in zip(expected_row, actual_row):
            r_coord, c_coord, north, east, south, west = expected_cell.split()
            assert(int(r_coord) == actual_cell.row)
            assert(int(c_coord) == actual_cell.column)
            if north == "None":
                assert(actual_cell.north is None)
            else:
                assert(actual_cell.north is not None)
                n_row, n_col = north.split("-")
                assert(actual_cell.north.row == int(n_row))
                assert(actual_cell.north.column == int(n_col))

            if east == "None":
                assert(actual_cell.east is None)
            else:
                assert(actual_cell.east is not None)
                e_row, e_col = east.split("-")
                assert(actual_cell.east.row == int(e_row))
                assert(actual_cell.east.column == int(e_col))

            if south == "None":
                assert(actual_cell.south is None)
            else:
                assert(actual_cell.south is not None)
                s_row, s_col = south.split("-")
                assert(actual_cell.south.row == int(s_row))
                assert(actual_cell.south.column == int(s_col))

            if west == "None":
                assert(actual_cell.west is None)
            else:
                assert(actual_cell.west is not None)
                w_row, w_col = west.split("-")
                assert(actual_cell.west.row == int(w_row))
                assert(actual_cell.west.column == int(w_col))


def do_test_trail(height, width, seed, interpose=""):
    m = Maze(height, width, seed)
    dirs_filename = "tests/maze-{}-{}-{}{}.lh".format(height, width, seed, interpose)
    with open(dirs_filename) as f:
        dirs = f.read().strip()
    trail_filename = "tests/maze-{}-{}-{}{}-trail.json".format(height, width, seed, interpose)
    with open(trail_filename) as f:
        expected = json.load(f)

    actual = m.directions_to_trail(dirs)
    if expected is None:
        assert(actual is None)
        return

    assert(len(actual) == len(expected))
    for expected_cell, actual_cell in zip(expected, actual):
        expected_r, expected_c = expected_cell.split()
        assert(int(expected_r) == actual_cell.row)
        assert(int(expected_c) == actual_cell.column)


def do_test_str(height, width, seed):
    m = Maze(height, width, seed)
    filename = "tests/maze-{}-{}-{}.str".format(height, width, seed)
    with open(filename, encoding="utf-8") as f:
        expected = f.read()
    assert(str(m) == expected)


def do_test_solve(height, width, seed):
    m = Maze(height, width, seed)
    filename = "tests/maze-{}-{}-{}.lh".format(height, width, seed)
    with open(filename) as f:
        expected = f.read()
    assert(m.solve_lefthand() == expected.strip())
    

def do_test_to_string(actual, filename):
    filename = "tests/" + filename
    with open(filename, encoding="utf-8") as f:
        expected = f.read()
    assert(actual == expected)

