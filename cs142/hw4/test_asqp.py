import numpy as np
import pandas as pd
import pickle

# import student code
from asqp import read_and_process_asc, \
                 delay_and_cancel_fractions, \
                 per_carrier_delays_cancels, \
                 average_delay, \
                 average_delay_by_period, \
                 underperforming_carriers, \
                 read_and_process_npy, \
                 remove_irregularities, \
                 remove_trend, \
                 is_seasonal

from test_utils import compare_dataframes

######### Testing Part 1: Pandas #########

# might need a helper to compare dfs
DATA_DIR = "data/"
TEST_DIR = "test-data/"

def task1_helper(filename):

    # run filename with student read_and_process_asc
    actual = read_and_process_asc(DATA_DIR + filename + ".asc")

    # open expected output (pickled filename)
    expected = pd.read_pickle(TEST_DIR + "task1_" + filename)
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by read_and_process_asc not as expected\n" + message

def test_task1_0():
    filename = "tiny"
    task1_helper(filename)

def test_task1_1():
    filename = "tiny_all_delayed"
    task1_helper(filename)

def test_task1_2():
    filename = "tiny_all_cancelled"
    task1_helper(filename)

def test_task1_3():
    filename = "tiny_all_on_time"
    task1_helper(filename)

def task2a_helper(df, expected):
    
    # run df through student delay_and_cancel_fractions
    actual = delay_and_cancel_fractions(df)

    # compare actual and expected
    assert actual == expected, "Values returned by delay_and_cancel_fractions not as expected"

def test_task2a_0():

    df = pd.read_pickle(TEST_DIR + "task1_tiny") # "correct" df
    expected = (0.2, 0.1)
    task2a_helper(df, expected)

def test_task2a_1():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_delayed") 
    expected = (1.0, 0.0)
    task2a_helper(df, expected)

def test_task2a_2():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_cancelled") 
    expected = (0.0, 1.0)
    task2a_helper(df, expected)

def test_task2a_3():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_on_time") 
    expected = (0.0, 0.0)
    task2a_helper(df, expected)

def task2b_helper(df, filename):

    # run df through student per_carrier_delays_cancels
    actual_delays, actual_cancels = per_carrier_delays_cancels(df)

    # open expected dataframes
    expected_delays = pd.read_pickle(TEST_DIR + "task2b_delays_" + filename)
    expected_cancels = pd.read_pickle(TEST_DIR + "task2b_cancels_" + filename)

    # compare actual and expected
    result, message = compare_dataframes(actual_delays, expected_delays)
    assert result, "Delay DataFrame returned by per_carrier_delays_cancels not as expected\n" + message

    result, message = compare_dataframes(actual_cancels, expected_cancels)
    assert result, "Cancel DataFrame returned by per_carrier_delays_cancels not as expected\n" + message

def test_task2b_0():

    filename = "tiny"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename) # "correct" df
    task2b_helper(df, filename)

def test_task2b_1():
    filename = "tiny_all_delayed"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2b_helper(df, filename)

def test_task2b_2():
    filename = "tiny_all_cancelled"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2b_helper(df, filename)

def test_task2b_3():
    filename = "tiny_all_on_time"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2b_helper(df, filename)

def task2c_helper(df, expected):

    # run df through student average_delay
    actual = average_delay(df)

    assert abs(actual - expected) < 0.001, "Value returned by average_delay not as expected"

def test_task2c_0():

    df = pd.read_pickle(TEST_DIR + "task1_tiny") # "correct" df
    expected = 57.333333333333336
    task2c_helper(df, expected)

def test_task2c_1():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_delayed") 
    expected = 62.5
    task2c_helper(df, expected)

def test_task2c_2():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_cancelled") 
    expected = 0.0
    task2c_helper(df, expected)

def test_task2c_3():

    df = pd.read_pickle(TEST_DIR + "task1_tiny_all_on_time") 
    expected = 0.0
    task2c_helper(df, expected)

def task2d_helper(df, filename):

    # run df through student average_delay_by_period
    actual = average_delay_by_period(df)
    expected = pd.read_pickle(TEST_DIR + "task2d_" + filename)

    # compare actual and expected
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by average_delay_by_period not as expected\n" + message

def test_task2d_0():

    filename = "tiny"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename) # "correct" df
    task2d_helper(df, filename)

def test_task2d_1():
    filename = "tiny_all_delayed"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2d_helper(df, filename)

def test_task2d_2():
    filename = "tiny_all_cancelled"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2d_helper(df, filename)

def test_task2d_3():
    filename = "tiny_all_on_time"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2d_helper(df, filename)

def task2e_helper(df, filename):

   # run df through student underperforming_carriers
    actual = underperforming_carriers(df)
    expected = pd.read_pickle(TEST_DIR + "task2e_" + filename)

    # compare actual and expected
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by underperforming_carriers not as expected\n" + message

def test_task2e_0():

    filename = "tiny"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename) # "correct" df
    task2e_helper(df, filename)

def test_task2e_1():
    filename = "tiny_all_delayed"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2e_helper(df, filename)

def test_task2e_2():
    filename = "tiny_all_cancelled"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2e_helper(df, filename)

def test_task2e_3():
    filename = "tiny_all_on_time"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)
    task2e_helper(df, filename)

######### Testing Part 2: NumPy #########

def task3_helper(actual_filename, expected_filename):

    actual = read_and_process_npy(actual_filename)
    expected = np.load(expected_filename)

    assert np.array_equal(actual, expected), "Array returned by read_and_process_npy not as expected"

def test_task3_0():
    task3_helper(DATA_DIR + "delays_tiny1.npy", TEST_DIR + "task3_delays_tiny1.npy")

def test_task3_1():
    task3_helper(DATA_DIR + "delays_tiny2.npy", TEST_DIR + "task3_delays_tiny2.npy")

def task4a_helper(actual_filename, expected_filename, w):

    ts = np.load(actual_filename)
    actual = remove_irregularities(ts, w)
    expected = np.load(expected_filename)

    assert np.isclose(actual, expected).all(), "Array returned by remove_irregularities not as expected"

def test_task4a_0():

    w = 1
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4a_delays_tiny1_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_1():

    w = 2
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4a_delays_tiny1_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_2():

    w = 3
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4a_delays_tiny1_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_3():

    w = 1
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4a_delays_tiny2_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_4():

    w = 2
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4a_delays_tiny2_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_5():

    w = 3
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4a_delays_tiny2_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def task4b_helper(actual_filename, expected_filename, w):

    ts = np.load(actual_filename)
    actual = remove_trend(ts, w)
    expected = np.load(expected_filename)

    assert np.isclose(actual, expected).all(), "Array returned by remove_irregularities not as expected"


def test_task4b_0():

    w = 1
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4b_delays_tiny1_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def test_task4b_1():

    w = 2
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4b_delays_tiny1_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def test_task4b_2():

    w = 1
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4b_delays_tiny2_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def test_task4b_3():

    w = 2
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4b_delays_tiny2_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def task4c_helper(actual_filename, expected_filename, w, expected_month):

    ts = np.load(actual_filename) 
    actual_buckets, actual_month = is_seasonal(ts, w)
    expected_buckets = np.load(expected_filename)

    assert np.isclose(actual_buckets, expected_buckets).all(), "Array returned by is_seasonal not as expected"
    assert actual_month == expected_month, "Month returned by is_seasonal not as expected"

def test_task4c_0():

    w = 1
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4c_delays_tiny1_w" + str(w) + ".npy"
    expected_month = 0

    task4c_helper(actual_filename, expected_filename, w, expected_month)

def test_task4c_1():

    w = 2
    actual_filename = "test-data/task3_delays_tiny1.npy"
    expected_filename = "test-data/task4c_delays_tiny1_w" + str(w) + ".npy"
    expected_month = 0

    task4c_helper(actual_filename, expected_filename, w, expected_month)

def test_task4c_2():

    w = 1
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4c_delays_tiny2_w" + str(w) + ".npy"
    expected_month = 2

    task4c_helper(actual_filename, expected_filename, w, expected_month)

def test_task4c_3():

    w = 2
    actual_filename = "test-data/task3_delays_tiny2.npy"
    expected_filename = "test-data/task4c_delays_tiny2_w" + str(w) + ".npy"
    expected_month = 2

    task4c_helper(actual_filename, expected_filename, w, expected_month)