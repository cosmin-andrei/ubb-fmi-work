class Baller:

    def __init__(self, __id_baller, __name, __value):
        self.__id_baller = __id_baller
        self.__name = __name
        self.__value = __value

    def get_id_baller(self):
        return self.__id_baller

    def get_name(self):
        return self.__name

    def get_value(self):
        return self.__value

    def __str__(self):
        return f"{self.__id_baller},{self.__name},{self.__value}"