#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	p_error = 0;
	i_error = 0;
	d_error = 0;
	output = 0;
	acumulated_error = 0;
	counter = 0;
	twiddle_counter = 0;
	(*this).Kp = Kp;
	(*this).Ki = Ki;
	(*this).Kd = Kd;
	dKp = 0.2;
	dKi = 0.001;
	dKd = 1;
}

void PID::UpdateError(double cte) {
	i_error += cte;
	d_error = cte - p_error;
	p_error = cte;
	acumulated_error += cte * cte;
	counter += 1;
}

double PID::UpdateOutput() {

	output = -Kp * p_error - Kd * d_error - Ki * i_error;

	return output;
}

double PID::TotalError() {

	return acumulated_error;
}


