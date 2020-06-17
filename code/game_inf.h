#ifndef GAME_INF_H
#define GAME_INF_H

#include <QString>



class circle{
public:
    circle();

    void setR(int);
    void setXy(double,double);
    void setVelocity(double);
    void setAngle(double);
    void setWeight(int);
    void setFriction(int);

    int getR();
    double getX();
    double getY();
    int getWeight();
    double getFriction();
    double getVelocity();
    double getAngle();
                                             //用于获取类的私有成员
    bool IsColl[13];

private:
    enum {classic,wood,metal,ballball};
    enum{grass,cement,galaxy,ice};
    int R;
    double x;                                //用于记录瓶盖的x坐标
    double y;                                //用于记录瓶盖的y坐标
    int weight;                              //用于记录瓶盖的重量
    double friction;                         //用于记录瓶盖的弹力系数
    double velocity;                         //用于记录瓶盖速度
    double angle;                            //用于记录瓶盖角度
};

class guy: public circle
{
public:
    guy();

    void setguykind(int);                    //用于设置类的私有成员

    int getGuyKind();

private:
    bool IsMy;                               //用于记录阵营
    int GuyKind;                             //用于记录瓶盖类型

};

class ball:public circle{
public:
    ball();
};

class game_inf
{
public:
    game_inf();

    void setMyTeam(int);              //用于设置瓶盖的坐标
    void setRivalTeam(int);           //用于设置对手瓶盖坐标
    void setWinBall(int);             //用于设置获胜的进球数
    void setGamePlace(int);           //用于设置球场类型
    void setGameMode(int);            //用于设置游戏模式
    void setGameTime(int);            //用于设置游戏总时间
    void setMyName(QString);          //用于设置我的队伍名字
    void setRivalName(QString);       //用于设置玩家2队伍名字
    void setMyGoal(int);              //用于设置我的比分
    void setRivalGoal(int);           //用于设置玩家2的比分

    int getWinBall();                 //用于获取赢球条件
    int getGamePlace();               //用于获取比赛场di
    int getGameMode();                //用于获取游戏模式
    int getGameTime();                //用于获取游戏总时间
    int getMyGoal();                  //用于获取我的比分
    int getRivalGoal();               //用于获取玩家2的比分
    int getTeam(int);                 //获取队型信息
    QString getMyName();              //用于获取我的名字
    QString getRivalName();           //用于获取玩家2的名字

    guy MyGuys[6];                     //用于记录己方瓶盖信息
    guy RivalGuys[6];                  //用于记录对方瓶盖信息
    ball football;                     //用于记录足球信息

private:
    enum {my,other,guys,place,mode,selection};
    enum {classic,wood,metal};
    enum{grass,cement,galaxy,ice};
    enum{now,round,total,time,strategy};

    QString MyName;
    QString RivalName;
    int MyGoal;
    int RivalGoal;
    int WinBall;                       //用于记录胜利条件（击球数）
    int GamePlace;                     //用于记录球场类型
    int GameMode;                      //用于记录游戏模式
    int GameTime;                      //用于记录游戏总时间
    int team[2];                          //记录游戏队形
    bool IsComputer;                   //用于记录对手是玩家2还是电脑
};

#endif // GAME_INF_H
