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

        std::string GetContent(std::string entry, std::string tag)
        {
            size_t start = entry.find(StartTag(tag)) + StartTag(tag).size();
            size_t end = entry.find(EndTag(tag));
            return entry.substr(start, end - start);
        }

        unsigned int GetUnsignedInt(std::string entry, std::string tag)
        {
            return std::stoul(GetContent(entry, tag));
        }

        double GetDouble(std::string entry, std::string tag)
        {
            std::string content = GetContent(entry, tag);
            std::stringstream ss;
            ss << content;
            double result;
            ss >> std::hexfloat >> result;
            return result;
        }

        std::vector<std::string> StringSplit(std::string str, char delimiter)
        {
            std::vector<std::string> strings;
            int startIndex = 0, endIndex = 0;
            for (int i = 0; i <= str.size(); i++) {
                
                // If we reached the end of the word or the end of the input.
                if (str[i] == delimiter || i == str.size()) {
                    endIndex = i;
                    std::string temp;
                    temp.append(str, startIndex, endIndex - startIndex);
                    strings.push_back(temp);
                    startIndex = endIndex + 1;
                }
            }
            return strings;
        }

        std::vector<unsigned int> GetUnsignedInts(std::string entry, std::string tag)
        {
            std::vector<unsigned int> result;
            std::string content = GetContent(entry, tag);
            std::vector<std::string> strNums = StringSplit(content, CmacTagger::DELIMITER[0]);
            for(size_t i = 0; i < strNums.size(); i++)
            {
                result.push_back(std::stoul(strNums[i]));
            }
            return result;
        }

        std::vector<double> GetDoubles(std::string entry, std::string tag)
        {
            std::vector<double> result;
            std::string content = GetContent(entry, tag);
            std::vector<std::string> strNums = StringSplit(content, CmacTagger::DELIMITER[0]);
            for(size_t i = 0; i < strNums.size(); i++)
            {
                std::stringstream ss;
                ss << strNums[i];
                double val;
                ss >> std::hexfloat >> val;
                result.push_back(val);
            }
            return result;
        }

        std::vector<std::vector<double>> GetMatrixDoubles(std::string entry, std::string tag)
        {
            std::string content = GetContent(entry, tag);
            std::vector<std::vector<double>> result;
            std::vector<std::string> lines = StringSplit(content, '\n');
            for(size_t i = 0; i < lines.size(); i++)
            {
                std::vector<double> vals;
                std::vector<std::string> strNums = StringSplit(lines[i], CmacTagger::DELIMITER[0]);
                for(size_t j = 0; j < strNums.size(); j++)
                {
                    std::stringstream ss;
                    ss << strNums[j];
                    double val;
                    ss >> std::hexfloat >> val;
                    vals.push_back(val);
                }

                if(vals.size() > 0) // avoid accidentally putting in empty vectors
                {
                    result.push_back(vals);
                }
            }
            return result;
        }
    };
}

#endif