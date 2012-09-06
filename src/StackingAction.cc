#include "StackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

#include "CreateTree.hh"
using namespace std;

StackingAction::StackingAction() : gammaCounter (0)
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack (const G4Track* aTrack)
{

    // ------------ Retrieve tracks and particle history -------------- //

    // Non optical particles
    if (aTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
        Int_t idx = CreateTree::Instance()->PartNum;
        /*if(idx+1 == 100) {
            CreateTree::Instance()->PartNum = 0;
            idx = CreateTree::Instance()->PartNum;
        }*/
        CreateTree::Instance()->PartNum++;
        CreateTree::Instance()->PartEn[idx] = aTrack->GetKineticEnergy();
        CreateTree::Instance()->PartID[idx] = aTrack->GetTrackID();
        CreateTree::Instance()->PartProcess[idx] = -1; // unknown process
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "phot")  CreateTree::Instance()->PartProcess[idx] = 1; // phot
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "compt") CreateTree::Instance()->PartProcess[idx] = 2; // compt
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "eBrem") CreateTree::Instance()->PartProcess[idx] = 3; // brems
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "eIoni") CreateTree::Instance()->PartProcess[idx] = 4; // ioni
        if (!aTrack->GetCreatorProcess())  CreateTree::Instance()->PartProcess[idx] = 0; //
        CreateTree::Instance()->PartIDParent[idx] = aTrack->GetParentID();
        CreateTree::Instance()->PartType[idx] = -1;
        if (aTrack->GetDefinition()->GetParticleName() == "gamma") CreateTree::Instance()->PartType[idx] = 0; // gamma
        if (aTrack->GetDefinition()->GetParticleName() == "e-") CreateTree::Instance()->PartType[idx] = 1; // e-
        if (aTrack->GetDefinition()->GetParticleName() == "e+") CreateTree::Instance()->PartType[idx] = 2; // e+





    }


// ------------------------ MIA PARTE ------------------------- //
    /*
    if(aTrack->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
    {
        G4ThreeVector pos = aTrack->GetPosition();
        G4ThreeVector ver = aTrack->GetVertexPosition();
        CreateTree::Instance()->finalPosX[idx] = pos[0];
        CreateTree::Instance()->finalPosY[idx] = pos[1];
        CreateTree::Instance()->finalPosZ[idx] = pos[2];
        CreateTree::Instance()->firstPosX[idx] = ver[0];
        CreateTree::Instance()->firstPosY[idx] = ver[1];
        CreateTree::Instance()->firstPosZ[idx] = ver[2];
        /*ofstream myfile;
        myfile.open ("mioFile.txt", ios::app);
        myfile <<aTrack->GetTrackID()<<" "<<aTrack->GetDefinition()->GetParticleName()<<endl;
        myfile.close();

    }*/
// ------------------------ FINE ------------------------- //



    // Optical photons
    if (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
            //if (cerenkovCounter++==2000000) cerenkovCounter=0;
            cerenkovCounter++;
        }
        if (aTrack->GetCreatorProcess() && aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") {
            //if (scintCounter++==2000000) scintCounter=0;
            scintCounter++;

        }
        if (aTrack->GetParentID() > 0) {
            //if (gammaCounter++==2000000) gammaCounter=0;
            gammaCounter++;
            CreateTree::Instance()->OptPhotonEnergy[gammaCounter - 1] = aTrack->GetTotalEnergy();
        }



    }




    return fUrgent;

}


void StackingAction::NewStage()
{
    //G4cout<<"Number of optical photons produces in this event : "<<gammaCounter<<G4endl;
    CreateTree::Instance()->NumOptPhotons = gammaCounter;
    CreateTree::Instance()->NumCerenkovPhotons = cerenkovCounter;
    CreateTree::Instance()->NumScintPhotons = scintCounter;
}


void StackingAction::PrepareNewEvent()
{
    gammaCounter = 0;
    cerenkovCounter = 0;
    scintCounter = 0;
}

