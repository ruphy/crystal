//
// Martin Goettlich @ DESY
// sc. crystal fibre read-out at both sides
//

#include "DetectorConstruction.hh"
#include "CreateTree.hh"
#include "MyMaterials.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"

#include "G4OpBoundaryProcess.hh"
#include "G4SDManager.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4SubtractionSolid.hh"

using namespace std;

class DetectorConstruction::Private
{
    Private() {
        topLayerMaterial = MyMaterials::Air();
    }

    G4Material *topLayerMaterial;

    friend class DetectorConstruction;
};

DetectorConstruction::DetectorConstruction()
{
    // set defaults for geometry and material properties
    //detectorMessenger = new DetectorMessenger(this);

    expHall_x = expHall_y = expHall_z = 400 * cm;
    crystal_abslength    = -1;

    updated = true;
    d = new Private;
}

DetectorConstruction::~DetectorConstruction()
{
    delete d;
}

void DetectorConstruction::setTopLayerMaterial(G4Material *material)
{
    d->topLayerMaterial = material;
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    readConfigFile("crystal.cfg");
    initializeMaterials();

    //
    //   S U R F A C E S   I N I T I A L I Z A T I O N
    //

    G4LogicalBorderSurface *CrystalSurfaceTop   = NULL;
    G4LogicalBorderSurface *TopWrappingSurface      = NULL;

    G4OpticalSurface *OpWrappingSurface         = NULL;
    G4OpticalSurface *OpCrystalSurface      = NULL;


    //
    // C O M M O N   V O L U M E S
    //


    /*-------EXPERIMENTAL HALL-------*/

    G4Box *expHall_box = new G4Box("World", expHall_x, expHall_y, expHall_z);
    G4LogicalVolume *expHall_log = new G4LogicalVolume(expHall_box, Air, "World", 0, 0, 0);
    G4VPhysicalVolume *expHall_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), expHall_log, "World", 0, false, 0);


    /*-------CRYSTAL-------*/

    G4LogicalVolume   *Crystal_log    = NULL;
    G4VPhysicalVolume *Crystal_phys   = NULL;

    G4Box *Crystal_box = new G4Box("Crystal", 0.5 * crystal_x, 0.5 * crystal_y, 0.5 * crystal_height);
    Crystal_log = new G4LogicalVolume(Crystal_box, ScMaterial, "Crystal", 0, 0, 0);
    Crystal_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), Crystal_log, "Crystal", expHall_log, false, 0);


    /*-------Sensor-------*/
    airgap = 100; // TODO HACK FIXME
    G4Box *TA_box = new G4Box("Sensor", 0.5 * crystal_x, 0.5 * crystal_y, 0.5 * airgap);
    G4LogicalVolume *TA_log  = new G4LogicalVolume(TA_box, Air, "Sensor", 0, 0, 0);
    G4VPhysicalVolume *TA_phys = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5 * (crystal_height)+airgap), TA_log, "Sensor", expHall_log, false, 0);
    TA_log->SetVisAttributes(G4Color(128/255,0,0));


    //
    // S U R F A C E S   C O N F I G U R A T I O N
    //

    //CASE 0: CRYSTAL ONLY
    if(surConfig == 0) {
        //Nothing - Crystal completely polished

    } else if(surConfig == 1) {
        cout << "Configuring a naked crystal, with only a tiny wrapping" << endl;
        /*-------CRYSTAL SURFACE-------*/
        OpCrystalSurface = new G4OpticalSurface("crystal");
        initializeSurface(OpCrystalSurface, "crystal");
        initializeReflectivitySurface(OpCrystalSurface, "crystal");
        CrystalSurfaceTop   = new G4LogicalBorderSurface("CrystalSurfaceTop", Crystal_phys, expHall_phys, OpCrystalSurface);

    }


    //
    // Visualization attributes
    //
    Crystal_log->SetVisAttributes(G4Colour(0, 87 / 255., 219 / 255.));
    expHall_log->SetVisAttributes(G4VisAttributes::Invisible);

    //always return the physical World
    return expHall_phys;
}


//
// Update geometry
//
void DetectorConstruction::UpdateGeometry()
{
    G4cout << "Updating detector ..." << G4endl;
    // clean-up previous geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    G4LogicalSkinSurface::CleanSurfaceTable();
    G4LogicalBorderSurface::CleanSurfaceTable();

    //define new one
    G4RunManager::GetRunManager()->DefineWorldVolume(this->Construct());
    G4RunManager::GetRunManager()->GeometryHasBeenModified();

    CreateTree::Instance()->CrystalHeight = crystal_height;
    updated = false;
}

G4bool DetectorConstruction::GetUpdated() const
{
    return updated;
}


// Initialization classes
//
void DetectorConstruction::initializeSurface(G4OpticalSurface *mySurface, string surfaceType)
{
    if(surfaceType == "crystal") {
//         cout << "CRISTALLO " << crystalSurfinish << endl;
        surfinish   = crystalSurfinish;
        RefFile     = cReffile;
        reflectivity    = cReflectivity;
        surrefind   = cSurrefind;
        surtype     = cSurtype;
        specularspike   = cSpecularspike;
        specularlobe    = cSpecularlobe;
        sigmaalpha  = cSigmaalpha;
        backscatter     = cBackscatter;
        lambertian  = cLambertian;
    }



    if(this->surfinish <= 5) {
        G4cout << "Using unified model." << G4endl;
        mySurface -> SetModel(unified);
        switch(this->surtype) {
        case 0:
            mySurface -> SetType(dielectric_metal);
            G4cout << "Surface type: dielectric_metal" << G4endl;
            break;
        case 1:
            mySurface -> SetType(dielectric_dielectric);
            G4cout << "Surface type: dielectric_dielectric" << G4endl;
            break;
        }
    } else if(this->surfinish > 5 && surfaceType == "wrapping") G4cout << "Value not allowed" << G4endl;
    else {
        G4cout << "Using LUT for surface treatment." << G4endl;
        mySurface -> SetModel(LUT);
        mySurface -> SetType(dielectric_LUT);
    }

    switch(this->surfinish) {
    case 0:
        mySurface -> SetFinish(polished);
        G4cout << "Surface finish: polished" << G4endl;
        break;
    case 1:
        mySurface -> SetFinish(polishedfrontpainted);
        G4cout << "Surface finish: polishedfrontpainted" << G4endl;
        break;
    case 2:
        mySurface -> SetFinish(polishedbackpainted);
        G4cout << "Surface finish: polishedbackpainted" << G4endl;
        break;
    case 3:
        mySurface -> SetFinish(ground);
        G4cout << "Surface finish: ground" << G4endl;
        break;
    case 4:
        mySurface -> SetFinish(groundfrontpainted);
        G4cout << "Surface finish: groundfrontpainted" << G4endl;
        break;
    case 5:
        mySurface -> SetFinish(groundbackpainted);
        G4cout << "Surface finish: groundbackpainted" << G4endl;
        break;
    case 17:
        mySurface -> SetFinish(polishedteflonair);
        G4cout << "Surface finish: polishedteflonair" << G4endl;
        break;
    case 18:
        mySurface -> SetFinish(polishedtioair);
        G4cout << "Surface finish: polishedtioair" << G4endl;
        break;
    case 26:
        mySurface -> SetFinish(etchedtioair);
        G4cout << "Surface finish: etchedtioair" << G4endl;
        break;
    case 34:
        mySurface -> SetFinish(groundtioair);
        G4cout << "Surface finish: groundtioair" << G4endl;
        break;
    case 36:
        mySurface -> SetFinish(polishedtyvekair);
        G4cout << "Surface finish: polishedtyvekair" << G4endl;
        break;
    default:
        G4cout << "Surface finish unkown!" << G4endl;
        exit(0);
    }
}


//
// reflectivity
//
void DetectorConstruction::initializeReflectivitySurface(G4OpticalSurface *surface, string surfaceType)
{

    int NumRefl = 0;
    G4double EphotonRefl[1000];
    G4double Refl[1000];
    if(this->RefFile != "none") {
        ifstream myReadFile;
        myReadFile.open(this->RefFile);

        G4cout << "Reflectivities read from file:" << G4endl;
        if(myReadFile.is_open()) {
            while(!myReadFile.eof()) {
                myReadFile >> EphotonRefl[NumRefl];
                if(EphotonRefl[NumRefl] == -1) break;
                myReadFile >> Refl[NumRefl];
                // convert to energy (1eV corresponds to 1239.8 nm: energy [eV]= 1239.8nmeV/lambda[nm])
                EphotonRefl[NumRefl] = 1239.8 / EphotonRefl[NumRefl] * eV;
                NumRefl++;
            }
        } else {
            G4cerr << "<DetectorConstruction> : Could not read file with reflectivities!" << G4endl;
            exit(0);
        }
        myReadFile.close();
    } else {
        EphotonRefl[0] = 0.0001 * eV;
        EphotonRefl[1] = 1.0 * eV;
        EphotonRefl[2] = 4.08 * eV;
        Refl[0] = 0.0; // suppress photons with energy < 1eV (will not be detected)
        Refl[1] = this->crystal_reflectivity;
        Refl[2] = this->crystal_reflectivity;
        NumRefl = 3;


    }
    G4cout << "Reflectivities as a function of the photon energy:" << G4endl;
    for(int i = 0; i < NumRefl; i++) {
        G4cout << i << "   " << EphotonRefl[i] << "   " << Refl[i] << G4endl;
    }


    Ephoton[0] = 0.0001 * eV;
    Ephoton[1] = 1.0 * eV;
    Ephoton[2] = 4.08 * eV;
    G4double RefractiveIndex[3] = {this->surrefind, this->surrefind, this->surrefind};
    G4double SpecularLobe[3]    = {this->specularlobe, this->specularlobe, this->specularlobe};
    G4double SpecularSpike[3]   = {this->specularspike, this->specularspike, this->specularspike};
    G4double Backscatter[3]     = {this->backscatter, this->backscatter, this->backscatter};
    G4double Lambertian[3]      = {this->lambertian, this->lambertian, this->lambertian};
    G4MaterialPropertiesTable *myST = new G4MaterialPropertiesTable();
    G4cout << "Read from config-file: " << G4endl;
    G4cout << "Read SPECULARLOBECONSTANT  : " << SpecularLobe[0] << G4endl;
    G4cout << "Read SPECULARSPIKECONSTANT : " << SpecularSpike[0] << G4endl;
    G4cout << "Read BACKSCATTERCONSTANT   : " << Backscatter[0] << G4endl;
    G4cout << "Read LAMBERTIAN            : " << Lambertian[0] << G4endl;
    G4cout << "Read ref. index            : " << RefractiveIndex[0] << G4endl;

    myST->AddProperty("RINDEX", Ephoton, RefractiveIndex, 3);
    if(this->specularlobe >= 0) {
        G4cout << "Setting SPECULARLOBECONSTANT to : " << SpecularLobe[0] << G4endl;
        myST->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    3);
    }
    if(this->specularspike >= 0) {
        G4cout << "Setting SPECULARSPIKECONSTANT to : " << SpecularSpike[0] << G4endl;
        myST->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   3);
    }
    if(this->backscatter >= 0) {
        G4cout << "Setting BACKSCATTERCONSTANT to : " << Backscatter[0] << G4endl;
        myST->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     3);
    }
    if(this->lambertian >= 0) {
        G4cout << "Setting LAMBERTIAN to : " << Lambertian[0] << G4endl;
        myST->AddProperty("LAMBERTIAN",            Ephoton, Lambertian,      3);
    }


    //myST->AddProperty("REFLECTIVITY", EphotonRefl, Refl, NumRefl);
    //try with real and complex index... remove line above and use ones below.
    G4double tyvek_rwavelength[1000] = { 1.24984 * eV, 1.3051 * eV, 1.3776 * eV, 1.45864 * eV, 1.5498 * eV, 1.65312 * eV, 1.7712 * eV, 1.90745 * eV, 2.0664 * eV,
                                         2.25426 * eV, 2.47968 * eV, 2.7552 * eV, 3.0996 * eV, 3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 4.13281 * eV
                                       };
    G4double tyvek_rindex[1000] = { 1.37, 1.49, 2.06, 2.61, 2.7, 2.4, 1.8, 1.32, 1.13, 0.907, 0.72, 0.578, 0.456, 0.433, 0.41, 0.382, 0.38, 0.4, 0.276};


    G4double tyvek_cwavelength[1000] = {1.24997 * eV, 1.3051 * eV, 1.34037 * eV, 1.3776 * eV, 1.41696 * eV, 1.45864 * eV, 1.50284 * eV, 1.6 * eV, 1.65312 * eV,
                                        1.74995 * eV, 1.8 * eV, 1.89985 * eV, 1.95005 * eV, 2.05 * eV, 2.1 * eV, 2.19986 * eV, 2.25426 * eV, 2.34997 * eV, 2.4498 * eV,
                                        2.50019 * eV, 2.7 * eV, 2.8 * eV, 2.99986 * eV, 3.19959 * eV, 3.39962 * eV, 3.54241 * eV, 3.69992 * eV, 3.9001 * eV, 4.13281 * eV
                                       };
    G4double tyvek_cindex[1000] = { 9.49, 8.88, 8.49, 8.3, 8.18, 8.22, 8.31, 8.6, 8.62,
                                    8.39, 8.21, 7.82, 7.65, 7.31, 7.15, 6.85, 6.69, 6.42, 6.15,
                                    6.03, 5.58, 5.38, 5.02, 4.71, 4.43, 4.24, 4.06, 3.84, 3.61
                                  };
    //-----------------------------------------------------------------------------------//
    myST->AddProperty("REALRINDEX", tyvek_rwavelength, tyvek_rindex, 19);
    myST->AddProperty("IMAGINARYRINDEX", tyvek_cwavelength, tyvek_cindex, 29);


    G4double air_rwavelength[1000] = {0.1 * eV, 1 * eV, 2 * eV, 3 * eV, 4 * eV};
    G4double air_rindex[1000] = {1, 1, 1, 1, 1};

    G4double air_cwavelength[1000] = {0.1 * eV, 1 * eV, 2 * eV, 3 * eV, 4 * eV};
    G4double air_cindex[1000] = {1, 1, 1, 1, 1};
    //myST->AddProperty("REALRINDEX", air_rwavelength, air_rindex, 5);
    //myST->AddProperty("IMAGINARYRINDEX", air_cwavelength, air_cindex, 5);



    surface->SetMaterialPropertiesTable(myST);
    if(this->sigmaalpha >= 0) surface->SetSigmaAlpha(this->sigmaalpha);


}


void DetectorConstruction::initializeMaterials()
{

    //
    // Materials
    //
    Air       = MyMaterials::Air();
    Water     = MyMaterials::Water();
    Vacuum    = MyMaterials::Vacuum();
    Silicon   = MyMaterials::Silicon();
    OptGrease = MyMaterials::OpticalGrease();
    ScMaterial = NULL;
    G4double EphotonMat[3] = {0.0001 * eV, 1.0 * eV, 4.08 * eV};


    if(crystal_material == 1)        ScMaterial = MyMaterials::LSO();
    else if(crystal_material == 2)   ScMaterial = MyMaterials::LYSO();
    else if(crystal_material == 3)   ScMaterial = MyMaterials::LUAGCE();
    else if(crystal_material == 4)   ScMaterial = MyMaterials::LUAGPR();
    else if(crystal_material == 5)   ScMaterial = MyMaterials::PbWO();
    else if(crystal_material == 6)   ScMaterial = MyMaterials::Air();
    else if(crystal_material > 6 || crystal_material <= 0) {
        G4cerr << "<DetectorConstruction::Construct>: Invalid material specifier " << crystal_material << G4endl;
        exit(0);
    }
    G4cout << "Sc. material: " << ScMaterial << G4endl;

    //
    // modify default properties of the scintillator
    //
    if(crystal_lightyield >= 0) {
        ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("SCINTILLATIONYIELD");
        ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("SCINTILLATIONYIELD", crystal_lightyield / MeV);
    } else {
        CreateTree::Instance()->ScintillationYield = ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("SCINTILLATIONYIELD");
    }
    if(crystal_risetime >= 0) {
        ScMaterial->GetMaterialPropertiesTable()->RemoveConstProperty("FASTSCINTILLATIONRISETIME");
        ScMaterial->GetMaterialPropertiesTable()->AddConstProperty("FASTSCINTILLATIONRISETIME", crystal_risetime / ns);
    } else {
        CreateTree::Instance()->RiseTime = ScMaterial->GetMaterialPropertiesTable()->GetConstProperty("FASTSCINTILLATIONRISETIME");
    }
    if(this->crystal_abslength >= 0) {
        ScMaterial->GetMaterialPropertiesTable()->RemoveProperty("ABSLENGTH");
        G4double Abslengh[2]    = {crystal_abslength *mm, crystal_abslength *mm};
        ScMaterial->GetMaterialPropertiesTable()->AddProperty("ABSLENGTH", EphotonMat, Abslengh, 2);
    } else {
        //CreateTree::Instance()->AbsLength = ScMaterial->GetMaterialPropertiesTable()->GetProperty("ABSLENGTH")->GetProperty(1.0*eV);
    }
}

void DetectorConstruction::readConfigFile(string configFileName)
{

    ConfigFile config(configFileName);
    config.readInto(crystal_height, "height");
    config.readInto(crystal_x, "crystalx");
    config.readInto(crystal_y, "crystaly");
    config.readInto(airgap, "airgap");

    config.readInto(crystal_material, "scmaterial");
    config.readInto(crystal_risetime, "risetime");
    config.readInto(crystal_lightyield, "lightyield");
    config.readInto(surConfig, "surConfig");
    config.readInto(wReffile, "wReffile");
    config.readInto(wReflectivity, "wReflectivity");
    config.readInto(wSurrefind, "wSurrefind");
    config.readInto(wSurtype, "wSurtype");
    config.readInto(wSpecularspike, "wSpecularspike");
    config.readInto(wSpecularlobe, "wSpecularlobe");
    config.readInto(wSigmaalpha, "wSigmaalpha");
    config.readInto(wLambertian, "wLambertian");
    config.readInto(wrappingSurfinish, "wrappingSurfinish");
    config.readInto(cReffile, "cReffile");
    config.readInto(crystal_reflectivity, "cReflectivity");
    config.readInto(cSurrefind, "cSurrefind");
    config.readInto(cSurtype, "cSurtype");
    config.readInto(cSpecularspike, "cSpecularspike");
    config.readInto(cSpecularlobe, "cSpecularlobe");
    config.readInto(cSigmaalpha, "cSigmaalpha");
    config.readInto(cSpecularspike, "cSpecularspike");
    config.readInto(cSpecularlobe, "cSpecularlobe");
    config.readInto(cSigmaalpha, "cSigmaalpha");
    config.readInto(cBackscatter, "cBackscatter");
    config.readInto(cLambertian, "cLambertian");
    config.readInto(crystalSurfinish, "crystalSurfinish");

}










