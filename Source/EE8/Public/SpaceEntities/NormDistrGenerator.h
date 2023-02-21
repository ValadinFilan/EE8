// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * 
 */
class EE8_API NormDistrGenerator
{
public:
	double RandNormFromUniform(double U1, double U2, double mu, double sigma);
	NormDistrGenerator();
	~NormDistrGenerator();
};
