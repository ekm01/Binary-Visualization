import subprocess
import os

try:
    command = "clang -lm -Wall -Wextra -o main src/main.c"
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

for file in files:
    try:
        args = []
        v = os.path.join(indir, file)
        print("File to be processed: " + file)
        if "." in file:
            s = file.split(".")
            args = [
                "./main",
                v,
                s[0] + "_" + s[1] + ".bmp",
                default_groupsize,
                default_edge,
            ]
        else:
            args = ["./main", v, file + "_" + ".bmp", default_groupsize, default_edge]

        path = os.path.join(outdir, args[2])
        subprocess.run(args, check=True)
        os.rename(args[2], path)
    except Exception as e:
        print("Error running the program!", e)
