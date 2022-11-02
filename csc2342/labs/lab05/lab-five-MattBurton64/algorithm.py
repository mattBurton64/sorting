class Algorithm:
    """
    A class to represent an algorithm.

    ...
    Attributes
    ----------
    
    Methods
    -------
    sort()
        outputs a sorted list of integers

    """

    def sort(self, data, length): #(data, n):
        """ Outputs a sorted list of integers
        Parameters
        ----------
        data : list
            a collection of integers as a list

        length : integer
            an integer value representing the len() of the data list
        """
        
        if length == 1:
            print(data)
            return
        
        for i in range(length):
            self.sort(data, length - 1)
            if length % 2 == 0:
                data[i], data[length - 1] = data[length - 1], data[i]
            else:
                data[0], data[length - 1] = data[length - 1], data[0]
