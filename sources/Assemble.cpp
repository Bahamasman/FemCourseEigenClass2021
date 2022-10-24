/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Assemble.h"
#include "CompMesh.h"
#include "GeoMesh.h"
#include "MathStatement.h"
#include "CompElement.h"



Assemble::Assemble() {
}

Assemble::Assemble(CompMesh *mesh) {
    cmesh = mesh;
}

Assemble::Assemble(const Assemble &copy) {
    cmesh = copy.cmesh;
}

Assemble &Assemble::operator=(const Assemble &copy) {
    cmesh = copy.cmesh;
    return *this;
}

void Assemble::SetMesh(CompMesh *mesh) {
    cmesh = mesh;
}

int64_t Assemble::NEquations() {
    int64_t neq = 0;
    int64_t i, ncon = cmesh->GetDOFVec().size();
    for (i = 0; i < ncon; i++) {
        DOF dof = cmesh->GetDOF(i);
        int64_t dofsize = dof.GetNShape() * dof.GetNState();
        neq += dofsize;
    }
    return neq;
}

void Assemble::OptimizeBandwidth() {    
}

void Assemble::Compute(SparseMat &globmat, MatrixDouble &rhs) {
    
    auto neq = NEquations();
    
    globmat.resize(neq, neq);
    globmat.setZero();
    rhs.resize(neq, 1);
    rhs.setZero();
    
    int64_t nelem = cmesh->GetGeoMesh()->NumElements();
    for (int el = 0; el < nelem; el++) {
        CompElement *cel = cmesh->GetElement(el);

        int nshape = cel->NShapeFunctions();
        int nstate = cel->GetStatement()->NState();
        MatrixDouble ek(nstate * nshape, nstate * nshape);
        MatrixDouble ef(nstate * nshape, 1);
        ek.setZero();
        ef.setZero();
        
        cel->CalcStiff(ek, ef);
        
        
        int ndof = cel->NDOF();
        int k = cel->NShapeFunctions();
        
        int icount = 0;
        for (size_t idof = 0; idof < ndof; idof++)
        {
            DOF & dofi = cel->GetDOF(idof);
            int64_t ifirst = dofi.GetFirstEquation();
            int Neqi = dofi.GetNShape() * dofi.GetNState();
            for (size_t i = 0; i < Neqi; i++)
            {
                rhs(ifirst+i,0) += ef(icount+i,0);
            }
            int jcount = 0;
            for (size_t jdof = 0; jdof < ndof; jdof++)
            {
                DOF & dofj = cel->GetDOF(jdof);
                int64_t jfirst = dofj.GetFirstEquation();
                int Neqj = dofj.GetNShape() * dofj.GetNState();
                for (size_t i = 0; i < Neqi; i++)
                {
                    for (size_t j = 0; j < Neqj; j++)
                    {
                        globmat.coeffRef(ifirst+i,jfirst+j) += ek(icount+i,jcount+j);
                    }
                    
                }
                jcount += Neqj;
            }
            icount += Neqi;
            
        }
        
        
        //DebugStop();
        //+++++++++++++++++
    }
    std::cout << "Matriz Global :" << globmat << std::endl;
    std::cout << "RHS :" << rhs << std::endl;
}
