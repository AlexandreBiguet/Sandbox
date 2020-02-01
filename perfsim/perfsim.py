import names
import random
import math
import csv
import os


class Person:
    def __init__(self, **kwargs):
        self.maximum_task_number_per_time_unit = kwargs[
            'maximum_task_number_per_time_unit']
        self.time_unit_needed_to_reach_full_performance = kwargs[
            'time_unit_needed_to_reach_full_performance']
        self.seniority = 0
        self.name = kwargs['name']

    def __str__(self):
        value = str(self.name) + ' ' + str(self.seniority) + ' ' + str(
            self.time_unit_needed_to_reach_full_performance) + ' ' + str(
            self.maximum_task_number_per_time_unit)
        return value


class TeamGenerator:
    def __init__(self, team_size):
        self.team_size = team_size
        self.task_range = (10, 20)
        self.time_to_max_perf_range = (2, 10)

    def random_generator(self, seed=0):
        random.seed(seed)
        team = []
        for _ in range(0, self.team_size):
            args = {'name': names.get_full_name(),
                    'maximum_task_number_per_time_unit': random.randint(
                        *self.task_range),
                    'time_unit_needed_to_reach_full_performance': random.randint(
                        *self.time_to_max_perf_range)
                    }
            team.append(Person(**args))
        return team


class Simulator:
    class _State:
        def __init__(self, initial_team):
            self.team = initial_team
            self.current_time_unit = 0
            self.performed_task = {}

        def __str__(self):
            output = 'time: ' + str(self.current_time_unit) + '\n'
            for name, task in self.performed_task.items():
                output = output + name + ' ' + str(task) + '\n'
            return output

    def __init__(self, initial_team, **kwargs):
        self.max_time_unit_number = kwargs['max_time_unit_number']
        self.state = self._State(initial_team)
        os.makedirs('./simulation_outputs/', exist_ok=True)
        self.output_filename = './simulation_outputs/simulation.csv'

    def simulate(self):
        with open(self.output_filename, 'w', newline='') as csvfile:
            fieldnames = [person.name for person in self.state.team]
            fieldnames.insert(0, 'iter')
            writer = csv.DictWriter(csvfile, delimiter=';',
                                    fieldnames=fieldnames)
            writer.writeheader()

            for t in range(1, self.max_time_unit_number + 1):
                print(self.state)
                self._update()
                row = {'iter': t}
                row.update(self.state.performed_task)
                writer.writerow(row)
                self.state.current_time_unit = self.state.current_time_unit + 1

    def _update(self):
        for person in self.state.team:
            self.state.performed_task[person.name] = self._performed_task(
                person)
            person.seniority = person.seniority + 1

    def _performed_task(self, person):
        ratio = self.state.current_time_unit / person.time_unit_needed_to_reach_full_performance
        if ratio >= 1:
            ratio = 1
        return math.floor(ratio * person.maximum_task_number_per_time_unit)


# TODO: implement in the simulation the fact that some new people can arrive
#  and simulate the time used to get them trained by the other people of the
#  team.

if __name__ == '__main__':
    generator = TeamGenerator(4)
    team = generator.random_generator()
    simulation = Simulator(team, max_time_unit_number=10)
    simulation.simulate()
