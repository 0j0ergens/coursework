import sys
import os
import random
import json

# tolerance for real-number comparisons
EPSILON = 0.1

# Handle the fact that the test code may not
# be in the same directory as the solution code
sys.path.insert(0, os.getcwd())

from minheap import MinHeap
from graph import Vertex, Graph
from a_star import a_star


def test_task1_heap_1():
    do_test_heap(elements=[10])


def test_task1_heap_2():
    do_test_heap(elements=[20, 40, 30, 10, 15, 50, 5])
    
    
def test_task2_indices_1():
    do_test_indices(elements=[20, 40, 30, 10, 15, 50, 5],
                    filename="tests/indices-1.json")

    
def test_task2_indices_2():
    do_test_indices(elements=[3, 8, 2, 5, 9, 6, 1, 4, 7],
                    filename="tests/indices-2.json")


def test_task2_indices_3():
    do_test_indices(elements=[6, 5, 4, 2, 8, 7, 3, 1, 9],
                    filename="tests/indices-3.json")
                    
                                        
def test_task2_indices_4():
    do_test_indices(elements=[25, 40, 45, 35, 50, 15, 10, 20, 30],
                    filename="tests/indices-4.json")
                                        
        
def test_task3_priority_1():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=10, new=0)
    
    
def test_task3_priority_2():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=90, new=0)
    
    
def test_task3_priority_3():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=10, new=35)
    
    
def test_task3_priority_4():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=90, new=25)
    
    
def test_task3_priority_5():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=20, new=45)
    
    
def test_task3_priority_6():
    do_test_change_priority(elements=list(range(10, 100, 10)), old=60, new=25)
    

def test_task4_a_star_1():
    do_test_a_star(start="ORD", end="SFO", nclosest=1)


def test_task4_a_star_2():
    do_test_a_star(start="ORD", end="SFO", nclosest=2)


def test_task4_a_star_3():
    do_test_a_star(start="ORD", end="SFO", nclosest=3)


def test_task4_a_star_4():
    do_test_a_star(start="ORD", end="SFO", nclosest=4)


def test_task4_a_star_5():
    do_test_a_star(start="BOS", end="LAX", nclosest=3)


def test_task4_a_star_6():
    do_test_a_star(start="BOS", end="LAX", nclosest=4)


def test_task4_a_star_7():
    do_test_a_star(start="BOS", end="LAX", nclosest=5)


def test_task4_a_star_8():
    do_test_a_star(start="SFO", end="SAN", nclosest=1)


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

def do_test_heap(elements):
    h = MinHeap()
    for i in elements:
        assert h.verify(), "heap verification failed during insertions"
        h.insert(i, str(i))
        assert h.verify(), "heap verification failed during insertions"
        
    assert h.size() == len(elements), "size does not reflect all insertions"
    
    elements.sort()
    for i in elements:
        assert h.min() == (i, str(i)),\
            "min provided incorrect answer for element {}".format(i)
        assert h.verify(), "heap verification failed during removals"
        assert h.remove_min() == (i, str(i)),\
            "remove_min provided incorrect answer for element {}".format(i)
        assert h.verify(), "heap verification failed during removals"
        
    assert h.is_empty(), "heap not empty after removal of all expected elements"


def do_test_indices(elements, filename):
    h = MinHeap()
    with open(filename) as f:
        expected = json.load(f)
    assert h.index_of_item == {}, "index_of_item not empty to start"
    for i in elements:
        h.insert(i, str(i))
        assert sorted(h.index_of_item.items()) == \
            list(map(tuple, expected.pop(0))), \
            "index_of_item not maintained correctly during insertions"
        
    for i in elements:
        h.remove_min()
        assert sorted(h.index_of_item.items()) == \
            list(map(tuple, expected.pop(0))), \
            "index_of_item not maintained correctly during removals"
            
            
def do_test_change_priority(elements, old, new):
    h = MinHeap()
    for i in elements:
        h.insert(i, str(i))
    
    h.change_priority(str(old), new)
    
    expected = sorted([x for x in elements if x != old] + [new])
    for i  in expected:
        actual_prio, actual_item = h.remove_min()
        if i == new:
            assert actual_prio == new
            assert actual_item == str(old)
        else:
            assert actual_prio == i
            assert actual_item == str(i)
        

def do_test_a_star(start, end, nclosest):
    filename = "tests/a_star-{}-{}-{}.json".format(start, end, nclosest)
    with open(filename) as f:
        expected = json.load(f)
        
    g = Graph("airports.csv", nclosest)
    actual = a_star(g, g.get_vertex(start), g.get_vertex(end))
    if expected is None:
        assert actual is None, "a_star did not return None as expected"
        return
    assert isinstance(actual, tuple), "a_star did not return a tuple"
    assert len(actual) == 3, \
           "a_star did not return a tuple with three components"
    
    exp_dist, exp_path, exp_visited = expected
    act_dist, act_path, act_visited = actual
    
    assert abs(act_dist - exp_dist) <= EPSILON, \
           "distance from a_star {} does not match expected {}".format(
           act_dist, exp_dist)
    assert act_path == exp_path, \
           "path from a_star {} does not match expected {}".format(
           act_path, exp_path)
    act_visited_list = sorted([v.name for v in act_visited])
    assert act_visited_list == exp_visited, \
           "actual closed set {} does not match expected {}".format(
           act_visited_list, exp_visited)
    
