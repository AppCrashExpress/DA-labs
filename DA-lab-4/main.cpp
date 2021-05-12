#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <memory>
#include <deque>

#include "CircularBuffer.h"

using TPattern = std::string;
using TVarSize = unsigned long;

void ToLower(std::string& str) {
    for (char& c : str) {
        c = std::tolower(c);
    }
}

//--------------------------------------------//
// Key retrival and suffix prefix array build //
//--------------------------------------------//

std::vector<TPattern> RetrieveKey() {
    std::vector<TPattern> words;
    TPattern firstLine, word;

    std::getline(std::cin, firstLine);
    std::istringstream lineToStream(firstLine);
    
    while (lineToStream >> word) {
        ToLower(word);
        words.push_back(word);
    }

    return words;
}

std::unique_ptr<TVarSize[]> Zfunc(const std::vector<std::string>& pat) { 
    const TVarSize n = pat.size();
    std::unique_ptr<TVarSize[]> zArray ( new TVarSize[n] );
    TVarSize zLeft = 0, zRight = 0;

    for (TVarSize i = 1; i != n; ++i) {
        if (i > zRight) {
            zRight = zLeft = i;
            while ( zRight < n && pat[zRight - zLeft] == pat[zRight]) {
                ++zRight;
            }
            zArray[i] = zRight - zLeft;
            --zRight;
        } else {
            TVarSize k = i - zLeft;
            if (zArray[k] < zRight - i + 1) {
                zArray[i] = zArray[k];
            } else {
                zLeft = i;
                while (zRight < n && pat[zRight - zLeft] == pat[zRight]) {
                    ++zRight;
                }
                zArray[i] = zRight - zLeft;
                --zRight;
            }
        }
    }

    return zArray;
}

std::unique_ptr<TVarSize[]> BuildSP(const std::vector<TPattern>& key) {
    std::unique_ptr<TVarSize[]> zArr = Zfunc(key);
    const TVarSize size = key.size();
    std::unique_ptr<TVarSize[]> suffPref ( new TVarSize[size + 1] );

    for (TVarSize i = 0; i < size + 1; ++i) {
        suffPref[i] = 0;
    }

    for (TVarSize i, j = key.size() - 1; j > 0; --j) {
        i = j + zArr[j];
        suffPref[i] = zArr[j];
    }

    return suffPref;
}

//------//
// Main //
//------//

int main() {

    std::vector<TPattern> key = RetrieveKey();
    std::ios_base::sync_with_stdio(false);
    const TVarSize patternSize = key.size();
    std::unique_ptr<TVarSize[]> suffPref = BuildSP(key);

    TVarSize iter = 0,
             lineNum = 1,
             wordNum = 1,
             currentWord = 0; 
    std::string buff;
    TCircBuff<std::string> text(patternSize);
    std::deque<TVarSize> newLineWordNum;

    char ch = '\0';
    while (ch != EOF) {
        while (text.Size() < patternSize && ch != EOF) {
            ch = std::tolower(std::getchar());
            
            if (ch == '\n' || ch == ' ' || ch == '\t' || ch == EOF) {
                if (!buff.empty()) {
                    text.pushBack(buff);
                    buff.clear();
                    ++currentWord;
                }
                
                if (ch == '\n') {
                    newLineWordNum.push_back(currentWord);
                    currentWord = 0;
                }

            } else {
                buff += ch;

            }
        }

        if (text.Size() < patternSize) {
            continue;
        }

        while (!newLineWordNum.empty() && wordNum > newLineWordNum[0]) {
            ++lineNum;
            wordNum -= newLineWordNum[0];
            newLineWordNum.pop_front();
        }

        while (iter < patternSize && text[iter] == key[iter]) {
            ++iter;
        }

        if (iter == patternSize) {
            std::cout << lineNum << ", " << wordNum << '\n';
        } else if (iter == 0) {
            ++iter;
        }

        text.removeFirst(iter - suffPref[iter]);
        wordNum += iter - suffPref[iter];
        iter = suffPref[iter];
    }

    if (iter == key.size()) {
        std::cout << lineNum << ", " << wordNum << '\n';
    }
}