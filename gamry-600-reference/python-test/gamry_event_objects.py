class GamryDtaqEvents():
    def __init__(self, dtaq, pstat):
        self.dtaq = dtaq
        self.acquired_points = []
        self.pstat = pstat
        
    def cook(self):
        count = 1
        while count > 0:
            count, points = self.dtaq.Cook(10)
            # The columns exposed by GamryDtaq.Cook vary by dtaq and are
            # documented in the Toolkit Reference Manual.
            #https://docs.python.org/3/library/functions.html#zip
            print(points);
            self.acquired_points.extend(zip(*points))
        
    def _IGamryDtaqEvents_OnDataAvailable(self, this):
        self.cook()

    def _IGamryDtaqEvents_OnDataDone(self, this):
        self.cook() # a final cook
        self.pstat.cominterface.Close();

class GamryDeviceListEvents():
    def __init__(self, device_list):
        self.device_list = device_list
        
    def _IGamryDeviceListEvents_OnDeviceListChanged(self, this):
        self.device_list.devicelistchanged.emit()
        print("Device list changed");

    