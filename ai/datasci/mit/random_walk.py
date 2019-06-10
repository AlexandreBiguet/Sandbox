
import numpy as np
import random
from dataclasses import dataclass

random.seed(0)


@dataclass
class Location:
    _x: float
    _y: float

    def __init__(self, *args):
        if len(args) != 2:
            raise ValueError('Location init takes two parameters: x, y')
        self._x = args[0]
        self._y = args[1]

    def __add__(self, other):
        # return Location(self._x + other.x, self._y + other.y)
        return Location(self._x + other.x, self._y + other.y)

    def __mul__(self, other):
        return Location(self._x * other, self._y * other)

    def move(self, dx, dy):
        return Location(self._x + dx, self._y + dy)

    def dot(self, other):
        return self.x * other.x + self.y * other.y

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    def dist_squared(self, other_loc):
        return (self._x - other_loc.x)**2 + (self._y - other_loc.y)**2


def simple_test_location():
    loc = Location(1, 2)
    loc = loc.move(1, 1)
    print(loc)
    loc1 = Location(1, 1)
    loc2 = Location(2, 2)
    print(loc1 + loc2)
    loc1 += loc2
    print(loc1)


@dataclass
class Field:
    _drunks: dict

    def add_drunk(self, drunk, loc):
        if drunk in self._drunks:
            raise ValueError('The drunk [{}] is already in the field', drunk)
        self._drunks[drunk] = loc

    def get_location(self, drunk):
        if drunk not in self._drunks:
            raise ValueError('Drunk [{}] not in field', drunk)
        return self._drunks[drunk]

    def move(self, drunk):
        if drunk not in self._drunks:
            raise ValueError('Drunk [{}] not in field', drunk)
        self._drunks[drunk.name] = drunk.step()


@dataclass
class Drunk:
    _name: str
    _max_step: float
    _n_trial: int

    def __init__(self, name, max_step=1.0, n_trial=100):
        self._name = name
        self._max_step = max_step
        self._n_trial = n_trial

    @property
    def name(self):
        return self._name

    @property
    def max_step(self):
        return self._max_step

    def _get_random_loc(self):
        loc = Location(random.uniform(0.0, self._max_step),
                       random.uniform(0.0, self._max_step))
        return loc

    def step(self):
        n_trial = 0
        loc = self._get_random_loc()
        while loc.dist_squared(Location(0., 0.)) > self._max_step**2 \
                and n_trial < self._n_trial:
            loc = self._get_random_loc()
            n_trial += 1
        return loc


@dataclass
class OrientedDrunk(Drunk):
    _favorite_direction: Location
    _favorite_direction_name: str

    def __init__(self, name, favorite_direction='North'):
        super(OrientedDrunk, self).__init__(name=name)
        self._favorite_direction_name = favorite_direction
        self._set_favorite_direction()

    def _set_favorite_direction(self):
        if self._favorite_direction_name == 'North':
            self._favorite_direction = Location(.0, 1.)
        elif self._favorite_direction_name == 'South':
            self._favorite_direction = Location(.0, -1.)
        elif self._favorite_direction_name == 'East':
            self._favorite_direction = Location(1., 0.)
        elif self._favorite_direction_name == 'West':
            self._favorite_direction = Location(-1., 0.)
        else:
            raise ValueError('favorite_direction should be in "North", '
                             '"South", "East" or "West" [value is {}]'.format(
                              self._favorite_direction_name))

    @property
    def favorite_direction(self):
        return self._favorite_direction

    def step(self):
        # Usual drunk step
        loc = super(OrientedDrunk, self).step()
        max_try = 10
        ntry = 0
        while loc.dot(self._favorite_direction) <= 0 and ntry != max_try:
            loc = super(OrientedDrunk, self).step()
            ntry += 1
        return loc


@dataclass
class SquareDrunk(Drunk):
    def __init__(self, name):
        super(SquareDrunk, self).__init__(name=name)

    @staticmethod
    def get_possible_moves():
        return [(1.0, 0.0), (0.0, 1.0), (-1.0, 0.0), (0.0, -1.0)]

    @staticmethod
    def get_random_loc():
        return Location(*random.choice(SquareDrunk.get_possible_moves()))

    def _get_random_loc(self):
        return self.get_random_loc()


@dataclass
class SquareOrientedDrunk(OrientedDrunk):
    def __init__(self, *args, **kwargs):
        super(SquareOrientedDrunk, self).__init__(*args, **kwargs)

    def step(self):
        loc = SquareDrunk.get_random_loc()
        max_try = 10
        ntry = 0
        while loc.dot(self._favorite_direction) <= 0 and ntry != max_try:
            loc = SquareDrunk.get_random_loc()
            ntry += 1
        return loc


@dataclass
class Simulation:
    _field : Field
    _n_steps: int

    def walk(self, drunk):
        start = self._field.get_location(drunk)
        for step in range(self._n_steps):
            self._field.move(drunk)
        pos = self._field.get_location(drunk)
        return np.sqrt(pos.dist_squared(start))


def simple_test_drunks():
    normal_drunk = Drunk('jacky')
    print(normal_drunk)
    print(normal_drunk.step())
    east_drunk = OrientedDrunk(name='jacky', favorite_direction='East')
    print(east_drunk)
    print('normal drunk step : ', normal_drunk.step())
    print('east drunk step : ', east_drunk.step())

    square_drunk = SquareDrunk(name='Jack')
    print('square normal drunk: ', square_drunk.step())

    square_oriented_drunk = SquareOrientedDrunk(name='Jim',
                                                favorite_direction='South')
    print('square oriented drunk: ', square_oriented_drunk.step())


def main():
    simple_test_location()
    simple_test_drunks()
    print('\n\n')

    drunk = SquareDrunk('Johnny')
    field = Field({drunk.name: Location(0.0, 0.0)})
    sim = Simulation(field, 1000)
    print('distance from start for ', drunk.name, ' : ', sim.walk(drunk))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('Interrupted by user')
