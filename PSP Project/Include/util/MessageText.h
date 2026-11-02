#ifndef MESSAGE_TEXT_H
#define MESSAGE_TEXT_H

#include <string>
#include <vector>

// Measure and render the same lines so panel height matches word wrapping.
template <typename Measure>
std::vector<std::string> wrapMessageText(const std::string &text, int width, Measure measure)
{
    std::vector<std::string> lines;
    size_t start = 0;
    do {
        size_t newline = text.find('\n', start);
        std::string paragraph = text.substr(start, newline - start);
        if (!paragraph.empty() && paragraph[paragraph.size() - 1] == '\r')
            paragraph.erase(paragraph.size() - 1);
        if (paragraph.empty())
            lines.push_back("");
        while (!paragraph.empty()) {
            size_t end = 1;
            while (end <= paragraph.size() && measure(paragraph.substr(0, end)) <= width)
                ++end;
            size_t count = end - 1;
            if (count < paragraph.size()) {
                size_t space = paragraph.rfind(' ', count);
                if (space != std::string::npos && space > 0)
                    count = space;
            }
            if (count == 0) count = 1;
            lines.push_back(paragraph.substr(0, count));
            paragraph.erase(0, count);
            paragraph.erase(0, paragraph.find_first_not_of(' '));
        }
        if (newline == std::string::npos) break;
        start = newline + 1;
    } while (start <= text.size());
    return lines;
}

#endif
