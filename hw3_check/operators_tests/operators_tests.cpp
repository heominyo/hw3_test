//
// CS104 Operators test suite
//

#include "list_utils.h"

#include <random_generator.h>

TEST(ListCopy, OneElement)
{
	ULListStr list1;
	list1.push_back("foo");

	ULListStr list2(list1);

	EXPECT_EQ(1, list2.size());
	EXPECT_EQ("foo", list2.get(0));
}

TEST(ListCopy, NoElements)
{
	ULListStr list1;
	ULListStr list2(list1);

	EXPECT_EQ(0, list2.size());
}

TEST(ListCopy, 15Elements)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(15, 42, 4, false);

	ULListStr const * list1 = makeList(contents);

	ULListStr list2(*list1);

	EXPECT_TRUE(checkListContent(&list2, contents));

	delete list1;
}

// this test is in case someone uses const_cast or "mutable" declarations or something to try and steal elements from the original list
TEST(ListCopy, SourceNotModified)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(15, 42, 4, false);

	ULListStr const * list1 = makeList(contents);

	ULListStr list2(*list1);

	// note: we have to use const_cast here because ULListStr::get() is not declared const
	EXPECT_TRUE(checkListContent(const_cast<ULListStr *>(list1), contents));

	delete list1;
}

TEST(ListAssign, OneElement)
{
	ULListStr list1;
	list1.push_back("foo");

	ULListStr list2;
	list2.push_back("bar");

	list2 = list1;

	EXPECT_EQ("foo", list2.get(0));
	EXPECT_EQ(1, list2.size());
}


TEST(ListAssign, OneElementToEmpty)
{
	ULListStr list1;
	list1.push_back("foo");

	ULListStr list2;

	list2 = list1;

	EXPECT_EQ(1, list2.size());
	EXPECT_EQ("foo", list2.get(0));
}

TEST(ListAssign, NoElements)
{
	ULListStr list1;

	ULListStr list2;
	list2.push_back("foo");

	list2 = list1;

	EXPECT_EQ(0, list2.size());
}

TEST(ListAssign, NoElementsToEmpty)
{
	ULListStr list1;

	ULListStr list2;
	list2.push_back("foo");

	list2 = list1;

	EXPECT_EQ(0, list2.size());
}


TEST(ListAssign, 15Elements)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(15, 12, 4, false);

	ULListStr receiver;

	ULListStr const * provider = makeList(contents);

	receiver = *provider;

	EXPECT_TRUE(checkListContent(&receiver, contents));

	delete provider;
}

TEST(ListPlus, EmptyPlusEmpty)
{
	ULListStr list1;

	ULListStr list2;

	ULListStr sum = list1 + list2;
	EXPECT_EQ(sum.size(), 0);
}

TEST(ListPlus, EmptyPlusOne)
{
	ULListStr list1;

	ULListStr list2;
	list2.push_back("blah");

	ULListStr sum = list1 + list2;
	EXPECT_TRUE(checkListContent(&sum, {"blah"}));
}

TEST(ListPlus, TwoPlusEmpty)
{
	ULListStr list1;
	list1.push_back("blorb");
	list1.push_back("bluk");

	ULListStr list2;

	ULListStr sum = list1 + list2;
	EXPECT_TRUE(checkListContent(&sum, {"blorb", "bluk"}));
}


TEST(ListMinusEquals, OneElement)
{
	ULListStr list;
	list.push_back("zork");

	list -= 1;

	EXPECT_EQ(0, list.size());
}

TEST(ListMinusEquals, ThreeElements)
{
	ULListStr list;
	list.push_back("zork");
	list.push_back("zog");
	list.push_back("zerg");

	list -= 2;

	EXPECT_EQ(1, list.size());
	EXPECT_EQ("zork", list.get(0));
}

TEST(ListMinusEquals, RemoveNoElements)
{
	ULListStr list;
	list.push_back("zork");
	list.push_back("zog");

	list -= 0;

	EXPECT_EQ(2, list.size());
	EXPECT_EQ("zork", list.get(0));
	EXPECT_EQ("zog", list.get(1));
}

TEST(ListMinusEquals, RemoveAllElements)
{
	ULListStr list;
	list.push_back("zork");
	list.push_back("zog");
	list.push_back("zerg");

	list -= 3;

	EXPECT_EQ(0, list.size());

}

TEST(ListMinusEquals, 15Elements)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(15, 233, 4, false);

	ULListStr * list = makeList(contents);

	// first try removing one element, then 5
	(*list) -= 1;
	contents.erase(contents.end() - 1);

	EXPECT_TRUE(checkListContent(list, contents));

	(*list) -= 5;
	contents.erase(contents.end() - 6, contents.end() - 1);

	delete list;
}

TEST(ListBracket, OneElement)
{
	ULListStr list;
	list.push_back("test");

	EXPECT_EQ("test", list[0]);
}

TEST(ListBracket, ElementAssignment)
{
	ULListStr list;
	list.push_back("fail");

	list[0] = "pass";

	EXPECT_EQ("pass", list[0]);
}
