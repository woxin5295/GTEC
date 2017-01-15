/*
    GTEC -  A high performance standardized implementation of 
    Multi Constellation GNSS Derived TEC Calibration 
    (Model by T/ICT4D Lab ICTP).
    Copyright (C) 2016,2017 Muhammad Owais
    
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

#include "triple.hpp"
#include "igrf.hpp"
#include <cmath>


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "Usage " << argv[0] << " <igrf-file-name>\n";
        return 1;
    }
    
    
    //Reference point Trieste-Italy
    //Latitude 45° 38' N   Longitude 13° 46' E (in Deg,Min,Sec)
    //Latitude 45.633°       Longitude 13.767°   (in Decimal Degrees)
    //Year  2017
    //Elevation/Height      350000.0 meters
    
    //Calculated reference point Inclination from online model http://wdc.kugi.kyoto-u.ac.jp/igrf/point/index.html
    //Inclination = 61.557°
    //MODIP = atan(I / sqrt(cos(phi)))
    double online_I = 61.50306;
    double online_phi = 45.645;
    double online_height = 350000; //in meters
        
    
    double online_modip = atan( online_I / sqrt( cos( online_phi ) ) );
    
    //create position object
    triple pos(45.645, 13.77694, 350.0);
    
    //set time in unit of Years
    int t = 2017;
    
    //create IGRF object
    igrf igrf12(argv[1]);
    
    //compute modip from class method
    double modip = igrf12.getMODIP(pos,t);
    
    if(online_modip != modip)
    {
        std::cout << "***FAIL***\n";
        std::cout << "Actual MODIP: " << online_modip << std::endl;
        std::cout << "Computed MODIP: " << modip << std::endl;
        return 2;
    }
    else
    {
        std::cout << "***PASS***\n";
        return 0;
    }
    
}