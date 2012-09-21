#include "MyMaterials.hh"


MyMaterials::MyMaterials()
{

}

MyMaterials::~MyMaterials()
{
    ;
}

G4Material *MyMaterials::Air()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *N = new G4Element ("Nitrogen", "N", z = 7 , a = 14.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);

    G4Material *Air = new G4Material ("Air", density = 1.29 * mg / cm3, nelements = 2);
    Air->AddElement (N, 70.*perCent);
    Air->AddElement (O, 30.*perCent);

    const G4int nEntries = 34;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.00 * eV,  2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003, 1.0003,
        1.0003, 1.0003, 1.0003, 1.0003, 1.0003
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

    Air->SetMaterialPropertiesTable (myMPT);

    return Air;
}


G4Material *MyMaterials::Water()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *H = new G4Element ("Hydrogen", "H", z = 1 , a = 1.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);
    G4Material *Water = new G4Material ("Water", density = 1.0 * g / cm3, nelements = 2);
    Water->AddElement (H, 2);
    Water->AddElement (O, 1);

    const G4int nEntries = 33;

    G4double PhotonEnergy[nEntries] = {
        0.1 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.3435, 1.3435, 1.344,  1.3445, 1.345,  1.3455,
        1.346,  1.3465, 1.347,  1.3475, 1.348,
        1.3485, 1.3492, 1.35,   1.3505, 1.351,
        1.3518, 1.3522, 1.3530, 1.3535, 1.354,
        1.3545, 1.355,  1.3555, 1.356,  1.3568,
        1.3572, 1.358,  1.3585, 1.359,  1.3595,
        1.36,   1.3608
    };

    G4double Absorption[nEntries] = {
        3.448, 3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m, 12.346 * m, 13.889 * m,
        15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
        45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
        52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
        30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
        17.500 * m, 14.500 * m
    };

    G4double ScintilFast[nEntries] = {
        1.00,   1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
        1.00, 1.00, 1.00, 1.00
    };
    G4double ScintilSlow[nEntries] = {
        0.01,   0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
        7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
        3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
        4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
        7.00, 6.00, 5.00, 4.00
    };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX",       PhotonEnergy, RefractiveIndex, nEntries);
    myMPT->AddProperty ("ABSLENGTH",    PhotonEnergy, Absorption,      nEntries);
    myMPT->AddProperty ("FASTCOMPONENT", PhotonEnergy, ScintilFast,     nEntries);
    myMPT->AddProperty ("SLOWCOMPONENT", PhotonEnergy, ScintilSlow,     nEntries);

    myMPT->AddConstProperty ("SCINTILLATIONYIELD", 50. / MeV);
    myMPT->AddConstProperty ("RESOLUTIONSCALE", 1.0);
    myMPT->AddConstProperty ("FASTTIMECONSTANT", 1.*ns);
    myMPT->AddConstProperty ("SLOWTIMECONSTANT", 10.*ns);
    myMPT->AddConstProperty ("YIELDRATIO", 0.8);

    Water->SetMaterialPropertiesTable (myMPT);

    return Water;
}
G4Material *MyMaterials::Vacuum()
{
    G4double a, z, density;
    G4int nelements;

    G4Element *N = new G4Element ("Nitrogen", "N", z = 7 , a = 14.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);

    G4Material *Air = new G4Material ("Air", density = 0.001 * mg / cm3, nelements = 2);
    Air->AddElement (N, 70.*perCent);
    Air->AddElement (O, 30.*perCent);

    const G4int nEntries = 3;

    G4double PhotonEnergy[nEntries] =
    { 0.0001 * eV, 1.00 * eV, 100.00 * eV };

    G4double RefractiveIndex[nEntries] =
    { 1.00, 1.00, 1.00 };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX", PhotonEnergy, RefractiveIndex, nEntries);

    Air->SetMaterialPropertiesTable (myMPT);

    return Air;
}
G4Material *MyMaterials::Silicon()
{
    G4double a, z, density;

    G4Element *Si = new G4Element ("Silicon",    "Si", z = 14., a = 28.09 * g / mole);
    G4Material *Silicon = new G4Material ("Silicon", density = 2.33 * g / cm3, 1);
    Silicon->AddElement (Si, 1);

    const G4int NUM = 4;

    G4double Energy[NUM]         = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUM]     = { 4.0, 4.0, 4.0, 4.0 };
    G4double ABS_LENGTH[NUM]     = { 0.1 * mm, 0.1 * mm, 0.1 * mm, 0.1 * mm};

    G4MaterialPropertiesTable *Si_mt = new G4MaterialPropertiesTable();
    Si_mt->AddProperty ("RINDEX",        Energy,  RIND_INDEX,     NUM);
    Si_mt->AddProperty ("ABSLENGTH",     Energy,  ABS_LENGTH,     NUM);

    Silicon->SetMaterialPropertiesTable (Si_mt);

    return Silicon;

}
G4Material *MyMaterials::OpticalGrease()
{
    G4double a, z, density;
    G4Element *H = new G4Element ("Hydrogen", "H", z = 1 , a = 1.01 * g / mole);
    G4Element *O = new G4Element ("Oxygen"  , "O", z = 8 , a = 16.00 * g / mole);
    G4Element *C = new G4Element ("Carbon"  , "C", z = 6 , a = 12.01 * g / mole);

    G4Material *Grease = new G4Material ("Grease", density = 1.0 * g / cm3, 3);
    Grease->AddElement (C, 1);
    Grease->AddElement (H, 1);
    Grease->AddElement (O, 1);

    const G4int nEntries = 34;

    G4double PhotonEnergy[nEntries] = {
        0.0001 * eV, 1.0 * eV, 2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV,
        2.177 * eV, 2.216 * eV, 2.256 * eV, 2.298 * eV,
        2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
        2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV,
        2.757 * eV, 2.820 * eV, 2.885 * eV, 2.954 * eV,
        3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
        3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV,
        3.760 * eV, 3.877 * eV, 4.002 * eV, 4.136 * eV
    };

    G4double RefractiveIndex[nEntries] = {
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50, 1.50, 1.50, 1.50,
        1.50, 1.50, 1.50, 1.50
    };

//   G4double Absorption[nEntries] =
//    { 3.448*m, 3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
//            15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
//            45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
//            52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
//            30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
//            17.500*m, 14.500*m };

    G4MaterialPropertiesTable *myMPT = new G4MaterialPropertiesTable();
    myMPT->AddProperty ("RINDEX",       PhotonEnergy, RefractiveIndex, nEntries);
//   myMPT->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption,      nEntries);
    Grease->SetMaterialPropertiesTable (myMPT);
    return Grease;
}


G4Material *MyMaterials::LUAGCE()  // Lutetium Aluminum Garnet
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71, a = 174.97 * g / mole);
    G4Element *Al = new G4Element ("Aluminum",  "Al",  z = 27, a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LUAG", density = 6.7 * g / cm3, 3);
    mat->AddElement (Lu, 3);
    mat->AddElement (Al, 12);
    mat->AddElement (O, 5);


    // large band between 470 (2.64 eV) and 630 nm (1.97 eV) (mean 535 nm, 2.32)
    const G4int NUMENTRIES_1 = 6;
    G4double FAST_Energy[NUMENTRIES_1]    = {1.0 * eV, 1.90 * eV, 1.97 * eV, 2.64 * eV, 2.70 * eV, 4.08 * eV};
    G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00, 0.00, 1.0, 1.0, 0.00, 0.00};


    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };
    G4double ABS_Energy[NUMENTRIES_2]     = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    //G4double ABS_LENGTH[NUMENTRIES_2]     = { 50.*m, 50.*m, 50.*m};
    G4double ABS_LENGTH[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm };
    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 15000 / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 8.5);
    mt->AddConstProperty ("FASTTIMECONSTANT", 60.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.5 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LUAGPR()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71, a = 174.97 * g / mole);
    G4Element *Al = new G4Element ("Aluminum",  "Al",  z = 27, a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LUAG", density = 6.7 * g / cm3, 3);
    mat->AddElement (Lu, 3);
    mat->AddElement (Al, 12);
    mat->AddElement (O, 5);

    //  2 bands at 290nm (4.28eV) and 350nm (3.54eV) about 50% of the light in each.
    const G4int NUMENTRIES_1 = 8;
    G4double FAST_Energy[NUMENTRIES_1]    = {1.0 * eV, 3.4 * eV, 3.5 * eV, 3.60 * eV, 3.90 * eV, 3.91 * eV, 4.07 * eV, 4.08 * eV};
    G4double FAST_COMPONENT[NUMENTRIES_1] = {0.00  , 0.00,  1.00,  0.0,    0.0,    1.0,    0.0,    0.0    };

    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };
    G4double ABS_Energy[NUMENTRIES_2]     = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double ABS_LENGTH[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm };
    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_2);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 7000 / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 6.4);
    mt->AddConstProperty ("FASTTIMECONSTANT", 20.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.5 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LYSO()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71., a = 174.97 * g / mole);
    G4Element *Si = new G4Element ("Silicon",   "Si",  z = 14., a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LYSO", density = 7.1 * g / cm3, 3, kStateSolid);
    mat->AddElement (Lu, 2);
    mat->AddElement (Si, 1);
    mat->AddElement (O, 5);

    const G4int NUMENTRIES_1 = 261;
    G4double FAST_Energy[NUMENTRIES_1] = {
        1.77169 * eV,
        1.77266 * eV,
        1.77558 * eV,
        1.77851 * eV,
        1.78145 * eV,
        1.78539 * eV,
        1.79033 * eV,
        1.7963 * eV,
        1.80231 * eV,
        1.80836 * eV,
        1.81445 * eV,
        1.82058 * eV,
        1.82882 * eV,
        1.83401 * eV,
        1.84553 * eV,
        1.85293 * eV,
        1.86147 * eV,
        1.869 * eV,
        1.87769 * eV,
        1.89308 * eV,
        1.90536 * eV,
        1.92007 * eV,
        1.93039 * eV,
        1.94901 * eV,
        1.95846 * eV,
        1.9668 * eV,
        1.97884 * eV,
        1.99102 * eV,
        2.00088 * eV,
        2.01209 * eV,
        2.02596 * eV,
        2.03617 * eV,
        2.04519 * eV,
        2.0569 * eV,
        2.06611 * eV,
        2.0794 * eV,
        2.09151 * eV,
        2.10239 * eV,
        2.112 * eV,
        2.1231 * eV,
        2.13431 * eV,
        2.14565 * eV,
        2.15566 * eV,
        2.16868 * eV,
        2.18038 * eV,
        2.19519 * eV,
        2.21171 * eV,
        2.2193 * eV,
        2.23619 * eV,
        2.23464 * eV,
        2.24395 * eV,
        2.25806 * eV,
        2.27234 * eV,
        2.28358 * eV,
        2.29493 * eV,
        2.30475 * eV,
        2.31631 * eV,
        2.32463 * eV,
        2.33134 * eV,
        2.33809 * eV,
        2.34487 * eV,
        2.35856 * eV,
        2.36719 * eV,
        2.37939 * eV,
        2.38642 * eV,
        2.40238 * eV,
        2.41134 * eV,
        2.424 * eV,
        2.43312 * eV,
        2.44047 * eV,
        2.44786 * eV,
        2.46278 * eV,
        2.47788 * eV,
        2.48741 * eV,
        2.49317 * eV,
        2.49702 * eV,
        2.50282 * eV,
        2.50865 * eV,
        2.5145 * eV,
        2.52038 * eV,
        2.52432 * eV,
        2.53223 * eV,
        2.5362 * eV,
        2.54619 * eV,
        2.55424 * eV,
        2.56031 * eV,
        2.56437 * eV,
        2.57049 * eV,
        2.57663 * eV,
        2.58487 * eV,
        2.59317 * eV,
        2.59734 * eV,
        2.60571 * eV,
        2.61414 * eV,
        2.61414 * eV,
        2.61837 * eV,
        2.62262 * eV,
        2.62475 * eV,
        2.62902 * eV,
        2.63331 * eV,
        2.63545 * eV,
        2.63976 * eV,
        2.64191 * eV,
        2.64841 * eV,
        2.65493 * eV,
        2.6593 * eV,
        2.66149 * eV,
        2.66588 * eV,
        2.67914 * eV,
        2.67914 * eV,
        2.68136 * eV,
        2.68136 * eV,
        2.68359 * eV,
        2.68805 * eV,
        2.68805 * eV,
        2.68805 * eV,
        2.69477 * eV,
        2.69477 * eV,
        2.69702 * eV,
        2.70153 * eV,
        2.70605 * eV,
        2.71286 * eV,
        2.71742 * eV,
        2.71971 * eV,
        2.722 * eV,
        2.722 * eV,
        2.72429 * eV,
        2.72889 * eV,
        2.72889 * eV,
        2.73351 * eV,
        2.73814 * eV,
        2.74279 * eV,
        2.74512 * eV,
        2.74979 * eV,
        2.75213 * eV,
        2.75447 * eV,
        2.75917 * eV,
        2.75682 * eV,
        2.76389 * eV,
        2.76626 * eV,
        2.76389 * eV,
        2.76626 * eV,
        2.77338 * eV,
        2.77576 * eV,
        2.78533 * eV,
        2.79255 * eV,
        2.79738 * eV,
        2.80223 * eV,
        2.80466 * eV,
        2.80709 * eV,
        2.80953 * eV,
        2.80953 * eV,
        2.81934 * eV,
        2.8218 * eV,
        2.82673 * eV,
        2.83168 * eV,
        2.84164 * eV,
        2.84916 * eV,
        2.85419 * eV,
        2.8643 * eV,
        2.86684 * eV,
        2.87449 * eV,
        2.87705 * eV,
        2.87961 * eV,
        2.88475 * eV,
        2.88733 * eV,
        2.8925 * eV,
        2.89509 * eV,
        2.90028 * eV,
        2.90549 * eV,
        2.90811 * eV,
        2.91073 * eV,
        2.91335 * eV,
        2.91335 * eV,
        2.91335 * eV,
        2.91861 * eV,
        2.92125 * eV,
        2.92125 * eV,
        2.92389 * eV,
        2.92654 * eV,
        2.92654 * eV,
        2.92919 * eV,
        2.92919 * eV,
        2.93185 * eV,
        2.93451 * eV,
        2.93717 * eV,
        2.93985 * eV,
        2.94252 * eV,
        2.9452 * eV,
        2.94789 * eV,
        2.94789 * eV,
        2.94789 * eV,
        2.95058 * eV,
        2.95868 * eV,
        2.96411 * eV,
        2.96955 * eV,
        2.97228 * eV,
        2.97228 * eV,
        2.96955 * eV,
        2.97228 * eV,
        2.97502 * eV,
        2.97776 * eV,
        2.97502 * eV,
        2.9805 * eV,
        2.9805 * eV,
        2.9805 * eV,
        2.98601 * eV,
        2.99154 * eV,
        2.99431 * eV,
        2.99431 * eV,
        2.99708 * eV,
        2.99431 * eV,
        2.99708 * eV,
        3.00544 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.01385 * eV,
        3.0223 * eV,
        3.02797 * eV,
        3.03081 * eV,
        3.02797 * eV,
        3.03365 * eV,
        3.03081 * eV,
        3.03081 * eV,
        3.0365 * eV,
        3.03935 * eV,
        3.04221 * eV,
        3.04795 * eV,
        3.04795 * eV,
        3.05083 * eV,
        3.05371 * eV,
        3.05949 * eV,
        3.06239 * eV,
        3.06529 * eV,
        3.0682 * eV,
        3.06529 * eV,
        3.07112 * eV,
        3.0682 * eV,
        3.07696 * eV,
        3.08283 * eV,
        3.0976 * eV,
        3.09464 * eV,
        3.09464 * eV,
        3.10653 * eV,
        3.11252 * eV,
        3.11852 * eV,
        3.12757 * eV,
        3.13668 * eV,
        3.14583 * eV,
        3.15813 * eV,
        3.16741 * eV,
        3.17675 * eV,
        3.20828 * eV,
        3.23719 * eV,
        3.26664 * eV,
        3.28656 * eV,
        3.31351 * eV,
        3.34783 * eV,
        3.38287 * eV,
    };
    G4double FAST_COMPONENT[NUMENTRIES_1] = {
        0.011691,
        0.011691,
        0.011691,
        0.0146138,
        0.0146138,
        0.0146138,
        0.011691,
        0.011691,
        0.00876827,
        0.00876827,
        0.00584551,
        0.00584551,
        0.00584551,
        0.00292276,
        0.00876827,
        0.0146138,
        0.0146138,
        0.0146138,
        0.0204593,
        0.023382,
        0.0263048,
        0.0204593,
        0.0204593,
        0.023382,
        0.0292276,
        0.0321503,
        0.0350731,
        0.0379958,
        0.0379958,
        0.0379958,
        0.0350731,
        0.0379958,
        0.0409186,
        0.0438413,
        0.0526096,
        0.0584551,
        0.0643006,
        0.0730689,
        0.0730689,
        0.0818372,
        0.0906054,
        0.0964509,
        0.0993737,
        0.105219,
        0.111065,
        0.122756,
        0.125678,
        0.146138,
        0.146138,
        0.160752,
        0.157829,
        0.163674,
        0.184134,
        0.192902,
        0.20167,
        0.219207,
        0.230898,
        0.242589,
        0.25428,
        0.265971,
        0.274739,
        0.292276,
        0.306889,
        0.315658,
        0.321503,
        0.350731,
        0.368267,
        0.385804,
        0.397495,
        0.415031,
        0.432568,
        0.458873,
        0.482255,
        0.496868,
        0.514405,
        0.529019,
        0.549478,
        0.564092,
        0.581628,
        0.593319,
        0.602088,
        0.616701,
        0.637161,
        0.660543,
        0.681002,
        0.71023,
        0.736534,
        0.756994,
        0.777453,
        0.806681,
        0.844676,
        0.868058,
        0.891441,
        0.9119,
        0.938205,
        0.955741,
        0.984969,
        1.0142,
        1.03173,
        1.05511,
        1.07557,
        1.11649,
        1.13695,
        1.15741,
        1.17495,
        1.19248,
        1.21002,
        1.22756,
        1.27432,
        1.2977,
        1.31524,
        1.32985,
        1.36785,
        1.40292,
        1.39415,
        1.4,
        1.41754,
        1.44092,
        1.47015,
        1.48476,
        1.50814,
        1.5286,
        1.54906,
        1.56952,
        1.58998,
        1.61921,
        1.63967,
        1.66597,
        1.68935,
        1.71566,
        1.73904,
        1.76242,
        1.77996,
        1.80042,
        1.8238,
        1.83549,
        1.85303,
        1.8618,
        1.87933,
        1.89979,
        1.91733,
        1.92902,
        1.95825,
        1.98163,
        2.01378,
        2.03424,
        2.0547,
        2.07808,
        2.09562,
        2.11023,
        2.12484,
        2.13361,
        2.15407,
        2.15699,
        2.15992,
        2.16576,
        2.16868,
        2.16868,
        2.16284,
        2.15699,
        2.14823,
        2.13946,
        2.12484,
        2.11023,
        2.08977,
        2.06639,
        2.04593,
        2.02839,
        2.01086,
        1.98455,
        1.96409,
        1.94948,
        1.93194,
        1.91733,
        1.90271,
        1.87641,
        1.86472,
        1.8501,
        1.83841,
        1.82088,
        1.79749,
        1.77119,
        1.75073,
        1.73027,
        1.70689,
        1.68058,
        1.65428,
        1.6309,
        1.60167,
        1.57244,
        1.55491,
        1.53152,
        1.50522,
        1.47891,
        1.45261,
        1.43215,
        1.40877,
        1.38831,
        1.362,
        1.33862,
        1.31232,
        1.28601,
        1.27432,
        1.25678,
        1.21587,
        1.19541,
        1.17203,
        1.14864,
        1.12234,
        1.10772,
        1.08434,
        1.06096,
        1.0142,
        0.987891,
        0.967432,
        0.938205,
        0.9119,
        0.879749,
        0.853445,
        0.82714,
        0.786221,
        0.765762,
        0.739457,
        0.716075,
        0.681002,
        0.660543,
        0.637161,
        0.60501,
        0.581628,
        0.552401,
        0.531942,
        0.505637,
        0.485177,
        0.458873,
        0.435491,
        0.412109,
        0.379958,
        0.356576,
        0.336117,
        0.309812,
        0.280585,
        0.25428,
        0.207516,
        0.175365,
        0.157829,
        0.13737,
        0.119833,
        0.0993737,
        0.0759916,
        0.0613779,
        0.0526096,
        0.0350731,
        0.0263048,
        0.011691,
        0.00876827,
        0.00876827,
        0.011691,
        0.011691,
        0.011691,
        0.00876827,
        0.011691,
    };



    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };

    const G4int NUMENTRIES_3 = 9;
    G4double ABS_Energy[NUMENTRIES_3]     = { 1.00 * eV , 2.82 * eV , 2.88 * eV , 2.95 * eV , 3.02 * eV  , 3.10 * eV  , 3.18 * eV  , 3.26 * eV , 4.08 * eV };
    G4double ABS_LENGTH[NUMENTRIES_3]     = { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5 * mm  , 11.5 * mm  , 1.0 * mm  , 1.0 * mm  };

//const G4int NUMENTRIES_3 = 3;
//G4double ABS_Energy[NUMENTRIES_3]     = { 1.0*eV, 1.84*eV, 4.08*eV };
//G4double ABS_LENGTH[NUMENTRIES_3]       = { 138000.*mm, 138000.*mm, 138000.*mm };
//G4double ABS_LENGTH[NUMENTRIES_3]       = { 500.*mm, 500.*mm, 500.*mm };


    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};


    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_3);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 40000. / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 3.4);
    mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}
G4Material *MyMaterials::LSO()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71., a = 174.97 * g / mole);
    G4Element *Si = new G4Element ("Silicon",   "Si",  z = 14., a = 28.09 * g / mole);

    G4Material *LSO = new G4Material ("LSO", density = 7.4 * g / cm3, 3);
    LSO->AddElement (Lu, 2);
    LSO->AddElement (Si, 1);
    LSO->AddElement (O, 5);

    const G4int LSO_NUMENTRIES_1 = 193;
    G4double LSO_FAST_Energy[LSO_NUMENTRIES_1] = {
        1.83966 * eV,
        1.84948 * eV,
        1.86274 * eV,
        1.87507 * eV,
        1.88413 * eV,
        1.90369 * eV,
        1.91187 * eV,
        1.92129 * eV,
        1.92962 * eV,
        1.93922 * eV,
        1.95258 * eV,
        1.96365 * eV,
        1.97986 * eV,
        1.99124 * eV,
        2.00533 * eV,
        2.02618 * eV,
        2.04747 * eV,
        2.06101 * eV,
        2.07472 * eV,
        2.09424 * eV,
        2.11269 * eV,
        2.12565 * eV,
        2.14466 * eV,
        2.16251 * eV,
        2.17914 * eV,
        2.19602 * eV,
        2.21317 * eV,
        2.22422 * eV,
        2.24021 * eV,
        2.25479 * eV,
        2.26462 * eV,
        2.27785 * eV,
        2.29462 * eV,
        2.30821 * eV,
        2.32024 * eV,
        2.33588 * eV,
        2.34643 * eV,
        2.35529 * eV,
        2.37322 * eV,
        2.38594 * eV,
        2.3896 * eV,
        2.39879 * eV,
        2.40805 * eV,
        2.41365 * eV,
        2.4268 * eV,
        2.44009 * eV,
        2.45161 * eV,
        2.46518 * eV,
        2.47693 * eV,
        2.48483 * eV,
        2.49477 * eV,
        2.50479 * eV,
        2.51692 * eV,
        2.53123 * eV,
        2.5457 * eV,
        2.54986 * eV,
        2.55613 * eV,
        2.56033 * eV,
        2.56665 * eV,
        2.58796 * eV,
        2.59658 * eV,
        2.60091 * eV,
        2.60309 * eV,
        2.60744 * eV,
        2.614 * eV,
        2.62059 * eV,
        2.62943 * eV,
        2.6361 * eV,
        2.64057 * eV,
        2.64729 * eV,
        2.65632 * eV,
        2.66085 * eV,
        2.6654 * eV,
        2.66997 * eV,
        2.67684 * eV,
        2.67684 * eV,
        2.68839 * eV,
        2.69303 * eV,
        2.70237 * eV,
        2.70471 * eV,
        2.71177 * eV,
        2.72124 * eV,
        2.72362 * eV,
        2.73077 * eV,
        2.73077 * eV,
        2.73317 * eV,
        2.73797 * eV,
        2.74279 * eV,
        2.74762 * eV,
        2.7549 * eV,
        2.7549 * eV,
        2.75978 * eV,
        2.75978 * eV,
        2.76468 * eV,
        2.76713 * eV,
        2.77205 * eV,
        2.77699 * eV,
        2.77699 * eV,
        2.77947 * eV,
        2.78941 * eV,
        2.79692 * eV,
        2.80195 * eV,
        2.80699 * eV,
        2.8146 * eV,
        2.81714 * eV,
        2.8248 * eV,
        2.8325 * eV,
        2.83507 * eV,
        2.85063 * eV,
        2.85847 * eV,
        2.86635 * eV,
        2.86899 * eV,
        2.87428 * eV,
        2.87959 * eV,
        2.88225 * eV,
        2.89027 * eV,
        2.89295 * eV,
        2.89833 * eV,
        2.90103 * eV,
        2.90915 * eV,
        2.91186 * eV,
        2.91731 * eV,
        2.92278 * eV,
        2.92278 * eV,
        2.92553 * eV,
        2.93103 * eV,
        2.93103 * eV,
        2.93103 * eV,
        2.94487 * eV,
        2.94487 * eV,
        2.94766 * eV,
        2.95324 * eV,
        2.95604 * eV,
        2.95885 * eV,
        2.95604 * eV,
        2.96166 * eV,
        2.96447 * eV,
        2.97012 * eV,
        2.96166 * eV,
        2.97295 * eV,
        2.98434 * eV,
        2.98434 * eV,
        2.98148 * eV,
        2.98434 * eV,
        2.99006 * eV,
        2.9872 * eV,
        2.99006 * eV,
        2.9872 * eV,
        2.99006 * eV,
        2.99869 * eV,
        3.00447 * eV,
        3.00737 * eV,
        3.0161 * eV,
        3.01902 * eV,
        3.0161 * eV,
        3.0161 * eV,
        3.01318 * eV,
        3.01318 * eV,
        3.02194 * eV,
        3.02781 * eV,
        3.03666 * eV,
        3.03666 * eV,
        3.03666 * eV,
        3.04556 * eV,
        3.05152 * eV,
        3.05152 * eV,
        3.05451 * eV,
        3.05451 * eV,
        3.05451 * eV,
        3.06051 * eV,
        3.05751 * eV,
        3.07258 * eV,
        3.07258 * eV,
        3.07561 * eV,
        3.08169 * eV,
        3.09085 * eV,
        3.08779 * eV,
        3.09085 * eV,
        3.09699 * eV,
        3.10935 * eV,
        3.10625 * eV,
        3.1218 * eV,
        3.12807 * eV,
        3.13121 * eV,
        3.14067 * eV,
        3.15657 * eV,
        3.16941 * eV,
        3.19213 * eV,
        3.21849 * eV,
        3.24529 * eV,
        3.27255 * eV,
        3.28981 * eV,
    };
    G4double LSO_FAST_COMPONENT[LSO_NUMENTRIES_1] = {
        0.0121475,
        0.0121475,
        0.0151844,
        0.0151844,
        0.0151844,
        0.0182213,
        0.0182213,
        0.0182213,
        0.024295,
        0.024295,
        0.0212581,
        0.0212581,
        0.0303688,
        0.0303688,
        0.0303688,
        0.0425163,
        0.0516269,
        0.0607375,
        0.0698482,
        0.072885,
        0.0850325,
        0.0941432,
        0.106291,
        0.127549,
        0.130586,
        0.142733,
        0.163991,
        0.179176,
        0.19436,
        0.212581,
        0.224729,
        0.239913,
        0.252061,
        0.273319,
        0.297614,
        0.318872,
        0.34013,
        0.355315,
        0.376573,
        0.38872,
        0.413015,
        0.4282,
        0.440347,
        0.458568,
        0.47679,
        0.507158,
        0.531453,
        0.567896,
        0.595228,
        0.628633,
        0.652928,
        0.68026,
        0.71974,
        0.759219,
        0.77744,
        0.813883,
        0.835141,
        0.859436,
        0.886768,
        0.920174,
        0.956616,
        0.990022,
        1.00521,
        1.01735,
        1.04165,
        1.06898,
        1.09328,
        1.11757,
        1.15098,
        1.17223,
        1.2026,
        1.23297,
        1.26334,
        1.29067,
        1.32104,
        1.37874,
        1.40304,
        1.43341,
        1.46074,
        1.49414,
        1.52451,
        1.56095,
        1.60043,
        1.63991,
        1.67028,
        1.69761,
        1.72191,
        1.7462,
        1.77354,
        1.81605,
        1.84946,
        1.88286,
        1.88286,
        1.88894,
        1.9102,
        1.94056,
        1.98308,
        2.00434,
        2.03167,
        2.07419,
        2.10759,
        2.13189,
        2.15315,
        2.16833,
        2.17744,
        2.19566,
        2.20781,
        2.20781,
        2.21996,
        2.21692,
        2.20477,
        2.18959,
        2.16833,
        2.14403,
        2.11367,
        2.08026,
        2.04685,
        2.01649,
        1.98308,
        1.94056,
        1.90716,
        1.87679,
        1.84642,
        1.80998,
        1.77354,
        1.73406,
        1.70369,
        1.66421,
        1.60651,
        1.53362,
        1.5154,
        1.49111,
        1.46985,
        1.44252,
        1.4243,
        1.39696,
        1.36356,
        1.318,
        1.26941,
        1.21171,
        1.16616,
        1.13275,
        1.09935,
        1.12972,
        1.11453,
        1.08416,
        1.05683,
        1.02343,
        0.993059,
        0.956616,
        0.929284,
        0.895879,
        0.87462,
        0.835141,
        0.801735,
        0.77744,
        0.747072,
        0.704555,
        0.67115,
        0.640781,
        0.595228,
        0.570933,
        0.540564,
        0.510195,
        0.473753,
        0.443384,
        0.419089,
        0.394794,
        0.373536,
        0.34013,
        0.318872,
        0.276356,
        0.252061,
        0.203471,
        0.185249,
        0.163991,
        0.142733,
        0.127549,
        0.112364,
        0.0911063,
        0.072885,
        0.0577007,
        0.0425163,
        0.0303688,
        0.024295,
        0.00911063,
        0.00607375,
        0.00607375,
        0.00303688,
        0.00303688,
        0.00911063,
        0.00911063,
    };


    const G4int LSO_NUMENTRIES_2 = 4;
    G4double LSO_RIND_Energy[LSO_NUMENTRIES_2]      = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double LSO_RIND_INDEX[LSO_NUMENTRIES_2]       = { 1.82, 1.82, 1.82, 1.82 };
    G4double LSO_ABS_Energy[LSO_NUMENTRIES_2]       = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    //G4double LSO_ABS_LENGTH[LSO_NUMENTRIES_2]     = { 50.*m, 50.*m, 50.*m};
    G4double LSO_ABS_LENGTH[LSO_NUMENTRIES_2]       = { 1 * mm, 138.*mm, 138.*mm, 138.*mm };
    //G4double LSO_Rayleigh[LSO_NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};

    G4MaterialPropertiesTable *LSO_mt = new G4MaterialPropertiesTable();
    LSO_mt->AddProperty ("FASTCOMPONENT", LSO_FAST_Energy, LSO_FAST_COMPONENT, LSO_NUMENTRIES_1);
    LSO_mt->AddProperty ("RINDEX",        LSO_RIND_Energy, LSO_RIND_INDEX,     LSO_NUMENTRIES_2);
    LSO_mt->AddProperty ("ABSLENGTH",     LSO_ABS_Energy,  LSO_ABS_LENGTH,     LSO_NUMENTRIES_2);
    //LSO_mt->AddProperty("RAYLEIGH",      LSO_ABS_Energy,  LSO_Rayleigh,     LSO_NUMENTRIES_2);
    LSO_mt->AddConstProperty ("SCINTILLATIONYIELD", 60000. / MeV);
    LSO_mt->AddConstProperty ("RESOLUTIONSCALE", 3.2);
    LSO_mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    LSO_mt->AddConstProperty ("YIELDRATIO", 1.0);
    LSO_mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);

    const G4int LSO_SCY_NUMENTRIES = 12;
    G4double LSO_SCY_Energy[LSO_SCY_NUMENTRIES] = { 0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV, 0.040 * MeV, 0.060 * MeV,
            0.080 * MeV, 0.090 * MeV, 0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV
                                                  };
    G4double LSO_SCY[LSO_SCY_NUMENTRIES]        = { 0.10, 0.46, 0.60, 0.68, 0.74, 0.80, 0.82,
            0.84, 0.87,  0.96,  0.98,  1.00
                                                  };
    for (int i = 0; i < LSO_SCY_NUMENTRIES; i++) {
        LSO_SCY[i] = 60000.0 * MeV * LSO_SCY[i] * LSO_SCY_Energy[i];
    }
    LSO_mt->AddProperty ("ELECTRONSCINTILLATIONYIELD", LSO_SCY_Energy, LSO_SCY, LSO_SCY_NUMENTRIES);




    LSO->SetMaterialPropertiesTable (LSO_mt);


    return LSO;
}


G4Material *MyMaterials::lowLYLYSO()
{
    G4double a, z, density;
    G4Element  *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Lu = new G4Element ("Lutetium",  "Lu",  z = 71., a = 174.97 * g / mole);
    G4Element *Si = new G4Element ("Silicon",   "Si",  z = 14., a = 28.09 * g / mole);

    G4Material *mat = new G4Material ("LYSO", density = 7.1 * g / cm3, 3, kStateSolid);
    mat->AddElement (Lu, 2);
    mat->AddElement (Si, 1);
    mat->AddElement (O, 5);

    const G4int NUMENTRIES_1 = 261;
    G4double FAST_Energy[NUMENTRIES_1] = {
        1.77169 * eV,
        1.77266 * eV,
        1.77558 * eV,
        1.77851 * eV,
        1.78145 * eV,
        1.78539 * eV,
        1.79033 * eV,
        1.7963 * eV,
        1.80231 * eV,
        1.80836 * eV,
        1.81445 * eV,
        1.82058 * eV,
        1.82882 * eV,
        1.83401 * eV,
        1.84553 * eV,
        1.85293 * eV,
        1.86147 * eV,
        1.869 * eV,
        1.87769 * eV,
        1.89308 * eV,
        1.90536 * eV,
        1.92007 * eV,
        1.93039 * eV,
        1.94901 * eV,
        1.95846 * eV,
        1.9668 * eV,
        1.97884 * eV,
        1.99102 * eV,
        2.00088 * eV,
        2.01209 * eV,
        2.02596 * eV,
        2.03617 * eV,
        2.04519 * eV,
        2.0569 * eV,
        2.06611 * eV,
        2.0794 * eV,
        2.09151 * eV,
        2.10239 * eV,
        2.112 * eV,
        2.1231 * eV,
        2.13431 * eV,
        2.14565 * eV,
        2.15566 * eV,
        2.16868 * eV,
        2.18038 * eV,
        2.19519 * eV,
        2.21171 * eV,
        2.2193 * eV,
        2.23619 * eV,
        2.23464 * eV,
        2.24395 * eV,
        2.25806 * eV,
        2.27234 * eV,
        2.28358 * eV,
        2.29493 * eV,
        2.30475 * eV,
        2.31631 * eV,
        2.32463 * eV,
        2.33134 * eV,
        2.33809 * eV,
        2.34487 * eV,
        2.35856 * eV,
        2.36719 * eV,
        2.37939 * eV,
        2.38642 * eV,
        2.40238 * eV,
        2.41134 * eV,
        2.424 * eV,
        2.43312 * eV,
        2.44047 * eV,
        2.44786 * eV,
        2.46278 * eV,
        2.47788 * eV,
        2.48741 * eV,
        2.49317 * eV,
        2.49702 * eV,
        2.50282 * eV,
        2.50865 * eV,
        2.5145 * eV,
        2.52038 * eV,
        2.52432 * eV,
        2.53223 * eV,
        2.5362 * eV,
        2.54619 * eV,
        2.55424 * eV,
        2.56031 * eV,
        2.56437 * eV,
        2.57049 * eV,
        2.57663 * eV,
        2.58487 * eV,
        2.59317 * eV,
        2.59734 * eV,
        2.60571 * eV,
        2.61414 * eV,
        2.61414 * eV,
        2.61837 * eV,
        2.62262 * eV,
        2.62475 * eV,
        2.62902 * eV,
        2.63331 * eV,
        2.63545 * eV,
        2.63976 * eV,
        2.64191 * eV,
        2.64841 * eV,
        2.65493 * eV,
        2.6593 * eV,
        2.66149 * eV,
        2.66588 * eV,
        2.67914 * eV,
        2.67914 * eV,
        2.68136 * eV,
        2.68136 * eV,
        2.68359 * eV,
        2.68805 * eV,
        2.68805 * eV,
        2.68805 * eV,
        2.69477 * eV,
        2.69477 * eV,
        2.69702 * eV,
        2.70153 * eV,
        2.70605 * eV,
        2.71286 * eV,
        2.71742 * eV,
        2.71971 * eV,
        2.722 * eV,
        2.722 * eV,
        2.72429 * eV,
        2.72889 * eV,
        2.72889 * eV,
        2.73351 * eV,
        2.73814 * eV,
        2.74279 * eV,
        2.74512 * eV,
        2.74979 * eV,
        2.75213 * eV,
        2.75447 * eV,
        2.75917 * eV,
        2.75682 * eV,
        2.76389 * eV,
        2.76626 * eV,
        2.76389 * eV,
        2.76626 * eV,
        2.77338 * eV,
        2.77576 * eV,
        2.78533 * eV,
        2.79255 * eV,
        2.79738 * eV,
        2.80223 * eV,
        2.80466 * eV,
        2.80709 * eV,
        2.80953 * eV,
        2.80953 * eV,
        2.81934 * eV,
        2.8218 * eV,
        2.82673 * eV,
        2.83168 * eV,
        2.84164 * eV,
        2.84916 * eV,
        2.85419 * eV,
        2.8643 * eV,
        2.86684 * eV,
        2.87449 * eV,
        2.87705 * eV,
        2.87961 * eV,
        2.88475 * eV,
        2.88733 * eV,
        2.8925 * eV,
        2.89509 * eV,
        2.90028 * eV,
        2.90549 * eV,
        2.90811 * eV,
        2.91073 * eV,
        2.91335 * eV,
        2.91335 * eV,
        2.91335 * eV,
        2.91861 * eV,
        2.92125 * eV,
        2.92125 * eV,
        2.92389 * eV,
        2.92654 * eV,
        2.92654 * eV,
        2.92919 * eV,
        2.92919 * eV,
        2.93185 * eV,
        2.93451 * eV,
        2.93717 * eV,
        2.93985 * eV,
        2.94252 * eV,
        2.9452 * eV,
        2.94789 * eV,
        2.94789 * eV,
        2.94789 * eV,
        2.95058 * eV,
        2.95868 * eV,
        2.96411 * eV,
        2.96955 * eV,
        2.97228 * eV,
        2.97228 * eV,
        2.96955 * eV,
        2.97228 * eV,
        2.97502 * eV,
        2.97776 * eV,
        2.97502 * eV,
        2.9805 * eV,
        2.9805 * eV,
        2.9805 * eV,
        2.98601 * eV,
        2.99154 * eV,
        2.99431 * eV,
        2.99431 * eV,
        2.99708 * eV,
        2.99431 * eV,
        2.99708 * eV,
        3.00544 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.00824 * eV,
        3.01385 * eV,
        3.0223 * eV,
        3.02797 * eV,
        3.03081 * eV,
        3.02797 * eV,
        3.03365 * eV,
        3.03081 * eV,
        3.03081 * eV,
        3.0365 * eV,
        3.03935 * eV,
        3.04221 * eV,
        3.04795 * eV,
        3.04795 * eV,
        3.05083 * eV,
        3.05371 * eV,
        3.05949 * eV,
        3.06239 * eV,
        3.06529 * eV,
        3.0682 * eV,
        3.06529 * eV,
        3.07112 * eV,
        3.0682 * eV,
        3.07696 * eV,
        3.08283 * eV,
        3.0976 * eV,
        3.09464 * eV,
        3.09464 * eV,
        3.10653 * eV,
        3.11252 * eV,
        3.11852 * eV,
        3.12757 * eV,
        3.13668 * eV,
        3.14583 * eV,
        3.15813 * eV,
        3.16741 * eV,
        3.17675 * eV,
        3.20828 * eV,
        3.23719 * eV,
        3.26664 * eV,
        3.28656 * eV,
        3.31351 * eV,
        3.34783 * eV,
        3.38287 * eV,
    };
    G4double FAST_COMPONENT[NUMENTRIES_1] = {
        0.011691,
        0.011691,
        0.011691,
        0.0146138,
        0.0146138,
        0.0146138,
        0.011691,
        0.011691,
        0.00876827,
        0.00876827,
        0.00584551,
        0.00584551,
        0.00584551,
        0.00292276,
        0.00876827,
        0.0146138,
        0.0146138,
        0.0146138,
        0.0204593,
        0.023382,
        0.0263048,
        0.0204593,
        0.0204593,
        0.023382,
        0.0292276,
        0.0321503,
        0.0350731,
        0.0379958,
        0.0379958,
        0.0379958,
        0.0350731,
        0.0379958,
        0.0409186,
        0.0438413,
        0.0526096,
        0.0584551,
        0.0643006,
        0.0730689,
        0.0730689,
        0.0818372,
        0.0906054,
        0.0964509,
        0.0993737,
        0.105219,
        0.111065,
        0.122756,
        0.125678,
        0.146138,
        0.146138,
        0.160752,
        0.157829,
        0.163674,
        0.184134,
        0.192902,
        0.20167,
        0.219207,
        0.230898,
        0.242589,
        0.25428,
        0.265971,
        0.274739,
        0.292276,
        0.306889,
        0.315658,
        0.321503,
        0.350731,
        0.368267,
        0.385804,
        0.397495,
        0.415031,
        0.432568,
        0.458873,
        0.482255,
        0.496868,
        0.514405,
        0.529019,
        0.549478,
        0.564092,
        0.581628,
        0.593319,
        0.602088,
        0.616701,
        0.637161,
        0.660543,
        0.681002,
        0.71023,
        0.736534,
        0.756994,
        0.777453,
        0.806681,
        0.844676,
        0.868058,
        0.891441,
        0.9119,
        0.938205,
        0.955741,
        0.984969,
        1.0142,
        1.03173,
        1.05511,
        1.07557,
        1.11649,
        1.13695,
        1.15741,
        1.17495,
        1.19248,
        1.21002,
        1.22756,
        1.27432,
        1.2977,
        1.31524,
        1.32985,
        1.36785,
        1.40292,
        1.39415,
        1.4,
        1.41754,
        1.44092,
        1.47015,
        1.48476,
        1.50814,
        1.5286,
        1.54906,
        1.56952,
        1.58998,
        1.61921,
        1.63967,
        1.66597,
        1.68935,
        1.71566,
        1.73904,
        1.76242,
        1.77996,
        1.80042,
        1.8238,
        1.83549,
        1.85303,
        1.8618,
        1.87933,
        1.89979,
        1.91733,
        1.92902,
        1.95825,
        1.98163,
        2.01378,
        2.03424,
        2.0547,
        2.07808,
        2.09562,
        2.11023,
        2.12484,
        2.13361,
        2.15407,
        2.15699,
        2.15992,
        2.16576,
        2.16868,
        2.16868,
        2.16284,
        2.15699,
        2.14823,
        2.13946,
        2.12484,
        2.11023,
        2.08977,
        2.06639,
        2.04593,
        2.02839,
        2.01086,
        1.98455,
        1.96409,
        1.94948,
        1.93194,
        1.91733,
        1.90271,
        1.87641,
        1.86472,
        1.8501,
        1.83841,
        1.82088,
        1.79749,
        1.77119,
        1.75073,
        1.73027,
        1.70689,
        1.68058,
        1.65428,
        1.6309,
        1.60167,
        1.57244,
        1.55491,
        1.53152,
        1.50522,
        1.47891,
        1.45261,
        1.43215,
        1.40877,
        1.38831,
        1.362,
        1.33862,
        1.31232,
        1.28601,
        1.27432,
        1.25678,
        1.21587,
        1.19541,
        1.17203,
        1.14864,
        1.12234,
        1.10772,
        1.08434,
        1.06096,
        1.0142,
        0.987891,
        0.967432,
        0.938205,
        0.9119,
        0.879749,
        0.853445,
        0.82714,
        0.786221,
        0.765762,
        0.739457,
        0.716075,
        0.681002,
        0.660543,
        0.637161,
        0.60501,
        0.581628,
        0.552401,
        0.531942,
        0.505637,
        0.485177,
        0.458873,
        0.435491,
        0.412109,
        0.379958,
        0.356576,
        0.336117,
        0.309812,
        0.280585,
        0.25428,
        0.207516,
        0.175365,
        0.157829,
        0.13737,
        0.119833,
        0.0993737,
        0.0759916,
        0.0613779,
        0.0526096,
        0.0350731,
        0.0263048,
        0.011691,
        0.00876827,
        0.00876827,
        0.011691,
        0.011691,
        0.011691,
        0.00876827,
        0.011691,
    };



    const G4int NUMENTRIES_2 = 3;
    G4double RIND_Energy[NUMENTRIES_2]    = { 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double RIND_INDEX[NUMENTRIES_2]     = { 1.82, 1.82, 1.82 };

    const G4int NUMENTRIES_3 = 9;
    G4double ABS_Energy[NUMENTRIES_3]     = { 1.00 * eV , 2.82 * eV , 2.88 * eV , 2.95 * eV , 3.02 * eV  , 3.10 * eV  , 3.18 * eV  , 3.26 * eV , 4.08 * eV };
    G4double ABS_LENGTH[NUMENTRIES_3]     = { 438.*mm , 438.*mm , 413.*mm , 375.*mm , 263.*mm  , 87.5 * mm  , 11.5 * mm  , 1.0 * mm  , 1.0 * mm  };

//const G4int NUMENTRIES_3 = 3;
//G4double ABS_Energy[NUMENTRIES_3]     = { 1.0*eV, 1.84*eV, 4.08*eV };
//G4double ABS_LENGTH[NUMENTRIES_3]       = { 138000.*mm, 138000.*mm, 138000.*mm };
//G4double ABS_LENGTH[NUMENTRIES_3]       = { 500.*mm, 500.*mm, 500.*mm };


    //G4double Rayleigh[NUMENTRIES_2]       = { 138.*mm, 138.*mm, 138.*mm};


    G4MaterialPropertiesTable *mt = new G4MaterialPropertiesTable();
    mt->AddProperty ("FASTCOMPONENT", FAST_Energy, FAST_COMPONENT, NUMENTRIES_1);
    mt->AddProperty ("RINDEX",        RIND_Energy, RIND_INDEX,     NUMENTRIES_2);
    mt->AddProperty ("ABSLENGTH",     ABS_Energy,  ABS_LENGTH,     NUMENTRIES_3);
    //mt->AddProperty("RAYLEIGH",      ABS_Energy,  Rayleigh,     NUMENTRIES_2);
    mt->AddConstProperty ("SCINTILLATIONYIELD", 10. / MeV);
    mt->AddConstProperty ("RESOLUTIONSCALE", 3.4);
    mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    mt->AddConstProperty ("YIELDRATIO", 1.0);
    mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);
    mat->SetMaterialPropertiesTable (mt);


    return mat;
}



/*============PbWO===================*/
G4Material *MyMaterials::PbWO()
{
    G4double a, z, density;
    G4Element *O = new G4Element ("Oxygen",    "O",   z = 8.,  a = 16.00 * g / mole);
    G4Element *Pb = new G4Element ("Lead",     "Pb",  z = 82., a = 207.21 * g / mole);
    G4Element *W = new G4Element ("Tungsten",  "W",   z = 74., a = 183.85 * g / mole);

    G4Material *PbWO = new G4Material ("PbWO", density = 8.28 * g / cm3, 3);
    PbWO->AddElement (Pb, 1);
    PbWO->AddElement (W, 1);
    PbWO->AddElement (O, 4);

    const G4int PbWO_NUMENTRIES_1 = 193;
    G4double PbWO_FAST_Energy[PbWO_NUMENTRIES_1] = {
        1.83966 * eV,
        1.84948 * eV,
        1.86274 * eV,
        1.87507 * eV,
        1.88413 * eV,
        1.90369 * eV,
        1.91187 * eV,
        1.92129 * eV,
        1.92962 * eV,
        1.93922 * eV,
        1.95258 * eV,
        1.96365 * eV,
        1.97986 * eV,
        1.99124 * eV,
        2.00533 * eV,
        2.02618 * eV,
        2.04747 * eV,
        2.06101 * eV,
        2.07472 * eV,
        2.09424 * eV,
        2.11269 * eV,
        2.12565 * eV,
        2.14466 * eV,
        2.16251 * eV,
        2.17914 * eV,
        2.19602 * eV,
        2.21317 * eV,
        2.22422 * eV,
        2.24021 * eV,
        2.25479 * eV,
        2.26462 * eV,
        2.27785 * eV,
        2.29462 * eV,
        2.30821 * eV,
        2.32024 * eV,
        2.33588 * eV,
        2.34643 * eV,
        2.35529 * eV,
        2.37322 * eV,
        2.38594 * eV,
        2.3896 * eV,
        2.39879 * eV,
        2.40805 * eV,
        2.41365 * eV,
        2.4268 * eV,
        2.44009 * eV,
        2.45161 * eV,
        2.46518 * eV,
        2.47693 * eV,
        2.48483 * eV,
        2.49477 * eV,
        2.50479 * eV,
        2.51692 * eV,
        2.53123 * eV,
        2.5457 * eV,
        2.54986 * eV,
        2.55613 * eV,
        2.56033 * eV,
        2.56665 * eV,
        2.58796 * eV,
        2.59658 * eV,
        2.60091 * eV,
        2.60309 * eV,
        2.60744 * eV,
        2.614 * eV,
        2.62059 * eV,
        2.62943 * eV,
        2.6361 * eV,
        2.64057 * eV,
        2.64729 * eV,
        2.65632 * eV,
        2.66085 * eV,
        2.6654 * eV,
        2.66997 * eV,
        2.67684 * eV,
        2.67684 * eV,
        2.68839 * eV,
        2.69303 * eV,
        2.70237 * eV,
        2.70471 * eV,
        2.71177 * eV,
        2.72124 * eV,
        2.72362 * eV,
        2.73077 * eV,
        2.73077 * eV,
        2.73317 * eV,
        2.73797 * eV,
        2.74279 * eV,
        2.74762 * eV,
        2.7549 * eV,
        2.7549 * eV,
        2.75978 * eV,
        2.75978 * eV,
        2.76468 * eV,
        2.76713 * eV,
        2.77205 * eV,
        2.77699 * eV,
        2.77699 * eV,
        2.77947 * eV,
        2.78941 * eV,
        2.79692 * eV,
        2.80195 * eV,
        2.80699 * eV,
        2.8146 * eV,
        2.81714 * eV,
        2.8248 * eV,
        2.8325 * eV,
        2.83507 * eV,
        2.85063 * eV,
        2.85847 * eV,
        2.86635 * eV,
        2.86899 * eV,
        2.87428 * eV,
        2.87959 * eV,
        2.88225 * eV,
        2.89027 * eV,
        2.89295 * eV,
        2.89833 * eV,
        2.90103 * eV,
        2.90915 * eV,
        2.91186 * eV,
        2.91731 * eV,
        2.92278 * eV,
        2.92278 * eV,
        2.92553 * eV,
        2.93103 * eV,
        2.93103 * eV,
        2.93103 * eV,
        2.94487 * eV,
        2.94487 * eV,
        2.94766 * eV,
        2.95324 * eV,
        2.95604 * eV,
        2.95885 * eV,
        2.95604 * eV,
        2.96166 * eV,
        2.96447 * eV,
        2.97012 * eV,
        2.96166 * eV,
        2.97295 * eV,
        2.98434 * eV,
        2.98434 * eV,
        2.98148 * eV,
        2.98434 * eV,
        2.99006 * eV,
        2.9872 * eV,
        2.99006 * eV,
        2.9872 * eV,
        2.99006 * eV,
        2.99869 * eV,
        3.00447 * eV,
        3.00737 * eV,
        3.0161 * eV,
        3.01902 * eV,
        3.0161 * eV,
        3.0161 * eV,
        3.01318 * eV,
        3.01318 * eV,
        3.02194 * eV,
        3.02781 * eV,
        3.03666 * eV,
        3.03666 * eV,
        3.03666 * eV,
        3.04556 * eV,
        3.05152 * eV,
        3.05152 * eV,
        3.05451 * eV,
        3.05451 * eV,
        3.05451 * eV,
        3.06051 * eV,
        3.05751 * eV,
        3.07258 * eV,
        3.07258 * eV,
        3.07561 * eV,
        3.08169 * eV,
        3.09085 * eV,
        3.08779 * eV,
        3.09085 * eV,
        3.09699 * eV,
        3.10935 * eV,
        3.10625 * eV,
        3.1218 * eV,
        3.12807 * eV,
        3.13121 * eV,
        3.14067 * eV,
        3.15657 * eV,
        3.16941 * eV,
        3.19213 * eV,
        3.21849 * eV,
        3.24529 * eV,
        3.27255 * eV,
        3.28981 * eV,
    };
    G4double PbWO_FAST_COMPONENT[PbWO_NUMENTRIES_1] = {
        0.0121475,
        0.0121475,
        0.0151844,
        0.0151844,
        0.0151844,
        0.0182213,
        0.0182213,
        0.0182213,
        0.024295,
        0.024295,
        0.0212581,
        0.0212581,
        0.0303688,
        0.0303688,
        0.0303688,
        0.0425163,
        0.0516269,
        0.0607375,
        0.0698482,
        0.072885,
        0.0850325,
        0.0941432,
        0.106291,
        0.127549,
        0.130586,
        0.142733,
        0.163991,
        0.179176,
        0.19436,
        0.212581,
        0.224729,
        0.239913,
        0.252061,
        0.273319,
        0.297614,
        0.318872,
        0.34013,
        0.355315,
        0.376573,
        0.38872,
        0.413015,
        0.4282,
        0.440347,
        0.458568,
        0.47679,
        0.507158,
        0.531453,
        0.567896,
        0.595228,
        0.628633,
        0.652928,
        0.68026,
        0.71974,
        0.759219,
        0.77744,
        0.813883,
        0.835141,
        0.859436,
        0.886768,
        0.920174,
        0.956616,
        0.990022,
        1.00521,
        1.01735,
        1.04165,
        1.06898,
        1.09328,
        1.11757,
        1.15098,
        1.17223,
        1.2026,
        1.23297,
        1.26334,
        1.29067,
        1.32104,
        1.37874,
        1.40304,
        1.43341,
        1.46074,
        1.49414,
        1.52451,
        1.56095,
        1.60043,
        1.63991,
        1.67028,
        1.69761,
        1.72191,
        1.7462,
        1.77354,
        1.81605,
        1.84946,
        1.88286,
        1.88286,
        1.88894,
        1.9102,
        1.94056,
        1.98308,
        2.00434,
        2.03167,
        2.07419,
        2.10759,
        2.13189,
        2.15315,
        2.16833,
        2.17744,
        2.19566,
        2.20781,
        2.20781,
        2.21996,
        2.21692,
        2.20477,
        2.18959,
        2.16833,
        2.14403,
        2.11367,
        2.08026,
        2.04685,
        2.01649,
        1.98308,
        1.94056,
        1.90716,
        1.87679,
        1.84642,
        1.80998,
        1.77354,
        1.73406,
        1.70369,
        1.66421,
        1.60651,
        1.53362,
        1.5154,
        1.49111,
        1.46985,
        1.44252,
        1.4243,
        1.39696,
        1.36356,
        1.318,
        1.26941,
        1.21171,
        1.16616,
        1.13275,
        1.09935,
        1.12972,
        1.11453,
        1.08416,
        1.05683,
        1.02343,
        0.993059,
        0.956616,
        0.929284,
        0.895879,
        0.87462,
        0.835141,
        0.801735,
        0.77744,
        0.747072,
        0.704555,
        0.67115,
        0.640781,
        0.595228,
        0.570933,
        0.540564,
        0.510195,
        0.473753,
        0.443384,
        0.419089,
        0.394794,
        0.373536,
        0.34013,
        0.318872,
        0.276356,
        0.252061,
        0.203471,
        0.185249,
        0.163991,
        0.142733,
        0.127549,
        0.112364,
        0.0911063,
        0.072885,
        0.0577007,
        0.0425163,
        0.0303688,
        0.024295,
        0.00911063,
        0.00607375,
        0.00607375,
        0.00303688,
        0.00303688,
        0.00911063,
        0.00911063,
    };

    G4double PbWO_indexZero     = 1.5861;
    G4double PbWO_nVec[1]       = { 1.1062 };
    G4double PbWO_lVec[1]       = { 270.63 };

    const G4int PbWO_NUMENTRIES_2 = 4;
    G4double PbWO_RIND_Energy[PbWO_NUMENTRIES_2]      = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double PbWO_RIND_INDEX[PbWO_NUMENTRIES_2]       = { 2.325, 2.325, 2.325, 2.325};
    /*G4double PbWO_RIND_INDEX[PbWO_NUMENTRIES_2]       = {
    CalculateSellmeier(PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(0.0001)),
    CalculateSellmeier(PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(1.0)),
    CalculateSellmeier(PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(1.84)),
    CalculateSellmeier(PbWO_indexZero,PbWO_nVec,PbWO_lVec,fromEvToNm(4.08)),
    };*/
/*
    const G4int PbWO_ABS_entries = 70;
    G4double PbWO_ABS_Energy[PbWO_ABS_entries]       = {
        1.25237 * eV, 1.26514 * eV, 1.27819 * eV, 1.2915 * eV, 1.3051 * eV, 1.31898 * eV, 1.33316 * eV, 1.34765 * eV, 1.36246 * eV, 1.3776 * eV,
        1.39308 * eV, 1.40891 * eV, 1.42511 * eV, 1.44168 * eV, 1.45864 * eV, 1.476 * eV, 1.49379 * eV, 1.512 * eV, 1.53067 * eV, 1.5498 * eV,
        1.56942 * eV, 1.58954 * eV, 1.61018 * eV, 1.63137 * eV, 1.65312 * eV, 1.67546 * eV, 1.69841 * eV, 1.722 * eV, 1.74626 * eV, 1.7712 * eV,
        1.79687 * eV, 1.8233 * eV, 1.85051 * eV, 1.87855 * eV, 1.90745 * eV, 1.93725 * eV, 1.968 * eV, 1.99974 * eV, 2.03253 * eV, 2.0664 * eV,
        2.10143 * eV, 2.13766 * eV, 2.17516 * eV, 2.214 * eV, 2.25426 * eV, 2.296 * eV, 2.33932 * eV, 2.38431 * eV, 2.43106 * eV, 2.47968 * eV,
        2.53029 * eV, 2.583 * eV, 2.63796 * eV, 2.69531 * eV, 2.7552 * eV, 2.81782 * eV, 2.88335 * eV, 2.952 * eV, 3.024 * eV, 3.0996 * eV,
        3.17908 * eV, 3.26274 * eV, 3.35092 * eV, 3.44401 * eV, 3.54241 * eV, 3.64659 * eV, 3.7571 * eV, 3.87451 * eV, 3.99949 * eV, 4.13281 * eV,


    };

    G4double PbWO_ABS_LENGTH[PbWO_ABS_entries] = {
        3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3110 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm, 3105 * mm,
        3105 * mm, 2745 * mm, 2460 * mm, 2230 * mm, 2039 * mm, 1877 * mm, 1859 * mm, 1826 * mm, 1764 * mm, 1760 * mm,
        1664 * mm, 1585 * mm, 1471 * mm, 1376 * mm, 1272 * mm, 1187 * mm, 1114 * mm, 1046 * mm, 993.2 * mm, 942.9 * mm,
        898.8 * mm, 856.9 * mm, 821.7 * mm, 794.2 * mm, 767.7 * mm, 746.5 * mm, 725.6 * mm, 710.7 * mm, 695.3 * mm, 686.2 * mm,
        674.8 * mm, 663.5 * mm, 648.3 * mm, 633.4 * mm, 622.3 * mm, 607.8 * mm, 590.9 * mm, 568.9 * mm, 541.4 * mm, 502.9 * mm,
        467 * mm, 430.2 * mm, 390.1 * mm, 345.3 * mm, 298.9 * mm, 256.7 * mm, 219.8 * mm, 185.4 * mm, 150.9 * mm, 116.4 * mm,
        84.8 * mm, 59.4 * mm, 41.1 * mm, 27.5 * mm, 24.2 * mm, 24.2 * mm, 24.3 * mm, 24.3 * mm, 24.4 * mm, 24.6 * mm
    };
    */


    const G4int PbWO_ABS_entries = 4;
    G4double PbWO_ABS_Energy[PbWO_ABS_entries]       = { 0.0001 * eV, 1.0 * eV, 1.84 * eV, 4.08 * eV };
    G4double PbWO_ABS_LENGTH[PbWO_ABS_entries] 	= { 185.4 * mm, 185.4 * mm, 185.4 * mm, 185.4 * mm};

    G4MaterialPropertiesTable *PbWO_mt = new G4MaterialPropertiesTable();
    PbWO_mt->AddProperty ("FASTCOMPONENT", PbWO_FAST_Energy, PbWO_FAST_COMPONENT, PbWO_NUMENTRIES_1);
    PbWO_mt->AddProperty ("RINDEX",        PbWO_RIND_Energy, PbWO_RIND_INDEX,     PbWO_NUMENTRIES_2);
    PbWO_mt->AddProperty ("ABSLENGTH",      PbWO_ABS_Energy,  PbWO_ABS_LENGTH,  PbWO_ABS_entries);

    PbWO_mt->AddConstProperty ("SCINTILLATIONYIELD", 60000. / MeV);
    PbWO_mt->AddConstProperty ("RESOLUTIONSCALE", 3.2);
    PbWO_mt->AddConstProperty ("FASTTIMECONSTANT", 40.*ns);
    PbWO_mt->AddConstProperty ("YIELDRATIO", 1.0);
    PbWO_mt->AddConstProperty ("FASTSCINTILLATIONRISETIME", 0.1 * ns);

    const G4int PbWO_SCY_NUMENTRIES = 12;
    G4double PbWO_SCY_Energy[PbWO_SCY_NUMENTRIES] = { 0.000 * MeV, 0.015 * MeV, 0.020 * MeV, 0.030 * MeV, 0.040 * MeV, 0.060 * MeV,
            0.080 * MeV, 0.090 * MeV, 0.105 * MeV, 0.300 * MeV, 0.500 * MeV, 1.000 * MeV
                                                    };
    G4double PbWO_SCY[PbWO_SCY_NUMENTRIES]        = { 0.10, 0.46, 0.60, 0.68, 0.74, 0.80, 0.82,
            0.84, 0.87,  0.96,  0.98,  1.00
                                                    };
    for (int i = 0; i < PbWO_SCY_NUMENTRIES; i++) {
        PbWO_SCY[i] = 60000.0 * MeV * PbWO_SCY[i] * PbWO_SCY_Energy[i];
    }
    PbWO_mt->AddProperty ("ELECTRONSCINTILLATIONYIELD", PbWO_SCY_Energy, PbWO_SCY, PbWO_SCY_NUMENTRIES);

    PbWO->SetMaterialPropertiesTable (PbWO_mt);

    return PbWO;
}

G4double MyMaterials::CalculateSellmeier (G4double indexZero, G4double *nVec, G4double *lVec, G4double wavelength)
{

    /*------http://gentitfx.fr/SLitrani/code/SLitraniCode/TLitSellmeier.html----*/

    int nVecSize = sizeof (nVec) / sizeof (G4double);
    int lVecSize = sizeof (lVec) / sizeof (G4double);

    if (nVecSize != lVecSize) {
        G4cout << G4endl << "========== ERROR ============" << G4endl;
        G4cout << "nVec and lVec have different size... check!" << G4endl;
        G4cout << "========== ERROR ============" << G4endl << G4endl;
        return 0;
    }

    float partial = indexZero * indexZero;
    float sum = 0;
    for (int i = 0; i < nVecSize; i++) {

        sum += nVec[i] * nVec[i] / (1 - lVec[i] * lVec[i] / wavelength);

    }

    partial += sum;
    partial += 1;

    G4cout << "Wavelength: " << wavelength << " -> rifr. index: " << sqrt (partial) << G4endl;

    return sqrt (partial);
}

G4double MyMaterials::fromEvToNm (G4double energy)
{

    return 1239.84187 / energy;

}

G4double MyMaterials::fromNmToEv (G4double wavelength)
{


    return 1239.84187 / wavelength;

}

