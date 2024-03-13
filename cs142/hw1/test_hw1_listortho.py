import sys
import os
import random

# Handle the fact that the test code may not
# be in the same directory as the solution code
sys.path.insert(0, os.getcwd())

from listortho import ListOrthographer

def test_insert_1():
    do_test_insert(word='hello')

def test_insert_2():
    do_test_insert(word='goodbye')

def test_insert_3():
    do_test_insert(word='marzipan')
    
def test_inserts_1():
    do_test_inserts(words=["a"])

def test_inserts_2():
    do_test_inserts(words=["a","bb","ba"])

def test_inserts_3():
    do_test_inserts(words=["a","bb","ba","bc","ca","ccc","cc","cdcc","cdd","q","r","t"])

def test_insert_from_file_1(tmp_path):
    do_test_insert_from_file(words=['x'], tmp_path=tmp_path)

def test_insert_from_file_2(tmp_path):
    do_test_insert_from_file(words=['a','b','c'], tmp_path=tmp_path)

def test_insert_from_file_3(tmp_path):
    do_test_insert_from_file(words=['a','a','b','c'], tmp_path=tmp_path)

def test_insert_from_file_4(tmp_path):
    do_test_insert_from_file(words=['a','a:','b','b:','c','c:'], tmp_path=tmp_path)
    
def test_contains_1():
    do_test_contains(words=[],sought="banana",result=False)

def test_contains_2():
    do_test_contains(words=["banana"],sought="banana",result=True)

def test_contains_3():
    do_test_contains(words=["ban"],sought="banana",result=False)

def test_contains_4():
    do_test_contains(words=["ban","banana"],sought="banana",result=True)

def test_contains_5():
    do_test_contains(words=["ban","banana"],sought="ban",result=True)

def test_contains_6():
    do_test_contains(words=["apple"],sought="banana",result=False)

def test_completions_1():
    do_test_completions(words=[],prefix="a",result=[])

def test_completions_2():
    do_test_completions(words=["a"],prefix="a",result=["a"])

def test_completions_3():
    do_test_completions(words=["b"],prefix="a",result=[])

def test_completions_4():
    do_test_completions(words=["a","aa","b","bc"],prefix="a",result=["a","aa"])

def test_completions_5():
    do_test_completions(words=["a","aa","b","bc"],prefix="b",result=["b","bc"])

def test_completions_6():
    do_test_completions(words=["a","aa","b","bc"],prefix="aa",result=["aa"])

def test_completions_7():
    do_test_completions(words=["a","aa","b","bc"],prefix="aaa",result=[])

def test_completions_8():
    do_test_completions(words=["a","aa","b","bc"],prefix="c",result=[])

def test_num_completions_1():
    do_test_num_completions(words=[],prefix="a",result=0)

def test_num_completions_2():
    do_test_num_completions(words=["a"],prefix="a",result=1)

def test_num_completions_3():
    do_test_num_completions(words=["a","ab","b"],prefix="a",result=2)

def test_num_completions_4():
    do_test_num_completions(words=["a","ab","b"],prefix="b",result=1)

def test_num_completions_5():
    do_test_num_completions(words=["a","ab","b"],prefix="x",result=0)

def test_all_words_1():
    do_test_all_words(words=[],result=[])

def test_all_words_2():
    do_test_all_words(words=["a"],result=["a"])

def test_all_words_3():
    do_test_all_words(words=["a","c","b"],result=["a","b","c"])

def test_all_words_4():
    do_test_all_words(words=["a","a","c","b"],result=["a","b","c"])

def test_all_words_5():
    do_test_all_words(words=["a","a","c","c","b","b"],result=["a","b","c"])

def test_all_words_6():
    do_test_all_words(words=["a","c","b","X"],result=["a","b","c"])

def test_all_words_7():
    do_test_all_words(words=["a","c","b","@"],result=["a","b","c"])

def test_all_words_8():
    do_test_all_words(words=["Xa","Xc","Xb","X@"],result=[])

def test_num_words_1():
    do_test_num_words(words=[],result=0)

def test_num_words_2():
    do_test_num_words(words=["a"],result=1)

def test_num_words_3():
    do_test_num_words(words=["a","c","b"],result=3)

def test_num_words_4():
    do_test_num_words(words=["a","a","c","b"],result=3)

def test_num_words_5():
    do_test_num_words(words=["a","a","c","c","b","b"],result=3)

def test_num_words_6():
    do_test_num_words(words=["a","c","b","X"],result=3)

def test_num_words_7():
    do_test_num_words(words=["a","c","b","@"],result=3)

def test_num_words_8():
    do_test_num_words(words=["Xa","Xc","Xb","X@"],result=0)

    
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


def all_lower(s):
    for c in s:
        if not(c.islower()):
            return False
    return True
    
# # #
#
# TEST HELPERS
#
# # #


def do_test_insert(word):
    lo = ListOrthographer()
    lo.insert(word)
    assert lo.words == [word]

def do_test_inserts(words):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert sorted(lo.words) == sorted(words)

def do_test_insert_from_file(words, tmp_path):
    filename = tmp_path / "words.txt"
    filename.write_text("\n".join(words))

    lo = ListOrthographer()
    lo.insert_from_file(str(filename))

    lowercase_words = filter(all_lower, words)
    assert sorted(list(set(lowercase_words))) == sorted(lo.words)
    
def do_test_contains(words, sought, result):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert lo.contains(sought)==result

def do_test_completions(words, prefix, result):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert sorted(lo.completions(prefix)) == sorted(result)

def do_test_num_completions(words, prefix, result):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert lo.num_completions(prefix)==result

def do_test_all_words(words, result):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert sorted(lo.all_words()) == sorted(result)

def do_test_num_words(words, result):
    lo = ListOrthographer()
    for word in words:
        lo.insert(word)
    assert lo.num_words() == result

