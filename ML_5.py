# -*- coding: utf-8 -*-
"""
Created on Wed Apr  8 00:13:04 2020

@author: Mark
"""


 

import statsmodels.api as sm
import statsmodels.formula.api as smf

import pandas as pd
import numpy as np
from sklearn import metrics
from sklearn.metrics import confusion_matrix
from sklearn import tree
from sklearn.tree import _tree
 
print('5')
 
############ PART 1 ###########################################################
feature_names = ['Temperature', 'Nausea', 'Lumbar pain', 'Urine pushing', 'Micturition pain',
                 'Burning of urethra', 'Inflammation', 'Nephritis']
 
data = pd.read_csv(r'C:\Users\morrismr\Documents\tennis_files\Lab 5 Data\diagnosis.csv', encoding='utf-16',
                   sep = '\t', decimal = ',', names = feature_names)
df = data
#df['0'] = [x.replace(',', '.') for x in df['0']]
#df['0'] = df['0'].astype(float)
 
#for x in feature_names:
#    if x!= 'Temperature':
#        df[x].replace(('yes', 'no'), (1,0), inplace=True)
       
 
 
df['Nausea'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Lumbar pain'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Urine pushing'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Micturition pain'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Burning of urethra'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Inflammation'].replace(('yes', 'no'), (1, 0), inplace=True)
df['Nephritis'].replace(('yes', 'no'), (1, 0), inplace=True)
 
X = df.iloc[:,0:6]
Y = df.iloc[:,6:8]
 
clf = tree.DecisionTreeClassifier()
clf = clf.fit(X, Y)
tree.plot_tree(clf.fit(X, Y))
 
yo = clf.predict(X)
 
from sklearn.metrics import accuracy_score
y_pred = clf.predict(X)
y_true = Y
#accuracy_score(X,Y)
 
 
 
 
 
 
def tree_to_pseudo(tree, feature_names):
 
              '''
              Outputs a decision tree model as if/then pseudocode
             
              Parameters:
              -----------
              tree: decision tree model
                             The decision tree to represent as pseudocode
              feature_names: list
                             The feature names of the dataset used for building the decision tree
              '''
 
              left = tree.tree_.children_left
              right = tree.tree_.children_right
              threshold = tree.tree_.threshold
              features = [feature_names[i] for i in tree.tree_.feature]
              value = tree.tree_.value
 
              def recurse(left, right, threshold, features, node, depth=0):
                             indent = "  " * depth
                             if (threshold[node] != -2):
                                           print (indent,"if ( " + features[node] + " <= " + str(threshold[node]) + " ) {")
                                           if left[node] != -1:
                                                          recurse (left, right, threshold, features, left[node], depth+1)
                                                          print (indent,"} else {")
                                                          if right[node] != -1:
                                                                        recurse (left, right, threshold, features, right[node], depth+1)
                                                          print (indent,"}")
                             else:
                                           print (indent,"return " + str(value[node]))
 
              recurse(left, right, threshold, features, 0)
 
 
tree_to_pseudo(clf,feature_names)
#last two columns yo
 
 
 
############ PART 2 ###########################################################
feature_names = []
for x in range(0,128):
    feature_names.append(x)
   
 ###########part a ###############  
communities = pd.read_csv(r'C:\Users\morrismr\Documents\tennis_files\Lab 5 Data\communities.csv',
                   sep = ',', names = feature_names)
df = communities
 
 
train = df.iloc[0:1495]
test = df.iloc[1495:1995]
 
############ part b ########################
 
#dropping non predictive features
train.drop(columns = [0,1,2,3,4], inplace=True)
test.drop(columns = [0,1,2,3,4], inplace=True)
 
#This runs column by column and fills in the missing values in each column with
#that columns' respective mean. Note we split the process by training and test set.
train.fillna(train.mean())
test.fillna(test.mean())
 
 
import matplotlib.pyplot as plt
 
plt.matshow(df.corr())
plt.show()
print(df.corr())
 
import seaborn as sns
corr = df.corr()
ax = sns.heatmap(
    corr,
    vmin=-1, vmax=1, center=0,
    cmap=sns.diverging_palette(20, 220, n=200),
    square=True
)
ax.set_xticklabels(
    ax.get_xticklabels(),
    rotation=45,
    horizontalalignment='right'
);
#source--https://towardsdatascience.com/better-heatmaps-and-correlation-matrix-plots-in-python-41445d0f2bec
 
       
stds = train.std(axis = 0)
means = train.mean(axis = 0)
 

 
cov = [float(b) / float(m) for b,m in zip(stds,means)]
cov.sort(reverse=True)
#floor of root (122) is 11
#
#for x in range(0,11):
#    bananasplit[x]
#   
# sns.boxplot(x=5, y =127, hue =127, palette=["b", "g"], data=df) 
 
import statsmodels.api as sm
results = smf.




