// algo_plugin.h : algo_plugin DLL 
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
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


// ��ʼ������������к��������б�ļ���
// Intialize the map of the name of all functions.
bool dynamic_init();

// ���ǵ��������ҵ����ݵĺ���
// This function has single input argument with single value, the same with output argument.
void dynamic_func_a(std::string _name,float _arg_input, float &_arg_output);

// ����һ��������������������ʽ���ݽ����ĺ������༴һά��������
// This is a function with single input argument and multiple value.
void dynamic_func_b(std::string _name,std::deque<float> _arg_input, std::deque<float> &_arg_output);

//���Ƕ�������������ÿ�����������鸳ֵ����ʽ���ݽ���������ά���麯��,�������Ϊһά����
//This function contains two dimensional input and  single dimension output arguments.
void dynamic_func_c(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);

//���Ƕ�������������ÿ�����������鸳ֵ����ʽ���ݽ���������ά���麯��
//This function contains two dimensional input and output arguments.
void dynamic_func_d(std::string _name, std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);