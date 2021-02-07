#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

bool find_elem(std::vector<std::string>& words , std::string word);
std::string tolover(std::string& word);
std::string erase_puncts(std::string& word);

int main()
{
	int most_freq = 0;
	std::string most_freq_word;

	std::string word;
	std::unordered_map<std::string , int> dictionary;
	std::vector<std::string> words;
	std::ifstream in("text");

	while(in >> word)
	{
		word = erase_puncts(word);
		word = tolover(word);
		if (word.size() == 0)
			continue;
		dictionary[word]++;
		if (find_elem(words , word))
			words.push_back(word);
	}

	for (auto it = words.begin() ; it != words.end() ; ++it)
		if (most_freq < dictionary[*it])
		{
			most_freq = dictionary[*it];
			most_freq_word = *it;
		};

		std::cout << most_freq_word << "-" << most_freq << std::endl;

	return 0;
}

bool find_elem(std::vector<std::string>& words , std::string word)
{
	bool mark = true;

	for (auto it = words.begin() ; it != words.end() ; ++it)
		if (*it == word)
		{
			mark = false;
			return mark;
		}
	return mark;
}

std::string tolover(std::string& word)
{
	for (auto it = word.begin() ; it != word.end() ; ++it)
		*it = tolower(*it);
	return word;
}

std::string erase_puncts(std::string& word)
{
	std::string result;
	for (auto it = word.begin() ; it != word.end() ; ++it)
		if (isalpha(*it))
			result = result + *it;
			
	return result;
}