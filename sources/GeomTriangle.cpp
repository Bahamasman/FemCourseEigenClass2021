/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GeomTriangle.h"

GeomTriangle::GeomTriangle() {
}

GeomTriangle::~GeomTriangle() {
}

GeomTriangle::GeomTriangle(const GeomTriangle &copy) {
    fNodeIndices = copy.fNodeIndices;

}

GeomTriangle& GeomTriangle::operator=(const GeomTriangle& copy) {
    fNodeIndices = copy.fNodeIndices;

    return *this;
}

void GeomTriangle::Shape(const VecDouble& xi, VecDouble& phi, MatrixDouble& dphi) {
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension || phi.size() != nCorners || dphi.rows() != Dimension || dphi.cols() != nCorners) DebugStop();
    double qsi = xi[0];
    double eta = xi[1];

    phi[0] = 1.0 - qsi - eta;
    phi[1] = qsi;
    phi[2] = eta;

    dphi(0, 0) = -1.0;
    dphi(1, 0) = -1.0;

    dphi(0, 1) = 1.0;
    dphi(1, 1) = 0.0;

    dphi(0, 2) = 0.0;
    dphi(1, 2) = 1.0;
    
    

   // DebugStop();
}

void GeomTriangle::X(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x) {
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension) DebugStop();
    if(x.size() < NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    

    VecDouble phi(nCorners);
    MatrixDouble dphi(Dimension, nCorners);
    
    
    Shape(xi, phi, dphi);
    int space = NodeCo.rows();

    for (int i = 0; i < space; i++) {
        x[i] = 0.0;
        for (int j = 0; j < nCorners; j++) {
            x[i] += phi[j] * NodeCo(i, j);
        }
    }
    //();
}

void GeomTriangle::GradX(const VecDouble &xi, MatrixDouble &NodeCo, VecDouble &x, MatrixDouble &gradx) {
    //std::cout << "\nPLEASE IMPLEMENT ME\n" << __PRETTY_FUNCTION__ << std::endl;
    if(xi.size() != Dimension) DebugStop();
    if(x.size() < NodeCo.rows()) DebugStop();
    if(NodeCo.cols() != nCorners) DebugStop();
    //DebugStop();

    gradx.resize(NodeCo.rows(), 2);
    gradx.setZero();
    x.resize(3);
    x.setZero();
    int nrow = NodeCo.rows();
    int ncol = NodeCo.cols();

    VecDouble phi(nCorners);
    MatrixDouble dphi(Dimension, nCorners);
    Shape(xi, phi, dphi);
    for (int i = 0; i < nCorners; i++) {
        for (int j = 0; j < nrow; j++) {
            x[j] += NodeCo(j,i) * phi[i];
            gradx(j, 0) += NodeCo(j, i) * dphi(0, i);
            gradx(j, 1) += NodeCo(j, i) * dphi(1, i);
        }
    }
    //std::cout << "gradx: "<< gradx << std::endl;
}

void GeomTriangle::SetNodes(const VecInt &nodes) {
    if(nodes.size() != nCorners) DebugStop();
    fNodeIndices = nodes;
}

void GeomTriangle::GetNodes(VecInt &nodes) const  {
    nodes = fNodeIndices;
}

int GeomTriangle::NodeIndex(int node) const {
    return fNodeIndices[node];
}

int GeomTriangle::NumNodes() {
    return nCorners;
}

GeoElementSide GeomTriangle::Neighbour(int side)  const {
    return fNeighbours[side];
}

void GeomTriangle::SetNeighbour(int side, const GeoElementSide &neighbour) {
    fNeighbours[side] = neighbour;
}
