# -*- coding: utf-8 -*-
"""laborator5.ipynb

Problema 1
"""

!pip install pandas scipy
from scipy.stats import pearsonr

import csv
import matplotlib.pyplot as plt
import os
import io
import requests
import pandas as pd
import numpy as np

from sklearn import linear_model
from sklearn.metrics import accuracy_score
from sklearn.metrics import mean_squared_error
from sklearn import linear_model

"""**Coeficientul Pearsonr**

Interpretarea valorilor:

r = 1: Corelație perfectă pozitivă (variabilele cresc împreună într-o manieră perfect liniară).

r = -1: Corelație perfectă negativă (când una dintre variabile crește, cealaltă scade într-o manieră perfect liniară).

r = 0: Nu există nicio corelație liniară între cele două variabile.

0 < r < 1: Corelație pozitivă, dar nu perfectă.

-1 < r < 0: Corelație negativă, dar nu perfectă.
"""

def get_correlation_between_columns(file_name):
  url = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab05/data/" + file_name
  !wget -O {file_name} {url}
  file_path = os.path.join(os.getcwd(), file_name)

  df = pd.read_csv(file_name)

  col1 = df['Economy..GDP.per.Capita.']
  col2 = df['Freedom']

  correlation, _ = pearsonr(col1, col2)

  print(f'Coeficientul Pearsonr între cele două coloane pentru fisierul:{file_name} este: {correlation}')

get_correlation_between_columns("v1_world-happiness-report-2017.csv")
get_correlation_between_columns("v2_world-happiness-report-2017.csv")
get_correlation_between_columns("v3_world-happiness-report-2017.csv")

"""**CU TOOL**

**Ce îi poate face pe oameni fericiți?**

Se consideră problema predicției gradului de fericire a populației globului folosind informații despre diferite caracteristici a bunăstării respectivei populații precum Produsul intern brut al țării în care locuiesc (gross domestic product – GBP), gradul de fericire, etc.

Folsind datele aferente anului 2017, fisierul v1_world-happiness-report-2017.csv, să se realizeze o predicție a gradului de fericire în funcție:

**a)** doar de Produsul intern brut
"""

def load_data(file_name, input_variab_name, output_variab_name):
  """
  Returneaza datele input si output dintr-un fisier csv
  :param file_name: numele fisierului csv
  :param input_variab_name: numele variabilei input
  :param output_variab_name: numele variabilei output
  :return: datele input si output
  """
  data = []
  data_names = []
  with open(file_name) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
      if line_count == 0:
        data_names = row
      else:
        data.append(row)
      line_count += 1

  selected_variable = data_names.index(input_variab_name)
  inputs = [float(data[i][selected_variable]) if data[i][selected_variable] != '' else np.nan for i in range(len(data))]
  selected_output = data_names.index(output_variab_name)
  outputs = [float(data[i][selected_output]) if data[i][selected_output] != '' else np.nan for i in range(len(data))]

  inputs_mean = np.nanmean(inputs)
  inputs = [inputs_mean if np.isnan(x) else x for x in inputs]

  outputs_mean = np.nanmean(outputs)
  outputs = [outputs_mean if np.isnan(x) else x for x in outputs]
  return inputs, outputs

def plot_data_histogram(x, variable_name):
  """
  Afiseaza histograma datelor
  :param x: datele
  :param variable_name: numele variabilei
  :return: histograma datelor
  """
  n, bins, patches = plt.hist(x, 10)
  plt.title("Histogramm of " + variable_name)
  plt.show()

def plot_data(trainingInp, trainingOut, learntInp = None, learntOut = None, testInp = None, testOut = None, title = None):
  """
  Afiseaza datele de antrenare, de validare si de testare
  :param trainingInp: datele de antrenare input
  :param trainingOut: datele de antrenare output
  :param learntInp: datele de validare input
  :param learntOut: datele de validare output
  :param testInp: datele de test input
  :param testOut: datele de test output
  :param title: titlul graficului
  """
  plt.plot(trainingInp, trainingOut, 'ro', label = 'training data')
  if (learntInp):
    plt.plot(learntInp, learntOut, 'b-', label = 'validation data')
  if (testInp):
    plt.plot(testInp, testOut, 'g^', label = 'computed test data')
  plt.title(title)
  plt.legend()
  plt.show()

def hapiness_prediction_depending_one_variable_with_tool(file_name, input_variable, output_variable):
  """
  Realizarea predictiei gradului de fericire în funcție de o variabila input
  :param file_name: numele fisierului csv
  :param input_variable: numele variabilei input
  :param output_variable: numele variabilei output
  :return: predictiei gradului de fericire în funcție de o variabila input
  """
  #descarc fisierul csv
  file_path = os.path.join(os.getcwd(), file_name)

  #extrag datele input si output
  inputs, outputs = load_data(file_path, input_variable, output_variable)

  #Pasul 1 - plot pt distributia datelor & plot pt “verificarea” liniaritatii
  # (daca legatura intre y si x e una liniara)
  plot_data_histogram(inputs, input_variable)
  plot_data_histogram(outputs, output_variable)

  titleplt = input_variable + " vs. " + output_variable
  plot_data(inputs, outputs, [], [], [], [], titleplt)

  #Pasul 2 - impartire date pe train si validation
  np.random.seed(5)
  indexes = [i for i in range(len(inputs))]
  train_sample = np.random.choice(indexes, size=int(0.8 * len(inputs)), replace=False)
  validation_sample = [i for i in indexes if not i in train_sample]
  train_inputs = [inputs[i] for i in train_sample]
  train_outputs = [outputs[i] for i in train_sample]
  validation_inputs = [inputs[i] for i in validation_sample]
  validation_outputs = [outputs[i] for i in validation_sample]

  #plot_data(train_inputs, train_outputs, [], [], validation_inputs, validation_outputs, 'train and test data')


  #Pasul 3 - invatare model (cu tool generic si cu tool de least square)
  xx = [[el] for el in train_inputs]
  regressor = linear_model.LinearRegression()
  regressor.fit(xx, train_outputs)
  w0, w1 = regressor.intercept_, regressor.coef_

  print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x')

  #Pasul 4 - plot rezultate (model invatat, predictii)
  #model
  no_of_points = 1000
  x_ref = []
  val = min(train_inputs)
  step = (max(train_inputs) - min(train_inputs)) / no_of_points
  for i in range(no_of_points):
    x_ref.append(val)
    val += step
  y_ref = [w0 + w1 * el for el in x_ref]
  plot_data(train_inputs, train_outputs, x_ref, y_ref, [], [], title = 'train data and model')

  #predictii
  computed_validation_outputs = regressor.predict([[x] for x in validation_inputs])

  #plot_data([], [], validation_inputs, computed_validation_outputs, validation_inputs, validation_outputs, 'predictions vs real test data')

  #Pasul 5 - calcul metrici de performanta (eroarea)
  error = mean_squared_error(validation_outputs, computed_validation_outputs)
  print("prediction error(tool): ", error)

print("Pentru fisierul v1_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v1_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

print("Pentru fisierul v2_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v2_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

print("Pentru fisierul v3_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v3_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

"""**b)** doar de caracteristica "Family"
"""

print("Pentru fisierul v1_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v1_world-happiness-report-2017.csv', 'Family', 'Happiness.Score')

print("Pentru fisierul v2_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v2_world-happiness-report-2017.csv', 'Family', 'Happiness.Score')

print("Pentru fisierul v3_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool('v3_world-happiness-report-2017.csv', 'Family', 'Happiness.Score')

"""**c)** de Produsul intern brut si de gradul de libertate"""

import csv
import os
import numpy as np
from sklearn import linear_model
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

def load_data(file_name, input_var1_name, input_var2_name, output_var_name):
    data = []
    data_names = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                data_names = row
            else:
                data.append(row)
            line_count += 1
    input_var1_index = data_names.index(input_var1_name)
    input_var2_index = data_names.index(input_var2_name)
    output_var_index = data_names.index(output_var_name)

    inputs1 = [float(data[i][input_var1_index]) if data[i][input_var1_index] != '' else np.nan for i in range(len(data))]
    inputs2 = [float(data[i][input_var2_index]) if data[i][input_var2_index] != '' else np.nan for i in range(len(data))]
    outputs = [float(data[i][output_var_index]) if data[i][output_var_index] != '' else np.nan for i in range(len(data))]

    inputs_mean1 = np.nanmean(inputs1)
    inputs1 = [inputs_mean1 if np.isnan(x) else x for x in inputs1]

    inputs_mean2 = np.nanmean(inputs2)
    inputs2 = [inputs_mean2 if np.isnan(x) else x for x in inputs2]

    outputs_mean = np.nanmean(outputs)
    outputs = [outputs_mean if np.isnan(x) else x for x in outputs]

    return inputs1, inputs2, outputs

def plot_data_histogram(x, variable_name):
    n, bins, patches = plt.hist(x, 10)
    plt.title("Histogram of " + variable_name)
    plt.show()

def plot_data(trainingInp1, trainingInp2, trainingOut, learntInp1=None, learntInp2=None, learntOut=None, testInp1=None, testInp2=None, testOut=None, title=None):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(trainingInp1, trainingInp2, trainingOut, c='r', marker='o', label='training data')
    if learntInp1 is not None and learntInp2 is not None and len(learntInp1) > 0 and len(learntInp2) > 0:
        ax.scatter(learntInp1, learntInp2, learntOut, c='b', marker='o', label='validation data')
    if testInp1 is not None and testInp2 is not None and len(testInp1) > 0 and len(testInp2) > 0:
        ax.scatter(testInp1, testInp2, testOut, c='g', marker='^', label='computed test data')
    ax.set_title(title)
    ax.legend()
    plt.show()



def happiness_prediction_depending_two_variables_with_tool(file_name, input_var1, input_var2, output_var):
     #descarc fisierul csv
    file_path = os.path.join(os.getcwd(), file_name)

    #extrag datele input si output
    inputs1, inputs2, outputs = load_data(file_path, input_var1, input_var2, output_var)

    #Pasul 1 - plot pt distributia datelor & plot pt “verificarea” liniaritatii
    # (daca legatura intre y si x e una liniara)
    plot_data_histogram(inputs1, input_var1)
    plot_data_histogram(inputs2, input_var2)
    plot_data_histogram(outputs, output_var)

    titleplt = input_var1 + " and " + input_var2 + " vs. " + output_var
    plot_data(inputs1, inputs2, outputs, [], [], [], [], [], titleplt)

    #Pasul 2 - impartire date pe train si validation
    np.random.seed(5)
    indexes = [i for i in range(len(inputs1))]
    train_sample = np.random.choice(indexes, size=int(0.8 * len(inputs1)), replace=False)
    validation_sample = [i for i in indexes if not i in train_sample]
    train_inputs1 = [inputs1[i] for i in train_sample]
    train_inputs2 = [inputs2[i] for i in train_sample]
    train_outputs = [outputs[i] for i in train_sample]
    validation_inputs1 = [inputs1[i] for i in validation_sample]
    validation_inputs2 = [inputs2[i] for i in validation_sample]
    validation_outputs = [outputs[i] for i in validation_sample]

    plot_data(train_inputs1, train_inputs2, train_outputs, [], [], [], validation_inputs1, validation_inputs2, validation_outputs, 'train and test data')

    #Pasul 3 - invatare model (cu tool generic si cu tool de least square)
    xx = [[el1, el2] for el1, el2 in zip(train_inputs1, train_inputs2)]
    regressor = linear_model.LinearRegression()
    regressor.fit(xx, train_outputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]

    print('the learnt model: f(x1, x2) = ', w0, ' + ', w1, ' * x1 + ', w2, ' * x2')

    # Calculate R-squared value
    r_squared = regressor.score(xx, train_outputs)
    print('R-squared: ', r_squared)

    #Pasul 4 - plot rezultate (model invatat, predictii)
    #model
    no_of_points = 1000
    x1_ref = np.linspace(min(train_inputs1), max(train_inputs1), no_of_points)
    x2_ref = np.linspace(min(train_inputs2), max(train_inputs2), no_of_points)
    y_ref = [w0 + w1 * x1 + w2 * x2 for x1, x2 in zip(x1_ref, x2_ref)]
    plot_data(train_inputs1, train_inputs2, train_outputs, x1_ref, x2_ref, y_ref, [], [], title='train data and model')

    #predictii
    computed_validation_outputs = regressor.predict([[x1, x2] for x1, x2 in zip(validation_inputs1, validation_inputs2)])
    plot_data([], [], [], validation_inputs1, validation_inputs2, computed_validation_outputs, validation_inputs1, validation_inputs2, validation_outputs, 'predictions vs real test data')

    #Pasul 5 - calcul metrici de performanta (eroarea)
    error = mean_squared_error(validation_outputs, computed_validation_outputs)
    print("prediction error(tool): ", error)

print("Pentru fisierul v1_world-happiness-report-2017.csv")
happiness_prediction_depending_two_variables_with_tool('v1_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')

import csv
import os
import numpy as np
from sklearn import linear_model
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

def load_data_v2(file_name, input_var1_name, input_var2_name, output_var_name):
    data = []
    data_names = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                data_names = row
            else:
                data.append(row)
            line_count += 1
    input_var1_index = data_names.index(input_var1_name)
    input_var2_index = data_names.index(input_var2_name)
    output_var_index = data_names.index(output_var_name)

    inputs1 = [float(data[i][input_var1_index]) if data[i][input_var1_index] != '' else np.nan for i in range(len(data))]
    inputs2 = [float(data[i][input_var2_index]) if data[i][input_var2_index] != '' else np.nan for i in range(len(data))]
    outputs = [float(data[i][output_var_index]) if data[i][output_var_index] != '' else np.nan for i in range(len(data))]

    inputs_mean1 = np.nanmean(inputs1)
    inputs1 = [inputs_mean1 if np.isnan(x) else x for x in inputs1]

    inputs_mean2 = np.nanmean(inputs2)
    inputs2 = [inputs_mean2 if np.isnan(x) else x for x in inputs2]

    inputs = [inputs1[i] + inputs2[i] for i in range(len(inputs1))]

    outputs_mean = np.nanmean(outputs)
    outputs = [outputs_mean if np.isnan(x) else x for x in outputs]

    return inputs, outputs

def plot_data_histogram_v2(x, variable_name):
  """
  Afiseaza histograma datelor
  :param x: datele
  :param variable_name: numele variabilei
  :return: histograma datelor
  """
  n, bins, patches = plt.hist(x, 10)
  plt.title("Histogramm of " + variable_name)
  plt.show()

def plot_data_v2(trainingInp, trainingOut, learntInp = None, learntOut = None, testInp = None, testOut = None, title = None):
  """
  Afiseaza datele de antrenare, de validare si de testare
  :param trainingInp: datele de antrenare input
  :param trainingOut: datele de antrenare output
  :param learntInp: datele de validare input
  :param learntOut: datele de validare output
  :param testInp: datele de test input
  :param testOut: datele de test output
  :param title: titlul graficului
  """
  plt.plot(trainingInp, trainingOut, 'ro', label = 'training data')
  if (learntInp):
    plt.plot(learntInp, learntOut, 'b-', label = 'validation data')
  if (testInp):
    plt.plot(testInp, testOut, 'g^', label = 'computed test data')
  plt.title(title)
  plt.legend()
  plt.show()


def hapiness_prediction_depending_one_variable_with_tool_v2(file_name, input_variable1, input_variable2, output_variable):
  """
  Realizarea predictiei gradului de fericire în funcție de o variabila input
  :param file_name: numele fisierului csv
  :param input_variable: numele variabilei input
  :param output_variable: numele variabilei output
  :return: predictiei gradului de fericire în funcție de o variabila input
  """
  #descarc fisierul csv
  file_path = os.path.join(os.getcwd(), file_name)

  #extrag datele input si output
  inputs, outputs = load_data_v2(file_path, input_variable1, input_variable2, output_variable)

  #Pasul 1 - plot pt distributia datelor & plot pt “verificarea” liniaritatii
  # (daca legatura intre y si x e una liniara)
  input_variable = input_variable1 + " + " + input_variable2
  plot_data_histogram_v2(inputs, input_variable)
  plot_data_histogram_v2(outputs, output_variable)

  titleplt = input_variable + " vs. " + output_variable
  plot_data_v2(inputs, outputs, [], [], [], [], titleplt)

  #Pasul 2 - impartire date pe train si validation
  np.random.seed(5)
  indexes = [i for i in range(len(inputs))]
  train_sample = np.random.choice(indexes, size=int(0.8 * len(inputs)), replace=False)
  validation_sample = [i for i in indexes if not i in train_sample]
  train_inputs = [inputs[i] for i in train_sample]
  train_outputs = [outputs[i] for i in train_sample]
  validation_inputs = [inputs[i] for i in validation_sample]
  validation_outputs = [outputs[i] for i in validation_sample]

  plot_data_v2(train_inputs, train_outputs, [], [], validation_inputs, validation_outputs, 'train and test data')


  #Pasul 3 - invatare model (cu tool generic si cu tool de least square)
  xx = [[el] for el in train_inputs]
  regressor = linear_model.LinearRegression()
  regressor.fit(xx, train_outputs)
  w0, w1 = regressor.intercept_, regressor.coef_

  print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x')

  #Pasul 4 - plot rezultate (model invatat, predictii)
  #model
  no_of_points = 1000
  x_ref = []
  val = min(train_inputs)
  step = (max(train_inputs) - min(train_inputs)) / no_of_points
  for i in range(no_of_points):
    x_ref.append(val)
    val += step
  y_ref = [w0 + w1 * el for el in x_ref]
  plot_data_v2(train_inputs, train_outputs, x_ref, y_ref, [], [], title = 'train data and model')

  #predictii
  computed_validation_outputs = regressor.predict([[x] for x in validation_inputs])

  plot_data_v2([], [], validation_inputs, computed_validation_outputs, validation_inputs, validation_outputs, 'predictions vs real test data')

  #Pasul 5 - calcul metrici de performanta (eroarea)
  error = mean_squared_error(validation_outputs, computed_validation_outputs)
  print("prediction error(tool): ", error)

print("Pentru fisierul v2_world-happiness-report-2017.csv")
hapiness_prediction_depending_one_variable_with_tool_v2('v2_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')

print("Pentru fisierul v3_world-happiness-report-2017.csv")
happiness_prediction_depending_two_variables_with_tool('v3_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')

"""**FĂRĂ TOOL**

**Ce îi poate face pe oameni fericiți?** Se consideră problema predicției gradului de fericire a populației globului folosind informații despre diferite caracteristici a bunăstării respectivei populații precum Produsul intern brut al țării în care locuiesc (gross domestic product – GBP), gradul de fericire, etc.

Folsind datele aferente anului 2017 să se realizeze o predicție a gradului de fericire în funcție:

**a)** doar de Produsul intern brut
"""

import numpy as np
from math import exp
from math import log2
from numpy.linalg import inv

def load_data(file_name, input_variab_name, output_variab_name):
  """
  Returneaza datele input si output dintr-un fisier csv
  :param file_name: numele fisierului csv
  :param input_variab_name: numele variabilei input
  :param output_variab_name: numele variabilei output
  :return: datele input si output
  """
  data = []
  data_names = []
  with open(file_name) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
      if line_count == 0:
        data_names = row
      else:
        data.append(row)
      line_count += 1
  selected_variable = data_names.index(input_variab_name)
  inputs = [float(data[i][selected_variable]) if data[i][selected_variable] != '' else np.nan for i in range(len(data))]
  selected_output = data_names.index(output_variab_name)
  outputs = [float(data[i][selected_output]) if data[i][selected_output] != '' else np.nan for i in range(len(data))]
  return inputs, outputs

def plot_data_histogram(x, variable_name):
  """
  Afiseaza histograma datelor
  :param x: datele
  :param variable_name: numele variabilei
  :return: histograma datelor
  """
  n, bins, patches = plt.hist(x, 10)
  plt.title("Histogramm of " + variable_name)
  plt.show()

def plot_data(trainingInp, trainingOut, learntInp = None, learntOut = None, testInp = None, testOut = None, title = None):
  """
  Afiseaza datele de antrenare, de validare si de testare
  :param trainingInp: datele de antrenare input
  :param trainingOut: datele de antrenare output
  :param learntInp: datele de validare input
  :param learntOut: datele de validare output
  :param testInp: datele de test input
  :param testOut: datele de test output
  :param title: titlul graficului
  """
  plt.plot(trainingInp, trainingOut, 'ro', label = 'training data')
  if (learntInp):
    plt.plot(learntInp, learntOut, 'b-', label = 'validation data')
  if (testInp):
    plt.plot(testInp, testOut, 'g^', label = 'computed test data')
  plt.title(title)
  plt.legend()
  plt.show()

class MyLinearUnivarRegression:
  def __init__(self):
    self.intercept_ = 0.0
    self.coef_ = 0.0

  def fit(self, x, y):
    sx = sum(x)
    sy = sum(y)
    sxx = sum([i * i for i in x])
    sxy = sum(i * j for (i, j) in zip(x, y))
    w1 = (len(x) * sxy - sx * sy) / (len(x) * sxx - sx * sx)
    w0 = (sy - w1 * sx) / len(x)
    self.intercept_ = w0
    self.coef_ = w1

  def predict(self, x):
    if (isinstance(x[0], list)):
      return [self.intercept_ + self.coef_ * i[0] for i in x]
    else:
      return [self.intercept_ + self.coef_ * i for i in x]

def hapiness_prediction_depending_one_variable_without_tool(file_name, input_variable, output_variable):
  #descarc fisierul csv
  url = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab05/data/" + file_name
  !wget -O {file_name} {url}
  file_path = os.path.join(os.getcwd(), file_name)

  #extrag datele input si output
  inputs, outputs = load_data(file_path, input_variable, output_variable)

  #Pasul 1 - plot pt distributia datelor & plot pt “verificarea” liniaritatii
  # (daca legatura intre y si x e una liniara)
  plot_data_histogram(inputs, input_variable)
  plot_data_histogram(outputs, output_variable)

  titleplt = input_variable + " vs. " + output_variable
  plot_data(inputs, outputs, [], [], [], [], titleplt)

  #Pasul 2 - impartire date pe train si validation
  np.random.seed(5)
  indexes = [i for i in range(len(inputs))]
  train_sample = np.random.choice(indexes, size=int(0.8 * len(inputs)), replace=False)
  validation_sample = [i for i in indexes if not i in train_sample]
  train_inputs = [inputs[i] for i in train_sample]
  train_outputs = [outputs[i] for i in train_sample]
  validation_inputs = [inputs[i] for i in validation_sample]
  validation_outputs = [outputs[i] for i in validation_sample]

  plot_data(train_inputs, train_outputs, [], [], validation_inputs, validation_outputs, 'train and test data')


  #Pasul 3 - invatare model (cu tool generic si cu tool de least square)
  mylineareg = MyLinearUnivarRegression()
  mylineareg.fit(train_inputs, train_outputs)
  computed_validation_outputs = mylineareg.predict(validation_inputs)
  w0 = mylineareg.intercept_
  w1 = mylineareg.coef_

  print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x')

  #Pasul 4 - plot rezultate (model invatat, predictii)
  #model
  no_of_points = 1000
  x_ref = []
  val = min(train_inputs)
  step = (max(train_inputs) - min(train_inputs)) / no_of_points
  for i in range(no_of_points):
    x_ref.append(val)
    val += step
  y_ref = [w0 + w1 * el for el in x_ref]
  plot_data(train_inputs, train_outputs, x_ref, y_ref, [], [], title = 'train data and model')

  #predictii
  computed_validation_outputs = [w0 + w1 * el for el in validation_inputs]
  plot_data([], [], validation_inputs, computed_validation_outputs, validation_inputs, validation_outputs, 'predictions vs real test data')

  #Pasul 5 - calcul metrici de performanta (eroarea)
  error = 0.0
  for t1, t2 in zip(computed_validation_outputs, validation_outputs):
    error += (t1 - t2) ** 2
  error = error / len(validation_outputs)
  print("prediction error (manual): ", error)

hapiness_prediction_depending_one_variable_without_tool('v1_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

"""**b)** doar de caracteristica "Family"
"""

hapiness_prediction_depending_one_variable_without_tool('v1_world-happiness-report-2017.csv', 'Family', 'Happiness.Score')

"""**c)** de Produsul intern brut si de gradul de libertate"""

def load_data_general(file_name, feature_names, output_variable):
    data = []
    data_names = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                data_names = row
                data_names = [name.strip() for name in data_names]
            else:
                data.append(row)
            line_count += 1
    inputs = []
    for i in range(len(data)):
        crt_example = []
        for feature in feature_names:
            selected_variable = data_names.index(feature)
            crt_example.append(data[i][selected_variable])
        inputs.append(crt_example)

    selected_output = data_names.index(output_variable)
    outputs = []
    for i in range(len(data)):
        outputs.append(data[i][selected_output])

    return inputs, outputs

def from_string_to_numeric(values):
    if isinstance(values[0], list):
        aux = []
        for i in range(len(values)):
            line = []
            for j in range(len(values[i])):
                line.append(float(values[i][j]))
            aux.append(line)
        return aux
    else:
        aux = []
        for i in range(len(values)):
            aux.append(float(values[i]))
        return aux

def get_feature(data, pos):
    values = []
    for i in range(len(data)):
        values.append(data[i][pos])
    return values

def plot_data_histogram(x, variable_name):
    n, bins, patches = plt.hist(x, 10)
    plt.title("Histogram of " + variable_name)
    plt.show()

def plot_data(trainingInp1, trainingInp2, trainingOut, learntInp1=None, learntInp2=None, learntOut=None, testInp1=None, testInp2=None, testOut=None, title=None):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(trainingInp1, trainingInp2, trainingOut, c='r', marker='o', label='training data')
    if learntInp1 is not None and learntInp2 is not None and len(learntInp1) > 0 and len(learntInp2) > 0:
        ax.scatter(learntInp1, learntInp2, learntOut, c='b', marker='o', label='validation data')
    if testInp1 is not None and testInp2 is not None and len(testInp1) > 0 and len(testInp2) > 0:
        ax.scatter(testInp1, testInp2, testOut, c='g', marker='^', label='computed test data')
    ax.set_title(title)
    ax.legend()
    plt.show()

class MyLinearBivarRegression:
  def __init__(self):
      self.intercept_ = 0.0
      self.coef_ = [0.0, 0.0]

  def fit(self, x1, x2, y):
      n = len(y)
      sx1 = sum(x1)
      sx2 = sum(x2)
      sy = sum(y)
      sxx1 = sum([i * i for i in x1])
      sxx2 = sum([i * i for i in x2])
      sx1x2 = sum([i * j for (i, j) in zip(x1, x2)])
      sx1y = sum([i * j for (i, j) in zip(x1, y)])
      sx2y = sum([i * j for (i, j) in zip(x2, y)])

      denominator = n * sxx1 * sxx2 - sx1 * sx1 * sxx2 - n * sx1x2 * sx1x2 + sx1 * sx2 * sx1x2
      w1 = (n * sx1y * sxx2 - sy * sx1 * sxx2 - n * sx1x2 * sx2y + sx1 * sx2 * sx2y) / denominator
      w2 = (n * sx2y * sxx1 - sy * sx2 * sxx1 - sx1 * sx1 * sx2y + sx1 * sx1x2 * sy) / denominator
      w0 = (sy - w1 * sx1 - w2 * sx2) / n

      self.intercept_ = w0
      self.coef_ = [w1, w2]

  def predict(self, x):
      if isinstance(x[0], list):
          return [self.intercept_ + self.coef_[0] * i[0] + self.coef_[1] * i[1] for i in x]
      else:
          return [self.intercept_ + self.coef_[0] * i for i in x]

def happiness_prediction_depending_two_variables_without_tool(file_name, input_var1, input_var2, output_var):
    # Download the CSV file
    url = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab05/data/" + file_name
    !wget -O {file_name} {url}
    file_path = os.path.join(os.getcwd(), file_name)

    # Extract input and output data using load_data_general
    inputs, outputs = load_data_general(file_path, [input_var1, input_var2], output_var)

    # Convert data to numeric using from_string_to_numeric
    inputs = from_string_to_numeric(inputs)
    outputs = from_string_to_numeric(outputs)

    # Step 1: Plot histograms and scatter plot
    plot_data_histogram(get_feature(inputs, 0), input_var1)
    plot_data_histogram(get_feature(inputs, 1), input_var2)
    plot_data_histogram(outputs, output_var)

    titleplt = input_var1 + " and " + input_var2 + " vs. " + output_var
    plot_data(get_feature(inputs, 0), get_feature(inputs, 1), outputs, [], [], [], [], [], titleplt)

    # Step 2: Split data into train and validation sets
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    train_sample = np.random.choice(indexes, size=int(0.8 * len(inputs)), replace=False)
    validation_sample = [i for i in indexes if not i in train_sample]
    train_inputs = [inputs[i] for i in train_sample]
    train_outputs = [outputs[i] for i in train_sample]
    validation_inputs = [inputs[i] for i in validation_sample]
    validation_outputs = [outputs[i] for i in validation_sample]

    plot_data(get_feature(train_inputs, 0), get_feature(train_inputs, 1), train_outputs, [], [], [], get_feature(validation_inputs, 0), get_feature(validation_inputs, 1), validation_outputs, 'train and test data')

    # Step 3: Train the model with both variables
    regressor = MyLinearBivarRegression()
    x1_train = get_feature(train_inputs, 0)
    x2_train = get_feature(train_inputs, 1)
    regressor.fit(x1_train, x2_train, train_outputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]

    print('the learnt model: f(x1, x2) = ', w0, ' + ', w1, ' * x1 + ', w2, ' * x2')

    # Step 4: Plot results
    no_of_points = 1000
    x1_ref = np.linspace(min(get_feature(train_inputs, 0)), max(get_feature(train_inputs, 0)), no_of_points)
    x2_ref = np.linspace(min(get_feature(train_inputs, 1)), max(get_feature(train_inputs, 1)), no_of_points)
    y_ref = [w0 + w1 * x1 + w2 * x2 for x1, x2 in zip(x1_ref, x2_ref)]
    plot_data(get_feature(train_inputs, 0), get_feature(train_inputs, 1), train_outputs, x1_ref, x2_ref, y_ref, [], [], title='train data and model')

    # Step 5: Make predictions and evaluate
    computed_validation_outputs = regressor.predict(validation_inputs)
    plot_data([], [], [], get_feature(validation_inputs, 0), get_feature(validation_inputs, 1), computed_validation_outputs, get_feature(validation_inputs, 0), get_feature(validation_inputs, 1), validation_outputs, 'predictions vs real test data')

    error = 0.0
    for t1, t2 in zip(computed_validation_outputs, validation_outputs):
      error += (t1 - t2) ** 2
    error = error / len(validation_outputs)
    print("prediction error (manual): ", error)

# Example usage
happiness_prediction_depending_two_variables_without_tool('v1_world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')

