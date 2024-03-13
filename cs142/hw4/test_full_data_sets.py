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

DATA_DIR = "full_data_sets/"
TEST_DIR = "full_data_sets/"

def test_task1_full():

    filename = "asqp"

    # run filename with student read_and_process_asc
    actual = read_and_process_asc(DATA_DIR + filename + ".asc")

    # open expected output (pickled filename)
    expected = pd.read_pickle(TEST_DIR + "task1_" + filename)
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by read_and_process_asc not as expected\n" + message

def test_task2a_full():

    df = pd.read_pickle(TEST_DIR + "task1_asqp") # "correct" df
    expected = (0.1873460363600532, 0.012289377740552792)
    
    # run df through student delay_and_cancel_fractions
    actual = delay_and_cancel_fractions(df)

    # compare actual and expected
    assert abs(actual[0] - expected[0]) < 0.001, "Values returned by delay_and_cancel_fractions not as expected"
    assert abs(actual[1] - expected[1]) < 0.001, "Values returned by delay_and_cancel_fractions not as expected"

def test_task2b_full():

    filename = "asqp"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename) # "correct" df

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

def test_task2c_full():

    df = pd.read_pickle(TEST_DIR + "task1_asqp") 
    expected = 33.76669981667645

    # run df through student average_delay
    actual = average_delay(df)

    assert abs(actual - expected) < 0.001, "Value returned by average_delay not as expected"

def test_task2d_full():

    filename = "asqp"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename) 

    # run df through student average_delay_by_period
    actual = average_delay_by_period(df)
    expected = pd.read_pickle(TEST_DIR + "task2d_" + filename)

    # compare actual and expected
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by average_delay_by_period not as expected\n" + message

def test_task2e_full():

    filename = "asqp"
    df = pd.read_pickle(TEST_DIR + "task1_" + filename)

   # run df through student underperforming_carriers
    actual = underperforming_carriers(df)
    expected = pd.read_pickle(TEST_DIR + "task2e_" + filename)

    # compare actual and expected
    result, message = compare_dataframes(actual, expected)
    assert result, "DataFrame returned by underperforming_carriers not as expected\n" + message

def task3_helper(actual_filename, expected_filename):

    actual = read_and_process_npy(actual_filename)
    expected = np.load(expected_filename)

    assert np.array_equal(actual, expected), "Array returned by read_and_process_npy not as expected"

def test_task3_full():
    task3_helper(DATA_DIR + "delays.npy", TEST_DIR + "task3_delays.npy")

def task4a_helper(actual_filename, expected_filename, w):

    ts = np.load(actual_filename)
    actual = remove_irregularities(ts, w)
    expected = np.load(expected_filename)

    assert np.isclose(actual, expected).all(), "Array returned by remove_irregularities not as expected"

def test_task4a_full_0():

    w = 1
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4a_delays_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_full_1():

    w = 2
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4a_delays_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def test_task4a_full_2():

    w = 3
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4a_delays_w" + str(w) + ".npy"
    task4a_helper(actual_filename, expected_filename, w)

def task4b_helper(actual_filename, expected_filename, w):

    ts = np.load(actual_filename)
    actual = remove_trend(ts, w)
    expected = np.load(expected_filename)

    assert np.isclose(actual, expected).all(), "Array returned by remove_irregularities not as expected"

def test_task4b_full_0():

    w = 1
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4b_delays_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def test_task4b_full_1():

    w = 2
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4b_delays_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def test_task4b_full_2():

    w = 1
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4b_delays_w" + str(w) + ".npy"
    task4b_helper(actual_filename, expected_filename, w)

def task4c_helper(actual_filename, expected_filename, w, expected_month):

    ts = np.load(actual_filename) 
    actual_buckets, actual_month = is_seasonal(ts, w)
    expected_buckets = np.load(expected_filename)

    assert np.isclose(actual_buckets, expected_buckets).all(), "Array returned by is_seasonal not as expected"
    assert actual_month == expected_month, "Month returned by is_seasonal not as expected"

def test_task4c_0():

    w = 1
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4c_delays_w" + str(w) + ".npy"
    expected_month = 6

    task4c_helper(actual_filename, expected_filename, w, expected_month)

def test_task4c_1():

    w = 2
    actual_filename = DATA_DIR + "task3_delays.npy"
    expected_filename = DATA_DIR + "task4c_delays_w" + str(w) + ".npy"
    expected_month = 6

    task4c_helper(actual_filename, expected_filename, w, expected_month)