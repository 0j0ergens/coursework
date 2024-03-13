"""
CMSC 14200, Winter 2023
Homework #3

Do not modify this file!
"""
from math import radians, cos, sin, asin, sqrt

def haversine(lat1, long1, lat2, long2):
    """
    Calculate the great circle distance between two points
    on the earth

    Parameters:
        lat1, long1 : float : latitude and longitude of one position
                              (in decimal degrees)
        lat2, long2 : float : latitude and longitude of a second position
                              (in decimal degrees)
        
    Returns: float : distance in statute miles
    """
    # convert decimal degrees to radians
    lat1, long1, lat2, long2 = map(radians, [lat1, long1, lat2, long2])

    # haversine formula
    dlat = lat2 - lat1
    dlong = long2 - long1
    a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlong / 2)**2
    c = 2 * asin(sqrt(a))

    radius = 3958.8
    mi = radius * c
    return mi

