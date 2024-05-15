import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

from ucimlrepo import fetch_ucirepo

# fetch dataset 
breast_cancer_wisconsin_diagnostic = fetch_ucirepo(id=17)

# data (as pandas dataframes) 
X = breast_cancer_wisconsin_diagnostic.data.features
y = breast_cancer_wisconsin_diagnostic.data.targets

# metadata 
print(breast_cancer_wisconsin_diagnostic.metadata)

# variable information 
print(breast_cancer_wisconsin_diagnostic.variables) 