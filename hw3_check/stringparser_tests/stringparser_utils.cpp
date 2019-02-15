//
// Created by cs104 on 2/10/19.
//

#include "stringparser_utils.h"

#include <user_code_runner.h>

#include <kwsys/Process.h>
#include <kwsys/SystemTools.hxx>

#include <fstream>

testing::AssertionResult runStringparserProgram(std::string const & input, std::stringstream &output)
{
	// get name of current test
	std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();

	// set up file structure
	std::string executablePath = STRINGPARSER_EXECUTABLE; // this definition points to the hw1_teams executable in the build tree
	std::string testFolder = TEST_BINARY_DIR "/stringparser_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// write teams list to file
	std::ofstream inputWriter(inputFilePath);
	inputWriter << input << std::endl;

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath, outputFilePath}, true);
	testing::AssertionResult result = runner.execute();

	if (!result)
	{
		return result;
	}


	// now, get the output
	{
		std::ifstream outputFile(outputFilePath);

		if (!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		// set the output file as the stream's buffer
		output << outputFile.rdbuf();
	}

	return testing::AssertionSuccess();
}