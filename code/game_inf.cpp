#include "game_inf.h"

game_inf::game_inf()
{
    WinBall=0;
    GameMode=0;
    GamePlace=0;
    MyGoal=0;
    RivalGoal=0;
    MyName="PLAY 1";
    RivalName="PLAY 2";

}

void game_inf::setMyTeam(int inf){
    team[0]=inf;
    switch (inf){
    case 132:   //设置132阵型的瓶盖坐标
        MyGuys[0].setXy(80,255);

        for(int i=1;i<4;i++){
            MyGuys[i].setXy(175,35+i*110);
        }

        for(int i=4;i<6;i++){
        MyGuys[i].setXy(300,30+(i-3)*150);
        }
        break;

    case 123:      //设置123阵型的瓶盖坐标
        MyGuys[0].setXy(80,255);

        for(int i=1;i<3;i++){
            MyGuys[i].setXy(175,30+i*150);

        }

        for(int i=3;i<6;i++){
            MyGuys[i].setXy(300,35+(i-2)*110);
        }
        break;

    case 141:     //设置141阵型的瓶盖坐标
        MyGuys[0].setXy(80,255);
        MyGuys[1].setXy(170,205);
        MyGuys[2].setXy(170,305);
        MyGuys[3].setXy(220,130);
        MyGuys[4].setXy(220,380);
        MyGuys[5].setXy(300,255);

        break;

    case 1221:     //设置1221阵型的瓶盖坐标
        MyGuys[0].setXy(80,255);
        MyGuys[1].setXy(150,180);
        MyGuys[2].setXy(150,330);
        MyGuys[3].setXy(250,180);
        MyGuys[4].setXy(250,330);
        MyGuys[5].setXy(310,255);

        break;

    case 321:    //设置321阵型的瓶盖的坐标值
        for(int i=0;i<3;i++){
            MyGuys[i].setXy(80,35+(i+1)*110);
        }

        for(int i=3;i<5;i++){
            MyGuys[i].setXy(180,30+(i-2)*150);

        }

        MyGuys[5].setXy(300,255);
        break;

    }
}

void game_inf::setRivalTeam(int inf){
    team[1]=inf;
    switch (inf){
    case 132:   //设置132阵型的瓶盖坐标
        RivalGuys[0].setXy(672,255);

        for(int i=1;i<4;i++){
            RivalGuys[i].setXy(570,35+i*110);
        }

        for(int i=4;i<6;i++){
        RivalGuys[i].setXy(445,30+(i-3)*150);
        }
        break;

    case 123:      //设置123阵型的瓶盖坐标
        RivalGuys[0].setXy(672,255);

        for(int i=1;i<3;i++){
            RivalGuys[i].setXy(570,30+i*150);
        }

        for(int i=3;i<6;i++){
            RivalGuys[i].setXy(445,35+(i-2)*110);
        }
        break;

    case 141:     //设置141阵型的瓶盖坐标
        RivalGuys[0].setXy(672,255);
        RivalGuys[1].setXy(600,205);
        RivalGuys[2].setXy(600,305);
        RivalGuys[3].setXy(550,130);
        RivalGuys[4].setXy(550,380);
        RivalGuys[5].setXy(450,255);
        break;

    case 1221:     //设置1221阵型的瓶盖坐标
        RivalGuys[0].setXy(672,255);
        RivalGuys[1].setXy(600,180);
        RivalGuys[2].setXy(600,330);
        RivalGuys[3].setXy(510,180);
        RivalGuys[4].setXy(510,330);
        RivalGuys[5].setXy(450,255);
        break;

    case 321:    //设置321阵型的瓶盖的坐标值
        for(int i=0;i<3;i++){
            RivalGuys[i].setXy(672,35+(i+1)*110);
        }

        for(int i=3;i<5;i++){
            RivalGuys[i].setXy(570,30+(i-2)*150);

        }
        RivalGuys[5].setXy(450,255);
        break;

    }
}

void game_inf::setWinBall(int wb)
{
    this->WinBall=wb;
}

void game_inf::setGamePlace(int gp)
{
    this->GamePlace=gp;

}

void game_inf::setGameMode(int gm)
{
    this->GameMode=gm;
}


void game_inf::setGameTime(int ti)
{
    GameTime=ti;
}

void game_inf::setMyName(QString smn)
{
    MyName=smn;
}

void game_inf::setRivalName(QString srn)
{
    RivalName=srn;
}

void game_inf::setMyGoal(int inf)
{
    MyGoal=inf;
}

void game_inf::setRivalGoal(int inf)
{
    RivalGoal=inf;
}

int game_inf::getWinBall()
{
    return WinBall;
}


int game_inf::getGamePlace()
{
    return GamePlace;
}

int game_inf::getGameMode()
{
    return GameMode;
}

int game_inf::getGameTime()
{
    return GameTime;
}

int game_inf::getMyGoal()
{
    return MyGoal;
}

int game_inf::getRivalGoal()
{
    return RivalGoal;
}

int game_inf::getTeam(int i)
{
    if(i==1) return team[0];
    else return team[1];
}

QString game_inf::getMyName()
{
    return MyName;
}

QString game_inf::getRivalName()
{
    return RivalName;
}




guy::guy(){

    GuyKind=0;
    IsMy=true;
    setR(25);

}

circle::circle()
{
    weight=0;
    friction=0;
    velocity=0;
    angle=0;
    x=0;
    y=0;
    for(int i=0;i<13;i++){
        IsColl[i]=true;
    }
}

void circle::setR(int sr)
{
    R=sr;
}

void circle::setXy(double cx,double cy)
{
    this->x=cx;
    this->y=cy;
}

void guy::setguykind(int gk)
{
    GuyKind=gk;
    setWeight(gk);
}

int guy::getGuyKind()
{
    return GuyKind;
}

void circle::setVelocity(double sv)
{
    this->velocity=sv;
}

void circle::setAngle(double sa)
{
    this->angle=sa;
}

void circle::setWeight(int sw)
{
    switch (sw){
    case classic:
        weight=20;
    case wood:
        weight=30;
        break;
    case metal:
        weight=50;
    case ballball:
        weight=10;
    }
}

void circle::setFriction( int e)
{
    switch(e){
    case grass:
        friction=0.7*weight*10;
        break;
    case cement:
        friction=0.4*weight*10;
        break;
    case galaxy:
        friction=0.4*weight*10;
        break;
    case ice:
        friction=0.2*weight*10;
        break;

    }
}


int circle::getR()
{
    return R;
}

double circle::getX()
{
    return this->x;
}

double circle::getY()
{
    return this->y;
}

int circle::getWeight()
{
    return this->weight;
}


double circle::getFriction()
{
    return this->friction;
}

double circle::getVelocity()
{
    return velocity;
}

double circle::getAngle()
{
    return angle;
}

ball::ball()
{
    setWeight(3);
    setVelocity(0);
    setAngle(0);
    setR(10);
    setXy(400,275);
}
