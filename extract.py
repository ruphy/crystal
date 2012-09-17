# Aggiungi qui, separandole da virgole, le classi di ROOT
# che usi:
from os import popen
from ROOT import TCanvas, TH1F, TFile, TF1
from ROOT import gInterpreter, gSystem, gROOT, gDirectory
import numpy as np
import matplotlib.pyplot as plt
from scipy import odr
from re import sub

gSystem.AddLinkedLibs(popen('root-config --libs').read())
gInterpreter.GenerateDictionary("vector<ROOT::Math::Cartesian3D<double> >", "Math/Cartesian3D.h")

# ---------------------- #
# Inizio codice serio    #
# ---------------------- #

def run_sim(nm):
    ev = 1239.84/nm
    # sub the new energy in the file
    with open('gps.mac','r') as f:
        newlines = []
        for line in f.readlines():
            newlines.append(sub(r'/gps/energy.*', '/gps/energy %.3f eV' % ev, line))
    with open('gps.mac', 'w') as f:
        for line in newlines:
            f.write(line)
    # run the simulation
    popen('./crystal crystal.cfg')

    # open the tree file
    myfile = TFile( 'out.root' )

    # retrieve the ntuple of interest
    mychain = gDirectory.Get( 'tree' )
    entries = mychain.GetEntriesFast()

    data = []

    for jentry in xrange( entries ):
        nb = mychain.GetEntry( jentry )
        data.append(mychain.AbsLength)

    def funz(P, x):
        return P[1]*np.exp(-x/P[0])

    plt.clf()
    plt.grid(True)

    (n, bins, patches) = plt.hist(data, 100, color='#50e300', alpha=.7)
    bins = 0.5*(bins[:-1] + bins[1:])

    (param, errors, cov) = odr.odr(funz, [184.5, 10000], n, bins)

    ydata = funz(param, np.arange(min(bins), max(bins)))
    plt.plot(np.arange(min(bins), max(bins)), ydata)

    plt.title(r"Mean absorption length (%dnm): $\lambda=$ %.1f mm" % (nm, param[0]))
    plt.ylabel("Photons")
    plt.xlabel("Distance travelled (mm)")

    #print "lambda calcolato = ", param[0]

    plt.savefig("out%d.png" %nm)


nms = [420, 470, 500];

for i in nms:
    run_sim(i)


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

