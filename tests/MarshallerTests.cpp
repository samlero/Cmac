#include <gtest/gtest.h>
#include "../include/CmacLib.h"
#include <memory>
#include <cmath>
#include <utility>
#include <filesystem>
#include "../include_internal/Serialization.h"

using namespace CmacLib;
using namespace std;

/// @brief A mock serializable
class MockSerializable : public ISerializable
{
private:
    string data;
public:
    MockSerializable() : data("BEGIN_DATA \n CONTENT_DATA \n END_DATA"){};
    ~MockSerializable(){};
    string GetData(){return data;};

public: // overrides
    unique_ptr<ISerialization> Serialize()
    {
        unique_ptr<Serialization> result(std::make_unique<Serialization>());
        result->SetIsSuccessful(true);
        result->SetString(this->data);
        return result;
    };
    void Deserialize(string&& content){data = content;};
    string GetExtension(){return "ext";};
};

/// @brief A mock serializable that will cause failures
class MockFailSerializable : public ISerializable
{
public:
    MockFailSerializable(){};
    ~MockFailSerializable(){};

public: // overrides
    unique_ptr<ISerialization> Serialize(){throw runtime_error("Serialize error.");};
    void Deserialize(string&& content){throw runtime_error("Deserialize error");};
    string GetExtension(){return "ext";};
};


TEST(MARSHALLER, SAVE_SUCCESS)
{
    string filename = "save_test";
    string dir = filesystem::current_path().string();

    // create the marshaller and mock serializable object
    unique_ptr<Factory> factory(make_unique<Factory>());
    unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
    unique_ptr<MockSerializable> serializable(make_unique<MockSerializable>());
    
    // delete the file first
    filesystem::path expectedPath = dir + "/" + filename + "." + serializable->GetExtension();
    remove(expectedPath);

    // call the subject method
    unique_ptr<IResult> result = marshaller->Save(serializable.get(), dir, "save_test");

    ASSERT_TRUE(result.get() != nullptr);
    ASSERT_TRUE(result->IsSuccessful());
    ASSERT_TRUE(result->GetMessage().size() == 0);
    ASSERT_TRUE(filesystem::exists(expectedPath));
}

TEST(MARSHALLER, SAVE_FAIL)
{
    string filename = "save_test";
    string dir = filesystem::current_path().string();

    // create the marshaller and mock serializable object
    unique_ptr<Factory> factory(make_unique<Factory>());
    unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
    unique_ptr<MockFailSerializable> serializable(make_unique<MockFailSerializable>());
    
    // delete the file first
    filesystem::path expectedPath = dir + "/" + filename + "." + serializable->GetExtension();
    remove(expectedPath);

    // call the subject method
    unique_ptr<IResult> result = marshaller->Save(serializable.get(), dir, "save_test");

    ASSERT_TRUE(result.get() != nullptr);
    ASSERT_FALSE(result->IsSuccessful());
    ASSERT_FALSE(result->GetMessage().size() == 0);
    ASSERT_FALSE(filesystem::exists(expectedPath));
}

TEST(MARSHALLER, LOAD_SUCCESS)
{
    string filename = "save_test";
    string dir = filesystem::current_path().string();

    // create the marshaller and mock serializable object
    unique_ptr<Factory> factory(make_unique<Factory>());
    unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
    unique_ptr<MockSerializable> serializable(make_unique<MockSerializable>());
    
    // delete the file first
    filesystem::path expectedPath = dir + "/" + filename + "." + serializable->GetExtension();
    remove(expectedPath);

    // call the save method
    unique_ptr<IResult> result = marshaller->Save(serializable.get(), dir, "save_test");    

    ASSERT_TRUE(result.get() != nullptr);
    ASSERT_TRUE(result->IsSuccessful());
    ASSERT_TRUE(result->GetMessage().size() == 0);
    ASSERT_TRUE(filesystem::exists(expectedPath));

    // create another serializable object
    unique_ptr<MockSerializable> actual(make_unique<MockSerializable>());
    unique_ptr<IResult> loadResult = marshaller->Load(actual.get(), expectedPath.string());

    ASSERT_TRUE(loadResult.get() != nullptr);
    ASSERT_TRUE(loadResult->IsSuccessful());
    ASSERT_TRUE(loadResult->GetMessage().size() == 0);
    ASSERT_TRUE(actual->GetData() == serializable->GetData());
}

TEST(MARSHALLER, LOAD_FAIL)
{
    string filename = "save_test";
    string dir = filesystem::current_path().string();

    // create the marshaller and mock serializable object
    unique_ptr<Factory> factory(make_unique<Factory>());
    unique_ptr<IMarshaller> marshaller = factory->CreateMarshaller();
    unique_ptr<MockSerializable> serializable(make_unique<MockSerializable>());
    
    // delete the file first
    filesystem::path expectedPath = dir + "/" + filename + "." + serializable->GetExtension();
    remove(expectedPath);

    // call the save method
    unique_ptr<IResult> result = marshaller->Save(serializable.get(), dir, "save_test");    

    ASSERT_TRUE(result.get() != nullptr);
    ASSERT_TRUE(result->IsSuccessful());
    ASSERT_TRUE(result->GetMessage().size() == 0);
    ASSERT_TRUE(filesystem::exists(expectedPath));

    // create another serializable object
    unique_ptr<MockFailSerializable> actual(make_unique<MockFailSerializable>());
    unique_ptr<IResult> loadResult = marshaller->Load(actual.get(), expectedPath.string());

    ASSERT_TRUE(loadResult.get() != nullptr);
    ASSERT_FALSE(loadResult->IsSuccessful());
    ASSERT_FALSE(loadResult->GetMessage().size() == 0);
}