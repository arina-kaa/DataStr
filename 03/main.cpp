/*
����������� �����, ���

   23. �������  ����  �������������  �����.  ��� ������  ������
�������� �� �����. ���� �� ������� �������� ��������. ���������
������� ������ ���� ������ �� ������������� ����� �� �������  �
������ ������. �����������  �����������  �����������  �����.  �
��������� ������ ������ ����� ����� �� ��������� (12).
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> getShortPaths(vector<vector<int>> roads, const int pointCount)
{
	vector<pair<int, int>> result(pointCount, pair<int, int>(INT_MAX, INT_MAX));
	vector<pair<bool, bool>> isVisited(pointCount, pair<int, int>(false, false));

	result[0].first = 0;
	int currentPoint = 0;
	bool isChanged = true;
	bool isFirst;

	while (isChanged)
	{
		int minLength = INT_MAX;
		for (int i = 0; i < pointCount; i++)
		{
			if (!isVisited[i].first && (result[i].first < minLength))
			{
				minLength = result[i].first;
				currentPoint = i;
				isFirst = true;
			}

			if (!isVisited[i].second && (result[i].second < minLength))
			{
				minLength = result[i].second;
				currentPoint = i;
				isFirst = false;
			}
		}

		if (minLength == INT_MAX)
			break;

		if (isFirst)
			isVisited[currentPoint].first = true;
		else
			isVisited[currentPoint].second = true;

		isChanged = false;
		for (int i = 0; i < pointCount; i++)
		{
			if (!roads[currentPoint][i]) 
			{
				continue;
			}

			int pathLength;
			if (isFirst && (!isVisited[i].first || !isVisited[i].second) && result[currentPoint].first != INT_MAX)
			{
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
			else if (!isVisited[i].second && result[currentPoint].second != INT_MAX)
			{
				pathLength = result[currentPoint].second + roads[currentPoint][i];
				if (pathLength < result[i].second)
				{
					result[i].second = pathLength;
					isChanged = true;
				}
			}

			isChanged = isChanged | !isVisited[i].first | !isVisited[i].second;
		}
	}
	return result;
}

int main()
{
	int pointCount, roadCount;
	cin >> pointCount >> roadCount;

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

	vector<pair<int, int>> paths = getShortPaths(roads, pointCount);

	for (int i = 2; i <= pointCount; i++)
	{
		cout << "From capital (" + to_string(1) + ") to " + to_string(i) + ": " + (paths[i - 1].second != INT_MAX ? to_string(paths[i - 1].second) : "Empty") << endl;
	}
}