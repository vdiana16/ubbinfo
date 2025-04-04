import os
import requests
from PIL import Image
import cv2

nume_imagini = ["Altman.webp", "Ng.webp", "Turing.webp",
                "BERT.png", "chatGPT.png",
                "Karpaty.jpg", "LeCun.jpg", "Leskovec.jpg", "Norvig.jpg", "Russell.jpg",
                "YOLO.jpg", "diffusionModel.jpg"]
folder = "imaginiAI"
os.makedirs(folder, exist_ok="True")

for imagine in nume_imagini:
  r = requests.get(imagine)
  if r.status_code == 200:
    with open(folder + "/" + imagine, 'wb') as f:
      f.write(r.content)
      print (f"Descarcata imaginea {imagine}")
  else:
    print(f"Eroare la descarcarea imaginii {imagine}")

"""Se cere: sa se vizualizeze una din imagini"""

import matplotlib.pyplot as plt

def vizualizare_imagine(cale_imagine):
  """
  Vizualizare imagine
  :param cale_imagine: calea catre imagine
  :return: imaginea vizualizata
  """
  imagine = cv2.imread(cale_imagine)
  imagine_rgb = cv2.cvtColor(imagine, cv2.COLOR_BGR2RGB)
  plt.imshow(imagine_rgb)
  plt.axis("off")
  plt.show()

cale_imagine = os.path.join(folder, "Karpaty.jpg")
vizualizare_imagine(cale_imagine)

"""daca imaginile nu au aceeasi dimensiune, sa se redimensioneze toate la 128 x 128 pixeli si sa se vizualizeze imaginile intr-un cadru tabelar."""

def redimensionare_vizualizare(folder):
  """
  Redimensionare si vizualizare imagini
  :param folder: calea catre folder-ul cu imagini
  :return: imaginile redimensionate si vizualizate
  """
  imagini = [f for f in os.listdir(folder) if f.endswith(('webp', 'png', 'jpg'))]
  lista_imagini = []
  for img in imagini:
    cale_imagine = os.path.join(folder, img)
    if  img is not None:
      img = Image.open(cale_imagine)
      img = img.resize((128, 128))
      lista_imagini.append(img)
    else:
      print(f"Eroare la incarcarea imaginii {img}")

  n = len(lista_imagini)
  n_coloane = 3
  n_randuri = (n + n_coloane - 1) // n_coloane
  fig, axs = plt.subplots(n_randuri, n_coloane, figsize=(12, 4*n_randuri))
  axs = axs.ravel()
  for i in range(n):
    axs[i].imshow(lista_imagini[i])
    axs[i].axis("off") #ascund axele

  for j in range(n,len(axs)):
    axs[j].axis("off") #impiedic afisarea axelor

  plt.tight_layout()
  plt.show()

redimensionare_vizualizare(folder)

"""sa se transforme imaginile in format gray-levels si sa se vizualizeze"""

import numpy as np
def redimensionare_vizualizare_gray(folder):
  """
  Redimensionare si vizualizare imagini in format gray-levels
  :param folder: calea catre folder-ul cu imagini
  :return: imaginile redimensionate si vizualizate
  """
  imagini = [f for f in os.listdir(folder) if f.endswith(('webp', 'png', 'jpg'))]
  lista_imagini = []
  for img in imagini:
    cale_imagine = os.path.join(folder, img)
    if  img is not None:
      img = Image.open(cale_imagine)
      img = img.resize((128, 128))
      img_np = np.array(img)
      # Verifică dacă imaginea are 3 canale de culoare (RGB sau BGR)
      if len(img_np.shape) == 3:
        img_gray = cv2.cvtColor(img_np, cv2.COLOR_RGB2GRAY)
      else:
        img_gray = img_np
      lista_imagini.append(img_gray)
    else:
      print(f"Eroare la incarcarea imaginii {img}")

  n = len(lista_imagini)
  n_coloane = 3
  n_randuri = (n + n_coloane - 1) // n_coloane
  fig, axs = plt.subplots(n_randuri, n_coloane, figsize=(12, 4*n_randuri))
  axs = axs.ravel()
  for i in range(n):
    axs[i].imshow(lista_imagini[i], cmap = 'gray')
    axs[i].axis("off") #ascund axele

  for j in range(n,len(axs)):
    axs[j].axis("off") #impiedic afisarea axelor

  plt.tight_layout()
  plt.show()

redimensionare_vizualizare_gray(folder)

"""sa se blureze o imagine si sa se afiseze in format "before-after"
"""

def blurare_imagine(cale_imagine):
  """
  Vizualizare imagine blurata
  :param cale_imagine: calea catre imagine
  :return: imaginea vizualizata
  """
  imagine = cv2.imread(cale_imagine)
  if imagine is None:
    print("Eroare la incarcarea imaginii")
  else:
    imagine_blurata = cv2.GaussianBlur(imagine, (15, 15), 0) # (15, 15) este dimensiunea kernelului

  imagine_rgb = cv2.cvtColor(imagine, cv2.COLOR_BGR2RGB)
  imagine_blurata_rgb = cv2.cvtColor(imagine_blurata, cv2.COLOR_BGR2RGB)
  fig, axs = plt.subplots(1, 2, figsize=(10, 5))

  axs[0].imshow(imagine_rgb)
  axs[0].set_title("Imagine inainte de blurare")
  axs[0].axis("off")

  axs[1].imshow(imagine_blurata_rgb)
  axs[1].set_title("Imagine dupa blurare")
  axs[1].axis("off")

  plt.tight_layout()
  plt.show()

cale_imagine = os.path.join(folder, "Karpaty.jpg")
blurare_imagine(cale_imagine)

"""sa se identifice muchiile intr-o imagine si sa se afiseze in format "before-after"
"""

def muchii_imagine(cale_imagine):
  """
  Vizualizare imagine cu muchiile
  :param cale_imagine: calea catre imagine
  :return: imaginea vizualizata
  """
  imagine = cv2.imread(cale_imagine)
  if imagine is None:
    print("Eroare la incarcarea imaginii")
  else:
    imagine_gray = cv2.cvtColor(imagine, cv2.COLOR_BGR2GRAY)

  imagine_rgb = cv2.cvtColor(imagine, cv2.COLOR_BGR2RGB)
  muchii = cv2.Canny(imagine_gray, 100, 200) # 100 și 200 sunt pragurile minime și maxime pentru Canny

  fig, axs = plt.subplots(1, 2, figsize=(10, 5))

  axs[0].imshow(imagine_rgb)
  axs[0].set_title("Imagine inainte(originală)")
  axs[0].axis("off")

  axs[1].imshow(muchii, cmap='gray')
  axs[1].set_title("Imagine dupa(muchii)")
  axs[1].axis("off")

  plt.tight_layout()
  plt.show()

cale_imagine = os.path.join(folder, "Karpaty.jpg")
muchii_imagine(cale_imagine)

"""Problema 4
Sa se normalizeze informatiile de la problema folosind diferite metode de normalizare astfel:
problema 2 - valorile pixelilor din imagini
"""

from sklearn.preprocessing import MinMaxScaler, StandardScaler
import numpy as np

def normalizare_valori_pixeli(folder):
  """
  Normalizare valori pixeli
  :param folder: calea catre folder-ul cu imagini
  :return: imaginile normalizate
  """
  imagini = [f for f in os.listdir(folder) if f.endswith(('webp', 'png', 'jpg'))]
  lista_imagini = []
  for img in imagini:
    cale_imagine = os.path.join(folder, img)
    if  img is not None:
      img = Image.open(cale_imagine)
      img = img.resize((128, 128))
      img_np = np.array(img)
      if len(img_np.shape) == 3 and img_np.shape[2] > 1:  # Check if it's not already grayscale
          imagine_rgb = cv2.cvtColor(img_np, cv2.COLOR_RGB2GRAY)
      else:
          imagine_rgb = img_np
      lista_imagini.append(imagine_rgb)
    else:
      print(f"Eroare la incarcarea imaginii {img}")
      return
  imagini = np.array(lista_imagini).astype(np.float32)

  scalare_minmax = MinMaxScaler()
  imagini_normalizate_min_max = scalare_minmax.fit_transform(imagini.reshape(len(lista_imagini), -1))
  imagini_normalizate_min_max = imagini_normalizate_min_max.reshape(len(lista_imagini),128,128)

  scalare_zscore = StandardScaler()
  imagini_normalizate_zscore = scalare_zscore.fit_transform(imagini.reshape(len(lista_imagini), -1))
  imagini_normalizate_zscore = imagini_normalizate_zscore.reshape(len(lista_imagini),128,128)

  fig, axes = plt.subplots(3, len(imagini), figsize=(5*len(lista_imagini), 15))
  for i in range(len(imagini)):
    axes[0, i].imshow(imagini[i], cmap='gray')
    axes[0, i].set_title('Imaginea originală')
    axes[0, i].axis('off')
    axes[1, i].imshow(imagini_normalizate_min_max[i], cmap='gray')
    axes[1, i].set_title('Imaginea normalizată folosind MinMaxScaler')
    axes[1, i].axis('off')
    axes[2, i].imshow(imagini_normalizate_zscore[i], cmap='gray')
    axes[2, i].set_title('Imaginea normalizată folosind StandardScaler')
    axes[2, i].axis('off')
  plt.tight_layout()
  plt.show()

normalizare_valori_pixeli(folder)


    
