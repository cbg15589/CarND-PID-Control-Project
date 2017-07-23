#ifndef PID_H
#define PID_H

class PID {
public:

	int counter;
	int twiddle_counter;
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double acumulated_error;
  double best_acumulated_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  double best_Kp;
  double best_Ki;
  double best_Kd;
  double dKp;
  double dKi;
  double dKd;

  /*
  * Output
  */
  double output;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  /*
  * Calculate the PID output.
  */
  double UpdateOutput();

};

#endif /* PID_H */
