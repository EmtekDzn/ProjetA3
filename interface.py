

from tkinter import *
from tkinter import ttk
import os
import time

REFRESH_TIME = 100
class TemperaturesAndStatus:
    def __init__(self, window):
        self.status = "false"
        self.exterior = "0.0"
        self.lastExterior = self.exterior
        self.interior = "0.0"
        self.lastInterior = self.interior

        self.tempExtLabel = Label(fenetre, text="Température Extérieure : "+self.exterior)
        self.tempExtLabel.pack()
        self.tempExtBar = ttk.Progressbar(window, mode='determinate', maximum=50, length=250)
        self.tempExtBar.pack()

        self.tempIntLabel = Label(fenetre, text="Température Intérieure : "+self.interior)
        self.tempIntLabel.pack()
        self.tempIntBar = ttk.Progressbar(window, mode='determinate', maximum=50, length=250)
        self.tempIntBar.pack()

        self.statusLabel = Label(fenetre, text="Chauffage éteint")
        self.statusLabel.pack()

    def display(self, window):
        self.tempExtLabel.config(text="Température Extérieure : "+self.exterior)
        self.tempIntLabel.config(text="Température Intérieure : "+self.interior)
        if self.status == "true":
            self.statusLabel.config(text="Chauffage allumé")
        else:
            self.statusLabel.config(text="Chauffage éteint")
        self.tempExtBar.step(float(self.exterior)-float(self.lastExterior))
        self.tempIntBar.step(float(self.interior)-float(self.lastInterior))


def getAndDisplayTempsAndStatus(temps, window):
    while os.path.exists(".verrouData"):
        print("verrouData présent")
        time.sleep(0.1)
    open(".verrouData", "w").close()
    f = open("data.txt", "r")
    lines = f.readlines()
    temps.lastExterior = temps.exterior
    temps.lastInterior = temps.interior
    temps.exterior = lines[0].strip()
    temps.interior = lines[1].strip()
    temps.status = lines[2].strip()
    f.close()
    os.remove(".verrouData")
    temps.display(window)
    fenetre.after(REFRESH_TIME, lambda: getAndDisplayTempsAndStatus(temps, window))


def readConsigne():
    while os.path.exists(".verrouConsigne"):
        print("verrouConsigne présent")
        time.sleep(0.1)
    open(".verrouConsigne", "w").close()
    f = open("consigne.txt", "r")
    consigne = f.read()
    f.close()
    os.remove(".verrouConsigne")
    return consigne


def writeConsigneFromInput(entree, string_consigne):
    consigne = entree.get().strip()
    try:
        float(consigne)
    except ValueError:
        string_consigne.set("18.0")
        return
    if consigne.isdigit():
        consigne += ".0"
    string_consigne.set(consigne)
    while os.path.exists(".verrouConsigne"):
        print("verrouConsigne présent")
        time.sleep(0.1)
    open(".verrouConsigne", "w").close()
    f = open("consigne.txt", "w")
    f.write(consigne)
    f.close()
    os.remove(".verrouConsigne")


fenetre = Tk()
fenetre.title("Interface")
fenetre.geometry("300x200")

label = Label(fenetre, text="Température consigne :")
label.pack()

string_consigne = StringVar()
string_consigne.set(readConsigne())
entree = Entry(fenetre, textvariable=string_consigne, width=5)
entree.pack()

submitConsigne = Button(fenetre, text='Valider',
                        command=lambda: writeConsigneFromInput(entree, string_consigne))
submitConsigne.pack(padx=5, pady=5)

temps = TemperaturesAndStatus(fenetre)


fenetre.after(REFRESH_TIME, lambda: getAndDisplayTempsAndStatus(temps, fenetre))
fenetre.mainloop()
