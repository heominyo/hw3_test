//
// Runtime tests for UnrolledLinkedList
//

#include "list_utils.h"

#include <runtime_evaluator.h>

#include <gtest/gtest.h>

TEST(ListRuntime, Get)
{
	RuntimeEvaluator runtimeEvaluator("ULListStr::get()", 0, 19, 30, [&](uint64_t numElements, RandomSeed)
	{
		ULListStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		// get the value in the middle of the list in case they've implemented backwards traversal
		// (like I did when I did this assignment)
		BenchmarkTimer timer;
		list.get(numElements / 2);
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}

TEST(ListRuntime, PushBack)
{
	RuntimeEvaluator runtimeEvaluator("ULListStr::push_back()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		ULListStr list;

		// fill the list from 0 to n-1 elements
		for(uint64_t element = 0; element < numElements - 1; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.push_back("b");
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(ListRuntime, PushFront)
{
	RuntimeEvaluator runtimeEvaluator("ULListStr::push_front()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		ULListStr list;

		// fill the list from 0 to n-1 elements
		for(uint64_t element = 0; element < numElements - 1; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.push_front("b");
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(ListRuntime, PopFront)
{
	RuntimeEvaluator runtimeEvaluator("ULListStr::pop_front()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		ULListStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.pop_front();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(ListRuntime, PopBack)
{
	RuntimeEvaluator runtimeEvaluator("ULListStr::pop_back()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		ULListStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.pop_back();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}


