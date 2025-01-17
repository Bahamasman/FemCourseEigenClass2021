//
//  ShapeQuad.cpp
//  FemSC
//
//  Created by Philippe Devloo on 03/04/18.
//

#include "Shape1d.h"
#include "ShapeQuad.h"

/// computes the shape functions in function of the coordinate in parameter space and orders of the shape functions (size of orders is number of sides of the element topology)
void ShapeQuad::Shape(const VecDouble &xi, VecInt &orders, VecDouble &phi, MatrixDouble &dphi){
    
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i] < 0) {
            std::cout << "ShapeQuad::Shape: Invalid dimension for arguments: order\n";
            DebugStop();
        }
    }
    if (orders[0] > 1 || orders[1] > 1 || orders[2] > 1 || orders[3] > 1) {
        std::cout << "ShapeQuad::Shape: Invalid dimension for arguments: order\n";
        DebugStop();
    }

    auto nf = NShapeFunctions(orders);

    if (orders[nf-1] > 2) {
        std::cout << "ShapeQuad::Shape, only implemented until order = 2" << std::endl;
        DebugStop();
    }

    //std::cout << "Please implement me\n";
    //DebugStop();

    double qsi = xi[0];
    double eta = xi[1];
    int nshape = NShapeFunctions(orders);

    phi[0] = (1.-qsi) * (1.-eta) * 0.25;
    phi[1] = (1.+qsi) * (1.-eta) * 1./4.;
    phi[2] = (1.+qsi) * (1.+eta) * 1./4.;
    phi[3] = (1.-qsi) * (1.+eta) * 1./4.;

    dphi(0, 0) = 1./4. * (-1. + eta);
    dphi(1, 0) = 1./4. * (-1. + qsi);

    dphi(0, 1) = 1./4. * (1. - eta);
    dphi(1, 1) = 1./4. * (-1. - qsi);

    dphi(0, 2) = 1./4. * (1. + eta);
    dphi(1, 2) = 1./4. * (1. + qsi);

    dphi(0, 3) = 1./4. * (-1. - eta);
    dphi(1, 3) = 1./4. * (1. - qsi);

    int count = 4;
    int is;
    for (is = 4; is < 8; is++) {
        if(orders[is] == 2)
        {
            int is1 = SideNodeLocIndex(is, 0);
            int is2 = SideNodeLocIndex(is, 1);
            phi[is] = 4. *phi[is1] * phi[is2];
            dphi(0, is) = 4. * (dphi(0, is1) * phi[is2] + phi[is1] * dphi(0, is2));
            dphi(1, is) = 4. * (dphi(1, is1) * phi[is2] + phi[is1] * dphi(1, is2));
            count++;
        } else if (orders[is] != 1) DebugStop();
    }
    if(count < nshape){
        if(orders[is] == 2)
        {
            int is1 = 0;
            int is2 = 2;
            phi[is] = 16. *phi[0] * phi[2];
            dphi(0, is) = 16. * (dphi(0, is1) * phi[is2] + phi[is1] * dphi(0, is2));
            dphi(1, is) = 16. * (dphi(1, is1) * phi[is2] + phi[is1] * dphi(1, is2));
            count ++;
        }

    }
    if(count != nshape) DebugStop();
    for(int is = 8 ; is< nSides; is++) if(orders[is] != 1 && orders[is] != 2) DebugStop();
}



/// returns the number of shape functions associated with a side
int ShapeQuad::NShapeFunctions(int side, int order){
    if(order < 1 || order >2) DebugStop();
    if(side<4)
        return 1;//0 a 4
    else if(side<8)
        return (order-1);//6 a 14
    else if(side==8)
        return ((order-1)*(order-1));
    
    std::cout << "ShapeQuad::NShapeFunctions, bad parameter side " << side << std::endl;
    DebugStop();
    
    return 0;
}

/// returns the total number of shape functions
int ShapeQuad::NShapeFunctions(VecInt &orders){
    
    int res=4;
    for(int in=4; in<orders.size(); in++) {
        res += NShapeFunctions(in, orders[in]);
    }
    
    return res;
}
