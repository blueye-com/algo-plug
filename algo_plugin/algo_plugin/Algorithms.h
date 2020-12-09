#pragma once

class CAlgorithms
{
public:
	CAlgorithms(void);
	~CAlgorithms(void);

	static void Example01(float _arg_input, float &_arg_output);
	static void Example02(std::deque<float> _arg_input, std::deque<float> &_arg_output);
	static void Example03(std::deque< std::deque<float> > _arg_input,  std::deque<float> &_arg_output);
	static void Example04(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);


	static void Example11(float _arg_input, float &_arg_output);
	static void Example12(std::deque<float> _arg_input, std::deque<float> &_arg_output);
	static void Example13(std::deque< std::deque<float> > _arg_input,  std::deque<float> &_arg_output);
	static void Example14(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);

	static void MA(std::deque<float> _arg_input,int _ma_period ,std::deque<float> &_arg_output);

	enum{DRAWSTYLE_BUY = 23,DRAWSTYLE_SELL,DRAWSTYLE_BUY_SHORT,DRAWSTYLE_SELL_SHORT};
};


typedef struct
{
	float high;
	float low;
	bool is_combined;
}SINGLE_DATA;