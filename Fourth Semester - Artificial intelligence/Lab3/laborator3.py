!pip install azure-cognitiveservices-vision-computervision
!pip install pillow

from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import OperationStatusCodes
from azure.cognitiveservices.vision.computervision.models import VisualFeatureTypes
from msrest.authentication import CognitiveServicesCredentials
from array import array
import os
from PIL import Image
import sys
import time

'''
Authenticate
Authenticates your credentials and creates a client.
'''

subscription_key = os.environ["VISION_KEY"]
endpoint = os.environ["VISION_ENDPOINT"]
computervision_client = ComputerVisionClient(endpoint, CognitiveServicesCredentials(subscription_key))
'''
END -Authenticate
'''

import requests
import shutil

img_path1 = "test1.png"
response1 = requests.get(img_url1)
if response1.status_code == 200:
  with open(img_path1, 'wb') as f:
    f.write(response1.content)
else:
  print(f"Eroare la descarcarea imaginii {img_path1}")

img_path2 = "test2.jpeg"
response2 = requests.get(img_url2)
if response2.status_code == 200:
  with open(img_path2, 'wb') as f:
    f.write(response2.content)
else:
  print(f"Eroare la descarcarea imaginii {img_path2}")

destination_path = "test2_copy.jpeg"
shutil.copy(img_path2, destination_path)

groundTruth1 = ["Google Cloud", "Platform"]
groundTruth2 = ["Succes în rezolvarea", "tEMELOR la", "LABORA toarele de", "Inteligență Artificială!"]

from re import T

def get_text_ocr(image):
  """
  Extrage textul prin OCR
  :param image: Cale catre imagine
  :return: Textul detectat
  """
  img = open(image, 'rb')
  read_resposponse = computervision_client.read_in_stream(
      image = img,
      mode = "Printed",
      raw = True
  )

  operation_location_remote = read_resposponse.headers["Operation-Location"]
  operation_id = operation_location_remote.split("/")[-1]
  while True:
    get_text_result = computervision_client.get_read_result(operation_id)
    if get_text_result.status not in ['notStarted', 'running']:
      break
    time.sleep(1)

  result = []
  if get_text_result.status == OperationStatusCodes.succeeded:
    for text_result in get_text_result.analyze_result.read_results:
      for line in text_result.lines:
        text = line.text
        result.append(text)
  return result

print(f"Textul identificat in imaginea test1.png {get_text_ocr(img_path1)}")
print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2)}")

def evaluate_output(groundTruth, image):
  """
  Returneaza numarul de linii identificate
  :param groundTruth: Textul real
  :param image: Cale catre imagine
  :return: Numarul de linii identificate
  """
  noOfCorrectLines = sum(i == j for i, j in zip(get_text_ocr(image), groundTruth))
  return noOfCorrectLines

print(f"Numarul de linii corect identificate in imaginea test1.png este: {evaluate_output(groundTruth1, img_path1)}")
print(f"Numarul de linii corect identificate in imaginea test2.jpeg este: {evaluate_output(groundTruth2, img_path2)}")

def get_location_ocr(image):
  """
  Extrage locatia textului prin OCR
  :param image: Cale catre imagine
  :return: Locatia textului
  """
  img = open(image, 'rb')
  read_resposponse = computervision_client.read_in_stream(
      image = img,
      mode = "Printed",
      raw = True
  )

  operation_location_remote = read_resposponse.headers["Operation-Location"]
  operation_id = operation_location_remote.split("/")[-1]
  while True:
    get_text_result = computervision_client.get_read_result(operation_id)
    if get_text_result.status not in ['notStarted', 'running']:
      break
    time.sleep(1)

  result = []
  if get_text_result.status == OperationStatusCodes.succeeded:
    for text_result in get_text_result.analyze_result.read_results:
      for line in text_result.lines:
        text = line.text
        location = line.bounding_box
        result.append(f"Text: {text}, Locatie: {location}")
  return result

print(f"Locatiile textului identificat in imaginea test1.png {get_location_ocr(img_path1)}")
print(f"Locatiile textului identificat in imaginea test2.jpeg {get_location_ocr(img_path2)}")

"""**Problema 1**

Calitatea procesului de recunoaștere a textului, atât la nivel de caracter, cât și la nivel de cuvânt.

a.prin folosirea unei metrici de distanta sau

b.prin folosirea mai multor metrici de distanta.

**Character Error Rate (CER)** - raportul dintre numărul total de erori și numărul total de caractere din textul de referință

**CER** = numărul de erori/numărul total de caractere din textul de referință
"""

def list_to_text(list1, list2):
  """
  Converteste doua liste in doua texte
  :param list1: Prima lista
  :param list2: A doua lista
  :return: Doua texte
  """
  text1 = " ".join(list1)
  text2 = " ".join(list2)
  return text1, text2

def CER_Metric(ocr_text, ground_truth):
  """
  Returneaza CER-ul
  :param ocr_text: Textul identificat
  :param ground_truth: Textul real
  :return: CER-ul
  """
  ocr_text = " ".join(ocr_text)
  ground_truth = " ".join(ground_truth)

  len_ocr = len(ocr_text)
  len_gt = len(ground_truth)
  len_min = min(len_ocr, len_gt)

  #Numarul caracterelor diferite in partea comuna
  errors = sum(1 for i in range(len_min) if ocr_text[i] != ground_truth[i])

  #Diferenta de lungimi
  errors += abs(len_ocr - len_gt)

  cer = errors/len_gt
  return cer

print(f"CER-ul imaginii test1.png este: {CER_Metric(get_text_ocr(img_path1), groundTruth1)}")
print(f"CER-ul imaginii test2.jpeg este: {CER_Metric(get_text_ocr(img_path2), groundTruth2)}")

"""**Word Error Rate (WER)** - raportul dintre numărul total de erori la nivel de cuvânt și numărul total de cuvinte din textul de referință.

**WER** = numărul de cuvinte greșite/numărul de cuvinte din textul de referință

"""

def WER_Metric(ocr_text, ground_truth):
  """
  Returneaza WER-ul
  :param ocr_text: Textul identificat
  :param ground_truth: Textul real
  :return: WER-ul
  """
  ocr_words = " ".join(ocr_text).split()
  gt_words = " ".join(ground_truth).split()

  num_of_words_ocr = len(ocr_words)
  num_of_words_gt = len(gt_words)
  num_of_words_min = min(num_of_words_ocr, num_of_words_gt)

  errors = sum(1 for i in range(num_of_words_min) if ocr_words[i] != gt_words[i])
  errors += abs(num_of_words_ocr - num_of_words_gt)

  wer = errors/num_of_words_gt
  return wer

print(f"WER-ul imaginii test1.png este: {WER_Metric(get_text_ocr(img_path1), groundTruth1)}")
print(f"WER-ul imaginii test2.jpeg este: {WER_Metric(get_text_ocr(img_path2), groundTruth2)}")

"""**Distanța Levenshtein** - numărul minim de operații (inserare, ștergere, substituire) necesare pentru a transforma un șir în altul, in functie de caractere."""

def Levenshtein_Characters_Distance(str1, str2):
  """
  Returneaza distanta Levenshtein pe caractere
  :param str1: Prima sir
  :param str2: A doua sir
  :return: Distanta Levenshtein pe caractere
  """
  len_str1 = len(str1)
  len_str2 = len(str2)

  #initializare matrice de costuri
  cost = [[0 for _ in range(len_str2 + 1)] for _ in range(len_str1 + 1)]
  for i in range(len_str1 + 1):
    cost[i][0] = i #cost inserare
  for j in range(len_str2 + 1):
    cost[0][j] = j #cost stergere

  for i in range(1, len_str1 + 1):
    for j in range(1, len_str2 + 1):
      c = 0 if str1[i - 1] == str2[j - 1] else 1 #cost substitutie
      cost[i][j] = min(cost[i - 1][j] + 1, #stergere
                       cost[i][j - 1] + 1, #inserare
                       cost[i - 1][j - 1] + c) #substitutie

  return cost[len_str1][len_str2]

text1, text2 = list_to_text(get_text_ocr(img_path1), groundTruth1)
print(f"Distanta Levenshtein pe caractere a textului identificat in imaginea test1.png este: {Levenshtein_Characters_Distance(text1, text2)}")

text1, text2 = list_to_text(get_text_ocr(img_path2), groundTruth2)
print(f"Distanta Levenshtein pe caractere a textului identificat in imaginea test2.jpeg este: {Levenshtein_Characters_Distance(text1, text2)}")

"""**Distanța Levenshtein** - numărul minim de operații (inserare, ștergere, substituire) necesare pentru a transforma un șir în altul, in functie de cuvinte."""

def Levenshtein_Words_Distance(str1, str2):
    """
    Returneaza distanta Levenshtein pe cuvinte
    :param str1: Primul text
    :param str2: Al doilea text
    :return: Distanta Levenshtein pe cuvinte
    """
    words1 = str1.split()
    words2 = str2.split()

    len_words1 = len(words1)
    len_words2 = len(words2)

    # Initializare matrice de costuri
    cost = [[0 for _ in range(len_words2 + 1)] for _ in range(len_words1 + 1)]
    for i in range(len_words1 + 1):
        cost[i][0] = i  # cost inserare
    for j in range(len_words2 + 1):
        cost[0][j] = j  # cost stergere

    for i in range(1, len_words1 + 1):
        for j in range(1, len_words2 + 1):
            c = 0 if words1[i - 1] == words2[j - 1] else 1  # cost substitutie
            cost[i][j] = min(cost[i - 1][j] + 1,  # stergere
                             cost[i][j - 1] + 1,  # inserare
                             cost[i - 1][j - 1] + c)  # substitutie

    return cost[len_words1][len_words2]

text1, text2 = list_to_text(get_text_ocr(img_path1), groundTruth1)
print(f"Distanta Levenshtein pe cuvinte a textului identificat in imaginea test1.png este: {Levenshtein_Words_Distance(text1, text2)}")

text1, text2 = list_to_text(get_text_ocr(img_path2), groundTruth2)
print(f"Distanta Levenshtein pe cuvinte a textului identificat in imaginea test2.jpeg este: {Levenshtein_Words_Distance(text1, text2)}")

"""**Distanța Hamming** - numărul de poziții dintre două șiruri de aceeași lungime sunt diferite, in functie de caractere

"""

def Hamming_Characters_Distance(str1, str2):
  """
  Returneaza distanta Hamming pe caractere
  :param str1: Prima sir
  :param str2: A doua sir
  :return: Distanta Hamming
  """
  len_str1 = len(str1)
  len_str2 = len(str2)
  if len_str1 != len_str2:
    print("Sirurile nu au aceeași lungime")
    return

  return sum(1 for i in range(len_str1) if str1[i] != str2[i])

text1, text2 = list_to_text(get_text_ocr(img_path1), groundTruth1)
print(f"Distanta Hamming pe caractere a textului identificat in imaginea test1.png este: {Hamming_Characters_Distance(text1, text2)}")

text1, text2 = list_to_text(get_text_ocr(img_path2), groundTruth2)
print(f"Distanta Hamming pe caractere a textului identificat in imaginea test2.jpeg este: {Hamming_Characters_Distance(text1, text2)}")

"""**Distanța Hamming** - numărul de poziții dintre două șiruri de aceeași lungime sunt diferite, in functie de cuvinte"""

def Hamming_Words_Distance(str1, str2):
    """
    Returneaza distanta Hamming pe cuvinte
    :param str1: Primul text
    :param str2: Al doilea text
    :return: Distanta Hamming pe cuvinte
    """
    words1 = str1.split()
    words2 = str2.split()

    len_words1 = len(words1)
    len_words2 = len(words2)

    if len_words1 != len_words2:
        print("Textele nu au acelasi numar de cuvinte")
        return

    return sum(1 for i in range(len_words1) if words1[i] != words2[i])

# Exemplu de utilizare
text1, text2 = list_to_text(get_text_ocr(img_path1), groundTruth1)
print(f"Distanta Hamming pe cuvinte pentru imaginea test1.png este: {Hamming_Words_Distance(text1, text2)}")

text1, text2 = list_to_text(get_text_ocr(img_path2), groundTruth2)
print(f"Distanta Hamming pe cuvinte pentru imaginea test2.jpeg este: {Hamming_Words_Distance(text1, text2)}")

"""**Distanța Euclidiană** - măsoară diferența dintr două distribuții de caractere sau cuvinte într-un spațiu multidimensional."""

from collections import Counter
import math

def Euclidian_Metric_Distance(str1, str2):
  """
  Returneaza distanta Euclidiană
  :param str1: Prima sir
  :param str2: A doua sir
  :return: Distanta Euclidiană
  """
  fr1 = Counter(str1)
  fr2 = Counter(str2)

  all_chars = set(fr1.keys()).union(set(fr2.keys())) #normalizez pentru a putea compara
  vec_fr1 = [fr1[c] for c in all_chars]
  vec_fr2 = [fr2[c] for c in all_chars]

  distance = math.sqrt(sum((a - b) ** 2 for a, b in zip(vec_fr1, vec_fr2)))
  return distance

text1, text2 = list_to_text(get_text_ocr(img_path1), groundTruth1)
print(f"Distanta Euclidiana a textului identificat in imaginea test1.png este: {Euclidian_Metric_Distance(text1, text2)}")

text1, text2 = list_to_text(get_text_ocr(img_path2), groundTruth2)
print(f"Distanta Euclidiana a textului identificat in imaginea test2.jpeg este: {Euclidian_Metric_Distance(text1, text2)}")

"""**Problema 2**

Să se determine calitatea localizarii corecte a textului in imagine.
"""

from PIL import ImageDraw
from IPython.display import display

def get_location_ocr_version2(image):
  """
  Extrage locatia textului prin OCR
  :param image: Cale catre imagine
  :return: Locatia textului
  """
  img = open(image, 'rb')
  read_resposponse = computervision_client.read_in_stream(
      image = img,
      mode = "Printed",
      raw = True
  )

  operation_location_remote = read_resposponse.headers["Operation-Location"]
  operation_id = operation_location_remote.split("/")[-1]
  while True:
    get_text_result = computervision_client.get_read_result(operation_id)
    if get_text_result.status not in ['notStarted', 'running']:
      break
    time.sleep(1)

  result = []
  if get_text_result.status == OperationStatusCodes.succeeded:
    for text_result in get_text_result.analyze_result.read_results:
      for line in text_result.lines:
        text = line.text
        location = line.bounding_box

        xmin = min(location[0], location[2], location[4], location[6])
        ymin = min(location[1], location[3], location[5], location[7])
        xmax = max(location[0], location[2], location[4], location[6])
        ymax = max(location[1], location[3], location[5], location[7])
        result.append([xmin, ymin, xmax, ymax])
  return result

def display_image(image, locations):
  draw = ImageDraw.Draw(image)
  for i in locations:
    draw.rectangle(i, outline="red", width=1)
  display(image)

img = Image.open(img_path1)
display_image(img, get_location_ocr_version2(img_path1))
img = Image.open(img_path2)
display_image(img, get_location_ocr_version2(img_path2))

"""**Intersection over Union (IoU)** - măsoară cât de bine se suprapune zona detectată cu cea reală.

**IoU** = Zonă suprarpunere/ Zonă unire
"""

def IoU_Metric(location1, location2):
  """
  Returneaza IoU-ul
  :param location1: Prima locatie, cea identificata
  :param location2: A doua locatie, cea reală
  :return: IoU-ul
  """
  x_min_intersection = max(location1[0], location2[0])
  y_min_intersection = max(location1[1], location2[1])
  x_max_intersection = min(location1[2], location2[2])
  y_max_intersection = min(location1[3], location2[3])

  intersection_area = max(0, x_max_intersection - x_min_intersection) * max(0, y_max_intersection - y_min_intersection)

  area1 = (location1[2] - location1[0]) * (location1[3] - location1[1])
  area2 = (location2[2] - location2[0]) * (location2[3] - location2[1])
  union_area = area1 + area2 - intersection_area

  return intersection_area/union_area if union_area > 0 else 0

def IoU_Metric_on_lines(location1, location2):
  """
  Returneaza IoU-ul pentru mai multe linii
  :param location1: Prima locatie, cea identificata
  :param location2: A doua locatie, cea reală
  :return: IoU-ul
  """
  for i, j in zip(location1, location2):
    print(IoU_Metric(i, j))


almost_real_location1 = [[176.0, 41.0, 415.0, 105.0],
[235.0, 112.0, 349.0, 151.0]]
print("IoU-ul pentru imaginea test1.png este:")
IoU_Metric_on_lines(get_location_ocr_version2(img_path1), almost_real_location1)

almost_real_location2 = [[70.0, 292.0, 1330.0, 462.0],
[130.0, 580.0, 1046.0, 725.0],
[78.0, 915.0, 1007.0, 1025.0],
[103.0, 1125.0, 1452.0, 1367.0]]
print("IoU-ul pentru imaginea test2.jpeg este:")
IoU_Metric_on_lines(get_location_ocr_version2(img_path2), almost_real_location2)

"""**Average IoU**

IoU ≈ 0	Localizare foarte slabă

0.5 ≤ IoU < 0.7	Localizare decentă

0.7 ≤ IoU < 0.9	Localizare bună

IoU ≥ 0.9	Localizare excelentă
"""

def average_IoU(ground_truth_boxes, ocr_boxes):
  """
  Returneaza media IoU
  :param ground_truth_boxes: Locatiile reale
  :param ocr_boxes: Locatiile identificate
  :return: Media IoU
  """
  total_iou = 0
  minim = min(len(ground_truth_boxes), len(ocr_boxes))
  for i in range(minim):
    total_iou += IoU_Metric(ground_truth_boxes[i], ocr_boxes[i])
  return total_iou/minim if minim > 0 else 0

print(f"Media IoU pentru imaginea test1.png este: {average_IoU(almost_real_location1, get_location_ocr_version2(img_path1))}")
print(f"Media IoU pentru imaginea test2.jpeg este: {average_IoU(almost_real_location2, get_location_ocr_version2(img_path2))}")

"""**Problema 3**

Să se determine posibilități de îmbunătățire a recunoașterii textului.
"""

import cv2

def normalization(image):
  """
  Normalizeaza imaginea
  :param image: Cale catre imagine
  :return: Imaginea normalizata
  """
  image = cv2.imread(image)
  image_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
  image_eq = cv2.equalizeHist(image_gray)
  image_norm = cv2.normalize(image_eq, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX)

  return image_norm

img_path2_n = normalization(img_path2)
plt.imshow(img_path2_n, cmap='gray')
plt.axis('off')
plt.show()
cv2.imwrite("test2_normalize.jpeg", img_path2_n)
img_path2_normalize = "test2_normalize.jpeg"
print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2_normalize)}")

"""**Binarize image**"""

import numpy as np
import cv2
import matplotlib.pyplot as plt

def binarize_image(image_pah, method):
  """
  Binarizeaza imaginea
  :param image_pah: Cale catre imagine
  :param method: Metoda de binarizare
  :return: Imaginea binarizata
  """
  img = cv2.imread(image_pah, cv2.IMREAD_GRAYSCALE)
  img = cv2.GaussianBlur(img, (3, 3), 0)
  if method == "otsu":
    _, binary_img = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
  elif method == "adaptive":
    binary_img = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                           cv2.THRESH_BINARY, 11, 2)
  elif method == "adaptive_mean":
    binary_img = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C,
                                           cv2.THRESH_BINARY, 11, 2)
  elif method == "inverse":
    _, binary_img = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
  else:
    raise ValueError("Metodă de binarizare necunoscută!")

  return binary_img

img_path1_bin = binarize_image(img_path1, "otsu")
plt.imshow(img_path1_bin, cmap='gray')
plt.axis('off')
plt.show()
cv2.imwrite("test1_binarized.png", img_path1_bin)
img_path1_binarized = "test1_binarized.png"

img_path2_bin = binarize_image(img_path2, "otsu")
plt.imshow(img_path2_bin, cmap='gray')
plt.axis('off')
plt.show()
cv2.imwrite("test2_binarized.jpeg", img_path2_bin)
img_path2_binarized = "test2_binarized.jpeg"
print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2_normalize)}")

def correct_text_alignment(image):
    """
    Corectarea aliniamentului textului în imagine.

    :param image: Imaginea originală.
    :return: Imagine cu textul corect aliniat.
    """
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray_image, 50, 150, apertureSize=3)
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, threshold=100, minLineLength=50, maxLineGap=10)
    angles = []
    for line in lines:
        x1, y1, x2, y2 = line[0]
        angle = np.arctan2(y2 - y1, x2 - x1) * 180 / np.pi
        angles.append(angle)
    median_angle = np.median(angles)
    (h, w) = image.shape[:2]
    M = cv2.getRotationMatrix2D((w / 2, h / 2), median_angle, 1.0)
    corrected_image = cv2.warpAffine(image, M, (w, h), flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_REPLICATE)

    return corrected_image

img = cv2.imread(img_path2)
img_correct = correct_text_alignment(img)
img_correct_rgb = cv2.cvtColor(img_correct, cv2.COLOR_BGR2RGB)

plt.imshow(img_correct_rgb)
plt.axis('off')
plt.show()

cv2.imwrite("test2_correct.jpeg", img_correct)
img_path2_correction = "test2_correct.jpeg"

print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2_correction)}")

def enlarge_text_in_image(image, scale_factor=2):
    """
    Mărirea fonturilor din imagine pentru a îmbunătăți recunoașterea textului.
    :param image: Imaginea originală.
    :param scale_factor: Factorul de scalare pentru mărirea textului.
    :return: Imaginea cu fonturi mărite.
    """
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    _, binary_image = cv2.threshold(gray_image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
    height, width = binary_image.shape[:2]
    new_dim = (int(width * scale_factor), int(height * scale_factor))
    enlarged_image = cv2.resize(binary_image, new_dim, interpolation=cv2.INTER_CUBIC)

    return enlarged_image

img = cv2.imread(img_path2)
image_enlarged = enlarge_text_in_image(img)
cv2.imwrite("image_enlarged.jpg", image_enlarged)

plt.imshow(image_enlarged)
plt.axis('off')
plt.show()

cv2.imwrite("test2_enlarge.jpeg", image_enlarged)
img_path2_enlarge = "test2_enlarge.jpeg"

print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2_enlarge)}")

def denoise_image(image_path):
  """
  Eliminarea zgomoturilor din imagine
  :param image_path: Cale catre imagine
  :return: Imaginea, din care sau eliminat zgomotele
  """
  image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
  blurred = cv2.GaussianBlur(image, (5, 5), 0)
  median_filtered = cv2.medianBlur(blurred, 3)
  _, binary_image = cv2.threshold(median_filtered, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)
  kernel = np.ones((2,2), np.uint8)
  clean_image = cv2.morphologyEx(binary_image, cv2.MORPH_OPEN, kernel, iterations=1)

  return clean_image

image_path2 = "test2.jpeg"
img_clean = denoise_image(image_path2)

plt.imshow(img_clean, cmap='gray')
plt.axis('off')
plt.show()

cv2.imwrite("test2_clean.jpeg", img_clean)
img_path2_clean = "test2_clean.jpeg"

print(f"Textul identificat in imaginea test2.jpeg {get_text_ocr(img_path2_clean)}")
    
