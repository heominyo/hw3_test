from pathlib import Path
import os
import sys

if(sys.argv[1] == 'ulliststr'):
    os.system("make")
elif sys.argv[1] == 'ststr':
    os.system("make ulliststr.o")
    os.system("g++ -g -Wall -c stackstring.cpp -o stackstring.o")
    os.system("g++ -g -Wall stackstring_test.cpp stackstring.o ulliststr.o -o prog")
elif sys.argv[1] == 'strparse':
    os.system("make stringparser")

if Path("prog").exists():

    os.system("valgrind --leak-check=yes ./prog")
    # os.system("./prog")
    os.system("rm prog")
else:
    print("Compilation Error")
