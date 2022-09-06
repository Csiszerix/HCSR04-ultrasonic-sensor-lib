#include "HCSR04.h"
////////////////////////////////////consttruct/destruct
void HCSR04::init(int out, int echo[], int n)
{
	this->out = out;
	this->echo = echo;
	this->n = n;
	this->updateSpeed(14.5);
	pinMode(this->out, OUTPUT);
	for (int i = 0; i < n; i++)
		pinMode(this->echo[i], INPUT);
}
HCSR04::HCSR04(int out, int echo) { this->init(out, new int[1]{echo}, 1); }
HCSR04::HCSR04(int out, int echo[], int n) { this->init(out, echo, n); }
HCSR04::~HCSR04()
{
	~this->out;
	delete[] this->echo;
	~this->n;
}

///////////////////////////////////////////////////dist
float HCSR04::dist(int n) const
{
	digitalWrite(this->out, LOW);
	delayMicroseconds(2);
	digitalWrite(this->out, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->out, LOW);
	noInterrupts();
	float d = pulseIn(this->echo[n], HIGH, 23529.4); // max sensor dist ~4m
	interrupts();
	return d / 20000 * this->speed; // in cm
}

float HCSR04::dist() const { return this->dist(0); }

///////////////////////////////////////////////////speed of sound
void HCSR04::updateSpeed(float temp){
	this->speed=331.3+0.6*temp;	
}