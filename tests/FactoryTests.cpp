#include <gtest/gtest.h>
#include <CmacLib.h>
#include <memory>
#include <cmath>
#include <utility>

using namespace CmacLib;
using namespace std;

TEST(FACTORY, CREATE_CMAC)
{
	// create factory
	std::unique_ptr<Factory> factory = ::std::make_unique<Factory>();

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

TEST(FACTORY, CREATE_MARSHALLER)
{
    // create factory
	std::unique_ptr<Factory> factory = ::std::make_unique<Factory>();

    ASSERT_TRUE(factory.get() != nullptr);

    std::unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();

    ASSERT_TRUE(marshaller.get() != nullptr);
}