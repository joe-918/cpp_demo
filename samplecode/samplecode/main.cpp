//
//  main.cpp
//  samplecode
//
//  Created by sunny on 2023/3/25.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>

int lengthOfLongestSubstring(std::string s);
int lengthOfLongestSubstring2(std::string s);

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    std::string strs[] = {
        "aabcdba",
        "abcde",
        "eabcae",
        "abcbd",
    };

    for (auto s : strs) {
        std::cout <<"maxlenth of: "<<s<<": "<<lengthOfLongestSubstring(s)<<std::endl;
        std::cout <<"maxlenth of: "<<s<<": "<<lengthOfLongestSubstring2(s)<<std::endl;
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

int lengthOfLongestSubstring2(std::string s) {
    std::unordered_set<char> set;
    int left = 0, right = 0, maxLength = 0;
    /**
     * 方法二，维护一个无序集合（unordered_set）来检测是否有重复字符。
     * left和right两个指针分别指向当前检测到的子串的左端点和右端点，然后不断地扩大右端点，同时判断是否有重复字符，如果有则缩小左端点，直到没有重复字符为止。
     * 在这个过程中，记录下最长的子串的长度并返回即可。
     */
    while (right < s.size()) {
        if (set.find(s[right]) == set.end()) {
            set.insert(s[right]);
            maxLength = std::max(maxLength, right - left + 1);
            right++;
        } else {
            //如果有重复字符，则窗口左端前进一位，右端不变，进行下一轮检查，直到窗口中无重复字符为止
            //比如abcc,检测到第二个c时就把窗口中的abc全清掉
            set.erase(s[left]);
            left++;
        }
    }
    return maxLength;
}
