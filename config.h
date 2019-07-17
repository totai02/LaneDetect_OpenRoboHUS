#ifndef CONFIG_H
#define CONFIG_H


class Config
{
public:
    static int LOOK_AT;
    static int LANE_WIDTH;
    static int WIDTH;
    static int HEIGHT;

	static int LOW_H;
	static int LOW_S;
	static int LOW_V;
	
	static int HIGH_H;
	static int HIGH_S;
	static int HIGH_V;
	
	static int SKY_LINE;

    static int WINDOW_WIDTH;
    static int WINDOW_HEIGHT;

    static float KP;
    static float KI;
    static float KD;

    static int BTN1;
    static int BTN2;
    static int BTN3;
    static int BTN4;

    static int sPWM1_1;
    static int sPWM1_2;
    static int sPWM2_1;
    static int sPWM2_2;

    static int SERVO;
    static int SERVO2;

    static int SERVO_ORIG;
    static int SERVO2_ORIG;

    static float VELOCITY;
};

#endif // CONFIG_H
