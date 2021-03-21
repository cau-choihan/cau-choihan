#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

SceneID scene1;
ObjectID startbutton, restartbutton, fake;
ObjectID board[3][3];

ObjectID Y[2];
TimerID timer1, timer2, timer3, timer4, timer5;

struct Block
{
    ObjectID id;
    int x, y;
    bool blank;
};

//int pX[3] = { 12 + 85, 182 + 85, 352 + 85 };
//int pY[3] = { 90 + 87, 265 + 87, 441 + 87 };
int pX[3] = { 12, 182, 352 };
int pY[3] = { 90, 265, 441 };
int radius = { 42 };
string filename[3][3] = { { "1.png", "2.png", "3.png" }, { "4.png", "5.png", "6.png" }, { "7.png", "8.png", "10.png" } };

Block pocket[3][3] = {};

ObjectID createObject(const char* name, const char* image, SceneID scene, int x, int y, bool shown) {
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown) {
        showObject(object);
    }
    return object;
}

bool CheckIn(int x, int y, int cx, int cy, int r) {
    return (x > cx - r && x < cx + r && y > cy - r && y < cy + r);
}

void timerCallback(TimerID timer) {
    if (timer == timer2) {
        setTimer(timer2, 1.0f);
        startTimer(timer2);
        increaseTimer(timer1, 1.0f);
    }
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
    //showMessage("zzzzzz");
    //showMessage(to_string(x).c_str());
    //showMessage(to_string(object).c_str());
    //showMessage(to_string(pocket[1][2].id).c_str());
    //showMessage(to_string(object).c_str());
    if (object == startbutton) {
        hideObject(fake);
        hideObject(startbutton);
        showObject(restartbutton);
        setTimer(timer1, 0.0f);
        setTimer(timer2, 1.0f);
        setTimer(timer2, 1.0f);
        startTimer(timer2);
        
    }
    else if(object == restartbutton){
        setTimer(timer2, 1.0f);
        setTimer(timer1, 0.0f);
        startTimer(timer2);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                pocket[i][j].id = createObject(filename[i][j].c_str(), filename[i][j].c_str(), scene1, pX[i], pY[j], true);
                pocket[i][j].x = pX[i];
                pocket[i][j].y = pY[j];
                pocket[i][j].blank = false;
            }
        }
        pocket[2][2].blank = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                locateObject(pocket[i][j].id, scene1, pX[i], pY[j]);
                showObject(pocket[i][j].id);
            }
        }
    }
    else{

        int blankPX, blankPY;

        for (int i = 0; i < 3; i++) {            //빈칸이 담긴 주머니 좌표 기억
            for (int j = 0; j < 3; j++) {
                if (pocket[i][j].blank == true) {
                    blankPX = i;
                    blankPY = j;
                }
            }
        }

        //showMessage(to_string(pocket[blankPX][blankPY].id).c_str());
        //to_string(object).c_str() == to_string(pocket[i][j].id).c_str()

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (object == pocket[i][j].id) { // 그 클릭한 지점의 사진을 담은 주머니 발견!
                   //showMessage(to_string(object).c_str());
                    if (((blankPX + 1 == i) && (blankPY == j)) || ((blankPX - 1 == i) && (blankPY == j)) || ((blankPX == i) && (blankPY + 1 == j)) || ((blankPX == i) && (blankPY - 1 == j))) {
                        // 만약 빈칸의 상하좌우 좌표와 그 클릭 주머니의 좌표가 일치한다면
                        int tmpX, tmpY;
                        ObjectID tmpId;
                        bool tmpBlank;

                        //showMessage("자리를 바꿀 수 있습니다!");
                        tmpX = pocket[i][j].x;
                        tmpY = pocket[i][j].y;
                        tmpId = pocket[i][j].id;
                        tmpBlank = pocket[i][j].blank;
                        //pocket[i][j].x = pocket[blankPX][blankPY].x;
                        //pocket[i][j].y = pocket[blankPX][blankPY].y;
                        pocket[i][j].id = pocket[blankPX][blankPY].id;
                        pocket[i][j].blank = pocket[blankPX][blankPY].blank;
                        //pocket[blankPX][blankPY].x = tmpX;
                        //pocket[blankPX][blankPY].y = tmpY;
                        pocket[blankPX][blankPY].id = tmpId;
                        pocket[blankPX][blankPY].blank = tmpBlank;

                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                locateObject(pocket[i][j].id, scene1, pX[i], pY[j]);
                                showObject(pocket[i][j].id);
                            }
                        }


                        /*Block tmpPocket = {};
                        tmpPocket = pocket[i][j];
                        pocket[i][j] = pocket[blankPX][blankPY];
                        pocket[blankPX][blankPY] = tmpPocket;*/
                        // 그 둘 주머니 안의 내용을 바꿔치기 함.
                    }

                }
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                locateObject(pocket[i][j].id, scene1, pX[i], pY[j]);
                showObject(pocket[i][j].id);
            }
        }

        /*for (int i = 0; i < 3; i++) {
           for (int j = 0; j < 3; j++) {
              pocket[i][j].x = 12;
              pocket[i][j].y = 265;
           }
        }*/

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                locateObject(pocket[i][j].id, scene1, pocket[i][j].x, pocket[i][j].y);
                showObject(pocket[i][j].id);
            }
        }
        if (pocket[0][0].x == 12 &&
            pocket[0][0].y == 90 &&
            pocket[0][1].x == 12 &&
            pocket[0][1].y == 265 &&
            pocket[0][2].x == 12 &&
            pocket[0][2].y == 441 &&
            pocket[1][0].x == 182 &&
            pocket[1][0].y == 90 &&
            pocket[1][1].x == 182 &&
            pocket[1][1].y == 265 &&
            pocket[1][2].x == 90 &&
            pocket[1][2].y == 441 &&
        pocket[2][0].x == 352 &&
        pocket[2][0].y == 90 &&
        pocket[2][1].x == 352 &&
        pocket[2][1].y == 265) {
            showMessage("clear! \ 상단에 클리어한 시간이 나와있어요!");
            stopTimer(timer2);
        }
    }
   
    
}



int main()
{



    scene1 = createScene("슬라이딩퍼즐", "picture.png");


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pocket[i][j].id = createObject(filename[i][j].c_str(), filename[i][j].c_str(), scene1, pX[i], pY[j], true);
            pocket[i][j].x = pX[i];
            pocket[i][j].y = pY[j];
            pocket[i][j].blank = false;
        }
    }
    pocket[2][2].blank = true;   // 빈칸은 빈칸으로 만듦

    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            locateObject(pocket[i][j].id, scene1, pX[i], pY[j]);
            showObject(pocket[i][j].id);
        }
    }

    
    fake = createObject("fake", "piece1.png", scene1, 12, 90, true);
    startbutton = createObject("start", "start.png", scene1, 215, 90, true);
    restartbutton = createObject("restart", "restart.png", scene1, 600,90, false);

    timer1 = createTimer(0.0F);
    showTimer(timer1);
    timer2 = createTimer(1.0F);

    startGame(scene1);

    

    system("pause");
}