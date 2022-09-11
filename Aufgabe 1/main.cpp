#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define CONTAINS(vector, element)(\
	std::find(vector.begin(), vector.end(), element) != vector.end())

template <typename T1, typename T2>
inline bool contains(std::vector<T1>& vec, T2& element) {
	return std::find(vec.begin(), vec.end(), element) != vec.end();
}

std::vector<std::string> split_str(const char* str, std::vector<char> splitter) {
	std::vector<std::string> str_splits;
	const char* tmp_str;
	char splitter_e = '\0';

	while (true) {
		tmp_str = str;

		for (; not CONTAINS(splitter, *str); str++) {
			if (*str == '\0') {
				str_splits.push_back(std::string(tmp_str));
				return str_splits;
			}
		}

		if ((str - tmp_str) != 0) {
			std::swap(*((char*)str), splitter_e);
			str_splits.push_back(std::string(tmp_str));
			std::swap(*((char*)str), splitter_e);
		}

		str++;
	}
}

size_t find_word(const char* str, std::string word) {

	const char* possible_begin;

	for (const char* s = str; *s != '\0'; s++) {
		if (std::tolower(*s) != word[0]) {
			for (; *s != ' '; s++);
		}
		else {

		}
	}

}

int main(int argc, char** argv) {
	
	auto read_text_file = [](std::string file) {

	};

	auto find_sentence_in_text = [](const char* text, std::string sentence) {

		std::vector<std::string> words = split_str(sentence.c_str(), { ' ', '_', '-', '\'', '"', '.', '!', '?', '[', ']', '(', ')', '»', '«', '\n', '\r' });
		
		for (auto word : words) {
			std::cout << "\"" << word << "\" ";
		}

	};

}

