// cowsay.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <tuple>

size_t GetMaxLineLength(std::vector<std::unique_ptr<char[]>>& lines) {
    size_t max_length = 0;
    for (const auto& line : lines) {
        max_length = std::max(max_length, strlen(line.get()));
    }
    return max_length;
}

std::vector<std::unique_ptr<char[]>> GetLines(std::vector<std::string>& input_lines) {
    std::vector<std::unique_ptr<char[]>> lines;

    for (const auto& line : input_lines) {
        auto c_line = line.c_str();
        auto line_length = strlen(c_line);
        auto line_copy = std::make_unique<char[]>(line_length + 1);
        memcpy(line_copy.get(), c_line, line_length);
        line_copy.get()[line_length] = '\0';

        lines.push_back(std::move(line_copy));
    }

    return lines;
}

std::tuple<char, char> GetSpeechBoarderChars(size_t current_line_number, size_t number_of_lines) {

    if (number_of_lines == 1) {
        return std::make_tuple<char, char>('<', '>');
    } else if (current_line_number == 0) {
        return std::make_tuple<char, char>('/', '\\');
    } else if (current_line_number == number_of_lines - 1) {
        return std::make_tuple<char, char>('\\', '/');
    } else {
        return std::make_tuple<char, char>('|', '|');
    }
}

void PrintSpeechBubble(size_t line_length, std::vector<std::unique_ptr<char[]>>& lines) {
    auto filler = std::make_unique<char[]>(line_length + 1);
    memset(filler.get(), ' ', line_length);

    //for (const auto& line : lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        const char* line = lines[i].get();

        auto need_to_fill = line_length - strlen(line);
        filler[need_to_fill] = '\0';

        char start_speech, end_speech;
        std::tie(start_speech, end_speech) = GetSpeechBoarderChars(i, lines.size());

        printf("  %c %s%s %c", start_speech, line, filler.get(), end_speech);
        filler[need_to_fill] = ' ';
        printf("\n");
    }
}

void PrintSpeechBubbleBorder(size_t line_length, bool isTop)
{
        printf("   ");
        for (size_t i = 0; i < line_length + 2; ++i) {
            printf("%c", isTop ? '_' : '-');
        }
        printf("\n");
}

void PrintCow() {
    printf("\t \\   ^__^\n");
    printf("\t   \\ (oo)\\______\n");
    printf("\t     (__)\\       )\\/\\\n");
    printf("\t         ||----w |\n");
    printf("\t         ||     ||\n");
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::vector<std::string> stdin_lines;
    { // get length of file:
        std::cin.seekg(0, std::cin.end);
        auto length = std::cin.tellg();
        std::cin.seekg(0, std::cin.beg);

        if (length.seekpos() > 0) {
            for (std::string readln; std::getline(std::cin, readln);) {
                stdin_lines.push_back(readln);
            }
        }
        else { // If there is nothing in stdin then just say something
            stdin_lines = { "The cow jumped", "over the moon" };
        }
    }

    auto lines = GetLines(stdin_lines);
    auto line_length = GetMaxLineLength(lines);

     // Print the top of the speech bubble
    PrintSpeechBubbleBorder(line_length, true);

    // Print the speech bubble with the text
    PrintSpeechBubble(line_length, lines);

     // Print the bottom of the speech bubble
    PrintSpeechBubbleBorder(line_length, false);

    // Print the cow image
    PrintCow();

    return 0;
}

