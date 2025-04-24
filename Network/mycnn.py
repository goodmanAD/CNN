#!/usr/bin/env python
# coding: utf-8

import sys
import os
import pathlib
import numpy as np


import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.callbacks import EarlyStopping, ModelCheckpoint, ReduceLROnPlateau
from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense, Conv2D, MaxPool2D, Flatten, Dropout, AveragePooling2D, BatchNormalization
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing import image
from tensorflow.keras.optimizers import RMSprop
from sklearn.metrics import roc_curve,auc

images_dir='./images'
train_dir = os.path.join(images_dir, 'Training')
test_dir  = os.path.join(images_dir, 'Testing')
train_class1_dir = os.path.join(train_dir,'HiPt')
train_class2_dir = os.path.join(train_dir,'LoPt')
test_class1_dir = os.path.join(test_dir,'HiPt')
test_class2_dir = os.path.join(test_dir,'LoPt')

#Class1 is thus Hi, Class2 is thus Lo

print('--- Statistics on dataset ---')
print('Number of Class1 training images:', len(os.listdir(train_class1_dir)))
print('Number of Class2 training images:', len(os.listdir(train_class2_dir)))
print('---')
print('Number of Class1 test images:', len(os.listdir(test_class1_dir)))
print('Number of Class2 test images:', len(os.listdir(test_class1_dir)))
print('---')


# We declare a few image generators. These will feed images
# batchwise to the network


imgen_train_augment = tf.keras.preprocessing.image.ImageDataGenerator(rescale=1./255, horizontal_flip=True)
#imgen_train_augment = tf.keras.preprocessing.image.ImageDataGenerator(rescale=1./255, horizontal_flip=True, rotation_range=10, fill_mode="nearest")
imgen_train = tf.keras.preprocessing.image.ImageDataGenerator(rescale=1./255)
imgen_test = tf.keras.preprocessing.image.ImageDataGenerator(rescale=1./255)

BATCH_SIZE = 32
#Rescale images to
IMG_HEIGHT = 128
IMG_WIDTH  = 128

#classes listed as background, signal -- FIRST ONE IS BKG
#Need to test by not giving it,
#because it does not seem like the actual names is mattering
train_data = imgen_train.flow_from_directory(batch_size=BATCH_SIZE, shuffle=True,
                                             target_size=(IMG_HEIGHT,IMG_WIDTH),
                                             directory=train_dir,
                                             class_mode='binary',color_mode='grayscale',
                                             classes = list(['LoPt','HiPt']))

test_data = imgen_test.flow_from_directory(batch_size=BATCH_SIZE, shuffle=True,
                                           target_size=(IMG_HEIGHT,IMG_WIDTH),
                                           directory=test_dir,
                                           class_mode='binary',color_mode='grayscale',
                                           classes = list(['LoPt','HiPt']))


#Callbacks
#cb = [ReduceLROnPlateau(patience=2), #EarlyStopping(patience=5, verbose=1), 
cb =  [ModelCheckpoint(filepath='best_model.h5',
                       monitor='val_accuracy', verbose=1, save_best_only=True, mode='max')]
#We have commented out the early stopping, let the model train for full epochs.



#Define the model
model = Sequential()
model.add(Conv2D(32, (5,5), strides=(1,1), activation='relu',kernel_initializer='he_uniform', padding='SAME', input_shape=(IMG_HEIGHT,IMG_WIDTH,1)))
model.add(MaxPool2D((2,2), padding='SAME'))
model.add(BatchNormalization())
model.add(Conv2D(64, (3,3), strides=(1,1), activation='relu',kernel_initializer='he_uniform', padding='SAME'))
model.add(MaxPool2D((2,2), padding='SAME'))
model.add(BatchNormalization())
model.add(Conv2D(64, (1,1), strides=(1,1), activation='relu',kernel_initializer='he_uniform', padding='SAME'))
model.add(MaxPool2D((2,2), padding='SAME'))
#model.add(AveragePooling2D((2,2), padding='SAME'))
model.add(BatchNormalization())
#model.add(Dropout(0.5))
model.add(Flatten())
model.add(Dense(128, activation='relu', kernel_initializer='he_uniform'))
model.add(Dense(32, activation='relu', kernel_initializer='he_uniform'))
model.add(Dense(1, activation='sigmoid'))

model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])

history = model.fit(train_data, epochs=10, verbose=0, validation_data=test_data, callbacks=cb)
print(history.history.keys())

model.summary()
loss, acc = model.evaluate(test_data,verbose=0)
print('Test Accuracy: %.3f' % acc)

model.save('my_model.h5')


plt.plot(history.history['accuracy'], label='Train Accuracy')
plt.plot(history.history['val_accuracy'], label = 'Val Accuracy')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.ylim([0.4, 1])
plt.legend(loc='upper left')
plt.savefig('acc_v_epoch.png')
plt.close()

plt.plot(history.history['loss'], label='Train Loss')
plt.plot(history.history['val_loss'], label = 'Val Loss')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.ylim([0.001, 10])
plt.yscale('log')
plt.legend(loc='upper right')
plt.savefig('loss_v_epoch.png')
plt.close()

#plt.plot(history.history['lr'], label='Learning Rate')
#plt.xlabel('Epoch')
#plt.ylabel('LR')
#plt.ylim([0.0000001, 0.01])
#plt.yscale('log')
#plt.legend(loc='upper right')
#plt.savefig('lr_v_epoch.png')
#plt.close()


