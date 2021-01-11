# -*- coding: utf-8 -*-
"""
Created on Wed Feb 12 10:17:49 2020

@author: Mark
"""
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from sklearn.metrics import classification_report, confusion_matrix
import statsmodels.api as sm
import statsmodels.formula.api as smf
from sklearn.preprocessing import PolynomialFeatures



#import statsmodels.regression.linear_model.OLS
# statsmodels module a little bit before starting your lab 2. It is a module 
# that is used for constructing linear regression models as well as generating 
# reports including P-value, R-square, Pearson's r, etc. (the "scikit-learn" does 
# not provide these kinds of information).

 
#print(results.summary())
#For easily fitting a model with interaction terms, you can explore the from_formula method in "statsmodels.regression.linear_model.OLS

print('start')
data = pd.read_excel(r'C:\Users\Mark\Documents\CS467\Lab 2 Data\Folds5x2_pp.xlsx',)
df = data

#####################################
#part b, part I
#There are 9568 rows and 5 columns
#Each row is an hourly average
#each column is a different measurement.
#- Temperature (T) in the range 1.81°C and 37.11°C,
#- Ambient Pressure (AP) in the range 992.89-1033.30 milibar,
#- Relative Humidity (RH) in the range 25.56% to 100.16%
#- Exhaust Vacuum (V) in teh range 25.36-81.56 cm Hg
#- Net hourly electrical energy output (EP) 420.26-495.76 MW

################################################
#part b, part II
sns.set(style="ticks", color_codes=True)
g = sns.pairplot(data)
plt.legend(loc='lower right')
plt.show()
################

################################################
#part b, part III
table = pd.DataFrame(index=['Mean', 'Median', 'Range','Q1', 'Q3','IQR'])

mycolumns = df.columns.to_list()
for X in mycolumns:
    Mean = df.AT.mean()
    table.loc['Mean', X] = df[X].mean()
    table.loc['Median', X] = df[X].median()
    table.loc['Range', X] = df[X].max() - df[X].min()
    table.loc['Q1', X] = np.percentile(df[X], [25])
    table.loc['Q3', X] = np.percentile(df[X],  [75])
    table.loc['IQR', X] = IQR = np.percentile(df[X],  [75]) - np.percentile(df[X], [25])
    
    Mean = df[X].mean()
    Median = df[X].median()
    Range = df[X].max() - df[X].min()
    Q1 = np.percentile(df[X], [25])
    Q3 = np.percentile(df[X],  [75])
    IQR = np.percentile(df[X],  [75]) - np.percentile(df[X], [25])
    mylist = [Mean, Median, Range, Q1, Q3, IQR]
###############################################
    
    
    
    
    
###############################################
    #part c
    ####running single regressions
results_AT = smf.ols('PE ~ AT', data=df).fit()
print(results_AT.summary())
results_V = smf.ols('PE ~ V', data=df).fit()
print(results_V.summary())
results_AP = smf.ols('PE ~ AP', data=df).fit()
print(results_AP.summary())
results_RH = smf.ols('PE ~ RH', data=df).fit()
print(results_RH.summary())


AT = df['AT'] 
V = df['V']
AP = df['AP']
RH = df['RH']
PE = df['PE']

ypred_AT = results_AT.predict(df['AT'])
ypred_V = results_V.predict(df['V'])
ypred_AP = results_AP.predict(df['AP'])
ypred_RH = results_RH.predict(df['RH'])




#####plotting
plt.figure(1)
plt.scatter(AT, PE)
plt.title('Temperature vs. Power')
plt.plot(AT, ypred_AT, color='red')

plt.figure(2)
plt.scatter(V, PE)
plt.title('Vacuum vs. Power')
plt.plot(V, ypred_V, color='red')

plt.figure(3)
plt.scatter(AP, PE)
plt.title('Ambient Pressure vs. Power')
plt.plot(AP, ypred_AP, color='red')

plt.figure(4)
plt.scatter(RH, PE)
plt.title('Relative Humidity vs. Power')
plt.plot(RH, ypred_RH, color='red')


##################################################
#part d
results_all = smf.ols('PE ~ AT + V + AP + RH', data=df).fit()
print(results_all.summary())


#all had very small p values so we reject the null for all
ypred_polyRH = results_all.predict(df['RH'])

plt.figure(5)
plt.scatter(RH, PE)
plt.plot(RH, ypred_polyRH, color='red')





########################################
#part e
my_array_AT = results_AT.params
my_array_V = results_V.params
my_array_AP = results_AP.params
my_array_RH = results_RH.params
my_array_all = results_all.params

x_simple_reg = [my_array_AT[1], my_array_V[1], my_array_AP[1], my_array_RH[1]]
y_multiple_reg = [my_array_all[1], my_array_all[2], my_array_all[3], my_array_all[4]]
plt.scatter(x_simple_reg, y_multiple_reg)
#######################################



######################
###attempting part f
results_polyRH = smf.ols('PE ~ RH + np.power(RH, 2) ', data=df).fit()
ypred_polyRH = results_all.predict(df['RH'])

plt.figure(1)
plt.scatter(RH, PE)
plt.plot(RH, ypred_polyRH, color='red')


results_polyAT = smf.ols('PE ~ AT + np.power(AT, 2) ', data=df).fit()
ypred_polyAT = results_all.predict(df['AT'])

plt.figure(2)
plt.scatter(AT, PE)
plt.plot(AT, ypred_polyAT, color='red')

results_polyV = smf.ols('PE ~ V + np.power(V, 2) ', data=df).fit()
ypred_polyV = results_all.predict(df['V'])
plt.figure(3)
plt.scatter(V, PE)
plt.plot(V, ypred_polyV, color='red')

results_polyAP = smf.ols('PE ~ AP + np.power(AP, 2) ', data=df).fit()
ypred_polyAP = results_all.predict(df['AP'])

plt.figure(4)
plt.scatter(AP, PE)
plt.plot(AP, ypred_polyAP, color='red')



polynomial_features= PolynomialFeatures(degree=2)
xp = polynomial_features.fit_transform(x)

poly_features = PolynomialFeatures(2)
#key line here

combined = np.vstack((AT, PE)).T
#poly_reg = poly_features.fit(combined)
poly_reg = poly_features.fit_transform(combined)
#running the line without transform it does not work


model_polyAT = sm.OLS(PE, poly_reg).fit()
ypred_polyAT = model_polyAT.predict(poly_reg)

plt.figure(5)
plt.scatter(AT, PE)
plt.plot(AT, ypred_polyAT, color='red')


#model_polyAT.summary()


#################################################################
#part g
#do the long line that does all interactions using lmline stuff inR
results_pairwise = smf.ols('PE ~ AT + V + AP + RH + AT:V + AT:AP + AT:RH + V:AP + V:RH + AP:RH ', data=df).fit()
print(results_pairwise.summary())




#################################################################
#part h
from sklearn import neighbors
n_neighbors = 5
neigh = neighbors.KNeighborsRegressor(n_neighbors)
X_raw = df[['AT', 'V', 'AP', 'RH']]
Y_raw = df['PE']


neigh.fit(X_raw,Y_raw)
knn_pred = neigh.predict(X_raw)    
knn_pred = pd.Series(knn_pred)
acc = metrics.mean_squared_error(Y_raw, knn_pred)




#part h
from sklearn import neighbors
n_neighbors = 5
neigh = neighbors.KNeighborsRegressor(n_neighbors)
X_raw = df[['AT', 'V', 'AP', 'RH']]
Y_raw = df['PE']

neigh.fit(X_raw,Y_raw)
knn_pred = neigh.predict(X_raw)    
knn_pred = pd.Series(knn_pred)
acc = metrics.mean_squared_error(Y_raw, knn_pred)
errors = []
for k in range(0,100):
    neigh = neighbors.KNeighborsRegressor(n_neighbors)
    neigh.fit(X_raw,Y_raw)
    knn_pred = neigh.predict(X_raw)    
    knn_pred = pd.Series(knn_pred)
    acc = metrics.mean_squared_error(Y_raw, knn_pred)
    errors.append(acc)


print(errors.index(min(errors)))





for i, weights in enumerate(['uniform', 'distance']):
    knn = neighbors.KNeighborsRegressor(n_neighbors, weights=weights)
    y_ = knn.fit(X, y).predict(T)

    plt.subplot(2, 1, i + 1)
    plt.scatter(X, y, color='darkorange', label='data')
    plt.plot(T, y_, color='navy', label='prediction')
    plt.axis('tight')
    plt.legend()
    plt.title("KNeighborsRegressor (k = %i, weights = '%s')" % (n_neighbors,
                                                                weights))

plt.tight_layout()
plt.show()

        k_value = k
        mydict = {'k_value' : k_value, 'test_error' : test_err, 
                  'training_error' : training_err }
        
        errors = []
        errors = errors.append(mydict, ignore_index=True)

##############################

#.reshape(-1,1)




#ggplot


#scatt(test:1, ep_test_T)
#plot(T_tes[:1], EP_pred_)T
#manually add constant?

#polynomial_results_RH = 
    




    





#head.set = []
#add all the columnn names
#names = head set
#info = ["mean, Median, ]

#
#for x,y in head_set, back_set:
#can run too for loops together at the same time
#print(regressor.params)
#coding knn from scratch?



