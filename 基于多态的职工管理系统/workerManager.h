#pragma once //防止头文件重复包含
#include<iostream> //包含输入输出流头文件
using namespace std; //使用标准命名空间

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:
	
	WorkerManager();  //构造函数
	
	void Show_Manu(); //展示菜单

	void Exit_System();	//退出系统

	void Add_Emp();  //添加职工

	void Save(); //保存文件

	int get_EmpNum();	//统计文件中的人数

	void init_Emp();//初始化员工

	void Show_Emp(); //显示员工

	void Del_Emp();//删除职工

	int IsExist(int id); //判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1

	void Mod_Emp();//修改职工

	void Find_Emp();//查找职工

	void Sort_Emp();//按编排序

	void Clean_File();//清空文件

	~WorkerManager();  //析构函数

	int m_EmpNum; //记录文件中的人数个数

	bool m_FileIsEmpty; //判断文件是否为空 的标志

	Worker** m_EmpArray;	//记录职工数组的指针
};
