/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "utils.h"
#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
  Kp = Kpi;
  Ki = Kii;
  Kd = Kdi;
  output_lim_max = output_lim_maxi;
  output_lim_min = output_lim_mini;
  sum_cte = 0.0;
  diff_cte = 0.0;
  cte = 0.0;
  first_input = true;
}

void PID::UpdateError(double cte_i) {
   /**
   * TODO: Update PID errors based on cte.
   **/

   if (first_input)
   {
      diff_cte = 0;
      first_input = false;
   }
   else if (std::abs(delta_time) < 1e-6)
   {
      diff_cte = 0;
   }
   else
   {
      diff_cte = (cte_i - cte) / delta_time;
   }

   sum_cte += cte_i * delta_time;
   cte = cte_i;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
   double control = -Kp * cte - Kd * diff_cte - Ki * sum_cte;

   // clamp to min max range
   control = utils::clampD(control, output_lim_min, output_lim_max);

   return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   delta_time = new_delta_time;
}