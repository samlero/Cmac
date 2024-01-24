#include <gtest/gtest.h>
#include "../include/CmacLib.h"
//#include <CmacLib.h>
#include <memory>
#include <cmath>
#include <utility>

using namespace CmacLib;
using namespace std;

TEST(FACTORY, CreateCmac)
{
	// create factory
	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();

	ASSERT_TRUE(factory.get() != nullptr);

	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, ::std::move(upper)
		, ::std::move(lower)
		, 0.001
		, 0.00001));

	ASSERT_TRUE(cmac.get() != nullptr);
}

TEST(CMAC, PREDICT_SUCCESS)
{
	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, ::std::move(upper)
		, ::std::move(lower)
		, 0.001
		, 0.00001));
	
	std::vector<double> input(2, 0.0);

	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	ASSERT_TRUE(prediction.get() != nullptr);

	// verify prediction properties
	ASSERT_EQ(prediction->GetValues().size(), 2);
	ASSERT_TRUE(prediction->GetResult() != nullptr);
	ASSERT_TRUE(prediction->GetResult()->IsSuccessful());
	ASSERT_EQ(prediction->GetBasisValues().size(), 100); // numlayers
	// check each basis value is between 0 and 1
	for(size_t i = 0; i < prediction->GetBasisValues().size(); i++)
	{
		ASSERT_TRUE(prediction->GetBasisValues()[i] <= 1.0 && prediction->GetBasisValues()[i] >= 0.0);
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
	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, ::std::move(upper)
		, ::std::move(lower)
		, 0.001
		, 0.00001));
	
	std::vector<double> input(1, 0.0);
	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	ASSERT_TRUE(prediction.get() != nullptr);

	// verify prediction properties
	ASSERT_EQ(prediction->GetValues().size(), 0);
	ASSERT_TRUE(prediction->GetResult() != nullptr);
	ASSERT_FALSE(prediction->GetResult()->IsSuccessful());
	ASSERT_EQ(prediction->GetBasisValues().size(), 0); // numlayers
	ASSERT_EQ(prediction->GetActiveWeights().size(), 0); // numoutput
	ASSERT_EQ(prediction->GetActiveWeightIndices().size(), 0); // numlayers
}

TEST(CMAC, ADJUST_SUCCESS)
{
	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, ::std::move(upper)
		, ::std::move(lower)
		, 0.001
		, 0.00001));

	std::vector<double> input(2, 0.0);
	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	ASSERT_TRUE(prediction.get() != nullptr);

	std::vector<double> correct(2, 0.001);
	std::unique_ptr<IAdjustment> adjust = cmac->Adjust(correct, prediction.get(), 0.00001);

	ASSERT_TRUE(adjust.get() != nullptr);
	ASSERT_TRUE(adjust->GetResult() != nullptr);
	ASSERT_TRUE(adjust->GetResult()->IsSuccessful());
	ASSERT_EQ(adjust->GetWeightChanges().size(), 2);

	for(size_t i = 0; i < adjust->GetWeightChanges().size(); i++)
	{
		ASSERT_EQ(adjust->GetWeightChanges()[i].size(), 100);
	}
}

TEST(CMAC, ADJUST_FAIL)
{
	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();
	std::vector<double> upper(2, 10.0);
	std::vector<double> lower(2, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 100
		, (unsigned int)1e5
		, 2
		, ::std::move(upper)
		, ::std::move(lower)
		, 0.001
		, 0.00001));

	std::vector<double> input(2, 0.0);
	std::unique_ptr<IPrediction> prediction = cmac->Predict(input);

	ASSERT_TRUE(prediction.get() != nullptr);

	std::vector<double> correct(1, 0.001);
	std::unique_ptr<IAdjustment> adjust = cmac->Adjust(correct, prediction.get(), 0.00001);

	ASSERT_TRUE(adjust.get() != nullptr);
	ASSERT_TRUE(adjust->GetResult() != nullptr);
	ASSERT_FALSE(adjust->GetResult()->IsSuccessful());
	ASSERT_EQ(adjust->GetWeightChanges().size(), 0);
}

/**
TEST(CMAC, ADAPTING)
{
	double dt = 0.01;
	double T = 100.0;
	double Tcheck = T - 2.0;

	double m = 0.1;
	double b = 0.001;
	double x = 0.0;
	double xdot = 0.0;
	double xr = 1.0;
	double thresh = 0.01;
	double kp = 1.0; double kd = 0.01;
	double nn = 0.0;

	std::unique_ptr<Factory> factory= ::std::make_unique<Factory>();
	std::vector<double> upper(1, 10.0);
	std::vector<double> lower(1, -10.0);
	std::unique_ptr<ICmac> cmac(factory->CreateCmac(10
		, 50
		, (unsigned int)1e5
		, 1
		, upper
		, lower
		, 0.1
		, 0));

	double lastErrors = 0.0;
	size_t numSamples = 0;
	
	for(double t = 0.0; t <= T; t+= dt)
	{
		double e = x - xr;
		double edot = xdot;
		double z = (kp/kd)*e + edot;

		std::vector<double> input(1,x);
		std::unique_ptr<IPrediction> predict = cmac->Predict(input);

		if(predict->GetResult()->IsSuccessful() == false)
		{
			std::cout << "Prediction failed." << std::endl;
		}

		ASSERT_TRUE(predict->GetResult()->IsSuccessful());

		nn = predict->GetValues()[0];
		double u = -kd*z - nn;

		double xddot = (-b*xdot + u)/m;
		xdot = xddot*dt;
		x = xdot*dt;

		std::vector<double> correction(1,z);
		std::unique_ptr<IAdjustment> adjust = cmac->Adjust(correction, predict.get(), std::abs(z));

		if(adjust->GetResult()->IsSuccessful() == false)
		{
			std::cout << "Prediction failed." << std::endl;
		}

		ASSERT_TRUE(adjust->GetResult()->IsSuccessful());

		if(t >= Tcheck)
		{
			lastErrors += e*e;
			numSamples++;
		}
	}

	lastErrors = std::sqrt(lastErrors/(double)numSamples);

	ASSERT_LT(lastErrors, thresh);
}
**/
