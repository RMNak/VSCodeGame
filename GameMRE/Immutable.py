#Create user defined Immutable class
class Immutable:
    def __init__(self, data):
        self.data = data

    def __setattr__(self, key, value):
        if key == 'data':
            super().__setattr__(key, value)
        else:
            raise AttributeError("Can't set attribute")

    def __delattr__(self, key):
        raise AttributeError("Can't delete attribute")

    def __repr__(self):
        return str(self.data)

    def __str__(self):
        return str(self.data)

    def __hash__(self):
        return hash(self.data)
    
    #write a method to reverse a string value
    def reverse(self):
        return self.data[::-1]