# -*- coding: utf-8 -*-
"""
Created on Sat Jan 25 21:45:11 2020

@author: Mark
"""


import pandas as pd
import numpy as np
from scipy.io import arff
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from sklearn.metrics import classification_report, confusion_matrix
import math

#need to fix using all the variables in my knn neighbors call even
#fix capitalizing
#if getting the n_neighbors error, it's because X_train's value gets reset
#when the variable name gets re-used later on  



print('start')

data = arff.loadarff(r'C:\Users\Mark\Documents\CS467\column_2C_weka.arff')
df = pd.DataFrame(data[0])
df.head()
df['Class'] = df['class'].str.decode('utf-8') 

#checking 
#np.where(pd.isnull(df))
#pd.isna(df['class'])
#df[df['class'] == ''].index


    sns.set(style="ticks", color_codes=True)
    g = sns.pairplot(df, hue = 'class')
    plt.legend(loc='lower right')
    plt.show()
 Use the 'hue' argument to provide a factor variable
sns.lmplot( data=df, fit_reg=False, hue='class', legend=False)
#
#fig, ax = plt.subplots()
#pos = np.array([1,2,3,4,5,6])
#bp = ax.boxplot(x = "class", y = , positions = pos)
sns.boxplot(x="Class", y="pelvic_incidence", hue="class", palette=["b", "g"],data=df)
sns.boxplot(x="Class", y="pelvic_tilt",hue="class", palette=["b", "m"], data=df)
sns.boxplot(x="Class", y="lumbar_lordosis_angle",hue="class", palette=["b", "g"], data=df)
sns.boxplot(x="Class", y="sacral_slope",hue="class", palette=["b", "g"], data=df)
sns.boxplot(x="Class", y="pelvic_radius",hue="class", palette=["b", "g"], data=df)
sns.boxplot(x="Class", y="degree_spondylolisthesis",hue="class", palette=["b", "g"], data=df)


#  use concat(frames)
#subplot(1,6)
#
#add each one 
#make it wider


#https://stackoverflow.com/questions/49806439/letter-appeared-in-data-when-arff-loaded-into-python

def label_race (row):
    if row['Class'] == 'Abnormal' :
        return 1
    else:
        return 0
df['Class_Num'] = df.apply (lambda row: label_race(row), axis=1)

training = df.iloc[0:140] #it starts with class 1
needToAppend = df.iloc[210:280] #it's all in order
training = training.append(needToAppend)


test = df.iloc[140:210]
test = test.append(df.iloc[281::])


X_train = training[['pelvic_incidence', 'pelvic_tilt', 'lumbar_lordosis_angle',
                   'sacral_slope','pelvic_radius', 'degree_spondylolisthesis'  ] ]
#that worked? to make it a dataframe~
X_test = test[['pelvic_incidence', 'pelvic_tilt', 'lumbar_lordosis_angle',
                   'sacral_slope','pelvic_radius', 'degree_spondylolisthesis'  ] ]
Y_train = training['Class_Num']
Y_test = test['Class_Num']
                                     
knn = KNeighborsClassifier(n_neighbors=5, metric='euclidean')
knn.fit(X_train, Y_train)

y_test_pred = knn.predict(X_test)


y_test = df['Class_Num'][140:210]
y_test = y_test.append(df['Class_Num'][281::])

#the actual values in class sliced out

errors = pd.DataFrame(columns = ['k_value','test_error', 'training_error'])
################################### Function to use later on ###################
def my_k_guy(N, errors, my_X_train, my_Y_train):
    
    for k in range (1, N, 3):
        knn = KNeighborsClassifier(n_neighbors= k , metric='euclidean')
        knn.fit(my_X_train, my_Y_train)
        
        y_training_pred = knn.predict(my_X_train)
        y_test_pred = knn.predict(X_test)
        
        test_err = 1 - metrics.accuracy_score(Y_test, y_test_pred)
        training_err = 1 - metrics.accuracy_score(my_Y_train, y_training_pred)

        k_value = k
        mydict = {'k_value' : k_value, 'test_error' : test_err, 
                  'training_error' : training_err }
        
        
        errors = errors.append(mydict, ignore_index=True)
        
    print('done')
    best_k_value = errors['k_value'][errors['test_error'].idxmin()]
    best_test_error = errors['test_error'].min()
    return [best_k_value, best_test_error]

###########################
#Part B
    
############################### Plotting training, test error against k##########
for k in range (208, 1, -3):
        knn = KNeighborsClassifier(n_neighbors= k , metric='euclidean')
        knn.fit(X_train, Y_train)
        
        y_training_pred = knn.predict(X_train)
        y_test_pred = knn.predict(X_test)
        
        test_err = 1 - metrics.accuracy_score(Y_test, y_test_pred)
        training_err = 1 - metrics.accuracy_score(Y_train, y_training_pred)

        k_value = k
        mydict = {'k_value' : k_value, 'test_error' : test_err, 
                  'training_error' : training_err }
        
        errors = errors.append(mydict, ignore_index=True)
        
errors['1/k_value'] = errors['k_value'].apply(lambda x: 1/x)
errors.plot(x = '1/k_value', y = ['test_error', 'training_error'])
    
print('done done')   



########################## Dispalying statistics for argmin k #################
errors = pd.DataFrame(columns = ['k_value','test_error', 'training_error'])
part_b_results = my_k_guy(208, errors, X_train, Y_train)
knn = KNeighborsClassifier(n_neighbors= int(part_b_results[0]) , metric='euclidean')
knn.fit(X_train, Y_train)

y_training_pred = knn.predict(X_train)
y_test_pred = knn.predict(X_test)

test_err = 1 - metrics.accuracy_score(Y_test, y_test_pred)
training_err = 1 - metrics.accuracy_score(Y_train, y_training_pred)

confusionMatrix = confusion_matrix(Y_test, y_test_pred)

print(confusion_matrix(Y_test, y_test_pred))
true_neg = confusionMatrix[0][0]
true_pos = confusionMatrix[1][1]
false_pos = confusionMatrix[0][1]
precision = true_pos /(true_pos + false_pos)
f_score = (1 + 1**2)*precision*true_pos/(1**2*precision + true_pos)

#######################################################################




#####################
#PART C

learning_curve = pd.DataFrame(columns=['training_size', 'best_k_value','min_test_error'])
for N in range(10, 210, 10):
    first_index = N-math.floor(N/3)
    loop_training = df.iloc[0:first_index]
    stop_index = 210 + math.floor(N/3)
    loop_needToAppend = df.iloc[210:stop_index] 
    loop_training = loop_training.append(needToAppend)
    
    loop_X_train = loop_training[['pelvic_incidence', 'pelvic_tilt', 'lumbar_lordosis_angle',
                   'sacral_slope','pelvic_radius', 'degree_spondylolisthesis'  ] ]
    loop_Y_train = loop_training['Class_Num']
    

    errors = pd.DataFrame(columns = ['k_value','test_error', 'training_error'])
    
    results = my_k_guy(N, errors, loop_X_train, loop_Y_train)
    best_k_value = results[0]
    min_test_error = results[1]
    mydict2 = {'training_size' : N, 'best_k_value' : best_k_value, 'min_test_error' : min_test_error}
    learning_curve = learning_curve.append(mydict2, ignore_index=True)
    
print('done done')   

learning_curve.plot(x = 'training_size', y = ['min_test_error'])
learning_curve.plot(x = 'training_size', y = ['best_k_value'])

#############################################################################

#plt.figure(figsize=(12, 6))
#plt.plot(range(1, 40), error, color='red', linestyle='dashed', marker='o',
#         markerfacecolor='blue', markersize=10)
#plt.title('Error Rate K Value')
#plt.xlabel('K Value')
#plt.ylabel('Mean Error')


#bottom of picture (missing) this line): return best_k, best_te_err_rate
#python for dat science datacamp.com
 #sina's seaborn cheat sheet
 #fig.setheight
 #fig.setwidth
 


#    
#    precision = ture_positive / (true positive + false negative)
#    recall = true positve/(true positive + false negatvie)
#    
#    f_score = 2* (precision * recall)/ (precision + recall)
#    sklearn.metrics.f1_score library to find f score


#df[]
#df.loc[]
#df.iloc[]

#do f10 do it? create the nice figure?
#When you call loc with a scalar value, you get a pd.Series. That series will then have one dtype. If you want to see the row as it is in the dataframe, you'll want to pass an array like indexer to loc.



