# -*- coding: utf-8 -*-
"""
Created on Mon Mar 23 14:49:43 2020

@author: Mark
"""
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 27 17:14:55 2020

@author: morrismr
"""

################# Part a ######################################################

import pandas as pd
import numpy as np
import math
from sklearn.feature_extraction.text import TfidfVectorizer
from nltk.corpus import stopwords
from sklearn.linear_model import LogisticRegression
from sklearn import metrics
from sklearn.metrics import confusion_matrix
from sklearn.metrics import roc_auc_score
from sklearn.metrics import roc_curve
import matplotlib.pyplot as plt
data = pd.read_csv(r'C:\Users\Mark\Documents\CS467\Lab 4 Data\YouTube-Spam-Collection-v1\Youtube04-Eminem.csv')

# data = pd.read_csv(r'Lab 4 Data\YouTube-Spam-Collection-v1\Youtube04-Eminem.csv')




data = data.sort_values(by = 'CLASS')
data.reset_index(inplace=True)
data.drop(columns=['index'], inplace=True)

#df.iloc[lambda x: x.index % 2 == 0]

################# Part b ######################################################
H = data[data.CLASS==0].sum()
H = math.floor(.8*203)
S = math.floor(.8*(245))

df = data
train = df.iloc[0:162]
train = train.append(df.iloc[203:399])
test = df.iloc[162:203]
test = test.append(df.iloc[399:])

################# Part c ######################################################


vectorizer = TfidfVectorizer()
vectors = vectorizer.fit_transform(df['CONTENT'])
feature_names = vectorizer.get_feature_names()
dense = vectors.todense()
denselist = dense.tolist()
df2 = pd.DataFrame(denselist, columns=feature_names)


pre_x_train = denselist[0:162]
pre_x_train.extend(denselist[203:399])
x_train = pd.DataFrame(pre_x_train)
y_train = train['CLASS']

pre_x_test = denselist[162:203]
pre_x_test.extend(denselist[399:])
x_test = pd.DataFrame(pre_x_test)
y_test = test['CLASS']

################# Part d ######################################################


from sklearn.metrics import recall_score
from sklearn.metrics import precision_score
from sklearn.metrics import accuracy_score
from sklearn.metrics import f1_score
from sklearn.metrics import fbeta_score
from sklearn.linear_model import RidgeClassifierCV
from sklearn.linear_model import LogisticRegressionCV

# part i
#training set
myarr = [10e-5, 10e-4, 10e-3, 10e-3, 10e-2, 10e-1, 10e0, 10e1, 10e2, 10e3, 10e4, 10e5]
a = np.array(myarr)
a = np.power(a,-1) #adjusting by raising to -1 exponent because the parameter is C^-1
ridgeclassifier = RidgeClassifierCV(alphas=a, cv=5).fit(x_train, y_train)
ridgeclassifier.score(x_train, y_train)
ridgeclassifier.get_params()
optimal_lambda = ridgeclassifier.alpha_
print("Optimal lambda: " + str(optimal_lambda))


def print_ROC(y_true, y_pred, title):
    auc_score = roc_auc_score(y_true, y_pred)  
    fpr, trp, thresholds_test = roc_curve(y_true, y_pred)
    plt.plot([0,1], [0,1], 'r--')
    plt.plot(fpr, trp, 'b', label = title)
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title(title)
    plt.show()
    print(auc_score)
    
def print_metrics(input_y_true, input_y_pred):
    # print("Confusion matrix: " + str(confusion_matrix(input_y_true,input_y_pred))
    x = str(accuracy_score(input_y_true, input_y_pred))
    print("Accuracy Score: " + x)
    x = str(precision_score(input_y_true, input_y_pred))
    print("Precision: " + x)
    x = str(recall_score(input_y_true, input_y_pred))
    print("Recall: " + x)
    x = str(f1_score(input_y_true, input_y_pred))
    print("F1 Score: " + x)
    
    

#part ii
#Training set

y_pred = ridgeclassifier.predict(x_train)
y_pred = pd.Series(y_pred)
y_true = y_train
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'L2 Penalized Logit Training Set ROC Curve')


#part iii ##########################################################
#TEST SET


y_pred = ridgeclassifier.predict(x_test)
y_pred = pd.Series(y_pred)
y_true = y_test
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'L2 Penalized Logit Test Set ROC Curve')

beta_array = [.1, .5, .9, 1, 5, 10]
for x in beta_array:
    Fb = fbeta_score(y_true, y_pred, beta=x)
    print("A beta of " + str(x) + " yields an F-beta score of: " + str(Fb))

# confusion_matrix(y_true,y_pred)
# accuracy_score(y_true, y_pred)
# precision_score(y_true, y_pred, average='macro')
# recall_score(y_true, y_pred)
# f1_score(y_true, y_pred)


###


################# Part e ######################################################

#training
#Part i
logisticclassifier = LogisticRegressionCV(cv=5, random_state=0).fit(x_train, y_train)
y_pred = logisticclassifier.predict(x_train)
y_pred = pd.Series(y_pred)
y_true = y_train
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'L1 Penalized Logit Training Set ROC Curve')



#test
#Part ii
y_pred = logisticclassifier.predict(x_test)
y_pred = pd.Series(y_pred)
y_true = y_test
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'L1 Penalized Logit Test Set ROC Curve')

    



################# Part f ######################################################
from sklearn.naive_bayes import GaussianNB
nbclassifier = GaussianNB()
nbclassifier.fit(x_train, y_train)
GaussianNB()

train_proba = nbclassifier.predict_proba(x_train)
train_proba = train_proba[:,1]
test_proba = nbclassifier.predict_proba(x_test)
test_proba = test_proba[:,1]

################## Training
y_pred = nbclassifier.predict(x_train)
y_pred = pd.Series(y_pred)
y_true = y_train
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'Naive Bayes Training Set ROC Curve')


##################Test#######################3
y_pred = nbclassifier.predict(x_test)
y_pred = pd.Series(y_pred)
y_true = y_test
print_metrics(y_true, y_pred)
print_ROC(y_true,y_pred, 'Naive Bayes Test Set ROC Curve')














































































