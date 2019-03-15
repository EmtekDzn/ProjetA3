

from tkinter import *
from tkinter import ttk
import os
import time

REFRESH_TIME = 200 # Délai de rafraichissement des données de températures et de statut du chauffage
DEFAULT_CSGN = "18.0" # Valeur par défaut de la consigne
class TemperaturesAndStatus:
    """
    string exterior la température extérieure
    string interior la température intérieure
    string status le statut du chauffage ('true' ou 'false')
    Label tempExtLabel le label affichant la température extérieure
    Label tempIntLabel le label affichant la température intérieure
    Label statusLabel le label affichant le statut du chauffage
    ttk.Progressbar tempExtBar la jauge de température extérieure (de 0°C à 50°C)
    ttk.Progressbar tempIntBar la jauge de température intérieure (de 0°C à 50°C)

    string lastExterior la température extérieure précédente (pour les calculs d'avancées de barre)
    string lastInterior la température intérieure précédente (pour les calculs d'avancées de barre)
    """
    def __init__(self, window): # window la window où insérer les éléments tkinter
        self.status = "false"
        self.exterior = "0.0"
        self.lastExterior = self.exterior
        self.interior = "0.0"
        self.lastInterior = self.interior

        self.tempExtLabel = Label(window, text="Température Extérieure : "+self.exterior)
        self.tempExtLabel.pack()
        self.tempExtBar = ttk.Progressbar(window, mode='determinate', maximum=50, length=250)
            # Barre en mode determinate (choix du niveau de remplissage), valeur maximum de 50(°C), 250 pixels de long
        self.tempExtBar.pack()

        self.tempIntLabel = Label(window, text="Température Intérieure : "+self.interior)
        self.tempIntLabel.pack()
        self.tempIntBar = ttk.Progressbar(window, mode='determinate', maximum=50, length=250)
            # Barre en mode determinate (choix du niveau de remplissage), valeur maximum de 50(°C), 250 pixels de long
        self.tempIntBar.pack()

        self.statusLabel = Label(window, text="Chauffage éteint")
        self.statusLabel.pack(pady=5) # Marges verticales autour de statusLabel de 5 px

    def display(self, window):
        """Affiche les températures et le statut
        """
        self.tempExtLabel.config(text="Température Extérieure : "+self.exterior) # Affichage des températures dans les labels
        self.tempIntLabel.config(text="Température Intérieure : "+self.interior) # Affichage des températures dans les labels
        if self.status == "true": # Si le chauffage est allumé
            self.statusLabel.config(text="Chauffage allumé")
            self.statusLabel.config(background="red")
        else:                     # Si le chauffage est étent
            self.statusLabel.config(text="Chauffage éteint")
            self.statusLabel.config(background="green")
        self.tempExtBar.step(float(self.exterior)-float(self.lastExterior)) # Avancée ou recul des jauges de températures
        self.tempIntBar.step(float(self.interior)-float(self.lastInterior)) # Avancée ou recul des jauges de températures


def getAndDisplayTempsAndStatus(temps, window):
    if os.path.exists(".verrouData"): # Si le verrou existe
        print("verrouData présent")
        window.after(REFRESH_TIME, lambda: getAndDisplayTempsAndStatus(temps, window)) # Rappel de la fonction après le délai
        return
    open(".verrouData", "w").close() # Création du verrou
    f = open("data.txt", "r") # Ouverture de data.txt en mode lecture seule
    lines = f.readlines() # Lecture des lignes
    f.close() # Fermeture du fichier
    temps.lastExterior = temps.exterior # Sauvegarde des températures
    temps.lastInterior = temps.interior # Sauvegarde des températures
    try:
        temps.exterior = lines[0].strip()
        temps.interior = lines[1].strip()
        temps.status = lines[2].strip()
        os.remove(".verrouData")
    except (OSError, IndexError) as e: # Il est possible que la lecture du fichier échoue, ou que l'effacement du verrou échoue
        print(e)
    temps.display(window) # Affichage des valeurs récupérées
    window.after(REFRESH_TIME, lambda: getAndDisplayTempsAndStatus(temps, window)) # Rappel de la fonction après le délai


def readConsigne():
    if os.path.exists(".verrouConsigne"): # Si le verrou existe
        print("verrouConsigne présent")
        return DEFAULT_CSGN # Retour de la valeur par défaut
    open(".verrouConsigne", "w").close() # Création du verrou
    f = open("consigne.txt", "r") # Ouverture de consigne.txt en mode lecture seule
    consigne = f.read() # Lecture de la consigne
    f.close()  # Fermeture du fichier
    try:
        os.remove(".verrouConsigne")
    except OSError: # Il est possible que l'effacement du verrou échoue
        print(OSError)
    return consigne


def writeConsigneFromInput(entry, string_consigne):
    consigne = entry.get().strip()  # Nettoyage des espaces blancs de la chaine
    try:
        float(consigne) # Tentative de convertir le string en float
    except ValueError: # Si consigne ne correspond pas à un flottant
        string_consigne.set(DEFAULT_CSGN) # Réinitialisation du contenu du Entry
        return
    if consigne.isdigit(): # Si la consigne est un entier
        consigne += ".0" # Ajout de ".0" derrière
    string_consigne.set(consigne) # Actualisation du contenu du Entry
    if os.path.exists(".verrouConsigne"): # Si le verrou existe
        print("verrouConsigne présent")
        return
    open(".verrouConsigne", "w").close() # Création du verrou
    f = open("consigne.txt", "w") # Ouverture de consigne.txt en mode écriture
    f.write(consigne) # Ecriture de la consigne
    f.close() # Fermeture du fichier
    try:
        os.remove(".verrouConsigne")
    except OSError:  # Il est possible que l'effacement du verrou échoue
        print(OSError)


window = Tk() # Fenêtre
window.title("Interface")
window.geometry("300x200")

labelDescCsgn = Label(window, text="Température consigne :")
labelDescCsgn.pack()

frameCsgn = Frame(window) # Frame pour mettre l'entrée consigne et la validation consigne
frameCsgn.pack()

string_consigne = StringVar()
string_consigne.set(readConsigne())
entryCsgn = Entry(frameCsgn, textvariable=string_consigne, width=5) # Entrée consigne
entryCsgn.pack(side=LEFT) # Alignement horizontal

submitConsigne = Button(frameCsgn, text='Valider',command=lambda: writeConsigneFromInput(entryCsgn, string_consigne)) 
    # Appuyer sur valider appelle writeConsigneFromInput
submitConsigne.pack(side=LEFT, padx=5, pady=5) # Alignement horizontal, paddings de 5px dans toutes les directions

temps = TemperaturesAndStatus(window)  # Objet TemperaturesAndStatus


window.after(REFRESH_TIME, lambda: getAndDisplayTempsAndStatus(temps, window))
    # Appeler getAndDisplayTempsAndStatus après le délai
window.mainloop()
