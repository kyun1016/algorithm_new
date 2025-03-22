#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<memory>

using namespace std;

template <typename T>
class Stack
{
public:
	Stack(size_t size = 8)
		: _size(size)
		, _count(0)
	{
		_arr = make_unique<T[]>(_size);
	}
	~Stack() = default;

	void Push(const T& d)
	{
		if (_count == _size)
		{
			_size <<= 1;
			unique_ptr<T[]> _newArr = make_unique<T[]>(_size);
			for (size_t i = 0; i < _count; ++i)
				_newArr[i] = _arr[i];

			_arr = move(_newArr);
		}

		_arr[_count++] = d;
	}

	T Pop()
	{
		if (Empty())
			return -1;
		return _arr[--_count];
	}

	size_t Count() const
	{
		return _count;
	}

	bool Empty() const
	{
		return _count == 0;
	}

	T Peak() const
	{
		if (Empty())
			return -1;
		return _arr[_count - 1];
	}


private:
	size_t _size;
	size_t _count;
	unique_ptr<T[]> _arr;
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N;
	int opcode;
	int operand;

	cin >> N;
	Stack<int> st(N);
	while (N--)
	{
		cin >> opcode;
		if (opcode == 1)
			cin >> operand;

		switch (opcode)
		{
		case 1:
			st.Push(operand);
			break;
		case 2:
			cout << st.Pop() << '\n';
			break;
		case 3:
			cout << st.Count() << '\n';
			break;
		case 4:
			if (st.Empty())
				cout << "1\n";
			else
				cout << "0\n";
			break;
		case 5:
			cout << st.Peak() << '\n';
			break;
		}
	}

	return 0;
}