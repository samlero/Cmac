#include <gtest/gtest.h>
#include "../include/CmacLib.h"
#include <memory>
#include <cmath>
#include <utility>
#include <filesystem>
#include <fstream>
#include <streambuf>

using namespace CmacLib;
using namespace std;

TEST(SERIALIZABLE, SERIALIZE_CMAC)
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

    std::unique_ptr<ISerialization> serialization = cmac->Serialize();

    //unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
    //marshaller->Save(cmac.get(), filesystem::current_path().string(), "expected_serialized_2.xml");

    // get expected string
    std::ifstream t("expected_serialized.xml");
    std::string expected((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    ASSERT_EQ(serialization->GetString().length(), expected.size());
    ASSERT_EQ(serialization->GetString(), expected);
}