#ifndef CMACTAGGER_H
#define CMACTAGGER_H

#include <string>
#include <sstream>
#include <vector>

namespace CmacLib
{
    class CmacTagger
    {
    public:
        CmacTagger(){};
        ~CmacTagger(){};

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
        std::string StartTag(std::string content)
        {
            return "<" + content + ">";
        };

        std::string EndTag(std::string content)
        {
            return "</" + content + ">";
        }

        std::string Entry(std::string content, std::string tag)
        {
            return StartTag(tag) + content + EndTag(tag) + "\n";
        }

        std::string ToString(double value)
        {
            std::stringstream ss;
            ss << std::hexfloat << value;
            return ss.str();
        }

        std::string ToString(std::vector<unsigned int> vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += std::to_string(vec[i]) + CmacTagger::DELIMITER;
            }
            result.pop_back(); // remove last delimiter
            return result;
        }

        std::string ToString(std::vector<double> vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += ToString(vec[i]) + CmacTagger::DELIMITER;
            }
            result.pop_back();
            return result;
        }

        std::string ToString(std::vector<std::vector<double>> mat)
        {
            std::string result = "\n";
            for(size_t i = 0; i < mat.size(); i++)
            {
                result += ToString(mat[i]) + "\n";
            }
            return result;
        }
    };
}

#endif