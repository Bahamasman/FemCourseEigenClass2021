//
//  TestOneDProblem.cpp MODIFICADO DO ORIGINAL
//  FemSC
//
//  Created by Eduardo Ferri on 08/17/15.
//
//
//TestOneDProblem cpp
/*
 Os testes foram preparados com um proposito educacional,
 recomenda-se que o aluno entenda a funcionalidade de cada
 teste e posteriormente use com seu cÛdigo caso a caso
 */
//      Obs: O xmax e xmin estao tomados como 4 e 0, respectivamente,
//      caso estes valores sejam alterados, editar o teste TestNodes.
//
//
#include <iostream>
#include <math.h>
#include "GeoMesh.h"
#include "ReadGmsh.h"
#include "CompMesh.h"
#include "Poisson.h"
#include "L2Projection.h"
#include "Analysis.h"
#include "PostProcessTemplate.h"
#include "VTKGeoMesh.h"

int main ()
{
    GeoMesh gmesh;
    ReadGmsh read;
    std::string filename("Example2DMesh.msh");
    //std::string filename("quads.msh");
#ifdef MACOSX
    filename = "../"+filename;
#endif
    read.Read(gmesh,filename);
    VTKGeoMesh::PrintGMeshVTK(&gmesh,"Example2DMesh.vtk");

    CompMesh cmesh(&gmesh);
    MatrixDouble perm(3,3);
    perm.setZero();
    perm(0,0) = 1.;
    perm(1,1) = 1.;
    perm(2,2) = 1.;
    Poisson *mat1 = new Poisson(1,perm);
    //Poisson *mat2 = new Poisson(1,perm);
    mat1->SetDimension(1);
    //mat2->SetDimension(2);

   auto exact = [](const VecDouble &x, VecDouble &val, MatrixDouble &deriv)
    {
        // val[0] = (1.-x[0])*x[0]*(1-x[1])*x[1];
        // deriv(0,0) = (1.-2.*x[0])*(1-x[1])*x[1];
        // deriv(1,0) = (1-2.*x[1])*(1-x[0])*x[0];

        val[0] = x[0]*x[0]*x[1]*x[1];
        deriv(0,0) = 2*x[0]*x[1]*x[1];
        deriv(1,0) = 2*x[1]*x[0]*x[0];
        
    }; 
    auto force = [](const VecDouble &x, VecDouble &res)
    {
        
        res[0] = -2*(x[0]*x[0]+x[1]*x[1]);

    };
    mat1->SetForceFunction(force);
    //mat2->SetForceFunction(force);
    MatrixDouble proj(1,1),val1(1,1),val2(1,1);
    proj.setZero();
    val1.setZero();
    val2.setZero();
   
    L2Projection *bc_left = new L2Projection(0,2,proj,val1,val2);
    L2Projection *bc_right = new L2Projection(0,3,proj,val1,val2);
    L2Projection *bc_bot = new L2Projection(0,4,proj,val1,val2);
    L2Projection *bc_top = new L2Projection(0,5,proj,val1,val2);
    bc_left->SetExactSolution(exact);
    bc_right->SetExactSolution(exact);
    bc_bot->SetExactSolution(exact);
    bc_top->SetExactSolution(exact);
   
    std::vector<MathStatement *> mathvec = {0, mat1,bc_left,bc_right,bc_bot,bc_top};
    cmesh.SetMathVec(mathvec);
    cmesh.SetDefaultOrder(2);
    cmesh.AutoBuild();
    cmesh.Resequence();
    //cmesh.Print();

        Analysis locAnalysis(&cmesh);
    locAnalysis.RunSimulation();
    PostProcessTemplate<Poisson> postprocess;

    //std::cout << "sol again = " << cmesh.Solution() << std::endl;

//    if (!strcmp("Sol", name.c_str())) return ESol;
//    if (!strcmp("DSol", name.c_str())) return EDSol;
//    if (!strcmp("Flux", name.c_str())) return EFlux;
//    if (!strcmp("Force", name.c_str())) return EForce;
//    if (!strcmp("SolExact", name.c_str())) return ESolExact;
//    if (!strcmp("DSolExact", name.c_str())) return EDSolExact;
    postprocess.AppendVariable("Sol");
    postprocess.AppendVariable("DSol");
    postprocess.AppendVariable("Flux");
    postprocess.AppendVariable("Force");
    postprocess.AppendVariable("SolExact");
    postprocess.AppendVariable("DSolExact");
    postprocess.SetExact(exact);
    mat1->SetExactSolution(exact);
    locAnalysis.PostProcessSolution("Example2DMesh.vtk", postprocess);

    VecDouble errvec;
    errvec = locAnalysis.PostProcessError(std::cout, postprocess);
    
    return 0;
}
