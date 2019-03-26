/*
 * MIT License
 * Copyright (c) 2019 Robert Slattery
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>

std::string a = "", b = "";

template<typename T>
constexpr T max(T a, T b)
{
	return (a > b ? a : b);
}

/*
 * Problem:
 * 
 * Given two sequences, find the maximal length of longest subsequence present
 * in both of them. A subsequence is a sequence that appears in the same relative order, 
 * but not necessarily contiguous.
 *
 * Time Complexity: 0(mn)
*/
std::vector<int> longest_common_subsequence(const std::vector<int>& a, const std::vector<int>& b)
{
	std::vector<int> early_out{};

	if (a.empty() || b.empty())
	{
		std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
		std::cout << "ERROR: Invalid array data!, main.cpp:55" << std::endl;
		std::cout << std::endl << "---------------------------------------" << std::endl << std::endl;
		return early_out;
	}

	auto m = a.size(), n = b.size();
	std::vector<std::vector<int>> table(m + 1, std::vector<int>(n + 1));

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if (a[i - 1] == b[j - 1])
				table[i][j] = table[i - 1][j - 1] + 1;
			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);
		}
	}

	int length = table[a.size()][b.size()];
	std::vector<int> lcs(length);
	auto i = m, j = n;

	while (i > 0 && j > 0)
	{
		if (a[i - 1] == b[j - 1])
		{
			lcs[length - 1] = a[i - 1];
			i--; 
			j--; 
			length--;
		}
		else if (table[i - 1][j] > table[i][j - 1])
			i--;
		else
			j--;
	}

	return lcs;
}

int main()
{
	// Read file of strings
	std::ifstream i_file("input.txt");
	i_file >> a;
	i_file.ignore(1024, '\n');
	i_file >> b;
	i_file.close();

	std::stringstream ss(a);
	std::stringstream ss_2(b);
	std::vector<int> v_1;
	std::vector<int> v_2;

	int value = 0;

	while (ss >> value)
	{
		v_1.push_back(value);
		if (ss.peek() == ',') ss.ignore();
	}

	int value_2 = 0;

	while (ss_2 >> value_2)
	{
		v_2.push_back(value_2);
		if (ss_2.peek() == ',') ss_2.ignore();
	}

	std::vector<int> result = longest_common_subsequence(v_1, v_2);

	// Write result to file   
	std::ofstream o_file("output.txt");

	for (int i = 0; i < result.size(); ++i)
	{
		if (i == 0)	o_file << result[i];
		else o_file << "," << result[i];
	}

	o_file.close();

	return 0;
}