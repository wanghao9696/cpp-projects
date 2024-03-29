#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<deque>

#include"speaker.h"

using namespace std;

// 演讲管理类
class SpeechManager{
public:
    //构造函数
    SpeechManager();
    
    void show_Menu(); //展示菜单
    void exitSystem(); // 退出系统
    void initSpeech(); // 初始化属性

    int m_Index; // 比赛轮数
    vector<int> v1; // 比赛选手：12人
    vector<int> v2; // 晋级第二轮选手：6人
    vector<int> vVictory; // 获胜选手：3人
    map<int, Speaker> m_Speaker; // 存放编号以及对应的具体选手

    void createSpeaker(); // 创建选手
    void startSpeech(); // 开始比赛
    void speechDraw(); // 抽签

    void speechContest(); // 比赛
    void showScore(); // 显示比赛结果

    void saveRecord(); // 保存记录
    void loadRecord(); // 读取记录
    void showRecord(); // 显示记录

    void clearRecord(); // 清空记录

    bool fileIsEmpty;

    // 往届记录
    map<int, vector<string>> m_Record;

    //析构函数
    ~SpeechManager();
};