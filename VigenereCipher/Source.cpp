// Source.cpp : main file

#include <iostream>
#include <string>
#include <vector>
#include <array>

constexpr std::array<int, 26> letters{ (int)'a', (int)'b', (int)'c', (int)'d', (int)'e', (int)'f', (int)'g', (int)'h', (int)'i', (int)'j', (int)'k', (int)'l', (int)'m', (int)'n', (int)'o', (int)'p', (int)'q', (int)'r', (int)'s',
't', (int)'u', (int)'v', (int)'w', (int)'x', (int)'y', (int)'z' };


std::vector<bool> checkCase(const std::vector<int>& vect) {

    std::vector<bool> caseList;

    for (size_t i{ 0 }; i < vect.size(); ++i) {

        if (vect[i] == std::toupper(vect[i])) {

            caseList.push_back(true);

        }
        else if (vect[i] == std::tolower(vect[i])) {

            caseList.push_back(false);

        }

    }

    return caseList;

}

std::vector<int> toLowerCase(std::vector<int> stringArr) {

    for (size_t i{ 0 }; i < stringArr.size(); ++i) {

        stringArr[i] = std::tolower(stringArr[i]);

    }

    return stringArr;

}

bool compare(int value, const std::array<int, 26>& arr) {

    for (size_t j{ 0 }; j < arr.size(); ++j) {

        if (value == static_cast<int>(arr[j])) {

            return true;

        }
    }

    return false;

}

template <typename Tx>
size_t indexOf(Tx value, const std::array<int, 26>& arr) {

    for (size_t i{ 0 }; i < arr.size(); ++i) {

        if (value == arr[i]) {

            return i; // if "value" and "array[i]" is equal "i" must be equal to index

        }

    }

    return arr.size(); // gives a value out of range of "arr" to indicate that "value" is not in array

}

std::vector<int> encode(std::vector<int> text, std::vector<int> key) {
    std::vector<int> result(text.size(), 0);

    int offset{ 0 };

    for (size_t i{ 0 }; i < text.size(); ++i) {
        if (compare(text[i], letters)) {

            result[i] = letters[(indexOf<int>(text[i], letters) + indexOf<int>(key[(i - offset) % key.size()], letters)) % letters.size()];

        }
        else {

            result[i] = text[i];
            ++offset;

        }
    }

    return result;

}

std::vector<int> decode(std::vector<int> text, std::vector<int> key) {
    std::vector<int> result(text.size(), 0);

    int offset{ 0 };

    for (size_t i{ 0 }; i < text.size(); ++i) {
        if (compare(text[i], letters)) {

            result[i] = letters[(letters.size() + (indexOf<int>(text[i], letters) - indexOf<int>(key[(i - offset) % key.size()], letters))) % letters.size()];

        }
        else {

            result[i] = text[i];
            ++offset;

        }
    }

    return result;

}

std::string asciiToString(const std::vector<int>& vect) {

    std::string str;

    for (size_t i{ 0 }; i < vect.size(); ++i) {

        str += static_cast<char>(vect[i]);

    }

    return str;

}

std::string setCase(std::string string, const std::vector<bool>& caseList) {

    for (size_t i{ 0 }; i < string.size(); ++i) {

        if (caseList[i]) {

            string[i] = static_cast<char>(toupper(static_cast<int>(string[i])));

        }

    }

    return string;
}


int main()
{
    // input text
    std::string inputText{};
    std::cout << "Input text ";
    std::getline(std::cin, inputText);

    // str split to array
    std::vector<int> strArr;
    for (size_t i{ 0 }; i < inputText.size(); ++i) {

        strArr.push_back(static_cast<int>(inputText[i]));

    }

    // check case of lnput text
    std::vector<bool> lowerUpper;
    lowerUpper = checkCase(strArr);

    // will not work with uppercase
    strArr = toLowerCase(strArr);


    // input key
    std::string inputKey{};
    std::cout << "Input key ";
    std::getline(std::cin, inputKey);

    // key split to array
    std::vector<int> keyArr;
    for (size_t i{ 0 }; i < inputKey.size(); ++i) {

        keyArr.push_back(static_cast<int>(inputKey[i]));

    }

    // will not work with uppercase
    keyArr = toLowerCase(keyArr);


    // ask to encode or decode
    int encDec{  };
    std::cout << "\nencode type \"1\" or decode type \"0\": ";
    std::cin >> encDec;

    // encode
    if (encDec == 1) {

        std::cout << '\n' << setCase(asciiToString(encode(strArr, keyArr)), lowerUpper) << '\n';

    }
    // decode
    else if (encDec == 0) {

        std::cout << '\n' << setCase(asciiToString(decode(strArr, keyArr)), lowerUpper) << '\n';

    }

}