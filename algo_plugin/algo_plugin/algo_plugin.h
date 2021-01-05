// algo_plugin.h : algo_plugin DLL 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		

/*
 * The project provides a algorithmic-box and interfaces which are associated with "BLUEYE" software.
 * All of interfaces functions need to be written according to this project template. In addition, the project offers 
 * examples for developer.
 * Author: Rom
 * Date: 2019.08.15.
 */


// Calgo_pluginApp

class Calgo_pluginApp : public CWinApp
{
public:
	Calgo_pluginApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

typedef bool	(*i_init)();
typedef void	(*i_dynamic_func_a)(float _arg_input, float &_arg_output);
typedef void	(*i_dynamic_func_b)(std::deque<float> _arg_input, std::deque<float> &_arg_output);
typedef void	(*i_dynamic_func_c)(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);
typedef void	(*i_dynamic_func_d)(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);


typedef struct  
{
	i_dynamic_func_a dynamic_func_a_;
	i_dynamic_func_b dynamic_func_b_;
	i_dynamic_func_c dynamic_func_c_;
	i_dynamic_func_d dynamic_func_d_;
}tag_FUNC_LIST;


// 初始化，在这里进行函数名称列表的加载
// Intialize the map of the name of all functions.
bool dynamic_init();

// 这是单参数并且单数据的函数
// This function has single input argument with single value, the same with output argument.
void dynamic_func_a(std::string _name,float _arg_input, float &_arg_output);

// 这是一个输入参数且以数组的形式传递进来的函数，亦即一维参数函数
// This is a function with single input argument and multiple value.
void dynamic_func_b(std::string _name,std::deque<float> _arg_input, std::deque<float> &_arg_output);

//这是多个输入参数，且每个参数以数组赋值的形式传递进来，即二维数组函数,输出参数为一维数组
//This function contains two dimensional input and  single dimension output arguments.
void dynamic_func_c(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);

//这是多个输入参数，且每个参数以数组赋值的形式传递进来，即二维数组函数
//This function contains two dimensional input and output arguments.
void dynamic_func_d(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);