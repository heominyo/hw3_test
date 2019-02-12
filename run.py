from pathlib import Path
import os
import sys

if(sys.argv[1] == 'ulliststr'):
    os.system("make")

if Path("prog").exists():

    os.system("valgrind --leak-check=yes ./prog")
    # os.system("./prog")
    os.system("rm prog")
else:
    print("Compilation Error")
