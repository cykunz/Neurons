#include <iostream>
#include <cmath>
#include "Neuron.hpp"
#include <vector>
#include <fstream>

using namespace std;

Neuron::Neuron(vector<double> time, double input, double potential, int spikes, double present, bool refractory)
	: 	time_(time), input_current_(input), membrane_potential_(potential), spikes_(spikes), present_time_(present),
		is_refractory_(refractory)
	{}
/***************************************************/
/*	Getters	*/
double Neuron::getInputCurrent() const
{	return input_current_;
}

double Neuron::getMembranePotential() const
{	return membrane_potential_;
}

double Neuron::getMembraneThreshold() const
{	return MembraneThreshold;
}

double Neuron::getPresentTime() const
{	return present_time_;
}

bool Neuron::getRefractory() const
{	return is_refractory_;
}

int Neuron::getSpikes() const
{	return spikes_;
}

vector<double> Neuron::getTime() const
{	return time_;
}
/***************************************************/
/*	Setters	*/
void Neuron::setInputCurrent(double const& new_input)
{	input_current_=new_input;
}

void Neuron::setMembranePotential(double const& new_potential)
{	membrane_potential_=new_potential;
}

void Neuron::setPresentTime(double const& present)
{	present_time_=present;
}

void Neuron::setRefractory(bool const& new_refractory)
{	is_refractory_=new_refractory;
}

void Neuron::setSpikes(int const& new_spikes)
{	spikes_=new_spikes;
}

void Neuron::setTime(vector<double> const& new_time)
{	time_=new_time;
}
/***************************************************/
void Neuron::addTimeValue(double const& new_time_value)
{	time_.push_back(new_time_value);
}

void Neuron::showTimeValues() const
{	
	if(!time_.empty()){
		for(size_t i(1); i<time_.size(); ++i)
		{	cout<<"Spike n°"<<i<<"	: "<< time_[i]<<endl;
			
		}
		cout<<"Total of "<<time_.size()-1<<" spikes."<<endl;
	} else { 
		cout<<"No value present."<<endl;
	}
	
	
}

double Neuron::MembranePotentialEquation(double const& time_interval) const
{	/*	Declaration of a variable to facilitate calculations.	*/
	double e(exp(-(time_interval)/(RefractoryPeriod)));

	return (getMembranePotential()*e) + (getInputCurrent()*Resistance*(1-(e)));
}
void Neuron::update(double const& timeA, double const& timeB, double const& input)
{	/*	We start the simulation at timeA.	*/
	setPresentTime(timeA);
	setInputCurrent(input);
	double spike_time(0.0);
	int n(0);
	
	/*	The file we want to keep membrane potential values in.	*/
	ofstream file("neurontext.txt");
	
	/*	While the present time is inferior to the superior time limit...	*/
	while(getPresentTime()<timeB){
		
			/*	If the neuron is refractory, and if the neuron is not in the refractory period anymore, 
			 * 	then it isn't refractory anymore.	*/
			 if(getRefractory())
			{	
				if(getPresentTime()>=spike_time+RefractoryPeriod)
				{
				setRefractory(false);
				}	
					
			}
			/*	If the membrane potential reaches the threshold, we have to record 
			 * 	the time value of the spike. By definition, the neuron is then
			 * 	refractory and the membrane potentiel is reset.	*/
			else {
				if(getMembranePotential()>=getMembraneThreshold())
			{	spike_time=getPresentTime();
				addTimeValue(spike_time);
				setRefractory(true);
				setMembranePotential(MembraneReset);
			} 
			else{
		/*	If the neuron isn't refractory nor is its membrane potential higher	
		 * 	than the threshold, then the potential can evolve.	*/
			setMembranePotential(MembranePotentialEquation(n*dt));
		}}
		
		
		
		
		setPresentTime(getPresentTime()+dt);
		/*	We write in the file the value of the current membrane potential.	*/
		file<<getMembranePotential()<<endl;
		/*	Variable counting the number of times the loop was executed.	*/
		++n;
	}
	setInputCurrent(0.0);
	
	file.close();
}
