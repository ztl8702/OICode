import sys
import os
import subprocess
from random import randint

def genTestData(n=10, count = 5):
    with open('test.in', "w") as f:
        f.write(str(n)+'\n')
        vst = set()
        for i in range(count): 
            x = randint(1,n)
            while (x in vst):
                x = randint(1,n)
            if (x not in vst):
                vst.add(x)
                f.write(str(x))
                if i!=count-1:
                    f.write(' ')
        f.write('\n')


for i in range(1000):
    print(f"Round {i}: ", flush=True, end='')
    genTestData(20,10)

    subprocess.run(["powershell", "-Command", "& {rm -Force abfs.out}"])
    subprocess.run(["powershell", "-Command", "& {rm -Force asearch.out}"])
    
    subprocess.run(["powershell", "-Command", "Get-Content test.in | ./abfs > abfs.out"])
    subprocess.run(["powershell", "-Command", "Get-Content test.in | ./asearch > asearch.out"])

    p = subprocess.Popen(["powershell", "-Command","& {(diff (Get-Content asearch.out) (Get-Content abfs.out)).Count}"],stdout=subprocess.PIPE)
    output, error = p.communicate()
    if (output.strip().decode('utf-8')!='0'):
        print("error!")
        exit(-1)

    
    print("ok")

