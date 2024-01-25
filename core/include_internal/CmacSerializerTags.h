#ifndef CMACSERIALIZERTAGS_H
#define CMACSERIALIZERTAGS_H

#include <string>

namespace CmacLib
{
    class CmacSerializerTags
    {
    public:
        /// @brief Disable constructor, static class
        CmacSerializerTags() = delete;

    public: // tags
        inline static const std::string ROOT = "Cmac";
        inline static const std::string NUM_Q = "NumQ";
        inline static const std::string NUM_LAYERS = "NumLayers";
        inline static const std::string MAX_MEMORY = "MaxMemory";
        inline static const std::string MAX_HASH_VALUE = "MaxHashValue";
        inline static const std::string NUM_OUTPUTS = "NumOutputs";
        inline static const std::string NUM_INPUTS = "NumInputs";
        inline static const std::string BETA = "Beta";
        inline static const std::string Nu = "Nu";
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
    };
}

#endif