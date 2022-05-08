#include <string>
#include <iostream>
#include <ctype.h>
#include <vector>

using namespace std;


string encodeRLE(string str)
{
	size_t len = str.length();
	string output = "";
	for (size_t iter = 0; iter < len; iter++) 
	{
		int count = 1;
		while (iter < len - 1 && str[iter] == str[iter + 1]) 
		{
			count++;
			iter++;
		}
		output += str[iter] + to_string(count);
	}
	return output;
}

string decodeRLE(string str)
{
	size_t len(str.length());
	int	repeat(0),
		iter(0);
	string output,
		number;
	char current_letter;
	
	while(iter<len)
	{
		current_letter = str[iter];
		iter++;
		number = "";
		while(iter<len && isdigit(str[iter]))
		{
			number += str[iter];
			iter++;
		}
		
		repeat = (number=="") ? 1 : stoi(number);
		output += string(repeat, current_letter);
	}
	return output;
}

void test(size_t idx, string input, string output, bool &status, string mode)
{
	string result = decodeRLE(input);
	bool pass = (result == output);

	if (mode != "silient")
	{
		cout << idx << endl;
		cout << input << endl;
		cout << result << endl;
		cout << (pass ? "PASS" : "FAIL") << endl << endl;
	}

	status &= pass;
}

void test_procedure(string mode)
{
	if (mode == "none")
		return;

	bool status = true;
	vector<string> tests = { "a","a3","a10","ab","a2b2","a2b10aca3" };
	vector<string> outputs = { "a","aaa","aaaaaaaaaa","ab","aabb","aabbbbbbbbbbacaaa" };

	if (tests.size() != outputs.size())
		return;

	for (size_t i = 0; i < tests.size(); i++)
		test(i, tests[i], outputs[i], status, mode);

	if (status == false)
	{
		string msg = "Tests not passed.";
		cout << msg << endl;
		throw runtime_error(msg);
	}
}

int main()
{
	test_procedure("silient");

	string input,output,mode;
	while (true)
	{
		cout << "encode(e)/decode(d)?" << endl;
		cin >> mode;
		if (mode != "d" && mode != "e")
			break;

		cout << "string?" << endl;
		cin >> input;
		output = (mode == "d") ? decodeRLE(input) : encodeRLE(input);
		cout << output << endl;
	}
	return 0;
}