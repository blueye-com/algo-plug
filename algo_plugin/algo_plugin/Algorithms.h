#pragma once

class CAlgorithms
{
public:
	CAlgorithms(void);
	~CAlgorithms(void);

	static void Example01(double _arg_input, double &_arg_output);
	static void Example02(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void Example03(std::deque< std::deque<double> > _arg_input,  std::deque<double> &_arg_output);
	static void Example04(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);


	static void Impulse1(double _arg_input, double &_arg_output);
	static void Impulse2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void Impulse3(std::deque< std::deque<double> > _arg_input,  std::deque<double> &_arg_output);
	static void Impulse4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void TRADING_BY_PRICE1(double _arg_input, double &_arg_output);
	static void TRADING_BY_PRICE2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void TRADING_BY_PRICE3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void TRADING_BY_PRICE4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void GET_PEAKS1(double _arg_input, double &_arg_output);
	static void GET_PEAKS2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void GET_PEAKS3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void GET_PEAKS4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void GET_VALLEYS1(double _arg_input, double &_arg_output);
	static void GET_VALLEYS2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void GET_VALLEYS3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void GET_VALLEYS4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void GET_PEAKS_LOWER1(double _arg_input, double &_arg_output);
	static void GET_PEAKS_LOWER2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void GET_PEAKS_LOWER3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void GET_PEAKS_LOWER4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void GET_VALLEYS_TOP1(double _arg_input, double &_arg_output);
	static void GET_VALLEYS_TOP2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void GET_VALLEYS_TOP3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void GET_VALLEYS_TOP4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void GET_RISE_RATE_BY_TIME1(double _arg_input, double &_arg_output);
	static void GET_RISE_RATE_BY_TIME2(std::deque<double> _arg_input, std::deque<double> &_arg_output);
	static void GET_RISE_RATE_BY_TIME3(std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output);
	static void GET_RISE_RATE_BY_TIME4(std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output);

	static void MA(std::deque<double> _arg_input,int _ma_period ,std::deque<double> &_arg_output);

	enum{DRAWSTYLE_BUY = 23,DRAWSTYLE_SELL,DRAWSTYLE_BUY_SHORT,DRAWSTYLE_SELL_SHORT};
};


typedef struct
{
	double high;
	double low;
	bool is_combined;
}SINGLE_DATA;

bool IS_SHAKE(double _x1, double _x2, double _rate = 0.02);//计算（x1-x2）/x1的绝对值

std::deque<double> smoothing(std::deque<double> _arg_input, double _coefficient);//根据相邻下一个数值进行曲线平滑运算

double get_rise_rate(double _x1, double _x2);//两条k线的涨幅