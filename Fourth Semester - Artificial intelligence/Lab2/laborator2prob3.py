"""
Se da un fisier care contine un text (format din mai multe propozitii) in limba romana - a se vedea fisierul ”data/texts.txt”. Se cere sa se determine si sa se vizualizeze
"""

import requests
import nltk

nltk.download('punkt')
nltk.download('punkt_tab')
nltk.download('wordnet')
!pip install unidecode

from unidecode import unidecode
from nltk.corpus import wordnet

url = "texts.txt"
r = requests.get(url)
if r.status_code == 200:
  with open("texts.txt", "w") as f:
    f.write(r.text)
else:
  print("Eroare la preluarea datelor")

cale_fisier = 'texts.txt'
with open(cale_fisier, 'r') as f:
    text = f.read()

"""numarul de propozitii din text;"""

def numar_propozitii(text):
  """
  Numarul de propozitii din text.
  :param text: textul de procesat
  :return: numarul de propozitii din text
  """
  propozitii = nltk.sent_tokenize(text)
  return len(propozitii)
print(f"Numarul de propozitii din text este: {numar_propozitii(text)}")

"""numarul de cuvinte din text"""

def numar_cuvinte(text):
  """
  Numarul de cuvinte din text.
  :param text: textul de procesat
  :return: numarul de cuvinte din text
  """
  cuvinte_extrase = nltk.word_tokenize(text)
  cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
  return len(cuvinte)
print(f"Numarul de cuvinte din text este: {numar_cuvinte(text)}")

"""numarul de cuvinte diferite din text"""

def numar_cuvinte_diferite(text):
  """
  Numarul de cuvinte diferite din text.
  :param text: textul de procesat
  :return: numarul de cuvinte diferite din text
  """
  cuvinte_extrase = nltk.word_tokenize(text)
  cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
  cuvinte_unice = set(cuvinte)
  return len(set(cuvinte_unice))
print(f"Numarul de cuvinte diferite este: {numar_cuvinte_diferite(text)}")

"""cel mai scurt si cel mai lung cuvant (cuvinte)"""

def numar_cuvinte_diferite(text):
  """
  Cel mai scurt si cel mai lung cuvant din text.
  :param text: textul de procesat
  :return: cel mai scurt si cel mai lung cuvant din text
  """
  cuvinte_extrase = nltk.word_tokenize(text)
  cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
  cel_mai_scurt_cuvant = min(cuvinte, key=len)
  cel_mai_lung_cuvant = max(cuvinte, key=len)
  return cel_mai_scurt_cuvant, cel_mai_lung_cuvant
print(f"Cel mai scurt cuvant este: {numar_cuvinte_diferite(text)[0]}")
print(f"Cel mai lung cuvant este: {numar_cuvinte_diferite(text)[1]}")

"""textul fara diacritice"""

def elimina_diacritice(text):
  """
  Elimina diacriticele din text.
  :param text: textul de procesat
  :return: textul fara diacritice
  """
  return unidecode(text)
print(f"Textul fara diacritice este: {elimina_diacritice(text)}")

"""sinonimele celui mai lung cuvant din text"""

import re
def sinonime_cel_mai_lung_cuvant(text):
  """
  Sinonimele celui mai lung cuvant din text.
  :param text: textul de procesat
  :return: sinonimele celui mai lung cuvant din text
  """
  cuvinte_extrase = nltk.word_tokenize(text)
  cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
  cel_mai_lung_cuvant = max(cuvinte, key=len)
  cel_mai_lung_cuvant = re.sub(r'(.)\1+', r'\1', cel_mai_lung_cuvant)
  sinonime = set()
  for sinonim in wordnet.synsets(cel_mai_lung_cuvant):
    for lemma in sinonim.lemmas():
      sinonime.add(lemma.name())
  return cel_mai_lung_cuvant, sinonime

print(f"Cel mai lung cuvant este: {sinonime_cel_mai_lung_cuvant(text)[0]}")
print(f"Sinonimele cuvantului sunt: {sinonime_cel_mai_lung_cuvant(text)[1]}")

"""Sa se normalizeze informatiile de la problema folosind diferite metode de normalizare astfel:
problema 3 - numarul de aparitii a cuvintelor la nivelul unei propozitii.
"""

from collections import Counter
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import matplotlib.pyplot as plt

def frecventa_cuvinte_propozitie(text):
  """
  Frecvența cuvintelor la nivelul unei propozitii.
  :param text: textul de procesat
  :return: frecvența cuvintelor la nivelul unei propozitii
           propozitiile
  """
  frecv = []
  propozitii = nltk.sent_tokenize(text)
  for propozitie in propozitii:
    cuvinte_extrase = nltk.word_tokenize(propozitie)
    cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
    frecv.append(Counter(cuvinte))
  return frecv, propozitii

def normalizare(text):
  frecventa, propozitii = frecventa_cuvinte_propozitie(text)

  # Lista tuturor cuvintelor unice
  cuvinte = list(set(cuv for prop in frecventa for cuv in prop.keys()))
  indecsi_cuvinte = {cuv: idx for idx, cuv in enumerate(cuvinte)}

  # Creăm matricea de frecvență
  matrice = np.zeros((len(propozitii), len(cuvinte)))

  for i, prop in enumerate(frecventa):
      for cuv, frecv in prop.items():
          matrice[i, indecsi_cuvinte[cuv]] = frecv

  df = pd.DataFrame(matrice, columns=cuvinte)

  # Aplicăm Min-Max Scaling
  scaler_minmax = MinMaxScaler()
  df_minmax = scaler_minmax.fit_transform(df)

  # Aplicăm Z-score
  scaler_zscore = StandardScaler()
  df_zscore = scaler_zscore.fit_transform(df)

  # Vizualizarea histogramelor
  fig, axes = plt.subplots(1, 3, figsize=(15, 6))

  axes[0].hist(df.values.flatten(), bins=20, alpha=0.6, color="#149414")
  axes[0].set_title("Distribuția frecvențelor originale")

  axes[1].hist(df_minmax.flatten(), bins=20, alpha=0.6, color="#add8e6")
  axes[1].set_title("Distribuția după Min-Max Scaling")

  axes[2].hist(df_zscore.flatten(), bins=20, alpha=0.6, color="#febfd2")
  axes[2].set_title("Distribuția după Z-score")

  plt.tight_layout()
  plt.show()

normalizare(text)

from collections import Counter
import numpy as np
import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler
import matplotlib.pyplot as plt

def frecventa_cuvinte_propozitie(text):
  """
  Frecvența cuvintelor la nivelul unei propozitii.
  :param text: textul de procesat
  :return: frecvența cuvintelor la nivelul unei propozitii
           propozitiile
  """
  frecv = []
  propozitii = nltk.sent_tokenize(text)
  for propozitie in propozitii:
    cuvinte_extrase = nltk.word_tokenize(propozitie)
    cuvinte = [cuvant.lower() for cuvant in cuvinte_extrase if cuvant.isalnum()]
    frecv.append(Counter(cuvinte))
  return frecv, propozitii

def normalizare(text):
  """
  Normalizarea datelor folosind Min-Max Scaling și Z-score.
  :param text: textul de procesat
  :return: matricea normalizată
  """
  frecventa, propozitii = frecventa_cuvinte_propozitie(text)
  cuvinte = list(set(cuv for prop in frecventa for cuv in prop.keys()))
  indecsi_cuvinte = {cuv: idx for idx, cuv in enumerate(cuvinte)}

  matrice = np.zeros((len(propozitii), len(cuvinte)))

  for i, prop in enumerate(frecventa):
      for cuv, frecv in prop.items():
          matrice[i, indecsi_cuvinte[cuv]] = frecv

  df = pd.DataFrame(matrice, columns=cuvinte, index=[f"Propozitie {i+1}" for i in range(len(propozitii))])

  scaler_minmax = MinMaxScaler()
  df_minmax = pd.DataFrame(scaler_minmax.fit_transform(df), columns=cuvinte, index=df.index)

  scaler_zscore = StandardScaler()
  df_zscore = pd.DataFrame(scaler_zscore.fit_transform(df), columns=cuvinte, index=df.index)

  print("\nFrecvențele originale:\n", df)
  print("\nDupă Min-Max Scaling:\n", df_minmax)
  print("\nDupă Z-score Scaling:\n", df_zscore)

  for i, prop in enumerate(propozitii):
      cuvinte_propozitie = list(frecventa[i].keys())
      fig, axes = plt.subplots(1, 3, figsize=(max(8, len(cuvinte_propozitie) * 0.8), 5))
      valori_originale = df.loc[f"Propozitie {i+1}", cuvinte_propozitie]
      valori_minmax = df_minmax.loc[f"Propozitie {i+1}", cuvinte_propozitie]
      valori_zscore = df_zscore.loc[f"Propozitie {i+1}", cuvinte_propozitie]

      axes[0].bar(cuvinte_propozitie, valori_originale, color="#149414", alpha=0.7)
      axes[0].set_title(f"Frecvențe originale - Propoziția {i+1}")
      axes[0].tick_params(axis='x', rotation=45, labelsize=10)

      axes[1].bar(cuvinte_propozitie, valori_minmax, color="#add8e6", alpha=0.7)
      axes[1].set_title(f"Min-Max Scaling - Propoziția {i+1}")
      axes[1].tick_params(axis='x', rotation=45, labelsize=10)

      axes[2].bar(cuvinte_propozitie, valori_zscore, color="#febfd2", alpha=0.7)
      axes[2].set_title(f"Z-score Scaling - Propoziția {i+1}")
      axes[2].tick_params(axis='x', rotation=45, labelsize=10)

      plt.tight_layout()
      plt.show()

normalizare(text)


    
