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
#import decrypt as dc

# Basic tests
# The points are per test points. The number of tests that passed or failed directly from C test-suite
tests_json = """{
  "mystery0.o": {
      "./cache-test-mystery0.bin": 10
      },
  "mystery1.o": {
      "./cache-test-mystery1.bin": 10
      },
  "mystery2.o": {
      "./cache-test-mystery2.bin": 10
      }
    }
"""

cachetests_json = """{
  "test1": {
      "diff <(./model/cache-ref -v -s 4 -E 1 -b 4 -L -t ./model/traces/fifo_s1.trace) <(./model/cache -v -s 4 -E 1 -b 4 -t ./model/traces/fifo_s1.trace)": 10
      },
  "test2": {
      "diff <(./model/cache-ref -v -s 8 -E 1 -b 5 -L -t ./model/traces/fifo_m1.trace) <(./model/cache -v -s 8 -E 1 -b 5 -t ./model/traces/fifo_m1.trace)": 10
      },
  "test3": {
      "diff <(./model/cache-ref -v -s 10 -E 8 -b 6  -L -t ./model/traces/fifo_l.trace) <(./model/cache -v -s 10 -E 8 -b 6  -t ./model/traces/fifo_l.trace)": 10
      },
 "test4": {
      "diff <(./model/cache-ref -v -s 10 -E 8 -b 6  -L -t ./model/traces/long.trace) <(./model/cache -v -s 10 -E 8 -b 6  -t ./model/traces/long.trace)": 10
      }
    }
"""

twoleveltests_json = """{
"2lvlt1": {
      "diff <(./model/2level-ref -c ./model/2level_1.config  -t ./model/traces/fifo_s2.trace) <(./model/2level -c ./model/2level_1.config -t ./model/traces/fifo_s2.trace)": 10
    },
"2lvlt2": {
      "diff <(./model/2level-ref  -c ./model/2level_2.config -t ./model/traces/long.trace) <(./model/2level -c ./model/2level_2.config -t ./model/traces/long.trace)": 10
    },
"2lvlt3": {
      "diff <(./model/2level-ref -L -c ./model/2level_2.config -t ./model/traces/long.trace) <(./model/2level -L -c ./model/2level_2.config -t ./model/traces/long.trace)": 10
    },
"2lvlt4": {
      "diff <(./model/2level-ref -L -c ./model/2level_3.config -t ./model/traces/long.trace) <(./model/2level -L -c ./model/2level_3.config -t ./model/traces/long.trace)": 10
    }   
    }"""

# Points in this case specified by driver2.py
trans_tests_json = """{
  "test-trans": {
      "python3 ./driver2.py -A": 0
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


def getfields(out_lines):
    block = 0
    size = 0
    assoc = 0
    for lines in out_lines:
        if b"Cache block size" in lines:
            block = int(re.findall(r'\d+', lines.decode('utf-8'))[0])
        elif b"Cache size" in lines:
            size = int(re.findall(r'\d+', lines.decode('utf-8'))[0])
        elif b"Cache associativity" in lines:
            assoc = int(re.findall(r'\d+', lines.decode('utf-8'))[0])
    return size, assoc, block


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
        block = 0
        size = 0
        assoc = 0
        size, assoc, block = getfields(out_lines)
        # Get the answers and check them.
        if (os.environ.get("PASSWORD")):
            answer = dc.getjson()
            if ((block == answer[name]["block"]) and (size == answer[name]["size"]) and (assoc == answer[name]["assoc"]) and (p.returncode == 0)):
                Success += "#### " + "*"*5+steps+"*"*5
                Success += "\n ```" + stdout_data.decode() + "\n```\n"
                points += test[steps]
            else:
                Error += "#### " + "*"*5+steps+"*"*5
                Error += "\n ```" + stdout_data.decode()
                Error += "\n```\n"
                PassOrFail = p.returncode
        else:
            PassOrFail = 1
        if points < total:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program exited with return code Or Output did not match. Answer (cache size = {0}, assoc = {1}, blocksize = {2}".format(size, assoc, block)}
        else:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program ran and output matched."}

def rundifftests(test, name):
    total = 0
    points = 0
    global Success
    global Final
    global Error
    global PassOrFail
    for steps in test.keys():
        print(steps)
        p = subprocess.Popen("/bin/bash -c " + "\"" + steps + "\"", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout_data, stderr_data = p.communicate()
        total = total + test[steps]
        out_lines = stdout_data.splitlines()
        success_cases = 0
        failed_cases = 0
        if(p.returncode != 0):
            Error += "#### " + "*"*5+steps+"*"*5
            Error += "\n ```" + stdout_data.decode()
            Error += "\n```\n"
            PassOrFail = p.returncode
        else:
            points = total
            Success += "#### " + "*"*5+steps+"*"*5
            Success += "\n ```" + stdout_data.decode() + "\n```\n"

        if points < total:
            Final[name.lower()] = {"mark": points,
                                   "comment": "Program exited with return code. Either your output does not match the reference output. Check the log to see if you program has any errors. Also see word-count/out/input.txt and compare against your output. Ensure you are using the prints match exactly as specified. Check hints section on assignment page." + name.lower()+str(p.returncode)}
        else:
            Final[name.lower()] = {"mark": points,
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
    # test_dict = json.loads(tests_json)
    # for parts in test_dict.keys():
    #     runtests(test_dict[parts], parts)

    # Cache Tests
    test_dict = json.loads(cachetests_json)
    for parts in test_dict.keys():
        rundifftests(test_dict[parts], parts)

    # 2-level Tests
    test_dict = json.loads(twoleveltests_json)
    for parts in test_dict.keys():
        rundifftests(test_dict[parts], parts)


    # test_dict = json.loads(trans_tests_json)
    # for parts in test_dict.keys():
    #     runtrans(test_dict[parts], parts)

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
