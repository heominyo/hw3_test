//
// Utilities for string parser tests
//

#include <string>
#include <sstream>
#include <iostream>

#include <gtest/gtest.h>

#ifndef CS104_HW3_TEST_SUITE_STRINGPARSER_UTILS_H
#define CS104_HW3_TEST_SUITE_STRINGPARSER_UTILS_H

/**
 * Runs stringparser on the given input and returns the output, or generates a failure if it couldn't be run.
 * @param input
 * @param output
 * @return
 */
testing::AssertionResult runStringparserProgram(std::string const & input, std::stringstream & output);

#define EXPECT_MALFORMED(inputstring) \
{\
	std::stringstream output;\
	testing::AssertionResult runResult = runStringparserProgram(inputstring, output);\
	if(!runResult)\
	{\
		FAIL() << runResult.message();\
	}\
	else\
	{\
		std::string outputLine;\
		std::getline(output, outputLine);\
		\
		if(outputLine != "Malformed")\
		{\
			ADD_FAILURE() << '\"' << (inputstring) << "\" should have been detected as Malformed, but instead was parsed to \"" << outputLine << '\"';\
		}\
		else\
		{\
			SUCCEED();\
			std::cout << "SUCCESS: \"" << inputstring << "\" was correctly detected as Malformed" << std::endl;\
		}\
	}\
}

#define EXPECT_PARSE(inputstring, outputstring) \
{\
	std::stringstream output;\
	testing::AssertionResult runResult = runStringparserProgram(inputstring, output);\
	if(!runResult)\
	{\
		FAIL() << runResult.message();\
	}\
	else\
	{\
		std::string outputLine;\
		std::getline(output, outputLine);\
		\
		if(outputLine == "Malformed")\
		{\
			ADD_FAILURE() << '\"' << (inputstring) << "\" was valid input, but user program said it was Malformed.";\
		}\
		else if(outputLine != (outputstring))\
		{\
			ADD_FAILURE() << '\"' << (inputstring) << "\" should have been parsed to \"" << outputstring << "\" but instead was parsed to \"" << outputLine << '\"';\
		}\
		else\
		{\
			SUCCEED();\
			std::cout << "SUCCESS: \"" << inputstring << "\" was correctly parsed to \"" << outputstring << "\"" << std::endl;\
		}\
	}\
}

#endif //CS104_HW3_TEST_SUITE_STRINGPARSER_UTILS_H
