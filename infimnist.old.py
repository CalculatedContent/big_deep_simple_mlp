import os
import numpy as np
import logging
from subprocess import Popen


log = logging.getLogger("infimnist")


class InfiMNIST(object):
    '''
    The infinite MNIST dataset (formerly known as MNIST8M) [1, 2]
    http://leon.bottou.org/projects/infimnist

    References:
    [1]: Loosli, Gaelle, Stephane Canu, and Leon Bottou. "Training invariant
         support vector machines using selective sampling." Large scale kernel
         machines (2007): 301-320.
    [2]: Simard, Patrice, et al. "Tangent prop - a formalism for specifying
         selected invariances in an adaptive network." Advances in neural
         information processing systems. 1992.
    '''

    def __init__(self):
        self.data_dir = "."
        self._infimnist_start = 10000
        self._infimnist_stop = 0


    def next_epoch(self):
        log.info('next epoch')
        self._infimnist_start = self._infimnist_start + 50000
        self._infimnist_stop =  self._infimnist_start + 50000
        lab_file = os.path.join(self.data_dir, 'infimnist-labels-idx1-ubyte')
        pat_file = os.path.join(self.data_dir, 'infimnist-patterns-idx3-ubyte')
        with open(lab_file, 'wb') as out:
            Popen(['./infimnist', 'lab', str(self._infimnist_start),
                str(self._infimnist_stop)], stdout=out, cwd=self.data_dir).wait()
        with open(pat_file, 'wb') as out:
            Popen(['./infimnist', 'pat', str(self._infimnist_start),
                str(self._infimnist_stop)], stdout=out, cwd=self.data_dir).wait()

