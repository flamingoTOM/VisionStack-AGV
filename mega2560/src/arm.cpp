#include "arm.h"

robotarm::robotarm(HardwareSerial &A)  //拷贝构造函数？构造函数用于初始化
{
    this->ServoController_p = new LobotServoController(A);  //分配新的内存空间
}

robotarm::~robotarm()    //析构函数
{
    delete ServoController_p;  //释放内存？作用
}



/*-------------------------------------------阶梯平台-----------------------------------------------*/

void robotarm::jtpy_hold_1()       {ServoController_p->runActionGroup(1, 1);}  //2.5
void robotarm::jtpy_catch_1()      {ServoController_p->runActionGroup(2, 1);}  //3


void robotarm::jtpy_hold_2()       {ServoController_p->runActionGroup(3, 1);}   //2.5
void robotarm::jtpy_hold_2_fast()  {ServoController_p->runActionGroup(4, 1);}   //0.4
void robotarm::jtpy_catch_2()      {ServoController_p->runActionGroup(5, 1);}   //3


void robotarm::jtpy_hold_3()       {ServoController_p->runActionGroup(6, 1);}    //2.5
void robotarm::jtpy_hold_3_fast()  {ServoController_p->runActionGroup(7, 1);}    //0.4
void robotarm::jtpy_catch_3()      {ServoController_p->runActionGroup(8, 1);}    //3

void robotarm::jtpy_1_to_2()       {ServoController_p->runActionGroup(9, 1);}    //2
void robotarm::curl()              {ServoController_p->runActionGroup(10, 1);}   //2

/*---------------------------------------------圆盘机-----------------------------------------------*/

void robotarm::ypj_hold()        {ServoController_p->runActionGroup(11, 1);}   //1.4
void robotarm::ypj_catch()       {ServoController_p->runActionGroup(12, 1);}   //0.3
void robotarm::ypj_put_1()       {ServoController_p->runActionGroup(13, 1);}   //1.5
void robotarm::ypj_put_2()       {ServoController_p->runActionGroup(14, 1);}   //1.5


/*---------------------------------------------立体仓库-----------------------------------------------*/
void robotarm::to_zero()            {ServoController_p->runActionGroup(15, 1);}   //1
void robotarm::ck_1_catch_1()       {ServoController_p->runActionGroup(16, 1);}   //2.6
void robotarm::ck_1_catch_2()       {ServoController_p->runActionGroup(17, 1);}   //2.1



void robotarm::ck_1_put_1()       {ServoController_p->runActionGroup(18, 1);}   //2.2最低的，第一行
void robotarm::ck_1_put_2()       {ServoController_p->runActionGroup(19, 1);}   //2.2
void robotarm::ck_1_put_3()       {ServoController_p->runActionGroup(20, 1);}   //2.2


//抽搐
void robotarm::cc()         {ServoController_p->runActionGroup(21, 1);}   //0.6s
void robotarm::look()       {ServoController_p->runActionGroup(22, 1);}   //1s
 
 //倒跺

void robotarm::dd_catch1()       {ServoController_p->runActionGroup(23, 1);}   //2.2s
void robotarm::dd_catch2()       {ServoController_p->runActionGroup(24, 1);}   //2.2s
void robotarm::dd_catch3()       {ServoController_p->runActionGroup(25, 1);}   //2.2s
void robotarm::dd_put()       {ServoController_p->runActionGroup(26, 1);}   //2.65s

void robotarm::grq()       {ServoController_p->runActionGroup(27, 1);}   //5s


//抓3放2

//抓2放2
//抓1放2



