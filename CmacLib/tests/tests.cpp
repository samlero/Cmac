#include <gtest/gtest.h>
#include "../include/CmacLib.h"
//#include <CmacLib.h>
#include <memory>

using namespace CmacLib;
using namespace std;

TEST(FACTORY, CreateCmac)
{
	// create factory
	std::unique_ptr<Factory> factory(new Factory());

	EXPECT_TRUE(factory.get() != nullptr);

	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, upper
		, lower
		, 0.001
		, 0.00001));

	EXPECT_TRUE(cmac.get() != nullptr);
}

TEST(CMAC, PREDICT_SUCCESS)
{
	std::unique_ptr<Factory> factory(new Factory());
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, upper
		, lower
		, 0.001
		, 0.00001));
	
	std::vector<double> input(2, 0.0);

	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	EXPECT_TRUE(prediction.get() != nullptr);

	// verify prediction properties
	ASSERT_EQ(prediction->GetValues().size(), 2);
	EXPECT_TRUE(prediction->GetResult() != nullptr);
	EXPECT_TRUE(prediction->GetResult()->IsSuccessful());
	ASSERT_EQ(prediction->GetBasisValues().size(), 100); // numlayers
	// check each basis value is between 0 and 1
	for(size_t i = 0; i < prediction->GetBasisValues().size(); i++)
	{
		EXPECT_TRUE(prediction->GetBasisValues()[i] <= 1.0 && prediction->GetBasisValues()[i] >= 0.0);
	}
	
	ASSERT_EQ(prediction->GetActiveWeights().size(), 2); // numoutput
	for(size_t i = 0; i < prediction->GetActiveWeights().size(); i++)
	{
		ASSERT_EQ(prediction->GetActiveWeights()[i].size(), 100); // numlayers
	}

	ASSERT_EQ(prediction->GetActiveWeightIndices().size(), 100); // numlayers
}

TEST(CMAC, PREDICT_FAIL)
{
	std::unique_ptr<Factory> factory(new Factory());
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, upper
		, lower
		, 0.001
		, 0.00001));
	
	std::vector<double> input(1, 0.0);

	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	EXPECT_TRUE(prediction.get() != nullptr);

	// verify prediction properties
	ASSERT_EQ(prediction->GetValues().size(), 0);
	EXPECT_TRUE(prediction->GetResult() != nullptr);
	EXPECT_FALSE(prediction->GetResult()->IsSuccessful());
	ASSERT_EQ(prediction->GetBasisValues().size(), 0); // numlayers
	ASSERT_EQ(prediction->GetActiveWeights().size(), 0); // numoutput
	ASSERT_EQ(prediction->GetActiveWeightIndices().size(), 0); // numlayers
}