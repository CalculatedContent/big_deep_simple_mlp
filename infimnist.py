import os
from subprocess import Popen
INFIMNIST = '/Users/charlesmartin/packages/infimnist/infimnist -d /Users/charlesmartin/packages/infimnist/data '

class InfiMNIST(object):

	def __init__(self):
	        self.data_dir = "."
	        self._infimnist_start = 10000
	        self._infimnist_stop =  self._infimnist_start + 59999
	        
        def next_epoch(self):
               #print "creating infimnist pat files %d - %d" % (self._infimnist_start, self._infimnist_stop)
                lab_file = os.path.join(self.data_dir, 'infimnist-labels')
                pat_file = os.path.join(self.data_dir, 'infimnist-images')
	                
                # execute cmd
	                
                with open(lab_file, 'wb') as out:
                        cmd = "{} lab {} {} ".format(INFIMNIST, self._infimnist_start, self._infimnist_stop)
                        #print cmd
                        Popen(cmd, shell=True, stdout=out, cwd=self.data_dir).wait()
	                        
                with open(pat_file, 'wb') as out:
                        cmd = "{} pat {} {} ".format(INFIMNIST, self._infimnist_start, self._infimnist_stop)
                        #print cmd
	                Popen(cmd, shell=True, stdout=out, cwd=self.data_dir).wait()
                                
                cmd1 = "rm infimnist-labels.gz infimnist-images.gz mnist-labels.gz mnist-images.gz"
                cmd2 = "gzip -f infimnist-labels infimnist-images"
                cmd3 = "ln -s infimnist-labels.gz  mnist-labels.gz"
                cmd4 = "ln -s infimnist-images.gz  mnist-images.gz"
	                                
                os.system(cmd1)
                os.system(cmd2)
                os.system(cmd3)
                os.system(cmd4)
	                                
                self._infimnist_start = self._infimnist_stop + 1
                self._infimnist_stop =  self._infimnist_start + 59999
