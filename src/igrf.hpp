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
#include "triple.hpp"


/**
 * @class igrf
 * @author Muhammad Owais
 * @date 14/01/17
 * @file igrf.hpp
 * @brief This class implements IGRF model.
 * 
 * This class implements IGRF (International Geomagnetic Reference Field) model, 
 * as defined in <a href="https://www.ngdc.noaa.gov/IAGA/vmod/igrf.html">IGRF Web Site</a>.
 * An instance of this class could be created using a generation of IGRF coefficients, 
 * currently <a href="http://earth-planets-space.springeropen.com/articles/10.1186/s40623-015-0228-9">IGRF-12</a>
 * which would be valid for years 1900 to 2020. 
 */

class igrf
{
    
public:

    //!Constructor with Input file
    /*!Constructs igrf object by reading input computed IGRF Model file, given Model year as @ref igrf_Year.
        * \param igrf_Year IGRF Model year. 
        */
    igrf(int igrf_Year);
    
    
    //!Function to compute MODIP.
    /*!This function compute MODIP (Modified Dip) given ellipsoidal coordinates of 
     * the point.
        * \param pos ellipsoidal coordinates of the point as @ref triple object.
        * \return Returns computed MODIP.
        */    
    double getMODIP(const triple& pos);
                    
                    
    void computeField(double& r,
                      double& lat,
                      double& lon,
                      int& t,
                      double& H,
                      double& F,
                      double& D,
                      double& I);

                    
    ~igrf();


    
private:
  
  
    //!Inclation on lat/long grid for IPP at height 350 KMs.
    double* ippI;
    
    //!Inclation on lat/long grid for station at height 0 KMs surface.
    double* stationI;    
    
    const int pnmDim = 81;
    
    //!Number of time columns in igrf-12 coefficients file
    const int numTimeCols = 25;
    
    //!Column size in igrf-12 coefficients file
    const int colSize = 208;
    
    //!Total size of array to store all values present in igrf-12 coefficients file
    int arraySize;
    
    //!Array pointer
    double* igrfCoeffs;
    
    //!Array pointer
    double* pnm;
    
    //!start offsets for blocks of n
    int nBlockStart[13] = {0,4,10,18,28,40,54,70,88,108,130,154,180};


    igrf();
    
    std::vector<std::string> linesplit(std::string str);
    
    int checkInput();
    
    void computePnm(double& theta);

    double computeV(double& r,
                  double& theta,
                  double& phi,
                  int &t);
    
    
    inline int getOffSetG(int n, int m, int t);
    inline int getOffSetH(int n, int m, int t);
    
};


int igrf::getOffSetG(int n, int m, int t)
{
  return ((t-1900)/5)*colSize + nBlockStart[n-1] + 2*m;
}

int igrf::getOffSetH(int n, int m, int t)
{
  return ((t-1900)/5)*colSize + nBlockStart[n-1] + 2*m+1;
}



#endif



