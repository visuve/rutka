#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>

namespace rutka
{
	template <typename T>
	T random_number()
	{
		thread_local std::random_device device;
		thread_local std::mt19937 engine(device());
		thread_local std::uniform_int_distribution<T> distribution(
			std::numeric_limits<T>::min(),
			std::numeric_limits<T>::max());

		return distribution(engine);
	}

	bool is_number(const std::string& str)
	{
		if (str.empty())
		{
			return false;
		}

		return std::find_if(str.cbegin(), str.cend(), std::isdigit) != str.cend();
	}

	template <typename T>
	T read_numeric_input(const std::string& message)
	{
		std::string input;

		do
		{
			std::cout << message << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input.clear();
			std::getline(std::cin, input);
		} while (!is_number(input));

		std::cout << std::endl;
		return static_cast<T>(std::strtoll(input.c_str(), 0, 10));
	}

	template <typename T>
	T generate_secret(T guess)
	{
		T secret;

		do
		{
			secret = random_number<T>();
		} while (guess == secret);

		return secret;
	}
}


int main(int argc, char** argv)
{
	using namespace rutka;

	std::cout << "Intialainen Rutka" << std::endl;
	std::cout << "Idea kopioitu: tAAt" << std::endl << std::endl;;

	const uint32_t guess = read_numeric_input<uint32_t>("Syötä numero:");

	std::cout << "Syöttämäsi luku: " << guess << std::endl;
	std::cout << "Koneen luku: " << generate_secret(guess) << std::endl;
	std::cout << std::endl << "Hävisit rutkasti." << std::endl;

	return 0;
}