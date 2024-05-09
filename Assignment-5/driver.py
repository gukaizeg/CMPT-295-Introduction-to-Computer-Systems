#!/usr//bin/python3
#
# driver.py - The driver tests the correctness
import subprocess
import re
import os
import sys
import argparse
import shutil
import json
import cryptography
import math

# Basic tests
# The points are per test points. The number of tests that passed or failed directly from C test-suite
tests_json = """{
   "relu": {
      "make Relu.bin": 0,
      "timeout 60 ./Relu.bin -l": 10
      },
  "reluext": {
      "make ReluEXT.bin": 0,
      "timeout 60 ./ReluEXT.bin -l": 10
      },
  "caxpy": {
      "make Caxpy.bin": 0,
      "timeout 60 ./Caxpy.bin -l": 10
      },
  "soa": {
      "make SoA.bin": 0,
      "timeout 60 ./SoA.bin -l": 10
      },
   "imax": {
      "make Imax.bin": 0,
      "timeout 60 ./Imax.bin -l": 20
      }
  }
"""


Final = {}
Error = ""
Success = ""
PassOrFail = 0
#
# main - Main function
#


def getlines(log, start, end):
    inRecordingMode = False
    for line in log.splitlines():
        if not inRecordingMode:
            if line.startswith(start):
                inRecordingMode = True
        elif line.startswith(end):
            inRecodingMode = False
        else:
            yield(line)


def runtests(test, name):
    total = 0
    points = 0
    global Success
    global Final
    global Error
    global PassOrFail
    for steps in test.keys():
        print(steps)
        p = subprocess.Popen(
            steps, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout_data, stderr_data = p.communicate()
        total = total + test[steps]
        # Parse the output
        out_lines = stdout_data.splitlines()
        result_string = list(line for line in getlines(
                stdout_data.decode('utf-8'), "Total Vector Instructions", "Utilized Vector Lanes:"))
        low_util = 0
        if result_string:
            print(result_string)
            util = result_string[0].split(":")[1].strip("%")
            if float(util) < 50 or math.isnan(float(util)):
                low_util = 1
                p.returncode = 1
        if p.returncode == 0:
            Success += "#### " + "*"*5+steps+"*"*5
            Success += "\n ```" + stdout_data.decode() + "\n```\n"
            points += test[steps]
        else:
            Error += "#### " + "*"*5+steps+"*"*5
            Error += "\n ```" + stdout_data.decode()
            Error += "\n```\n"
            PassOrFail = p.returncode
        if points < total:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program exited with error codes or utilization of vector lanes below 50%. Run with program with -l to check"}
        else:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program ran and output matched"}

def runperftests(test, name):
    total = 0
    points = 0
    global Success
    global Final
    global Error
    global PassOrFail
    for steps in test.keys():
        print(steps)
        p = subprocess.Popen(
            steps, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout_data, stderr_data = p.communicate()
        total = total + test[steps]

        # Parse the output
        out_lines = stdout_data.splitlines()
        if p.returncode == 0:
            result_string = list(line for line in getlines(
                stdout_data.decode('utf-8'), "Using default", "\n"))
            if len(result_string) == 1:
                print(result_string)
                calculate = re.search("(\d+)/", result_string[0])
                performance = int(calculate.group(0)[:-1])
                Success += "#### " + "*"*5+steps+"*"*5
                Success += "\n ```" + stdout_data.decode() + "\n```\n"
                points = int(10*(performance/100+0.1))
            else:
                Error += "#### " + "*"*5+steps+"*"*5
                Error += "\n ```" + stdout_data.decode()
                Error += "\n```\n"
                PassOrFail = 1
        else:
            Error += "#### " + "*"*5+steps+"*"*5
            Error += "\n ```" + stdout_data.decode()
            Error += "\n```\n"
            PassOrFail = p.returncode

        if points < total:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program exited with error codes"}
        else:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program ran and output matched.{0}".format(result_string[0])}


def main():
        # Parse the command line arguments

    # Basic Tests
    test_dict = json.loads(tests_json)
    for parts in test_dict.keys():
        runtests(test_dict[parts], parts)

    # test_dict = json.loads(perftests_json)
    # for parts in test_dict.keys():
    #     runperftests(test_dict[parts], parts)

    githubprefix = os.path.basename(os.getcwd())
    Final["userid"] = "GithubID:" + githubprefix
    j = json.dumps(Final, indent=2)

    with open(githubprefix + "_Grade"+".json", "w+") as text_file:
        text_file.write(j)

    with open("LOG.md", "w+") as text_file:
        text_file.write("## " + '*'*20 + 'FAILED' + '*'*20 + '\n' + Error)
        text_file.write("\n" + "*" * 40)
        text_file.write("\n## " + '*'*20 + 'SUCCESS' + '*'*20 + '\n' + Success)

    sys.exit(PassOrFail)

    # execute main only if called as a script
if __name__ == "__main__":
    main()
