class Animation(object):
    __metaclass__ = ABCMeta
    
    @abstractmethod
    def pre_animation(self):
        pass

    @abstractmethod
    def animate(self, timedelta):
        pass
