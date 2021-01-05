#include "stdafx.h"
#include "Algorithms.h"


CAlgorithms::CAlgorithms(void)
{
}


CAlgorithms::~CAlgorithms(void)
{
}


void CAlgorithms::Example01(float _arg_input, float &_arg_output)
{
	float a = 9.35, b = 10.12;
	_arg_output = a * _arg_output + b;
}
void CAlgorithms::Example02(std::deque<float> _arg_input, std::deque<float> &_arg_output)
{
	_arg_output.clear();
	std::deque<float> _ma5, _ma15;
	int i;
	
	for(i=0;i<_arg_input.size();i++)
	{
		_ma5.push_back(0);
		_ma15.push_back(0);
		_arg_output.push_back(0);
	}

	MA(_arg_input,5,_ma5);
	MA(_arg_input,15,_ma15);

	for(int i=1;i<_arg_input.size();i++)
	{
		if ( _ma5[i-1] <_ma15[i-1] && _ma5[i] > _ma15[i] )
			_arg_output[i] = DRAWSTYLE_BUY;

		else if( _ma5[i-1] >_ma15[i-1] && _ma5[i] < _ma15[i])
			_arg_output[i] = DRAWSTYLE_SELL;
		else 
			_arg_output[i] = 0;
	}
}
void CAlgorithms::Example03(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output)
{
	_arg_output.clear();
	std::deque<SINGLE_DATA> mdata;
	for (int i = 0; i < _arg_input[0].size(); i++)
	{
		SINGLE_DATA _single_data;
		_single_data.high = _arg_input[0][i];
		_single_data.low = _arg_input[1][i];
		_single_data.is_combined = 0;
		mdata.push_back(_single_data);
		_arg_output.push_back(0);
	}

	/*for (int i = 0; i < _arg_input[0].size() - 1; i++)
	{
		if (mdata[i].is_combined) continue;
		int next = 1;
		while((mdata[i].high > mdata[i + next].high && mdata[i].low < mdata[i + next].low) || (mdata[i].high < mdata[i + next].high && mdata[i].low > mdata[i + next].low))
		{
			mdata[i + next].is_combined = 1;
			int k = 1;
			while (mdata[i - k].is_combined) k++;
			if(0 == i || mdata[i].high > mdata[i-k].high)
			{
				mdata[i].high = mdata[i].high > mdata[i + next].high ? mdata[i].high : mdata[i + next].high;
				mdata[i].low = mdata[i].low > mdata[i + next].low ? mdata[i].low : mdata[i + next].low;
			}
			else
			{ 
				mdata[i].high = mdata[i].high < mdata[i + next].high ? mdata[i].high : mdata[i + next].high;
				mdata[i].low = mdata[i].low < mdata[i + next].low ? mdata[i].low : mdata[i + next].low;
			}
			++next;
		}
	}*/

	for(int i=0;i<_arg_input[0].size()-1;i++)
	{
		if (_arg_output[i] == 100) continue;
		if ((_arg_input[0][i] >= _arg_input[0][i + 1] && _arg_input[1][i] <= _arg_input[1][i + 1]) || (_arg_input[0][i] <= _arg_input[0][i + 1] && _arg_input[1][i] >= _arg_input[1][i + 1]))
		{
			_arg_output[i + 1] = 100;
		}
	}
}

void CAlgorithms::Example04(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output)
{
	_arg_output.clear();
	for(int i=1;i<_arg_input.size();i++)
	{
		std::deque<float> _v;
		for(int j=0;j<_arg_input[i].size();j++)
			_v.push_back(log(_arg_input[i][j]));
		_arg_output.push_back(_v);
	}
}


void CAlgorithms::Example11(float _arg_input, float &_arg_output)
{
	;
}
void CAlgorithms::Example12(std::deque<float> _arg_input, std::deque<float> &_arg_output)
{
	;
}
void CAlgorithms::Example13(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output)
{
	;
}
void CAlgorithms::Example14(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output)
{
	;
}

void CAlgorithms::MA(std::deque<float> _arg_input,int _ma_period ,std::deque<float> &_arg_output)
{
	int i;
	float _sum = 0;
	
	for(i = 0; i < ((_ma_period < _arg_input.size()) ? _ma_period : _arg_input.size()); i++)
	{
		_sum += _arg_input[i];
		_arg_output[i] = _sum / (i+1);
	}

	for(i = _ma_period; i < _arg_input.size(); i++)
	{
		_sum += _arg_input[i] - _arg_input[i-_ma_period];
		_arg_output[i] = _sum / _ma_period;
	}
}