"""
CMSC 14200, Winter 2023
Homework #4

Module for miscellaneous definitions and functions
"""

import numpy as np

TIME_SERIES_DATA_LEN = 36

DAYS_OF_WEEK = {
    1: "Monday",
    2: "Tuesday",
    3: "Wednesday",
    4: "Thursday",
    5: "Friday",
    6: "Saturday",
    7: "Sunday"
}

CARRIERS = {
    "9E": "Endeavor",
    "AA": "American",
    "AS": "Alaska",
    "AX": "Trans States",
    "B6": "JettBlue",
    "C5": "CommutAir",
    "CP": "Compass",
    "DL": "Delta",
    "EM": "Empire",
    "EV": "ExpressJet",
    "F9": "Frontier",
    "G4": "Allegiant",
    "G7": "GoJet",
    "HA": "Hawaiian",
    "KS": "PenAir",
    "MQ": "Envoy",
    "NK": "Spirit",
    "OH": "PSA",
    "OO": "SkyWest",
    "PT": "Piedmont",
    "QX": "Horizon",
    "UA": "United",
    "WN": "Southwest",
    "YV": "Mesa",
    "YX": "Republic",
    "ZW": "Air Wisconsin",
}

MIL_TIME = ['Landing', 'Takeoff','Departure Scheduled CRS', \
            'Departure Scheduled OAG','Arrive Scheduled OAG', \
                'Arrive Scheduled CRS', 'Departure Actual Gate', \
                    'Arrive Actual Gate']

FL_NUMS = ['Marketing Carrier Flight Number', \
            'Planned Operating Carrier Flight Number', \
                'Actual Operating Carrier Flight Number']

MAINLINE = ["AA", "DL", "WN", "UA"]

CANCELLATIONS = {
    "A": "Carrier Caused",
    "B": "Weather",
    "C": "NAS",
    "D": "Security"
}

def perform_least_squares(y):
    """
    Given a data set, finds the line best fit perform least squares

    Input:
        y (array): data

    Returns (tuple of floats): the slope and y-intercept of the
        line fitted to y
    """

    x = np.arange(len(y))
    A = np.vstack([x, np.ones(len(y))]).T
    m, b = np.linalg.lstsq(A, y, rcond=None)[0]

    return m, b

#   #figure out the types of the columns: print(df.dtypes)
   
