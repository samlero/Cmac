#include <gtest/gtest.h>
#include <CmacLib.h>
#include <cmaclib/CmacTagger.h>
#include <memory>
#include <cmath>
#include <utility>

using namespace CmacLib;
using namespace std;

TEST(CMAC_TAGGER, GET_DOUBLE)
{
    std::string entry = "<Beta>0x1.0624dd2f1a9fcp-10</Beta>";
    std::string tag = "Beta";

    std::unique_ptr<CmacTagger> tagger(std::make_unique<CmacTagger>());

    double value = tagger->GetDouble(entry, tag);

    double expected = 0.001;

    ASSERT_EQ(value, expected);
}
