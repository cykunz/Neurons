#ifndef NEURON_H
#define NEURON_H

#include <vector>
using namespace std;

/*	Constants needed for the calculations	*/
const double dt = 0.02; /*	20 ms	*/
const double MembraneThreshold = 0.2 /*	20 mV	*/;
const double MembraneReset = 0.0; /*	10 mV	*/
const double RefractoryPeriod = 0.002 /*	2 ms, = R*C	*/;
const double Resistance = 0.002; 
const double Capacity =  1.0;

class Neuron {
	private:	
		/*	The neuron is characterized by the input current, membrane potential
		 * 	number of spikes, time at which the spikes occured, the present time
		 * 	and can be refractory or not.	*/
		
		vector<double> time_;
		double input_current_;
		double membrane_potential_;
		int spikes_;
		double present_time_;
		bool is_refractory_;
	
	
	public:
	Neuron(vector<double> time = vector<double>(0.0), double input=0.0, double potential=0.0, int spikes=0, double present=0.0, bool refractory=false); 
	~Neuron()=default;
	
	/*	Getters	*/
	double getInputCurrent() const;
	double getMembranePotential() const;
	double getMembraneThreshold() const;
	double getPresentTime() const;
	bool getRefractory() const;
	int getSpikes() const;
	vector<double> getTime() const;
	
	
	/*	Setters	*/
	void setInputCurrent(double const& new_input);
	void setMembranePotential(double const& new_potential);
	void setPresentTime(double const& present);
	void setRefractory(bool const& is_refractory);
	void setSpikes(int const& new_spikes);
	void setTime(vector<double> const& new_time);
	
	/*	Method adding the time of a spike*/
	void addTimeValue(double const& new_time_value);
	/*	Method displaying the time values of the spikes	*/
	void showTimeValues() const;
	/*	Method calculating the membrane potential after a certain 
	 * 	time interval	*/
	double MembranePotentialEquation(double const& time_interval) const;
	/*	Method updating the neuron's membrane potential during a 
	 * 	given time interval	*/
	void update(double const& timeA, double const& timeB, double const& input);

};

#endif
