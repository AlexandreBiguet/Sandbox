"""
Building a model of housing price in california
data : California Housing Prices Dataset (1990)

"""


import os
import pandas as pd
import numpy as np
import datetime

from fetch import fetch_data

import matplotlib.pyplot as plt

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
LOCAL_DATASET_PATH = CURRENT_DIR + '/datasets'
DL_ROOT = 'https://raw.githubusercontent.com/ageron/handson-ml/master/'
HOUSING_URL = DL_ROOT + 'datasets/housing/housing.tgz'
OUTPUT_PATH = CURRENT_DIR + '/outputs/housing/'


def fetch_housing_data():
    fetch_data(remote_path=HOUSING_URL,
               local_path_prefix=LOCAL_DATASET_PATH,
               local_path='housing/housing.tgz')


def explore_data(data, path_prefix):

    if not os.path.isdir(path_prefix):
        os.makedirs(path_prefix)

    print(data.info(), '\n')
    print(data.describe(), '\n')
    print(data.head(5), '\n')
    print(data['ocean_proximity'].value_counts(), '\n')
    data.hist(bins=70, figsize=(20, 15), xrot=15)
    plt.savefig(path_prefix + 'data_hists.pdf')

    plt.figure()
    data['median_house_value'].hist(bins=60)
    plt.savefig(path_prefix + 'median_house_value.pdf')

    plt.figure()
    data['housing_median_age'].hist(bins=50)
    plt.savefig(path_prefix + 'housing_median_age')


def split_data_set(data, method, **kwargs):
    """
    Creating a test set to avoid data snooping bias.

    :param data: the data
    :param method: splitting method type
    :param kwargs: arguments specific to the split method being called
            * random split :
               - seed : the seed to be used for random number generator
               - ratio : ratio of data to used for the test set
    :return: [training set, test set]
    """

    if method == 'random split':
        return _create_test_set_random_split(data, **kwargs)
    elif method == 'identifier hash':
        return _create_test_set_hash_id(data, **kwargs)


def _create_test_set_random_split(data, ratio=0.2, seed=42):
    """
    Creates a training and a test set using a random approach.
    The
    :param data: the data
    :param ratio: the ratio of data to be used for the test set
    :param seed: seed to use for random number generator. seed < 0,
                 seed is not specified.
    :return: [training set, test set]
    """

    if seed >= 0:
        np.random.seed(seed)

    shuffled_idx = np.random.permutation(len(data))
    test_set_size = int(len(data) * ratio)
    test_idx = shuffled_idx[:test_set_size]
    train_idx = shuffled_idx[test_set_size:]
    return data.iloc[train_idx], data.iloc[test_idx]


def get_random_split_path():

    return OUTPUT_PATH + \
           datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S') + '/'


def _create_test_set_hash_id(data, ratio=0.2, hash):


if __name__ == '__main__':

    fetch_housing_data()
    housing_data = pd.read_csv(LOCAL_DATASET_PATH+'/housing/housing.csv')
    explore_data(housing_data, path_prefix=OUTPUT_PATH + 'full_data/')

    housing_train_data, housing_test_data \
        = split_data_set(housing_data, method='random split')

    explore_data(housing_train_data, path_prefix=OUTPUT_PATH + 'training_data/')
    explore_data(housing_test_data, path_prefix=OUTPUT_PATH + 'test_data/')