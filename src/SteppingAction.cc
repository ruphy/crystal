#include "SteppingAction.hh"

#include "G4SteppingManager.hh"
#include "G4SDManager.hh"
#include "G4EventManager.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>
#include "CreateTree.hh"
using namespace std;

SteppingAction::SteppingAction()
{
    m_showPhotons = true;
}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step *theStep)
{

    G4StepPoint *thePrePoint = theStep->GetPreStepPoint();
    G4VPhysicalVolume *thePrePV = thePrePoint->GetPhysicalVolume();
    G4StepPoint *thePostPoint = theStep->GetPostStepPoint();
    G4VPhysicalVolume *thePostPV = thePostPoint->GetPhysicalVolume();

    G4OpBoundaryProcessStatus boundaryStatus = Undefined;
    static G4OpBoundaryProcess *boundary = NULL;

    G4Track *theTrack = theStep->GetTrack();
    G4ParticleDefinition *particleType = theTrack->GetDefinition();


    CreateTree *tree = CreateTree::Instance();

    // ------------------------ STORING PARTICLE AND PROCESSES ------------------------- //

    // Storing time, energy and position of optical photons absorbed
    if(particleType == G4OpticalPhoton::OpticalPhotonDefinition()) {
        if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption") {
            if(tree->Absorptions()) {
                tree->BulkAbsorptionTime[tree->NumOptPhotonsAbsorbed] = theTrack->GetGlobalTime();
                tree->BulkAbsorptionPhotonEnergy[tree->NumOptPhotonsAbsorbed] = theTrack->GetTotalEnergy();
                tree->AbsLength = theStep->GetTrack()->GetTrackLength();
                tree->BulkAbsorptionPosX[tree->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().x();
                tree->BulkAbsorptionPosY[tree->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().y();
                tree->BulkAbsorptionPosZ[tree->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().z();
            }
            tree->NumOptPhotonsAbsorbed++;
        }
    }

    // Printing out the processes step by step
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() != "Transportation"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "OpAbsorption"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "phot"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "compt"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "eIoni"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "Scintillation"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "Cerenkov"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "OpRayleigh"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "eBrem"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "UserMaxStep" // !!!!!!!!!!!!!!!!!
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "msc"
            && thePostPoint->GetProcessDefinedStep()->GetProcessName() != "Rayl") {
        G4cout << thePostPoint->GetProcessDefinedStep()->GetProcessName() << G4endl;
    }

    // Storing photoelectric and low energy processes (DOI, energy)
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "phot"
            || thePostPoint->GetProcessDefinedStep()->GetProcessName() == "LowEnPhotoElec") {
        tree->Process = 1;
        Float_t d = 0.5 * tree->CrystalHeight - thePostPoint->GetPosition().z();
        tree->DOI = d;
        //tree->zPhotCompt = thePostPoint->GetPosition().z();

        tree->EProcessStart[tree->NumProcess] = thePrePoint->GetTotalEnergy();
        tree->EProcessFinal[tree->NumProcess] = thePostPoint->GetTotalEnergy();
        tree->IDProcess[tree->NumProcess] = 1;
        tree->DOIProcess[tree->NumProcess] = d;
        tree->NumProcess++;
    }

    // Storing Compton processes (DOI, energy)
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "compt"
            ||  thePostPoint->GetProcessDefinedStep()->GetProcessName() == "LowEnCompton") {
        tree->Process = 2;
        Float_t d = 0.5 * tree->CrystalHeight - thePostPoint->GetPosition().z();
        tree->DOI = d;
        //tree->zPhotCompt = thePostPoint->GetPosition().z();

        tree->EProcessStart[tree->NumProcess] = thePrePoint->GetTotalEnergy();
        tree->EProcessFinal[tree->NumProcess] = thePostPoint->GetTotalEnergy();
        tree->DOIProcess[tree->NumProcess] = d;
        tree->IDProcess[tree->NumProcess] = 2;
        tree->NumProcess++;
    }



    // Storing Rayleigh processes
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpRayleigh") {
        tree->NumOptPhotonsRayleigh++;
    }

    // Storing Cerenkov processes
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "Cerenkov") {
        tree->NumCherenkovPr++;
    }

    // Storing Brem processes
    if(thePostPoint->GetProcessDefinedStep()->GetProcessName() == "eBrem") {
        tree->NumeBrem++;
    }

    /*if (thePrePV->GetName()!="World"){
    G4ThreeVector in  = thePrePoint->GetMomentumDirection();
            G4ThreeVector out = thePostPoint->GetMomentumDirection();
    cout<<"Tutti: "<<thePrePV->GetName()<<" "<<thePostPV->GetName()<<endl;
    cout<<"Tutti: "<<in[2]<<" "<<out[2]<<endl;
    }*/
// ------------------------ MIA PARTE ------------------------- //
    if(thePrePV->GetName() == "Crystal" &&  thePostPV->GetName() == "Sensor") {

        tree->pushData(CreateTree::PolIn, thePrePoint->GetPolarization());
        tree->pushData(CreateTree::MomentumIn, thePrePoint->GetMomentumDirection());

    }

    if(thePrePV->GetName() == "Sensor" &&  thePostPV->GetName() == "Crystal") {
//if (thePrePV->GetName()=="TopAir" &&  thePostPV!=NULL){

        Int_t counter = tree->OutSurface;
        tree->OutSurface++;


        G4ThreeVector deltaPolReflect = thePrePoint->GetPolarization() - thePostPoint->GetPolarization();
        G4ThreeVector deltaMomentumReflect = thePrePoint->GetMomentumDirection() - thePostPoint->GetMomentumDirection();
 
        tree->pushData(CreateTree::DeltaMomReflect, deltaMomentumReflect);
        tree->pushData(CreateTree::DeltaPolReflect, deltaPolReflect);
        tree->pushData(CreateTree::MomRefl, thePostPoint->GetMomentumDirection());

        if(!m_showPhotons) {
            theStep->GetTrack()->SetTrackStatus(fStopAndKill);
        }
    }

    if((thePrePV->GetName() == "Crystal") &&  ((thePostPV->GetName() == "Sensor") or (thePostPV->GetName() == "World")) ) {
        tree->PhotonHasQuitTheCrystal++;
    }

    if(thePrePV->GetName() == "Sensor" &&  thePostPV->GetName() == "World") {

        G4ThreeVector deltaMomRefr = thePrePoint->GetMomentumDirection() - thePostPoint->GetMomentumDirection();
        G4ThreeVector deltaPolRefr = thePrePoint->GetPolarization() - thePostPoint->GetPolarization();

        tree->pushData(CreateTree::DeltaMomRefract, deltaMomRefr);
        tree->pushData(CreateTree::DeltaPolRefract, deltaPolRefr);
        tree->pushData(CreateTree::MomentumOut, thePostPoint->GetMomentumDirection());
        tree->pushData(CreateTree::PositionOut, thePostPoint->GetPosition());
    }

// ------------------------ FINE ------------------------- //

    // ------------------------ STORING OPTICAL PROCESSES ------------------------- //

    //find the boundary process only once
    if(!boundary) {
        G4ProcessManager *pm = theStep->GetTrack()->GetDefinition()->GetProcessManager();
        G4int nprocesses = pm->GetProcessListLength();
        G4ProcessVector *pv = pm->GetProcessList();
        G4int i;
        for(i = 0; i < nprocesses; i++) {
            if((*pv) [i]->GetProcessName() == "OpBoundary") {
                boundary = (G4OpBoundaryProcess *)(*pv) [i];
                break;
            }
        }
    }

    if(!boundary) return;

    boundaryStatus = boundary->GetStatus();

    //Check to see if the particle was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check

    if(thePostPoint->GetStepStatus() == fGeomBoundary) {
        bool ISREFL = false;
        switch(boundaryStatus) {
        case Absorption: {
            if(CreateTree::Instance()->Absorptions()) {

                CreateTree::Instance()->BoundaryAbsorptionTime[CreateTree::Instance()->NumBoundaryAbsorption] = theStep->GetTrack()->GetGlobalTime();
                CreateTree::Instance()->BoundaryAbsorptionPhotonEnergy[CreateTree::Instance()->NumBoundaryAbsorption] = theStep->GetTrack()->GetTotalEnergy();
                CreateTree::Instance()->BoundaryAbsorptionPosX[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().x();
                CreateTree::Instance()->BoundaryAbsorptionPosY[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().y();
                CreateTree::Instance()->BoundaryAbsorptionPosZ[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().z();
            }

            tree->PhotonHasQuitTheCrystal = 0;
            CreateTree::Instance()->NumBoundaryAbsorption++;
            break;
        }
        case Detection:
            // Note, this assumes that the volume causing detection
            //is the surface of the MPPC because it is the only one with
            //non-zero efficiency
            // SOMETHING TO IMPLEMENT!!!!
            break;

        case StepTooSmall:
            CreateTree::Instance()->NumBoundaryStepTooSmall++;
            break;

        case LambertianReflection:
            CreateTree::Instance()->NumBoundaryLambertianReflection++;
            ISREFL = true;
            break;

        case FresnelReflection:
            CreateTree::Instance()->NumBoundaryFresnelReflection++;
            tree->PhotonHasQuitTheCrystal = 0;
            ISREFL = true;
            break;

        case TotalInternalReflection:
            CreateTree::Instance()->NumBoundaryTotalInternalReflection++;
            ISREFL = true;
            break;

        case SpikeReflection:
            CreateTree::Instance()->NumBoundarySpikeReflection++;
            ISREFL = true;
            break;

        case LobeReflection:
            CreateTree::Instance()->NumBoundaryLobeReflection++;
            ISREFL = true;
            break;

        case FresnelRefraction:
            if(thePrePV->GetName() == "Crystal" &&  thePostPV->GetName() == "Sensor") {
                CreateTree::Instance()->FresnelCS++;
            }
            if(thePrePV->GetName() == "Crystal" &&  thePostPV->GetName() == "World") {
                CreateTree::Instance()->NumOutOfTheCrystalBySide++;
            }

            CreateTree::Instance()->NumBoundaryFresnelRefraction++;
            ISREFL = false;
            break;

        case BackScattering:
            CreateTree::Instance()->NumBoundaryBackScattering++;
            ISREFL = true;
            break;

        default:
            ISREFL = false;
            break;
        } // end switch

        if(ISREFL) {
            if(CreateTree::Instance()->Absorptions()) {
                CreateTree::Instance()->BoundaryReflectionTime[CreateTree::Instance()->NumBoundaryReflection] = theStep->GetTrack()->GetGlobalTime();
                CreateTree::Instance()->BoundaryReflectionPosX[CreateTree::Instance()->NumBoundaryReflection] = thePostPoint->GetPosition().x();
                CreateTree::Instance()->BoundaryReflectionPosY[CreateTree::Instance()->NumBoundaryReflection] = thePostPoint->GetPosition().y();
                CreateTree::Instance()->BoundaryReflectionPosZ[CreateTree::Instance()->NumBoundaryReflection] = thePostPoint->GetPosition().z();
                CreateTree::Instance()->BoundaryReflectionType[CreateTree::Instance()->NumBoundaryReflection] = (Int_t) boundaryStatus;
            }
            CreateTree::Instance()->NumBoundaryReflection++;
        }
    }// at boundary

}

void SteppingAction::setShowPhotons(bool showPhotons)
{
    m_showPhotons = showPhotons;
}

