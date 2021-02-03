// algo_plugin.cpp : 
//

#include "stdafx.h"

#include "algo_plugin.h"

#include "Algorithms.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// Calgo_pluginApp

BEGIN_MESSAGE_MAP(Calgo_pluginApp, CWinApp)
END_MESSAGE_MAP()



Calgo_pluginApp::Calgo_pluginApp()
{
	// TODO: 
}

Calgo_pluginApp theApp;


// Calgo_pluginApp Initialization

BOOL Calgo_pluginApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

std::map<std::string, tag_FUNC_LIST> g_map_functions;

bool dynamic_init()
{
	tag_FUNC_LIST _func_list;
	
	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::Example01;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::Example02;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::Example03;
	g_map_functions.insert(std::make_pair("EXAMPLE0",_func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::Impulse1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::Impulse2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::Impulse3;
	g_map_functions.insert(std::make_pair("IMPULSE",_func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::TRADING_BY_PRICE1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::TRADING_BY_PRICE2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::TRADING_BY_PRICE3;
	g_map_functions.insert(std::make_pair("TRADING_BY_PRICE", _func_list));
	
	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::GET_PEAKS1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::GET_PEAKS2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::GET_PEAKS3;
	g_map_functions.insert(std::make_pair("GET_PEAKS", _func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::GET_VALLEYS1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::GET_VALLEYS2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::GET_VALLEYS3;
	g_map_functions.insert(std::make_pair("GET_VALLEYS", _func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::GET_PEAKS_LOWER1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::GET_PEAKS_LOWER2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::GET_PEAKS_LOWER3;
	g_map_functions.insert(std::make_pair("GET_PEAKS_LOWER", _func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::GET_VALLEYS_TOP1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::GET_VALLEYS_TOP2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::GET_VALLEYS_TOP3;
	g_map_functions.insert(std::make_pair("GET_VALLEYS_TOP", _func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::GET_RISE_RATE_BY_TIME1;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::GET_RISE_RATE_BY_TIME2;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::GET_RISE_RATE_BY_TIME3;
	g_map_functions.insert(std::make_pair("GET_RISE_RATE_BY_TIME", _func_list));

	// To do, add more functions in the following ......
	//...

	return true;
}

void dynamic_func_a(std::string _name,double _arg_input, double &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_a_(_arg_input,_arg_output);
}

void dynamic_func_b(std::string _name,std::deque<double> _arg_input, std::deque<double> &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_b_(_arg_input,_arg_output);
}

void dynamic_func_c(std::string _name, std::deque< std::deque<double> > _arg_input, std::deque<double> &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_c_(_arg_input,_arg_output);
}

void dynamic_func_d(std::string _name, std::deque< std::deque<double> > _arg_input, std::deque< std::deque<double> > &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_d_(_arg_input,_arg_output);
}