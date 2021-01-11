# -*- coding: utf-8 -*-
"""
Created on Mon Mar  2 18:10:12 2020

@author: Mark
"""

import numpy as np
import pandas as pd
import seaborn as sns
import statsmodels.api as sm
from sklearn.metrics import auc

data = pd.read_csv(r'C:\Users\Mark\Documents\CS467\Lab 3 Data\wdbc.data', names = 
                   [ 'ID', 'Diagnosis', 'Radius', 'Texture', 'Perimeter', 'Area', 
                    'Smoothness' ])

data = pd.read_csv(r'C:\Users\Mark\Documents\CS467\Lab 3 Data\wdbc.data', header=None)
data = data.sort_values(by=[1])
data.reset_index(inplace=True)
df = data
df.drop(columns=['index'], inplace=True)


#remember shallow copies


train = df.iloc[0:50]
train = train.append(df.iloc[357:387])

#train.rename(columns={0:'Label'}, inplace=True)


#
#
#sns.set(style="ticks", color_codes=True)
#g = sns.pairplot(train, hue='Label')
#plt.legend(loc='lower right')
#plt.show()



def replace(row):
    if row[1] == 'B':
        return 0
    else:
        return 1
train['Label'] = df.apply(lambda x: replace(x), axis=1)



trainX = train[[2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]]
trainY = train['Label']

logit = sm.Logit(trainY,trainX )
result = logit.fit(Max_Iter=10)



print(result.summary())
import statsmodels.formula.api as smf
model = smf.glm(formula = formula, data=train, family=sm.families.Binomial())
result = model.fit()
print(result.summary())


x = trainX.corr()

logit.fit().params

for x in df.columns:
    if (df[x].dtype == np.bool):
        df[x] = df[x].astype(np.float64)



#it's the datatype of trainY???
#import sklearn
#from sklearn.linear_model import LogisticRegression as LR
#logr = LR()
#logr.fit( trainX, trainY )
#results = logr.predict( trainX)




