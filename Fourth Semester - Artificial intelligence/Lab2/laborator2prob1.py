#extragere date
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
df=pd.read_csv('surveyDataSience.csv')
df.head()

"""numarul de respondenti (de la care s-au colectate informatiile)"""

def numar_respondenti(df):
  """
  Afișează numarul de respondenti
  :param df: dataframe-ul
  :return: numarul de respondenti
  """
  return len(df) - 1
numar_respondenti(df)

"""numar si tipul informatiilor (atributelor, proprietatilor) detinute pentru un respondent"""

def tip_numar_informatii(df):
  """
  Afișează tipul si numarul de informatii detinute pentru un respondent
  :param df: dataframe-ul
  :return: series pandas - tipul informatiilor detinute de un respondent
           int -  numarul de informatii detinute pentru un respondent
  """
  nr_atribute = df.shape[1]
  tip_atribute = df.dtypes
  print(f"Numarul de atribute: {nr_atribute}")
  print("Tipul atributelor:")
  print(tip_atribute)
tip_numar_informatii(df)

"""numarul de respondenti pentru care se detin date complete"""

def numar_respondenti_date_complete(df):
  """
  Returnează numarul de respondenti pentru care se detin date complete
  :param df: dataframe-ul
  :return: int - numarul de respondenti pentru care se detin date complete
  """
  return df[1:].dropna().shape[0]
print(f"Numarul de respondenti pentru care se detin date complete: {numar_respondenti_date_complete(df)}")

"""durata medie a anilor de studii superioare pentru acesti respondenti (cea efectiva sau cea estimata), durata medie a anilor de studii pentru respondentii din Romania si durata medie a anilor de studii pentru respondentii din Romania care sunt femei. Comparati rezultatele obtinute pentru cele trei grupuri de respondenti. Se presupune ca studiile de licenta dureaza 3 ani, cele de master 2 ani si cele de doctorat 3 ani."""

def durata_medie_respondenti(df, tara=None, gen=None):
  """
  Returnează durata medie a anilor de studii superioare pentru acesti respondenti,
  în funcție de parametrii
  :param df: dataframe-ul
  :param tara: str - tara din care se extrag datele
  :param gen: str - genul din care se extrag datele
  :return: float -  durata medie a anilor de studii superioare pentru acesti respondenti
  """
  durata_studii ={
      'Bachelor’s degree': 3,
      'Master’s degree': 5,
      'Doctoral degree': 8
  }
  if tara is not None:
    df = df[df['Q3'] == tara]
  if gen is not None:
    df = df[df['Q2'] == gen]
  durata_medie = df['Q4'].map(durata_studii).mean()
  return durata_medie

print(f"Durata medie a anilor de studii superioare pentru respondenți: {durata_medie_respondenti(df)}")
print(f"Durata medie a anilor de studii superioare pentru respondenții din România: {durata_medie_respondenti(df, 'Romania')}")
print(f"Durata medie a anilor de studii superioare pentru respondenții femei din România: {durata_medie_respondenti(df, 'Romania', 'Woman')}")

"""numarul de respondenti femei din Romania pentru care se detin date complete"""

def numar_respondeti_Romania(df):
  """
  Returnează numarul de respondenti femei din Romania pentru care se detin date
  complete
  :param df: dataframe-ul
  :return: int - numarul de respondenti femei din Romania pentru care se
   detin date complete
  """
  df_ro=df[(df['Q3'] == 'Romania') & (df['Q2'] == 'Woman')]
  print(f"Numarul de respondenti femei din Romania pentru care se detin date complete: {df_ro.dropna().shape[0]}")
numar_respondeti_Romania(df)

"""numarul de femei din Romania care programeaza in Python, precum si intervalul de varsta cu cele mai multe femei care programeaza in Python? Dar in C++? Comparati rezultatele obtinute pentru cele doua limbaje de programare."""

def numar_respondenti_ro_fem_Python(df):
  """
  Afișează numarul de de femei din Romania care programeaza în Python și
  intervalul de varsta cu cele mai multe femei care programeaza în limbajul dat
  :param df: dataframe-ul
  :param limbaj: str
  :return: int - numarul de respondenți din Romania care programeaza în Python
           str - intervalul de varsta cu cele mai multe femei care programeaza
  în limbajul dat
  """
  df_ro=df[(df['Q3'] == 'Romania') & (df['Q2'] == 'Woman') & (df['Q7_Part_1'] == 'Python')]
  print(f"Numărul de femei din România care programează în Python: {df_ro.shape[0]}")

  interval_varsta = df_ro.groupby('Q1').size().idxmax()
  print(f"Intervalul de vârstă cu cele mai multe femei care programează în Python din România: {interval_varsta}")

def numar_respondenti_ro_fem_Cplusplus(df):
  """
  Afișează numarul de de femei din Romania care programeaza în C++ și
  intervalul de varsta cu cele mai multe femei care programeaza în limbajul dat
  :param df: dataframe-ul
  :param limbaj: str
  :return: int - numarul de respondenți din Romania care programeaza în C++
           str - intervalul de varsta cu cele mai multe femei care programeaza
  în limbajul dat
  """
  df_ro=df[(df['Q3'] == 'Romania') & (df['Q2'] == 'Woman') & (df['Q7_Part_5'] == 'C++')]
  print(f"Numărul de femei din România care programează în C++: {df_ro.shape[0]}")

  interval_varsta = df_ro.groupby('Q1').size().idxmax()
  print(f"Intervalul de vârstă cu cele mai multe femei care programează în C++ din România: {interval_varsta}")

numar_respondenti_ro_fem_Python(df)
numar_respondenti_ro_fem_Cplusplus(df)

"""domeniul de valori posibile si valorile extreme pentru fiecare atribut/proprietate (feature). In cazul
proprietatilor nenumerice, cate valori posibile are fiecare astfel de proprietate
"""

def test_coloana_compusa(c):
  """
  Testeaza daca coloana e formata din mai multe parti
  :param c: coloana
  :return: True daca coloana e formata din mai multe parti, False in caz contrar
  """
  if "_Part_" in c:
    return True
  return False

def coloana_compusa(c):
  """
  Returneaza numarul de parti si valorile posibile ale coloanei
  :param c: coloana
  :return: int - numarul de parti
           list - valorile posibile ale coloanei
  """
  val_unic = []
  c = c.split('_',1)[0]
  contor = 0
  for coloana in df.columns:
    if c in coloana:
      contor+=1
      val_unic.extend(df[coloana][1:].unique())
  return (contor, list(set(val_unic)))

def domeniu_valori(df):
  """
  Afișează domeniul de valori posibile și valorile extreme pentru fiecare atribut/proprietate
  :param df: dataframe-ul
  :return: dictionar - dictionarul cu domeniul de valori posibile și valorile extreme, respectiv
                       numarul de valori posibile ale coloanei
  """
  rezultat={}
  i = 0
  for col in df.columns:
    valori_unice = df[col][1:].dropna().unique()

    if col in ['Time from Start to Finish (seconds)']:
       df[col][1:] = pd.to_numeric(df[col][1:])
       rezultat[col] = {'domeniu': valori_unice,
                       'val_extreme': (df[col][1:].min(), df[col][1:].max()),
                       'numar_valori_posibile': len(coloana_compusa(col)[1])}
    elif test_coloana_compusa(col):
      col = col.split('_',1)[0]
      rezultat[col] = {'domeniu': coloana_compusa(col)[1],
                       'val_extreme': '-',
                       'numar_valori_posibile': len(coloana_compusa(col)[1])}
      i+=coloana_compusa(col)[0]
    else:
      rezultat[col] = {'domeniu': valori_unice,
                       'val_extreme': '-',
                       'numar_valori_posibile': len(valori_unice)}
      i+=1

  for column, values in rezultat.items():
    print(f"Coloana: {column}")
    print(f"  Domeniu: {values['domeniu']}")
    print(f"  Valori extreme(pentru valori numerice): {values['val_extreme']}")
    print(f"  Numar valori posibile: {values['numar_valori_posibile']}\n")
domeniu_valori(df)

"""transformati informatiile despre vechimea in programare in numar de ani (folositi in locul intervalului, mijlocul acestuia) si apoi calculati momentele de ordin 1 si 2 pentru aceasta variabila (minim, maxim, media, deviatia standard, mediana). Ce se poate spune despre aceasta variabila?"""

def conversie(val):
  """
  Converteste valoarea intervalului in mijlocul acestuia
  :param val: str
  :return: int - mijlocul intervalului
  """
  if isinstance(val, str):
    if '< 1 years' in val:
      return 0.5
    elif '20+ years' in val:
      return 25
    elif '-' in val:
      start, end = val.split('-')
      start = int(start.strip())
      end = int(end.split()[0].strip())
      return (start+end)/2
    else:
      return 0

def transformare_coloana(df):
  df.loc[1:, 'Q6'] = df.loc[1:, 'Q6'].apply(conversie)

def calculul_momentelor(df):
  print("Momentele de ordin 1 și 2 pentru coloana Q6 sunt:")
  print(f"  Minim: {df['Q6'][1:].min()}")
  print(f"  Maxim: {df['Q6'][1:].max()}")
  print(f"  Medie: {df['Q6'][1:].mean()}")
  print(f"  Deviația standard: {df['Q6'][1:].std()}")
  print(f"  Mediana: {df['Q6'][1:].median()}")

transformare_coloana(df)
df.head()
calculul_momentelor(df)

"""1.b. Sa se vizualizeze:

distributia respondentilor care programeaza in Python pe categorii de varsta
"""

def distributie_respondenti_Python(df):
  """
  Vizualizează distributia respondentilor care programeaza in Python pe categorii de varsta
  :param df: dataframe-ul
  """
  df_python = df[df['Q7_Part_1'] == 'Python']
  distributie_ani = df_python.groupby('Q1').size()

  #creare grafic
  plt.figure(figsize=(10, 6))
  distributie_ani.plot(kind='bar', color='#149414')
  plt.title('Distributie respondenti care programeaza in Python pe categorii de varsta')
  plt.xlabel('Categorii de varsta')
  plt.ylabel('Numar respondenti')
  plt.xticks(rotation=45)
  plt.grid(True)
  plt.show()

distributie_respondenti_Python(df)

"""distributia respondentilor din Romania care programeaza in Python pe categorii de varsta

"""

def distributie_respondenti_Python_Romania(df):
  """
  Vizualizează distributia respondentilor care programeaza in Python din Romania pe categorii de varsta
  :param df: dataframe-ul
  """
  df_python = df[(df['Q7_Part_1'] == 'Python') & (df['Q3'] == 'Romania')]
  distributie_ani = df_python.groupby('Q1').size()

  #creare grafic
  plt.figure(figsize=(10, 6))
  distributie_ani.plot(kind='bar', color='#add8e6')
  plt.title('Distributie respondenti care programeaza in Python  din Romania pe categorii de varsta')
  plt.xlabel('Categorii de varsta')
  plt.ylabel('Numar respondenti')
  plt.xticks(rotation=45)
  plt.grid(True)
  plt.show()

distributie_respondenti_Python_Romania(df)

"""distributia respondentilor femei din Romania care programeaza in Python pe categorii de varsta"""

def distributie_respondenti_femei_Python_Romania(df):
  """
  Vizualizează distributia respondentilor femei care programeaza in Python din Romania pe categorii de varsta
  :param df: dataframe-ul
  """
  df_python = df[(df['Q7_Part_1'] == 'Python') & (df['Q3'] == 'Romania') & (df['Q2'] == 'Woman')]
  distributie_ani = df_python.groupby('Q1').size()

  #creare grafic
  plt.figure(figsize=(10, 6))
  distributie_ani.plot(kind='bar', color='#febfd2')
  plt.title('Distributie respondenti femei care programeaza in Python  din Romania pe categorii de varsta')
  plt.xlabel('Categorii de varsta')
  plt.ylabel('Numar respondenti')
  plt.xticks(rotation=45)
  plt.grid(True)
  plt.show()

distributie_respondenti_femei_Python_Romania(df)

"""respondentii care pot fi considerati "outlieri" din punct de vedere al vechimii in programare (puteti folositi un boxplot pentru a identifica aceste valori)"""

def distributie_respondenti_vechime_outlieri(df):
  """
  Vizualizează respondentii care pot fi considerati "outlieri" din punct de vedere al vechimii in programare (puteti folositi un boxplot pentru a identifica aceste valori)
  :param df: dataframe-ul
  """
  df_python = df[(df['Q7_Part_1'] == 'Python') & (df['Q3'] == 'Romania') & (df['Q2'] == 'Woman')]
  distributie_ani = df_python.groupby('Q1').size()

  #creare grafic
  plt.figure(figsize=(10, 6))
  sns.boxplot(x=df_python['Q6'], color="#add8e6")
  plt.title('Boxplot pentru vechime in programare')
  plt.xlabel('Vechime in programare')
  plt.xticks(rotation=45)
  plt.grid(True)
  plt.show()

def outlieri(df):
  """
  Returnează respondentii care pot fi considerati "outlieri" din punct de vedere al vechimii in programare
  :param df: dataframe-ul
  :return: dataframe - dataframe-ul cu
  """
  df_python = df[(df['Q7_Part_1'] == 'Python') & (df['Q3'] == 'Romania') & (df['Q2'] == 'Woman')]
  q1 = df_python['Q6'].quantile(0.25)
  q3 = df_python['Q6'].quantile(0.75)
  iqr = q3 - q1
  lower_bound = q1 - 1.5 * iqr
  upper_bound = q3 + 1.5 * iqr
  outliers = df_python[(df_python['Q6'] < lower_bound) | (df_python['Q6'] > upper_bound)]
  print("Outlieri:")
  print(outliers[['Q6']])

outlieri(df)
distributie_respondenti_vechime_outlieri(df)

"""problema 4
normalizare - durata anilor de studii universitare, vechimea in programare
"""

from sklearn.preprocessing import MinMaxScaler, StandardScaler

def calculeaza_durata_studii(valoare):
  nr_ani = 0
  if 'Bachelor’s degree' in valoare:
    nr_ani+=3
  elif 'Master’s degree' in valoare:
    nr_ani+=2
  elif 'Doctoral degree' in valoare:
    nr_ani+=3
  return nr_ani

def transforma_col(df):
  df["Q4_new"] = df["Q4"].apply(calculeaza_durata_studii)

def normalizare(df):
  df_min_max = df.copy()
  df_z_score = df.copy()

  df_numeric=df.loc[1:, ["Q4_new","Q6"]].copy()

  #Aplic Min_Max Scaling
  scalare_minmax = MinMaxScaler()
  df_min_max.loc[1:, ["Q4_new","Q6"]] = scalare_minmax.fit_transform(df_numeric)

  #Aplic Z-score
  scalare_z_score = StandardScaler()
  df_z_score.loc[1:, ["Q4_new","Q6"]] = scalare_z_score.fit_transform(df_numeric)

  fig, axes = plt.subplots(2, 3, figsize=(15, 8))

  #Histograma initiala
  axes[0, 0].hist(df["Q4_new"][1:], bins=12, alpha=0.6, color="#add8e6")
  axes[0, 0].set_title("Durata studii superioare")
  axes[0, 1].hist(df["Q6"][1:], bins=12, alpha=0.6, color="#149414")
  axes[0, 1].set_title("Vechime in programare")

  #Min-Max Scaling
  axes[1, 0].hist(df_min_max["Q4_new"][1:], bins=12, alpha=0.6, color="#add8e6")
  axes[1, 0].set_title("Durata studii superioare (Min-Max Scaling)")
  axes[1, 1].hist(df_min_max["Q6"][1:], bins=12, alpha=0.6, color="#149414")
  axes[1, 1].set_title("Vechime in programare (Min-Max Scaling)")

  #Z-score
  axes[1, 2].hist(df_z_score["Q4_new"][1:], bins=12, alpha=0.6, color="#add8e6")
  axes[1, 2].set_title("Durata studii superioare (Z-score)")
  axes[0, 2].hist(df_z_score["Q6"][1:], bins=12, alpha=0.6, color="#149414")
  axes[0, 2].set_title("Vechime in programare (Z-score)")

  print("Valori inițiale:\n", df_numeric)
  print("Min-Max Scaling:\n", df_min_max[["Q4_new", "Q6"]])
  print("Z-score Scaling:\n", df_z_score[["Q4_new", "Q6"]])

  plt.tight_layout()
  plt.show()

transforma_col(df)
normalizare(df)


    
