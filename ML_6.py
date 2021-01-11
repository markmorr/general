# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 23:27:14 2020

@author: Mark
"""

import pandas as pd
import numpy as np
import tensorflow as tf
import math
import timeit
import matplotlib.pyplot as plt
from six.moves import cPickle as pickle
import os
import platform
from subprocess import check_output
import keras
import scipy as sp
import seaborn as sns
import tensorflow as tf
import tqdm
from keras import regularizers
from keras.callbacks import ModelCheckpoint
from keras.datasets import cifar10
from keras.layers import (
    Activation,
    Conv2D,
    Dense,
    Dropout,
    Flatten,
    MaxPooling2D,
    Reshape,
    Softmax,
)

from keras.models import Sequential
from keras.preprocessing.image import ImageDataGenerator
from keras.utils import np_utils
from scipy.spatial.distance import euclidean
from sklearn.cluster import KMeans
from sklearn.metrics import accuracy_score
from sklearn.metrics.pairwise import euclidean_distances
from sklearn.model_selection import train_test_split
from sklearn.neighbors import DistanceMetric
from sklearn.preprocessing import LabelEncoder, OneHotEncoder
from tensorflow.python.client import device_lib
from keras.datasets import cifar10

import random
from random import randrange

import fbprophet
#part a##############
(x_train, y_train), (x_test, y_test) = cifar10.load_data()


# #i was trying
# x_train = x_train[y_train == 2, :, :] not sure why it didn't work

#part b ##############
def myguy(x,y,i):
    y = np.array(y)
    
    pos_i = np.argwhere(y == i)
    
    pos_i = list(pos_i[:,0])
    
    x_i = [x[j] for j in pos_i]
    
    return np.asarray(x_i)


x_train_birds = myguy(x_train, y_train, 2)
x_test_birds = myguy(x_test, y_test, 2)
#print shape to prove it's the right shape!*

#print shape to show it worked in google colab
total_birds = np.concatenate((x_train_birds, x_test_birds))
tb = total_birds
print(tb.size)
#thanks for the helpful error message numpy

RGB_vectors = np.zeros(shape=(6000,3))
for i in range(0,6000):
  for j in range(0,32):
    for k in range(0,32):
      RGB_vectors[i] = tb[i][j][k]
print(RGB_vectors.shape)
print(RGB_vectors[0])



from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters = 4).fit(RGB_vectors)
kmeans_output = kmeans.labels_   
main_colors = kmeans.cluster_centers_ #this  is stupidly named

import math
from scipy.spatial import distance
tetrachrome = np.zeros(shape=(6000,32,32,3))
#convert to integers 
for i in range(0,4):
    for j in range(0,3):
          main_colors[i][j] = int(main_colors[i][j])
main_colors = main_colors.astype(int)
print(main_colors[1][2].type)

print("first 10 images")
fig = plt.figure(figsize = (9,3))
for i in range(0,10):
    ax = fig.add_subplot(2,5,i+1)
    plt.imshow(total_birds[i])
    plt.show()

#ok so gotta 
#############################
percent_pixels = .80
P = .80 * 6000 * 32 * 32
print(P)
          
#this gives the cluster each RGB vector was assigned to
# kmeans.predict uses Euclidean distance by default to estimate closest?  

fig = plt.figure(figsize = (9,3))
for i in range(0,10):
    ax = fig.add_subplot(2,5,i+1)
    plt.imshow(tetrachrome[i])
    plt.show()

  
    
from skimage import data  
from skimage.color import rgb2gray
grayscale = np.zeros(shape = (6000,32,32))

for i in range(0,6000):
    original = tb[i]
    grayscale[i] = rgb2gray(original)

for i in range(0,3):
    fig, axes = plt.subplots(1, 2, figsize=(8, 4))
    ax = axes.ravel()
    
    ax[0].imshow(tb[i])
    ax[0].set_title("Original")
    ax[1].imshow(grayscale[i], cmap=plt.cm.gray)
    ax[1].set_title("Grayscale")
    
    fig.tight_layout()
    plt.show()
    


#each image is 32X32 pixels
#we have 6000 of them
#pick 80% of these randomly. each pixel is an RGB vector

