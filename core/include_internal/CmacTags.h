#ifndef CMACTAGS_H
#define CMACTAGS_H

#include <string>
#include <sstream>
#include <vector>

namespace CmacLib
{
    class CmacTags
    {
    public:
        /// @brief Disable constructor, static class
        CmacTags() = delete;

    public: // tags
        inline static const std::string ROOT = "Cmac";
        inline static const std::string NUM_Q = "NumQ";
        inline static const std::string NUM_LAYERS = "NumLayers";
        inline static const std::string MAX_MEMORY = "MaxMemory";
        inline static const std::string MAX_HASH_VALUE = "MaxHashValue";
        inline static const std::string NUM_OUTPUTS = "NumOutputs";
        inline static const std::string NUM_INPUTS = "NumInputs";
        inline static const std::string BETA = "Beta";
        inline static const std::string NU = "Nu";
        inline static const std::string UPPER_LIMITS = "UpperLimits";
        inline static const std::string LOWER_LIMITS = "LowerLimits";
        inline static const std::string MEMORY = "Memory";
        inline static const std::string DELIMITER = ",";
        inline static const std::string HASHTABLE = "Hashtable";
        inline static const std::string DENOMINATOR = "Denominator";
        inline static const std::string OFFSETS = "Offsets";

    public: // helper methods
        inline static std::string StartTag(std::string content)
        {
            return "<" + content + ">";
        };

        inline static std::string EndTag(std::string content)
        {
            return "</" + content + ">";
        }

        inline static std::string Entry(std::string content, std::string tag)
        {
            return CmacTags::StartTag(tag) + content + CmacTags::EndTag(tag) + "\n";
        }

        inline static std::string ToString(double value)
        {
            std::stringstream ss;
            ss << std::hexfloat << value;
            return ss.str();
        }

        inline static std::string ToString(std::vector<unsigned int> vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += std::to_string(vec[i]) + CmacTags::DELIMITER;
            }
            result.pop_back(); // remove last delimiter
            return result;
        }

        inline static std::string ToString(std::vector<double> vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += CmacTags::ToString(vec[i]) + CmacTags::DELIMITER;
            }
            result.pop_back();
            return result;
        }

        inline static std::string ToString(std::vector<std::vector<double>> mat)
        {
            std::string result;
            for(size_t i = 0; i < mat.size(); i++)
            {
                result += CmacTags::ToString(mat[i]) + "\n";
            }
            result.pop_back();
            return result;
        }
    };
}

#endif