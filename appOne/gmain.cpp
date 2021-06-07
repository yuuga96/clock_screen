#if 1//�������Ń^�C�v���������͂������P�ɂ��Ă�������
#include"libOne.h"
#include<time.h>
void gmain() {
    window(1000, 1000);
    float x, y, deg = 0;
    float second = 0, minute = 0,hour = 0;
    angleMode(DEGREES);
    time_t stdTime;
    struct tm local;
    while (notQuit) {
        time(&stdTime);
        localtime_s(&local, &stdTime);
        second = local.tm_sec;
        minute = local.tm_min;
        hour = local.tm_hour;


        //second += 20;
        //if (second >= 60) { minute++; second = 0; }
        //if (minute >= 60) { hour++; minute = 0; }
        clear(200);
       
        deg = 30 * hour + 30 * minute / 60;
        x = sin(deg) * 300;
        y = -cos(deg) * 300;
        strokeWeight(20);
        line(500, 500, 500 + x, 500 + y);
        
        
        deg = 6 * minute + 6 * second /60;
        x = sin(deg) * 400;
        y = -cos(deg) * 400;
        strokeWeight(20);
        line(500, 500, 500+x, 500+y);

        deg = 6 * second;
        x = sin(deg) * 400;
        y = -cos(deg) * 400;
        strokeWeight(5);
        line(500, 500, 500 + x, 500 + y);
    }
}


#else
//���݈ȉ��̃R�[�h���L���ɂȂ��Ă��܂�
#include"libOne.h"
#include<time.h>
//�b�j�A���j�A���j�̃f�[�^�i�p��Őj��hand�j
struct HAND {
    float deg, scale, satulation, value, weight;
};
//���v�f�[�^
struct CLOCK {
    float num, diameter, radius;
    float sx=0, sy=0, hue=0;
    int hour=0, minute=0, second=0;
    struct HAND hourHand   = { 0, 0.56f, 200,  255, 40 };
    struct HAND minuteHand = { 0, 0.8f,  100,  255, 30 };
    struct HAND secondHand = { 0, 0.8f,  255,  128, 10 };
};
//���ݎ������f�[�^�ɃZ�b�g����
void setTime(struct CLOCK& c) {
    if (!isPress(KEY_SPACE)) {
        //���A���A�b���擾
        time_t stdTime= time(NULL);//�W�����Ԃ��擾
        struct tm local;
        localtime_s(&local, &stdTime);//���[�J��������
        c.hour = local.tm_hour;
        c.minute = local.tm_min;
        c.second = local.tm_sec;
    }
    else {
        //�X�y�[�X�������Ɛj����������
        c.second += 5;
        if (c.second >= 60) { c.minute++; c.second = 0; }
        if (c.minute >= 60) { c.hour += 1; c.minute = 0; }
        if (c.hour >= 24) {c.hour = 0;}
    }
}
//�e�j�̕`��Ŏg�p����֐�
void draw(const struct CLOCK& c, const struct HAND& h) {
    strokeWeight(h.weight / c.num);
    stroke(c.hue, h.satulation, h.value);
    float ex = c.sx + sin(h.deg) * (c.radius-30) * h.scale;
    float ey = c.sy - cos(h.deg) * (c.radius-30) * h.scale;
    line(c.sx, c.sy, ex, ey);
}
//���v�̕`��
void draw(struct CLOCK& c) {
    //�~��
    noStroke();
    fill(c.hue, 200, 255);
    circle(c.sx, c.sy, c.diameter);
    fill(c.hue, 30, 255);
    circle(c.sx, c.sy, c.diameter-150/c.num);
    //��
    c.hourHand.deg = (c.hour * 30) + 30 * (c.minute / 60.0f);
    draw(c, c.hourHand);
    //��
    c.minuteHand.deg = (c.minute * 6) + 6 * (c.second / 60.0f);
    draw(c, c.minuteHand);
    //�b
    c.secondHand.deg = c.second * 6;
    draw(c, c.secondHand);
    //�b�j�̗v
    strokeWeight(20 / c.num);
    point(c.sx, c.sy);
}

void gmain() {
    window(1080, 1080, full);
    angleMode(DEGREES);
    colorMode(HSV);
    struct CLOCK clock;
    clock.num = 1;
    clock.diameter = height / clock.num;
    clock.radius = clock.diameter / 2;
    while (notQuit) {
        if (isPress(KEY_D) || isPress(KEY_A) ||
            isTrigger(KEY_W) || isTrigger(KEY_S)) {
            if (isPress(KEY_D) )++clock.num;
            if (isPress(KEY_A) && clock.num > 1)clock.num--;
            if (isTrigger(KEY_W))clock.num++;
            if (isTrigger(KEY_S) && clock.num > 1)clock.num--;
            clock.diameter = height / clock.num;
            clock.radius = clock.diameter / 2;
        }
        setTime(clock);
        clear(55);
        for (int j = 0; j < clock.num; j++) {
            clock.sy = clock.radius + clock.diameter * j;
            for (int i = 0; i < clock.num; i++) {
                clock.sx = clock.radius + clock.diameter * i;
                clock.hue = 360.0f / (clock.num*clock.num) * (j * clock.num + i)+25;
                draw(clock);
            }
        }
    }
}
#endif