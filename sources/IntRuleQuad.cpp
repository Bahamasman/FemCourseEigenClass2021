/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

///\cond
#include <iostream> 
///\endcond
#include "IntRule1d.h"
#include "IntRuleQuad.h"

IntRuleQuad::IntRuleQuad(){
}

IntRuleQuad::IntRuleQuad(int order) {
    SetOrder(order);
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    //DebugStop();
}

void IntRuleQuad::SetOrder(int order) {
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    fOrder = order;
    if (order < 0 || order > MaxOrder()) {
        DebugStop();
    }
    
    int npoints = floor(((fOrder +1)/2)+1);
    VecDouble aux(npoints);
    fPoints.resize(npoints * npoints, 2);
    fWeights.resize(npoints);
    gaulegQuad(-1.,1.,aux,fWeights);
    for (size_t i = 0; i < npoints*npoints; i++)
    {
        fPoints(i,0) = aux[i];
        fPoints(i,1) = aux[i+ npoints*npoints];
    }
//    std::cout << fOrder << std::endl<< std::endl;
//    std::cout << fPoints << std::endl<< std::endl;
//    std::cout << fWeights << std::endl<< std::endl;

}

void IntRuleQuad::gaulegQuad(const double x1, const double x2, VecDouble &co, VecDouble &w) {
    IntRule1d x;
    IntRule1d y;
    
    int n = w.size();   

    VecDouble cox(n);
    VecDouble coy(n);
    VecDouble wx(n);
    VecDouble wy(n);


    x.gauleg(x1, x2, cox, wx);
    y.gauleg(x1, x2, coy, wy);
    
    co.resize(2*n*n);
    w.resize(n * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            co[j + i * n] = cox[j];
            co[j + i * n + n * n] = coy[i];
            w[n * i + j] = wx[i] * wy[j];
        }
    }
}
