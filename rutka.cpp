#include <algorithm>
#include <cstdint>
#include <iostream>
#include <locale>
#include <random>
#include <string>
#include <string_view>

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

	bool is_number(std::wstring_view str)
	{
		if (str.empty())
		{
			return false;
		}

		auto is_digit = [](wchar_t c)
		{
			static std::locale loc;
			return std::isdigit(c, loc);
		};

		return std::all_of(str.cbegin(), str.cend(), isdigit);
	}

	template <typename T>
	T read_numeric_input(std::wstring_view message)
	{
		std::wstring input;

		do
		{
			std::wcout << message << std::endl;
			std::wcin >> input;
		} while (!is_number(input));

		std::cout << std::endl;
		return static_cast<T>(std::stoll(input, 0, 10));
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

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
int wmain(int, wchar_t**)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
#else
int main(int, char**)
{
	setlocale(LC_ALL, "en_US.UTF-8");
#endif
	using namespace rutka;

	std::wcout << L"Intialainen Rutka" << std::endl;
	std::wcout << L"Idea kopioitu: tAAt" << std::endl << std::endl;;

	const uint32_t guess = read_numeric_input<uint32_t>(L"Syötä numero:");

	std::wcout << L"Syöttämäsi luku: " << guess << std::endl;
	std::wcout << L"Koneen luku: " << generate_secret(guess) << std::endl;
	std::wcout << std::endl << L"Hävisit rutkasti." << std::endl;

	return 0;
}