#include <gtest/gtest.h>
#include <CmacLib.h>
#include <memory>
#include <cmath>
#include <utility>
#include <filesystem>
#include <fstream>
#include <streambuf>

using namespace CmacLib;
using namespace std;

TEST(SERIALIZABLE, SERIALIZE_DESERIALIZE_CMAC)
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

	ASSERT_TRUE(serialization->IsSuccessful());
	ASSERT_GT(serialization->GetString().size(), 0);
	ASSERT_EQ(serialization->GetMessage().size(), 0);

	std::unique_ptr<ICmac> defCmac = factory->CreateDefaultCmac();
	std::unique_ptr<IResult> deserialization = defCmac->Deserialize(serialization->GetString());


	std::unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
	marshaller->Save(cmac.get(), filesystem::current_path().string(), "expected");



	ASSERT_TRUE(deserialization->IsSuccessful());
	ASSERT_EQ(deserialization->GetMessage().size(), 0);

	std::unique_ptr<ISerialization> anotherSerialization = defCmac->Serialize();

	ASSERT_TRUE(anotherSerialization->IsSuccessful());
	ASSERT_GT(anotherSerialization->GetString().size(), 0);
	ASSERT_EQ(anotherSerialization->GetMessage().size(), 0);
	ASSERT_EQ(serialization->GetString(), anotherSerialization->GetString());

}