//
// CS104 Stack runtime tests
//

#include <stackstring.h>

#include <runtime_evaluator.h>

#include <gtest/gtest.h>

TEST(StackRuntime, Push)
{
	RuntimeEvaluator runtimeEvaluator("StackString::push", 0, 19, 40, [&](uint64_t numElements, RandomSeed)
	{
		StackString stack;

		// fill the list from 0 to n - 1 elements
		for(uint64_t element = 0; element < numElements - 1; ++element)
		{
			stack.push("and");
		}

		BenchmarkTimer timer;
		stack.push("but");
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(StackRuntime, Pop)
{
	RuntimeEvaluator runtimeEvaluator("StackString::pop", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		StackString stack;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			stack.push("so");
		}

		BenchmarkTimer timer;
		stack.pop();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(StackRuntime, Top)
{
	RuntimeEvaluator runtimeEvaluator("StackString::top", 0, 19, 30, [&](uint64_t numElements, RandomSeed)
	{
		StackString stack;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			stack.push("uh");
		}

		BenchmarkTimer timer;
		stack.top();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1.4);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}