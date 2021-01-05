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

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::Example11;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::Example12;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::Example13;
	g_map_functions.insert(std::make_pair("EXAMPLE1",_func_list));
	
	// To do, add more functions in the following ......
	//...

	return true;
}

void dynamic_func_a(std::string _name,float _arg_input, float &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_a_(_arg_input,_arg_output);
}

void dynamic_func_b(std::string _name,std::deque<float> _arg_input, std::deque<float> &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_b_(_arg_input,_arg_output);
}

void dynamic_func_c(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_c_(_arg_input,_arg_output);
}

void dynamic_func_d(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output)
{
	if(g_map_functions.count(_name) > 0)
		g_map_functions[_name].dynamic_func_d_(_arg_input,_arg_output);
}