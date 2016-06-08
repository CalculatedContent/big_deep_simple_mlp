# big_deep_simple_mlp


This is an attempt to use TensorFlow to reproduce the Big, Deep, Simple MLP 

http://arxiv.org/pdf/1003.0358.pdf

The idea is simple. They claim to get state-of-the-art accuarcy on MNIST using a 5-layer MLP, but running a large number of epochs with just SGD, a decaying learnng rate, and an augmented data set.

This paper still appears to be 1 of the top 10 results in deep learning

http://rodrigob.github.io/are_we_there_yet/build/classification_datasets_results.html


The key idea is that the augmented data set can provide, in practice, an infinite amount of training data.

I am trying to repeat this experiment using Tensorflow and 2 kinds of augmented data sets.

### Requirements

We will use 2 different data augementation methods

#### InfiMNIST

 http://leon.bottou.org/projects/infimnist

 Install infimnist and set the path in infimnist.py  

#### AlignMNIST

 http://people.csail.mit.edu/freifeld/cpab/poster_ICCV2015.pdf

 http://www2.compute.dtu.dk/~sohau/augmentations/

 Download alignmnist.npz	

 Test with

 - AlignMNIST-test.ipynb


### Run these notebooks next

run this notebook first to create and test augmentmnist.py

- AugmentMNIST.ipynb

then

- 2-Layer-MLP-AlignMNiST.ipynb

- 2-Layer-MLP-InfiMNiST.ipynb  


### Results so far:

I have run 75 epochs of AlignMNIST using RMSProp for a 2 layer and 5 layer MLP

the resulting accuracies are much lower than reported in the paper

https://github.com/CalculatedContent/big_deep_simple_mlp/blob/master/2-Layer-MLP-AlignMNiST.ipynb

https://github.com/CalculatedContent/big_deep_simple_mlp/blob/master/5-Layer-MLP-AlignMNiST.ipynb

https://github.com/CalculatedContent/big_deep_simple_mlp/blob/master/2-Layer-MLP-InfiMNiST.ipynb



The initial result suggest that having a very good augmentation scheme matters, as the AlignMNIST data is much more generalizable than the InfiMNIST data. Although one has to be careful to look for information leakage, and it would be good to double check that the AlignMNIST does not actually include deformations of the test data.





