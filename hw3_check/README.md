# CS104 HW3 Checker

This checker contains a subset of the tests that we'll grade your homework on.  It's meant to help verify that the basic functionality of your program works, but it doesn't cover every corner case.

### Using the Tests
1. Copy this directory into your `hw3` folder
2. Open a terminal and cd into `hw3_check`
3. Initialize the test suite by running `cmake .`.  _You should only do this once!  Never run CMake again! Just run make and ctest!_
4. Build the code: `make`
5. Run the tests: `ctest --output-on-failure`

### Dealing with Failures

If tests are failing, first and foremost, look at the output!  That will usually give you a clue about what's going on and how you can reproduce it.

If that doesn't help, you can try debugging the tests.  New in this test suite is a feature we call Auto-Debug!  You can now run GDB on a specific test without worrying about specific executables and test case names.  

Let's say some test, like `ListPlus.EmptyPlusEmpty`, is failing.  You just take the name of that test, put `make debug-` before it, and run that on the command line.

```
➜  hw3 make debug-ListPlus.EmptyPlusEmpty
[100%] Debugging ListPlus.EmptyPlusEmpty with GDB...
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /home/cs104/Documents/cs104-cp/cmake-dirs/hw3/operators_tests/operators_tests...done.
(gdb) 
```

Bam!  GDB opens, and it's run with arguments (`--gtest_filter`) that make it run only that specific test. This should make test failures a bit easier to debug.

However, keep in mind that Auto-Debug **only** works with tests where your functions get called directly from our GTest cases, as opposed to your executable being run.  When it's an executable, you want to debug your own executable, not our test cases.  

Luckily, whenever we run one of your executables, we print out the full command line we're using, so you can just plonk that into GDB and get down to business.

### CMake Issues

CMake is really cool, but it can be a bit temperamental.  If you ever move the `hw3_check` directory after you've run `cmake .`, then it will start giving you an error, like
```
CMake Error: The current CMakeCache.txt directory <...> is different than the directory <...> where CMakeCache.txt was created.
```

Don't worry, there's an easy fix!  Just run this:
```sh
rm -rf CMakeFiles CMakeCache.txt
```
Then run `cmake .` again.  That should sort things out!