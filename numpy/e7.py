"""
numpy histograms
"""

import numpy as np
import matplotlib.pyplot as plt


def main():
    mean = 2
    sigma = 0.5
    n = 100000
    vec = np.random.normal(mean, sigma, n)
    hist, bins = np.histogram(vec, bins=n//100, density=True)
    print('bin : \n', bins, '\n')
    print('hist: \n', hist, '\n')
    plt.plot(.5 * (bins[1:] + bins[:-1]), hist)
    plt.show()


if __name__ == '__main__':
    main()
