# big_deep_simple_mlp


This is an attempt to use TensorFlow to reproduce the Big, Deep, Simple MLP 

http://arxiv.org/pdf/1003.0358.pdf

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

I am currently running 500 and 10,000 epochs of RMSProp using the InfiMNIST dataset now








