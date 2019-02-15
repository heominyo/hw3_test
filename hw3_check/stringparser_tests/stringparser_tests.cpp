//
// CS104 StringParser tests
//

#include "stringparser_utils.h"

TEST(StringParser, UltraBasic)
{
	EXPECT_PARSE("a", "a");
}

TEST(StringParser, BlankLine)
{
	EXPECT_PARSE("", ""); // NOLINT
}

TEST(StringParser, OneRemStart)
{
	EXPECT_PARSE(">string", "tring");
}

TEST(StringParser, TwoRemStart)
{
	EXPECT_PARSE(">>astring", "tring");
}

TEST(StringParser, OneRemBack)
{
	EXPECT_PARSE("<string", "strin");
}

TEST(StringParser, SimpleAddition)
{
	EXPECT_PARSE("(a+b)", "ab");
}

TEST(StringParser, QuadAddition)
{
	EXPECT_PARSE("(a + b + c + d)", "abcd");
}

TEST(StringParser, NestedAddition)
{
	EXPECT_PARSE("( a + ( b + cde ) )", "abcde");
}

TEST(StringParser, MultiNestedAddition)
{
	EXPECT_PARSE("(( a + b ) + ( c + def) )", "abcdef");
}

TEST(StringParser, NoopSubtraction)
{
	EXPECT_PARSE("(a - b)", "a");
}

TEST(StringParser, SimpleSubtraction)
{
	EXPECT_PARSE("(abc - c)", "ab");
}

TEST(StringParser, MultiCharSubtraction)
{
	EXPECT_PARSE("(abcdefg - bcdefg )", "a");
}

TEST(StringParser, InnerTextSubtraction)
{
	EXPECT_PARSE("( abcdefghij - bcd)", "aefghij");
}

TEST(StringParser, RepeatedTextSubtraction)
{
	EXPECT_PARSE("( abcabcabcabc - bc )", "aabcabcabc");
}

TEST(StringParser, NestedSubtraction)
{
	EXPECT_PARSE("( abcdefg - (bcdef - ( cdef - f)))", "abcdefg");
}

TEST(StringParser, MultiNestedSubtraction)
{
	EXPECT_PARSE("( ( input - in ) - ( txt - xt) )", "pu");
}

TEST(StringParser, NestedSubtraction2)
{
	EXPECT_PARSE("( abcdeg - (abc - c) )", "cdeg");
}

TEST(StringParser, Example1)
{
	EXPECT_PARSE("(<<dagobah -(>>yoda+go ))", "b");
}

TEST(StringParser, Example2)
{
	EXPECT_PARSE("<> <<<((eve + boo+buzz)  - ( >< <nemo))", "eboo");
}

TEST(StringParser, Example3)
{
	EXPECT_PARSE("<>((<<mario + >>zelda)- ><samus)", "arld");
}

TEST(StringParser, GeneralMix)
{
	EXPECT_PARSE("<> ((malformed + case + that)  -  >< took) ", "alformedcasetha");
}

TEST(StringParser, NestedParenthesis)
{
	EXPECT_PARSE("((< to +write)) ", "twrite");
}

TEST(StringParser, UnaryBinaryPrecedence)
{
	EXPECT_PARSE("(<<(>>which + <<operates) - >><<first)", "ichope");
}

TEST(StringParser, Multiline)
{
	// Most of these tests are not multiline.
	// This is because if one input makes your program crash, we don't want
	// to double-dip you for subsequent test cases in that file.

	std::string input = "(your + program)\n"
	                    "(shouldb - b)\n"
	                    "<<(able + to )\n"
	                    ">>accommondate\n"
	                    "(all + these + cases)\n";

	std::vector<std::string> expectedOutput = {
			"yourprogram",
			"should",
			"able",
			"commondate",
			"allthesecases"
	};

	std::stringstream actualOutput;
	ASSERT_TRUE(runStringparserProgram(input, actualOutput));

	for(std::string const & expectedLine : expectedOutput)
	{
		std::string actualOutputLine;
		std::getline(actualOutput, actualOutputLine);
		EXPECT_EQ(expectedLine, actualOutputLine);
	}
}

TEST(StringParser, NoParenthesis)
{
	EXPECT_PARSE("noparens", "noparens");
}

TEST(StringParserMalformed, Capitals)
{
	EXPECT_MALFORMED("(AAAARGH)");
}


TEST(StringParserMalformed, MixedOperators)
{
	EXPECT_MALFORMED("(mixed + up - operators)");
}

TEST(StringParserMalformed, MultipleSubtraction)
{
	EXPECT_MALFORMED("(multiple - minus - here)");
}

TEST(StringParserMalformed, NoParenthesisAddition)
{
	EXPECT_MALFORMED("no + prenthesis + add");
}

TEST(StringParserMalformed, ExtraOperators)
{
	EXPECT_MALFORMED("( + extra + operator + here)");
}

TEST(StringParserMalformed, Example1)
{
	EXPECT_MALFORMED("((<mccoy+sulu)");
}

TEST(StringParserMalformed, Example2)
{
	EXPECT_MALFORMED("(leonardo-foot+splinter)");
}

TEST(StringParserMalformed, Example3)
{
	EXPECT_MALFORMED("(+pikachu+charizard)");
}

TEST(StringParserMalformed, RemoveAtEndOfString)
{
	EXPECT_MALFORMED("<(along>  -(<<with+ thefollowing )) ");
}

TEST(StringParserMalformed, MissingParen)
{
	EXPECT_MALFORMED("(malformed - ornot");
}

TEST(StringParserMalformed, NestedParensWithoutOperator)
{
	EXPECT_MALFORMED("(dog + eats(man))");
}

TEST(StringParserMalformed, ExtraParen)
{
	EXPECT_MALFORMED("(seems + (un + bala + (nc +    ed))))");
}

TEST(StringParserMalformed, Smiley)
{
	EXPECT_MALFORMED(":)");
}

// This here is a fun little snippet!
// It allows you to "multiply" a string by a number to make n copies of that string.

std::string operator*(std::string const & string, std::string::size_type times)
{
	std::string sum;

	for(size_t count = 0; count < times; ++count)
	{
		sum.append(string);
	}

	return sum;
}

TEST(StringParserStress, LargeString)
{
	// try parsing a string with 5000 characters
	std::string longString = std::string("b") * 4999;
	std::string input = ">c" + longString;

	EXPECT_PARSE(input, longString);
}
