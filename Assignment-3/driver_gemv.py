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
  "dot": {
      "timeout 120 java -jar venus.jar ./test_files/test_dot.s > ./out/test_dot.out": 0,
      "diff ./out/test_dot.out ./ref/test_dot.out": 10
      },
  "gemv": {
      "timeout 120 java -jar venus.jar ./test_files/test_gemv.s > ./out/test_gemv.out": 0,
      "diff ./out/test_gemv.out ./ref/test_gemv.out": 10
      },
  "read_matrix": {
      "timeout 120 java -jar venus.jar ./test_files/test_read_matrix.s > ./out/test_read_matrix.out": 0,
      "diff ./out/test_read_matrix.out ./ref/test_read_matrix.out": 10
      }
    }
"""

simple = """{
  "simple0": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/simple0/bin/v.bin ./inputs/simple0/bin/m.bin -ms -1 > ./out/gemv/simple/simple0.trace" : 0,
    "python3 part2_tester.py gemv/simple/simple0": 5
  },
  "simple1": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/simple1/bin/v.bin ./inputs/simple1/bin/m.bin -ms -1 > ./out/gemv/simple/simple1.trace" : 0,
    "python3 part2_tester.py gemv/simple/simple1": 5
  },
  "simple2": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/simple2/bin/v.bin ./inputs/simple2/bin/m.bin -ms -1 > ./out/gemv/simple/simple2.trace" : 0,
    "python3 part2_tester.py gemv/simple/simple2": 5
  }
 }"""


mnist_gemv = """{
  "mnist-input0": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v0.bin ./inputs/mnist/bin/m.bin -ms -1 > ./out/gemv/mnist/v0.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v0": 10
  },
  "mnist-input1": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v1.bin ./inputs/mnist/bin/m.bin -ms -1 > ./out/gemv/mnist/v1.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v1": 10
  },
  "mnist-input2": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v2.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v2.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v2": 10
  },
  "mnist-input3": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v3.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v3.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v3": 10
  },
  "mnist-input4": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v4.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v4.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v4": 10
  },
  "mnist-input5": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v5.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v5.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v5": 10
  },
  "mnist-input6": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v6.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v6.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v6": 10
  },
  "mnist-input7": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v7.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v7.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v7": 10
  },
  "mnist-input8": {
    "timeout 120 java -jar venus.jar ./test_files/main_gemv.s ./inputs/mnist/bin/v8.bin ./inputs/mnist/bin/m.bin  -ms -1 > ./out/gemv/mnist/v8.trace" : 0,
    "python3 part2_tester.py gemv/mnist/v8": 10
  }  
}"""


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

    # Simple tests (0,1,2)
    test_dict = json.loads(simple)
    if not os.path.exists(output_folder+"/simple"):
        os.makedirs(output_folder+"/simple")
    for parts in test_dict.keys():
        runtests(test_dict[parts], parts)


    # MNIST Tests
    test_dict = json.loads(mnist_gemv)
    if not os.path.exists(output_folder+"/mnist"):
        os.makedirs(output_folder+"/mnist")
    for parts in test_dict.keys():
        runtests(test_dict[parts], parts)

    githubprefix = os.path.basename(os.getcwd())
    Final["userid"] = "GithubID:" + githubprefix
    j = json.dumps(Final, indent=2)

    with open(githubprefix + "_Grade_GEMV"+".json", "w+") as text_file:
        text_file.write(j)

    with open("LOG.md", "w+") as text_file:
        text_file.write("## " + '*'*20 + 'FAILED' + '*'*20 + '\n' + Error)
        text_file.write("\n" + "*" * 40)
        text_file.write("\n## " + '*'*20 + 'SUCCESS' + '*'*20 + '\n' + Success)

    sys.exit(PassOrFail)

    # execute main only if called as a script
if __name__ == "__main__":
    main()
