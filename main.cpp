#include<iostream>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
using namespace std;
//City
bool showCity = true;                      //true = City scene show, false = Village scene show
float carX = 0;
float busX = 0;
float cloudX = 0;
float planeX = 0;
float carSpeed = 0;
float busSpeed = 0;
float cloudSpeed = 0.3f;
float planeSpeed = 1.0f;
bool mallLightOn = true;                   //Shopping mall er light on/off toggle(left click)
bool hospitalLightOn = true;               //Hospital er light on/off toggle(right click)
//Rain
#define MAX_RAIN 1200                       //ak shate screen thakbe or 1200 rain hobe
float rainX[MAX_RAIN];                     //Protiti rain drop er X position
float rainY[MAX_RAIN];                     //Protiti rain drop er Y position
float rainSpeed = 5.0f;                    //rain er speed
bool rainday = false;                      //true = rain hosse ,false = rain nei(R key)
bool cityIsDay = false;                     //true = city din,false = city rat(D/N key)
float sunX =0.0f;                            //Sun er current X position(bam theke shuru)
float sunSpeed =1.0f;                        //Sun er bam-dan speed
bool sunRight = true;
//Village
bool villageIsDay = true;                  //true = village din,false = village rat
float bx_v = 0;                              //Village r boat  X position theke asbe
float cx_v = 0;                            //Village r Cloud X position
float birdX = 0;                           //Village r sob bird X  position theke translation kore
float birdSpeed_v = 2.0f;                  //Village r bird er speed(2.0)
//drawCircle
//x,y = center position,radius = circle er size
void drawCircle(float x, float y, float radius)
{
    glBegin(GL_POLYGON);                        // ploygon circle draw shuru
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.14159f / 180.0f;    //Degree theke radian e convert kortase
        float dx = x + cos(angle) * radius;
        float dy = y + sin(angle) * radius;
        glVertex2f(dx, dy);                    //Circle er ekta point set kore
    }
    glEnd();                                   //Polygon draw shesh
}
//DAY SKY
//din er akash halka neel
void Day_Sky()
{
    glColor3f(0.53f, 0.81f, 0.92f);         //Halka neel(sky blue)
    glBegin(GL_QUADS);                      //draw shuru
    glVertex2f(0,0);                        //Niche bam corner
    glVertex2f(1200,0);                     //Niche dan corner
    glVertex2f(1200,600);                   //Upore dan corner
    glVertex2f(0,600);                      //Upore bam corner
    glEnd();                                //Rectangle draw shesh
}
//PLANE
//dan theke bam dike jay
void Plane()
{
    glPushMatrix();
    glTranslatef(planeX,400,0);            //position: X=planeX,Y=400
    glScalef(8.0f,8.0f, 0);
    glColor3f(.8, .8, 0.8);                //Halka gray rang body
    glBegin(GL_POLYGON);                   //body draw shuru
    glVertex2f(21, 20);                    //upor point
    glVertex2f(18, 19);                    //pechoner niche
    glVertex2f(21, 19);                    //majhe niche
    glVertex2f(24, 19);                    //dan niche
    glVertex2f(24, 20);                    //dan upor
    glVertex2f(25, 21);                    //wing er dan shesh
    glEnd();                               //body draw shesh
    glColor3f(1, 1, 1);                    //Shada rang
    drawCircle(20, 19.6, 0.2);             //engine(choto shada circle)
    glColor3f(0, 0, 1);                    //Neel rang  window circle er jonno
    drawCircle(23.8, 20, 0.2);             //uporer window (neel circle)
    glColor3f(1, 0, 0);                    //Lal rang  nicher window
    drawCircle(23.8, 19.5, 0.2);           //nicher window(lal circle)
    glPopMatrix();                         //transform shesh
}
//CLOUDS
void Clouds()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();                      //Matrix reset
    glTranslatef(cloudX, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);         //Shada rang
    drawCircle(100.0f, 550.0f, 20.0f);   //cloud 1
    drawCircle(120.0f, 540.0f, 20.0f);
    drawCircle(125.0f, 560.0f, 20.0f);
    drawCircle(150.0f, 550.0f, 20.0f);

    drawCircle(200.0f, 490.0f, 20.0f);    //cloud 2
    drawCircle(220.0f, 480.0f, 20.0f);
    drawCircle(225.0f, 500.0f, 20.0f);
    drawCircle(250.0f, 490.0f, 20.0f);
    drawCircle(255.0f, 490.0f, 20.0f);

    drawCircle(400.0f, 520.0f, 20.0f);  //cloud 3
    drawCircle(420.0f, 510.0f, 20.0f);
    drawCircle(425.0f, 530.0f, 20.0f);
    drawCircle(450.0f, 520.0f, 20.0f);
    drawCircle(455.0f, 520.0f, 20.0f);

    drawCircle(500.0f, 560.0f, 20.0f);   //cloud 4
    drawCircle(520.0f, 550.0f, 20.0f);
    drawCircle(525.0f, 570.0f, 20.0f);
    drawCircle(550.0f, 560.0f, 20.0f);

    drawCircle(700.0f, 540.0f, 20.0f);   //cloud 5
    drawCircle(720.0f, 530.0f, 20.0f);
    drawCircle(725.0f, 550.0f, 20.0f);
    drawCircle(750.0f, 540.0f, 20.0f);

    drawCircle(850.0f, 520.0f, 20.0f);   //cloud 6
    drawCircle(870.0f, 510.0f, 20.0f);
    drawCircle(875.0f, 530.0f, 20.0f);
    drawCircle(900.0f, 520.0f, 20.0f);
    drawCircle(905.0f, 520.0f, 20.0f);
    glPopMatrix();                         //Matrix restore
}
//SUN,MOON
//sun holud-shobuj,position(1000, 530),radius 40
void sunA()
{
//Sun
    glPushMatrix();                          //Transform shuru — save koro
    glTranslatef(sunX, 530, 0);             //sunX position set(bam and dan movement)
    glColor3f(.882, .937, .161);             //Holud-shobuj body
    drawCircle(0, 0, 40);
//rotation
    if (sunRight)                        //Dan dike jabe
    {
        sunX += sunSpeed;                //x barle dan dike jabe
        if (sunX >1200)
            sunRight = false;
    }
    else
    {
        sunX -= sunSpeed;                //X kamole bam dike jabe
        if (sunX <0)
            sunRight = true;
    }
   glPopMatrix();
}
//moon cream/off-white
void Moon()
{
    glColor3f(.960, .941, .832);            //Cream/off-white
    drawCircle(1000.0f, 530.0f, 40.0f);     //draw koro
}
//GROUND ROAD DAY
void Ground_D()
{
    glColor3f(0.360f, 0.478f, 0.470f);      //Dark rang
    glBegin(GL_QUADS);                      //rectangle shuru
    glVertex2f(0,0);
    glVertex2f(1200,0);
    glVertex2f(1200,130);
    glVertex2f(0,130);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);         //Shada rang road er majher line
    glBegin(GL_QUADS);
    glVertex2f(0, 63);
    glVertex2f(1200, 63);
    glVertex2f(1200, 67);
    glVertex2f(0, 67);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Gray rang footpath
    glBegin(GL_QUADS);
    glVertex2f(0, 130);
    glVertex2f(1200, 130);
    glVertex2f(1200, 136);
    glVertex2f(0, 136);
    glEnd();
    glColor3f(.647, 0.647, 0.647);       //Halka gray footpath
    glBegin(GL_QUADS);
    glVertex2f(0, 136);
    glVertex2f(1200, 136);
    glVertex2f(1200, 160);
    glVertex2f(0, 160);
    glEnd();
    glColor3f(.537, 0.792, 0.306);       //Shobuj rang grass
    glBegin(GL_QUADS);
    glVertex2f(0, 160);
    glVertex2f(1200, 160);
    glVertex2f(1200, 250);
    glVertex2f(0, 250);
    glEnd();
    glColor3f(.647, 0.647, 0.647);       //Gray
    glBegin(GL_QUADS);
    glVertex2f(280, 136);
    glVertex2f(320, 206);
    glVertex2f(345, 206);
    glVertex2f(315, 136);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Darker gray
    glBegin(GL_QUADS);
    glVertex2f(310, 130);
    glVertex2f(345, 206);
    glVertex2f(349, 206);
    glVertex2f(314, 130);
    glEnd();
    glColor3f(.647, 0.647, 0.647);       //Gray
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(475, 206);
    glVertex2f(520, 136);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Darker gray
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(442, 206);
    glVertex2f(477, 130);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Gray(horizontal)
    glBegin(GL_QUADS);
    glVertex2f(445, 202);
    glVertex2f(442, 206);
    glVertex2f(349, 206);
    glVertex2f(345, 202);
    glEnd();
    glColor3f(.647, 0.647, 0.647);       //Gray
    glBegin(GL_POLYGON);
    glVertex2f(320, 206);
    glVertex2f(475, 206);
    glVertex2f(470, 214);
    glVertex2f(465, 216);
    glVertex2f(330, 216);
    glVertex2f(325, 214);
    glEnd();
    glColor3f(.360f, .478f, .470f);
    glBegin(GL_QUADS);
    glVertex2f(314, 130);
    glVertex2f(347, 202);
    glVertex2f(444, 202);
    glVertex2f(478, 130);
    glEnd();
    glColor3f(1,1,1);                    //Shada
    glBegin(GL_QUADS);
    glVertex2f(396, 130);
    glVertex2f(396, 202);
    glVertex2f(400, 202);
    glVertex2f(400, 130);
    glEnd();
}
//RAIN
void initRain()
{
    for (int i = 0; i < MAX_RAIN; i++)      //1200 r drop er jonno loop
    {
        rainX[i] = rand() % 1200;           //Random X position(0 theke 1200)
        rainY[i] = rand() % 600;            //Random Y position(0 theke 600)
    }
}
//Timer function
void updateRain(int value)
{
    if (rainday)                          //rain update
    {
        for (int i = 0; i < MAX_RAIN; i++)   //Protiti drop update
        {
            rainY[i] -= rainSpeed;          //Drop niche neme jay(Y kom hoy)
            if (rainY[i] < 0)               //Screen er niche gele
                rainY[i] = 600;            //Upore fire ashe
        }
    }
    glutPostRedisplay();                   //Screen redraw kore
    glutTimerFunc(16, updateRain, 0);      //16ms por por call hoi
}
void drawRain()
{
    if (!rainday) return;
    glColor3f(0.7f, .7f, .7f);             //Halka gray
    glLineWidth(1.0f);                     //rain fot porar man
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAIN; i++)      // Protiti drop er jonno
    {
        glVertex2f(rainX[i], rainY[i]);       //Drop er uporer point
        glVertex2f(rainX[i], rainY[i] + 8);   //Drop-er nicher point(8 unit lamba)
    }
    glEnd();
}
//GROUND,ROAD(Rat)
void Ground_N()
{
    glColor3f(0.252f, 0.334f, 0.329f);   //Dark
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 130);
    glVertex2f(0, 130);
    glEnd();
    glColor3f(0.7f, 0.7f, 0.7f);         //Gray
    glBegin(GL_QUADS);
    glVertex2f(0, 63);
    glVertex2f(1200, 63);
    glVertex2f(1200, 67);
    glVertex2f(0, 67);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Gray road border
    glBegin(GL_QUADS);
    glVertex2f(0, 130);
    glVertex2f(1200, 130);
    glVertex2f(1200, 136);
    glVertex2f(0, 136);
    glEnd();
    glColor3f(0.453f, 0.453f, 0.453f);   //Dark gray raat er footpath
    glBegin(GL_QUADS);
    glVertex2f(0, 136);
    glVertex2f(1200, 136);
    glVertex2f(1200, 160);
    glVertex2f(0, 160);
    glEnd();
    glColor3f(0.376f, 0.554f, 0.214f);   //Dark shobuj rat er gress
    glBegin(GL_QUADS);
    glVertex2f(0, 160);
    glVertex2f(1200, 160);
    glVertex2f(1200, 250);
    glVertex2f(0, 250);
    glEnd();
    glColor3f(0.453f, 0.453f, 0.453f);    //Dark gray
    glBegin(GL_QUADS);
    glVertex2f(280, 136);
    glVertex2f(320, 206);
    glVertex2f(345, 206);
    glVertex2f(315, 136);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);      //Gray pillar shadow side
    glBegin(GL_QUADS);
    glVertex2f(310, 130);
    glVertex2f(345, 206);
    glVertex2f(349, 206);
    glVertex2f(314, 130);
    glEnd();
    glColor3f(0.453f, 0.453f, 0.453f);   //Dark gray
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(475, 206);
    glVertex2f(520, 136);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);     //Gray
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(442, 206);
    glVertex2f(477, 130);
    glEnd();
    glColor3f(.525f, 0.525, 0.525f);
    glBegin(GL_QUADS);
    glVertex2f(445, 202);
    glVertex2f(442, 206);
    glVertex2f(349, 206);
    glVertex2f(345, 202);
    glEnd();
    glColor3f(0.453f, 0.453f, 0.453f);   //Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(320, 206);
    glVertex2f(475, 206);
    glVertex2f(470, 214);
    glVertex2f(465, 216);
    glVertex2f(330, 216);
    glVertex2f(325, 214);
    glEnd();
    glColor3f(0.252f, 0.334f, 0.329f);
    glBegin(GL_QUADS);
    glVertex2f(314, 130);
    glVertex2f(347, 202);
    glVertex2f(444, 202);
    glVertex2f(478, 130);
    glEnd();
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_QUADS);
    glVertex2f(396, 130);
    glVertex2f(396, 202);
    glVertex2f(400, 202);
    glVertex2f(400, 130);
    glEnd();
}
//CITY,BUILDINGS day
//Hospital(bam),University/Office(majhe),Shopping Mall(dan)
void Buildings()
{
//HOSPITAL
    glColor3f(0.91f, 0.96f, 0.97f);        //Off-white
    glBegin(GL_POLYGON);
    glVertex2f( 80, 185);
    glVertex2f( 90, 180);
    glVertex2f(170, 180);
    glVertex2f(180, 185);
    glVertex2f(180, 400);
    glVertex2f(170, 410);
    glVertex2f( 90, 410);
    glVertex2f( 80, 400);
    glEnd();
    glColor3f(0.84f, 0.91f, 0.97f);       //Halka neel shada bam
    glBegin(GL_QUADS);
    glVertex2f(-20, 185);
    glVertex2f( 80, 185);
    glVertex2f( 80, 355);
    glVertex2f(-20, 355);
    glEnd();
    glColor3f(0.84f, 0.91f, 0.97f);        // Same rang dan
    glBegin(GL_POLYGON);
    glVertex2f(180, 185);
    glVertex2f(270, 185);
    glVertex2f(270, 345);
    glVertex2f(260, 355);
    glVertex2f(180, 355);
    glEnd();
    glColor3f(0.65f, 0.78f, 0.88f);       //Neel gray
    glBegin(GL_QUADS);
    glVertex2f(270, 185);
    glVertex2f(275, 185);
    glVertex2f(275, 337);
    glVertex2f(270, 345);
    glEnd();

//HOSPITAL r Plus Sign
    glColor3f(0.91f, 0.20f, 0.14f);        //Lal rang
    glBegin(GL_QUADS);
    glVertex2f(110, 380);
    glVertex2f(150, 380);
    glVertex2f(150, 430);
    glVertex2f(110, 430);
    glEnd();
    glColor3f(1, 1, 1);                   //Shada plus er vertical bar
    glBegin(GL_QUADS);
    glVertex2f(127, 385);
    glVertex2f(133, 385);
    glVertex2f(133, 425);
    glVertex2f(127, 425);
    glEnd();
    glColor3f(1, 1, 1);                   //Shada plus er horizontal bar
    glBegin(GL_QUADS);
    glVertex2f(115, 402);
    glVertex2f(145, 402);
    glVertex2f(145, 410);
    glVertex2f(115, 410);
    glEnd();
//window
    glColor3f(0.18f, 0.53f, 0.76f);        //Neel rang
    glBegin(GL_QUADS);
    glVertex2f(110, 180);
    glVertex2f(150, 180);
    glVertex2f(150, 220);
    glVertex2f(110, 220);
    glEnd();
    glColor3f(1, 1, 1);                   //Shada
    glBegin(GL_LINES);
    glVertex2f(110, 212);
    glVertex2f(150, 212);
    glVertex2f(130, 212);
    glVertex2f(130, 180);
    glEnd();
//Floor windows
    glColor3f(0.18f, 0.53f, 0.76f);         //Neel
    glBegin(GL_QUADS);
    glVertex2f(90, 230);                  //Floor 1 window
    glVertex2f(170, 230);
    glVertex2f(170, 245);
    glVertex2f(90, 245);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 2 window
    glVertex2f(90, 255);
    glVertex2f(170, 255);
    glVertex2f(170, 270);
    glVertex2f(90, 270);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 3 window
    glVertex2f(90, 280);
    glVertex2f(170, 280);
    glVertex2f(170, 295);
    glVertex2f(90, 295);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 4 window
    glVertex2f(90, 305);
    glVertex2f(170, 305);
    glVertex2f(170, 320);
    glVertex2f(90, 320);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 5 window
    glVertex2f(90, 330);
    glVertex2f(170, 330);
    glVertex2f(170, 345);
    glVertex2f(90, 345);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 6 window
    glVertex2f(90, 355);
    glVertex2f(170, 355);
    glVertex2f(170, 370);
    glVertex2f(90, 370);
    glEnd();
// Bam windows
    glBegin(GL_QUADS);                    //Bam  floor 1 window
    glVertex2f(-20, 200);
    glVertex2f(70, 200);
    glVertex2f(70, 215);
    glVertex2f(-20, 215);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 2
    glVertex2f(-20, 225);
    glVertex2f(70, 225);
    glVertex2f(70, 240);
    glVertex2f(-20, 240);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 3
    glVertex2f(-20, 250);
    glVertex2f(70, 250);
    glVertex2f(70, 265);
    glVertex2f(-20, 265);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 4
    glVertex2f(-20, 275);
    glVertex2f(70, 275);
    glVertex2f(70, 290);
    glVertex2f(-20, 290);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 5
    glVertex2f(-20, 300);
    glVertex2f( 70, 300);
    glVertex2f( 70, 315);
    glVertex2f(-20, 315);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 6
    glVertex2f(-20, 325);
    glVertex2f( 70, 325);
    glVertex2f( 70, 340);
    glVertex2f(-20, 340);
    glEnd();
//Dan windows
    glBegin(GL_QUADS);                    //Dan floor 1 window
    glVertex2f(190, 200);
    glVertex2f(260, 200);
    glVertex2f(260, 215);
    glVertex2f(190, 215);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 2
    glVertex2f(190, 225);
    glVertex2f(260, 225);
    glVertex2f(260, 240);
    glVertex2f(190, 240);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 3
    glVertex2f(190, 250);
    glVertex2f(260, 250);
    glVertex2f(260, 265);
    glVertex2f(190, 265);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 4
    glVertex2f(190, 275);
    glVertex2f(260, 275);
    glVertex2f(260, 290);
    glVertex2f(190, 290);
    glEnd();
    glBegin(GL_QUADS);                    //Floor 5
    glVertex2f(190, 300);
    glVertex2f(260, 300);
    glVertex2f(260, 315);
    glVertex2f(190, 315);
    glEnd();
    glBegin(GL_QUADS);                    // Floor 6
    glVertex2f(190, 325);
    glVertex2f(260, 325);
    glVertex2f(260, 340);
    glVertex2f(190, 340);
    glEnd();
//UNIVERSITY Dan
    glColor3f(0.98f, 0.96f, 0.90f);       //Cream rang  dan tower
    glBegin(GL_POLYGON);
    glVertex2f(420, 230);
    glVertex2f(420, 415);
    glVertex2f(425, 420);
    glVertex2f(515, 420);
    glVertex2f(520, 415);
    glVertex2f(520, 230);
    glEnd();
    glColor3f(0.66f, 0.85f, 0.91f);       //Neel er glass
    glBegin(GL_POLYGON);
    glVertex2f(424, 240);
    glVertex2f(424, 411);
    glVertex2f(429, 416);
    glVertex2f(511, 416);
    glVertex2f(516, 411);
    glVertex2f(516, 240);
    glEnd();
//UNIVERSITY Bam
    glColor3f(0.98f, 0.96f, 0.90f);       //Cream bam tower
    glBegin(GL_POLYGON);
    glVertex2f(300, 230);
    glVertex2f(300, 415);
    glVertex2f(305, 420);
    glVertex2f(395, 420);
    glVertex2f(400, 415);
    glVertex2f(400, 230);
    glEnd();
    glColor3f(0.66f, 0.85f, 0.91f);       //Neel bam glass
    glBegin(GL_POLYGON);
    glVertex2f(304, 240);
    glVertex2f(304, 411);
    glVertex2f(309, 416);
    glVertex2f(391, 416);
    glVertex2f(396, 411);
    glVertex2f(396, 240);
    glEnd();
//Window grid lines horizontal
    glColor3f(0.98f, 0.96f, 0.90f);        //Cream window grid horizontal lines
    glBegin(GL_LINES);
    glVertex2f(304, 260);
    glVertex2f(516, 260);
    glVertex2f(304, 280);
    glVertex2f(516, 280);
    glVertex2f(304, 300);
    glVertex2f(516, 300);
    glVertex2f(304, 320);
    glVertex2f(516, 320);
    glVertex2f(304, 340);
    glVertex2f(516, 340);
    glVertex2f(304, 360);
    glVertex2f(396, 360);
    glVertex2f(304, 380);
    glVertex2f(396, 380);
    glVertex2f(304, 400);
    glVertex2f(396, 400);
    glVertex2f(424, 400);
    glVertex2f(516, 400);
    glVertex2f(424, 380);
    glVertex2f(516, 380);
    glVertex2f(424, 360);
    glVertex2f(516, 360);
    glEnd();
//Window grid lines vertical
    glBegin(GL_LINES);                    //Vertical lines shuru
    glVertex2f(309, 240);
    glVertex2f(309, 416);
    glVertex2f(329, 240);
    glVertex2f(329, 416);
    glVertex2f(349, 240);
    glVertex2f(349, 416);
    glVertex2f(369, 240);
    glVertex2f(369, 416);
    glVertex2f(389, 240);
    glVertex2f(389, 416);
    glVertex2f(429, 240);
    glVertex2f(429, 416);
    glVertex2f(449, 240);
    glVertex2f(449, 416);
    glVertex2f(469, 240);
    glVertex2f(469, 416);
    glVertex2f(489, 240);
    glVertex2f(489, 416);
    glVertex2f(509, 240);
    glVertex2f(509, 416);
    glEnd();
//Majher connecting block
    glColor3f(1.0f, 0.97f, 0.88f);        //Halka cream majher connecting block body
    glBegin(GL_POLYGON);
    glVertex2f(360, 230);
    glVertex2f(360, 345);
    glVertex2f(365, 350);
    glVertex2f(455, 350);
    glVertex2f(460, 345);
    glVertex2f(460, 230);
    glEnd();
    glColor3f(0.66f, 0.85f, 0.91f);       //Neel glass
    glBegin(GL_POLYGON);
    glVertex2f(364, 240);
    glVertex2f(364, 341);
    glVertex2f(369, 346);
    glVertex2f(451, 346);
    glVertex2f(456, 341);
    glVertex2f(456, 240);
    glEnd();
    glColor3f(1.0f, 0.97f, 0.88f);         //Cream window horizontal lines
    glBegin(GL_LINES);
    glVertex2f(364, 260);
    glVertex2f(456, 260);     //Floor 1
    glVertex2f(364, 280);
    glVertex2f(456, 280);     //Floor 2
    glVertex2f(364, 300);
    glVertex2f(456, 300);    //Floor 3
    glVertex2f(364, 320);
    glVertex2f(456, 320);    //Floor 4
    glVertex2f(364, 340);
    glVertex2f(456, 340);    //Floor 5
    glEnd();
    glBegin(GL_LINES);                    //vertical window lines
    glVertex2f(369, 240);
    glVertex2f(369, 346);      //Col 1
    glVertex2f(389, 240);
    glVertex2f(389, 346);      //Col 2
    glVertex2f(409, 240);
    glVertex2f(409, 346);     //Col 3
    glVertex2f(429, 240);
    glVertex2f(429, 346);     //Col 4
    glVertex2f(449, 240);
    glVertex2f(449, 346);     //Col 5
    glEnd();
//entry block
    glColor3f(0.56f, 0.76f, 0.60f);        //Shobuj  entry  block
    glBegin(GL_POLYGON);
    glVertex2f(390, 230);
    glVertex2f(390, 265);
    glVertex2f(395, 270);
    glVertex2f(425, 270);
    glVertex2f(430, 265);
    glVertex2f(430, 230);
    glEnd();
    glColor3f(0,0,0);                      //Kalo center divider line
    glBegin(GL_LINES);
    glVertex2f(410, 230);
    glVertex2f(410, 270);
    glEnd();
//SHOPPING MALL Bam
    glColor3f(0.20f, 0.60f, 0.86f);
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(680, 280);
    glVertex2i(680, 190);
    glEnd();
    glColor3f(0.12f, 0.38f, 0.55f);       //Dark neel
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(560, 285);
    glVertex2i(560, 198);
    glEnd();
    glColor3f(0.12f, 0.38f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(690, 280);
    glVertex2i(615, 320);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(615, 320);
    glVertex2i(550, 290);
    glEnd();
    glColor3f(0.12f, 0.38f, 0.55f);       //Dark neel vertical bar
    glBegin(GL_QUADS);
    glVertex2i(635, 300);
    glVertex2i(645, 300);
    glVertex2i(645, 345);
    glVertex2i(635, 340);
    glEnd();
    glColor3f(0.66f, 0.85f, 0.91f);        //Neel glass
    glBegin(GL_QUADS);
    glVertex2i(590, 190);
    glVertex2i(590, 250);
    glVertex2i(660, 250);
    glVertex2i(660, 190);
    glEnd();
    glColor3f(0,0,0);                     //Kalo window center
    glBegin(GL_LINES);
    glVertex2i(625, 190);
    glVertex2i(625, 250);
    glEnd();
//SHOPPING MALL Dan
    glColor3f(0.10f, 0.74f, 0.61f);        //Shobuj rang
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(823, 280);
    glVertex2i(823, 190);
    glEnd();
    glColor3f(0.08f, 0.56f, 0.47f);        //Dark shobuj
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(703, 285);
    glVertex2i(703, 198);
    glEnd();
    glColor3f(0.08f, 0.44f, 0.38f);       //Darker shobuj
    glBegin(GL_QUADS);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(815, 310);
    glVertex2i(830, 270);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(695, 280);
    glEnd();
    glColor3f(0.08f, 0.44f, 0.38f);
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();
    glColor3f(0.66f, 0.85f, 0.91f);       //Neel glass
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(765, 250);
    glVertex2i(765, 200);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(767, 195);
    glVertex2i(767, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();
//SHOPPING MALL Main body
    glColor3f(0.96f, 0.80f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2i(860, 210);
    glVertex2i(860, 400);
    glVertex2i(1010, 440);
    glVertex2i(1010, 190);
    glEnd();
    glColor3f(0.94f, 0.70f, 0.48f);        //Orange mall main dan
    glBegin(GL_QUADS);
    glVertex2i(1010, 190);
    glVertex2i(1010, 440);
    glVertex2i(1160, 400);
    glVertex2i(1160, 210);
    glEnd();
    glColor3f(0.98f, 0.91f, 0.62f);       //Holud mall er top windows(aam)
    glBegin(GL_QUADS);
    glVertex2i(910, 203);
    glVertex2i(910, 240);
    glVertex2i(960, 236);
    glVertex2i(960, 196);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(1060, 196);
    glVertex2i(1060, 236);
    glVertex2i(1110, 241);
    glVertex2i(1110, 203);
    glEnd();
    glColor3f(0.56f, 0.27f, 0.68f);       //Badami neel
    glBegin(GL_QUADS);
    glVertex2i(865, 250);
    glVertex2i(865, 395);
    glVertex2i(1005, 430);
    glVertex2i(1005, 240);
    glEnd();
    glColor3f(0.65f, 0.41f, 0.74f);      //Halka badami
    glBegin(GL_QUADS);
    glVertex2i(1015, 240);
    glVertex2i(1015, 430);
    glVertex2i(1155, 395);
    glVertex2i(1155, 250);
    glEnd();
    glColor3f(1,1,1);                     //Shada  mall bam  window cross lines
    glBegin(GL_LINES);
    glVertex2i(935, 244);                 //Vertical
    glVertex2i(935, 412);
    glVertex2i(865, 322);                 //Horizontal
    glVertex2i(1005, 335);
    glEnd();
    glBegin(GL_LINES);                    //Mall dan window cross lines
    glVertex2i(1085, 244);                //Vertical
    glVertex2i(1085, 412);
    glVertex2i(1155, 322);                //Horizontal
    glVertex2i(1015, 335);
    glEnd();
}
//CITY,BUILDINGS NIGHT
void Buildings_N()
{
//HOSPITAL
    glColor3f(0.45f, 0.52f, 0.58f);      //Dark gray  main
    glBegin(GL_POLYGON);
    glVertex2f( 80, 185);
    glVertex2f( 90, 180);
    glVertex2f(170, 180);
    glVertex2f(180, 185);
    glVertex2f(180, 400);
    glVertex2f(170, 410);
    glVertex2f( 90, 410);
    glVertex2f( 80, 400);
    glEnd();
    glColor3f(0.38f, 0.44f, 0.52f);      //Darker gray  bam
    glBegin(GL_QUADS);
    glVertex2f(-20, 185);
    glVertex2f( 80, 185);
    glVertex2f( 80, 355);
    glVertex2f(-20, 355);
    glEnd();
    glColor3f(0.38f, 0.44f, 0.52f);      //Darker gray dan
    glBegin(GL_POLYGON);
    glVertex2f(180, 185);
    glVertex2f(270, 185);
    glVertex2f(270, 345);
    glVertex2f(260, 355);
    glVertex2f(180, 355);
    glEnd();
    glColor3f(0.28f, 0.32f, 0.38f);      //dark
    glBegin(GL_QUADS);
    glVertex2f(270, 185);
    glVertex2f(275, 185);
    glVertex2f(275, 337);
    glVertex2f(270, 345);
    glEnd();
    glColor3f(0.55f, 0.10f, 0.08f);      //Dark lal plus sign(rat)
    glBegin(GL_QUADS);
    glVertex2f(110, 380);
    glVertex2f(150, 380);
    glVertex2f(150, 430);
    glVertex2f(110, 430);
    glEnd();
    glColor3f(0.7f, 0.7f, 0.7f);          //gray plus vertical bar
    glBegin(GL_QUADS);
    glVertex2f(127, 385);
    glVertex2f(133, 385);
    glVertex2f(133, 425);
    glVertex2f(127, 425);
    glEnd();
    glBegin(GL_QUADS);                    //Plus horizontal bar
    glVertex2f(115, 402);
    glVertex2f(145, 402);
    glVertex2f(145, 410);
    glVertex2f(115, 410);
    glEnd();
//true hole holud, false hole kalo
    if(hospitalLightOn)
       glColor3f(0.90f, 0.78f, 0.30f);     //Holud alo  light on
    else
       glColor3f(0.12f, 0.12f, 0.12f);     //kalo  light off
    glBegin(GL_QUADS);
    glVertex2f(110, 180);
    glVertex2f(150, 180);
    glVertex2f(150, 220);
    glVertex2f(110, 220);
    glEnd();
    glColor3f(0.6f, 0.6f, 0.6f);           //gray top window
    glBegin(GL_LINES);
    glVertex2f(110, 212);
    glVertex2f(150, 212);
    glVertex2f(130, 212);
    glVertex2f(130, 180);
    glEnd();
// Floor windows
    if(hospitalLightOn)
       glColor3f(0.90f, 0.78f, 0.30f);      //Light on holud
    else
       glColor3f(0.12f, 0.12f, 0.12f);      //Light off — kalo
    glBegin(GL_QUADS);
    glVertex2f(90, 230);
    glVertex2f(170, 230);
    glVertex2f(170, 245);
    glVertex2f(90, 245);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(90, 255);
    glVertex2f(170, 255);
    glVertex2f(170, 270);
    glVertex2f(90, 270);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(90, 280);
    glVertex2f(170, 280);
    glVertex2f(170, 295);
    glVertex2f(90, 295);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(90, 305);
    glVertex2f(170, 305);
    glVertex2f(170, 320);
    glVertex2f(90, 320);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(90, 330);
    glVertex2f(170, 330);
    glVertex2f(170, 345);
    glVertex2f(90, 345);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(90, 355);
    glVertex2f(170, 355);
    glVertex2f(170, 370);
    glVertex2f(90, 370);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 200);
    glVertex2f(70, 200);
    glVertex2f(70, 215);
    glVertex2f(-20, 215);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 225);
    glVertex2f(70, 225);
    glVertex2f(70, 240);
    glVertex2f(-20, 240);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 250);
    glVertex2f(70, 250);
    glVertex2f(70, 265);
    glVertex2f(-20, 265);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 275);
    glVertex2f(70, 275);
    glVertex2f(70, 290);
    glVertex2f(-20, 290);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 300);
    glVertex2f( 70, 300);
    glVertex2f( 70, 315);
    glVertex2f(-20, 315);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-20, 325);
    glVertex2f( 70, 325);
    glVertex2f( 70, 340);
    glVertex2f(-20, 340);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 200);
    glVertex2f(260, 200);
    glVertex2f(260, 215);
    glVertex2f(190, 215);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 225);
    glVertex2f(260, 225);
    glVertex2f(260, 240);
    glVertex2f(190, 240);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 250);
    glVertex2f(260, 250);
    glVertex2f(260, 265);
    glVertex2f(190, 265);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 275);
    glVertex2f(260, 275);
    glVertex2f(260, 290);
    glVertex2f(190, 290);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 300);
    glVertex2f(260, 300);
    glVertex2f(260, 315);
    glVertex2f(190, 315);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(190, 325);
    glVertex2f(260, 325);
    glVertex2f(260, 340);
    glVertex2f(190, 340);
    glEnd();
//UNIVERSITY dark
    glColor3f(0.30f, 0.28f, 0.22f);            //Dark brown dan tower(rat)
    glBegin(GL_POLYGON);
    glVertex2f(420, 230);
    glVertex2f(420, 415);
    glVertex2f(425, 420);
    glVertex2f(515, 420);
    glVertex2f(520, 415);
    glVertex2f(520, 230);
    glEnd();
    glColor3f(0.18f, 0.26f, 0.30f);            //dark neel glass(rat)
    glBegin(GL_POLYGON);
    glVertex2f(424, 240);
    glVertex2f(424, 411);
    glVertex2f(429, 416);
    glVertex2f(511, 416);
    glVertex2f(516, 411);
    glVertex2f(516, 240);
    glEnd();
    glColor3f(0.30f, 0.28f, 0.22f);            //Dark brown bam(rat)
    glBegin(GL_POLYGON);
    glVertex2f(300, 230);
    glVertex2f(300, 415);
    glVertex2f(305, 420);
    glVertex2f(395, 420);
    glVertex2f(400, 415);
    glVertex2f(400, 230);
    glEnd();
    glColor3f(0.18f, 0.26f, 0.30f);           //dark neel
    glBegin(GL_POLYGON);
    glVertex2f(304, 240);
    glVertex2f(304, 411);
    glVertex2f(309, 416);
    glVertex2f(391, 416);
    glVertex2f(396, 411);
    glVertex2f(396, 240);
    glEnd();
    glColor3f(0.30f, 0.28f, 0.22f);           // Dark window grid lines(rat)
    glBegin(GL_LINES);
    glVertex2f(304, 260);
    glVertex2f(516, 260);
    glVertex2f(304, 280);
    glVertex2f(516, 280);
    glVertex2f(304, 300);
    glVertex2f(516, 300);
    glVertex2f(304, 320);
    glVertex2f(516, 320);
    glVertex2f(304, 340);
    glVertex2f(516, 340);
    glVertex2f(304, 360);
    glVertex2f(396, 360);
    glVertex2f(304, 380);
    glVertex2f(396, 380);
    glVertex2f(304, 400);
    glVertex2f(396, 400);
    glVertex2f(424, 400);
    glVertex2f(516, 400);
    glVertex2f(424, 380);
    glVertex2f(516, 380);
    glVertex2f(424, 360);
    glVertex2f(516, 360);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(309, 240);
    glVertex2f(309, 416);
    glVertex2f(329, 240);
    glVertex2f(329, 416);
    glVertex2f(349, 240);
    glVertex2f(349, 416);
    glVertex2f(369, 240);
    glVertex2f(369, 416);
    glVertex2f(389, 240);
    glVertex2f(389, 416);
    glVertex2f(429, 240);
    glVertex2f(429, 416);
    glVertex2f(449, 240);
    glVertex2f(449, 416);
    glVertex2f(469, 240);
    glVertex2f(469, 416);
    glVertex2f(489, 240);
    glVertex2f(489, 416);
    glVertex2f(509, 240);
    glVertex2f(509, 416);
    glEnd();
    glColor3f(0.32f, 0.30f, 0.24f);        //Dark(raat)
    glBegin(GL_POLYGON);
    glVertex2f(360, 230);
    glVertex2f(360, 345);
    glVertex2f(365, 350);
    glVertex2f(455, 350);
    glVertex2f(460, 345);
    glVertex2f(460, 230);
    glEnd();
    glColor3f(0.18f, 0.26f, 0.30f);
    glBegin(GL_POLYGON);
    glVertex2f(364, 240);
    glVertex2f(364, 341);
    glVertex2f(369, 346);
    glVertex2f(451, 346);
    glVertex2f(456, 341);
    glVertex2f(456, 240);
    glEnd();
    glColor3f(0.32f, 0.30f, 0.24f);
    glBegin(GL_LINES);
    glVertex2f(364, 260);
    glVertex2f(456, 260);
    glVertex2f(364, 280);
    glVertex2f(456, 280);
    glVertex2f(364, 300);
    glVertex2f(456, 300);
    glVertex2f(364, 320);
    glVertex2f(456, 320);
    glVertex2f(364, 340);
    glVertex2f(456, 340);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(369, 240);
    glVertex2f(369, 346);
    glVertex2f(389, 240);
    glVertex2f(389, 346);
    glVertex2f(409, 240);
    glVertex2f(409, 346);
    glVertex2f(429, 240);
    glVertex2f(429, 346);
    glVertex2f(449, 240);
    glVertex2f(449, 346);
    glEnd();
    glColor3f(0.28f, 0.40f, 0.32f);        //Dark shobuj entry(rat)
    glBegin(GL_POLYGON);
    glVertex2f(390, 230);
    glVertex2f(390, 265);
    glVertex2f(395, 270);
    glVertex2f(425, 270);
    glVertex2f(430, 265);
    glVertex2f(430, 230);
    glEnd();
    glColor3f(0, 0, 0);                     //Kalo
    glBegin(GL_LINES);
    glVertex2f(410, 230);
    glVertex2f(410, 270);
    glEnd();
//SHOPPING MALL dark light toggle
    glColor3f(0.10f, 0.28f, 0.44f);        //Dark neel  mall bam section(rat)
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(680, 280);
    glVertex2i(680, 190);
    glEnd();
    glColor3f(0.06f, 0.18f, 0.28f);
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(560, 285);
    glVertex2i(560, 198);
    glEnd();
    glColor3f(0.06f, 0.18f, 0.28f);
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(690, 280);
    glVertex2i(615, 320);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(615, 320);
    glVertex2i(550, 290);
    glEnd();
    glColor3f(0.06f, 0.18f, 0.28f);
    glBegin(GL_QUADS);
    glVertex2i(635,300);
    glVertex2i(645,300);
    glVertex2i(645,345);
    glVertex2i(635,340);
    glEnd();
    glColor3f(0.70f, 0.60f, 0.25f);        //Holud bam window
    glBegin(GL_QUADS);
    glVertex2i(590,190);
    glVertex2i(590,250);
    glVertex2i(660,250);
    glVertex2i(660,190);
    glEnd();
    glColor3f(0, 0, 0);                    //Kalo window
    glBegin(GL_LINES);
    glVertex2i(625,190);
    glVertex2i(625,250);
    glEnd();
    glColor3f(0.05f, 0.35f, 0.28f);        //Dark shobuj dan section(aat)
    glBegin(GL_QUADS);
    glVertex2i(713,190);
    glVertex2i(713,280);
    glVertex2i(823,280);
    glVertex2i(823,190);
    glEnd();
    glColor3f(0.04f, 0.26f, 0.22f);        //Darker  dan side
    glBegin(GL_QUADS);
    glVertex2i(713,190);
    glVertex2i(713,280);
    glVertex2i(703,285);
    glVertex2i(703,198);
    glEnd();
    glColor3f(0.04f, 0.20f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2i(708,270);
    glVertex2i(710,310);
    glVertex2i(815,310);
    glVertex2i(830,270);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(708,270);
    glVertex2i(710,310);
    glVertex2i(695,280);
    glEnd();
    glColor3f(0.04f, 0.20f, 0.18f);
    glBegin(GL_QUADS);
    glVertex2i(738,190);
    glVertex2i(738,250);
    glVertex2i(800,250);
    glVertex2i(800,190);
    glEnd();
    glColor3f(0.70f, 0.60f, 0.25f);        //Holud dan window(alo jole)
    glBegin(GL_QUADS);
    glVertex2i(738,190);
    glVertex2i(738,250);
    glVertex2i(765,250);
    glVertex2i(765,200);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(767,195);
    glVertex2i(767,250);
    glVertex2i(800,250);
    glVertex2i(800,190);
    glEnd();
    glColor3f(0.22f, 0.18f, 0.12f);      //dark brown mall main bam (rat)
    glBegin(GL_QUADS);
    glVertex2i(860,210);
    glVertex2i(860,400);
    glVertex2i(1010,440);
    glVertex2i(1010,190);
    glEnd();
    glColor3f(0.18f, 0.14f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2i(1010,190);
    glVertex2i(1010,440);
    glVertex2i(1160,400);
    glVertex2i(1160,210);
    glEnd();
//mallLightOn toggle(Left click diye on/off)
    if(mallLightOn)
       glColor3f(1.0f, 0.80f, 0.20f);      //Bright holud  mall light on
    else
       glColor3f(0.15f, 0.15f, 0.15f);     //kalo mall light off
    glBegin(GL_QUADS);
    glVertex2i(910,203);
    glVertex2i(910,240);
    glVertex2i(960,236);
    glVertex2i(960,196);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(1060,196);
    glVertex2i(1060,236);
    glVertex2i(1110,241);
    glVertex2i(1110,203);
    glEnd();
//Mall main windows
    if(mallLightOn)
       glColor3f(1.0f, 0.80f, 0.20f);      //Bright holud  on
    else
       glColor3f(0.12f, 0.12f, 0.12f);     //Kalo  off
    glBegin(GL_QUADS);
    glVertex2i(865, 250);
    glVertex2i(865, 395);
    glVertex2i(1005, 430);
    glVertex2i(1005, 240);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i(1015, 240);
    glVertex2i(1015, 430);
    glVertex2i(1155, 395);
    glVertex2i(1155, 250);
    glEnd();
    glColor3f(1, 1, 1);                   // Shada mall window cross
    glBegin(GL_LINES);
    glVertex2i(935, 244);
    glVertex2i(935, 412);
    glVertex2i(865, 322);
    glVertex2i(1005, 335);
    glEnd();
    glBegin(GL_LINES);
    glVertex2i(1085, 244);
    glVertex2i(1085, 412);
    glVertex2i(1155, 322);
    glVertex2i(1015, 335);
    glEnd();
}
//TREES day bright green
void Trees()
{
//tree 1
    glColor3ub(78, 148, 45);               //Medium shobuj
    glBegin(GL_TRIANGLES);
    glVertex2i(520, 190);
    glVertex2i(590, 195);
    glVertex2i(550, 230);
    glEnd();
    glColor3ub(39, 118, 37);               //Darker shobuj
    glBegin(GL_TRIANGLES);
    glVertex2i(525, 212);
    glVertex2i(582, 208);
    glVertex2i(555, 237);
    glEnd();
    glColor3ub(78, 148, 45);              //Medium shobuj
    glBegin(GL_TRIANGLES);
    glVertex2i(530, 230);
    glVertex2i(575, 230);
    glVertex2i(555, 255);
    glEnd();
    glColor3ub(119, 68, 34);              //Badami
    glBegin(GL_QUADS);
    glVertex2i(550, 175);
    glVertex2i(560, 175);
    glVertex2i(560, 193);
    glVertex2i(550, 193);
    glEnd();
//tree 2
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(670, 190);
    glVertex2i(740, 195);
    glVertex2i(700, 230);
    glEnd();
    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(675, 212);
    glVertex2i(732, 208);
    glVertex2i(705, 237);
    glEnd();
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(680, 230);
    glVertex2i(725, 230);
    glVertex2i(705, 255);
    glEnd();
    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(700, 175);
    glVertex2i(710, 175);
    glVertex2i(710, 193);
    glVertex2i(700, 193);
    glEnd();
//tree 3
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(820, 190);
    glVertex2i(890, 195);
    glVertex2i(850, 230);
    glEnd();
    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(825, 212);
    glVertex2i(882, 208);
    glVertex2i(855, 237);
    glEnd();
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(830, 230);
    glVertex2i(875, 230);
    glVertex2i(855, 255);
    glEnd();
    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(850, 175);
    glVertex2i(860, 175);
    glVertex2i(860, 193);
    glVertex2i(850, 193);
    glEnd();
//tree 4
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(170, 190);
    glVertex2i(240, 195);
    glVertex2i(200, 230);
    glEnd();
    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(175, 212);
    glVertex2i(232, 208);
    glVertex2i(205, 237);
    glEnd();
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(180, 230);
    glVertex2i(225, 230);
    glVertex2i(205, 255);
    glEnd();
    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(200, 175);
    glVertex2i(210, 175);
    glVertex2i(210, 193);
    glVertex2i(200, 193);
    glEnd();
//tree 5
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(1120, 190);
    glVertex2i(1190, 195);
    glVertex2i(1150, 230);
    glEnd();
    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(1125, 212);
    glVertex2i(1182, 208);
    glVertex2i(1155, 237);
    glEnd();
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(1130, 230);
    glVertex2i(1175, 230);
    glVertex2i(1155, 255);
    glEnd();
    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(1150, 175);
    glVertex2i(1160, 175);
    glVertex2i(1160, 193);
    glVertex2i(1150, 193);
    glEnd();
}
//TREES(Rat) dark green
void Trees_N()
{
//tree 1
    glColor3ub(55, 108, 34);                //Dark shobuj
    glBegin(GL_TRIANGLES);
    glVertex2i(520, 190);
    glVertex2i(590, 195);
    glVertex2i(550, 230);
    glEnd();
    glColor3ub(28, 83, 27);                //Darker  middle
    glBegin(GL_TRIANGLES);
    glVertex2i(525, 212);
    glVertex2i(582, 208);
    glVertex2i(555, 237);
    glEnd();
    glColor3ub(55, 108, 34);               //Dark shobuj
    glBegin(GL_TRIANGLES);
    glVertex2i(530, 230);
    glVertex2i(575, 230);
    glVertex2i(555, 255);
    glEnd();
    glColor3ub(87, 47, 23);               //Dark badami
    glBegin(GL_QUADS);
    glVertex2i(550, 175);
    glVertex2i(560, 175);
    glVertex2i(560, 193);
    glVertex2i(550, 193);
    glEnd();
//tree 2
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(670, 190);
    glVertex2i(740, 195);
    glVertex2i(700, 230);
    glEnd();
    glColor3ub(28, 83, 27);
    glBegin(GL_TRIANGLES);
    glVertex2i(675, 212);
    glVertex2i(732, 208);
    glVertex2i(705, 237);
    glEnd();
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(680, 230);
    glVertex2i(725, 230);
    glVertex2i(705, 255);
    glEnd();
    glColor3ub(87, 47, 23);
    glBegin(GL_QUADS);
    glVertex2i(700, 175);
    glVertex2i(710, 175);
    glVertex2i(710, 193);
    glVertex2i(700, 193);
    glEnd();
//tree 3
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(820, 190);
    glVertex2i(890, 195);
    glVertex2i(850, 230);
    glEnd();
    glColor3ub(28, 83, 27);
    glBegin(GL_TRIANGLES);
    glVertex2i(825, 212);
    glVertex2i(882, 208);
    glVertex2i(855, 237);
    glEnd();
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(830, 230);
    glVertex2i(875, 230);
    glVertex2i(855, 255);
    glEnd();
    glColor3ub(87, 47, 23);
    glBegin(GL_QUADS);
    glVertex2i(850, 175);
    glVertex2i(860, 175);
    glVertex2i(860, 193);
    glVertex2i(850, 193);
    glEnd();
//tree 4
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(170, 190);
    glVertex2i(240, 195);
    glVertex2i(200, 230);
    glEnd();
    glColor3ub(28, 83, 27);
    glBegin(GL_TRIANGLES);
    glVertex2i(175, 212);
    glVertex2i(232, 208);
    glVertex2i(205, 237);
    glEnd();
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(180, 230);
    glVertex2i(225, 230);
    glVertex2i(205, 255);
    glEnd();
    glColor3ub(87, 47, 23);
    glBegin(GL_QUADS);
    glVertex2i(200, 175);
    glVertex2i(210, 175);
    glVertex2i(210, 193);
    glVertex2i(200, 193);
    glEnd();
//tree 5
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(1120, 190);
    glVertex2i(1190, 195);
    glVertex2i(1150, 230);
    glEnd();
    glColor3ub(28, 83, 27);
    glBegin(GL_TRIANGLES);
    glVertex2i(1125, 212);
    glVertex2i(1182, 208);
    glVertex2i(1155, 237);
    glEnd();
    glColor3ub(55, 108, 34);
    glBegin(GL_TRIANGLES);
    glVertex2i(1130, 230);
    glVertex2i(1175, 230);
    glVertex2i(1155, 255);
    glEnd();
    glColor3ub(87, 47, 23);
    glBegin(GL_QUADS);
    glVertex2i(1150, 175);
    glVertex2i(1160, 175);
    glVertex2i(1160, 193);
    glVertex2i(1150, 193);
    glEnd();
}
//CAR day
void Car_1()
{
    glPushMatrix();                        //Transform shuru
    glTranslatef(carX, 0, 0);              //position
    glColor3f(0.0f, 0.0f, 1.0f);           //Neel rangbody
    glBegin(GL_POLYGON);
    glVertex2f(210, 20);
    glVertex2f(350, 20);
    glVertex2f(350, 40);
    glVertex2f(330, 60);
    glVertex2f(200, 60);
    glVertex2f(200, 40);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.6f);          //Dark neel
    glBegin(GL_POLYGON);
    glVertex2f(230, 60);
    glVertex2f(320, 60);
    glVertex2f(305, 85);
    glVertex2f(245, 85);
    glEnd();
    glColor3f(0.75f, 0.75f, 0.75f);       //Halka gray
    glBegin(GL_QUADS);
    glVertex2f(250, 65);
    glVertex2f(300, 65);
    glVertex2f(290, 80);
    glVertex2f(260, 80);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);          //Kalo  tyre
    drawCircle(230, 20, 15);              //Bam tyre
    drawCircle(320, 20, 15);              //Dan tyre
    glColor3f(0.3f, 0.3f, 0.3f);         //Dark gray
    drawCircle(230, 20, 7);               //Bam rim
    drawCircle(320, 20, 7);               //Dan rim
    glPopMatrix();
}
//CAR(Rat)dark body
void Car_1_N()
{
    glPushMatrix();
    glTranslatef(carX, 0, 0);
    glColor3f(0.8f, 0.7f, 0.3f);          //Holud  car er headlight
    glBegin(GL_TRIANGLES);
    glVertex2f(340, 45);
    glVertex2f(410, 25);
    glVertex2f(410, 55);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.5f);          //Dark neel  car body (rat)
    glBegin(GL_POLYGON);
    glVertex2f(210, 20);
    glVertex2f(350, 20);
    glVertex2f(350, 40);
    glVertex2f(330, 60);
    glVertex2f(200, 60);
    glVertex2f(200, 40);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.3f);         //dark neel roof (rat)
    glBegin(GL_POLYGON);
    glVertex2f(230, 60);
    glVertex2f(320, 60);
    glVertex2f(305, 85);
    glVertex2f(245, 85);
    glEnd();
    glColor3f(0.8f, 0.7f, 0.3f);         //Holud (headlight)
    glBegin(GL_QUADS);
    glVertex2f(250, 65);
    glVertex2f(300, 65);
    glVertex2f(290, 80);
    glVertex2f(260, 80);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);         //Kalo tyre
    drawCircle(230, 20, 15);
    drawCircle(320, 20, 15);
    glColor3f(0.2f, 0.2f, 0.2f);         //Dark gray
    drawCircle(230, 20, 7);
    drawCircle(320, 20, 7);
    glPopMatrix();
}
//BUS day
void Car_2()
{
    glPushMatrix();
    glTranslatef(busX, 0, 0);
    glColor3f(1.0f, 1.0f, 1.0f);   //shada
    glBegin(GL_POLYGON);
    glVertex2f(810, 90);
    glVertex2f(805, 120);
    glVertex2f(810, 165);
    glVertex2f(815, 170);
    glVertex2f(990, 170);
    glVertex2f(995, 165);
    glVertex2f(995, 95);
    glVertex2f(990, 90);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);         //Kalo tyre
    drawCircle(850, 90, 15);
    drawCircle(940, 90, 15);
    glColor3f(0.2f, 0.2f, 0.2f);         //Dark gray
    drawCircle(850, 90, 7);
    drawCircle(940, 90, 7);
    glColor3f(0.0f, 1.0f, 1.0f);          //Cyan
    glBegin(GL_POLYGON);
    glVertex2f(805, 125);
    glVertex2f(825, 125);
    glVertex2f(830, 130);
    glVertex2f(830, 170);
    glVertex2f(810, 170);
    glEnd();
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(835, 120);
    glVertex2f(990, 120);
    glVertex2f(990, 160);
    glVertex2f(985, 165);
    glVertex2f(835, 165);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(865, 120);
    glVertex2f(865, 165);   //Window 1
    glVertex2f(866, 120);
    glVertex2f(866, 165);
    glVertex2f(895, 120);
    glVertex2f(895, 165);    //Window 2
    glVertex2f(896, 120);
    glVertex2f(896, 165);
    glVertex2f(925, 120);
    glVertex2f(925, 165);    //Window 3
    glVertex2f(926, 120);
    glVertex2f(926, 165);
    glVertex2f(955, 120);
    glVertex2f(955, 165);    // Window 4
    glVertex2f(956, 120);
    glVertex2f(956, 165);
    glEnd();
    glPopMatrix();
}
//BUS(Rat)  dark gray body
void Car_2_N()
{
    glPushMatrix();
    glTranslatef(busX, 0, 0);
    glColor3f(.5f, 0.5f, 0.5f);           //Gray  bus body(rat)
    glBegin(GL_POLYGON);
    glVertex2f(810, 90);
    glVertex2f(805, 120);
    glVertex2f(810, 165);
    glVertex2f(815, 170);
    glVertex2f(990, 170);
    glVertex2f(995, 165);
    glVertex2f(995, 95);
    glVertex2f(990, 90);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);         //Kalo  tyre
    drawCircle(850, 90, 15);
    drawCircle(940, 90, 15);
    glColor3f(0.2f, 0.2f, 0.2f);          //Gray  rim
    drawCircle(850, 90, 7);
    drawCircle(940, 90, 7);
    glColor3f(0.8f, 0.7f, 0.3f);          //Holud
    glBegin(GL_POLYGON);
    glVertex2f(805, 125);
    glVertex2f(825, 125);
    glVertex2f(830, 130);
    glVertex2f(830, 170);
    glVertex2f(810, 170);
    glEnd();
    glColor3f(0.8f, 0.7f, 0.3f);         //Holud — window
    glBegin(GL_POLYGON);
    glVertex2f(835, 120);
    glVertex2f(990, 120);
    glVertex2f(990, 160);
    glVertex2f(985, 165);
    glVertex2f(835, 165);
    glEnd();
    glColor3f(0,0,0);                     // Kalo  window
    glBegin(GL_LINES);
    glVertex2f(865, 120);
    glVertex2f(865, 165);
    glVertex2f(866, 120);
    glVertex2f(866, 165);
    glVertex2f(895, 120);
    glVertex2f(895, 165);
    glVertex2f(896, 120);
    glVertex2f(896, 165);
    glVertex2f(925, 120);
    glVertex2f(925, 165);
    glVertex2f(926, 120);
    glVertex2f(926, 165);
    glVertex2f(955, 120);
    glVertex2f(955, 165);
    glVertex2f(956, 120);
    glVertex2f(956, 165);
    glEnd();
    glPopMatrix();                        // Transform shesh
}
//BUILDING(Din)

void Building_Shadows()
{
    glColor3f(.392, .412, .519);          //Dark neel gray
    glBegin(GL_QUADS);
    glVertex2f(580,200);
    glVertex2f(650,200);
    glVertex2f(650,430);
    glVertex2f(580,430);
    glEnd();
    glColor3f(.808, .816, .855);          //Halka gray
    glBegin(GL_QUADS);
    glVertex2f(590,200);
    glVertex2f(660,200);
    glVertex2f(660,440);
    glVertex2f(590,440);
    glEnd();
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(680,200);
    glVertex2f(750,200);
    glVertex2f(750,410);
    glVertex2f(680,430);
    glEnd();
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(690,200);
    glVertex2f(760,200);
    glVertex2f(760,420);
    glVertex2f(690,440);
    glEnd();
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(830,250);
    glVertex2f(900,250);
    glVertex2f(900,460);
    glVertex2f(830,460);
    glEnd();
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(840,250);
    glVertex2f(910,250);
    glVertex2f(910,470);
    glVertex2f(840,470);
    glEnd();
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(300,250);
    glVertex2f(300,460);
    glVertex2f(230,450);
    glEnd();
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(240,250);
    glVertex2f(310,250);
    glVertex2f(310,470);
    glVertex2f(240,460);
    glEnd();
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(330,250);
    glVertex2f(400,250);
    glVertex2f(400,460);
    glVertex2f(330,460);
    glEnd();
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(340,250);
    glVertex2f(410,250);
    glVertex2f(410,470);
    glVertex2f(340,470);
    glEnd();
}
//BUILDING(Rat)
void Building_Shadows_N()
{
    glColor3f(.2,.2,.3);                   //dark(rat)
    glBegin(GL_QUADS);
    glVertex2f(580,200);
    glVertex2f(650,200);
    glVertex2f(650,430);
    glVertex2f(580,430);
    glEnd();
    glColor3f(.4,.4,.4);                  //Dark gray
    glBegin(GL_QUADS);
    glVertex2f(590,200);
    glVertex2f(660,200);
    glVertex2f(660,440);
    glVertex2f(590,440);
    glEnd();
    glColor3f(.2,.2,.3);
    glBegin(GL_QUADS);
    glVertex2f(680,200);
    glVertex2f(750,200);
    glVertex2f(750,410);
    glVertex2f(680,430);
    glEnd();
    glColor3f(.4,.4,.4);
    glBegin(GL_QUADS);
    glVertex2f(690,200);
    glVertex2f(760,200);
    glVertex2f(760,420);
    glVertex2f(690,440);
    glEnd();
    glColor3f(.2,.2,.3);
    glBegin(GL_QUADS);
    glVertex2f(830,250);
    glVertex2f(900,250);
    glVertex2f(900,460);
    glVertex2f(830,460);
    glEnd();
    glColor3f(.4,.4,.4);
    glBegin(GL_QUADS);
    glVertex2f(840,250);
    glVertex2f(910,250);
    glVertex2f(910,470);
    glVertex2f(840,470);
    glEnd();
    glColor3f(.2,.2,.3);
    glBegin(GL_QUADS);
    glVertex2f(230,250);
    glVertex2f(300,250);
    glVertex2f(300,460);
    glVertex2f(230,450);
    glEnd();
    glColor3f(.4,.4,.4);
    glBegin(GL_QUADS);
    glVertex2f(240,250);
    glVertex2f(310,250);
    glVertex2f(310,470);
    glVertex2f(240,460);
    glEnd();
    glColor3f(.2,.2,.3);
    glBegin(GL_QUADS);
    glVertex2f(330,250);
    glVertex2f(400,250);
    glVertex2f(400,460);
    glVertex2f(330,460);
    glEnd();
    glColor3f(.4,.4,.4);
    glBegin(GL_QUADS);
    glVertex2f(340,250);
    glVertex2f(410,250);
    glVertex2f(410,470);
    glVertex2f(340,470);
    glEnd();
}
//NIGHT SKY + STARS
void Night_Sky()
{
    glColor3f(0.0f, 0.0f, 0.0f);          //Kalo rat er akash background
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1200,0);
    glVertex2f(1200,600);
    glVertex2f(0,600);
    glEnd();
    glPointSize(3.0f);                    //star er size 3 pixel
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);         //Shada rang
    glVertex2i(50,490);                   //star 1-40
    glVertex2i(140,460);
    glVertex2i(190,470);
    glVertex2i(240,520);
    glVertex2i(290,490);
    glVertex2i(340,500);
    glVertex2i(390,510);
    glVertex2i(440,460);
    glVertex2i(500,520);
    glVertex2i(550,535);
    glVertex2i(590,480);
    glVertex2i(640,510);
    glVertex2i(690,520);
    glVertex2i(740,530);
    glVertex2i(790,500);
    glVertex2i(840,460);
    glVertex2i(890,500);
    glVertex2i(940,530);
    glVertex2i(70,515);
    glVertex2i(170,525);
    glVertex2i(230,535);
    glVertex2i(300,525);
    glVertex2i(350,530);
    glVertex2i(410,520);
    glVertex2i(470,515);
    glVertex2i(530,530);
    glVertex2i(590,510);
    glVertex2i(640,530);
    glVertex2i(710,515);
    glVertex2i(760,500);
    glVertex2i(820,530);
    glVertex2i(890,525);
    glVertex2i(940,500);
    glVertex2i(990,510);
    glVertex2i(1015,515);
    glVertex2i(1115,510);
    glVertex2i(1090,495);
    glVertex2i(1105,535);
    glVertex2i(1085,520);
    glVertex2i(1150,500);
    glEnd();
}
//MAIN FUNCTIONS
void City_Day_Scn()
{
    glClear(GL_COLOR_BUFFER_BIT);         //ager frame mochhe
    Day_Sky();
    sunA();
    Clouds();
    Building_Shadows();
    Ground_D();
    Buildings();
    Trees();
    Car_2();
    Car_1();
    Plane();
    glutSwapBuffers();                    //screen show kore
}
void City_Night_Scn()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Night_Sky();                          //Kalo akash,stars
    Moon();
    Building_Shadows_N();
    Ground_N();
    Buildings_N();
    Trees_N();
    Car_2_N();
    Car_1_N();
    Plane();
    drawRain();
    glutSwapBuffers();
}
//VILLAGE
void drawcircle_v(GLfloat rx, GLfloat ry, GLfloat px, GLfloat py)
{
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416f / 180;  //Degree theke radian convert
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f(x + px, y + py);
    }
    glEnd();
}
//STARS
void drawStar_v()
{
    if (villageIsDay) return;             //Din hole function theke ber hoe jao
    glColor3ub(255, 255, 255);            //Shada
    glPointSize(4.0f);                    //star size 4 pixel
    glBegin(GL_POINTS);                   //star draw shuru
    glVertex2f(120,580);                 //star 1-12
    glVertex2f(280,550);
    glVertex2f(480,570);
    glVertex2f(700,540);
    glVertex2f(850,580);
    glVertex2f(1000,550);
    glVertex2f(1120,520);
    glVertex2f(200,500);
    glVertex2f(400,520);
    glVertex2f(750,500);
    glVertex2f(920,530);
    glVertex2f(1080,480);
    glEnd();
    glPointSize(1.0f);                    //Point size default
}
//SUN,MOON
//day sun holud circle,rat moon  gray+kalo overlap
void drawmoon_v()
{
    if (villageIsDay)
    {
        glColor3ub(255, 215, 0);           //Holud rang
        drawcircle_v(40, 40, 1080, 520);  //sun er dan dike upore,radius 40
    }
    else
    {
        glColor3ub(220, 220, 180);        //Cream rang
        drawcircle_v(40, 40, 350, 530);   //moon main circle
        glColor3ub(13, 13, 51);
        drawcircle_v(32,32,370,540);
    }
}
// CLOUDS
void drawcloud_v()
{
    glPushMatrix();
    glTranslatef(cx_v, 0, 0);
    if(villageIsDay)
        glColor3ub(255, 255, 255);        //day shada cloud
    else
        glColor3ub(80, 80, 120);          //Raat e  neelash cloud
    drawcircle_v(45,35,1080,540);      //cloud 1
    drawcircle_v(35,30,1040,540);      //bam circle(choto)
    drawcircle_v(35,30,1120,540);      //dan circle (choto)
    drawcircle_v(45, 35, 900, 500);       //Cloud 2
    drawcircle_v(35, 30, 860, 500);       //bam circle
    drawcircle_v(35, 30, 940, 500);       //dan circle
    glPopMatrix();
}
//BOAT
void drawboat_v()
{
    glPushMatrix();
    glTranslatef(bx_v, 0, 0);
    glColor3ub(0, 0, 0);                   //Kalo upper body
    glBegin(GL_POLYGON);
    glVertex2d(780, 250);
    glVertex2d(960, 250);
    glVertex2d(1020, 300);
    glVertex2d(720, 300);
    glEnd();
    glColor3ub(205, 133, 63);             //Kath r rong lower body
    glBegin(GL_POLYGON);
    glVertex2d(790, 300);
    glVertex2d(950, 300);
    glVertex2d(920, 350);
    glVertex2d(820, 350);
    glEnd();
    glPopMatrix();
}
//BIRDS
void Birds()
{
    if (!villageIsDay) return;            //rat ebird asbe nah
    glPushMatrix();
    glTranslatef(birdX, 0, 0);
    glColor3f(0.0f, 0.0f, 0.0f);          //Kalo rang
//Bird 1
    glBegin(GL_LINES);
    glVertex2f(50, 520);
    glVertex2f(60, 515);
    glVertex2f(60, 515);
    glVertex2f(70, 520);
    glVertex2f(60, 515);
    glEnd();
//Bird 2
    glBegin(GL_LINES);
    glVertex2f(80, 525);
    glVertex2f(90, 520);
    glVertex2f(90, 520);
    glVertex2f(100, 525);
    glVertex2f(90, 520);
    glEnd();
//Bird 3
    glBegin(GL_LINES);
    glVertex2f(110, 515);
    glVertex2f(120, 510);
    glVertex2f(120, 510);
    glVertex2f(130, 515);
    glVertex2f(120, 510);
    glEnd();
//Bird 4
    glBegin(GL_LINES);
    glVertex2f(150, 530);
    glVertex2f(160, 525);
    glVertex2f(160, 525);
    glVertex2f(170, 530);
    glVertex2f(160, 525);
    glEnd();
//Bird 5
    glBegin(GL_LINES);
    glVertex2f(200, 510);
    glVertex2f(210, 505);
    glVertex2f(210, 505);
    glVertex2f(220, 510);
    glVertex2f(210, 505);
    glEnd();
//Bird 6
    glBegin(GL_LINES);
    glVertex2f(250, 535);
    glVertex2f(260, 530);
    glVertex2f(260, 530);
    glVertex2f(270, 535);
    glVertex2f(260, 530);
    glEnd();
//Bird 7
    glBegin(GL_LINES);
    glVertex2f(300, 505);
    glVertex2f(310, 500);
    glVertex2f(310, 500);
    glVertex2f(320, 505);
    glVertex2f(310, 500);
    glEnd();
//Bird 8
    glBegin(GL_LINES);
    glVertex2f(350, 540);
    glVertex2f(360, 535);
    glVertex2f(360, 535);
    glVertex2f(370, 540);
    glVertex2f(360, 535);
    glEnd();
//Bird 9
    glBegin(GL_LINES);
    glVertex2f(400, 518);
    glVertex2f(410, 513);
    glVertex2f(410, 513);
    glVertex2f(420, 518);
    glVertex2f(410, 513);
    glEnd();

    glPopMatrix();
}
//MAIN  FUNCTION
void Village_Scn()
{
    cx_v += 1.0f;                         //Cloud er X position ber hoi
    if (cx_v > 1200)                      //Screen er bam theke  gele
        cx_v = -1200;                     //Bam dike fire ase

    bx_v+= 3.0f;                      //Bam theke dane jabe
    if (bx_v >1200)
        bx_v = -1200;

    birdX += birdSpeed_v;                 //X position
    if (birdX > 1200)
        birdX = -500;

    if (villageIsDay)
        glClearColor(0.0f, 0.9f, 0.9f, 0.0f);      //day  er background  cyan akash
    else
        glClearColor(0.05f, 0.05f, 0.2f, 0.0f);    //Rat er background dark neel akash
    glClear(GL_COLOR_BUFFER_BIT);               //Screen clear koro

    drawStar_v();
//Ground
    if (villageIsDay)
       glColor3ub(0, 255, 0);             //Bright shobuj
    else
       glColor3ub(0, 100, 0);             //Dark shobuj
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(1200,0);
    glVertex2d(1200,360);
    glVertex2d(0,360);
    glEnd();
//River
    if (villageIsDay)
       glColor3ub(100,149,237);            //Neel din
    else
       glColor3ub(20,40,100);             //Dark neel rat
    glBegin(GL_POLYGON);                  //river upper part
    glVertex2d(720,360);
    glVertex2d(600,180);
    glVertex2d(900,180);
    glVertex2d(1080,360);
    glEnd();
    glBegin(GL_POLYGON);                   //river lower part
    glVertex2d(720,180);
    glVertex2d(600,0);
    glVertex2d(900,0);
    glVertex2d(1080,180);
    glEnd();
    glBegin(GL_POLYGON);                  //river horizontal
    glVertex2d(0,240);
    glVertex2d(0,360);
    glVertex2d(1200,360);
    glVertex2d(1200,240);
    glEnd();
//Hills
    if (villageIsDay)
       glColor3ub(184,134,11);            //Holud badami bam din
    else
       glColor3ub(80,80,20);               //Dark  bam (rat)
    glBegin(GL_POLYGON);                   //Bam hill shuru
    glVertex2d(0,360);
    glVertex2d(420,360);
    glVertex2d(220,540);
    glEnd();

    if (villageIsDay)
       glColor3ub(218,165,32);            //holud day
    else
       glColor3ub(100,100,30);            //Dark (rat)
    glBegin(GL_POLYGON);
    glVertex2d(300,360);
    glVertex2d(780,360);
    glVertex2d(540,560);
    glEnd();

    if (villageIsDay)
        glColor3ub(184,134,11);           //Holud badami
    else
        glColor3ub(80,80,20);             //Dark
    glBegin(GL_POLYGON);
    glVertex2d(650,360);
    glVertex2d(1200,360);
    glVertex2d(950,550);
    glEnd();
    drawboat_v();
//House 1
    glColor3ub(160,82,45);                //Badami  1 chal
    glBegin(GL_POLYGON);
    glVertex2d(120,290);
    glVertex2d(340,290);
    glVertex2d(300,370);
    glVertex2d(150,370);
    glEnd();
    glColor3ub(255,222,173);              //Wheat rang(wall)
    glBegin(GL_POLYGON);
    glVertex2d(140,190);
    glVertex2d(320,190);
    glVertex2d(320,290);
    glVertex2d(140,290);
    glEnd();
    glColor3ub(160,82,45);                //Badami wall(beam)
    glBegin(GL_POLYGON);
    glVertex2d(140,190);
    glVertex2d(320,190);
    glVertex2d(320,175);
    glVertex2d(140,175);
    glEnd();
    glColor3ub(120,60,20);                //Dark badami(door)
    glBegin(GL_POLYGON);
    glVertex2d(230,190);
    glVertex2d(270,190);
    glVertex2d(270,255);
    glVertex2d(230,255);
    glEnd();
//Bam window  rat e holud alo,din-e kath rang
    if (!villageIsDay)
        glColor3ub(255,220,80);           //Holud
    else
        glColor3ub(160,82,45);            //Kath
    glBegin(GL_POLYGON);
    glVertex2d(160,220);
    glVertex2d(200,220);
    glVertex2d(200,260);
    glVertex2d(160,260);
    glEnd();
//Dan window
    if (!villageIsDay)
        glColor3ub(255,220,80);           //Holud
    else
        glColor3ub(160,82,45);            //Kath
    glBegin(GL_POLYGON);
    glVertex2d(280,220);
    glVertex2d(310,220);
    glVertex2d(310,260);
    glVertex2d(280,260);
    glEnd();
//Car
    glPushMatrix();
    glColor3ub(255,0,0);                  //Lal  car body (lower)
    glBegin(GL_POLYGON);
    glVertex2d(100,80);
    glVertex2d(380,80);
    glVertex2d(400,115);
    glVertex2d(80,115);
    glEnd();
    glColor3ub(200,0,0);                  //Dark lal  car roof
    glBegin(GL_POLYGON);
    glVertex2d(130,115);
    glVertex2d(360,115);
    glVertex2d(330,155);
    glVertex2d(160,155);
    glEnd();
    glColor3ub(135,206,235);              //Neel glass
    glBegin(GL_POLYGON);
    glVertex2d(170,120);
    glVertex2d(240,120);
    glVertex2d(235,148);
    glVertex2d(175,148);
    glEnd();
    glColor3ub(135,206,235);
    glBegin(GL_POLYGON);
    glVertex2d(260,120);
    glVertex2d(330,120);
    glVertex2d(325,148);
    glVertex2d(265,148);
    glEnd();
    glColor3ub(0,0,0);                    //Kalo  car tyre
    drawcircle_v(16,16,140,75);           //Bam tyre
    drawcircle_v(16,16,340,75);           //Dan tyre
    glPopMatrix();
//Tree
    glColor3ub(139,69,19);                //Badami(trunk)
    glBegin(GL_POLYGON);
    glVertex2d(360,190);
    glVertex2d(390,190);
    glVertex2d(390,330);
    glVertex2d(360,330);
    glEnd();

    if (villageIsDay)
        glColor3ub(0,128,0);              //Bright shobuj  din
    else
        glColor3ub(0,80,0);               //Dark shobuj  rat
    drawcircle_v(45,45,350,360);         //leaf 1  bam dike circle
    drawcircle_v(45,45,400,360);         //leaf 2  dan dike circle
    drawcircle_v(40,40,375,420);         //leaf 3  upore center
//House 2
    glColor3ub(210,105,30);               //Dark orange roof
    glBegin(GL_POLYGON);
    glVertex2d(430,270);
    glVertex2d(600,270);
    glVertex2d(560,340);
    glVertex2d(470,340);
    glEnd();
    glColor3ub(244,164,96);               //Halka orange wall
    glBegin(GL_POLYGON);
    glVertex2d(450,190);
    glVertex2d(580,190);
    glVertex2d(580,270);
    glVertex2d(450,270);
    glEnd();
    glColor3ub(160,82,45);                //Badami
    glBegin(GL_POLYGON);
    glVertex2d(450,190);
    glVertex2d(580,190);
    glVertex2d(580,175);
    glVertex2d(450,175);
    glEnd();
    glColor3ub(160,82,45);                //Badami door
    glBegin(GL_POLYGON);
    glVertex2d(505,190);
    glVertex2d(545,190);
    glVertex2d(545,245);
    glVertex2d(505,245);
    glEnd();
//Window rat e holud,din-e badami
    if (!villageIsDay)
        glColor3ub(255,220,80);           //Holud alo
    else
        glColor3ub(160,82,45);            //Kath rang
    glBegin(GL_POLYGON);
    glVertex2d(460,220);
    glVertex2d(490,220);
    glVertex2d(490,250);
    glVertex2d(460,250);
    glEnd();

    Birds();         //bird ke call korte se
    drawmoon_v();      //sun and moon ke
    drawcloud_v();       //cloud ke

    glutSwapBuffers();                    // screen e show kore
}
//display callback
void display()
{
    if (showCity)                         //showCity true hole city scene
    {
        if (cityIsDay)
        City_Day_Scn();                   //City din
        else
        City_Night_Scn();                 //City rat
    }
    else
    {
        Village_Scn();                    //Village scene
    }
}
//Timer callbacks
//16ms city
void update1(int value)
{
    carX += carSpeed;                     //Car bam theke dan dike age
    if (carX > 1200)                      //Screen er bar gele
        carX = -200;                      //Bam dike fire ashe(screen er baaire theke)

    busX -= busSpeed;                     //Bus dan theke bam dike age
    if (busX < -1200)                     //Screen er baar gele
        busX = 1250;                      //Dan dike fire ashe

    cloudX += cloudSpeed;
    if (cloudX > 1200)
        cloudX = -1000;

    planeX -= planeSpeed;
    if (planeX < -200)
        planeX = 1300;

    glutPostRedisplay();                  //Redraw
    glutTimerFunc(16, update1, 0);        //16ms pore abar call hosse
}
//Keyboard,Mouse
void keypressed(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        carSpeed += 2.0f;
        busSpeed += 2.0f;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        carSpeed -= 2.0f;
        if (carSpeed < 0)
        carSpeed = 0;
        busSpeed -= 2.0f;
        if (busSpeed < 0)
        busSpeed = 0;
    }
}
//V = Village,C = City,D = Din,N = Rat,R = Rain toggle,ESC = exit
void keyboard1(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'v':
    case 'V':
    showCity = false;                     //V key
    glutPostRedisplay();                  //Redraw request
    break;
    case 'c':
    case 'C':
    showCity = true;                      //C key
    glutPostRedisplay();
    break;
    case 'd':
    case 'D':
    if (showCity)
    cityIsDay = true;                      //D key +city  din mode
    else
    villageIsDay = true;                  //D key + village  din mode
    glutPostRedisplay();
    break;
    case 'n':
    case 'N':
    if (showCity)
    cityIsDay = false;                    //N key + city  rat mode
    else
    villageIsDay = false;                 //N key + village  rat mode
    glutPostRedisplay();
    break;
    case 'r':
    case 'R':
    rainday = !rainday;                   //R key  rain on/off toggle
    break;
    case 27:
    exit(0);                              //ESC key — program bondho
    }
}
//Mouse click
//City:Left click = mall light,Right click = hospital light
//Village: Left click =din/raat toggle
void mouse(int button, int state, int x, int y)
{
    if (showCity)                              //City scene active
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)            //Left click
        {
            mallLightOn = !mallLightOn;                               //Mall er light on/off toggle
            glutPostRedisplay();
        }
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)            //Right click
        {
            hospitalLightOn = !hospitalLightOn;                                //Hospital er light on/off toggle
            glutPostRedisplay();
        }
    }
    else                                                      //Village scene active
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)          //Left click
        {
            villageIsDay = !villageIsDay;                        //Din/raat toggle
            glutPostRedisplay();
        }
    }
}
//MAIN FUNCTION
int main(int argc, char** argv)
{
    glutInit(&argc, argv);                             //initialize kore
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Jashore And Rupdia:");
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);        //Default background color(sky blue)
    glMatrixMode(GL_PROJECTION);                    //Projection matrix select kore
    glLoadIdentity();                               //Matrix reset
    gluOrtho2D(0, 1200, 0, 600);
    glutDisplayFunc(display);                       //Display callback
    glutKeyboardFunc(keyboard1);                    //Keyboard callback
    glutSpecialFunc(keypressed);                    //Arrow key callback
    glutTimerFunc(0, update1, 0);                   //Animation timer shuru
    initRain();                                     //Rain drop initial position set
    glutTimerFunc(0, updateRain, 0);                //Rain animation timer shuru
    glutMouseFunc(mouse);                           //Mouse callback
    glutMainLoop();                                 //program cholte thakbe
    return 0;
}
