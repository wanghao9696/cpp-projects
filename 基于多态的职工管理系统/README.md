# 基于多态的职工管理系统

### 职工分类:
普通员工、经理、老板；
### 包含信息：  
职工编号、职工姓名、职工岗位
### 普通员工职责：
完成经理交给的任务
### 经理职责：
完成老板交给的任务，并下发给员工
### 老板指责：
管理公司事务

### 管理系统的功能：
退出管理程序：退出当前管理系统

增加职工信息：实现批量添加职工功能，将信息录入到文件中，职工信息为：职工编号、姓名、部门编号

显示职工信息：显示公司内部所有职工的信息

删除离职职工：按照编号删除指定的职工

修改职工信息：按照编号修改职工的个人信息

查找职工信息：按照职工的编号或者姓名进行查找相关的人员信息

按照编号排序：按照职工编号，进行排序，排序规则由用户指定

清空所有文档：清空文件中记录的所有职工信息，需要确认，防止误删




# tips:
> Q: VS Code中编写c++代码时，导入自定义的.h头文件时，显示头文件not found

>> A: 首选项->设置->搜索"clang.diagnostic.enable"，把勾选去掉

> Q: VS Code写c++时的红色波浪线问题

>> A: 首选项->设置->搜索"squiggle"，将出现的 Error Squiggles 选项改为 Disabled