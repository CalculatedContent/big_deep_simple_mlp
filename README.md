# big_deep_simple_mlp
Attempt to use TensorFlow to reproduce the Big, Deep, Simple MLP 

http://arxiv.org/pdf/1003.0358.pdf


Using infinimist to generate the data

http://leon.bottou.org/projects/infimnist

<pre>
infimnist/infimnist pat 10000 8109999 > mnist8m-patterns-idx3-ubyte
infimnist/infimnist lab 10000 8109999 > mnist8m-labels-idx1-ubyte

infimnist/infimnist pat 10000 810999 > mnist800k-patterns-idx3-ubyte
infimnist/infimnist lab 10000 810999 > mnist800k-labels-idx1-ubyte

infimnist/infimnist pat  0 9999 > mnist10k-patterns-idx3-ubyte
infimnist/infimnist lab 0 9999 > mnist10k-labels-idx1-ubyte

gzip mnist*
</pre>






