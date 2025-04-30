# -*- coding: utf-8 -*-
"""laborator6.ipynb


**Problema 1**

Ce îi poate face pe oameni fericiți? Se consideră problema predicției gradului de fericire a populației globului folosind informații despre diferite caracteristici a bunăstării respectivei populații precum Produsul intern brut al țării în care locuiesc (gross domestic product – GBP), gradul de fericire, etc.

Folsind datele aferente anului 2017 link, să se realizeze o predicție a gradului de fericire în funcție:

doar de Produsul intern brut
de Produsul intern brut si de gradul de libertate.
"""

import warnings; warnings.simplefilter('ignore')
import csv
import matplotlib.pyplot as plt
import numpy as np
import random
from sklearn.metrics import mean_squared_error
import csv
import os
import math
import io

from sklearn import linear_model
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import SGDRegressor
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score
from sklearn.metrics import accuracy_score, roc_curve, auc
from sklearn.model_selection import cross_val_score, KFold
from sklearn.preprocessing import LabelEncoder

from math import sqrt

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

class MySGDRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    # simple stochastic GD
    def fit(self, x, y, learningRate = 0.001, noEpochs = 1000):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]    #beta or w coefficients y = w0 + w1 * x1 + w2 * x2 + ...
        # self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]    #beta or w coefficients
        for epoch in range(noEpochs):
            # TBA: shuffle the trainind examples in order to prevent cycles
            for i in range(len(x)): # for each sample from the training data
                ycomputed = self.eval(x[i])     # estimate the output
                crtError = ycomputed - y[i]     # compute the error for the current sample
                for j in range(0, len(x[0])):   # update the coefficients
                    self.coef_[j] = self.coef_[j] - learningRate * crtError * x[i][j]
                self.coef_[len(x[0])] = self.coef_[len(x[0])] - learningRate * crtError * 1

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x):
        yComputed = [self.eval(xi) for xi in x]
        return yComputed

class MyBGDRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    # simple stochastic GD
    def fit(self, x, y, learningRate = 0.001, noEpochs = 1000):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]    #beta or w coefficients y = w0 + w1 * x1 + w2 * x2 + ...
        # self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]    #beta or w coefficients
        for epoch in range(noEpochs):
            # TBA: shuffle the trainind examples in order to prevent cycles
            sum_error = 0
            for i in range(len(x)): # for each sample from the training data
                ycomputed = self.eval(x[i])     # estimate the output
                crtError = ycomputed - y[i]     # compute the error for the current sample
                sum_error += crtError
            for j in range(0, len(x[0])):   # update the coefficients
                self.coef_[j] = self.coef_[j] - learningRate * sum_error * x[i][j]
            self.coef_[len(x[0])] = self.coef_[len(x[0])] - learningRate * sum_error * 1

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x):
        yComputed = [self.eval(xi) for xi in x]
        return yComputed

def univariate_regression_for_happiness(file_name, input_variable_name, output_variable_name, tool, mode):
    url = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab06/SGD/data/" + file_name
    !wget -O {file_name} {url}
    crtDir =  os.getcwd()
    filePath = os.path.join(crtDir, file_name)

    inputs, outputs = load_data(filePath, input_variable_name, output_variable_name)

    plot_data_histogram(inputs, input_variable_name)
    plot_data_histogram(outputs, output_variable_name)

    # check the liniarity (to check that a linear relationship exists between the dependent variable y and the independent variable x
    title = input_variable_name + " vs " + output_variable_name
    #plot_data(inputs, outputs, [], [], [], [], title)

    # split data into training data (80%) and testing data (20%)
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace = False)
    testSample = [i for i in indexes  if not i in trainSample]
    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    #plot_data(trainInputs, trainOutputs, [], [], testInputs, testOutputs, "train and test data")

    # training step
    xx = [[el] for el in trainInputs]
    if tool == "yes" and mode == "stocastic":
      regressor = linear_model.SGDRegressor(max_iter =  10000)
      regressor.fit(xx, trainOutputs)
    if tool == "no" and mode == "stocastic":
      regressor = MySGDRegression()
      regressor.fit(xx, trainOutputs)
    if tool == "yes" and mode == "batch":
      # inițializăm SGDRegressor cu parametri determinați (non-stochastic)
      regressor = SGDRegressor(
          max_iter=1,
          tol=None,
          learning_rate='constant',
          eta0=0.01,
          random_state=42,
          fit_intercept=True
      )

      # reshape la (n_samples, 1)
      X_train = np.array(trainInputs).reshape(-1, 1)
      y_train = np.array(trainOutputs)

      # împărțim datele în batch-uri
      n_batches = 10
      X_batches = np.array_split(X_train, n_batches)
      y_batches = np.array_split(y_train, n_batches)

      for i in range(n_batches):
            regressor.partial_fit(X_batches[i], y_batches[i])

    if tool == "no" and mode == "batch":
      regressor = MyBGDRegression()
      regressor.fit(xx, trainOutputs)

    w0, w1 = regressor.intercept_, regressor.coef_[0]


    print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x')

    # plot the model
    noOfPoints = 1000
    xref = []
    val = min(trainInputs)
    step = (max(trainInputs) - min(trainInputs)) / noOfPoints
    for i in range(1, noOfPoints):
        xref.append(val)
        val += step
    yref = [w0 + w1 * el for el in xref]
    plot_data(trainInputs, trainOutputs, xref, yref, [], [], title = "train data and model")

    #makes predictions for test data
    # computedTestOutputs = [w0 + w1 * el for el in testInputs]
    #makes predictions for test data (by tool)
    computedTestOutputs = regressor.predict([[x] for x in testInputs])
    #plot_data([], [], testInputs, computedTestOutputs, testInputs, testOutputs, "predictions vs real test data")

    #compute the differences between the predictions and real outputs
    error = 0.0
    for t1, t2 in zip(computedTestOutputs, testOutputs):
        error += (t1 - t2) ** 2
    error = error / len(testOutputs)
    print("prediction error (manual): ", error)

    error = mean_squared_error(testOutputs, computedTestOutputs)
    print("prediction error (tool): ", error)

univariate_regression_for_happiness('world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score', "yes", "stocastic")

univariate_regression_for_happiness('world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score', "no", "stocastic")

univariate_regression_for_happiness('world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score', "yes", "batch")

univariate_regression_for_happiness('world-happiness-report-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score', "no", "batch")

def load_data_more_inputs(fileName, inputVariabNames, outputVariabName):
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1
    selectedVariable1 = dataNames.index(inputVariabNames[0])
    selectedVariable2 = dataNames.index(inputVariabNames[1])
    inputs = [[float(data[i][selectedVariable1]), float(data[i][selectedVariable2])] for i in range(len(data))]
    selectedOutput = dataNames.index(outputVariabName)
    outputs = [float(data[i][selectedOutput]) for i in range(len(data))]

    return inputs, outputs

def remove_negative_values(feature1, feature2, outputs):
    new_feature1 = []
    new_feature2 = []
    new_outputs = []
    for f1, f2, out in zip(feature1, feature2, outputs):
      if f1 >= 0 and f2 >= 0 and out >= 0:
        new_feature1.append(f1)
        new_feature2.append(f2)
        new_outputs.append(out)
    return new_feature1, new_feature2, new_outputs


def plot_3D_data(x1Train, x2Train, yTrain, x1Model = None, x2Model = None, yModel = None, x1Test = None, x2Test = None, yTest = None, title = None):
    from mpl_toolkits import mplot3d
    x1Train, x2Train, yTrain = remove_negative_values(x1Train, x2Train, yTrain)
    ax = plt.axes(projection = '3d')
    if (x1Train):
        plt.scatter(x1Train, x2Train, yTrain, c = 'r', marker = 'o', label = 'train data')
    if (x1Model):
        plt.scatter(x1Model, x2Model, yModel, c = 'b', marker = '_', label = 'learnt model')
    if (x1Test):
        plt.scatter(x1Test, x2Test, yTest, c = 'g', marker = '^', label = 'test data')
    plt.title(title)
    ax.set_xlabel("capita")
    ax.set_ylabel("freedom")
    ax.set_zlabel("happiness")
    plt.legend()
    plt.show()

def normalisation(trainData, testData):
    scaler = StandardScaler()
    if not isinstance(trainData[0], list):
        #encode each sample into a list
        trainData = [[d] for d in trainData]
        testData = [[d] for d in testData]

        scaler.fit(trainData)  #  fit only on training data
        normalisedTrainData = scaler.transform(trainData) # apply same transformation to train data
        normalisedTestData = scaler.transform(testData)  # apply same transformation to test data

        #decode from list to raw values
        normalisedTrainData = [el[0] for el in normalisedTrainData]
        normalisedTestData = [el[0] for el in normalisedTestData]
    else:
        scaler.fit(trainData)  #  fit only on training data
        normalisedTrainData = scaler.transform(trainData) # apply same transformation to train data
        normalisedTestData = scaler.transform(testData)  # apply same transformation to test data
    return normalisedTrainData, normalisedTestData, scaler

def bivariate_regression(file_name, input_variable_names, output_variable_name, tool, mode):
    url = "https://raw.githubusercontent.com/lauradiosan/AI-UBB/main/2024-2025/labs/lab06/SGD/data/" + file_name
    !wget -O {file_name} {url}
    crtDir =  os.getcwd()
    filePath = os.path.join(crtDir, file_name)

    inputs, outputs = load_data_more_inputs(filePath, input_variable_names, output_variable_name)
    feature1 = [ex[0] for ex in inputs]
    feature2 = [ex[1] for ex in inputs]

    plot_data_histogram(feature1, input_variable_names[0])
    plot_data_histogram(feature2, input_variable_names[1])
    plot_data_histogram(outputs, output_variable_name)

    # check the liniarity (to check that a linear relationship exists between the dependent variable y and the independent variable x
    title = input_variable_names[0] + "and" + input_variable_names[1] + " vs " + output_variable_name
    #plot_data(inputs, outputs, [], [], [], [], title)

    # split data into training data (80%) and testing data (20%)
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace = False)
    testSample = [i for i in indexes  if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    trainInputs, testInputs, _ = normalisation(trainInputs, testInputs)
    trainOutputs, testOutputs, _ = normalisation(trainOutputs, testOutputs)

    feature1train = [ex[0] for ex in trainInputs]
    feature2train = [ex[1] for ex in trainInputs]

    feature1test = [ex[0] for ex in testInputs]
    feature2test = [ex[1] for ex in testInputs]

    #plot_3D_data(feature1train, feature2train, trainOutputs, [], [], [], feature1test, feature2test, testOutputs, "train and test data(after normalisation)")


    # training step
    if tool == "yes" and mode == "stocastic":
      regressor = linear_model.SGDRegressor(max_iter =  10000)
    if tool == "no" and mode == "stocastic":
      regressor = MySGDRegression()
    if tool == "yes" and mode == "batch":
      regressor = BGDRegressor()
    if tool == "no" and mode == "batch":
      regressor = MyBGDRegression()
    regressor.fit(trainInputs, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]


    print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x1 + ' , w2, '* x2' )

    # plot the model
    noOfPoints = 50
    xref1 = []
    val = min(feature1)
    step1 = (max(feature1) - min(feature1)) / noOfPoints
    for _ in range(1, noOfPoints):
      for _ in range(1, noOfPoints):
        xref1.append(val)
      val += step1

    xref2 = []
    val = min(feature2)
    step2 = (max(feature2) - min(feature2)) / noOfPoints
    for _ in range(1, noOfPoints):
      aux = val
      for _ in range(1, noOfPoints):
        xref2.append(aux)
        aux += step2

    yref = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(xref1, xref2)]
    plot_3D_data(feature1train, feature2train, trainOutputs, xref1, xref2, yref, [], [], [], title = "train data and model")

    #makes predictions for test data
    # computedTestOutputs = [w0 + w1 * el for el in testInputs]
    #makes predictions for test data (by tool)
    computedTestOutputs = regressor.predict(testInputs)
    #plot_3D_data([], [], [], feature1test, feature2test, computedTestOutputs, feature1test, feature2test, testOutputs, "predictions vs real test data")

    #compute the differences between the predictions and real outputs
    error = 0.0
    for t1, t2 in zip(computedTestOutputs, testOutputs):
        error += (t1 - t2) ** 2
    error = error / len(testOutputs)
    print("prediction error (manual): ", error)

    error = mean_squared_error(testOutputs, computedTestOutputs)
    print("prediction error (tool): ", error)

bivariate_regression('world-happiness-report-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score', "yes", "stocastic")

bivariate_regression('world-happiness-report-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score', "no", "stocastic")

bivariate_regression('world-happiness-report-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score', "yes", "batch")

bivariate_regression('world-happiness-report-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score', "no", "batch")

"""**Problema 2**

Clasificarea țesuturilor cancerigene Se consideră informații despre cancerul de sân la femei, informații extrase din ecografii mamare (detalii aici) precum: - Tipul malformației identificate (țesut benign sau țesut malign) - Caracteristici numerice ale nucleului celulelor din aceste țesuturi: - raza (media distanțelor între centru si punctele de pe contur) - textura (măsurată prin deviația standard a nivelelor de gri din imaginea asociată țesutului analizat) Folosindu-se aceste date, să se decidă dacă țesutul dintr-o nouă ecografie (pentru care se cunosc cele 2 caracteristici numerice – raza și textura –) va fi etichetat ca fiind malign sau benign.

 Antrenati cate un clasificator pentru fiecare problema, pe care apoi sa ii utilizati pentru a stabili:

daca o leziune (dintr-o mamografie) caracterizata printr-o textura de valoare 10 si o raza de valoare 18 este leziune maligna sau benigna
"""

import pandas as pd
import numpy as np
import requests

# URL for the Wisconsin Breast Cancer Diagnostic dataset
url = "https://archive.ics.uci.edu/ml/machine-learning-databases/breast-cancer-wisconsin/wdbc.data"

# Column names according to the UCI documentation
column_names = [
    'ID',
    'Diagnosis',  # M = malignant, B = benign
    'Radius_Mean',
    'Texture_Mean',
    'Perimeter_Mean',
    'Area_Mean',
    'Smoothness_Mean',
    'Compactness_Mean',
    'Concavity_Mean',
    'Concave_Points_Mean',
    'Symmetry_Mean',
    'Fractal_Dimension_Mean',
    'Radius_SE',
    'Texture_SE',
    'Perimeter_SE',
    'Area_SE',
    'Smoothness_SE',
    'Compactness_SE',
    'Concavity_SE',
    'Concave_Points_SE',
    'Symmetry_SE',
    'Fractal_Dimension_SE',
    'Radius_Worst',
    'Texture_Worst',
    'Perimeter_Worst',
    'Area_Worst',
    'Smoothness_Worst',
    'Compactness_Worst',
    'Concavity_Worst',
    'Concave_Points_Worst',
    'Symmetry_Worst',
    'Fractal_Dimension_Worst'
]

try:
    # Download the data directly
    response = requests.get(url)
    response.raise_for_status()  # Raise exception for HTTP errors
    data_str = response.text

    # Parse the data into a DataFrame
    df = pd.read_csv(io.StringIO(data_str), header=None, names=column_names)

except Exception as e:
    print(f"Could not download data from UCI repository: {e}")
    print("Please check your internet connection or the URL.")
    # Create a simple synthetic dataset as fallback
    print("Creating a synthetic dataset for demonstration...")

# Create a simplified DataFrame with just the columns we need
simplified_df = df[['ID', 'Diagnosis', 'Radius_Mean', 'Texture_Mean']]

# Rename columns to match the requested format
simplified_df = simplified_df.rename(columns={
    'Radius_Mean': 'Radius',
    'Texture_Mean': 'Texture'
})

# Map diagnosis: 'M' -> 1 (malignant), 'B' -> 0 (benign)
simplified_df['Diagnosis'] = simplified_df['Diagnosis'].map({'M': 1, 'B': 0})

# Save to CSV
csv_filename = 'breast_cancer_simplified.csv'
simplified_df.to_csv(csv_filename, index=False)

print(f"CSV file created: {csv_filename}")

def plot_ROC_Curve(fpr, tpr, thresholds):
  # Calculate the AUC (Area Under Curve)
  roc_auc = auc(fpr, tpr)

  # Ensure that AUC is a float
  roc_auc = float(roc_auc)

  # Plot ROC curve
  plt.figure(figsize=(8, 6))
  plt.plot(fpr, tpr, color='b', label=f'ROC curve (AUC = {roc_auc:.2f})')
  plt.plot([0, 1], [0, 1], color='gray', linestyle='--')  # Random classifier line
  plt.xlabel('False Positive Rate')
  plt.ylabel('True Positive Rate')
  plt.title('Receiver Operating Characteristic (ROC) Curve')
  plt.legend(loc='lower right')
  plt.show()

def plot_decision_boundary(X, y, model):
    """
    Funcție pentru plotarea limitei de decizie care funcționează atât cu implementarea sklearn,
    cât și cu implementarea manuală, și atât cu numpy arrays cât și cu liste simple.
    """
    import matplotlib.pyplot as plt
    import numpy as np

    # Convertim datele la numpy array dacă sunt liste
    if isinstance(X, list):
        X = np.array(X)
    if isinstance(y, list):
        y = np.array(y)

    # Definim limitele plot-ului
    h = 0.02  # Rezoluția gridului
    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1

    # Generăm grid de puncte
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h), np.arange(y_min, y_max, h))

    # Verificăm tipul modelului și facem predicții corespunzător
    mesh_points = np.c_[xx.ravel(), yy.ravel()]

    if hasattr(model, 'predict_proba') and callable(getattr(model, 'predict_proba')):
        try:
            # Pentru sklearn LogisticRegression
            Z = model.predict(mesh_points)
        except:
            # Pentru implementarea manuală MyLogisticRegression
            Z = model.predict(mesh_points.tolist())
    else:
        # Fallback pentru alte tipuri de modele
        Z = model.predict(mesh_points)

    # Reshape rezultatul pentru plot
    Z = np.array(Z).reshape(xx.shape)

    # Creăm plot-ul
    plt.figure(figsize=(10, 8))
    plt.contourf(xx, yy, Z, alpha=0.8, cmap=plt.cm.RdBu)

    # Plotăm și punctele de antrenare
    plt.scatter(X[:, 0], X[:, 1], c=y, edgecolors='k', cmap=plt.cm.RdBu)
    plt.xlabel('Caracteristica 1')
    plt.ylabel('Caracteristica 2')
    plt.title('Limită de decizie regresie logistică')
    plt.show()

class MyLogisticRegression:
    def __init__(self, learning_rate=0.01, num_iterations=1000, verbose=False, thresholds=[0.5]):
        self.learning_rate = learning_rate
        self.num_iterations = num_iterations
        self.verbose = verbose
        self.theta = None
        self.thresholds = thresholds

    def __sigmoid(self, z):
        """Implementare robustă a funcției sigmoid pentru a evita overflow"""
        # Tratăm separat valorile mici și mari pentru stabilitate numerică
        if isinstance(z, list):
            result = []
            for val in z:
                if val >= 0:
                    result.append(1.0 / (1.0 + math.exp(-val)))
                else:
                    exp_val = math.exp(val)
                    result.append(exp_val / (1.0 + exp_val))
            return result
        else:
            if z >= 0:
                return 1.0 / (1.0 + math.exp(-z))
            else:
                exp_val = math.exp(z)
                return exp_val / (1.0 + exp_val)

    def __calculate_loss(self, h, y, epsilon=1e-15):
        """Calculează Binary Cross-Entropy Loss cu stabilitate numerică"""
        loss = 0.0
        for i in range(len(y)):
            # Aplicăm clipping pentru a evita log(0)
            h_i = max(min(h[i], 1 - epsilon), epsilon)
            loss += -y[i] * math.log(h_i) - (1 - y[i]) * math.log(1 - h_i)
        return loss / len(y)

    def __hinge_loss(self, h, y, threshold):
        """Implementare simplificată și stabilă a Hinge Loss"""
        loss = 0.0
        for i in range(len(y)):
            y_pred = 1 if h[i] >= threshold else -1
            y_true = 2 * y[i] - 1  # Convertim {0,1} la {-1,1}
            loss += max(0, 1 - y_true * y_pred)
        return loss / len(y)

    def __mean_squared_error(self, h, y, threshold):
        """Calcul simplu pentru Mean Squared Error"""
        loss = 0.0
        for i in range(len(y)):
            y_pred = 1 if h[i] >= threshold else 0
            loss += (y_pred - y[i]) ** 2
        return loss / len(y)

    def __matrix_vector_multiply(self, X, theta):
        """Înmulțire matrice-vector implementată eficient"""
        result = []
        for row in X:
            val = sum(x_i * t_i for x_i, t_i in zip(row, theta))
            result.append(val)
        return result

    def fit(self, X, y, max_iter=None):
        """
        Antrenează modelul de regresie logistică
        X: lista de liste, fiecare listă internă reprezentând un exemplu
        y: lista de etichete (0 sau 1)
        """
        import math

        # Asigurăm-ne că datele sunt liste simple
        if not isinstance(X[0], list):
            X = [list(x) for x in X]
        if not isinstance(y, list):
            y = list(y)

        m = len(X)  # Numărul de exemple
        n = len(X[0])  # Numărul de caracteristici

        # Inițializăm coeficienții la zero
        self.theta = [0.0] * (n + 1)

        # Adăugăm termenul de bias (1) la începutul fiecărui exemplu
        X_with_bias = [[1.0] + row for row in X]

        # Setăm numărul maxim de iterații
        iterations = max_iter if max_iter is not None else self.num_iterations

        # Algoritmul gradient descent
        for i in range(iterations):
            # Calculăm predicțiile
            z = self.__matrix_vector_multiply(X_with_bias, self.theta)
            h = self.__sigmoid(z)

            # Calculăm gradientul pentru fiecare coeficient
            gradients = [0.0] * (n + 1)
            for j in range(n + 1):
                for k in range(m):
                    gradients[j] += (h[k] - y[k]) * X_with_bias[k][j]
                gradients[j] /= m

            # Actualizăm coeficienții
            for j in range(n + 1):
                self.theta[j] -= self.learning_rate * gradients[j]

            # Afișăm progresul dacă verbose=True
            if self.verbose and i % (iterations // 10 or 1) == 0:
                try:
                    loss = self.__calculate_loss(h, y)
                    print(f"Iterația {i}, Loss: {loss}")

                    for threshold in self.thresholds:
                        hinge = self.__hinge_loss(h, y, threshold)
                        mse = self.__mean_squared_error(h, y, threshold)
                        print(f"Threshold {threshold}: Hinge Loss={hinge}, MSE={mse}")
                except Exception as e:
                    print(f"Eroare la calculul loss: {e}")

    def predict_proba(self, X):
        """Returnează probabilitățile pentru clasa pozitivă"""
        # Asigurăm-ne că datele sunt liste simple
        if not isinstance(X[0], list):
            X = [list(x) for x in X]

        # Adăugăm termenul de bias
        X_with_bias = [[1.0] + row for row in X]

        # Calculăm scorurile și le transformăm în probabilități
        z = self.__matrix_vector_multiply(X_with_bias, self.theta)
        probabilities = self.__sigmoid(z)

        return probabilities

    def predict(self, X):
        """Returnează clasele prezise (0 sau 1)"""
        import math  # Importăm aici pentru siguranță

        probabilities = self.predict_proba(X)
        predictions = [1 if p >= 0.5 else 0 for p in probabilities]
        return predictions

def logistic_regression_for_cancerous(file_name, input_variable_names, output_variab_name, tool, treshold_input):
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, file_name)

    inputs, outputs = load_data_more_inputs(filePath, input_variable_names, output_variab_name)

    # Împărțim datele în training (80%) și testing (20%)
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    trainInputs, testInputs, scaler = normalisation(trainInputs, testInputs)

    if tool == "yes":
        # Folosim implementarea sklearn
        regressor = LogisticRegression(max_iter=1000)
        regressor.fit(trainInputs, trainOutputs)
        w0, w1, w2 = regressor.intercept_[0], regressor.coef_[0][0], regressor.coef_[0][1]
    else:
        # Folosim implementarea manuală cu parametri modificați pentru convergență rapidă
        regressor = MyLogisticRegression(learning_rate=0.1, num_iterations=500, verbose=True, thresholds=treshold_input)

        # Convertim la liste simple dacă sunt array-uri numpy
        if isinstance(trainInputs, np.ndarray):
            trainInputs = trainInputs.tolist()
        if isinstance(trainOutputs, np.ndarray):
            trainOutputs = trainOutputs.flatten().tolist()

        # Limităm numărul de iterații pentru a evita blocajul
        regressor.fit(trainInputs, trainOutputs, max_iter=500)
        w0, w1, w2 = regressor.theta[0], regressor.theta[1], regressor.theta[2]

    print('the learnt model: f(x) = ', w0, ' + ', w1, ' * x1 + ', w2, '* x2')

    # Decidem cum gestionăm plot_decision_boundary în funcție de implementare
    # Presupunem că funcția poate gestiona ambele tipuri
    plot_decision_boundary(trainInputs, trainOutputs, regressor)

    # Asigurăm-ne că testInputs este în formatul corect
    if tool != "yes" and isinstance(testInputs, np.ndarray):
        testInputs = testInputs.tolist()

    # Facem predicții
    computedTestOutputs = regressor.predict(testInputs)

    # Convertim la numpy pentru funcțiile scikit-learn
    if not isinstance(computedTestOutputs, np.ndarray):
        computedTestOutputs = np.array(computedTestOutputs)
    if not isinstance(testOutputs, np.ndarray):
        testOutputs = np.array(testOutputs)

    # Calculăm și afișăm curba ROC
    fpr, tpr, thresholds = roc_curve(testOutputs, computedTestOutputs)
    #plot_ROC_Curve(fpr, tpr, thresholds)

    print("Accuracy model " + str(accuracy_score(testOutputs, computedTestOutputs)))

    # Clasificăm un nou exemplu
    new_input = scaler.transform([[18, 10]])
    if tool != "yes" and isinstance(new_input, np.ndarray):
        new_input = new_input.tolist()

    new_prediction = regressor.predict(new_input)
    if isinstance(new_prediction, list) and len(new_prediction) > 0:
        pred_value = new_prediction[0]
    elif hasattr(new_prediction, 'shape'):  # Numpy array
        pred_value = new_prediction[0]
    else:
        pred_value = new_prediction  # În caz că este o singură valoare

    if pred_value == 1:
        print("Leziunea e maligna")
    else:
        print("Leziunea e benigna")

logistic_regression_for_cancerous('breast_cancer_simplified.csv', ['Radius', 'Texture'], 'Diagnosis', "yes", [0.5])

logistic_regression_for_cancerous('breast_cancer_simplified.csv', ['Radius', 'Texture'], 'Diagnosis', "no",[0.5])

logistic_regression_for_cancerous('breast_cancer_simplified.csv', ['Radius', 'Texture'], 'Diagnosis', "no",[0.2])



def logistic_regression_for_cancerous_cross_validation(file_name, input_variable_names, output_variab_name):
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, file_name)

    inputs, outputs = load_data_more_inputs(filePath, input_variable_names, output_variab_name)

    scaler = StandardScaler()
    inputs = scaler.fit_transform(inputs)

    regressor = LogisticRegression()
    kf = KFold(n_splits=5, shuffle=True, random_state=10)
    scores = cross_val_score(regressor, inputs, outputs, cv=kf, scoring='accuracy')

    print("Accuracy: ", scores)
    print("Mean accuracy: ", scores.mean())

    regressor.fit(inputs, outputs)
    print("the learnt model: f(x) = ", regressor.intercept_[0], " + ", regressor.coef_[0][0], " * x1 + ", regressor.coef_[0][1], " * x2")

    normalized_inputs = scaler.transform([[18, 10]])
    prediction = regressor.predict(np.array(normalized_inputs))
    if prediction[0] == 1:
        print("Leziunea e maligna")
    else:
        print("Leziunea e benigna")

logistic_regression_for_cancerous_cross_validation('breast_cancer_simplified.csv', ['Radius', 'Texture'], 'Diagnosis')

"""**Problema 3**

Ce fel de floare preferi? Se consideră problema clasificării florilor de iris în diferite specii precum: setosa, versicolor și virginica. Pentru fiecare floare se cunosc caracteristici precum: lungimea și lățimea sepalei, lungimea și lățimea petalei. Mai multe detalii despre acest set se pot găsi aici. Folosindu-se aceste informații, să se decidă din ce specie aparține o anumită floare.

Antrenati cate un clasificator pentru fiecare problema, pe care apoi sa ii utilizati pentru a stabili:
specia unei flori de iris care are sepala lunga de 5.35 cm si lata de 3.85 cm, iar petala lunga de 1.25 cm si lata de 0.4cm
"""

import pandas as pd

# Descarcă datasetul Iris
url_iris = "https://archive.ics.uci.edu/ml/machine-learning-databases/iris/iris.data"
iris_columns = ['SepalLength', 'SepalWidth', 'PetalLength', 'PetalWidth', 'Species']

iris_df = pd.read_csv(url_iris, header=None, names=iris_columns)

# Salvează doar coloanele necesare
iris_df.to_csv('iris_data.csv', index=False)
print("Fișier iris_data.csv creat cu succes.")

def load_data_more_inputs_pb3(fileName, inputVariabNames, outputVariabName, labelEncoder):
    import csv
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1

    # indexuri pentru toate variabilele de intrare
    selectedInputs = [dataNames.index(var) for var in inputVariabNames]
    inputs = [[float(data[i][j]) for j in selectedInputs] for i in range(len(data))]

    selectedOutput = dataNames.index(outputVariabName)
    outputs = [data[i][selectedOutput] for i in range(len(data))]

    # encode output labels
    outputs = labelEncoder.fit_transform(outputs)
    outputs = outputs.reshape(-1, 1)

    return inputs, outputs

import math

class MyLogisticRegression:
    def __init__(self, learning_rate=0.01, num_iterations=1000, threshold=0.33):
        self.learning_rate = learning_rate
        self.num_iterations = num_iterations
        self.threshold = threshold
        self.theta = None

    def sigmoid(self, z):
        """Funcția sigmoid"""
        return 1 / (1 + math.exp(-z))

    def cost_function(self, X, y, theta):
        """Calcularea funcției de cost"""
        m = len(y)
        epsilon = 1e-5  # pentru a preveni log(0)
        total_cost = 0

        for i in range(m):
            # Calculul prezicerii (h(x) = sigmoid(X * theta))
            h = self.sigmoid(self.dot_product(X[i], theta))
            # Calculul costului pentru fiecare instanță
            term1 = y[i] * math.log(h + epsilon)
            term2 = (1 - y[i]) * math.log(1 - h + epsilon)
            total_cost += -term1 - term2

        # Returnăm costul mediu pe toate exemplele
        return total_cost / m

    def dot_product(self, a, b):
        """Calculul produsului scalar între două liste (a și b)"""
        return sum(x * y for x, y in zip(a, b))

    def gradient_descent(self, X, y):
        """Calcularea gradientului și actualizarea parametrilor (theta)"""
        m = len(X)  # numărul de exemple
        n = len(X[0]) if m > 0 else 0  # numărul de caracteristici
        self.theta = [0] * n  # inițializarea coeficientului theta cu 0

        for _ in range(self.num_iterations):
            gradients = [0] * n  # inițializăm gradientul

            # Calculăm gradientul pe fiecare instanță
            for i in range(m):
                h = self.sigmoid(self.dot_product(X[i], self.theta))
                error = (h - y[i])
                #error = (h - y[i])**2
                for j in range(n):
                    gradients[j] += X[i][j] * error

            # Actualizăm coeficientul theta în direcția opusă gradientului
            for j in range(n):
                self.theta[j] -= (self.learning_rate / m) * gradients[j]

    def fit(self, X, y):
        """Antrenăm modelul (calculăm theta pe baza datelor)"""
        # Adăugăm termenul de interceptare (coloana de 1) la X
        X_with_intercept = []
        for row in X:
            X_with_intercept.append([1] + row)  # Coloană de 1 pentru intercept
        # Aplicăm gradient descent pentru a ajusta coeficientul theta
        self.gradient_descent(X_with_intercept, y)

    def predict(self, X):
        """Fă predicții pentru noi exemple"""
        # Adăugăm termenul de interceptare (coloana de 1) la X
        X_with_intercept = []
        for row in X:
            X_with_intercept.append([1] + row)  # Coloană de 1 pentru intercept

        predicted_labels = []
        for row in X_with_intercept:
            # Calculăm z (produsul scalar) și obținem probabilitatea (sigmoid(z))
            z = self.dot_product(row, self.theta)
            prob = self.sigmoid(z)
            # Aplicăm pragul pentru a face predicția 0 sau 1
            predicted_labels.append(1 if prob >= self.threshold else 0)

        return predicted_labels



def logistic_regression_for_flowers(file_name, input_variable_names, output_variab_name, tool):
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, file_name)
    label_encoder = LabelEncoder()
    inputs, outputs = load_data_more_inputs_pb3(filePath, input_variable_names, output_variab_name, label_encoder)

    # PASUL 2: split data into training data (80%) and testing data (20%) and normalise data
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    # Normalization
    scaler = StandardScaler()
    scaler.fit(trainInputs)
    trainInputs = scaler.transform(trainInputs)
    testInputs = scaler.transform(testInputs)

    # PASUL 3: training step
    if tool == "yes":
        regressor = LogisticRegression()
        regressor.fit(trainInputs, trainOutputs)
        w0, w1 = regressor.intercept_, regressor.coef_[0]
        print('the learnt model: f(x) = ', w0[0], ' + ', w1[0], ' * x1 + ', w1[1], ' * x2')
    else:
        # Custom Logistic Regression model implementation can be used here
        regressor = MyLogisticRegression()
        regressor.fit(trainInputs, trainOutputs)
        coefficients = regressor.theta
        print('the learnt model: f(x) = ', coefficients[0][0], ' + ', coefficients[1][0], ' * x1 + ', coefficients[2][0], ' * x2')


    computedTestOutputs = regressor.predict(testInputs)

    print('Accuracy: ', accuracy_score(testOutputs, computedTestOutputs))  # correct predictions / total predictions

    # Verification for a new input
    normalized_inputs = scaler.transform([[5.35, 3.85, 1.25, 0.4]])
    prediction = regressor.predict(np.array(normalized_inputs))
    predicted_species = label_encoder.inverse_transform(prediction)
    print("The predicted species for the flower is: ", predicted_species[0])

logistic_regression_for_flowers('iris_data.csv', ['SepalLength', 'SepalWidth', 'PetalLength', 'PetalWidth'], 'Species', "yes")

logistic_regression_for_flowers('iris_data.csv', ['SepalLength', 'SepalWidth', 'PetalLength', 'PetalWidth'], 'Species', "no")

