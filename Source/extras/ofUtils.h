/*
  ==============================================================================

    ofUtils.h
    Created: 17 Mar 2024 1:26:25pm
    Author:  Zabba

  ==============================================================================
*/

#pragma once


#include <iostream>
#include <string>
#include <regex>
#include <map>
#include <cctype>
#include <iterator>
#include <regex>

//#include "Poco/RegularExpression.h"
//using Poco::RegularExpression;


using namespace std;


class ofVec2f {
public:
    ofVec2f( int x, int y ) : x(x), y(y) {};

    /// \brief Stores the `x` component of the vector.
    int x;

    /// \brief Stores the `y` component of the vector.
    int y;
};




class RegularExpression {
    
public:
    RegularExpression(string regex) : rgx(regex) {};
    
    bool search(string str, regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript | std::regex_constants::icase) {
        std::regex self_regex(rgx, flags);
        return std::regex_search(str, self_regex);
    }
    
    string replace(string str, string replacementRegex, regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript | std::regex_constants::icase) {
        // eg use "[$&]" for replacementRegex to wrape square brackets around the replacement!
        std::regex self_regex(rgx, flags);
        std::string new_s = std::regex_replace(str, self_regex, replacementRegex);
        return new_s;
    }
    
    string match(string str, regex_constants::syntax_option_type flags = std::regex_constants::ECMAScript | std::regex_constants::icase) {
        std::regex self_regex(rgx, flags);
        
        std::smatch match;
        std::regex_search(str, match, self_regex);
        if (match.size() > 0) {
            return match[0];
        } else {
            return "";
        }
    }
    
private:
    string rgx;
};





/// \section String Conversion
/// \brief Convert a value to a string.
///
/// ofToString does its best to convert any value to a string. If the data type
/// implements a stream << operator, then it will be converted.
///
/// Example:
/// ~~~~{.cpp}
///    std::string str = "framerate is ";
///    str += ofToString(ofGetFrameRate()) + " fps";
///    // The string now contains something like "framerate is 60 fps".
/// ~~~~
///
/// \tparam T The data type of the value to convert to a string.
/// \param value The value to convert to a string.
/// \returns A string representing the value or an empty string on failure.
template <class T>
std::string ofToString(const T & value) {
    std::ostringstream out;
    out << value;
    return out.str();
}

/// \brief Convert a value to a string with a specific precision.
///
/// Like sprintf "%4f" format, in this example precision=4
///
/// \tparam T The data type of the value to convert to a string.
/// \param value The value to convert to a string.
/// \param precision The precision to use when converting to a string.
/// \returns The string representation of the value.
template <class T>
std::string ofToString(const T & value, int precision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

/// \brief Convert a value to a string with a specific width and fill
///
/// Like sprintf "% 4d" or "% 4f" format, in this example width=4, fill=' '
///
/// \tparam T The data type of the value to convert to a string.
/// \param value The value to convert to a string.
/// \param width The width of the value to use when converting to a string.
/// \param fill The character to use when padding the converted string.
/// \returns The string representation of the value.
template <class T>
std::string ofToString(const T & value, int width, char fill) {
    std::ostringstream out;
    out << std::fixed << std::setfill(fill) << std::setw(width) << value;
    return out.str();
}

/// \brief Convert a value to a string with a specific precision, width and filll
///
/// Like sprintf "%04.2d" or "%04.2f" format, in this example precision=2, width=4, fill='0'
///
/// \tparam T The data type of the value to convert to a string.
/// \param value The value to convert to a string.
/// \param precision The precision to use when converting to a string.
/// \param width The width of the value to use when converting to a string.
/// \param fill The character to use when padding the converted string.
/// \returns The string representation of the value.
template <class T>
std::string ofToString(const T & value, int precision, int width, char fill) {
    std::ostringstream out;
    out << std::fixed << std::setfill(fill) << std::setw(width) << std::setprecision(precision) << value;
    return out.str();
}

/// \brief Convert a vector of values to a comma-delimited string.
///
/// This method will take any vector of values and output a list of the values
/// as a comma-delimited string.
///
/// \tparam T The data type held by the vector.
/// \param values The vector of values to be converted to a string.
/// \returns a comma-delimited string representation of the intput values.
template <class T>
std::string ofToString(const std::vector<T> & values) {
    std::stringstream out;
    int n = values.size();
    out << "{";
    if (n > 0) {
        for (int i = 0; i < n - 1; i++) {
            out << values[i] << ", ";
        }
        out << values[n - 1];
    }
    out << "}";
    return out.str();
}






/// \brief Convert a string to a given data type.
/// \tparam T The return type.
/// \param str The string value to convert to a give type.
/// \returns the string converted to the type.
template <typename T>
T ofTo(const std::string & str) {
    T x;
    std::istringstream cur(str);
    cur >> x;
    return x;
}

//----------------------------------------
//int ofToInt(const string & intString) {
//    return ofTo<int>(intString);
//}









//--------------------------------------------------
// helper method to get locale from name
static std::locale getLocale(const string & locale) {
    std::locale loc;
#if defined(TARGET_WIN32) && !_MSC_VER
    static bool printonce = true;
    if (printonce) {
        std::string current(setlocale(LC_ALL, NULL));
        setlocale(LC_ALL, "");
        cout << "std::locale not supported. Using C locale: " << current;
        printonce = false;
    }
#else
    try {
        loc = std::locale(locale.c_str());
    } catch (...) {
       // ofLogWarning("ofUtils") << "Couldn't create locale " << locale << " using default, " << loc.name();
    }
#endif
    return loc;
}

////--------------------------------------------------
//string ofTrimFront(const string & src, const string & locale = "") {
//    auto dst = src;
//    std::locale loc = getLocale(locale);
//    dst.erase(dst.begin(), std::find_if_not(dst.begin(), dst.end(), [&](char & c) { return std::isspace<char>(c, loc); }));
//    return dst;
//}
//
////--------------------------------------------------
//string ofTrimBack(const string & src, const string & locale = "") {
//    auto dst = src;
//    std::locale loc = getLocale(locale);
//    dst.erase(std::find_if_not(dst.rbegin(), dst.rend(), [&](char & c) { return std::isspace<char>(c, loc); }).base(), dst.end());
//    return dst;
//}
//
////--------------------------------------------------
//string ofTrim(const string & src, const string & locale = "") {
//    return ofTrimFront(ofTrimBack(src));
//}
//
//--------------------------------------------------
//void ofStringReplace(string & input, const string & searchStr, const string & replaceStr) {
//    auto pos = input.find(searchStr);
//    while (pos != std::string::npos) {
//        input.replace(pos, searchStr.size(), replaceStr);
//        pos += replaceStr.size();
//        std::string nextfind(input.begin() + pos, input.end());
//        auto nextpos = nextfind.find(searchStr);
//        if (nextpos == std::string::npos) {
//            break;
//        }
//        pos += nextpos;
//    }
//}

////--------------------------------------------------
//bool ofIsStringInString(const string & haystack, const string & needle) {
//    return haystack.find(needle) != std::string::npos;
//}
//
////--------------------------------------------------
//std::size_t ofStringTimesInString(const string & haystack, const string & needle) {
//    const size_t step = needle.size();
//
//    size_t count(0);
//    size_t pos(0);
//
//    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
//        pos += step;
//        ++count;
//    }
//
//    return count;
//}
//
////--------------------------------------------------
//vector<string> ofSplitString(const string & source, const string & delimiter, bool ignoreEmpty = false, bool trim = true) {
//    vector<string> result;
//    if (delimiter.empty()) {
//        result.push_back(source);
//        return result;
//    }
//    string::const_iterator substart = source.begin(), subend;
//    while (true) {
//        subend = search(substart, source.end(), delimiter.begin(), delimiter.end());
//        string sub(substart, subend);
//        if (trim) {
//            sub = ofTrim(sub);
//        }
//        if (!ignoreEmpty || !sub.empty()) {
//            result.push_back(sub);
//        }
//        if (subend == source.end()) {
//            break;
//        }
//        substart = subend + delimiter.size();
//    }
//    return result;
//}
//
////--------------------------------------------------
//string ofJoinString(const vector<string> & stringElements, const string & delimiter) {
//    string str;
//    if (stringElements.empty()) {
//        return str;
//    }
//    auto numStrings = stringElements.size();
//    string::size_type strSize = delimiter.size() * (numStrings - 1);
//    for (const string & s : stringElements) {
//        strSize += s.size();
//    }
//    str.reserve(strSize);
//    str += stringElements[0];
//    for (decltype(numStrings) i = 1; i < numStrings; ++i) {
//        str += delimiter;
//        str += stringElements[i];
//    }
//    return str;
//}
//
//
////--------------------------------------------------
string ofToLower(const juce::String & src) {
    return src.toLowerCase();
}
//
////--------------------------------------------------
string ofToUpper(const juce::String & src) {
    return src.toUpperCase();
}
//
////--------------------------------------------------
//
