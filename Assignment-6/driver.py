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
import decrypt as dc

# Basic tests
# The points are per test points. The number of tests that passed or failed directly from C test-suite
tests_json = """{
  "factorial": {
      "python3 decrypt.pyc -F Factorial_Pipeline.enc -C Factorial_Pipeline.csv": 10
      },
  "fibonacci": {
      "python3 decrypt.pyc -F Fibonacci_Pipeline.enc -C Fibonacci_Pipeline.csv": 10
      },
  "jtable": {
      "python3 decrypt.pyc -F JTable.enc -C JTable.csv": 10
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
        if(p.returncode != 0):
            Error += "### " + "*"*5+steps+"*"*5
            Error += "\n ```" + stdout_data.decode()
            Error += "\n```\n"
            PassOrFail = p.returncode
        else:
            points += test[steps]
            Success += "### " + "*"*5+steps+"*"*5
            Success += "\n ```" + stdout_data.decode() + "\n```\n"
        if points < total:
            Final[name] = {"mark": points,
                           "comment": "Program exited with return code"+str(p.returncode)}
        else:
            Final[name] = {"mark": points,
                           "comment": "Program ran and output matched."}


def runtrans(test, name):
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
        result_string = ""
        for lines in out_lines:
            if b"AUTORESULT_STRING=" in lines:
                points += int(re.findall(r'\d+', lines.decode('utf-8'))[0])
                print(int(re.findall(r'\d+', lines.decode('utf-8'))[0]))
        if (p.returncode == 0):
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
                                   "comment": "Program exited with return code Or Output did not match. Answer (cache size = {0}, assoc = {1}, blocksize = {2}".format(size, assoc, block)}
        else:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program ran and output matched."}


def main():
        # Parse the command line arguments

    # Basic Tests
    test_dict = json.loads(tests_json)
    for parts in test_dict.keys():
        runtests(test_dict[parts], parts)

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
