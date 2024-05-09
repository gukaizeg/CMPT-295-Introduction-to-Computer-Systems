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


# Basic tests
tests_json = """{
  "sdot": {
      "timeout 120 java -jar venus.jar ./test_files/test_sdot.s > ./out/test_sdot.out": 0,
      "diff ./out/test_sdot.out ./ref/test_sdot.out": 30
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


def main():
        # Parse the command line arguments

    parser = argparse.ArgumentParser()

    parser.add_argument("-D", dest="output",
                        help="output directory", required=True)

    opts = parser.parse_args()
    output_folder = opts.output
    if os.path.exists(output_folder):
        shutil.rmtree(output_folder)

    # Basic Tests
    test_dict = json.loads(tests_json)
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)
    for parts in test_dict.keys():
        runtests(test_dict[parts], parts)

    githubprefix = os.path.basename(os.getcwd())
    Final["userid"] = "GithubID:" + githubprefix
    j = json.dumps(Final, indent=2)

    with open(githubprefix + "_Grade_SPMV"+".json", "w+") as text_file:
        text_file.write(j)

    with open("LOG.md", "w+") as text_file:
        text_file.write("## " + '*'*20 + 'FAILED' + '*'*20 + '\n' + Error)
        text_file.write("\n" + "*" * 40)
        text_file.write("\n## " + '*'*20 + 'SUCCESS' + '*'*20 + '\n' + Success)

    sys.exit(PassOrFail)

    # execute main only if called as a script
if __name__ == "__main__":
    main()
