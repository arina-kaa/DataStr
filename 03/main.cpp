/*
Каравайцева Арина, ИПС

   23. Имеется  сеть  автомобильных  дорог.  Для каждой  дороги
известна ее длина. Один из городов является столицей. Требуется
вывести список длин вторых по минимальности путей из столицы  в
другие города. Допускается  присутствие  циклических  путей.  В
некоторые города вторых путей может не оказаться (12).
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> getShortPaths(vector<vector<int>> roads, const int pointCount, const int capitalIndex)
{
	vector<pair<int, int>> result(pointCount, pair<int, int>(INT_MAX, INT_MAX));
	vector<pair<bool, bool>> isVisited(pointCount, pair<int, int>(false, false));

	result[capitalIndex].first = 0;
	int currentPoint = 0;
	bool isChanged = true;

	while (isChanged)
	{
		int minLength = INT_MAX;

		for (int i = 0; i < pointCount; i++)
		{
			if (!isVisited[i].first && (result[i].first < minLength))
			{
				minLength = result[i].first;
				currentPoint = i;
				isVisited[currentPoint].first = true;
			}

			if (!isVisited[i].second && (result[i].second < minLength))
			{
				minLength = result[i].second;
				currentPoint = i;
				isVisited[currentPoint].second = true;
			}
		}

		if (minLength == INT_MAX)
			break;

		isChanged = false;
		for (int i = 0; i < pointCount; i++)
		{
			if (!roads[currentPoint][i])
			{
				continue;
			}

			int pathLength = result[currentPoint].second + roads[currentPoint][i];
			if (isVisited[currentPoint].first && !isVisited[currentPoint].second)
			{
				if (isVisited[i].first && isVisited[i].second && result[currentPoint].first == INT_MAX)
				{
					continue;
				}
				pathLength = result[currentPoint].first + roads[currentPoint][i];
				if (pathLength < result[i].first)
				{
					result[i].second = result[i].first;
					result[i].first = pathLength;
					isChanged = true;
				}
				else if (pathLength < result[i].second)
				{
					result[i].second = pathLength;
					isChanged = true;
				}
			}
			else if (!isVisited[i].second && result[currentPoint].second != INT_MAX && (pathLength < result[i].second))
			{
				result[i].second = pathLength;
				isChanged = true;
			}

			isChanged = isChanged || !isVisited[i].first || !isVisited[i].second;
		}
	}
	return result;
}

int main()
{
	int pointCount, roadCount, capitalNumber;
	cin >> pointCount >> roadCount >> capitalNumber;

	vector<vector<int>> roads(pointCount);

	for (int i = 0; i < pointCount; i++)
	{
		roads[i].resize(pointCount);
	}

	for (int i = 0; i < roadCount; i++)
	{
		int startPoint, endPoint, roadLength;
		cin >> startPoint >> endPoint >> roadLength;
		roads[startPoint - 1][endPoint - 1] = roadLength;
	}

	vector<pair<int, int>> paths = getShortPaths(roads, pointCount, capitalNumber - 1);

	for (int i = 1; i <= pointCount; i++)
	{
		if (capitalNumber != i)
		{
			cout << "From " + to_string(capitalNumber) + " to " + to_string(i) + ": " + (paths[i - 1].second != INT_MAX ? to_string(paths[i - 1].second) : "No path") << endl;
		}
	}

	return 0;
}