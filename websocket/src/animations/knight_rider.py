class KnightRider(Animation):
    def __init__(self, **kwargs):
        self.start = kwargs.get("begin", 17)
        self.width = kwargs.get("width", 8)
        self.end = kwargs.get("end", 90-12-self.width)

        self.index = self.start
        self.dir = 1
    
    def pre_animation(self):
        self.index = self.start
        self.dir = 1

    def animate(self, timedelta):
        res = {r:0,g:0,b:0}*90
        for x in range(self.size):
            bs[(x+i)*3]["r"] = 29
            bs[(x+i)*3]["g"] = 66
            bs[(x+i)*3]["b"] = 138

        self.index += 1

        if self.index >= self.end or self.index <= self.start:
            self.index = self.end
            self.dir = -self.dir

        return res
