#include "workerManager.h"

WorkerManager::WorkerManager() {
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	if (!ifs.is_open()) {
		//测试代码 cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//文件为空
		//测试代码 cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3.文件存在，并且数据不为空
	int num = this->get_EmpNum();
	//测试代码 cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();

	////测试代码
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << "职工编号：" << this->m_EmpArray[i]->m_Id
	//		<< "姓名：" << this->m_EmpArray[i]->m_Name
	//		<< "岗位编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

void WorkerManager::Show_Manu() {
	cout << "*******************************************" << endl;
	cout << "********   欢迎使用职工管理系统!   ********" << endl;
	cout << "***********   0.退出管理程序   ************" << endl;
	cout << "***********   1.增加职工信息   ************" << endl;
	cout << "***********   2.显示职工信息   ************" << endl;
	cout << "***********   3.删除离职职工   ************" << endl;
	cout << "***********   4.修改职工信息   ************" << endl;
	cout << "***********   5.查找职工信息   ************" << endl;
	cout << "***********   6.按照编号排序   ************" << endl;
	cout << "***********   7.清空所有文档   ************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

void WorkerManager::Exit_System() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量：" << endl;

	int addNum = 0; //保存用户的输入数量
	cin >> addNum;

	if (addNum > 0) {
		//添加
		//计算添加新空间的大小
		int newSize = this->m_EmpNum + addNum; //新空间人数 = 原来记录人数 + 新增人数

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			while (1) {
				cout << "请输入第 " << i + 1 << " 个新职工的编号：" << endl;
				cin >> id;
				if (this->IsExist(id) == -1) {
					break;
				}
				else {
					cout << "该编号已存在，请重新输入" << endl;
				}
			}

			cout << "请输入第 " << i + 1 << " 个新职工的姓名：" << endl;
			cin >> name;

			while (1) {
				cout << "请选择该职工的岗位：" << endl;
				cout << "1.普通员工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
				cin >> dSelect;

				if (dSelect == 1 || dSelect == 2 || dSelect == 3) {
					break;
				}
				else {
					cout << "无该岗位，请重新输入" << endl;
				}
			}

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工指针， 保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加 " << addNum << " 名新职工!" << endl;

		//成功添加后保存到文件中
		this->Save();
	}
	else {
		cout << "输入有误，请重新输入" << endl;
	}
	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");
}  

//保存文件
void WorkerManager::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件 --写文件

	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}

//统计文件中的人数
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;//统计人数变量
	}

	return num;
}

//初始化员工
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;

		if (dId == 1) { //普通职工
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) { //经理
			worker = new Manager(id, name, dId);
		}
		if (dId == 3) { //老板
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

//显示员工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//删除职工
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
	}
	else {
		//按照职工编号删除
		int id = 0;
		cout << "请输入要删除的职工编号：" << endl;
		cin >> id;
		
		int flag = this->IsExist(id);

		if (flag != -1) {//说明职工存在，并且要删除掉index位置上的职工
			for (int i = flag; i < this->m_EmpNum - 1; i++) {
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中的记录人员个数
			//同步更新到文件中
			this->Save();

			cout << "删除成功！" << endl;
		}
		else {
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int flag = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			flag = i;
			break;
		}
	}
	return flag;
}

//修改职工
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
	}
	else {
		cout << "请输入需要修改的职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) {
			//查到该员工，开始修改员工信息

			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "查到编号为：" << id << " 的职工，请输入新的职工编号：" << endl;
			cin >> newid;

			cout << "请输入新姓名：" << endl;
			cin >> newname;

			while (1) {
				cout << "请输入新岗位：" << endl;
				cout << "1.普通员工" << endl;
				cout << "2.经理" << endl;
				cout << "3.老板" << endl;
				cin >> dSelect;

				if (dSelect == 1 || dSelect == 2 || dSelect == 3) {
					break;
				}
				else {
					cout << "无该岗位，请重新输入" << endl;
				}
			}

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(newid, newname, 1);
				break;
			case 2:
				worker = new Manager(newid, newname, 2);
				break;
			case 3:
				worker = new Boss(newid, newname, 3);
				break;
			default:
				break;
			}

			//更新数据到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功!" << endl;

			//保存到文件中
			this->Save();
		}
		else {
			cout << "查无此人，修改失败" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
	}
	else {

		while (1) 
		{

			cout << "请输入查找的方式：" << endl;
			cout << "1.按职工编号查找" << endl;
			cout << "2.按姓名查找" << endl;

			int select = 0;
			cin >> select;

			if (select == 1)//按职工编号查找
			{
				int id;
				cout << "请输入查找职工的编号：" << endl;
				cin >> id;

				int ret = IsExist(id);
				if (ret != -1) {
					cout << "查找成功!该职工的信息如下：" << endl;
					this->m_EmpArray[ret]->showInfo();
				}
				else {
					cout << "查找失败，查无此人" << endl;
				}
				break;
			}
			else if (select == 2)//按职工姓名查
			{
				string name;
				cout << "请输入查找职工的姓名：" << endl;
				cin >> name;

				bool flag = false;//查找到的标志
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Name == name)
					{
						cout << "查找成功!该职工的信息如下：" << endl;
						this->m_EmpArray[i]->showInfo();
						flag = true;
					}
				}
				if (flag == false)
				{
					cout << "查找失败，查无此人" << endl;
				}
				break;
			}
			else
			{
				cout << "非法输入，请检查！" << endl;
			}
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");

}

//按编排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者文件为空！" << endl;
		//按任意键清屏
		system("pause");
		system("cls");
	}
	else {

		while (1) {
			cout << "请选择排序方式：" << endl;
			cout << "1.按照职工号进行升序排序" << endl;
			cout << "2.按照职工号进行降序排序" << endl;

			int select = 0;
			cin >> select;

			if (select == 1 || select == 2) {
				for (int i = 0; i < m_EmpNum; i++) {
					int minOrMax = i;
					for (int j = i + 1; j < m_EmpNum; j++) {
						if (select == 1) {													//升序
							if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
								minOrMax = j;
							}
						}
						else if (select == 2)												//降序
						{
							if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
								minOrMax = j;
							}
						}
					}
					//判断一开始认定 最小值或者最大值 是不是计算的最小值或者最大值，如果不是，交换数据
					if (i != minOrMax) {
						Worker* temp = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
						this->m_EmpArray[minOrMax] = temp;
					}
						
				}
				cout << "排序成功！排序后的结果如下：" << endl;
				this->Save(); //排序后的结果保存到文件中
				this->Show_Emp(); //展示所有职工

				break;
			
			}
			else {
				cout << "请输入合法值！" << endl;
			}
		}
	}
}

//清空文件
void WorkerManager::Clean_File()
{

	while (1) {
		cout << "确认清空？" << endl;
		cout << "1.确认" << endl;
		cout << "2.返回" << endl;

		int select = 0;
		cin >> select;
		if (select == 1 || select == 2) {
			if (select == 1) {
				//打开模式ios::trunc 如果存在删除文件并重新创建
				ofstream ofs(FILENAME, ios::trunc);
				ofs.close();

				if (this->m_EmpArray != NULL) {
					for (int i = 0; i < this->m_EmpNum; i++) {
						if (this->m_EmpArray[i] != NULL) {
							delete this->m_EmpArray[i];
						}
					}
					//删除堆区数组指针
					this->m_EmpNum = 0;
					delete[] this->m_EmpArray;
					this->m_EmpArray = NULL;
					this->m_FileIsEmpty = true;
				}
				cout << "清空成功!" << endl;
				//按任意键清屏
				system("pause");
				system("cls");
			}
			else {
				//按任意键清屏
				system("pause");
				system("cls");
			}
			break;
		}
		else {
			cout << "非法输入，请检查！" << endl;
		}
	}

}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != NULL) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			if (this->m_EmpArray[i] != NULL) {
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}