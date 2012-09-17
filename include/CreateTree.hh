// Martin Goettlich @ DESY
//
#ifndef CREATETREE_H
#define CREATETREE_H

#include <iostream>
#include <vector>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include <G4ThreeVector.hh>
#include <Math/Cartesian3D.h>

using namespace std;

class CreateTree
{
private:

    TTree              *ftree;
    TString             fname;

    Bool_t              HITS;
    Bool_t              ABSORPTIONS;

    static const Int_t  MaxNum = 2000000;
    static const Int_t  MaxNumPro = 1000;

public:

    enum DataType {
        FirstElement, // Leave me first!!
        MomentumIn,
        MomentumOut,
        DeltaMomReflect,
        DeltaMomRefract,
        PolIn,
        DeltaPolReflect,
        DeltaPolRefract,
        MomRefl,
        PositionOut,
        LastElement // Leave me last!!
    };
    
    CreateTree(TString name, Bool_t hits, Bool_t absorptions);
    ~CreateTree();

    TTree              *GetTree() const {
        return ftree;
    };
    TString             GetName() const {
        return fname;
    };
    Int_t               Fill() {
        return this->GetTree()->Fill();
    };
    Bool_t              Write();
    void                Clear();
    static CreateTree  *Instance() {
        return fInstance;
    };
    static CreateTree  *fInstance;

    Bool_t              Hits() const {
        return this->HITS;
    };
    Bool_t              Absorptions() const {
        return this->ABSORPTIONS;
    };

    void pushData(CreateTree::DataType type, const G4ThreeVector &vector);

    Int_t               Run;
    Int_t               Event;
    Int_t               NumOptPhotons;
    Int_t               NumCerenkovPhotons;
    Int_t               NumScintPhotons;
    Int_t               NumOptPhotonsAbsorbed;
    Int_t               NumOptPhotonsRayleigh;
    Int_t               MPPCNumHits;
    Int_t               NumBoundaryAbsorption;
    Int_t               NumBoundaryReflection;
    Int_t               NumBoundaryFresnelRefraction;
    Int_t               NumBoundaryFresnelReflection;
    Int_t               NumBoundaryLobeReflection;
    Int_t               NumBoundarySpikeReflection;
    Int_t               NumBoundaryTotalInternalReflection;
    Int_t               NumBoundaryLambertianReflection;
    Int_t               NumBoundaryBackScattering;
    Int_t               NumOutOfTheCrystalBySide;
    Int_t               NumPhotonsThatQuitTheCrystal;
    Int_t               FresnelCS;

    Int_t               NumBoundaryStepTooSmall;
    Int_t               Process; // 1: Photo-Effect; 2: Compton-Effect

    Int_t               NumCherenkovPr;
    Int_t               NumeBrem;

    Float_t             zPhotCompt;
    Float_t             zeIoni;
    Float_t             zScint;

    Float_t             EProcessStart[MaxNumPro];
    Float_t             EProcessFinal[MaxNumPro];
    Int_t               NumProcess;
    Int_t               IDProcess[MaxNumPro];
    Float_t             DOIProcess[MaxNumPro];



    Float_t             BoundaryAbsorptionPosX[MaxNum];
    Float_t             BoundaryAbsorptionPosY[MaxNum];
    Float_t             BoundaryAbsorptionPosZ[MaxNum];
    Float_t             BoundaryAbsorptionTime[MaxNum];
    Float_t             BoundaryAbsorptionPhotonEnergy[MaxNum];

    Float_t             BoundaryReflectionPosX[MaxNum];
    Float_t             BoundaryReflectionPosY[MaxNum];
    Float_t             BoundaryReflectionPosZ[MaxNum];
    Float_t             BoundaryReflectionTime[MaxNum];
    Int_t               BoundaryReflectionType[MaxNum];

    Float_t             BulkAbsorptionPosX[MaxNum];
    Float_t             BulkAbsorptionPosY[MaxNum];
    Float_t             BulkAbsorptionPosZ[MaxNum];
    Float_t             BulkAbsorptionTime[MaxNum];
    Float_t             BulkAbsorptionPhotonEnergy[MaxNum];


    Float_t             OptPhotonEnergy[MaxNum];

    Float_t             ScintillationYield;
    Float_t             RiseTime;
    Float_t             CrystalHeight;
    Float_t             CrystalDiameter;
    Float_t             CrystalY;
    Float_t             CrystalX;
    Float_t             Reflectivity;
    Float_t             AbsLength;
    Float_t             Gap;
    Float_t             GapMaterial;
    Float_t             GapRefIndex;
    Float_t             Shape;
    Float_t             Readout;
    Float_t             DOI;
    Float_t             ScMaterial;

    Int_t               ReflBackside;

    Int_t               AirLayer;
    Float_t             AirGap;
    Float_t             AirLayerSigmaAlpha;

    Float_t             gammax;
    Float_t             gammay;
    Float_t             gammaz;

    Int_t               PartNum;
    Float_t             PartEn[MaxNum];
    Int_t               PartID[MaxNum];
    Int_t               PartProcess[MaxNum];
    Int_t               PartIDParent[MaxNum];
    Int_t               PartType[MaxNum];


    Int_t       OutSurface;

    map<CreateTree::DataType, vector<ROOT::Math::Cartesian3D<double> > > m_data;

    Int_t               TestI;
    Float_t             TestF;
};

/*
 00085 enum G4OpBoundaryProcessStatus {  Undefined,
 00086                                   FresnelRefraction, FresnelReflection,
 00087                                   TotalInternalReflection,
 00088                                   LambertianReflection, LobeReflection,
 00089                                   SpikeReflection, BackScattering,
 00090                                   Absorption, Detection, NotAtBoundary,
 00091                                   SameMaterial, StepTooSmall, NoRINDEX };
*/

#endif
