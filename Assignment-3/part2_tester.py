import re
import sys
import difflib
from pprint import pprint

trace_format = "{0}/{1}.trace"
max_trace = 1000


def run_test(name):
    pass_bool = True
    # open trace
    ref_trace = open(trace_format.format("ref", name), 'r')
    student_trace = open(trace_format.format("out", name), 'r')
    Step = -1

    ref_data = ref_trace.read()
    ref_phases = re.split("\*\*Step.*\n", ref_data)
    student_data = student_trace.read()
    student_phases = re.split("\*\*Step.*\n", student_data)
    ref_phases.pop(0)
    student_phases.pop(0)
    PassOrFail = [0]*len(ref_phases)
    for i in range(len(ref_phases)):
        Step += 1
        try:
            for line in difflib.unified_diff(ref_phases[i].splitlines(), student_phases[i].splitlines()):
                print(line)
                PassOrFail[Step] = 1
        except IndexError:
            PassOrFail[Step] = 1
            print("Student has not completed phase")
    return PassOrFail


if __name__ == "__main__":
    test = sys.argv[1]
    print("")
    print("Starting {0} test".format(test))
    has_failed = run_test(test)
    if 1 in has_failed:
        print("{0} test has failed. Phase {1}".format(
            test, has_failed.index(1)))
        sys.exit(1)
    else:
        print("{0} test has passed.".format(test))
        sys.exit(0)
