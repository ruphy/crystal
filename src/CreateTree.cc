#include "CreateTree.hh"
#include <vector>

#include <map>

CreateTree *CreateTree::fInstance = NULL;

using namespace std;

CreateTree::CreateTree(TString name, Bool_t hits, Bool_t absorptions)
{
    if(fInstance) {
        return;
    }

    this->HITS = hits;
    this->ABSORPTIONS = absorptions;

    this->fInstance = this;
    this->fname = name;
    this->ftree = new TTree("tree", "name");

    this->GetTree()->Branch("Run", &this->Run, "Run/I");
    this->GetTree()->Branch("Event", &this->Event, "Event/I");
    this->GetTree()->Branch("Process", &this->Process, "Process/I");
    this->GetTree()->Branch("NumOptPhotons", &this->NumOptPhotons, "NumOptPhotons/I");
    this->GetTree()->Branch("NumCerenkovPhotons", &this->NumCerenkovPhotons, "NumCerenkovPhotons/I");
    this->GetTree()->Branch("NumScintPhotons", &this->NumScintPhotons, "NumScintPhotons/I");
    this->GetTree()->Branch("NumOptPhotonsAbsorbed", &this->NumOptPhotonsAbsorbed, "NumOptPhotonsAbsorbed/I");
    this->GetTree()->Branch("NumOptPhotonsRayleigh", &this->NumOptPhotonsRayleigh, "NumOptPhotonsRayleigh/I");
    this->GetTree()->Branch("NumCherenkovPr", &this->NumCherenkovPr, "NumCherenkovPr/I");
    this->GetTree()->Branch("NumeBrem", &this->NumeBrem, "NumeBrem/I");


    this->GetTree()->Branch("NumBoundaryAbsorption", &this->NumBoundaryAbsorption, "NumBoundaryAbsorption/I");
    this->GetTree()->Branch("NumBoundaryReflection", &this->NumBoundaryReflection, "NumBoundaryReflection/I");
    if(this->ABSORPTIONS) {
        this->GetTree()->Branch("BoundaryAbsorptionPosX", &this->BoundaryAbsorptionPosX, "BoundaryAbsorptionPosX[NumBoundaryAbsorption]/F");
        this->GetTree()->Branch("BoundaryAbsorptionPosY", &this->BoundaryAbsorptionPosY, "BoundaryAbsorptionPosY[NumBoundaryAbsorption]/F");
        this->GetTree()->Branch("BoundaryAbsorptionPosZ", &this->BoundaryAbsorptionPosZ, "BoundaryAbsorptionPosZ[NumBoundaryAbsorption]/F");
        this->GetTree()->Branch("BoundaryAbsorptionTime", &this->BoundaryAbsorptionTime, "BoundaryAbsorptionTime[NumBoundaryAbsorption]/F");
        this->GetTree()->Branch("BoundaryAbsorptionPhotonEnergy", &this->BoundaryAbsorptionPhotonEnergy, "BoundaryAbsorptionPhotonEnergy[NumBoundaryAbsorption]/F");

        this->GetTree()->Branch("BoundaryReflectionPosX", &this->BoundaryReflectionPosX, "BoundaryPosX[NumBoundaryReflection]/F");
        this->GetTree()->Branch("BoundaryReflectionPosY", &this->BoundaryReflectionPosY, "BoundaryPosY[NumBoundaryReflection]/F");
        this->GetTree()->Branch("BoundaryReflectionPosZ", &this->BoundaryReflectionPosZ, "BoundaryPosZ[NumBoundaryReflection]/F");
        this->GetTree()->Branch("BoundaryReflectionTime", &this->BoundaryReflectionTime, "BoundaryTime[NumBoundaryReflection]/F");
        this->GetTree()->Branch("BoundaryReflectionType", &this->BoundaryReflectionType, "BoundaryReflectionType[NumBoundaryReflection]/I");

        this->GetTree()->Branch("BulkAbsorptionPosX", &this->BulkAbsorptionPosX, "BulkAbsorptionPosX[NumOptPhotonsAbsorbed]/F");
        this->GetTree()->Branch("BulkAbsorptionPosY", &this->BulkAbsorptionPosY, "BulkAbsorptionPosY[NumOptPhotonsAbsorbed]/F");
        this->GetTree()->Branch("BulkAbsorptionPosZ", &this->BulkAbsorptionPosZ, "BulkAbsorptionPosZ[NumOptPhotonsAbsorbed]/F");
        this->GetTree()->Branch("BulkAbsorptionTime", &this->BulkAbsorptionTime, "BulkAbsorptionTime[NumOptPhotonsAbsorbed]/F");
        this->GetTree()->Branch("BulkAbsorptionPhotonEnergy", &this->BulkAbsorptionPhotonEnergy, "BulkAbsorptionPhotonEnergy[NumOptPhotonsAbsorbed]/F");
    }

    this->GetTree()->Branch("OptPhotonEnergy", &this->OptPhotonEnergy, "OptPhotonEnergy[NumOptPhotons]/F");
    this->GetTree()->Branch("NumBoundaryFresnelRefraction", &this->NumBoundaryFresnelRefraction, "NumBoundaryFresnelRefraction/I");
    this->GetTree()->Branch("NumBoundaryStepTooSmall", &this->NumBoundaryStepTooSmall, "NumBoundaryStepTooSmall/I");
    this->GetTree()->Branch("NumBoundaryFresnelReflection", &this->NumBoundaryFresnelReflection, "NumBoundaryFresnelReflection/I");
    this->GetTree()->Branch("NumBoundaryLobeReflection", &this->NumBoundaryLobeReflection, "NumBoundaryLobeReflection/I");
    this->GetTree()->Branch("NumBoundarySpikeReflection", &this->NumBoundarySpikeReflection, "NumBoundarySpikeReflection/I");
    this->GetTree()->Branch("NumBoundaryTotalInternalReflection", &this->NumBoundaryTotalInternalReflection, "NumBoundaryTotalInternalReflection/I");
    this->GetTree()->Branch("NumBoundaryLambertianReflection", &this->NumBoundaryLambertianReflection, "NumBoundaryLambertianReflection/I");
    this->GetTree()->Branch("NumBoundaryBackScattering", &this->NumBoundaryBackScattering, "NumBoundaryBackScattering/I");
    this->GetTree()->Branch("NumOutOfTheCrystalBySide", &this->NumOutOfTheCrystalBySide, "NumOutOfTheCrystalBySide/I");
    this->GetTree()->Branch("PhotonHasQuitTheCrystal", &this->PhotonHasQuitTheCrystal, "PhotonHasQuitTheCrystal/I");

    this->GetTree()->Branch("FresnelCS", &this->FresnelCS, "FresnelCS/I");

    this->GetTree()->Branch("ScintillationYield", &this->ScintillationYield, "ScintillationYield/F");
    this->GetTree()->Branch("RiseTime", &this->RiseTime, "RiseTime/F");
    this->GetTree()->Branch("Reflectivity", &this->Reflectivity, "Reflectivity/F");
    this->GetTree()->Branch("CrystalHeight", &this->CrystalHeight, "CrystalHeight/F");
    this->GetTree()->Branch("CrystalDiameter", &this->CrystalDiameter, "CrystalDiameter/F");
    this->GetTree()->Branch("CrystalX", &this->CrystalX, "CrystalX/F");
    this->GetTree()->Branch("CrystalY", &this->CrystalY, "CrystalY/F");
    this->GetTree()->Branch("Gap", &this->Gap, "Gap/F");
    this->GetTree()->Branch("GapMaterial", &this->GapMaterial, "GapMaterial/F");
    this->GetTree()->Branch("GapRefIndex", &this->GapRefIndex, "GapRefIndex/F");
    this->GetTree()->Branch("AbsLength", &this->AbsLength, "AbsLength/F");

    this->GetTree()->Branch("Shape", &this->Shape, "Shape/F");
    this->GetTree()->Branch("Readout", &this->Readout, "Readout/F");

    this->GetTree()->Branch("ScMaterial", &this->ScMaterial, "ScMaterial/F");

    this->GetTree()->Branch("DOI", &this->DOI, "DOI/F");
    this->GetTree()->Branch("zPhotCompt", &this->zPhotCompt, "zPhotCompt/F");
    this->GetTree()->Branch("zeIoni", &this->zeIoni, "zeIoni/F");
    this->GetTree()->Branch("zScint", &this->zScint, "zScint/F");

    this->GetTree()->Branch("ReflBackside", &this->ReflBackside, "ReflBackside/I");

    this->GetTree()->Branch("NumProcess", &this->NumProcess, "NumProcess/I");
    this->GetTree()->Branch("EProcessStart", &this->EProcessStart, "EProcessStart[NumProcess]/F");
    this->GetTree()->Branch("EProcessFinal", &this->EProcessFinal, "EProcessFinal[NumProcess]/F");
    this->GetTree()->Branch("IDProcess", &this->IDProcess, "IDProcess[NumProcess]/I");
    this->GetTree()->Branch("DOIProcess", &this->DOIProcess, "DOIProcess[NumProcess]/F");

    this->GetTree()->Branch("AirLayer", &this->AirLayer, "AirLayer/I");
    this->GetTree()->Branch("AirGap", &this->AirGap, "AirGap/F");
    this->GetTree()->Branch("AirLayerSigmaAlpha", &this->AirLayerSigmaAlpha, "AirLayerSigmaAlpha/F");

    this->GetTree()->Branch("gammax", &this->gammax, "gammax/F");
    this->GetTree()->Branch("gammay", &this->gammay, "gammay/F");
    this->GetTree()->Branch("gammaz", &this->gammaz, "gammaz/F");

    // electrons/gammas
    this->GetTree()->Branch("PartNum", &this->PartNum, "PartNum/I");
    this->GetTree()->Branch("PartID", &this->PartID, "PartID[PartNum]/I");
    this->GetTree()->Branch("PartProcess", &this->PartProcess, "PartProcess[PartNum]/I");
    this->GetTree()->Branch("PartIDParent", &this->PartIDParent, "PartIDParent[PartNum]/I");
    this->GetTree()->Branch("PartEn", &this->PartEn, "PartEn[PartNum]/F");
    this->GetTree()->Branch("PartType", &this->PartType, "PartType[PartNum]/I");

    this->GetTree()->Branch("TestI", &this->TestI, "TestI/I");
    this->GetTree()->Branch("TestF", &this->TestF, "TestF/F");

    /*--------------------MY STUFF-----------------*/

    this->GetTree()->Branch("OutSurface", &this->OutSurface, "OutSurface/I");

    this->GetTree()->Branch("MomentumIn", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::MomentumIn]));
    this->GetTree()->Branch("MomentumOut", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::MomentumOut]));
    this->GetTree()->Branch("DeltaMomReflect", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::DeltaMomReflect]));
    this->GetTree()->Branch("DeltaMomRefract", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::DeltaMomRefract]));
    this->GetTree()->Branch("PolIn", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::PolIn]));
    this->GetTree()->Branch("DeltaPolReflect", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::DeltaPolReflect]));
    this->GetTree()->Branch("DeltaPolRefract", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::DeltaPolRefract]));
    this->GetTree()->Branch("MomRefl", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::MomRefl]));
    this->GetTree()->Branch("PositionOut", "vector<ROOT::Math::Cartesian3D<double> >", &(m_data[CreateTree::PositionOut]));

    this->Clear();
}

CreateTree::~CreateTree()
{

}

void CreateTree::pushData(CreateTree::DataType type, const G4ThreeVector &vector)
{
    ROOT::Math::Cartesian3D<double> vec;
    vec.SetX(vector.x());
    vec.SetY(vector.y());
    vec.SetZ(vector.z());
    m_data[type].push_back(vec);
}

Bool_t CreateTree::Write()
{
    TString filename = this->GetName();
    filename += ".root";
    TFile *file = new TFile(filename, "RECREATE");
    this->GetTree()->Write();
    file->Write();
    file->Close();
    return true;
}

void CreateTree::Clear()
{

    Run = 0;
    Event = 0;
    Process = 0;
    NumOptPhotons = 0;
    NumCerenkovPhotons = 0;
    NumScintPhotons = 0;
    NumOptPhotonsAbsorbed = 0;
    NumOptPhotonsRayleigh = 0;
    PhotonHasQuitTheCrystal = 0;
    MPPCNumHits = 0;
    NumCherenkovPr = 0;
    NumeBrem = 0;

    zPhotCompt = -999;
    zeIoni = -999;
    zScint = -999;

    DOI = -1;
    TestI = 0;
    TestF = 0;

    NumBoundaryAbsorption = 0;
    NumBoundaryReflection = 0;
    NumBoundaryStepTooSmall = 0;
    NumBoundaryFresnelRefraction = 0;
    
    FresnelCS = 0;
    
    NumBoundaryFresnelReflection = 0;
    NumBoundaryLobeReflection = 0;
    NumBoundarySpikeReflection = 0;
    NumBoundaryTotalInternalReflection = 0;
    NumBoundaryLambertianReflection = 0;
    NumBoundaryBackScattering = 0;
    NumOutOfTheCrystalBySide = 0;

    NumProcess = 0;
    PartNum = 0;

    OutSurface = 0;

    map<CreateTree::DataType, vector<ROOT::Math::Cartesian3D<double> > >::iterator iter;

    for (iter = m_data.begin(); iter != m_data.end(); ++iter) {
        iter->second.clear();
    }
}
