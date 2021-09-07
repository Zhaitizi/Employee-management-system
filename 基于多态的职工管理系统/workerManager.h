#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream> //�������������ͷ�ļ�
using namespace std; //ʹ�ñ�׼�����ռ�

#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:
	
	WorkerManager();  //���캯��
	
	void Show_Manu(); //չʾ�˵�

	void Exit_System();	//�˳�ϵͳ

	void Add_Emp();  //���ְ��

	void Save(); //�����ļ�

	int get_EmpNum();	//ͳ���ļ��е�����

	void init_Emp();//��ʼ��Ա��

	void Show_Emp(); //��ʾԱ��

	void Del_Emp();//ɾ��ְ��

	int IsExist(int id); //�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1

	void Mod_Emp();//�޸�ְ��

	void Find_Emp();//����ְ��

	void Sort_Emp();//��������

	void Clean_File();//����ļ�

	~WorkerManager();  //��������

	int m_EmpNum; //��¼�ļ��е���������

	bool m_FileIsEmpty; //�ж��ļ��Ƿ�Ϊ�� �ı�־

	Worker** m_EmpArray;	//��¼ְ�������ָ��
};
