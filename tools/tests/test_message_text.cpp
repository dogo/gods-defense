#include "../../PSP Project/Include/util/MessageText.h"
#include <cassert>

int main()
{
    const auto measure = [](const std::string &s) { return (int)s.size(); };
    assert((wrapMessageText("Wave 1!", 20, measure) == std::vector<std::string>{"Wave 1!"}));
    assert((wrapMessageText("one two three", 7, measure) == std::vector<std::string>{"one two", "three"}));
    assert((wrapMessageText("12345678", 3, measure) == std::vector<std::string>{"123", "456", "78"}));
    assert((wrapMessageText("a\r\n\nb\n", 10, measure) == std::vector<std::string>{"a", "", "b", ""}));
    assert((wrapMessageText("", 10, measure) == std::vector<std::string>{""}));
    const auto variableWidth = [](const std::string &s) {
        int width = 0;
        for (char c : s) width += c == 'W' ? 3 : 1;
        return width;
    };
    assert((wrapMessageText("WW ii WW", 6, variableWidth) == std::vector<std::string>{"WW", "ii", "WW"}));
}
