#include "stdafx.h"
#include "Algorithms.h"
#include<fstream>
#include<float.h>
#include<math.h>

bool IS_SHAKE(double _x1, double _x2,double _rate)
{
	if (_x1 == 0)
		return false;
	if (abs((_x1 - _x2) / _x1) < _rate)
		return true;
	return false;
}//判断是连续变动还是抖动

std::deque<double> smoothing(std::deque<double> _arg_input, double _coefficient)
{
	if (_arg_input.size() < 2 || _coefficient < 0 || _coefficient>1)
		return _arg_input;
	int _lenth = _arg_input.size();
	for (int i = 0;i < _lenth-1;i++)
	{
		_arg_input[i] = (1 - _coefficient)*_arg_input[i] + _coefficient * _arg_input[i + 1];
	}
	return _arg_input;
}

double get_rise_rate(double _x1,double _x2)
{
	if (_x1 == 0)
		return 0;
	return (_x2 - _x1) / _x1;
}

CAlgorithms::CAlgorithms(void)
{
}

CAlgorithms::~CAlgorithms(void)
{
}

//样例
void CAlgorithms::Example01(double _arg_input, double &_arg_output)
{
	double a = 9.35, b = 10.12;
	_arg_output = a * _arg_output + b;
}
void CAlgorithms::Example02(std::deque<double> _arg_input, std::deque<double> &_arg_output)
{
	//std::ofstream _file;
	//_file.open("dll_daily.txt");

	_arg_output.clear();
	for (int i = 0; i < _arg_input.size(); i++)
	{
		_arg_output.push_back(0);
		//_file << _arg_input[i] << " ";
	}
	int i = 0;
	if (_arg_input[0] > _arg_input[1])
		_arg_output[0] = 1;
	else
		_arg_output[0] = 0;

	for (i = 1; i < _arg_input.size() - 1; i++)
	{
		if (_arg_input[i] >= _arg_input[i + 1] && _arg_input[i] > _arg_input[i - 1])
			_arg_output[i] = 1;
		else
			_arg_output[i] = 0;
	}

	if (_arg_input[i] > _arg_input[i - 1])
		_arg_output[i] = 1;
	else
		_arg_output[i] = 0;
}
void CAlgorithms::Example03(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output)
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

	for (int i = 0; i < _arg_input[0].size() - 1; i++)
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
	}

	for(int i=0;i<_arg_input[0].size()-1;i++)
	{
		if (_arg_output[i] == 100) continue;
		if ((_arg_input[0][i] >= _arg_input[0][i + 1] && _arg_input[1][i] <= _arg_input[1][i + 1]) || (_arg_input[0][i] <= _arg_input[0][i + 1] && _arg_input[1][i] >= _arg_input[1][i + 1]))
		{
			_arg_output[i + 1] = 100;
		}
	}
}
void CAlgorithms::Example04(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output)
{
	_arg_output.clear();
	for(int i=1;i<_arg_input.size();i++)
	{
		std::deque<double> _v;
		for(int j=0;j<_arg_input[i].size();j++)
			_v.push_back(log(_arg_input[i][j]));
		_arg_output.push_back(_v);
	}
}

//冲击函数
void CAlgorithms::Impulse1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::Impulse2(std::deque<double> _arg_input, std::deque<double> &_arg_output)
{
	_arg_output.clear();
	int _lenth = _arg_input.size();
	if (_lenth < 2)return;
	double _start_to_up=_arg_input[0];
	if (_start_to_up == 0)_start_to_up = 0.001;
	for (int i = 0; i < _lenth; i++)
	{
		_arg_output.push_back(0);
	}
	for (int i = 1; i < _lenth; i++)
	{
		if (_arg_input[i] <= _arg_input[i - 1])
		{
			if ((_arg_input[i-1] - _start_to_up) / _start_to_up >= 0.1)
			{
				_arg_output[i-1]=1;
				_start_to_up = _arg_input[i];
				continue;
			}
			_start_to_up = _arg_input[i];
		}
	}
	if (_arg_input[_lenth - 1] >= _arg_input[_lenth - 2])
	{
		if ((_arg_input[_lenth - 1] - _start_to_up) / _start_to_up >= 0.1)
			_arg_output[_lenth - 1]=1;
	}
}

void CAlgorithms::Impulse3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output)
{
	_arg_output.clear();
	int i = 0;
	if (_arg_input[0] > _arg_input[1])
		_arg_output[0] = 1;
	else
		_arg_output[0] = 0;

	for (i = 1; i < _arg_input.size() - 1; i++)
	{
		if (_arg_input[i] >= _arg_input[i + 1] && _arg_input[i] > _arg_input[i - 1])
			_arg_output[i] = 1;
		else
			_arg_output[i] = 0;
	}

	if (_arg_input[i] > _arg_input[i - 1])
		_arg_output[i] = 1;
	else
		_arg_output[i] = 0;
}

void CAlgorithms::Impulse4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//高抛低吸
void CAlgorithms::TRADING_BY_PRICE1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::TRADING_BY_PRICE2(std::deque<double> _arg_input, std::deque<double> &_arg_output) { ; }

void CAlgorithms::TRADING_BY_PRICE3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input.size()!=3)
		return;

	_arg_output.clear();
	_arg_output.push_back(0);//第一个肯定没有标志

	int _buy_number = _arg_input[2][0];
	double _flag_rate = _arg_input[1][0];
	int _lenth = _arg_input[0].size();
	int _price_flag = 1;
	double _basic_price = _arg_input[0][0];

	//std::ofstream f;
	//f.open("dll_daily.txt");
	//f << _arg_input[1][0] << " " << _arg_input[2][0]<<" "<<_lenth<<std::endl;

	//for (int i = 1;i < _lenth;i++)f << _arg_input[0][i] << " ";

	for (int i = 1;i < _lenth;i++)
	{
		if (_arg_input[0][i] > _basic_price)//上升
		{
			if (_price_flag = -1)//之前在下降
			{
				_basic_price = _arg_input[0][i - 1];
				if (((_arg_input[0][i] - _basic_price) / _basic_price) >= _flag_rate)
					_arg_output.push_back(-_buy_number);
				else
					_arg_output.push_back(0);

				_price_flag = 1;
			}
			else//之前在上升，判断是否满足条件
			{
				//f << "进了1" << " ";
				if (((_arg_input[0][i] - _basic_price) / _basic_price) >= _flag_rate)
				{
					//f << "进了1-1" << " ";
					_arg_output.push_back(-_buy_number);
					_basic_price = _arg_input[0][i];
				}
				else
					_arg_output.push_back(0);
			}
		}
		else//下降
		{
			if (_price_flag == -1)
			{
				if ((-(_arg_input[0][i] - _basic_price) / _basic_price) >= _flag_rate)
				{
					_arg_output.push_back(_buy_number);
					_basic_price = _arg_input[0][i];
				}
				else
					_arg_output.push_back(0);
			}
			else//上升转下降
			{
				//f << "进了2" << " ";
				_basic_price = _arg_input[0][i - 1];
				if ((-(_arg_input[0][i] - _basic_price) / _basic_price) >= _flag_rate)
					_arg_output.push_back(_buy_number);
				else
					_arg_output.push_back(0);

				_price_flag = -1;
			}
		}
	}
	//f.close();
}

void CAlgorithms::TRADING_BY_PRICE4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//取波峰并延续
void CAlgorithms::GET_PEAKS1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::GET_PEAKS2(std::deque<double> _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input.size()<2)
		return;
	_arg_output.clear();
	double _temp;
	bool _equl_flag = false;
	_arg_output.push_back(_arg_input[0]);
	_arg_output.push_back(_arg_input[0]);
	_temp = _arg_input[0];
	for (int i = 2;i < _arg_input.size();i++)
	{
		if (_arg_input[i - 2] < _arg_input[i - 1] && _arg_input[i-1] > _arg_input[i])
			_temp = _arg_input[i - 1];
		if(_equl_flag&&_arg_input[i - 1] > _arg_input[i])
			_temp = _arg_input[i - 1];
		if (_arg_input[i - 1] == _arg_input[i]&& _arg_input[i - 2] < _arg_input[i - 1])
			_equl_flag = true;
		else
			_equl_flag = false;
		_arg_output.push_back(_temp);
	}
}

void CAlgorithms::GET_PEAKS3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input[0].size() < 2)
		return;
	if (_arg_input[1][0] < 0)
		_arg_input[1][0] = 0;
	if (_arg_input[1][0] > 1)
		_arg_input[1][0] = 1;
	_arg_output.clear();
	double _temp;
	bool _equl_flag = false;
	_arg_output.push_back(_arg_input[0][0]);
	_arg_output.push_back(_arg_input[0][0]);
	_temp = _arg_input[0][0];
	double _up_base= _arg_input[0][0];
	for (int i = 2;i < _arg_input[0].size();i++)
	{
		if (_arg_input[0][i - 2] < _arg_input[0][i - 1] && _arg_input[0][i - 1] > _arg_input[0][i]&&!IS_SHAKE(_arg_input[0][i - 1],_up_base, _arg_input[1][0]))
			_temp = _arg_input[0][i - 1];
		if (_equl_flag&&_arg_input[0][i - 1] > _arg_input[0][i])
			_temp = _arg_input[0][i - 1];
		if (_arg_input[0][i - 1] == _arg_input[0][i] && _arg_input[0][i - 2] < _arg_input[0][i - 1] && !IS_SHAKE(_arg_input[0][i - 1], _up_base, _arg_input[1][0]))
			_equl_flag = true;
		else
			_equl_flag = false;
		_arg_output.push_back(_temp);
		if (_arg_input[0][i - 1] > _arg_input[0][i])
			_up_base = _arg_input[0][i];
	}
}

void CAlgorithms::GET_PEAKS4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//取波谷并延续
void CAlgorithms::GET_VALLEYS1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::GET_VALLEYS2(std::deque<double> _arg_input, std::deque<double> &_arg_output)
{
	if (_arg_input.size() < 2)
		return;
	_arg_output.clear();
	double _temp;
	bool _equl_flag = false;
	_arg_output.push_back(_arg_input[0]);
	_arg_output.push_back(_arg_input[0]);
	_temp = _arg_input[0];
	for (int i = 2;i < _arg_input.size();i++)
	{
		if (_arg_input[i - 2] > _arg_input[i - 1] && _arg_input[i - 1] < _arg_input[i])
			_temp = _arg_input[i - 1];
		if (_equl_flag&&_arg_input[i - 1] < _arg_input[i])
			_temp = _arg_input[i - 1];
		if (_arg_input[i - 1] == _arg_input[i]&& _arg_input[i - 2] > _arg_input[i - 1])
			_equl_flag = true;
		else
			_equl_flag = false;
		_arg_output.push_back(_temp);
	}
}

void CAlgorithms::GET_VALLEYS3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output)
{
	if (_arg_input[0].size() < 2)
		return;
	if (_arg_input[1][0] < 0)
		_arg_input[1][0] = 0;
	if (_arg_input[1][0] > 1)
		_arg_input[1][0] = 1;
	_arg_output.clear();
	double _temp;
	bool _equl_flag = false;
	_arg_output.push_back(_arg_input[0][0]);
	_arg_output.push_back(_arg_input[0][0]);
	_temp = _arg_input[0][0];
	double _up_base = _arg_input[0][0];
	for (int i = 2;i < _arg_input[0].size();i++)
	{
		if (_arg_input[0][i - 2] > _arg_input[0][i - 1] && _arg_input[0][i - 1] < _arg_input[0][i] && !IS_SHAKE(_arg_input[0][i - 1], _up_base, _arg_input[1][0]))
			_temp = _arg_input[0][i - 1];
		if (_equl_flag&&_arg_input[0][i - 1] < _arg_input[0][i])
			_temp = _arg_input[0][i - 1];
		if (_arg_input[0][i - 1] == _arg_input[0][i] && _arg_input[0][i - 2] > _arg_input[0][i - 1] && !IS_SHAKE(_arg_input[0][i - 1], _up_base, _arg_input[1][0]))
			_equl_flag = true;
		else
			_equl_flag = false;
		_arg_output.push_back(_temp);
		if (_arg_input[0][i - 1] < _arg_input[0][i])
			_up_base = _arg_input[0][i];
	}
}

void CAlgorithms::GET_VALLEYS4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//取波峰上沿
void CAlgorithms::GET_PEAKS_LOWER1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::GET_PEAKS_LOWER2(std::deque<double> _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input.size() < 2)
		return;
	//std::ofstream f;
	//f.open("dll_daily.txt");
	int _lenth = _arg_input.size();
	bool _equl_flag=false;
	double _h_now = FLT_MAX;
	_arg_output.clear();
	_arg_output.push_back(_arg_input[0]);
	if (_arg_input[0] <= _arg_input[1])
		_arg_output.push_back(_arg_input[1]);
	else
		_arg_output.push_back(_arg_input[0]);
	double _h_value = _arg_output[1];
	double _up_base= _arg_input[1];
	for (int i = 2;i < _lenth;i++)
	{
		if (_arg_input[i - 2] < _arg_input[i - 1] && _arg_input[i - 1] > _arg_input[i]
			&&!IS_SHAKE(_up_base, _arg_input[i - 1]))
		{
			if (_h_now <= _arg_input[i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[i - 1];
			_h_now = _arg_input[i - 1];
		}
		if(_equl_flag&& _arg_input[i - 1] > _arg_input[i])
		{
			if (_h_now <= _arg_input[i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[i - 1];
			_h_now = _arg_input[i - 1];
			//f << _arg_input[i - 2] << " " << _arg_input[i - 1] << " " << _arg_input[i];
		}
		if (_arg_input[i - 1] == _arg_input[i] && _arg_input[i - 2] < _arg_input[i - 1] && !IS_SHAKE(_up_base, _arg_input[i]))
			_equl_flag = true;
		else
			_equl_flag = false;
		if (_arg_input[i] < _arg_input[i - 1])
		{
			_up_base = _arg_input[i];
		}
		_arg_output.push_back(_h_value);
	}
	//f.close();
}

void CAlgorithms::GET_PEAKS_LOWER3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input[0].size() < 2)
		return;
	if (_arg_input[1][0] < 0)
		_arg_input[1][0] = 0;
	if (_arg_input[1][0] > 1)
		_arg_input[1][0] = 1;
	//std::ofstream f;
	//f.open("dll_daily.txt");
	int _lenth = _arg_input[0].size();
	bool _equl_flag = false;
	double _h_now = FLT_MAX;
	_arg_output.clear();
	_arg_output.push_back(_arg_input[0][0]);
	if (_arg_input[0][0] <= _arg_input[0][1])
		_arg_output.push_back(_arg_input[0][1]);
	else
		_arg_output.push_back(_arg_input[0][0]);
	double _h_value = _arg_output[1];
	double _up_base = _arg_input[0][1];
	for (int i = 2;i < _lenth;i++)
	{
		if (_arg_input[0][i - 2] < _arg_input[0][i - 1] && _arg_input[0][i - 1] > _arg_input[0][i]
			&& !IS_SHAKE(_up_base, _arg_input[0][i - 1], _arg_input[1][0]))
		{
			if (_h_now <= _arg_input[0][i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[0][i - 1];
			_h_now = _arg_input[0][i - 1];
		}
		if (_equl_flag&& _arg_input[0][i - 1] > _arg_input[0][i])
		{
			if (_h_now <= _arg_input[0][i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[0][i - 1];
			_h_now = _arg_input[0][i - 1];
			//f << _arg_input[i - 2] << " " << _arg_input[i - 1] << " " << _arg_input[i];
		}
		if (_arg_input[0][i - 1] == _arg_input[0][i] && _arg_input[0][i - 2] < _arg_input[0][i - 1] && !IS_SHAKE(_up_base, _arg_input[0][i], _arg_input[1][0]))
			_equl_flag = true;
		else
			_equl_flag = false;
		if (_arg_input[0][i] < _arg_input[0][i - 1])
		{
			_up_base = _arg_input[0][i];
		}
		_arg_output.push_back(_h_value);
	}
	//f.close();
}

void CAlgorithms::GET_PEAKS_LOWER4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//取波谷上沿
void CAlgorithms::GET_VALLEYS_TOP1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::GET_VALLEYS_TOP2(std::deque<double> _arg_input, std::deque<double> &_arg_output)
{
	if (_arg_input.size() < 2)
		return;
	//std::ofstream f;
	//f.open("dll_daily.txt");
	int _lenth = _arg_input.size();
	bool _equl_flag = false;
	double _h_now = FLT_MAX;
	_arg_output.clear();
	_arg_output.push_back(_arg_input[0]);
	if (_arg_input[0] >= _arg_input[1])
		_arg_output.push_back(_arg_input[1]);
	else
		_arg_output.push_back(_arg_input[0]);
	double _h_value = _arg_output[1];
	double _up_base = _arg_input[1];
	for (int i = 2;i < _lenth;i++)
	{
		if (_arg_input[i - 2] > _arg_input[i - 1] && _arg_input[i - 1] < _arg_input[i]
			&& !IS_SHAKE(_up_base, _arg_input[i - 1]))
		{
			if (_h_now >= _arg_input[i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[i - 1];
			_h_now = _arg_input[i - 1];
		}
		if (_equl_flag&& _arg_input[i - 1] < _arg_input[i])
		{
			if (_h_now >= _arg_input[i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[i - 1];
			_h_now = _arg_input[i - 1];
			//f << _arg_input[i - 2] << " " << _arg_input[i - 1] << " " << _arg_input[i];
		}
		if (_arg_input[i - 1] == _arg_input[i] && _arg_input[i - 2] > _arg_input[i - 1] && !IS_SHAKE(_up_base, _arg_input[i]))
			_equl_flag = true;
		else
			_equl_flag = false;
		if (_arg_input[i] > _arg_input[i - 1])
		{
			_up_base = _arg_input[i];
		}
		_arg_output.push_back(_h_value);
	}
	//f.close();
}

void CAlgorithms::GET_VALLEYS_TOP3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output) 
{
	if (_arg_input[0].size() < 2)
		return;
	if (_arg_input[1][0] < 0)
		_arg_input[1][0] = 0;
	if (_arg_input[1][0] > 1)
		_arg_input[1][0] = 1;
	//std::ofstream f;
	//f.open("dll_daily.txt");
	
	int _lenth = _arg_input[0].size();
	bool _equl_flag = false;
	double _h_now = -FLT_MAX;
	_arg_output.clear();
	_arg_output.push_back(_arg_input[0][0]);
	if (_arg_input[0][0] >= _arg_input[0][1])
		_arg_output.push_back(_arg_input[0][1]);
	else
		_arg_output.push_back(_arg_input[0][0]);
	double _h_value = _arg_output[1];
	double _up_base = _arg_input[0][1];
	for (int i = 2;i < _lenth;i++)
	{
		if (_arg_input[0][i - 2] > _arg_input[0][i - 1] && _arg_input[0][i - 1] < _arg_input[0][i]
			&& !IS_SHAKE(_up_base, _arg_input[0][i - 1], _arg_input[1][0]))
		{
			if (_h_now >= _arg_input[0][i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[0][i - 1];
			_h_now = _arg_input[0][i - 1];
		}
		if (_equl_flag&& _arg_input[0][i - 1] < _arg_input[0][i])
		{
			if (_h_now >= _arg_input[0][i - 1])
				_h_value = _h_now;
			else
				_h_value = _arg_input[0][i - 1];
			_h_now = _arg_input[0][i - 1];
			//f << _arg_input[i - 2] << " " << _arg_input[i - 1] << " " << _arg_input[i];
		}
		if (_arg_input[0][i - 1] == _arg_input[0][i] && _arg_input[0][i - 2] > _arg_input[0][i - 1] && !IS_SHAKE(_up_base, _arg_input[0][i], _arg_input[1][0]))
			_equl_flag = true;
		else
			_equl_flag = false;
		if (_arg_input[0][i] > _arg_input[0][i - 1])
		{
			_up_base = _arg_input[0][i];
		}
		_arg_output.push_back(_h_value);
	}
	//f.close();
}

void CAlgorithms::GET_VALLEYS_TOP4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

//股票热度判断，近_n个工作日的增长率
void CAlgorithms::GET_RISE_RATE_BY_TIME1(double _arg_input, double &_arg_output) { ; }

void CAlgorithms::GET_RISE_RATE_BY_TIME2(std::deque<double> _arg_input, std::deque<double> &_arg_output) { ; }

void CAlgorithms::GET_RISE_RATE_BY_TIME3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output)
{
	if (_arg_input.size() != 2)
		return;
	if (_arg_input[0].size() < _arg_input[1][0])
		return;
	int _n = _arg_input[1][0];
	_arg_output.push_back(0);
	for (int i = 1;i <= _n;i++)
	{
		_arg_output.push_back(get_rise_rate(_arg_input[0][i], _arg_input[0][0]));
	}
	for (int i = _n+1;i < _arg_input[0].size();i++)
	{
		_arg_output.push_back(get_rise_rate(_arg_input[0][i], _arg_input[0][i - _n]));
	}
}

void CAlgorithms::GET_RISE_RATE_BY_TIME4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output) { ; }

void CAlgorithms::MA(std::deque<double> _arg_input,int _ma_period ,std::deque<double> &_arg_output)
{
	int i;
	double _sum = 0;
	
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