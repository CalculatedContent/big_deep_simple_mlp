import numpy as np

class AlignMNIST(object):

    def __init__(self, filename='alignmnist.npz'):
        self._alignmnist_start = 0
        self._alignmnist_stop =  self._alignmnist_start + 60000           
        self._data = np.load(filename, mmap_mode='r')
        
    # does not work
    def dense_to_one_hot(self, labels_dense, num_classes=10):
        """Convert class labels from scalars to one-hot vectors."""
        num_labels = labels_dense.shape[0]
        index_offset = np.arange(num_labels) * num_classes
        labels_one_hot = np.zeros((num_labels, num_classes))
        labels_one_hot.flat[index_offset + labels_dense.ravel()] = 1
        return labels_one_hot
    
    def reshape_images(self, images):
        #print images.shape[0], images.shape[1] * images.shape[2]
        images = images.reshape(images.shape[0], images.shape[1] * images.shape[2])
        # Convert from [0, 255] -> [0.0, 1.0].
        images = images.astype(np.float32)
        images = np.multiply(images, 1.0 / 255.0)
        return images
        
    def shuffle_epoch(self, images, labels):   
        num = labels.shape[0]
        pids = np.arange(num)
        np.random.shuffle(pids)
        images, labels = images[pids], labels[pids]
        return images, labels

    # we could also just use all the data instead of 55,000
    # but the first epoch is always the original data set
    def next_epoch(self):

        x = self._data['x']
        x = x[self._alignmnist_start:self._alignmnist_stop,:,:]
        y = self._data['y']
        y = y.astype(int)
        y = y[self._alignmnist_start:self._alignmnist_stop]
        
        self._alignmnist_start += 60000
        self._alignmnist_stop += 60000

        #print x.shape, y.shape
        x = self.reshape_images(x)
        y = self.dense_to_one_hot(y)
        #print x.shape, y.shape
                
        x_train, y_train = x[0:55000,:], y[0:55000]
        x_test, y_test = x[55000:60000,:], y[55000:60000]

        #print x_train.shape, y_train.shape, x_test.shape, y_test.shape
        x_train, y_train = self.shuffle_epoch(x_train,y_train)
        #print x_train.shape, y_train.shape, x_test.shape, y_test.shape
        
        return x_train, y_train, x_test, y_test
