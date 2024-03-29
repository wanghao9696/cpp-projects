#include"workerManger.h"
#include"employee.h"
#include"manger.h"
#include"boss.h"


WorkerManger::WorkerManger()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    // 文件不存在的情况
    if(!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        this->m_EmpNum = 0; // 初始化人数
        this->m_FileIsEmpty = true; // 初始化文件为空的标志
        this->m_EmpArray = NULL; // 初始化数组
        ifs.close(); // 关闭文件
        return;
    }

    // 文件存在，并且没有记录
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        cout << "文件为空" << endl;
        cout << "文件不存在！" << endl;
        this->m_EmpNum = 0; // 初始化人数
        this->m_FileIsEmpty = true; // 初始化文件为空的标志
        this->m_EmpArray = NULL; // 初始化数组
        ifs.close(); // 关闭文件
        return;
    }

    int num = this->get_EmpNum();
    // cout << "职工个数为：" << num << endl;
    this->m_EmpNum = num;

    // 根据职工数创建数组
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    // 初始化职工
    init_Emp();

    // 测试
    // for(int i=0; i<m_EmpNum; i++)
    // {
    //     cout << "职工号：" << this->m_EmpArray[i]->m_Id
    //         << "职工姓名：" << this->m_EmpArray[i]->m_Name
    //         << "部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
    // }
}

WorkerManger::~WorkerManger()
{
    if(this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
    }
}

// 显示菜单函数实现
void WorkerManger::show_Menu()
{
    cout << "***********************************" << endl;
    cout << "******  欢迎使用职工管理系统  *********" << endl;
    cout << "********  0.退出管理程序  ***********" << endl;
    cout << "********  1.增加职工信息  ***********" << endl;
    cout << "********  2.显示职工信息  ***********" << endl;
    cout << "********  3.删除职工信息  ***********" << endl;
    cout << "********  4.修改职工信息  ***********" << endl;
    cout << "********  5.查找职工信息  ***********" << endl;
    cout << "********  6.按照编号排序  ***********" << endl;
    cout << "********  7.清空所有文档  ***********" << endl;
    cout << "***********************************" << endl;
    cout << endl;
}

// 退出系统函数实现
void WorkerManger::exitSystem()
{
    cout << "欢迎下次使用！" << endl;
    exit(0);
}

// 增加职工函数实现
void WorkerManger::Add_Emp()
{
    cout << "请输入增加职工的数量：" << endl;

    int addNum = 0;
    cin >> addNum;

    if(addNum > 0)
    {
        // 计算新空间大小
        int newSize = this->m_EmpNum + addNum;

        // 开辟新空间
        Worker ** newSpace = new Worker*[newSize];

        // 将原空间下内容存放到新空间下
        if(this->m_EmpArray != NULL)
        {
            for(int i=0; i<addNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        // 输入新数据
        for(int i=0; i<addNum; i++)
        {
            int id;
            string name;
            int dSelect;

            cout << "请输入第" << i + 1 << "个新职工编号" << endl;
            cin >> id;

            cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
            cin >> name;

            cout << "请选择该职工的岗位："
                << "\t1、普通员工"
                << "\t2、经理"
                << "\t3、老板"<< endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manger(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            
            default:
                break;
            }

            newSpace[this->m_EmpNum + i] = worker;
        }

        // 释放原有空间
        delete[] this->m_EmpArray;

        // 更改新空间的指向
        this->m_EmpArray = newSpace;

        // 更新新的个数
        this->m_EmpNum = newSize;

        // 更新职工不为空的标志位
        this->m_FileIsEmpty = false;

        //提示信息
        cout << "成功添加" << addNum << "名新职工" <<endl;

        // 保存到文件中
        this->save();
    }
    else
    {
        cout << "输入有误" << endl;
    }
}

// 保存职工信息
void WorkerManger::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);

    for(int i=0; i<this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();
}

// 获取职工人数
int WorkerManger::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int num = 0;

    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num ++;
    }
    ifs.close();
    
    return num;
}

// 初始化员工
void WorkerManger::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int dId;

    int index = 0;
    while(ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker * worker = NULL;

        // 根据不同部门的Id创建不同对象
        if(dId == 1)
        {
            worker = new Employee(id, name, dId);
        }
        else if(dId == 2)
        {
            worker = new Manger(id, name, dId);
        }
        else
        {
            worker = new Boss(id, name, dId);
        }

        // 存放在数组中
        this->m_EmpArray[index] = worker;
        index++;
    }
}

// 显示职工
void WorkerManger::show_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或文件记录为空" << endl;
    }
    else{
        for(int i=0; i<m_EmpNum; i++)
        {
            // 利用多态调用接口
            this->m_EmpArray[i]->showInfo();
        }
    }

    system("pause");
    system("cls");
}

// 职工存在判断
int WorkerManger::isExit(int id)
{
    int index = -1;

    for(int i=0; i<this->m_EmpNum; i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            index = i;

            break;
        }
    }
    return index;
}

// 删除职工函数实现
void WorkerManger::del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者文件为空！" << endl;
    }
    else
    {
        // 按职工编号删除
        cout << "请输入要删除的职工编号：" << endl;
        int id = 0;
        cin >> id;

        int index = this->isExit(id);

        if(index != -1)
        {
            for(int i=index; i<this->m_EmpNum-1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;

            this->save(); // 删除或数据同步到文件
            cout << "成功删除编号为" << id << "的职工" << endl;
        }
        else
        {
            cout << "删除失败，未找到编号为" << id << "的职工！" << endl;
        }
    }

    system("cls");
}

// 修改职工函数实现
void WorkerManger::mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或文件为空！" << endl;
    }
    else
    {
        cout << "请输入要修改的职工编号：" << endl;
        int id;
        cin >> id;

        int ret = this->isExit(id);
        if(ret != -1)
        {
            // 查找到编号的职工
            delete this->m_EmpArray[ret];

            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到：" << id << "号职工，请输入新职工号" << endl;
            cin >> newId;

            cout << "请输入新姓名" << endl;
            cin >> newName;

            cout << "请输入岗位：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;

            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manger(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            
            default:
                break;
            }

            // 更改数据，更新到数组中
            this->m_EmpArray[ret] = worker;

            cout << "修改成功！" << endl;
        }
        else
        {
            cout << "修改失败，查无此人！" << endl;
        }
    }
}

// 查找职工函数实现
void WorkerManger::find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或文件为空！" << endl;
    }
    else
    {
        cout << "请输入查找方式：" << endl;
        cout << "1、按职工编号查找" << endl;
        cout << "2、按姓名查找" << endl;

        int select = 0;
        cin >> select;

        if(select == 1)
        {
            int id;
            cout << "请输入职工编号：" << endl;
            cin >> id;

            int ret = isExit(id);
            if(ret != -1)
            {
                cout << "查找成功！该职工信息如下" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查找失败，查无此人！" << endl;
            }
        }
        else if(select == 2)
        {
            string name = "";
            cout << "请输入职工姓名" << endl;
            cin >> name;

            bool flag = false; // 查找到的标志
            for(int i=0; i< m_EmpNum; i++)
            {
                if(m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功，该职工信息如下：" << endl;
                    this->m_EmpArray[i]->showInfo();

                    flag = true;
                }
            }
            if(flag == false)
            {
                cout << "查找失败，查无此人！"  << endl;
            }
        }
        else
        {
            cout << "输入选项有误！" << endl;
        }
    }
}

// 排序职工
void WorkerManger::sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或文件为空！" << endl;
    }
    else
    {
        cout << "请选择排序方式：" << endl;
        cout << "1、按职工编号升序" << endl;
        cout << "2、按职工编号降序" << endl;

        int select = 0;
        cin >> select;

        for(int i=0; i<m_EmpNum; i++)
        {
            int minOrMax = i;
            for(int j=i+1; j<m_EmpNum; j++)
            {
                if(select == 1)
                {
                    if(m_EmpArray[minOrMax]->m_Id > m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
                else
                {
                    if(m_EmpArray[minOrMax]->m_Id < m_EmpArray[j]->m_Id)
                    {
                        minOrMax = j;
                    }
                }
            }
            if(i != minOrMax)
            {
                Worker * temp = m_EmpArray[i];
                m_EmpArray[i] = m_EmpArray[minOrMax];
                m_EmpArray[minOrMax] = temp;
            }
        }
        cout << "排序成功，排序后的结果为：" << endl;
        this->save();
        this->show_Emp();
    }
}

void WorkerManger::clear_File()
{
    cout << "确认清空？" << endl;
    cout << "1、确认" << endl;
    cout << "2、返回" << endl;

    int select = 0;
    cin >> select;

    if(select == 1)
    {
        // 打开模式 ios::trunc 如果存在删除文件并重新创建
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for(int i=0; i<this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];
                }
            }
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_FileIsEmpty = true;

        }
        cout << "清空成功!" << endl;
    }
}