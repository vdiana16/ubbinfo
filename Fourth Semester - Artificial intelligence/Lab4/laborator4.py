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
import matplotlib.pyplot as plt
from skimage import io
import numpy as np

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

def download_image(url, file_name):
  response = requests.get(url)
  if response.status_code == 200:
    with open(file_name, 'wb') as f:
      f.write(response.content)
  else:
    print(f"Eroare la descarcarea imaginii {file_name}")

img_url1 = "people.jpg"
img_file_name1 = "people.jpg"
download_image(img_url1, img_file_name1)
img1 = open(img_file_name1, "rb")
result = computervision_client.analyze_image_in_stream(img1, visual_features=[VisualFeatureTypes.tags, VisualFeatureTypes.objects])
print("tags ")
for tag in result.tags:
  print(tag)
  if (tag.name == "people") or (tag.name == "person") or (tag.name == "human") or (tag.name == "man"):
    print("People detected: ", tag.confidence)

print("objects ")
for obj in result.objects:
  print(obj.object_property, obj.rectangle)

img_url2 = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab04/images/animals.png"
img_file_name2 = "animals.png"
download_image(img_url2, img_file_name2)
img2 = open(img_file_name2, "rb")
im = plt.imread(img_file_name2)
plt.imshow(im)
plt.show()

dog_bb = [20.0, 15.0, 230, 250.0]
cat_bb = [190.0, 50.0, 325.0, 240.0]

im = plt.imread(img_file_name2)
fig = plt.imshow(im)
fig.axes.add_patch(plt.Rectangle((dog_bb[0], dog_bb[1]), width = dog_bb[2] - dog_bb[0], height = dog_bb[3] - dog_bb[1], fill=False, edgecolor='r', linewidth=2))
fig.axes.add_patch(plt.Rectangle((cat_bb[0], cat_bb[1]), width = cat_bb[2] - cat_bb[0], height = cat_bb[3] - cat_bb[1], fill=False, edgecolor='b', linewidth=2))
plt.show()

img = open(img_file_name2, "rb")
result = computervision_client.detect_objects_in_stream(img, visual_features=[VisualFeatureTypes.objects])
for obj in result.objects:
  if(obj.object_property == "cat"):
    predicted_cat_bb = [obj.rectangle.x, obj.rectangle.y, obj.rectangle.x + obj.rectangle.w, obj.rectangle.y + obj.rectangle.h]

err = 0
for v in zip(predicted_cat_bb, cat_bb):
  err += (v[0] - v[1])**2
err /= 4
print("Error: ", err)

im = plt.imread(img_file_name2)
fig = plt.imshow(im)
fig.axes.add_patch(plt.Rectangle(xy = (dog_bb[0], dog_bb[1]), width = dog_bb[2] - dog_bb[0], height = dog_bb[3] - dog_bb[1], fill=False, edgecolor='r', linewidth=2))
fig.axes.add_patch(plt.Rectangle(xy = (cat_bb[0], cat_bb[1]), width = cat_bb[2] - cat_bb[0], height = cat_bb[3] - cat_bb[1], fill=False, edgecolor='b', linewidth=2))
fig.axes.add_patch(plt.Rectangle(xy = (predicted_cat_bb[0], predicted_cat_bb[1]), width = predicted_cat_bb[2] - predicted_cat_bb[0], height = predicted_cat_bb[3] - predicted_cat_bb[1], fill=False, edgecolor='g', linewidth=2))
plt.show()

"""**Problema 1**

Sa se foloseasca un algoritm de clasificare a imaginilor (etapa de inferenta/testare) si sa se stabileasca performanta acestui algoritm de clasificare binara (imagini cu biciclete vs. imagini fara biciclete).
"""

import requests
import shutil

def download_image(url, file_name):
  """
  Download an image from a URL and save it to a file.
  :param url: The URL of the image to download.
  :param file_name: The name of the file to save the image to.
  :return: None
  """
  response = requests.get(url)
  if response.status_code == 200:
    with open(file_name, 'wb') as f:
      f.write(response.content)
  else:
    print(f"Eroare la descarcarea imaginii {file_name}")

def download_images(images_file_names):
  """
  Download images from a list of URLs and save them to files.
  :param images_file_names: A list of tuples containing the URL and file name of each image to download.
  :return: None
  """
  for img_file_name in images_file_names:
    img_url = img_file_name
    download_image(img_url, img_file_name)

images_file_names = ["bike1.jpg", "bike02.jpg", "bike03.jpg", "bike04.jpg", "bike05.jpg",
"bike06.jpg", "bike07.jpg", "bike08.jpg", "bike09.jpg", "bike10.jpg", "traffic01.jpg",
"traffic02.jpg", "traffic03.jpg", "traffic04.jpg", "traffic05.jpg", "traffic06.jpg",
"traffic07.jpg", "traffic08.jpg", "traffic09.jpg", "traffic10.jpg"]
download_images(images_file_names)

"""Clasificarea imaginilor"""

def image_clasification(image_file_name):
  """
  Classify an image using the Azure Computer Vision API.
  :param image_file_name: The name of the image file to classify.
  :return: A dictionary containing the tags and objects detected in the image.
  """
  with open(image_file_name, "rb") as img:
    result = computervision_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.tags, VisualFeatureTypes.objects])
  tags = {}
  objects = {}
  for tag in result.tags:
    if tag.name in tags:
      tags[tag.name] += tag.confidence
    else:
      tags[tag.name] = tag.confidence
  for obj in result.objects:
    objects[obj.object_property] = obj.confidence
  return tags, objects

def images_clasification(images_file_names):
  """
  Classify images using the Azure Computer Vision API.
  :param images_file_names: A list of file names of the images to classify.
  :return: tags and objects for each image.
  """
  for img_file_name in images_file_names:
    tags, objects = image_clasification(img_file_name)
    print(f"Tags for {img_file_name}: {tags}")
    print(f"Objects for {img_file_name}: {objects}")

images_clasification(images_file_names)

"""Clasificare binara - contine sau nu contine bicicleta"""

def object_detection(image_file_name, object_searched):
  """
  Classify image using the Azure Computer Vision API and return a binary classification result depending on an object searched.
  :param images_file_names: A list of file names of the images to classify.
  :param object_searched: The name of the object to search for in the images.
  :return:
  """
  with open(image_file_name, "rb") as img:
    result = computervision_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.tags, VisualFeatureTypes.objects])
  for obj in result.objects:
    if obj.object_property == object_searched:
      return 1, f"{object_searched} detected"
  return 0, f"{object_searched} not detected"

def binary_clasification_object(images_file_names, object_searched):
  """
  Classify images using the Azure Computer Vision API and return a binary classification result depending on an object searched.
  :param images_file_names: A list of file names of the images to classify.
  :param object_searched: The name of the object to search for in the images.
  """
  result_clasificiation = {}
  result_binary = []
  for img_file_name in images_file_names:
    res = object_detection(img_file_name, object_searched)
    result_binary.append(res[0])
    result_clasificiation[img_file_name] = res[1]
  return result_binary, result_clasificiation

object_searched = "bicycle"
print(binary_clasification_object(images_file_names, object_searched)[1])

"""Performanta algoritmului de clasificare binara"""

#version 1
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score

def algorithm_performance(realLabels, computedLabels, labelNames):
  """
  Compute the performance of an algorithm given the real labels and the computed labels.
  :param realLabels: A list of the real labels.
  :param computedLabels: A list of the computed labels.
  :param labelNames: A list of the label names.
  :return: The accuracy, precision and recall of the algorithm.
  """
  cm = confusion_matrix(realLabels, computedLabels, labels = labelNames)
  accuracy = accuracy_score(realLabels, computedLabels)
  precision = precision_score(realLabels, computedLabels, average = None, labels = labelNames)
  recall = recall_score(realLabels, computedLabels, average = None, labels = labelNames)
  return accuracy, float(precision[1]), float(recall[1]), float(precision[0]), float(recall[0])

#version 2
def algorithm_performance_version2(realLabels, computedLabels, pos, neg):
  """
  Compute the performance of an algorithm given the real labels and the computed labels.
  :param realLabels: A list of the real labels.
  :param computedLabels: A list of the computed labels.
  """
  TP = sum([1 if (realLabels[i] == pos and computedLabels[i] == pos) else 0 for i in range(len(realLabels))])
  FP = sum([1 if (realLabels[i] == neg and computedLabels[i] == pos) else 0 for i in range(len(realLabels))])
  TN = sum([1 if (realLabels[i] == neg and computedLabels[i] == neg) else 0 for i in range(len(realLabels))])
  FN = sum([1 if (realLabels[i] == pos and computedLabels[i] == neg) else 0 for i in range(len(realLabels))])

  accuracy = sum([1 if realLabels[i] == computedLabels[i] else 0 for i in range(len(realLabels))]) / len(realLabels)
  precisionPos = TP / (TP + FP) if (TP + FP) != 0 else 0
  recallPos = TP / (TP + FN) if (TP + FN) != 0 else 0
  precisionNeg = TN / (TN + FN) if (TN + FN) != 0 else 0
  recallNeg = TN / (TN + FP) if (TN + FP) != 0 else 0

  return accuracy, precisionPos, recallPos, precisionNeg, recallNeg

realLabels = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
object_searched = "bicycle"
computedLabels = binary_clasification_object(images_file_names, object_searched)[0]
labelNames = [0, 1]

print("Version 1 for algorithm performance")
res = algorithm_performance(realLabels, computedLabels, labelNames)
print("Accuracy: ", res[0])
print("Precision: ", res[1])
print("Recall: ", res[2])
print("Precision neg: ", res[3])
print("Recall neg: ", res[4])

print("Version 2 for algorithm performance")
res = algorithm_performance_version2(realLabels, computedLabels, 1, 0)
print("Accuracy: ", res[0])
print("Precision: ", res[1])
print("Recall: ", res[2])
print("Precision neg: ", res[3])
print("Recall neg: ", res[4])

"""**Problema 2**

Pentru imaginile care contin biciclete:

a. sa se localizeze automat bicicletele in aceste imagini si sa se evidentieze chenarele care incadreaza bicicletele

b. sa se eticheteze (fara ajutorul algoritmilor de AI) aceste imagini cu chenare care sa incadreze cat mai exact bicicletele. Care task dureaza mai mult (cel de la punctul a sau cel de la punctul b)?

c. sa se determine performanta algoritmului de la punctul a avand in vedere etichetarile realizate la punctul b (se vor folosi cel putin 2 metrici).

a. sa se localizeze automat bicicletele in aceste imagini si sa se evidentieze chenarele care incadreaza bicicletele
"""

from math import e

def draw_object(result, image):
  """
  Draw an object in an image using the Azure Computer Vision API.
  :param result: The result of the image analysis.
  :return: draw object
  """
  fig = plt.imshow(image)
  for obj in result.objects:
    if obj.object_property == "bicycle":
      location = obj.rectangle
      fig.axes.add_patch(plt.Rectangle(xy = (location.x, location.y), width = location.w, height = location.h, fill=False, edgecolor='r', linewidth=2))
      return [location.x, location.y, location.x + location.w, location.y + location.h]
  return [0, 0, 0, 0]

def localization_images(images_file_names):
  result_bbox = {}
  for img_file_name in images_file_names:
    with open(img_file_name, "rb") as img:
      result = computervision_client.detect_objects_in_stream(img, visual_features=[VisualFeatureTypes.objects])
    im = plt.imread(img_file_name)
    result_bbox[img_file_name] = draw_object(result, im)
    plt.show()

  return result_bbox


images_file_names_with_bicycles = ["bike1.jpg", "bike02.jpg", "bike03.jpg", "bike04.jpg", "bike05.jpg",
"bike06.jpg", "bike07.jpg", "bike08.jpg", "bike09.jpg", "bike10.jpg"]
predicted_boundig_box = localization_images(images_file_names_with_bicycles)
print("predicted_boundig_box): ", predicted_boundig_box)

"""
b. sa se eticheteze (fara ajutorul algoritmilor de AI) aceste imagini cu chenare care sa incadreze cat mai exact bicicletele. Care task dureaza mai mult (cel de la punctul a sau cel de la punctul b)?
"""

from google.colab import files
uploaded = files.upload()

import pandas as pd

def manual_images_localization(file_csv):
  """
  Draw an object in an image using manual localizarion.
  :param file_csv: The csv file with the manual localization stored.
  :return: draw object
  """

  df = pd.read_csv("bike_detection_2025-03-23-11-01-51.csv")
  result = {}
  for img_file_name in df['image_name']:
    img = open(img_file_name, "rb")
    im = plt.imread(img_file_name)
    fig = plt.imshow(im)

    row = df[df['image_name'] == img_file_name].iloc[0]
    bbox_x = row['bbox_x']
    bbox_y = row['bbox_y']
    bbox_w = row['bbox_width']
    bbox_h = row['bbox_height']

    result[img_file_name] = [float(bbox_x), float(bbox_y), float(bbox_w), float(bbox_h)]

    fig.axes.add_patch(plt.Rectangle(xy = (bbox_x, bbox_y), width = bbox_w, height = bbox_h, fill=False, edgecolor='r', linewidth=2))
    plt.show()
  return result

real_bounding_box = manual_images_localization(uploaded)
print("real_bounding_box: ", real_bounding_box)

"""c. sa se determine performanta algoritmului de la punctul a avand in vedere etichetarile realizate la punctul b (se vor folosi cel putin 2 metrici)."""

def calculate_iou(pred_bbox, real_bbox, image):
  """
  Calculate the Intersection over Union (IoU) between two bounding boxes.
  :param pred_bbox: The predicted bounding box.
  :param real_bbox: The real bounding box.
  :param image: The image.
  :return: The IoU between the two bounding boxes.
  """
  x_max = max(pred_bbox[img][0], real_bbox[img][0])
  y_max = max(pred_bbox[img][1], real_bbox[img][1])
  x_min = min(pred_bbox[img][2], real_bbox[img][2])
  y_min = min(pred_bbox[img][3], real_bbox[img][3])
  intersection = max(0, x_min - x_max) * max(0, y_min - y_max)

  area_pred_bbox = (pred_bbox[img][2] - pred_bbox[img][0] + 1) * (pred_bbox[img][3] - pred_bbox[img][1] + 1)
  area_real_bbox = (real_bbox[img][2] - real_bbox[img][0] + 1) * (real_bbox[img][3] - real_bbox[img][1] + 1)

  union = area_pred_bbox + area_real_bbox - intersection

  iou = intersection / union
  return iou

def calculate_iou_for_all_images(pred_bbox, real_bbox, images_file_names_with_bicycles):
  """
  Calculate the IoU between the predicted and real bounding boxes for all images.
  :param pred_bbox: The predicted bounding box.
  :param real_bbox: The real bounding box.
  :param images_file_names_with_bicycles: The list of images with bicycles.
  :return: The IoU between the two bounding boxes for each image.
  """
  for img in images_file_names_with_bicycles:
    iou = calculate_iou(pred_bbox, real_bbox, img)
    print(f"IOU for {img}: {iou}")

calculate_iou(predicted_boundig_box, real_bounding_box, images_file_names_with_bicycles)

def evaluate_algorithm_performance(pred_bbox, real_bbox, real_detection, images_file_names_with_bicycles, threshold = 0.5):
  """
  Evaluate the performance of the algorithm by calculating the accuracy, precision, recall, and F1 score.
  :param pred_bbox: The predicted bounding box.
  :param real_bbox: The real bounding box.
  :param real_detection: The real detection.
  :param images_file_names_with_bicycles: The list of images with bicycles.
  :return: The accuracy, precision, recall, and F1 score for each image.
  """
  for img in images_file_names_with_bicycles:
    TP = FP = FN = TN = 0
    x_max = max(pred_bbox[img][0], real_bbox[img][0])
    y_max = max(pred_bbox[img][1], real_bbox[img][1])
    x_min = min(pred_bbox[img][2], real_bbox[img][2])
    y_min = min(pred_bbox[img][3], real_bbox[img][3])
    intersection = max(0, x_min - x_max) * max(0, y_min - y_max)

    area_pred_bbox = (pred_bbox[img][2] - pred_bbox[img][0] + 1) * (pred_bbox[img][3] - pred_bbox[img][1] + 1)
    area_real_bbox = (real_bbox[img][2] - real_bbox[img][0] + 1) * (real_bbox[img][3] - real_bbox[img][1] + 1)

    union = area_pred_bbox + area_real_bbox - intersection

    iou = intersection / union
    if real_detection[img] == 1:
      if iou > threshold:
        TP += 1
      else:
        FN += 1
    else:
      if iou > threshold:
        FP += 1
      else:
        TN += 1

    accuracy = (TP + TN) / (TP + TN + FP + FN) if (TP + TN + FP + FN) != 0 else 0
    precision = TP / (TP + FP) if (TP + FP) != 0 else 0
    recall = TP / (TP + FN) if (TP + FN) != 0 else 0
    f1_score = 2 * precision * recall / (precision + recall) if (precision + recall) != 0 else 0

    print(f"Image {img}")
    print(f"Accuracy for {img}: {accuracy}")
    print(f"Precision for {img}: {precision}")
    print(f"Recall for {img}: {recall}")
    print(f"F1 score for {img}: {f1_score}")

real_detection = {'bike1.jpg': 1, 'bike10.jpg': 1, 'bike02.jpg': 1, 'bike03.jpg': 1, 'bike04.jpg': 1, 'bike05.jpg': 1, 'bike06.jpg': 1, 'bike07.jpg': 1, 'bike08.jpg': 1, 'bike09.jpg': 1}
evaluate_algorithm_performance(predicted_boundig_box, real_bounding_box, real_detection, images_file_names_with_bicycles)


    
