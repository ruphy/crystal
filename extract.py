# Aggiungi qui, separandole da virgole, le classi di ROOT
# che usi:
from os import popen
from ROOT import TCanvas, TH1F, TChain
from ROOT import gInterpreter, gSystem, gROOT
import numpy as np

gSystem.AddLinkedLibs(popen('root-config --libs').read())
gInterpreter.GenerateDictionary("vector<ROOT::Math::Cartesian3D<double> >", "Math/Cartesian3D.h")

# ---------------------- #
# Inizio codice serio    #
# ---------------------- #

c1 = TChain('tree')
c1.Add('out.root')

a = [x.MomentumOut for x in c1]
print a[1].size()
a = filter(lambda x: x.size() > 0, a)

print len(a)
for item in a:
    print item.z()

for event in c1:
    if (event.MomentumOut.size()):
        print acos(event.MomentumOut[0].z())

