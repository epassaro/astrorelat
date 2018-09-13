#include <iostream>
#include <fstream>
#include <math.h>
#include "constants.h"

using namespace std;

const double ENERGY_MIN = 2.0*EE;                          // Energía mínima de las partículas relativistas
const double ENERGY_MAX = 1.0e+14*EV;                      // Energía máxima de las partículas relativistas 
const double STEP = 1.10;                                  // Paso de los bucles 
const double TEMP = 9.0e+04;                               // Temperatura de la estrella 
const double B_MAG = 20.0;                                 // Intensidad del campo magnético

                                                           // See: https://martin-ueding.de/articles/currying-in-c/index.html
double energy;                                             // Energía de los electrones relativistas 
double pho;                                                // Energía de los fotones gamma

double pho_index;                                          // Índice espectral
double e_0;                                                //
double knee;                                               // Energía de quiebre de la ley de potencias


double bkplaw(double energy, double e_0, double knee){       // Función distribución de energía

        if (energy < knee) {
                return e_0*pow(energy, -pho_index); 
        }

        else { 
                return e_0*pow(energy,-pho_index +1);
        } 
}

double qag(double a, double b, double (* func)(double, void *));

double ec(double energy){                                  // Energía crítica sincrotrón
        return (3.0/4.0)*E*H*B_MAG/(PI*ME*C)*(energy/EE*energy/EE);
}

double intSy(double energy, void *param){                  // Función a integrar
        return pow(pho/ec(energy),1.0/3.0)*exp(-pho/ec(energy))*bkplaw(energy, e_0, knee);
}


int main(){

        cout << endl << "BROKEN POWERLAW PARAMETERS" << endl << endl;
        cout << "Spectral index (e.g. 2.1):  ";
        cin >> pho_index;
        cout << "Knee region in ergs (e.g. 1.0e+07):  ";
        cin >> knee;
        cout << "Base energy in ergs (e.g. 4.7e+35):  ";
        cin >> e_0;
        cout << endl << "OK. Type 'make plot' to generate a graph." << endl << endl;

        ofstream outfile ("./sync.dat", ios::out);
        outfile << "#ENERGY[erg] LUM[erg s-1]" << endl << endl;

        double PHO_MAX = 20.0*ec(ENERGY_MAX);
        double PHO_MIN = 1.0e-8*EV;                         // El pico de la aproximación se da en 0.29*ec(ENERGY_MAX) 
        int N = log(PHO_MAX/PHO_MIN)/log(STEP);

        for(int i = 0; i < N+1; i++) {

                pho = PHO_MIN*pow(STEP, i);
                outfile  << pho
                         << " " 
                         << sqrt(3.0)*E*E*E*B_MAG/(H*EE)*1.85*qag(ENERGY_MIN, ENERGY_MAX, intSy)        // Luminosidad sincrotrón
                         << " " 
                         << endl;

        }

        outfile.close();

}
