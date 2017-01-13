/*
    GTEC -  A high performance standardized implementation of 
    Multi Constellation GNSS Derived TEC Calibration 
    (Model by T/ICT4D Lab ICTP).
    Copyright (C) 2016,2017  Muhammad Owais
    
    This file is part of GTEC.

    GTEC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2 of the License.

    GTEC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GTEC.  If not, see <http://www.gnu.org/licenses/>.
    
    Disclaimer: GTEC is a research implementation which is under 
    development and should not be considered fully functional unless 
    otherwise stated or a release is announced. Author is providing this 
    software on a best effort AS IS basis and do not warrant validity, 
    functionality, and suitability for any particular purpose. All copyright 
    notices must be kept intact. 

*/



#ifndef __IGRF__HPP
#define __IGRF__HPP

#include <string>
#include <vector>
#include <cmath>



const int ndim = 15;
const int mdim = 15;
const int tdim = 200;


std::vector<std::string> linesplit(std::string str);

int getGaussCoeffIGRF( std::string fname, float* gnm, float* hnm, float* svg, float* svh );


void getGaussCoeff(const float* gnm,
		   const float* hnm, 
		   const float* svg,
		   const float* svh, 
		   const int &t, 
		   const int &n, 
		   const int &m, 
		   float &gnmt, 
		   float &hnmt );



int checkInput(const float* gnm, const float* hnm, const float* svg, const float* svh);

void calculatePnm(float &theta, float* pnm );

float computeV(const float &r, float &theta, const float &phi, int &t, 
	float *gnm, 
	float *hnm, 
	float *svg, 
	float *svh,
	float *pnm );

float computeI(float &r, float &lat, float &lon, int &t,
	float *gnm, 
	float *hnm, 
	float *svg, 
	float *svh );


#endif



