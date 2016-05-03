class Animation(object):
    __metaclass__ = ABCMeta

    @abstractmethod
    def get_keyframe(self, timedelta):
        pass
