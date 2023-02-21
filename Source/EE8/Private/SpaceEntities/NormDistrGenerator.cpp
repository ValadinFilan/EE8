// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEntities/NormDistrGenerator.h"
#include "..\..\Public\SpaceEntities\NormDistrGenerator.h"

double NormDistrGenerator::RandNormFromUniform(double U1, double U2, double mu, double sigma)
{
	/// <summary>
	/// generate randomly distributed value from two uniformly-distributed values in range [0, 1]
	/// </summary>
	/// <param name="U1">num1[0, 1]</param>
	/// <param name="U2">num2[0, 1]</param>
	/// <param name="mu">expectation</param>
	/// <param name="sigma">standard deviation</param>
	/// <returns></returns>
	/// 
	//constexpr double epsilon = std::numeric_limits<double>::epsilon();
	double result = sqrt(-2 * log(U1)) * cos(2 * M_PI * U2);
	result = result * sigma + mu;
	return result;
}

NormDistrGenerator::NormDistrGenerator()
{
}

NormDistrGenerator::~NormDistrGenerator()
{
}
