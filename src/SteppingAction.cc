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
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction (const G4Step* theStep)
{

    G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
    G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();
    G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
    G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

    G4OpBoundaryProcessStatus boundaryStatus = Undefined;
    static G4OpBoundaryProcess* boundary = NULL;

    G4Track* theTrack = theStep->GetTrack();
    G4ParticleDefinition* particleType = theTrack->GetDefinition();



    // ------------------------ STORING PARTICLE AND PROCESSES ------------------------- //

    // Storing time, energy and position of optical photons absorbed
    if (particleType == G4OpticalPhoton::OpticalPhotonDefinition()) {
        if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption") {
            if (CreateTree::Instance()->Absorptions()) {
                CreateTree::Instance()->BulkAbsorptionTime[CreateTree::Instance()->NumOptPhotonsAbsorbed] = theStep->GetTrack()->GetGlobalTime();
                CreateTree::Instance()->BulkAbsorptionPhotonEnergy[CreateTree::Instance()->NumOptPhotonsAbsorbed] = theStep->GetTrack()->GetTotalEnergy();
                CreateTree::Instance()->BulkAbsorptionPosX[CreateTree::Instance()->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().x();
                CreateTree::Instance()->BulkAbsorptionPosY[CreateTree::Instance()->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().y();
                CreateTree::Instance()->BulkAbsorptionPosZ[CreateTree::Instance()->NumOptPhotonsAbsorbed] = thePostPoint->GetPosition().z();
            }
            CreateTree::Instance()->NumOptPhotonsAbsorbed++;
        }
    }

    // Printing out the processes step by step
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() != "Transportation"
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
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "phot"
            || thePostPoint->GetProcessDefinedStep()->GetProcessName() == "LowEnPhotoElec") {
        CreateTree::Instance() -> Process = 1;
        Float_t d = 0.5 * CreateTree::Instance()->CrystalHeight - thePostPoint->GetPosition().z();
        CreateTree::Instance() -> DOI = d;
        //CreateTree::Instance()->zPhotCompt = thePostPoint->GetPosition().z();

        CreateTree::Instance() -> EProcessStart[CreateTree::Instance()->NumProcess] = thePrePoint->GetTotalEnergy();
        CreateTree::Instance() -> EProcessFinal[CreateTree::Instance()->NumProcess] = thePostPoint->GetTotalEnergy();
        CreateTree::Instance() -> IDProcess[CreateTree::Instance()->NumProcess] = 1;
        CreateTree::Instance() -> DOIProcess[CreateTree::Instance()->NumProcess] = d;
        CreateTree::Instance() -> NumProcess++;
    }

    // Storing Compton processes (DOI, energy)
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "compt"
            ||  thePostPoint->GetProcessDefinedStep()->GetProcessName() == "LowEnCompton") {
        CreateTree::Instance() -> Process = 2;
        Float_t d = 0.5 * CreateTree::Instance()->CrystalHeight - thePostPoint->GetPosition().z();
        CreateTree::Instance() -> DOI = d;
        //CreateTree::Instance()->zPhotCompt = thePostPoint->GetPosition().z();

        CreateTree::Instance()->EProcessStart[CreateTree::Instance()->NumProcess] = thePrePoint->GetTotalEnergy();
        CreateTree::Instance()->EProcessFinal[CreateTree::Instance()->NumProcess] = thePostPoint->GetTotalEnergy();
        CreateTree::Instance()->DOIProcess[CreateTree::Instance()->NumProcess] = d;
        CreateTree::Instance()->IDProcess[CreateTree::Instance()->NumProcess] = 2;
        CreateTree::Instance()->NumProcess++;
    }



    // Storing Rayleigh processes
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpRayleigh") {
        CreateTree::Instance()->NumOptPhotonsRayleigh++;
    }

    // Storing Cerenkov processes
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "Cerenkov") {
        CreateTree::Instance()->NumCherenkovPr++;
    }

    // Storing Brem processes
    if (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "eBrem") {
        CreateTree::Instance()->NumeBrem++;
    }

    /*if (thePrePV->GetName()!="World"){
    G4ThreeVector in  = thePrePoint->GetMomentumDirection();
            G4ThreeVector out = thePostPoint->GetMomentumDirection();
    cout<<"Tutti: "<<thePrePV->GetName()<<" "<<thePostPV->GetName()<<endl;
    cout<<"Tutti: "<<in[2]<<" "<<out[2]<<endl;
    }*/
// ------------------------ MIA PARTE ------------------------- //
    if (thePrePV->GetName() == "Crystal" &&  thePostPV->GetName() == "TopAir") {

        CreateTree::Instance()->PolInX.push_back (thePrePoint->GetPolarization().x());
        CreateTree::Instance()->PolInY.push_back (thePrePoint->GetPolarization().y());
        CreateTree::Instance()->PolInZ.push_back (thePrePoint->GetPolarization().z());
        CreateTree::Instance()->MomentumInX.push_back (thePrePoint->GetMomentumDirection().x());
        CreateTree::Instance()->MomentumInY.push_back (thePrePoint->GetMomentumDirection().y());
        CreateTree::Instance()->MomentumInZ.push_back (thePrePoint->GetMomentumDirection().z());


    }
    if (thePrePV->GetName() == "TopAir" &&  thePostPV->GetName() == "Crystal") {
//if (thePrePV->GetName()=="TopAir" &&  thePostPV!=NULL){

        Int_t counter = CreateTree::Instance()->OutSurface;
        CreateTree::Instance()->OutSurface++;

        CreateTree::Instance()->DeltaMomReflX.push_back (CreateTree::Instance()->MomentumInX.back() - thePostPoint->GetMomentumDirection().x());
        CreateTree::Instance()->DeltaMomReflY.push_back (CreateTree::Instance()->MomentumInY.back() - thePostPoint->GetMomentumDirection().y());
        CreateTree::Instance()->DeltaMomReflZ.push_back (CreateTree::Instance()->MomentumInZ.back() - thePostPoint->GetMomentumDirection().z());

        CreateTree::Instance()->DeltaPolReflX.push_back (CreateTree::Instance()->PolInX.back() - thePostPoint->GetPolarization().x());
        CreateTree::Instance()->DeltaPolReflY.push_back (CreateTree::Instance()->PolInY.back() - thePostPoint->GetPolarization().y());
        CreateTree::Instance()->DeltaPolReflZ.push_back (CreateTree::Instance()->PolInZ.back() - thePostPoint->GetPolarization().z());

        CreateTree::Instance()->MomReflX.push_back (thePostPoint->GetMomentumDirection().x());
        CreateTree::Instance()->MomReflY.push_back (thePostPoint->GetMomentumDirection().y());
        CreateTree::Instance()->MomReflZ.push_back (thePostPoint->GetMomentumDirection().z());


//         theStep->GetTrack()->SetTrackStatus (fStopAndKill);
    }

    if (thePrePV->GetName() == "TopAir" &&  thePostPV->GetName() == "World") {

        CreateTree::Instance()->DeltaMomRefrX.push_back (CreateTree::Instance()->MomentumInX.back() - thePostPoint->GetMomentumDirection().x());
        CreateTree::Instance()->DeltaMomRefrY.push_back (CreateTree::Instance()->MomentumInY.back() - thePostPoint->GetMomentumDirection().y());
        CreateTree::Instance()->DeltaMomRefrZ.push_back (CreateTree::Instance()->MomentumInZ.back() - thePostPoint->GetMomentumDirection().z());

        CreateTree::Instance()->DeltaPolRefrX.push_back (CreateTree::Instance()->PolInX.back() - thePostPoint->GetPolarization().x());
        CreateTree::Instance()->DeltaPolRefrY.push_back (CreateTree::Instance()->PolInY.back() - thePostPoint->GetPolarization().y());
        CreateTree::Instance()->DeltaPolRefrZ.push_back (CreateTree::Instance()->PolInZ.back() - thePostPoint->GetPolarization().z());


    }

// ------------------------ FINE ------------------------- //

    // ------------------------ STORING OPTICAL PROCESSES ------------------------- //

    //find the boundary process only once
    if (!boundary) {
        G4ProcessManager* pm = theStep->GetTrack()->GetDefinition()->GetProcessManager();
        G4int nprocesses = pm->GetProcessListLength();
        G4ProcessVector* pv = pm->GetProcessList();
        G4int i;
        for (i = 0; i < nprocesses; i++) {
            if ( (*pv) [i]->GetProcessName() == "OpBoundary") {
                boundary = (G4OpBoundaryProcess*) (*pv) [i];
                break;
            }
        }
    }

    if (!boundary) return;

    boundaryStatus = boundary->GetStatus();

    //Check to see if the particle was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check

    if (thePostPoint->GetStepStatus() == fGeomBoundary) {
        bool ISREFL = false;
        switch (boundaryStatus) {
        case Absorption: {
            if (CreateTree::Instance()->Absorptions()) {




                CreateTree::Instance()->BoundaryAbsorptionTime[CreateTree::Instance()->NumBoundaryAbsorption] = theStep->GetTrack()->GetGlobalTime();
                CreateTree::Instance()->BoundaryAbsorptionPhotonEnergy[CreateTree::Instance()->NumBoundaryAbsorption] = theStep->GetTrack()->GetTotalEnergy();
                CreateTree::Instance()->BoundaryAbsorptionPosX[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().x();
                CreateTree::Instance()->BoundaryAbsorptionPosY[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().y();
                CreateTree::Instance()->BoundaryAbsorptionPosZ[CreateTree::Instance()->NumBoundaryAbsorption] = thePostPoint->GetPosition().z();
            }

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
            CreateTree::Instance()->NumBoundaryFresnelRefraction++;
            ISREFL = true;
            break;

        case BackScattering:
            CreateTree::Instance()->NumBoundaryBackScattering++;
            ISREFL = true;
            break;

        default:
            ISREFL = false;
            break;
        } // end switch

        if (ISREFL) {
            if (CreateTree::Instance()->Absorptions()) {
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

