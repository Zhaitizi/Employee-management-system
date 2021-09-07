#include "workerManager.h"

WorkerManager::WorkerManager() {
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�

	if (!ifs.is_open()) {
		//���Դ��� cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.�ļ��� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//�ļ�Ϊ��
		//���Դ��� cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3.�ļ����ڣ��������ݲ�Ϊ��
	int num = this->get_EmpNum();
	//���Դ��� cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();

	////���Դ���
	//for (int i = 0; i < this->m_EmpNum; i++) {
	//	cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id
	//		<< "������" << this->m_EmpArray[i]->m_Name
	//		<< "��λ��ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}

void WorkerManager::Show_Manu() {
	cout << "*******************************************" << endl;
	cout << "********   ��ӭʹ��ְ������ϵͳ!   ********" << endl;
	cout << "***********   0.�˳��������   ************" << endl;
	cout << "***********   1.����ְ����Ϣ   ************" << endl;
	cout << "***********   2.��ʾְ����Ϣ   ************" << endl;
	cout << "***********   3.ɾ����ְְ��   ************" << endl;
	cout << "***********   4.�޸�ְ����Ϣ   ************" << endl;
	cout << "***********   5.����ְ����Ϣ   ************" << endl;
	cout << "***********   6.���ձ������   ************" << endl;
	cout << "***********   7.��������ĵ�   ************" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
}

void WorkerManager::Exit_System() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ��������" << endl;

	int addNum = 0; //�����û�����������
	cin >> addNum;

	if (addNum > 0) {
		//���
		//��������¿ռ�Ĵ�С
		int newSize = this->m_EmpNum + addNum; //�¿ռ����� = ԭ����¼���� + ��������

		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++) {
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��

			while (1) {
				cout << "������� " << i + 1 << " ����ְ���ı�ţ�" << endl;
				cin >> id;
				if (this->IsExist(id) == -1) {
					break;
				}
				else {
					cout << "�ñ���Ѵ��ڣ�����������" << endl;
				}
			}

			cout << "������� " << i + 1 << " ����ְ����������" << endl;
			cin >> name;

			while (1) {
				cout << "��ѡ���ְ���ĸ�λ��" << endl;
				cout << "1.��ͨԱ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
				cin >> dSelect;

				if (dSelect == 1 || dSelect == 2 || dSelect == 3) {
					break;
				}
				else {
					cout << "�޸ø�λ������������" << endl;
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

			//��������ְ��ָ�룬 ���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ���� " << addNum << " ����ְ��!" << endl;

		//�ɹ���Ӻ󱣴浽�ļ���
		this->Save();
	}
	else {
		cout << "������������������" << endl;
	}
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}  

//�����ļ�
void WorkerManager::Save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//������ķ�ʽ���ļ� --д�ļ�

	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << "  "
			<< this->m_EmpArray[i]->m_Name << "  "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}

//ͳ���ļ��е�����
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ� ��

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;//ͳ����������
	}

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;

		if (dId == 1) { //��ְͨ��
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) { //����
			worker = new Manager(id, name, dId);
		}
		if (dId == 3) { //�ϰ�
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}

//��ʾԱ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//ɾ��ְ��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	else {
		//����ְ�����ɾ��
		int id = 0;
		cout << "������Ҫɾ����ְ����ţ�" << endl;
		cin >> id;
		
		int flag = this->IsExist(id);

		if (flag != -1) {//˵��ְ�����ڣ�����Ҫɾ����indexλ���ϵ�ְ��
			for (int i = flag; i < this->m_EmpNum - 1; i++) {
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������еļ�¼��Ա����
			//ͬ�����µ��ļ���
			this->Save();

			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
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

//�޸�ְ��
void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1) {
			//�鵽��Ա������ʼ�޸�Ա����Ϣ

			delete this->m_EmpArray[ret];

			int newid = 0;
			string newname = "";
			int dSelect = 0;

			cout << "�鵽���Ϊ��" << id << " ��ְ�����������µ�ְ����ţ�" << endl;
			cin >> newid;

			cout << "��������������" << endl;
			cin >> newname;

			while (1) {
				cout << "�������¸�λ��" << endl;
				cout << "1.��ͨԱ��" << endl;
				cout << "2.����" << endl;
				cout << "3.�ϰ�" << endl;
				cin >> dSelect;

				if (dSelect == 1 || dSelect == 2 || dSelect == 3) {
					break;
				}
				else {
					cout << "�޸ø�λ������������" << endl;
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

			//�������ݵ�������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�!" << endl;

			//���浽�ļ���
			this->Save();
		}
		else {
			cout << "���޴��ˣ��޸�ʧ��" << endl;
		}
	}
	//�����������
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	else {

		while (1) 
		{

			cout << "��������ҵķ�ʽ��" << endl;
			cout << "1.��ְ����Ų���" << endl;
			cout << "2.����������" << endl;

			int select = 0;
			cin >> select;

			if (select == 1)//��ְ����Ų���
			{
				int id;
				cout << "���������ְ���ı�ţ�" << endl;
				cin >> id;

				int ret = IsExist(id);
				if (ret != -1) {
					cout << "���ҳɹ�!��ְ������Ϣ���£�" << endl;
					this->m_EmpArray[ret]->showInfo();
				}
				else {
					cout << "����ʧ�ܣ����޴���" << endl;
				}
				break;
			}
			else if (select == 2)//��ְ��������
			{
				string name;
				cout << "���������ְ����������" << endl;
				cin >> name;

				bool flag = false;//���ҵ��ı�־
				for (int i = 0; i < this->m_EmpNum; i++)
				{
					if (this->m_EmpArray[i]->m_Name == name)
					{
						cout << "���ҳɹ�!��ְ������Ϣ���£�" << endl;
						this->m_EmpArray[i]->showInfo();
						flag = true;
					}
				}
				if (flag == false)
				{
					cout << "����ʧ�ܣ����޴���" << endl;
				}
				break;
			}
			else
			{
				cout << "�Ƿ����룬���飡" << endl;
			}
		}
	}
	//�����������
	system("pause");
	system("cls");

}

//��������
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
		//�����������
		system("pause");
		system("cls");
	}
	else {

		while (1) {
			cout << "��ѡ������ʽ��" << endl;
			cout << "1.����ְ���Ž�����������" << endl;
			cout << "2.����ְ���Ž��н�������" << endl;

			int select = 0;
			cin >> select;

			if (select == 1 || select == 2) {
				for (int i = 0; i < m_EmpNum; i++) {
					int minOrMax = i;
					for (int j = i + 1; j < m_EmpNum; j++) {
						if (select == 1) {													//����
							if (m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id) {
								minOrMax = j;
							}
						}
						else if (select == 2)												//����
						{
							if (m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id) {
								minOrMax = j;
							}
						}
					}
					//�ж�һ��ʼ�϶� ��Сֵ�������ֵ �ǲ��Ǽ������Сֵ�������ֵ��������ǣ���������
					if (i != minOrMax) {
						Worker* temp = this->m_EmpArray[i];
						this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
						this->m_EmpArray[minOrMax] = temp;
					}
						
				}
				cout << "����ɹ��������Ľ�����£�" << endl;
				this->Save(); //�����Ľ�����浽�ļ���
				this->Show_Emp(); //չʾ����ְ��

				break;
			
			}
			else {
				cout << "������Ϸ�ֵ��" << endl;
			}
		}
	}
}

//����ļ�
void WorkerManager::Clean_File()
{

	while (1) {
		cout << "ȷ����գ�" << endl;
		cout << "1.ȷ��" << endl;
		cout << "2.����" << endl;

		int select = 0;
		cin >> select;
		if (select == 1 || select == 2) {
			if (select == 1) {
				//��ģʽios::trunc �������ɾ���ļ������´���
				ofstream ofs(FILENAME, ios::trunc);
				ofs.close();

				if (this->m_EmpArray != NULL) {
					for (int i = 0; i < this->m_EmpNum; i++) {
						if (this->m_EmpArray[i] != NULL) {
							delete this->m_EmpArray[i];
						}
					}
					//ɾ����������ָ��
					this->m_EmpNum = 0;
					delete[] this->m_EmpArray;
					this->m_EmpArray = NULL;
					this->m_FileIsEmpty = true;
				}
				cout << "��ճɹ�!" << endl;
				//�����������
				system("pause");
				system("cls");
			}
			else {
				//�����������
				system("pause");
				system("cls");
			}
			break;
		}
		else {
			cout << "�Ƿ����룬���飡" << endl;
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