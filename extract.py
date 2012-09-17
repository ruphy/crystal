# Aggiungi qui, separandole da virgole, le classi di ROOT
# che usi:
from os import popen
from ROOT import TCanvas, TH1F, TFile, TF1
from ROOT import gInterpreter, gSystem, gROOT, gDirectory
import numpy as np
import matplotlib.pyplot as plt
from scipy import odr


gSystem.AddLinkedLibs(popen('root-config --libs').read())
gInterpreter.GenerateDictionary("vector<ROOT::Math::Cartesian3D<double> >", "Math/Cartesian3D.h")

# ---------------------- #
# Inizio codice serio    #
# ---------------------- #

# open the file
myfile = TFile( 'out.root' )

# retrieve the ntuple of interest
mychain = gDirectory.Get( 'tree' )
entries = mychain.GetEntriesFast()

data = []

for jentry in xrange( entries ):
    nb = mychain.GetEntry( jentry )
    data.append(mychain.AbsLength)

def funz(P, x):
    return 10000*np.exp(-x/P[0])

plt.clf()
plt.grid(True)

(n, bins, patches) = plt.hist(data, 100, color='#50e300', alpha=.7)
bins = 0.5*(bins[:-1] + bins[1:])

(param, errors, cov) = odr.odr(funz, [184.5], n, bins)

ydata = funz(param, np.arange(min(bins), max(bins)))
plt.plot(np.arange(min(bins), max(bins)), ydata)


print "lambda calcolato = ", param[0]

plt.savefig("out.png")


# ----------- #
# Fine codice #
# ----------- #

# HACK!!!
# Non modificare il codice sotto questa riga:
# serve a gestire correttamente la finestra di root
#import sys
#from Tkinter import Tk

#def check_quit():
  #try:
    #a = c1.GetWindowWidth()
    #root.after(500, check_quit)
  #except AttributeError:
    #sys.exit()

#root = None # invisible tk window
#root = Tk()
#root.withdraw()
#root.after(1, check_quit)
#root.mainloop()

