def include(path):
    pass


def call(name, *argv):
    pass


def constant(name):
    pass


def globals(name):
    pass


class Reference:
    def __init__(self):
        pass

    def get(self):
        return "name"


class Object:
    def __init__(self, class_name, *args):
        pass

    def get(self, name):
        pass

    def set(self, name, value):
        pass

    def call(self, name, *args):
        pass


class Class:
    def __init__(self, class_name):
        pass

    def get(self, name):
        pass

    def set(self, name, value):
        pass

    def new(self, *args):
        pass
