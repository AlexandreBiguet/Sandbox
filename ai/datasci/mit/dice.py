from dataclasses import dataclass
import random

random.seed(0)


def get_die_list():
    return [1, 2, 3, 4, 5, 6]


def roll_die(list_of_numbers):
    """
    :return: returns a random integer number in a list of number
    """
    return random.choice(list_of_numbers)


def roll_test(list_of_numbers, n_elements):
    result = ''
    for i in range(n_elements):
        result += str(roll_die(list_of_numbers))
    return result


@dataclass
class SimulationResult:
    theoretical_probability: float
    sample_probability: float
    sample_over_theoretical: float
    variation: float


def roll_sim(list_of_numbers, wanted_result, n_trials):
    """

    :param list_of_numbers:
    :param wanted_result:
    :param n_trials:
    :return:
    """
    total = 0
    n_elements = len(wanted_result)
    for i in range(n_trials):
        result = roll_test(list_of_numbers, n_elements)
        if result == wanted_result:
            total += 1
    th = 1.0/6**n_elements
    s = total/n_trials
    r = s / th
    v = (th - s) / th
    return SimulationResult(th, s, r, v)


def main():
    print('\n')
    print(roll_test(get_die_list(), 4), '\n')
    print(roll_sim(get_die_list(), '1234', 1000000))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')
