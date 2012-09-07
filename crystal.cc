// Martin Goettlich @ DESY
//
#include <time.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4ios.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include <sstream>
#include "PrimaryGeneratorAction.hh"
//#include "MyPrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "StackingAction.hh"
#include "SteppingVerbose.hh"
#include "SteppingAction.hh"
#include "MyMaterials.hh"

#include "Randomize.hh"

#include "ConfigFile.h"

#include "TRandom1.h"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "CreateTree.hh"
#include "TString.h"

#include "G4UIExecutive.hh"


#include "TCint.h"
using namespace std;

// Ciao vecchio pirata

long int CreateSeed();



int main(int argc, char **argv)
{
    // -----------------------------------------
    // -----------------------------------------
    // PARSE CONFIGURATION FILE
    // -----------------------------------------
    // -----------------------------------------

    if(argc < 2) {
        cout << "Syntax: crystal <configuration file>" << endl;
        exit(0);
    }
#pragma link off all classes;
#pragma link C++ class std::vector<float>;
    gInterpreter->GenerateDictionary("vector<float>", "vector");



    cout << "\n" << endl;
    cout << "###########################################################" << endl;
    cout << "#                                                         #" << endl;
    cout << "#  GEANT4 simulation of a scintillator read-out           #" << endl;
    cout << "#  by a photo-detector.                                   #" << endl;
    cout << "#                                                         #" << endl;
    cout << "#  Author: Martin Goettlich, DESY, 2010                   #" << endl;
    cout << "#                                                         #" << endl;
    cout << "###########################################################" << endl;
    cout << "\n\n" << endl;
    cout << "=====>   C O N F I G U R A T I O N   <====\n" << endl;

    G4cout << "Configuration file: '" << argv[1] << "'" << G4endl;
    ConfigFile config(argv[1]);
    string filename;
    config.readInto(filename, "output");
    G4cout << "Writing data to file '" << filename << "' ..." << G4endl;
    string macro;
    config.readInto(macro, "macro");
    G4cout << "Reading macro '" << macro << "' ..." << G4endl;
    G4long myseed = config.read<long int> ("seed");
    if(myseed == -1) {
        G4cout << "Creating random seed..." << G4endl;
        myseed = CreateSeed();
    }
    G4cout << "Random seed : " << myseed << G4endl;
    Bool_t HITS = (Bool_t) config.read<int> ("hits");
    Bool_t ABSORPTIONS = (Bool_t) config.read<int> ("absorptions");
    G4cout << "Store x,y,z of hits : " << HITS << G4endl;
    G4cout << "Store x,y,z of absorptions : " << ABSORPTIONS << G4endl;

    G4int showPhotons = config.read<double> ("showPhotons");

    // Other crystal parameters
    G4double len = config.read<double> ("height");
    G4cout << "Crystal length [mm]: " << len << G4endl;
    G4double crystalx = config.read<double> ("crystalx");
    G4cout << "Crystal dimension x [mm]: " << crystalx << G4endl;
    G4double crystaly = config.read<double> ("crystaly");
    G4cout << "Crystal dimension y [mm]: " << crystaly << G4endl;

    G4double lightyield = config.read<double> ("lightyield");
    if(lightyield >= 0) {
        G4cout << "Light yield [1/MeV]: " << lightyield << G4endl;
    } else {
        G4cout << "Light yield [1/MeV]: material default" << G4endl;
    }
    G4double risetime = config.read<double> ("risetime");
    if(risetime >= 0) {
        G4cout << "Scintillation rise time [ns]: " << risetime << G4endl;
    } else {
        G4cout << "Scintillation rise time [ns]: material default" << G4endl;
    }
    G4double abslen = config.read<double> ("abslength");
    if(abslen >= 0) {
        G4cout << "Absorption length in crystal [mm]: " << abslen << G4endl;
    } else {
        G4cout << "Absorption length in crystal [mm]: material default" << G4endl;
    }

    // Crystal surface properties
    G4cout << "\nCrystal surface properties: " << G4endl;




    // -----------------------------------------
    // -----------------------------------------
    // SET DETECTOR PROPERTIES
    // -----------------------------------------
    // -----------------------------------------

    CreateTree *mytree = new CreateTree("g4pet", HITS, ABSORPTIONS);
    DetectorConstruction *detector = new DetectorConstruction();

    G4Material *tlMaterial = 0;
    switch(config.read<int> ("tlmaterial")) {
    case 1:
        G4cout << "Scintillator material: Silicon" << G4endl;
        tlMaterial = MyMaterials::Silicon();
        break;
    case 2:
        G4cout << "Scintillator material: Air" << G4endl;
        tlMaterial = MyMaterials::Air();
        break;
    default:
        G4cerr << "<main>: Invalid material specifier: " << config.read<int> ("tlmaterial") << G4endl;
        exit(0);
    }
    detector->setTopLayerMaterial(tlMaterial);

    // -----------------------------------------
    // -----------------------------------------
    // END CONFIGURATION ----> SIMULATION
    // -----------------------------------------
    // -----------------------------------------

    cout << "\n\n" << endl;
    cout << "=====>   S I M U L A T I O N   <====" << endl;

    CLHEP::HepRandom::setTheSeed(myseed);

    // User Verbose output class
    G4VSteppingVerbose *verbosity = new SteppingVerbose;
    G4VSteppingVerbose::SetInstance(verbosity);

    // Run manager
    G4RunManager *runManager = new G4RunManager;

    // UserInitialization classes - mandatory / Detector
    runManager->SetUserInitialization(detector);

    // UserInitialization classes - mandatory / Physics list
    G4VUserPhysicsList *physics = NULL;
    physics = new PhysicsList;
    runManager->SetUserInitialization(physics);

    // Visualization manager
#ifdef G4VIS_USE
    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

    // UserAction classes
    G4UserRunAction *run_action = new RunAction;
    runManager->SetUserAction(run_action);

    // Gen action
    G4VUserPrimaryGeneratorAction *gen_action = NULL;
    gen_action = new PrimaryGeneratorAction;
    runManager->SetUserAction(gen_action);

    // Event action
    G4UserEventAction *event_action = new EventAction;
    runManager->SetUserAction(event_action);

    // Stacking action
    G4UserStackingAction *stacking_action = new StackingAction;
    runManager->SetUserAction(stacking_action);

    // Stepping action
    SteppingAction *stepping_action = new SteppingAction;
    stepping_action->setShowPhotons(showPhotons);
    runManager->SetUserAction(stepping_action);

    // Initialize G4 kernel
    runManager->Initialize();

    // Get the pointer to the User Interface manager
    G4UImanager *UI = G4UImanager::GetUIpointer();

    if(macro == "") {
        // Define UI session for interactive mode
        G4UIsession *session = 0;
#ifdef G4UI_USE_TCSH
        session = new G4UIterminal(new G4UItcsh);
#else
        session = new G4UIterminal();
#endif
        //UI->ApplyCommand("/control/execute vis.mac");
        session->SessionStart();
        delete session;
    } else {
        // Batch mode
        //UI->ApplyCommand("/control/execute physics.in");
        G4String command = "/control/execute ";
        G4String fileName = macro;
        UI->ApplyCommand(command + fileName);
    }

    //per fermare il terminale utente
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    ui->SessionStart();
    delete ui;

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    //                 owned and deleted by the run manager, so they should not
    //                 be deleted in the main() program !

#ifdef G4VIS_USE
    delete visManager;
#endif
    delete runManager;
    delete verbosity;

    if(argv[2] != NULL) {
        filename = argv[2];
    }
    TFile *outfile = new TFile((TString) filename, "RECREATE");
    outfile->cd();
    G4cout << "Writing tree to file " << filename << " ..." << G4endl;
    mytree->GetTree()->Write();
    outfile->Write();
    outfile->Close();

    return 0;
}


long int CreateSeed()
{
    TRandom1 rangen;
    long int s = time(0);
    cout << "Time : " << s << endl;
    s += getpid();
    cout << "PID  : " << getpid() << endl;

    FILE *fp = fopen("/dev/urandom", "r");
    int uptime, upsecs;
    if(fp != NULL) {
        char buf[BUFSIZ];
        int res;
        char *b = fgets(buf, BUFSIZ, fp);
        if(b == buf) {
            /* The following sscanf must use the C locale.  */
            setlocale(LC_NUMERIC, "C");
            res = sscanf(buf, "%i", &upsecs);
            setlocale(LC_NUMERIC, "");
            if(res == 1) uptime = (time_t) upsecs;
        }
        fclose(fp);
    }

    cout << "Uptime: " << upsecs << endl;
    s += upsecs;

    cout << "Seed for srand: " << s << endl;
    srand(s);
    rangen.SetSeed(rand());
    long int seed = round(1000000 * rangen.Uniform());
    return seed;
}

