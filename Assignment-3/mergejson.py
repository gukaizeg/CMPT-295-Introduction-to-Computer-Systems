import os
import json

githubprefix = os.path.basename(os.getcwd())

with open(githubprefix + "_Grade_GEMV"+".json", "r") as gemv:
    with open(githubprefix + "_Grade_SPMV"+".json", "r") as spmv:
        gemv_dict = json.load(gemv)
        spmv_dict = json.load(spmv)
        gemv_dict.update(spmv_dict)
    with open(githubprefix + "_Grade"+".json", "w+") as grade:
        grade.write(json.dumps(gemv_dict, indent=2))
    grade.close

