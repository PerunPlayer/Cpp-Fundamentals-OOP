#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> createSimpleField(size_t n)
{
	vector<string> frogField((n * 2) + 1);
	for (size_t i = 0; i < frogField.size(); i++)
	{
		if (i < n)
		{
			frogField[i] = "R";
		}
		else if (i == n)
		{
			frogField[i] = " ";
		}
		else
		{
			frogField[i] = "L";
		}
	}
	return frogField;
}

vector<string> createCorrectField(size_t n)
{
	vector<string> frogField((n * 2) + 1);
	for (size_t i = 0; i < frogField.size(); i++)
	{
		if (i < n)
		{
			frogField[i] = "L";
		}
		else if (i == n)
		{
			frogField[i] = " ";
		}
		else
		{
			frogField[i] = "R";
		}
	}
	return frogField;
}

void print(vector<string>& frogField)
{
	cout << "[";
	size_t i = 0;
	for (; i < frogField.size() - 1; i++)
	{
		cout << frogField[i] << ", ";
	}
	cout << frogField[i] << "]\n";
}

void moveToLeft(size_t steps, size_t countMax, vector<string>& frogField, vector<string>& correctField)
{
	for (int i = 0; (i < frogField.size()) && steps; i++)
	{
		if ((frogField[0] == "L") && (countMax >= 2) && (i == 0))
		{
			continue;
		}
		else if ((frogField[0] == "L") && (countMax >= 2) && (frogField[i] == "L") && (frogField[i - 1] == " "))
		{
			swap(frogField[i], frogField[i - 1]);
			print(frogField);
			steps--;
			if (frogField == correctField)
			{
				return;
			}
		}
		else if ((frogField[i] == "L") && (frogField[i - 1] == " ") && ((i - 2) < 0))
		{
			swap(frogField[i], frogField[i - 1]);
			print(frogField);
			steps--;
		}
		else if ((frogField[i] == "L") && (frogField[i - 1] == " ") && ((i - 2) >= 0) && (frogField[i - 2] == "R"))
		{
			swap(frogField[i], frogField[i - 1]);
			print(frogField);
			steps--;
		}
		else if ((frogField[i] == "L") && ((i - 2) >= 0) && (frogField[i - 2] == " "))
		{
			swap(frogField[i], frogField[i - 2]);
			print(frogField);
			steps--;
		}
	}
}

void moveToRight(size_t steps, size_t countMax, vector<string>& frogField, vector<string>& correctField)
{
	bool flag = false;
	for (size_t i = 0; i < frogField.size() && steps;)
	{
		flag = false;
		if ((frogField[i] == "R") && ((i + 1) < frogField.size()) && (frogField[i + 1] == " ") && (steps == 1))
		{
			swap(frogField[i], frogField[i + 1]);
			print(frogField);
			steps--;
		}
		else if ((frogField[i] == "R") && ((i + 1) < frogField.size()) && (frogField[i + 1] == " ") && (steps != 1) && (countMax >= 2))
		{
			swap(frogField[i], frogField[i + 1]);
			print(frogField);
			steps--;
			flag = true;
			if (frogField == correctField)
			{
				return;
			}
		}
		else if ((frogField[i] == "R") && ((i + 2) < frogField.size()) && (frogField[i + 2] == " ") && (frogField[i + 1] != "R"))
		{
			swap(frogField[i], frogField[i + 2]);
			print(frogField);
			steps--;
			flag = true;
		}
		else if (frogField[i] == "R")
		{
			bool areInCorrectDirection = true;
			int diff = frogField.size() - i;
			for (size_t j = i; j < frogField.size(); j++)
			{
				if (frogField[j] != "R")
				{
					areInCorrectDirection = false;
					break;
				}
			}
			if (areInCorrectDirection && (diff == ((frogField.size() - 1) / 2)))
			{
				return;
			}
		}
		i = flag ? 0 : i + 1;
	}
}

void frogsJumping(size_t frogsInDirection)
{
	vector<string> frogField((frogsInDirection * 2) + 1);
	frogField = createSimpleField(frogsInDirection);
	vector<string> correctField((frogsInDirection * 2) + 1);
	correctField = createCorrectField(frogsInDirection);

	//--------------------------
	print(frogField);
	//print(correctField);
	//--------------------------

	size_t countMax = 0;		//max times for max movements made in one direction
	for (size_t i = 1; i <= frogField.size(), countMax <= 3, frogField != correctField;)
	{
		moveToLeft(i, countMax, frogField, correctField);
		((i == frogsInDirection) && countMax < 3) ? countMax++ : i++;
		if (frogField == correctField)
		{
			return;
		}
		if (countMax == 3)
		{
			i = frogsInDirection;
		} 
		moveToRight(i, countMax, frogField, correctField);
		if (frogField == correctField)
		{
			return;
		}

		((i == frogsInDirection) && countMax < 3) ? countMax++ : i++;
	}
	print(frogField);
}

int main()
{
	int frogsInDirection;

	do
	{
		cout << "Enter a positive number of frogs in one direction: ";
		cin >> frogsInDirection;
	} while (frogsInDirection <= 0);

	frogsJumping(frogsInDirection);

	return 0;
}