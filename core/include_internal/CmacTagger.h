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
        inline static const char* ROOT = "Cmac";
        inline static const char* NUM_Q = "NumQ";
        inline static const char* NUM_LAYERS = "NumLayers";
        inline static const char* MAX_MEMORY = "MaxMemory";
        inline static const char* MAX_HASH_VALUE = "MaxHashValue";
        inline static const char* NUM_OUTPUTS = "NumOutputs";
        inline static const char* NUM_INPUTS = "NumInputs";
        inline static const char* BETA = "Beta";
        inline static const char* NU = "Nu";
        inline static const char* UPPER_LIMITS = "UpperLimits";
        inline static const char* LOWER_LIMITS = "LowerLimits";
        inline static const char* MEMORY = "Memory";
        inline static char DELIMITER = ',';
        inline static const char* HASHTABLE = "Hashtable";
        inline static const char* DENOMINATOR = "Denominator";
        inline static const char* OFFSETS = "Offsets";

    public: // helper methods
        inline std::string StartTag(const std::string& content)
        {
            return "<" + content + ">";
        }
        inline std::string StartTag(std::string&& content)
        {
            return "<" + content + ">";
        }

        inline std::string EndTag(const std::string& content)
        {
            return "</" + content + ">";
        }
        inline std::string EndTag(std::string&& content)
        {
            return "</" + content + ">";
        }

        inline std::string Entry(std::string&& content, const std::string& tag)
        {
            return StartTag(tag) + std::move(content) + EndTag(tag) + "\n";
        }

        inline std::string ToString(double value)
        {
            std::stringstream ss;
            ss << std::hexfloat << value;
            return ss.str();
        }

        inline std::string ToString(const std::vector<unsigned int>& vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += std::to_string(vec[i]) + CmacTagger::DELIMITER;
            }
            result.pop_back(); // remove last delimiter
            return result;
        }

        inline std::string ToString(const std::vector<double>& vec)
        {
            std::string result;
            for(size_t i = 0; i < vec.size(); i++)
            {
                result += ToString(vec[i]) + CmacTagger::DELIMITER;
            }
            result.pop_back();
            return result;
        }

        inline std::string ToString(const std::vector<std::vector<double>>& mat)
        {
            std::string result = "\n";
            for(size_t i = 0; i < mat.size(); i++)
            {
                result += ToString(mat[i]) + "\n";
            }
            return result;
        }

        inline std::string GetContent(
            const std::string& entry, const std::string& tag)
        {
            size_t start = entry.find(StartTag(tag)) + StartTag(tag).size();
            size_t end = entry.find(EndTag(tag));
            return entry.substr(start, end - start);
        }

        inline unsigned int GetUnsignedInt(
            const std::string& entry, const std::string& tag)
        {
            return std::stoul(GetContent(entry, tag));
        }

        inline double GetDouble(
            const std::string& entry, const std::string& tag)
        {
            std::string content = GetContent(entry, tag);
            std::stringstream ss(content);
            return std::strtod(ss.str().c_str(), NULL);
        }

        inline std::vector<std::string> StringSplit(
            const std::string& str, char delimiter)
        {
            std::vector<std::string> strings;
            std::istringstream stream(str);
            std::string token;

            while (std::getline(stream, token, delimiter)) {
                strings.emplace_back(std::move(token));
            }

            return strings;
        }

        inline std::vector<unsigned int> GetUnsignedInts(
            const std::string& entry, const std::string& tag)
        {
            std::vector<unsigned int> result;
            std::string content = GetContent(entry, tag);
            std::vector<std::string> strNums = StringSplit(content, CmacTagger::DELIMITER);
            for(size_t i = 0; i < strNums.size(); i++)
            {
                result.emplace_back(std::stoul(strNums[i]));
            }
            return result;
        }

        inline std::vector<double> GetDoubles(
            const std::string& entry, const std::string& tag)
        {
            std::vector<double> result;
            std::string content = GetContent(entry, tag);
            std::vector<std::string> strNums = StringSplit(content, CmacTagger::DELIMITER);
            for(size_t i = 0; i < strNums.size(); i++)
            {
                std::stringstream ss(strNums[i]);
                double val = std::strtod(ss.str().c_str(), NULL);
                result.emplace_back(val);
            }
            return result;
        }

        inline std::vector<std::vector<double>> GetMatrixDoubles(
            const std::string& entry, const std::string& tag)
        {
            std::string content = GetContent(entry, tag);
            // remove new lines
            content = content.erase(0,1); 
            content.pop_back();
            std::vector<std::vector<double>> result;
            std::vector<std::string> lines = StringSplit(content, '\n');
            for(size_t i = 0; i < lines.size(); i++)
            {
                std::vector<double> vals;
                std::vector<std::string> strNums = StringSplit(lines[i], CmacTagger::DELIMITER);
                for(size_t j = 0; j < strNums.size(); j++)
                {
                    std::stringstream ss(strNums[j]);
                    double val = std::strtod(ss.str().c_str(), NULL);
                    vals.emplace_back(val);
                }

                if(vals.size() > 0) // avoid accidentally putting in empty vectors
                {
                    result.emplace_back(vals);
                }
            }
            return result;
        }
    };
}

#endif