#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>

using namespace std;

int N;
unsigned int A[500001];
unsigned int B[500001];
unsigned long long ret;

// �պ� �� ������ �Բ� ���ϱ�
void merge(int begin, int end)
{
	int mid = (begin + end) / 2;
	int l = begin;
	int r = mid + 1;
	int k = begin;

	int cnt = 0;

	while (l <= mid && r <= end)
	{
		// ���� �迭�� ���� ���ĵ� ��
		if (A[l] <= A[r])
		{
			B[k++] = A[l++];
			ret += static_cast<unsigned long long>(cnt);
		}
		// ������ �迭�� ���� ���ĵ� ��
		else
		{
			B[k++] = A[r++];
			++cnt;
		}
	}

	if (l > mid)
	{
		while (r <= end)
		{
			B[k++] = A[r++];
			cnt++;
		}
	}
	else
	{
		while (l <= mid)
		{
			B[k++] = A[l++];
			ret += static_cast<unsigned long long>(cnt);
		}
	}

	for (int i = begin; i <= end; ++i)
		A[i] = B[i];
}

void mergesort(int begin, int end)
{
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		mergesort(begin, mid);
		mergesort(mid + 1, end);
		merge(begin, end);
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> A[i];

	mergesort(0, N - 1);

	cout << ret;
}