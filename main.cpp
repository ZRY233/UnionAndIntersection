#include<iostream>
#include<map>
using namespace std;

//字体颜色：https://blog.csdn.net/qq_42876636/article/details/82960511

/*
	作者：@ZRY233 (https://zry233.t.me)
		Email：zhangruiyang233@gmail.com

	小白练手作品

*/

inline void loopAssignment(int* input, int value, int count)
{
	for (int i = 0; i < count; i++)
	{
		input[i] = value;
	}
}

inline void loopPrint(int* input, int count)
{
	if (count == 0)
	{
		cout << "[]" << endl;
		return;
	}
	cout << "[";
	for (int i = 0; i < count; i++)
	{
		cout << input[i] << ",";
	}
	cout << "\b]" << endl;
}

int convertUnion(int* input, int count)
{
	int tempArray[1024]{};
	int unionedCount = 0;
	loopAssignment(tempArray, INT_MIN, 1024);

	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (input[i] == tempArray[j])
			{
				break;
			}
			else if (j == i)
			{
				tempArray[unionedCount++] = input[i];
			}
		}
	}

	loopAssignment(input, INT_MIN, count);
	for (int i = 0; i < unionedCount; i++)
	{
		input[i] = tempArray[i];
	}

	return unionedCount;
}

int convertIntersection(int* input, int count, int times)
{
	using MAP = map<int, int>;
	MAP m;

	for (int i = 0; i < count; i++)
	{
		m[input[i]] = 0;
	}

	for (int i = 0; i < count; i++)
	{
		m[input[i]] += 1;
	}

	int tempArray[1024]{};
	int intersectedCount = 0;
	for (MAP::iterator it = m.begin(); it != m.end(); it++)
	{
		if (it->second == times)
		{
			tempArray[intersectedCount++] = it->first;
		}
	}

	loopAssignment(input, INT_MIN, count);
	for (int i = 0; i < intersectedCount; i++)
	{
		input[i] = tempArray[i];
	}

	return intersectedCount;
}

int main()
{
	int times = 0;
	cout << "\033[42m[interact]\033[49m \033[33mtimes\033[37m:\033[35m";
	cin >> times;

	int overallArray[1024]{};
	loopAssignment(overallArray, INT_MIN, 1024);

	int count = 0;
	cout << "\033[43m\033[37m[hint]\033[49m \033[32m向数组中输入元素，使用空白字符进行分隔，完成后输入非整数类数据以结束输入\033[37m" << endl;
	for (int i = 0; i < times; i++)
	{
		int tempArray[256]{};
		int tempCount = 0;
		loopAssignment(tempArray, INT_MIN, 256);

		cout << "\033[37m\033[42m[interact]\033[49m \033[33mArray #" << i + 1 << "\033[37m:\033[35m";
		while (cin >> tempArray[tempCount])++tempCount;
		cin.clear();
		cin.ignore(LLONG_MAX, '\n');

		int unionedCount = convertUnion(tempArray, tempCount);
		for (int i = 0; i < unionedCount; i++)
		{
			overallArray[count++] = tempArray[i];
		}
	}

	cout << "\033[41m\033[37m[debug]\033[49m \033[31moverallArray\033[37m:\033[32m";
	loopPrint(overallArray, count);

	//取并集
	int* unionArray = new int[count] {};
	copy(overallArray, overallArray + count, unionArray);
	int unionedOverallCount = convertUnion(unionArray, count);
	cout << "\033[0m\033[44m\033[37m[output]\033[49m \033[33m取\033[1m并\033[0m\033[33m集为\033[37m\033[1m:\033[36m";
	loopPrint(unionArray, unionedOverallCount);
	delete[] unionArray;

	//取交集
	int* intersectionArray = new int[count] {};
	copy(overallArray, overallArray + count, intersectionArray);
	int intersectedOverallCount = convertIntersection(intersectionArray, count, times);
	cout << "\033[0m\033[44m\033[37m[output]\033[49m \033[33m取\033[1m交\033[0m\033[33m集为\033[37m\033[1m:\033[36m";
	loopPrint(intersectionArray, intersectedOverallCount);
	delete[] intersectionArray;

	cout << "\033[0m";
}