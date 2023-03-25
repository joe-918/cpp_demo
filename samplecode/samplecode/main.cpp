//
//  main.cpp
//  samplecode
//
//  Created by sunny on 2023/3/25.
//

#include <iostream>
#include <unordered_map>

int lengthOfLongestSubstring(std::string s);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    std::string strs[] = {
        "aabcdba",
        "abcde",
        "eabcae",
    };

    for (auto s : strs) {
        std::cout <<"maxlenth of: "<<s<<": "<<lengthOfLongestSubstring(s)<<std::endl;
    }

    return 0;
}



/**
 * 无重复的最长子序列
 *     https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 */
int lengthOfLongestSubstring(std::string s) {
    int maxLen = 0; //最大长度
    int left = 0; //无重复字串的起始位置
    std::unordered_map<char,int> charset;

    /**
     * 说明：从左向右遍历每个字符，把每个字符在字符串中的位置记录在临时map中
     * 如果遇到map中包含的字符，该字符上一次出现的下一位作为无重复字符串的起始位置
     * 但是需要确保无重复子串的起始位置是一直右移的
     */
    for (int i = 0; i < s.size(); i++) {
        auto c = s[i];
        if (charset.count(c) != 0) {
            //检测到一个重复的字符，无重复字串的指针右移一位
            left = std::max(left, charset[c] + 1);
        }
        charset[c] = i;
        //i - left + 1 是因为left-i之间都是无重复子串，需要包含left位置的元素	
        maxLen = std::max(maxLen, i - left + 1);
    }

    /**
     * 注意，不能用字符当前位置减去上一次的位置当作字串长度，因为两个字符中间可能还会有重复字符
     * 所以必须用left来记录当前遍历过程中的无重复字串
     */
    return maxLen;
}
