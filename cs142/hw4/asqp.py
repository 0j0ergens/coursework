"""
CMSC 14200, Winter 2023
Homework #4

People Consulted:
   List anyone (other than the course staff) that you consulted about
   this assignment.

Online resources consulted:
    map function https://cmdlinetips.com/2018/01/how-to-add-a-new-column-to-using-a-dictionary-in-pandas-data-frame/
    booleans https://datatofish.com/if-condition-in-pandas-dataframe/
    datetime https://pandas.pydata.org/docs/reference/api/pandas.to_datetime.html#pandas.to_datetime
"""

import numpy as np
import pandas as pd
import utils
import os

def read_and_process_asc(filename):
    """
    Read in and process a ASC file from the ASQP data set

    Input:
        filename (string): name of the file

    Returns (Pandas DataFrame): a Pandas DataFrame with the ASQP data
    """
   
    col_types = {}

    for name in utils.MIL_TIME + utils.FL_NUMS: 
        col_types[name] = str 
    
    if os.path.exists(filename):
        df = pd.read_csv(filename, sep = '|', low_memory=False, dtype=col_types)
        df['Date'] = (pd.to_datetime(df['Date'], format='%Y%m%d'))
        date_str = df['Date'].astype(str)
        df['Year'] = pd.DatetimeIndex(df['Date']).year
        df['Month'] = pd.DatetimeIndex(df['Date']).month
        df['Day'] = pd.DatetimeIndex(df['Date']).day 
        df['Day of Week'] = df['Date'].dt.day_name()
        
        for name in utils.MIL_TIME: 
            df[name] = df[name].str.zfill(4)
            df[name] = pd.to_datetime(df[name], format = '%H%M', \
            errors='coerce')

        bins =  [0, 5, 11, 17, 23]
        periods = ["Overnight", "Morning", "Afternoon", "Evening"]
        dep = (pd.DatetimeIndex(df['Departure Scheduled CRS']).hour)
        df['Period'] = pd.cut(dep, bins, labels=periods, include_lowest=True)
        df['Operator'] = df['Actual Operating Carrier'].replace(utils.CARRIERS)
        df['Mainline'] = 'Regional'
        df.loc[df['Actual Operating Carrier'].isin(utils.MAINLINE), 'Mainline'] = 'Mainline'
        df['Cancellation Code'] = df['Cancellation Code']\
        .map(utils.CANCELLATIONS)
        df.rename(columns={'Cancellation Code':'Cancellation Reason'}, \
        inplace=True)
        df['Cancelled?'] = df['Cancellation Reason'].notnull()
        df['Delayed?'] = df['Arrival Delay'] >= 15

        return(df)

    return None 
    
def delay_and_cancel_fractions(df):
    """
    Given ASQP data, compute the fraction of delayed and cancelled flights

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (tuple of floats): fraction of flights that were delayed,
        fraction of flights that were cancelled
    """ 
    delayed = len(df[df['Delayed?']])
    cancelled = len(df[df['Cancelled?']])
    total = len(df)

    return(delayed/total, cancelled/total)

def per_carrier_delays_cancels(df):
    """
    Given ASQP data, determine how many of each carrier's flights were
        delayed or cancelled

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (tuple of DataFrame): delays by carrier, cancellations per carrier
    """
    cancelled = df[df['Cancelled?']]
    delayed = df[df['Delayed?']]

    return (delayed['Operator'].value_counts().to_frame(), \
        cancelled['Operator'].value_counts().to_frame())

def nonearly(df):
    """
    Returns the dataset of all flights that did not arrive early. 

    Input:
        df (DataFrame): an ASQP DataFrame
    
    Returns (dataframe): all columns of flights that did not arrive early
    """
 
    return(df[df['Arrival Delay']>=0])

def average_delay(df):
    """
    Given ASQP data, determine the average flight delay

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (float): the average delay
    """

    return(nonearly(df)['Arrival Delay'].mean())

def average_delay_by_period(df):
    """
    Given ASQP data, determine whether or not delays get worse throughout
        the day

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (DataFrame): the average delay per period of day
    """
    return(nonearly(df).groupby(['Period'])['Arrival Delay'].mean().to_frame())

def underperforming_carriers(df):
    """
    Given ASQP data, determine which carriers have a worse than average delay

    Input:
        df (DataFrame): an ASQP DataFrame

    Returns (DafaFrame): underperforming carriers and their average delay
    """

    avs = nonearly(df).groupby(['Operator'])['Arrival Delay'].mean().to_frame()
    return(avs[avs['Arrival Delay'] > average_delay(df)])

def read_and_process_npy(filename):
    """
    Read in and process time series ASQP data

    Input:
        filename (string): name of the NPY file

    Returns (NumPy array): a time series NumPy array
    """
    if os.path.exists(filename):
        delays = np.load(filename)
        return(np.sum(delays>=60, axis=1))
    
    return None 

def remove_irregularities(ts, width):
    """
    Apply a smoothing technique to remove irregularities from the
        times series ASQP data

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe

    Returns (NumPy array): smoothed time series data

    For every element i in the time series, replace that value with 
    the average over the elements in the interval [i-width, i+width] 
    (both sides inclusive), where the width is a parameter to the function.
     If i-width or i+width is outside of the bounds of the array, truncate the 
     interval so that it stays in bounds. (That is, take the largest possible 
     interval around i, but if i is close to the start or end of the array, 
     you will be taking the average of fewer values).
    """
  
    new = np.zeros(len(ts))

    for i in range(len(ts)): 
        beginning = max(0, i-width)
        end = min(i+width, len(ts))
        new[i] = ts[beginning:end+1].mean()
        
    return(new)   

def remove_trend(ts, width):
    """
    Remove overall trend from time series ASQP data

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe

    Returns (NumPy array): detrended time series data
    """
    new = np.zeros(len(ts))
    array = remove_irregularities(ts, width)
    m = utils.perform_least_squares(array)[0]
    b = utils.perform_least_squares(array)[1]

    for i in range(len(ts)):
        line = m * i 
        new[i] = ts[i] - line

    return(new)

def is_seasonal(ts, width):
    """
    Bucket late flights, determine the bucket with the most
        late flights

    Input:
        ts (NumPy array): the time series
        width (int): the width over which to smoothe

    Returns (NumPy array, int): number of delays in each month,
        the index of the month with the most delays (January = 0, etc.)
    """
    return None

    
    
