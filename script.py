import subprocess
import os
import sys

try:
    command = "clang -lm -Wall -Wextra -o bin_vis src/main.c"
    completed = subprocess.run(command, shell=True, check=True)
except Exception as e:
    print("Error while compiling the program!", e)

outdir = "output"
if not os.path.exists(outdir):
    os.makedirs(outdir)

indir = "input"
files = os.listdir("input")

default_groupsize = "3"
default_edge = "1024"

if len(sys.argv) == 3:
    default_groupsize = sys.argv[1]
    default_edge = sys.argv[2]

for file in files:
    try:
        args = []
        v = os.path.join(indir, file)
        print("File to be processed: " + file)
        if "." in file:
            s = file.split(".")
            args = [
                "./bin_vis",
                v,
                s[0] + "_" + s[1] + ".bmp",
                default_groupsize,
                default_edge,
            ]
        else:
            args = [
                "./bin_vis",
                v,
                file + "_" + ".bmp",
                default_groupsize,
                default_edge,
            ]

        path = os.path.join(outdir, args[2])
        subprocess.run(args, check=True)
        os.rename(args[2], path)
        print()
    except Exception as e:
        print("Error running the program!", e)
        print()
