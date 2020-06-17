#include "game.h"
#include "ui_game.h"
#include <QPalette>
#include <string.h>

QTextStream out(stdout);
game::game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::game)
{
    setModal(true);
    ui->setupUi(this);

    fo=this->font();
    game::init_menu();
    game::init_setup();
    game::init_game_pre();
    game::init_gaming();

    ui->line1->hide();
    ui->line_2->hide();


    counter=0;
    IsMyPaint=false;
    IsRivalPaint=false;
    IsMyPress=false;
    IsRivalPress=false;
    IsGaming=false;
    for(int i=0;i<5;i++)IsPress[i]=false;

    makeBGM();
    musicTimer.setInterval(193000);
    musicTimer.setSingleShot(false);
    connect(&musicTimer,SIGNAL(timeout()),this,SLOT(makeBGM()));
    musicTimer.start();
}


game::~game()
{
    delete ui;
}


void game::gaming()
{

    menu();
    this->btnQuick->hide();
    this->btnContinueGame->hide();
    this->btnSetup->hide();
    this->btnExit->hide();
    //隐藏之前的控件

    for(int i=0;i<6;i++){
    btnMyTeam[i]->show();
    //显示我方瓶盖

    btnRivalTeam[i]->show();
    //显示对方瓶盖
    }

    btnBall->show();
    btnStop->show();

    IsGaming=true;
    GameTimer.setSingleShot(false);
    connect(&GameTimer,SIGNAL(timeout()),this,SLOT(Gamefinish()));
    GameTimer.start(1000);


    setGuyXy();

    setPlace();

    setGuyKind();

    setSelection();

    WaitMyMove();
}

void game::ContinueGame()
{


    QFile file(QCoreApplication::applicationDirPath()+"/GameInfo.txt");
    QTextStream cin(&file);
    bool ok;
    double x=0,y=0;
    QString str;
    file.open(QIODevice::ReadOnly);
    str=cin.readLine();
    if(str==NULL)return;
    Ginf.setMyTeam(decode(str.toInt(&ok,10)));
    Ginf.setRivalTeam(decode(cin.readLine().toInt(&ok,10)));
    for(int i=0;i<6;i++){
        x=decode(cin.readLine().toInt(&ok,10));
        y=decode(cin.readLine().toInt(&ok,10));
        btnMyTeam[i]->setGeometry(x,y,50,50);
        x=decode(cin.readLine().toInt(&ok,10));
        y=decode(cin.readLine().toInt(&ok,10));
        btnRivalTeam[i]->setGeometry(x,y,50,50);
    }
    x=decode(cin.readLine().toInt(&ok,10));
    y=decode(cin.readLine().toInt(&ok,10));
    btnBall->setGeometry(x,y,15,15);
    IsMyPress=cin.readLine().toInt(&ok,10);
    IsRivalPress=cin.readLine().toInt(&ok,10);
    Ginf.setGamePlace(decode(cin.readLine().toInt(&ok,10)));
    Ginf.MyGuys[0].setguykind(decode(cin.readLine().toInt(&ok,10)));
    Ginf.RivalGuys[0].setguykind(decode(cin.readLine().toInt(&ok,10)));
    Ginf.setGameMode(decode(cin.readLine().toInt(&ok,10)));
    Ginf.setWinBall(decode(cin.readLine().toInt(&ok,10)));
    Ginf.setMyGoal(decode(cin.readLine().toInt(&ok,10)));
    Ginf.setRivalGoal(decode(cin.readLine().toInt(&ok,10)));
    Ginf.setMyName(cin.readLine());
    Ginf.setRivalName(cin.readLine());
    Ginf.setGameTime(decode(cin.readLine().toInt(&ok,10)));
    WhoGaming=cin.readLine().toInt(&ok,10);
    file.close();

    //重现游戏场面
    menu();
    this->btnQuick->hide();
    this->btnContinueGame->hide();
    this->btnSetup->hide();
    this->btnExit->hide();
    //隐藏之前的控件

    for(int i=0;i<6;i++){
    btnMyTeam[i]->show();
    //显示我方瓶盖
    btnRivalTeam[i]->show();
    //显示对方瓶盖
    }

    btnBall->show();
    btnStop->show();

    IsGaming=true;
    GameTimer.setSingleShot(false);
    connect(&GameTimer,SIGNAL(timeout()),this,SLOT(Gamefinish()));
    GameTimer.start(1000);

    setPlace();
    setGuyKind();
    whoMove();

}

void game::menu()
{
    IsGaming=false;

    this->btnQuick->show();
    this->btnContinueGame->show();
    this->btnSetup->show();
    this->btnExit->show();
    //显示四个按钮

    this->labbgm->hide();
    this->labgm->hide();
    this->btnbgm->hide();
    this->btngm->hide();
    this->btnback->hide();      //隐藏设置界面的按钮和文本

    this->btnPreStart->hide();
    ui->line1->hide();
    ui->line_2->hide();
    this->btnPreMy->hide();
    this->btnPreOther->hide();
    this->btnPreGuy->hide();
    this->btnPreMode->hide();
    this->btnPrePlace->hide();
    this->btnPreSelection->hide();
    this->btnPre1->hide();
    this->btnPre2->hide();
    this->btnPre3->hide();
    this->btnPre4->hide();
    this->btnPre5->hide();
    this->labDisplay->hide();
    this->labIllustrate->hide();
    this->labSelectBall->hide();
    this->labSelectTime->hide();
    //隐藏游戏准备界面按钮

    for(int i=0;i<6;i++){
    btnMyTeam[i]->hide();
    //隐藏我方瓶盖

    btnRivalTeam[i]->hide();
    //隐藏对方瓶盖
    }
    btnBall->hide();

    btnBTG->hide();
    btnStop->hide();
    btnETG->hide();
    labmeng->hide();
    labPaint->hide();
    labRecord->hide();
    btnGoal->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    btnMyMove->hide();
    btnRivalMove->hide();

    this->setStyleSheet("#game { \nborder-image: url(:/logo/Image/menu.jpg);\n} \n#game * { \nborder-image:url(); \n}");
    fo=this->font();
}

void game::setup()
{
    this->btnQuick->hide();
    this->btnContinueGame->hide();
    this->btnSetup->hide();
    this->btnExit->hide();                  //隐藏菜单界面四个按钮

    this->labbgm->show();
    this->labgm->show();
    this->btnbgm->show();
    this->btngm->show();
    this->btnback->show();
    //显示setup界面的控件

}

void game::Exit()
{
    if(QMessageBox::question(this,tr("Warning!"),tr("Are you sure to exit?"),
                             QMessageBox::Cancel|QMessageBox::Yes)==QMessageBox::Yes)
    {
        exit(0);
    }
}

void game::game_pre()
{
    this->btnQuick->hide();
    this->btnContinueGame->hide();
    this->btnSetup->hide();
    this->btnExit->hide();
    //隐藏菜单界面按钮

    btnback->show();
    btnPreStart->show();
    //显示返回和开始按钮

    btnPreMy->show();
    btnPreOther->show();
    btnPreGuy->show();
    btnPreMode->show();
    btnPrePlace->show();
    btnPreSelection->show();
    //显示六个主选项按钮

    fo=this->font();
    btnback->setFont(fo);
    btnPreStart->setFont(fo);
    btnPre1->setFont(fo);
    btnPre2->setFont(fo);
    btnPre3->setFont(fo);
    btnPre4->setFont(fo);
    btnPre5->setFont(fo);

    game::btnPreGuy_click();
    game::btnPreMode_click();
    game::btnPreOther_click();
    game::btnPrePlace_click();
    game::btnPreMy_click();
    //每个执行一遍，以防人为未选择导致为初始化

    for(int i=0;i<5;i++)IsPress[i]=false;

    ui->line1->show();
    ui->line_2->show();
    //显示分隔线
}


void game::btnPreMy_click()
{
    counter=my;
    //用于简易标记本模式

    btnPre1->show();
    btnPre2->show();
    btnPre3->show();
    btnPre4->show();
    btnPre5->show();
    //显示五个按钮

    labDisplay->show();
    labIllustrate->hide();
    labSelectBall->hide();
    labSelectTime->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    //显示两个label

    record(0);
    refont(15);
    btnPreMy->setFont(this->font());
    //btnpremy按钮字体增大

    btnPre1->setText("1-3-2");
    btnPre2->setText("1-2-3");
    btnPre3->setText("1-4-1");
    btnPre4->setText("1-2-2-1");
    btnPre5->setText("3-2-1");

    //设置五个副选项按钮的文本

    if(IsPress[0]==false) btnPre1_click();
    //防止人为未选择导致控件初始化
    IsPress[0]=true;
}

void game::btnPreOther_click(){
    counter=other;
    //用于简易标记本模式

    btnPre1->show();
    btnPre4->show();
    btnPre5->show();
    //显示五个按钮

    labDisplay->show();
    labIllustrate->hide();
    labSelectBall->hide();
    labSelectTime->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    //显示两个label

    record(1);
    refont(15);
    btnPreOther->setFont(this->font());
    //btnpreother按钮字体增大

    btnPre1->setText("1-3-2");
    btnPre2->setText("1-2-3");
    btnPre3->setText("1-4-1");
    btnPre4->setText("1-2-2-1");
    btnPre5->setText("3-2-1");
    //设置五个副选项按钮的文本

    if(IsPress[1]==false) btnPre1_click();
    //防止人为未选择导致控件初始化

    IsPress[1]=true;
}

void game::btnPreGuy_click(){
    counter=guys;
    //用于简易标记本模式

    btnPre1->show();
    btnPre4->show();
    btnPre5->hide();
    //显示五个按钮

    labDisplay->show();
    labIllustrate->hide();
    labSelectBall->hide();
    labSelectTime->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    //显示两个label

    refont(15);
    btnPreGuy->setFont(this->font());
    //btnpreguy按钮字体增大

    btnPre1->setText("PLAY 1");
    btnPre2->setText("classic");
    btnPre3->setText("wood");
    btnPre4->setText("metal");
    btnPre5->setText("Wait For More");
    //设置五个副选项按钮的文本

    if(IsPress[2]==false) {
        btnPre2_click();
        btnPre1_click();
        btnPre2_click();
        btnPre1_click();
    }
    //防止人为未选择导致控件初始化
   IsPress[2]=true;
}

void game::btnPrePlace_click(){
    counter=place;
    //用于简易标记本模式

    btnPre1->show();
    btnPre4->show();
    btnPre5->show();
    //显示五个按钮

    labDisplay->show();
    labIllustrate->hide();
    labSelectBall->hide();
    labSelectTime->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    //显示两个label

    record(3);
    refont(15);
    btnPrePlace->setFont(this->font());
    //btnpreplace按钮字体增大

    btnPre1->setText("GrassLand");
    btnPre2->setText("Cement Floor");
    btnPre3->setText("Galaxy");
    btnPre4->setText("Ice Surface");
    btnPre5->setText("Wait For More");
    //设置五个副选项按钮的文本

    if(IsPress[3]==false) btnPre1_click();
    //防止人为未选择导致控件初始化
    IsPress[3]=true;
}

void game::btnPreMode_click(){
    counter=mode;
    //用于简易标记本模式

    btnPre1->show();
    btnPre4->show();
    btnPre5->show();
    //显示五个按钮

    labDisplay->show();
    labIllustrate->show();
    labSelectBall->hide();
    labSelectTime->hide();
    btnBallLeft->hide();
    btnBallRight->hide();
    btnTimeLeft->hide();
    btnTimeRight->hide();
    //显示两个label

    record(4);
    refont(15);
    btnPreMode->setFont(this->font());
    //btnPreMode按钮字体增大

    btnPre1->setText("即时模式");
    btnPre2->setText("回合模式");
    btnPre3->setText("总数模式");
    btnPre4->setText("计时模式");
    btnPre5->setText("战略模式");
    //设置五个副选项按钮的文本

    if(IsPress[4]==false) btnPre1_click();
    //防止人为未选择导致控件初始化
   IsPress[4]=true;
}

void game::btnPreSelection_click(){
    counter=selection;
    //用于简易标记本模式

    btnPre1->hide();
    btnPre4->hide();
    btnPre5->hide();
    //显示五个按钮

    labDisplay->hide();
    labIllustrate->hide();
    labSelectBall->show();
    labSelectTime->show();
    btnBallLeft->show();
    btnBallRight->show();
    btnTimeLeft->show();
    btnTimeRight->show();
    labRecord->hide();

    refont(15);
    btnPreSelection->setFont(this->font());
    //btnPreSelection按钮字体增大

    btnPre2->setText("The Total Ball");
    btnPre3->setText("The Total Time");
    //设置五个副选项按钮的文本
}


void game::btnPre1_click(){

    switch (counter){
    case my:
        labDisplay->setPixmap(QPixmap(":/logo/Image/132.png"));
        Ginf.setMyTeam(132);
        Record[0]=1;
        labRecord->setGeometry(50,120,200,50);
        break;
    case other:
        labDisplay->setPixmap(QPixmap(":/logo/Image/132.png"));
        Ginf.setRivalTeam(132);
        Record[1]=1;
        labRecord->setGeometry(50,120,200,50);
        break;
    case guys:
        if(btnPre1->text()=="PLAY 1") {btnPre1->setText("PLAY 2");
                                       record(5);}
        else {btnPre1->setText("PLAY 1");
              record(2);}
        break;
    case place:
        labDisplay->setPixmap(QPixmap(":/place/Image/草地.jpg").scaled(QSize(400,225)));
        Ginf.setGamePlace(grass);
        Record[3]=1;
        labRecord->setGeometry(50,120,200,50);
        break;
    case mode:
        labDisplay->setPixmap(QPixmap(":/logo/Image/即时模式.jpg"));
        Ginf.setGameMode(now);
        labIllustrate->setText("Two players hit the ball at the same time.");
        Record[4]=1;
        labRecord->setGeometry(50,120,200,50);
        break;
   }
}

void game::btnPre2_click(){
    switch (counter){
    case my:
        labDisplay->setPixmap(QPixmap(":/logo/Image/123.png"));
        Ginf.setMyTeam(123);
        Record[0]=2;
        labRecord->setGeometry(50,190,200,50);
        break;
    case other:
        labDisplay->setPixmap(QPixmap(":/logo/Image/123.png"));
        Ginf.setRivalTeam(123);
        Record[1]=2;
        labRecord->setGeometry(50,190,200,50);
        break;
    case guys:
        labDisplay->setPixmap(QPixmap(":/baller/Image/classic_show.png"));
        if(btnPre1->text()=="PLAY 1")
            for(int i=0;i<6;i++)  {Ginf.MyGuys[i].setguykind(classic);
                                   Record[2]=2;labRecord->setGeometry(50,190,200,50);}
        if(btnPre1->text()=="PLAY 2")
            for(int i=0;i<6;i++)  {Ginf.RivalGuys[i].setguykind(classic);
                                   Record[5]=2;labRecord->setGeometry(50,190,200,50);}
        break;
    case place:
        labDisplay->setPixmap(QPixmap(":/place/Image/水泥.jpg").scaled(QSize(400,225)));
        Ginf.setGamePlace(cement);
        Record[3]=2;
        labRecord->setGeometry(50,190,200,50);
        break;
    case mode:
        labDisplay->setPixmap(QPixmap(":/logo/Image/回合模式.jpg"));
        labIllustrate->setText("Each player hits the ball once, once the ball is finished, the next player will hit the ball.");
        Ginf.setGameMode(round);
        Record[4]=2;
        labRecord->setGeometry(50,190,200,50);
        break;
    }
}

void game::btnPre3_click(){
    switch (counter){
    case my:
        labDisplay->setPixmap(QPixmap(":/logo/Image/141.png"));
        Ginf.setMyTeam(141);
        Record[0]=3;
        labRecord->setGeometry(50,260,200,50);
        break;
    case other:
        labDisplay->setPixmap(QPixmap(":/logo/Image/141.png"));
        Ginf.setRivalTeam(141);
        Record[1]=3;
        labRecord->setGeometry(50,260,200,50);
        break;
    case guys:
        labDisplay->setPixmap(QPixmap(":/baller/Image/wood_show.png"));
        if(btnPre1->text()=="PLAY 1")
            for(int i=0;i<6;i++)  {Ginf.MyGuys[i].setguykind(wood);
                                   Record[2]=3;labRecord->setGeometry(50,260,200,50);}
        if(btnPre1->text()=="PLAY 2")
            for(int i=0;i<6;i++)  {Ginf.RivalGuys[i].setguykind(wood);
                                   Record[5]=3;labRecord->setGeometry(50,260,200,50);}
        break;
    case place:
        labDisplay->setPixmap(QPixmap(":/place/Image/银河.jpg").scaled(QSize(400,225)));
        Ginf.setGamePlace(galaxy);
        Record[3]=3;
        labRecord->setGeometry(50,260,200,50);
        break;
    case mode:
        labDisplay->setPixmap(QPixmap(":/logo/Image/总数模式.jpg"));
        //labIllustrate->setText("Both players can move all the caps needed to move forward at the same time.");
        Ginf.setGameMode(total);
        Record[4]=3;
        labRecord->setGeometry(50,260,200,50);
        break;
}
}

void game::btnPre4_click(){
    switch (counter){
    case my:
        labDisplay->setPixmap(QPixmap(":/logo/Image/1221.png"));
        Ginf.setMyTeam(1221);
        Record[0]=4;
        labRecord->setGeometry(50,330,200,50);
        break;
    case other:
        labDisplay->setPixmap(QPixmap(":/logo/Image/1221.png"));
        Ginf.setRivalTeam(1221);
        Record[1]=4;
        labRecord->setGeometry(50,330,200,50);
        break;
    case guys:
        labDisplay->setPixmap(QPixmap(":/baller/Image/metel_show.png"));
        if(btnPre1->text()=="PLAY 1")
            for(int i=0;i<6;i++)  {Ginf.MyGuys[i].setguykind(metal);
                                   Record[2]=4;labRecord->setGeometry(50,330,200,50);}
        if(btnPre1->text()=="PLAY 2")
            for(int i=0;i<6;i++)  {Ginf.RivalGuys[i].setguykind(metal);
                                   Record[5]=4;labRecord->setGeometry(50,330,200,50);}
        break;
    case place:
        labDisplay->setPixmap(QPixmap(":/place/Image/雪地.jpg").scaled(QSize(400,225)));
        Ginf.setGamePlace(ice);
        Record[3]=4;
        labRecord->setGeometry(50,330,200,50);
        break;
    case mode:
        labDisplay->setPixmap(QPixmap(":/logo/Image/计时模式.jpg"));
        labIllustrate->setText("Each player has a limited time to move the cap.");
        Ginf.setGameMode(time);
        Record[4]=4;
        labRecord->setGeometry(50,330,200,50);
        break;
}
}

void game::btnPre5_click(){

    switch (counter){
    case my:
        labDisplay->setPixmap(QPixmap(":/logo/Image/321.png"));
        Ginf.setMyTeam(321);
        Record[0]=5;
        labRecord->setGeometry(50,410,200,50);
        break;
    case other:
        labDisplay->setPixmap(QPixmap(":/logo/Image/321.png"));
        Ginf.setRivalTeam(321);
        Record[1]=5;
        labRecord->setGeometry(50,410,200,50);
        break;
    case guys:
        break;
    case place:
        break;
    case mode:
        labDisplay->setPixmap(QPixmap(":/logo/Image/战略模式.jpg"));
        labIllustrate->setText("When it's your turn, the player can move several caps before hitting the ball.");
        Ginf.setGameMode(strategy);
        Record[4]=5;
        labRecord->setGeometry(50,410,200,50);
        break;
    }
}

void game::BallLeft()
{
    QString m=labSelectBall->text();
    if(m=="1 Ball") labSelectBall->setText("INFINITY");
    else if(m=="2 Balls") labSelectBall->setText("1 Ball");
    else if(m=="3 Balls") labSelectBall->setText("2 Balls");
    else labSelectBall->setText("3 Balls");
}

void game::BallRight()
{
    QString m=labSelectBall->text();
    if(m=="1 Ball") labSelectBall->setText("2 Balls");
    else if(m=="2 Balls") labSelectBall->setText("3 Balls");
    else if(m=="3 Balls") labSelectBall->setText("INFINITY");
    else labSelectBall->setText("1 Ball");
}

void game::TimeLeft()
{
    QString m=labSelectTime->text();
    if(m=="1 minute")labSelectTime->setText("5 minutes");
    else if(m=="2 minutes")labSelectTime->setText("1 minute");
    else if(m=="3 minutes")labSelectTime->setText("2 minutes");
    else if(m=="4 minutes")labSelectTime->setText("3 minutes");
    else if(m=="5 minutes")labSelectTime->setText("4 minutes");
}

void game::TimeRight()
{
    QString m=labSelectTime->text();
    if(m=="1 minute")labSelectTime->setText("2 minutes");
    else if(m=="2 minutes")labSelectTime->setText("3 minutes");
    else if(m=="3 minutes")labSelectTime->setText("4 minutes");
    else if(m=="4 minutes")labSelectTime->setText("5 minutes");
    else if(m=="5 minutes")labSelectTime->setText("1 minute");
}


void game::GameRuning()
{
    timeline.setUpdateInterval(10);
    IdentifyColl();
    timeline.setDuration(20000);
    timeline.setFrameRange(0,20000);
    timeline.start();
}

void game::Gamefinish()
{
   if(Ginf.getGameTime()==0) goal();
   else Ginf.setGameTime(Ginf.getGameTime()-1);
}

void game::PressEvent(int i)
{
    GuyCounter=i+1;
    WaitForMove();
}

void game::ReleaseEvent()
{
    QPoint mouse;
    mouse=this->mapFromGlobal(this->cursor().pos());
    bool ming;
    ming=(GuyCounter<=6);
    switch(ming){
    case true:
        if(Ginf.MyGuys[GuyCounter-1].getVelocity()<=20){
            Ginf.MyGuys[GuyCounter-1].setVelocity(0);
            Ginf.MyGuys[GuyCounter-1].setAngle(0);
            IsMyPaint=false;
            WaitMyMove();
        }else if(mouse.x()>=btnMyTeam[GuyCounter-1]->x()&&mouse.y()>=btnMyTeam[GuyCounter-1]->y()&&mouse.x()<=btnMyTeam[GuyCounter-1]->x()+50&&mouse.y()<=btnMyTeam[GuyCounter-1]->y()+50){
            IsMyPress=false;
            IsMyPaint=false;
            labPaint->hide();
            MyTimer.stop();
            WaitRivalMove();
        }else {}
        break;
    case false:
        if(Ginf.RivalGuys[GuyCounter-6-1].getVelocity()<=20){
            IsRivalPaint=false;
            Ginf.RivalGuys[GuyCounter-6-1].setVelocity(0);
            Ginf.RivalGuys[GuyCounter-6-1].setAngle(0);
            WaitRivalMove();
        }else if(mouse.x()>=btnRivalTeam[GuyCounter-7]->x()&&mouse.y()>=btnRivalTeam[GuyCounter-7]->y()&&mouse.x()<=btnRivalTeam[GuyCounter-7]->x()+50&&mouse.y()<=btnRivalTeam[GuyCounter-7]->y()+50){
            IsRivalPress=false;
            IsRivalPaint=false;
            labPaint->hide();
            RivalTimer.stop();
            GameRuning();
        }else {}
        break;
    }
}

void game::btnStop_click()
{
    labmeng->show();
    btnBTG->show();
    btnETG->show();
    btnStop->hide();
    GameTimer.stop();

    for(int i=0;i<6;i++){
        btnMyTeam[i]->setEnabled(false);
        btnRivalTeam[i]->setEnabled(false);
    }
}

void game::btnBTG_click()
{
    btnStop->show();
    btnETG->hide();
    btnBTG->hide();
    labmeng->hide();
    GameTimer.start();

    for(int i=0;i<6;i++){
        btnMyTeam[i]->setEnabled(true);
        btnRivalTeam[i]->setEnabled(true);
    }
}

void game::btnETG_click()
{
    for(int i=0;i<6;i++){
        btnMyTeam[i]->setEnabled(true);
        btnRivalTeam[i]->setEnabled(true);
    }

    if(WhoGaming==my)MyTimer.stop();
    else if(WhoGaming==other)RivalTimer.stop();


    QFile file(QCoreApplication::applicationDirPath()+"/GameInfo.txt");
    srand(std::time(NULL));
    QTextStream cout(&file);
    file.open(QIODevice::WriteOnly);
    cout<<encryption(Ginf.getTeam(1))<<"\n";
    cout<<encryption(Ginf.getTeam(2))<<"\n";
    for(int i=0;i<6;i++){
        cout<<encryption(btnMyTeam[i]->x())<<"\n";
        cout<<encryption(btnMyTeam[i]->y())<<"\n";
        cout<<encryption(btnRivalTeam[i]->x())<<"\n";
        cout<<encryption(btnRivalTeam[i]->y())<<"\n";
    }
    cout<<encryption(btnBall->x())<<"\n"<<encryption(btnBall->y())<<"\n";
    cout<<IsMyPress<<"\n"<<IsRivalPress<<"\n";
    cout<<encryption(Ginf.getGamePlace())<<"\n";
    cout<<encryption(Ginf.MyGuys[0].getGuyKind())<<"\n";
    cout<<encryption(Ginf.RivalGuys[0].getGuyKind())<<"\n";
    cout<<encryption(Ginf.getGameMode())<<"\n";
    cout<<encryption(Ginf.getWinBall())<<"\n";
    cout<<encryption(Ginf.getMyGoal())<<"\n"<<encryption(Ginf.getRivalGoal())<<"\n";
    cout<<Ginf.getMyName()<<"\n"<<Ginf.getRivalName()<<"\n";
    cout<<encryption(Ginf.getGameTime())<<"\n";
    cout<<encryption(WhoGaming)<<"\n";
    file.close();

    IsMyPress=false;
    IsRivalPress=false;
    menu();

}

void game::btnbgm_click()
{
    if(this->btnbgm->text()=="on"){
        this->btnbgm->setText("off");
        player.stop();
        musicTimer.stop();
    }
    else {
        this->btnbgm->setText("on");
        player.play();
        musicTimer.start();
    }

}
//设置背景音乐的按钮函数

void game::btngm_click()
{
    if(this->btngm->text()=="on")
        this->btngm->setText("off");

    else this->btngm->setText("on");
}
//设置游戏音乐的函数

void game::btnback_click()
{
    game::menu();
}
//设置中返回按钮的实现代码



void game::init_menu()
{
    btnMyTeam[0]=btnMyTeam1;
    btnMyTeam[1]=btnMyTeam2;
    btnMyTeam[2]=btnMyTeam3;
    btnMyTeam[3]=btnMyTeam4;
    btnMyTeam[4]=btnMyTeam5;
    btnMyTeam[5]=btnMyTeam6;

    btnRivalTeam[0]=btnRivalTeam1;
    btnRivalTeam[1]=btnRivalTeam2;
    btnRivalTeam[2]=btnRivalTeam3;
    btnRivalTeam[3]=btnRivalTeam4;
    btnRivalTeam[4]=btnRivalTeam5;
    btnRivalTeam[5]=btnRivalTeam6;

    //初始化menu的控件：
    this->btnQuick->setGeometry(this->width()*3/8,this->height()*2/5,200,40);
    this->btnContinueGame->setGeometry(this->width()*3/8,this->height()*260/500,200,40);
    this->btnSetup->setGeometry(this->width()*3/8,this->height()*320/500,200,40);
    this->btnExit->setGeometry(this->width()*3/8,this->height()*380/500,200,40);
    //设置四个按钮的xy值和长宽

    this->btnQuick->setFont(fo);
    this->btnContinueGame->setFont(fo);
    this->btnSetup->setFont(fo);
    this->btnExit->setFont(fo);

    this->btnQuick->setText("Quick game");
    this->btnContinueGame->setText("Continue Game");
    this->btnSetup->setText("Setup");
    this->btnExit->setText("Exit");
    //设置四个按钮的显示文字

    this->btnQuick->setFlat(true);
    this->btnContinueGame->setFlat(true);
    this->btnSetup->setFlat(true);
    this->btnExit->setFlat(true);
    //消除按钮边框

    this->connect(this->btnQuick,SIGNAL(clicked(bool)),this,SLOT(game_pre()));
    this->connect(this->btnContinueGame,SIGNAL(clicked(bool)),this,SLOT(ContinueGame()));
    this->connect(this->btnSetup,SIGNAL(clicked(bool)),this,SLOT(setup()));
    this->connect(this->btnExit,SIGNAL(clicked(bool)),this,SLOT(Exit()));
    //连接个按钮信号和槽
}

void game::init_setup()
{
    palette.setColor(QPalette::WindowText,Qt::black);
    //初始化setup控件
    this->labbgm->setGeometry(this->width()*170/800,this->height()*250/500,250,40);
    this->labbgm->setText("Background Music :");
    this->labbgm->setPalette(palette);
    this->labbgm->setEnabled(false);
    this->labbgm->setFont(this->font());//设置labbgm的参数

    this->labgm->setGeometry(this->width()*170/800,this->height()*330/500,180,40);
    this->labgm->setText("Game Music :");
    this->labgm->setPalette(palette);
    this->labgm->setEnabled(false);
    this->labgm->setFont(this->font());//设置labgm的参数

    this->btnbgm->setGeometry(this->width()*480/800,this->height()*250/500,100,40);
    if(this->btnbgm->text()==NULL) this->btnbgm->setText("on");
    this->btnbgm->setFont(this->font());//设置btnbgm的参数

    this->btngm->setGeometry(this->width()*480/800,this->height()*330/500,100,40);
    if(this->btngm->text()==NULL) this->btngm->setText("on");
    this->btngm->setFont(this->font());
    //设置btngmde的参数


    this->btnback->setText("<<<BACK");
    this->btnback->setGeometry(0,0,150,30);
    this->btnback->setFont(this->font());

    this->btnbgm->setFlat(true);
    this->btngm->setFlat(true);
    this->btnback->setFlat(true);
    //消除按钮边框


    this->connect(this->btnbgm,SIGNAL(clicked(bool)),this,SLOT(btnbgm_click()));
    this->connect(this->btngm,SIGNAL(clicked(bool)),this,SLOT(btngm_click()));
    this->connect(this->btnback,SIGNAL(clicked(bool)),this,SLOT(btnback_click()));
    //按钮与对应函数连接

}

void game::init_game_pre()
{
    btnPreStart->setGeometry(650,0,150,30);     //设置返回和开始按钮的geometry
    btnPreStart->setText("START >>>");

    palette.setColor(QPalette::ButtonText,Qt::gray);
    btnback->setPalette(palette);
    btnPreStart->setPalette(palette);

    refont(15);
    btnPreMy->setGeometry(15,35,160,40);
    btnPreOther->setGeometry(143,35,170,40);
    btnPrePlace->setGeometry(271,35,160,40);
    btnPreGuy->setGeometry(399,35,160,40);
    btnPreMode->setGeometry(527,35,160,40);
    btnPreSelection->setGeometry(655,35,160,40);                  //设置六个主选项按钮的位置


    btnPre1->setGeometry(60,120,180,40);
    btnPre2->setGeometry(60,190,180,40);
    btnPre3->setGeometry(60,260,180,40);
    btnPre4->setGeometry(60,330,180,40);
    btnPre5->setGeometry(60,410,180,40);
                                                   //设置五个副选项按钮的geometry
    fo.setPointSize(15);
    labIllustrate->setFont(fo);
    //设置labillustrate的字号大小为15
    labDisplay->setGeometry(300,120,490,330);
    labIllustrate->setGeometry(300,450,490,30);
    labSelectBall->setGeometry(450,190,150,40);
    labSelectTime->setGeometry(450,260,150,30);
    //设置四个label的geometry

    btnBallLeft->setGeometry(405,190,40,40);
    btnBallRight->setGeometry(615,190,40,40);
    btnTimeLeft->setGeometry(405,260,40,40);
    btnTimeRight->setGeometry(615,260,40,40);

    btnBallLeft->setFlat(true);
    btnBallRight->setFlat(true);
    btnTimeLeft->setFlat(true);
    btnTimeRight->setFlat(true);

    btnBallLeft->setIcon(QPixmap(":/logo/Image/Left.png").scaled(40,40));
    btnBallRight->setIcon(QPixmap(":/logo/Image/right.png").scaled(40,40));
    btnTimeLeft->setIcon(QPixmap(":/logo/Image/Left.png").scaled(40,40));
    btnTimeRight->setIcon(QPixmap(":/logo/Image/right.png").scaled(40,40));

    labSelectBall->setEnabled(true);
    labSelectTime->setEnabled(true);

    btnPreMy->setText("My Team");
    btnPreOther->setText("Rival's Team");
    btnPrePlace->setText("Ground");
    btnPreGuy->setText("Footballer");
    btnPreMode->setText("Mode");
    btnPreSelection->setText("Selection");        //设置六个主选项按钮的显示文本

    labSelectBall->setText("3 Balls");
    labSelectTime->setText("5 minutes");

    btnPreMy->setFlat(true);
    btnPreOther->setFlat(true);
    btnPreGuy->setFlat(true);
    btnPrePlace->setFlat(true);
    btnPreMode->setFlat(true);
    btnPreSelection->setFlat(true);

    btnPreStart->setFlat(true);

    btnPre1->setFlat(true);
    btnPre2->setFlat(true);
    btnPre3->setFlat(true);
    btnPre4->setFlat(true);
    btnPre5->setFlat(true);

    this->connect(this->btnPreStart,SIGNAL(clicked(bool)),this,SLOT(gaming()));
                                                  //连接返回、开始按钮的实现函数

    this->connect(this->btnPreMy,SIGNAL(clicked(bool)),this,SLOT(btnPreMy_click()));
    this->connect(this->btnPreOther,SIGNAL(clicked(bool)),this,SLOT(btnPreOther_click()));
    this->connect(this->btnPrePlace,SIGNAL(clicked(bool)),this,SLOT(btnPrePlace_click()));
    this->connect(this->btnPreMode,SIGNAL(clicked(bool)),this,SLOT(btnPreMode_click()));
    this->connect(this->btnPreGuy,SIGNAL(clicked(bool)),this,SLOT(btnPreGuy_click()));
    this->connect(this->btnPreSelection,SIGNAL(clicked(bool)),this,SLOT(btnPreSelection_click()));
                                                   //连接六个主选项按钮和其实现函数

    this->connect(this->btnPre1,SIGNAL(clicked(bool)),this,SLOT(btnPre1_click()));
    this->connect(this->btnPre2,SIGNAL(clicked(bool)),this,SLOT(btnPre2_click()));
    this->connect(this->btnPre3,SIGNAL(clicked(bool)),this,SLOT(btnPre3_click()));
    this->connect(this->btnPre4,SIGNAL(clicked(bool)),this,SLOT(btnPre4_click()));
    this->connect(this->btnPre5,SIGNAL(clicked(bool)),this,SLOT(btnPre5_click()));
    //连接五个副选项按钮和其实现函数

    connect(this->btnBallLeft,SIGNAL(clicked(bool)),this,SLOT(BallLeft()));
    connect(this->btnBallRight,SIGNAL(clicked(bool)),this,SLOT(BallRight()));
    connect(this->btnTimeLeft,SIGNAL(clicked(bool)),this,SLOT(TimeLeft()));
    connect(this->btnTimeRight,SIGNAL(clicked(bool)),this,SLOT(TimeRight()));

    labRecord->setGeometry(0,0,150,40);
    labRecord->setPixmap(QPixmap(":/logo/Image/choose.png"));

}

void game::init_gaming()
{
    for(int i=0;i<6;i++){
        connect(this->btnMyTeam[i],SIGNAL(pressed()),&SignalMapper,SLOT(map()));
        SignalMapper.setMapping(this->btnMyTeam[i],i);
    }
    for(int i=6;i<12;i++){
        connect(this->btnRivalTeam[i-6],SIGNAL(pressed()),&SignalMapper,SLOT(map()));
        SignalMapper.setMapping(this->btnRivalTeam[i-6],i);
    }
    connect(&SignalMapper,SIGNAL(mapped(int)),this,SLOT(PressEvent(int)));

    for(int i=0;i<12;i++){
        if(i<6)
            connect(this->btnMyTeam[i],SIGNAL(released()),this,SLOT(ReleaseEvent()));
        else
            connect(this->btnRivalTeam[i-6],SIGNAL(released()),this,SLOT(ReleaseEvent()));
    }

    btnStop->setGeometry(0,0,40,40);
    btnBTG->setGeometry(250,200,100,100);
    btnETG->setGeometry(450,200,100,100);
    btnMyMove->setGeometry(200,470,80,30);
    btnRivalMove->setGeometry(520,470,80,30);
    labmeng->setGeometry(0,0,800,500);

    btnStop->setIconSize(QSize(40,40));
    btnBTG->setIconSize(QSize(100,100));
    btnETG->setIconSize(QSize(100,100));
    btnMyMove->setIconSize(QSize(80,30));
    btnRivalMove->setIconSize(QSize(80,30));

    btnStop->setFlat(true);
    btnBTG->setFlat(true);
    btnETG->setFlat(true);

    btnStop->setIcon(QIcon(":/logo/Image/stop.png"));
    btnBTG->setIcon(QIcon(":/logo/Image/BTG.png"));
    btnETG->setIcon(QIcon(":/logo/Image/ETG.png"));
    btnMyMove->setIcon(QPixmap(":/logo/Image/btnMove.png"));
    btnRivalMove->setIcon(QPixmap(":/logo/Image/btnMove.png"));

    connect(this->btnStop,SIGNAL(clicked(bool)),this,SLOT(btnStop_click()));
    connect(this->btnBTG,SIGNAL(clicked(bool)),this,SLOT(btnBTG_click()));
    connect(this->btnETG,SIGNAL(clicked(bool)),this,SLOT(btnETG_click()));
    connect(this->btnMyMove,SIGNAL(clicked(bool)),this,SLOT(whoMove()));
    connect(this->btnRivalMove,SIGNAL(clicked(bool)),this,SLOT(whoMove()));
    connect(&timeline,SIGNAL(frameChanged(int)),this,SLOT(IdentifyColl()));
}

void game::refont(int a)
{
    palette.setColor(QPalette::ButtonText,Qt::gray);
    fo.setPointSize(a);
    btnPreMy->setFont(fo);
    btnPreGuy->setFont(fo);
    btnPreMode->setFont(fo);
    btnPreSelection->setFont(fo);
    btnPreOther->setFont(fo);
    btnPrePlace->setFont(fo);

    btnPreMy->setPalette(palette);
    btnPreGuy->setPalette(palette);
    btnPreMode->setPalette(palette);
    btnPreSelection->setPalette(palette);
    btnPreOther->setPalette(palette);
    btnPrePlace->setPalette(palette);

}

void game::record(int a)
{
    switch(Record[a]){
    case 1:
        labRecord->setGeometry(50,120,200,50);
        btnPre1_click();
        break;
    case 2:
        labRecord->setGeometry(50,190,200,50);
        btnPre2_click();
        break;
    case 3:
        labRecord->setGeometry(50,260,200,50);
        btnPre3_click();
        break;
    case 4:
        labRecord->setGeometry(50,330,200,50);
        btnPre4_click();
        break;
    case 5:
        labRecord->setGeometry(50,410,200,50);
        btnPre5_click();
        break;
    }
    labRecord->show();
}

int game::encryption(int inf)
{

    int aa=0;
    while(aa==0){
    aa=rand()%10;
    }
    return inf*aa*10+aa;
}

int game::decode(int inf)
{
    int aa=inf%10;
    return (inf/10)/aa;
}

void game::setSelection()
{
    QString m;
    m=labSelectBall->text();

    if(m=="1 Ball") Ginf.setWinBall(1);
    else
        if(m=="2 Balls")  Ginf.setWinBall(2);
        else
            if(m=="3 Balls") Ginf.setWinBall(3);
            else Ginf.setWinBall(-1);


    m=labSelectTime->text();
    if(m=="1 minute") Ginf.setGameTime(60);
    else
        if(m=="2 minutes")  Ginf.setGameTime(120);
        else
            if(m=="3 minutes") Ginf.setGameTime(180);
            else
                if(m=="4 minutes") Ginf.setGameTime(240);
                else
                    if(m=="5 minutes") Ginf.setGameTime(300);

}

void game::setGuyXy()
{
    Ginf.setMyTeam(Ginf.getTeam(1));
    Ginf.setRivalTeam(Ginf.getTeam(2));
    for(int i=0;i<6;i++){
    btnMyTeam[i]->setGeometry(Ginf.MyGuys[i].getX(),Ginf.MyGuys[i].getY(),50,50);
    Ginf.MyGuys[i].setVelocity(0);
    btnRivalTeam[i]->setGeometry(Ginf.RivalGuys[i].getX(),Ginf.RivalGuys[i].getY(),50,50);
    Ginf.RivalGuys[i].setVelocity(0);
    }

    btnBall->setGeometry(390,265,20,20);
}

void game::setGuyKind()
{
    QPixmap qp1;
    QPixmap qp2;

    qp1.scaled(QSize(100,100));

    switch(Ginf.MyGuys[0].getGuyKind()){
    case classic:
        qp1=QPixmap(":/guy/Image/classic.png");
        break;
    case wood:
        qp1=QPixmap(":/guy/Image/wood.png");
        break;
    case metal:
        qp1=QPixmap(":/guy/Image/metal.png");
        break;
    }

    switch(Ginf.RivalGuys[0].getGuyKind()){
    case classic:
        qp2=QPixmap(":/guy/Image/classic2.png");
        break;
    case wood:
        qp2=QPixmap(":/guy/Image/wood2.png");
        break;
    case metal:
        qp2=QPixmap(":/guy/Image/metal2.png");
        break;
    }

    for (int i=0;i<6;i++){
        btnMyTeam[i]->setIconSize(QSize(50,50));
        btnMyTeam[i]->setIcon(qp1);
        btnMyTeam[i]->setFlat(true);
        Ginf.MyGuys[i].setFriction(Ginf.getGamePlace());

        btnRivalTeam[i]->setIconSize(QSize(50,50));
        btnRivalTeam[i]->setIcon(qp2);
        btnRivalTeam[i]->setFlat(true);
        Ginf.RivalGuys[i].setFriction(Ginf.getGamePlace());
    }

    btnBall->setFlat(true);
    btnBall->setIconSize(QSize(20,20));
    btnBall->setIcon(QPixmap(":/guy/Image/ball.png"));
    Ginf.football.setFriction(Ginf.getGamePlace());

}

void game::setPlace()
{
    switch(Ginf.getGamePlace()){
    case grass:
        this->setStyleSheet("#game { \nborder-image: url(:/ground/Image/grass.png);\n} \n#game * { \nborder-image:url(); \n}");
        *pixmapBack=QPixmap(":/ground/Image/grass.png");
        break;
    case cement:
        this->setStyleSheet("#game { \nborder-image: url(:/ground/Image/cement.png);\n} \n#game * { \nborder-image:url(); \n}");
        *pixmapBack=QPixmap(":/ground/Image/cement.png");
        break;
    case galaxy:
        this->setStyleSheet("#game { \nborder-image: url(:/ground/Image/galaxy.png);\n} \n#game * { \nborder-image:url(); \n}");
        *pixmapBack=QPixmap(":/ground/Image/galaxy.png");
        break;
    case ice:
        this->setStyleSheet("#game { \nborder-image: url(:/ground/Image/ice.png);\n} \n#game * { \nborder-image:url(); \n}");
        *pixmapBack=QPixmap(":/ground/Image/ice.png");
        break;
    }
}

void game::goal()
{
    timeline.stop();
    GameTimer.stop();
    btnGoal->setGeometry(250,100,300,300);
    btnGoal->setIconSize(QSize(300,300));
    btnGoal->setFlat(true);
    if(Ginf.getMyGoal()==Ginf.getWinBall()||(Ginf.getMyGoal()>Ginf.getRivalGoal()&&Ginf.getGameTime()==0)){
        btnGoal->setIcon(QPixmap(":/logo/Image/win1.png"));
        btnGoal->show();
        Timer.start(3000);
        connect(&Timer,SIGNAL(timeout()),this,SLOT(menu()));
    }
    else if(Ginf.getRivalGoal()==Ginf.getWinBall()||(Ginf.getMyGoal()<Ginf.getRivalGoal()&&Ginf.getGameTime()==0)){
        btnGoal->setIcon(QPixmap(":/logo/Image/win2.png"));
        btnGoal->show();
        Timer.start(3000);
        connect(&Timer,SIGNAL(timeout()),this,SLOT(menu()));
    }
    else if(Ginf.getMyGoal()==Ginf.getRivalGoal()&&Ginf.getGameTime()==0){
        btnGoal->setIcon(QPixmap(":/logo/Image/bothwin.png"));
        btnGoal->show();
        Timer.start(3000);
        connect(&Timer,SIGNAL(timeout()),this,SLOT(menu()));
    }
    else{
        setGuyXy();
        for(int i=0;i<6;i++){
            Ginf.MyGuys[i].setVelocity(0);
            Ginf.RivalGuys[i].setVelocity(0);
        }
        Ginf.football.setVelocity(0);
        whoMove();
    }
}

void game::whoMove()
{
    switch(Ginf.getGameMode()){
    case now:
        WaitMyMove();
        break;
    case round:
        if(WhoGaming==my){
            WaitRivalMove();
            return;
        }
        if(WhoGaming==other){
            WaitMyMove();
            return;
        }
        break;
    case total:
        if(WhoGaming==3){
            btnMyMove->show();
            WaitMyMove();
            return;
        }
        if(WhoGaming==my){
            MyTimer.stop();
            btnRivalMove->show();
            btnMyMove->hide();
            WaitRivalMove();
            return;
        }
        if(WhoGaming==other){
            RivalTimer.stop();
            IsRivalPress=false;
            btnRivalMove->hide();
            GameRuning();
            return;}
        break;
    case time:
        if(MyTimer.isActive()==true||(RivalTimer.isActive()==false&&WhoGaming==3)){WaitMyMove();return;}
        if(RivalTimer.isActive()==true||(MyTimer.isActive()==false&&WhoGaming==2)){WaitRivalMove();return;}
        break;
    case strategy:
        if(WhoGaming==my){
            IsMyPaint=false;
            IsMyPress=false;
            btnMyMove->hide();
            MyTimer.stop();
            GameRuning();
            return;
        }
        if(WhoGaming==other){
            IsRivalPaint=false;
            IsRivalPress=false;
            btnRivalMove->hide();
            RivalTimer.stop();
            GameRuning();
            return;
        }
        if(WhoGaming==2) {btnMyMove->show();WaitMyMove();return;}
        if(WhoGaming==3){btnRivalMove->show();WaitRivalMove();return;}
        break;
    }
}

void game::makeBGM()
{
    playerlist.setPlaybackMode(QMediaPlaylist::Loop);
    player.setPlaylist(&playerlist);
    player.setMedia(QUrl("qrc:/music/Image/Animal Kingdom - Get Away With It.mp3"));
    player.setVolume(60);
    player.play();
}

void game::WaitMyMove()
{
    if(Ginf.getGameMode()==total||Ginf.getGameMode()==strategy)btnMyMove->show();

    WhoGaming=my;
    IsMyPress=true;
    IsRivalPress=false;
    connect(&MyTimer,SIGNAL(timeout()),this,SLOT(whoMove()));
    MyTimer.setSingleShot(true);
    if(MyTimer.isActive()==false)MyTimer.start(15000);
}

void game::WaitRivalMove()
{
    WhoGaming=other;
    IsRivalPress=true;
    IsMyPress=false;
    connect(&RivalTimer,SIGNAL(timeout()),this,SLOT(whoMove()));
    RivalTimer.setSingleShot(true);
    if(RivalTimer.isActive()==false)RivalTimer.start(15000);
}

void game::IdentifyColl()
{
    double UpdateTime=double(timeline.updateInterval())/1000;

    if(AllStop()==true){
        if(timeline.state()==QTimeLine::Running)timeline.stop();

        if(labgm->text()=="on"){
        CollPlayer.setMedia(QUrl("qrc:/music/Image/Coll.wav"));
        CollPlayer.setVolume(60);
        CollPlayer.play();}

        if(WhoGaming==my)WhoGaming=2;
        else if(WhoGaming==other)WhoGaming=3;
        whoMove();
        return;
    }

    QPushButton *btnwhy;
    QPushButton *btnhow;
    QPushButton *btncoll;
    circle *guywhy;
    circle *guyhow;
    circle *guycoll;
    double s1=0;
    double s2=0;
    double s=0;
    double t_guy=100000;
    double t_wall=0;
    double far2=0;
    double fix_velocity=0;
    double fix_angle=0;
    double jia_angle=0;
    double location_angle=0;
    const double pi=std::atan(1)*4;

    for(int i=0;i<=12;i++){

        t_guy=100000;
        if(i<=5) {btnwhy=btnMyTeam[i];
                  guywhy=&Ginf.MyGuys[i];
        }
        if(i>5&&i<=11){btnwhy=btnRivalTeam[i-6];
                       guywhy=&Ginf.RivalGuys[i-6];
        }
        if(i==12){
            btnwhy=btnBall;
            guywhy=&Ginf.football;
        }
        if(guywhy->getVelocity()==0)continue;
        else{
            guywhy->setXy(btnwhy->x()+guywhy->getR(),btnwhy->y()+guywhy->getR());
            t_wall=std::min((std::abs(guywhy->getAngle())<=pi/2 ? 710-guywhy->getX() : guywhy->getX()-90)/std::abs(std::cos(guywhy->getAngle()))/guywhy->getVelocity(),(guywhy->getAngle()>=0 ? guywhy->getY()-90 : 475-guywhy->getY())/std::abs(std::sin(guywhy->getAngle()))/guywhy->getVelocity());

         for(int j=0;j<13;j++){
             if(i==j) continue;

             if(j<=5) {btnhow=btnMyTeam[j];
                       guyhow=&Ginf.MyGuys[j];
                 }
             if(j>5&&i<=11){btnhow=btnRivalTeam[j-6];
                            guyhow=&Ginf.RivalGuys[j-6];
                 }
             if(j==12){
                     btnhow=btnBall;
                     guyhow=&Ginf.football;
                      }
             guyhow->setXy(btnhow->x()+guyhow->getR(),btnhow->y()+guyhow->getR());
//if(std::pow(guywhy->getVelocity()*std::cos(guywhy->getAngle())*UpdateTime+guywhy->getX()-guyhow->getVelocity()*std::cos(guyhow->getAngle())*UpdateTime+guyhow->getX(),2)+std::pow(guywhy->getVelocity()*std::sin(guywhy->getAngle())*UpdateTime+guywhy->getY()-guyhow->getVelocity()*std::sin(guyhow->getAngle())*UpdateTime-guyhow->getY(),2)<=std::pow(guywhy->getR()+guyhow->getR(),2))

             if(guyhow->getVelocity()==0){
                 fix_angle=guywhy->getAngle();
                 fix_velocity=guywhy->getVelocity();
             }
             //先判断静态的瓶盖会不会碰撞

            if(guyhow->getVelocity()!=0) {
                 double angle_180=(guyhow->getAngle()>0 ? guyhow->getAngle()- pi:guyhow->getAngle()+pi);
                 //计算被碰物体的速度的反向
                 fix_velocity=std::sqrt(std::pow(guywhy->getVelocity(),2)+std::pow(guyhow->getVelocity(),2)-2*guywhy->getVelocity()*guyhow->getVelocity()*std::cos(angle_180-guywhy->getAngle()));
                 //计算合成速度
                 fix_angle=calculateAngle(0,0,guywhy->getVelocity()*std::cos(guywhy->getAngle())+guyhow->getVelocity()*std::cos(angle_180),-guywhy->getVelocity()*std::sin(guywhy->getAngle())-guyhow->getVelocity()*std::sin(angle_180));
                 //计算合成后的速度角度
            }

             location_angle=calculateAngle(guywhy->getX(),guywhy->getY(),guyhow->getX(),guyhow->getY());
             //计算位置直线的倾斜角
             jia_angle=((std::abs(fix_angle-location_angle)>pi) ? 2*pi-std::abs(fix_angle-location_angle) : std::abs(fix_angle-location_angle));
             //计算夹角

             far2=std::pow(guywhy->getX()-guyhow->getX(),2)+std::pow(guywhy->getY()-guyhow->getY(),2);
             //计算静态瓶盖与运动瓶盖距离的平方

             //如果垂线大于2r或夹角大于90度，判定为不会碰撞
             if(std::sqrt(far2)*std::sin(jia_angle)<guywhy->getR()+guyhow->getR()&&jia_angle<0.5*pi&&fix_velocity!=0) {
                 s1=std::sqrt(far2-std::pow(std::sqrt(far2)*std::sin(jia_angle),2));
                 s2=std::sqrt(std::pow(guywhy->getR()+guyhow->getR(),2)-std::pow(std::sqrt(far2)*std::sin(jia_angle),2));
                 s=s1-s2 ;

                 if(t_guy>s/fix_velocity){
                     btncoll=btnhow;
                     guycoll=guyhow;

                     t_guy=s/fix_velocity;
                 }    //判定为会撞
             }
        }



     if(t_guy<=t_wall&&t_guy<UpdateTime) {
         guywhy->setXy(btnwhy->x()+t_guy*guywhy->getVelocity()*std::cos(guywhy->getAngle()),btnwhy->y()-t_guy*guywhy->getVelocity()*std::sin(guywhy->getAngle()));
         guycoll->setXy(btncoll->x()+t_guy*guycoll->getVelocity()*std::cos(guycoll->getAngle()),btncoll->y()-t_guy*guycoll->getVelocity()*std::sin(guycoll->getAngle()));

         btnwhy->setGeometry(guywhy->getX(),guywhy->getY(),2*guywhy->getR(),2*guywhy->getR());
         btncoll->setGeometry(guycoll->getX(),guycoll->getY(),2*guycoll->getR(),2*guycoll->getR());

         Coll(guywhy,guycoll);
         i=i-1;continue;

         guywhy->setXy(btnwhy->x()+(UpdateTime-t_guy)*guywhy->getVelocity()*std::cos(guywhy->getAngle()),btnwhy->y()-(UpdateTime-t_guy)*guywhy->getVelocity()*std::sin(guywhy->getAngle()));
         guycoll->setXy(btncoll->x()+(UpdateTime-t_guy)*guycoll->getVelocity()*std::cos(guycoll->getAngle()),btncoll->y()-(UpdateTime-t_guy)*guycoll->getVelocity()*std::sin(guycoll->getAngle()));

     }
     else if(t_guy>t_wall&&t_wall<UpdateTime){
         guywhy->setXy(btnwhy->x()+t_wall*guywhy->getVelocity()*std::cos(guywhy->getAngle())+guywhy->getR(),btnwhy->y()-t_wall*guywhy->getVelocity()*std::sin(guywhy->getAngle())+guywhy->getR());

         CollWall(guywhy);
         //i=i-1;continue;
         guywhy->setXy(btnwhy->x()+(UpdateTime-t_wall)*guywhy->getVelocity()*std::cos(guywhy->getAngle()),btnwhy->y()-(UpdateTime-t_wall)*guywhy->getVelocity()*std::sin(guywhy->getAngle()));

     }
     else{
       guywhy->setXy(btnwhy->x()+UpdateTime*guywhy->getVelocity()*std::cos(guywhy->getAngle()),btnwhy->y()-UpdateTime*guywhy->getVelocity()*std::sin(guywhy->getAngle()));

       guywhy->setVelocity(guywhy->getVelocity()-(guywhy->getFriction()/guywhy->getWeight())*UpdateTime*20);
       guywhy->setVelocity(guywhy->getVelocity()<0?0:guywhy->getVelocity());
       //计算减速后的速度
     }

     btnwhy->setGeometry(guywhy->getX(),guywhy->getY(),2*guywhy->getR(),2*guywhy->getR());
     //如果直线距离小于两个半径加40ms移动距离


         }
}}


void game::WaitForMove()
{
        if(GuyCounter<=6&&IsMyPress==true){
            IsMyPaint=true;
            return;
        }
        if(GuyCounter>6&&IsRivalPress==true){
            IsRivalPaint=true;
            return;
        }
}

void game::Coll(circle *guywhy,circle *guyhow)
{
    double location_angle=0;
    double jia_why=0;
    double jia_how=0;
    double v_why=0;
    double v_how=0;
    double afterV_why=0;
    double afterV_how=0;
    double pi=std::atan(1)*4;

        location_angle=calculateAngle(guywhy->getX()+guywhy->getR(),guywhy->getY()+guywhy->getR(),guyhow->getX()+guyhow->getR(),guyhow->getY()+guyhow->getR());
        jia_why=std::abs(guywhy->getAngle()-location_angle);
        //计算夹角
        v_why=guywhy->getVelocity()*std::cos(jia_why);

        jia_how=std::abs(guyhow->getAngle()-location_angle);
        v_how=guyhow->getVelocity()*std::cos(jia_how);

        afterV_how=(2*guywhy->getWeight()*v_why+(guyhow->getWeight()-guywhy->getWeight())*v_how)/(guywhy->getWeight()+guyhow->getWeight());
        afterV_why=((guywhy->getWeight()-guyhow->getWeight())*v_why+2*guyhow->getWeight()*v_how)/(guywhy->getWeight()+guyhow->getWeight());

        guywhy->setAngle(calculateAngle(0,0,guywhy->getVelocity()*std::cos(guywhy->getAngle())+(afterV_why-v_why)*std::cos(location_angle),-guywhy->getVelocity()*std::sin(guywhy->getAngle())+(afterV_why-v_why)*std::sin(location_angle)));
        guyhow->setAngle(calculateAngle(0,0,guyhow->getVelocity()*std::cos(guyhow->getAngle())+(afterV_how-v_how)*std::cos(-location_angle),-guyhow->getVelocity()*std::sin(guyhow->getAngle())+(afterV_how-v_how)*std::sin(-location_angle)));

        guywhy->setVelocity(std::sqrt(std::pow(guywhy->getVelocity()*std::sin(jia_why),2)+std::pow(afterV_why,2)));
        guyhow->setVelocity(std::sqrt(std::pow(guyhow->getVelocity()*std::sin(jia_how),2)+std::pow(afterV_how,2)));

        for(int i=0;i<6;i++){
            for(int j=0;j<13;j++){
            Ginf.MyGuys[i].IsColl[j]=true;
            Ginf.RivalGuys[i].IsColl[j]=true;
            Ginf.football.IsColl[j]=true;
            }
        }
QTextStream cout(stdout);
        cout<<v_why<<";"<<v_how<<";"<<";"<<afterV_why<<";"<<afterV_how<<";"<<guywhy->getAngle()<<";"<<guyhow->getAngle()<<endl;
}

void game::CollWall(circle *guywhy)
{
    double pi=std::atan(1)*4;
    double t_left=(std::abs(guywhy->getAngle())<=pi/2 ? 710-guywhy->getX() : guywhy->getX()-90)/(std::abs(std::cos(guywhy->getAngle()))*guywhy->getVelocity());
    double t_up=(guywhy->getAngle()>=0 ? (guywhy->getY()-90) : (475-guywhy->getY()))/(std::abs(std::sin(guywhy->getAngle()))*guywhy->getVelocity());

    if(t_left<=t_up&&t_left>=0){
        double t_y=guywhy->getY()+guywhy->getR()+t_left*guywhy->getVelocity()*std::sin(guywhy->getAngle());
        if(t_y<230||t_y>360||guywhy->getR()==25) guywhy->setAngle(guywhy->getAngle()>=0?pi-guywhy->getAngle():-pi-guywhy->getAngle());
        else{
                if(guywhy->getX()<400)Ginf.setRivalGoal(Ginf.getRivalGoal()+1);
                else Ginf.setMyGoal(Ginf.getMyGoal()+1);
                goal();
        }
    }
    if(t_left>t_up&&t_up>=0) guywhy->setAngle(-guywhy->getAngle());
}

bool game::AllStop()
{
    for(int i=0;i<6;i++){
        if(Ginf.MyGuys[i].getVelocity()!=0)
            return false;
        if(Ginf.RivalGuys[i].getVelocity()!=0)
            return false;
    }
    if(Ginf.football.getVelocity()!=0)
        return false;
    return true;
}

double game::calculateAngle(double mx, double my, double cx, double cy)
{
    double tanAngle;
    double angle;
    double pi=std::atan(1)*4;

    tanAngle=std::abs((my-cy)/(mx-cx));
    //计算倾斜角

    if(my>cy&&mx<cx) angle=std::atan(tanAngle);
    else if(my>cy&&mx>cx) angle=std::atan(-(tanAngle))+pi;
         else if(my<cy&&mx<cx) angle=(-std::atan(tanAngle));
              else if(my<cy&&mx>cx) angle=(-std::atan(-tanAngle))-pi;
                   else if(my>cy&&mx==cx) angle=pi/2;
                        else if (my<cy&&mx==cx) angle=pi/(-2);
                             else if (my==cy&&mx>cx) angle=pi;
                                  else if (my==cy&&mx<cx) angle=0;
    //计算角度

    return angle;
}

void game::paintEvent(QPaintEvent *)
{   
    if(IsGaming==false){}
    else {
        QPixmap *pixmap=new QPixmap(800,500);    //创建绘图设备
        *pixmap=*pixmapBack;                     //把背景图片作为绘图背景

        //绘制瞄准的画面
        if(IsMyPaint==true||IsRivalPaint==true){
            QPoint mouse;                            //用于记录鼠标的坐标
            QPoint center;                           //用于记录圆的圆心坐标
            QPushButton *btn;                        //用于记录被按下的按钮
            int radiu;                               //用于记录圆的半径
            int rx;                                  //用于记录直线末端x坐标
            int ry;                                  //用于记录直线末端y坐标

            mouse=this->mapFromGlobal(this->cursor().pos()); //把鼠标坐标赋值给QPoint变量mouse

            if(GuyCounter<=6) btn=btnMyTeam[GuyCounter-1];
            else btn=btnRivalTeam[GuyCounter-6-1];            //传递被按下的按钮信息

            center=QPoint(btn->x()+Ginf.MyGuys[0].getR(),btn->y()+Ginf.MyGuys[0].getR());
            radiu=std::sqrt(std::pow(btn->x()+Ginf.MyGuys[0].getR()-mouse.x(),2)+std::pow(btn->y()+Ginf.MyGuys[0].getR()-mouse.y(),2));
            radiu=radiu>100 ? 100 : radiu;
            //记录中心点坐标，以及计算半径（不大于100）
            rx=center.x()-mouse.x();
            ry=center.y()-mouse.y();
            if(std::pow(center.x()-mouse.x(),2)+std::pow(center.y()-mouse.y(),2)>std::pow(100,2)){
                rx=100*std::cos(calculateAngle(mouse.x(),mouse.y(),center.x(),center.y()));
                ry=-100*std::sin(calculateAngle(mouse.x(),mouse.y(),center.x(),center.y()));
            }//记录中心点和圆与直线交点坐标的x和y的差值

            painter.begin(pixmap);                                 //设置绘图设备
            painter.setPen(QPen(Qt::red,6,Qt::SolidLine));         //设置画直线的画笔
            painter.drawLine(center.x()-rx,center.y()-ry,center.x()+rx,center.y()+ry);  //画直线
            painter.setPen(QPen(Qt::blue,6,Qt::SolidLine));        //设置画圆的画笔
            painter.drawEllipse(center,radiu,radiu);               //画以中心点为圆心的圆
            painter.end();                                         //结束绘画

            if(GuyCounter<=6) {
                Ginf.MyGuys[GuyCounter-1].setVelocity(radiu*5);
                Ginf.MyGuys[GuyCounter-1].setAngle(calculateAngle(mouse.x(),mouse.y(),center.x(),center.y()));
            }
            else {
                Ginf.RivalGuys[GuyCounter-6-1].setVelocity(radiu*5);
                Ginf.RivalGuys[GuyCounter-6-1].setAngle(calculateAngle(mouse.x(),mouse.y(),center.x(),center.y()));
            }
        }else {}

        //接下来绘制击球时间显示条以及双方比赛信息
        painter.begin(pixmap);
        painter.setPen(QPen(Qt::black,6,Qt::SolidLine));
        static double mymsec=0,rivalmsec=0;
        mymsec=MyTimer.isActive()==true?(15000-MyTimer.remainingTime())*0.016:mymsec;
        painter.drawLine(60+mymsec,45,300,45);
        painter.drawLine(300,45,330,5);
        painter.drawLine(470,5,500,45);
        rivalmsec=RivalTimer.isActive()==true?(15000-RivalTimer.remainingTime())*0.016:(MyTimer.isActive()==true)?0:rivalmsec;
        painter.drawLine(500,45,740-rivalmsec,45);

        painter.setFont(this->font());
        painter.drawText(QRect(70,3,180,40),Qt::AlignHCenter,Ginf.getMyName());
        painter.drawText(QRect(250,3,50,40),Qt::AlignHCenter,QString::number(Ginf.getMyGoal()));
        painter.drawText(QRect(500,3,50,40),Qt::AlignHCenter,QString::number(Ginf.getRivalGoal()));
        painter.drawText(QRect(570,3,180,40),Qt::AlignHCenter,Ginf.getRivalName());
        painter.setFont(QFont("宋体",15, QFont::Bold, true));
        painter.drawText(QRect(340,1,120,19),Qt::AlignHCenter,"LEFT TIME");

        painter.drawText(QRect(350,20,20,20),"0");
        painter.drawText(QRect(370,20,20,20),QString::number(Ginf.getGameTime()/60));
        painter.drawText(QRect(390,20,20,20),": ");
        painter.drawText(QRect(410,20,20,20),QString::number((Ginf.getGameTime()%60)/10));
        painter.drawText(QRect(430,20,20,20),QString::number((Ginf.getGameTime()%60)%10));

        painter.end();

        labPaint->setPixmap(*pixmap);
        labPaint->show();

        delete pixmap;
        }
}

void game::mouseReleaseEvent(QMouseEvent *)
{
    switch(Ginf.getGameMode()){
    case now:
        if(IsMyPaint==true){
            IsMyPress=false;
            IsMyPaint=false;
            labPaint->hide();
            MyTimer.stop();
            WaitRivalMove();
            return;
        }
        if(IsRivalPaint==true){
            IsRivalPress=false;
            IsRivalPaint=false;
            labPaint->hide();
            RivalTimer.stop();
            GameRuning();
            return;
        }
        break;
    case round:
        if(WhoGaming==my){
            IsMyPaint=false;
            labPaint->hide();
            MyTimer.stop();
            GameRuning();
        }
        if(WhoGaming==other){
            IsRivalPaint=false;
            labPaint->hide();
            RivalTimer.stop();
            GameRuning();
        }
        break;
    case total:
        if(WhoGaming==my){
            WaitMyMove();
            IsMyPaint=false;
        }
        if(WhoGaming==other){
            WaitRivalMove();
            IsRivalPaint=false;
        }
        break;
    case time:
        if(WhoGaming==my){
            IsMyPress=false;
            IsMyPaint=false;
            labPaint->hide();
            GameRuning();
        }
        if(WhoGaming==other){
            IsRivalPress=false;
            IsRivalPaint=false;
            labPaint->hide();
            GameRuning();
        }
        break;
    case strategy:
        if(WhoGaming==my){
            IsMyPaint=false;
            WaitMyMove();
        }
        if(WhoGaming==other){
            IsRivalPaint=false;
            WaitRivalMove();
        }
        break;

   }
}

