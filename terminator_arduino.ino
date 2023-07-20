#include <FastLED.h>
#include <Servo.h>
#include <ServoEasing.hpp>

// by OneIdMONstr (you can find me on Twitter, Instagram, Youtube, Reddit)
// Version 1.0


//#define SERVO_INIT  Run this during build, then comment out!
//#define SERVO_INIT

// !!!! !!!! !!!! !!!! !!!! !!!! !!!! IMPORTANT !!!! !!!! !!!! !!!! !!!! !!!! !!!!
//
// Install the following librarys via Sketch - Include library - Manage Libraries
//
// - FastLED
// - ServoEasing
//
// !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!! !!!!


#define FRONT_LEDS_MIDDLE_PIN             2
#define FRONT_LEDS_MIDDLE_AMOUNT          5

#define SERVO_EYES_LEFT_RIGHT_PIN         3
#define SERVO_EYES_UP_DOWN_PIN            4

#define SERVO_HEAD_LEFT_RIGHT_PIN         5
#define SERVO_HEAD_UP_DOWN_RIGHT_PIN      6
#define SERVO_HEAD_UP_DOWN_LEFT_PIN       7

#define LED_TYPE    WS2812B
#define SATURATION 254
#define COLOR_RED   96

#define COLOR_ORDER RGB

CRGB frontLEDsMiddle[FRONT_LEDS_MIDDLE_AMOUNT];

ServoEasing servo_eyes_left_right; // Define our Servo
ServoEasing servo_eyes_up_down; // Define our Servo
ServoEasing servo_head_left_right; // Define our Servo
ServoEasing servo_head_up_down_left; // Define our Servo
ServoEasing servo_head_up_down_right; // Define our Servo

// EYES
int i_servo_eyes_init_pos_up_down = 90; // - up, + down
int i_servo_eyes_up_down_max_angle = 16;

int i_servo_eyes_init_pos_left_right = 90; //- right, + left
int i_servo_eyes_left_right_max_angle = 25;

// HEAD
int i_servo_head_up_down_max_angle = 35;
int i_servo_head_init_pos_up_down_left = 120; //140; // - down, +up
int i_servo_head_init_pos_up_down_right = 50; // 50; // - up  , +down

int i_servo_head_init_pos_left_right = 90; //- right, +left, max +-30
int i_servo_head_left_right_max_angle = 30;

int iDelay = 1000;

void servo_init()
{
  servo_eyes_up_down.setEaseTo(i_servo_eyes_init_pos_up_down);
  servo_eyes_left_right.setEaseTo(i_servo_eyes_init_pos_left_right);

  servo_head_up_down_right.setEaseTo(i_servo_head_init_pos_up_down_right);
  servo_head_up_down_left.setEaseTo(i_servo_head_init_pos_up_down_left);
  servo_head_left_right.setEaseTo(i_servo_head_init_pos_left_right);
  
  synchronizeAllServosStartAndWaitForAllServosToStop();
  
  servo_eyes_left_right.detach();
  servo_eyes_up_down.detach();
  servo_head_up_down_right.detach();
  servo_head_up_down_left.detach();
  servo_head_left_right.detach();
  
  while(1)
  {
    delay(100);
  }

}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ SETUP +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup() {

  FastLED.addLeds<LED_TYPE, FRONT_LEDS_MIDDLE_PIN, COLOR_ORDER>(frontLEDsMiddle, FRONT_LEDS_MIDDLE_AMOUNT).setCorrection( TypicalLEDStrip );

  FastLED.show();

  servo_eyes_left_right.attach(SERVO_EYES_LEFT_RIGHT_PIN);
  servo_eyes_up_down.attach(SERVO_EYES_UP_DOWN_PIN);
  servo_head_up_down_right.attach(SERVO_HEAD_UP_DOWN_RIGHT_PIN);
  servo_head_up_down_left.attach(SERVO_HEAD_UP_DOWN_LEFT_PIN);
  servo_head_left_right.attach(SERVO_HEAD_LEFT_RIGHT_PIN);

  //servo_head_up_down_right.write(i_servo_head_init_pos_up_down_right);
  //servo_head_up_down_left.write(i_servo_head_init_pos_up_down_left);
  //servo_head_left_right.write(i_servo_head_init_pos_left_right);

  //servo_eyes_left_right.detach();
  //servo_eyes_up_down.detach();

  //delay(300);
  setSpeedForAllServos(50);

  servo_eyes_left_right.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default
  servo_eyes_up_down.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default
  servo_head_left_right.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default
  servo_head_up_down_left.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default
  servo_head_up_down_right.setEasingType(EASE_CUBIC_IN_OUT); // EASE_LINEAR is default

// Run this bevor installing the gears!
#ifdef SERVO_INIT  
  servo_init();
#endif

  servo_eyes_up_down.setEaseTo(i_servo_eyes_init_pos_up_down + i_servo_eyes_up_down_max_angle + 5);
  servo_eyes_left_right.setEaseTo(i_servo_eyes_init_pos_left_right);

  servo_head_up_down_right.setEaseTo(i_servo_head_init_pos_up_down_right + i_servo_head_up_down_max_angle);
  servo_head_up_down_left.setEaseTo(i_servo_head_init_pos_up_down_left - i_servo_head_up_down_max_angle);
  servo_head_left_right.setEaseTo(i_servo_head_init_pos_left_right);

  synchronizeAllServosStartAndWaitForAllServosToStop();

  set_eye(0, 20);
  delay(50);
  //servo_eyes_up_down.write(i_servo_eyes_init_pos_up_down);
  servo_eyes_left_right.detach();
  servo_eyes_up_down.detach();

  //servo_head_up_down_right.detach();
  //servo_head_up_down_left.detach();
  servo_head_left_right.detach();


  delay(500);

  init_lights();

  servo_eyes_left_right.attach(SERVO_EYES_LEFT_RIGHT_PIN);
  servo_eyes_up_down.attach(SERVO_EYES_UP_DOWN_PIN);
  servo_head_left_right.attach(SERVO_HEAD_LEFT_RIGHT_PIN);
  //servo_head_up_down_left.attach(SERVO_HEAD_UP_DOWN_LEFT_PIN);
  //servo_head_up_down_right.attach(SERVO_HEAD_UP_DOWN_RIGHT_PIN);

}

long posEyesHorizEnd = 0;
long posEyesVertEnd = 0;

long posHeadVertLeftEnd = 0;
long posHeadVertRightEnd = 0;
long posHeadHorizEnd = 0;

long timeStart = 0;

void set_eye(int iBrightness, int iDelay) {

  for (int i = 0; i < FRONT_LEDS_MIDDLE_AMOUNT; i++) {
    frontLEDsMiddle[i].setHSV(COLOR_RED , SATURATION, iBrightness);
  }
  FastLED.show();
  delay(iDelay);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ INIT_LIGHTS +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_lights() {

  int i, j;

  set_eye(0, 2000);

  for (i = 0; i < 40; i++) {
    set_eye(i, 80);
  }
  delay(500);


  for (i = 40; i > 20; i--) {
    set_eye(i, 20);
  }
  for (i = 0; i < 40; i++) {
    set_eye(i, 80);
  }

  set_eye(0, 20);
  set_eye(40, 220);
  set_eye(0, 20);
  set_eye(30, 20);
  set_eye(0, 30);
  set_eye(30, 600);
  set_eye(0, 20);
  set_eye(30, 20);
  set_eye(0, 100);
  set_eye(30, 250);
  set_eye(0, 100);
  set_eye(30, 20);
  set_eye(0, 20);
  set_eye(30, 200);
  set_eye(0, 80);
  set_eye(50, 200);
  set_eye(0, 80);
  set_eye(70, 200);
  set_eye(0, 300);
  set_eye(10, 40);
  set_eye(0, 700);
  set_eye(100, 20);

  timeStart = millis();

  return;
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ HEAD_VERT_LEFT +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void head_vert_left() {
  int iAngle = i_servo_head_init_pos_up_down_left + ( (float)((float)(posHeadVertLeftEnd / 100.0) *
               (float)i_servo_head_up_down_max_angle));
  servo_head_up_down_left.setEaseTo(iAngle);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ HEAD_VERT_RIGHT ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void head_vert_right() {
  int iAngle = i_servo_head_init_pos_up_down_right - ( (float)((float)(posHeadVertRightEnd / 100.0) *
               (float)i_servo_head_up_down_max_angle));
  servo_head_up_down_right.setEaseTo(iAngle);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ HEAD_HORIZ +#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void head_horiz() {
  int iAngle = i_servo_head_init_pos_left_right - ( (float)((float)(posHeadHorizEnd / 100.0) *
               (float)i_servo_head_left_right_max_angle));
  servo_head_left_right.setEaseTo(iAngle);
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ EYES_HORIZ +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void eyes_horiz() {
  int iAngle = i_servo_eyes_init_pos_left_right - ( (float)((float)(posEyesHorizEnd / 100.0) *
               (float)i_servo_eyes_left_right_max_angle));
  servo_eyes_left_right.setEaseTo(iAngle);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ EYES_VERT ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void eyes_vert() {
  int iAngle = i_servo_eyes_init_pos_up_down - ( (float)((float)(posEyesVertEnd / 100.0) *
               (float)i_servo_eyes_up_down_max_angle));
  servo_eyes_up_down.setEaseTo(iAngle);
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ LOOP ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop(void)
{
  int iX;
  int iY;

  static int count = 0;
  char text[1000];
  long timeNow = millis();

  // new Random values
  if (timeNow > timeStart + iDelay) {

    timeStart = millis();

    iX = 0;
    iY = 0;

    posEyesHorizEnd = random(-100, 100);
    posEyesHorizEnd *= 1.5;
    if (posEyesHorizEnd > 100) {
      posEyesHorizEnd = 100;
    }
    if (posEyesHorizEnd < -100) {
      posEyesHorizEnd = -100;
    }

    posEyesVertEnd = random(-60, 60);

    posHeadVertLeftEnd = posEyesVertEnd;
    posHeadVertRightEnd = posEyesVertEnd;
    posHeadHorizEnd = posEyesHorizEnd;

    iDelay = random(1000, 3000);
  }

  int iSpeed;
  if (random(0, 100) < 80) { // 80% of the time slow
    iSpeed = random(10, 30);
  } else {
    iSpeed = random(30, 100 /*200*/);
  }

  setSpeedForAllServos(iSpeed);

  servo_eyes_left_right.setSpeed(iSpeed * 2);
  servo_eyes_up_down.setSpeed(iSpeed * 2);

  servo_head_up_down_right.setSpeed(iSpeed / 2);
  servo_head_up_down_left.setSpeed(iSpeed / 2);
  servo_head_left_right.setSpeed(iSpeed / 2);

  eyes_horiz();
  eyes_vert();

  head_vert_left();
  head_vert_right();
  head_horiz();

  synchronizeAllServosStartAndWaitForAllServosToStop();

  return;

}
