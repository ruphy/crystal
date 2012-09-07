#include "globals.hh"
#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4ProcessManager.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList() :  G4VUserPhysicsList()
{
    theCerenkovProcess           = NULL;
    theScintillationProcess      = NULL;
    theAbsorptionProcess         = NULL;
    theRayleighScatteringProcess = NULL;
    theMieHGScatteringProcess    = NULL;
    theBoundaryProcess           = NULL;

    defaultCutValue = 0.01 * mm;
    cutForGamma     = defaultCutValue;
    cutForElectron  = defaultCutValue;
    cutForPositron  = defaultCutValue;
    cutForProton    = defaultCutValue;

    pMessenger = new PhysicsListMessenger (this);
    SetVerboseLevel (0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{
    delete pMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructParticle()
{
    // In this method, static member functions should be called
    // for all particles which you want to use.
    // This ensures that objects of these particle types will be
    // created in the program.

    ConstructBosons();
    ConstructLeptons();
    ConstructMesons();
    ConstructBaryons();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructBosons()
{
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    // optical photon
    G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructLeptons()
{
    // leptons
    //  e+/-
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    // mu+/-
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();
    // nu_e
    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    // nu_mu
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructMesons()
{
    //  mesons
    G4PionPlus::PionPlusDefinition();
    G4PionMinus::PionMinusDefinition();
    G4PionZero::PionZeroDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructBaryons()
{
    //  barions
    G4Proton::ProtonDefinition();
    G4AntiProton::AntiProtonDefinition();

    G4Neutron::NeutronDefinition();
    G4AntiNeutron::AntiNeutronDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    ConstructGeneral();
    ConstructEM();
    ConstructOp();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructGeneral()
{
    // Add Decay Process
    G4Decay *theDecayProcess = new G4Decay();
    theParticleIterator->reset();
    while ( (*theParticleIterator) ()) {
        G4ParticleDefinition *particle = theParticleIterator->value();
        G4ProcessManager *pmanager = particle->GetProcessManager();
        if (theDecayProcess->IsApplicable (*particle)) {
            pmanager ->AddProcess (theDecayProcess);
            // set ordering for PostStepDoIt and AtRestDoIt
            pmanager ->SetProcessOrdering (theDecayProcess, idxPostStep);
            pmanager ->SetProcessOrdering (theDecayProcess, idxAtRest);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructEM()
{
    theParticleIterator->reset();
    while ( (*theParticleIterator) ()) {
        G4ParticleDefinition *particle = theParticleIterator->value();
        G4ProcessManager *pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        if (particleName == "gamma") {
            // gamma
            // Construct processes for gamma
            pmanager->AddDiscreteProcess (new G4GammaConversion());
            pmanager->AddDiscreteProcess (new G4ComptonScattering());
            pmanager->AddDiscreteProcess (new G4PhotoElectricEffect());

        } else
            if (particleName == "e-") {
                //electron
                // Construct processes for electron
                pmanager->AddProcess (new G4eMultipleScattering(), -1, 1, 1);
                pmanager->AddProcess (new G4eIonisation(),       -1, 2, 2);
                pmanager->AddProcess (new G4eBremsstrahlung(),   -1, 3, 3);

            } else
                if (particleName == "e+") {
                    //positron
                    // Construct processes for positron
                    pmanager->AddProcess (new G4eMultipleScattering(), -1, 1, 1);
                    pmanager->AddProcess (new G4eIonisation(),       -1, 2, 2);
                    pmanager->AddProcess (new G4eBremsstrahlung(),   -1, 3, 3);
                    pmanager->AddProcess (new G4eplusAnnihilation(),  0, -1, 4);

                } else
                    if (particleName == "mu+" ||
                            particleName == "mu-") {
                        //muon
                        // Construct processes for muon
                        pmanager->AddProcess (new G4MuMultipleScattering(), -1, 1, 1);
                        pmanager->AddProcess (new G4MuIonisation(),      -1, 2, 2);
                        pmanager->AddProcess (new G4MuBremsstrahlung(),  -1, 3, 3);
                        pmanager->AddProcess (new G4MuPairProduction(),  -1, 4, 4);

                    } else {
                        if ( (particle->GetPDGCharge() != 0.0) &&
                                (particle->GetParticleName() != "chargedgeantino")) {
                            // all others charged particles except geantino
                            pmanager->AddProcess (new G4hMultipleScattering(), -1, 1, 1);
                            pmanager->AddProcess (new G4hIonisation(),       -1, 2, 2);
                        }
                    }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::ConstructOp()
{
    theCerenkovProcess           = new G4Cerenkov ("Cerenkov");
    theScintillationProcess      = new G4Scintillation ("Scintillation");
    theAbsorptionProcess         = new G4OpAbsorption();
    theRayleighScatteringProcess = new G4OpRayleigh();
    theMieHGScatteringProcess    = new G4OpMieHG();
    theBoundaryProcess           = new G4OpBoundaryProcess();

//  theCerenkovProcess->DumpPhysicsTable();
//  theScintillationProcess->DumpPhysicsTable();
//  theRayleighScatteringProcess->DumpPhysicsTable();

    SetVerbose (0);

    theCerenkovProcess->SetMaxNumPhotonsPerStep (100);
    theCerenkovProcess->SetMaxBetaChangePerStep (10.0);
    theCerenkovProcess->SetTrackSecondariesFirst (true);

    theScintillationProcess->SetScintillationYieldFactor (1.);
    theScintillationProcess->SetTrackSecondariesFirst (true);

    // Use Birks Correction in the Scintillation process

    G4EmSaturation *emSaturation = G4LossTableManager::Instance()->EmSaturation();
    theScintillationProcess->AddSaturation (emSaturation);

    theParticleIterator->reset();
    while ( (*theParticleIterator) ()) {
        G4ParticleDefinition *particle = theParticleIterator->value();
        G4ProcessManager *pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        if (theCerenkovProcess->IsApplicable (*particle)) {
            pmanager->AddProcess (theCerenkovProcess);
            pmanager->SetProcessOrdering (theCerenkovProcess, idxPostStep);
        }
        if (theScintillationProcess->IsApplicable (*particle)) {
            pmanager->AddProcess (theScintillationProcess);
            pmanager->SetProcessOrderingToLast (theScintillationProcess, idxAtRest);
            pmanager->SetProcessOrderingToLast (theScintillationProcess, idxPostStep);
        }
        if (particleName == "opticalphoton") {
            G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
            pmanager->AddDiscreteProcess (theAbsorptionProcess);
            pmanager->AddDiscreteProcess (theRayleighScatteringProcess);
            pmanager->AddDiscreteProcess (theMieHGScatteringProcess);
            pmanager->AddDiscreteProcess (theBoundaryProcess);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetVerbose (G4int verbose)
{
    theCerenkovProcess->SetVerboseLevel (verbose);
    theScintillationProcess->SetVerboseLevel (verbose);
    theAbsorptionProcess->SetVerboseLevel (verbose);
    theRayleighScatteringProcess->SetVerboseLevel (verbose);
    theMieHGScatteringProcess->SetVerboseLevel (verbose);
    theBoundaryProcess->SetVerboseLevel (verbose);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetNbOfPhotonsCerenkov (G4int MaxNumber)
{
    theCerenkovProcess->SetMaxNumPhotonsPerStep (MaxNumber);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{

    if (verboseLevel > 0) {
        G4cout << "PhysicsList::SetCuts:";
        G4cout << "CutLength : " << G4BestUnit (defaultCutValue, "Length") << G4endl;
    }

    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma

    SetCutValue (cutForGamma, "gamma");
    SetCutValue (cutForElectron, "e-");
    SetCutValue (cutForPositron, "e+");
    SetCutValue (cutForProton, "proton");

    if (verboseLevel > 0) {
        DumpCutValuesTable();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForGamma (G4double cut)
{
    cutForGamma = cut;
    SetParticleCuts (cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForElectron (G4double cut)
{
    cutForElectron = cut;
    SetParticleCuts (cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForPositron (G4double cut)
{
    cutForPositron = cut;
    SetParticleCuts (cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCutForProton (G4double cut)
{
    cutForPositron = cut;
    SetParticleCuts (cutForProton, G4Proton::Proton());
}
