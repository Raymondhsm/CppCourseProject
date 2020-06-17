#ifndef game_H
#define game_H

#include "game_inf.h"

#include <ctime>
#include <iostream>
#include <QTextStream>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QColor>
#include <QTimeLine>
#include <QMouseEvent>
#include <math.h>
#include <QSignalMapper>
#include <QPainter>
#include <QTimer>
#include <QFile>
#include <QPropertyAnimation>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMessageBox>

namespace Ui {
class game;
}

class game : public QDialog
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);

    ~game();

public slots:

    void menu();//用于菜单界面设置

private slots:
    void gaming();//用于游戏进行的函数
    void ContinueGame();
    void setup();//用于设置界面
    void Exit();//用于关闭程序界面设置
    void game_pre();//用于游戏准备界面

    void btnbgm_click();
    void btngm_click();    //用于设置界面中两按钮的点击函数
    void btnback_click();  //用于设置界面返回按钮点击函数

    void btnPreMy_click();
    void btnPreOther_click();
    void btnPrePlace_click();
    void btnPreGuy_click();
    void btnPreMode_click();
    void btnPreSelection_click();
    // 用于游戏准备界面的六个主选项按钮的点击函数

    void btnPre1_click();
    void btnPre2_click();
    void btnPre3_click();
    void btnPre4_click();
    void btnPre5_click();
    //用于游戏准备界面五个副选项按钮的点击函数

    void BallLeft();
    void BallRight();
    void TimeLeft();
    void TimeRight();

    void GameRuning();
    //用于每一帧调用的函数
    void Gamefinish();
    //游戏结束是调用的函数
    void WaitMyMove();                                 //用于我方瓶盖的瞄准函数
    void WaitRivalMove();                              //用于玩家2的瞄准函数

    void PressEvent(int);
    void ReleaseEvent();
    //12个瓶盖 的点击函数

    void btnStop_click();
    void btnBTG_click();
    void btnETG_click();
    void IdentifyColl();                            //用于检测碰撞

    void whoMove();
    void makeBGM();
private:
    Ui::game *ui;

    void paintEvent(QPaintEvent *);                    //用于绘图
    void mouseReleaseEvent(QMouseEvent *);             //用于鼠标松开的的事件

    void init_menu();                                  //用于初始化menu界面的控件
    void init_setup();                                 //用于初始化setup界面的控件
    void init_game_pre();                              //用于初始化game_pre界面的控件
    void init_gaming();                                //用于初始化gaming界面
    void refont(int);                                  //用于字体设置
    void record(int);                                  //用于界面优化
    int encryption(int);                               //用于加密数据
    int decode(int);                                   //用于解密数据
    void setSelection();                               //用于反馈选项中的选择

    void setGuyXy();                                   //用于设置瓶盖坐标
    void setGuyKind();                                 //用于设置瓶盖类型
    void setPlace();                                   //用于设置游戏场地
    void goal();                                       //用于进球后画面制作

    void WaitForMove();                                //用于瓶盖等待运动的函数
    void Coll(circle *, circle *);                     //用于碰撞后运动轨迹计算
    void CollWall(circle *);
    bool AllStop();                                    //用于判断瓶盖是否都静止
    double calculateAngle(double,double,double,double);   //用于计算运动瓶盖速度方向与另一瓶盖位置的夹角

    game_inf Ginf;
    int counter;
    int GuyCounter;
    int Record[6]={1,1,2,1,1,2};
    bool IsPress[5];
    bool IsMyPaint;
    bool IsRivalPaint;
    bool IsMyPress;
    bool IsRivalPress;
    bool IsGaming;
    int WhoGaming;
    enum {my,other,guys,place,mode,selection};
    enum {classic,wood,metal};
    enum{grass,cement,galaxy,ice};
    enum{now,round,total,time,strategy};

    QPalette palette;
    QMediaPlayer player;
    QMediaPlayer CollPlayer;
    QMediaPlaylist playerlist;
    QFont fo;
    QTimeLine timeline;
    QTimer Timer;
    QTimer GameTimer;
    QTimer MyTimer;
    QTimer RivalTimer;
    QTimer musicTimer;
    QSignalMapper SignalMapper;
    QSignalMapper SignalMapper1;
    QPainter painter;
    QPixmap *pixmapBack=new QPixmap(800,500);
    QLabel *labPaint=new QLabel(this);
    QLabel *labmeng=new QLabel(this);
    QLabel *labRecord=new QLabel(this);
    QPushButton *btnGoal=new QPushButton(this);

    QPushButton *btnQuick =new QPushButton(this);
    QPushButton *btnContinueGame =new QPushButton(this);
    QPushButton *btnSetup =new QPushButton(this);
    QPushButton *btnExit =new QPushButton(this);
    //创建菜单界面四个按钮

    QPushButton *btnbgm=new QPushButton(this);
    QPushButton *btngm=new QPushButton(this);
    QPushButton *btnback=new QPushButton(this);
    QLabel *labbgm=new QLabel(this);
    QLabel *labgm=new QLabel(this);
    //创建设置界面所需控件

    QPushButton *btnPreMy=new QPushButton(this);
    QPushButton *btnPreOther=new QPushButton(this);
    QPushButton *btnPrePlace=new QPushButton(this);
    QPushButton *btnPreGuy=new QPushButton(this);
    QPushButton *btnPreMode=new QPushButton(this);
    QPushButton *btnPreSelection=new QPushButton(this);
    //创建游戏准备界面的六个主选项按钮

    QPushButton *btnPre1=new QPushButton(this);
    QPushButton *btnPre2=new QPushButton(this);
    QPushButton *btnPre3=new QPushButton(this);
    QPushButton *btnPre4=new QPushButton(this);
    QPushButton *btnPre5=new QPushButton(this);
    //创建游戏准备界面的五个副选项按钮

    QPushButton *btnPreStart=new QPushButton(this);
    //创建游戏准备界面的返回和开始按钮

    QLabel *labDisplay=new QLabel(this);
    QLabel *labIllustrate=new QLabel(this);
    //创建游戏界面的label显示框

    QLabel *labSelectBall=new QLabel(this);
    QLabel *labSelectTime=new QLabel(this);
    //创建游戏准备选项中的两个label

    QPushButton *btnMyTeam1=new QPushButton(this);
    QPushButton *btnMyTeam2=new QPushButton(this);
    QPushButton *btnMyTeam3=new QPushButton(this);
    QPushButton *btnMyTeam4=new QPushButton(this);
    QPushButton *btnMyTeam5=new QPushButton(this);
    QPushButton *btnMyTeam6=new QPushButton(this);
    // 创建游戏瓶盖的我方六个按钮
    QPushButton *btnMyTeam[6];

    QPushButton *btnRivalTeam1=new QPushButton(this);
    QPushButton *btnRivalTeam2=new QPushButton(this);
    QPushButton *btnRivalTeam3=new QPushButton(this);
    QPushButton *btnRivalTeam4=new QPushButton(this);
    QPushButton *btnRivalTeam5=new QPushButton(this);
    QPushButton *btnRivalTeam6=new QPushButton(this);
    QPushButton *btnRivalTeam[6];
    // 创建游戏瓶盖的对方六个按钮

    QPushButton *btnBallLeft=new QPushButton(this);
    QPushButton *btnBallRight=new QPushButton(this);
    QPushButton *btnTimeLeft=new QPushButton(this);
    QPushButton *btnTimeRight=new QPushButton(this);

    QPushButton *btnBall=new QPushButton(this);
    QPushButton *btnStop=new QPushButton(this);
    QPushButton *btnBTG=new QPushButton(this);
    QPushButton *btnETG=new QPushButton(this);

    QPushButton *btnMyMove=new QPushButton(this);
    QPushButton *btnRivalMove=new QPushButton(this);

};

#endif // game_H
