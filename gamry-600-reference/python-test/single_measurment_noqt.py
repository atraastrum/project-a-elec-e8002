import comtypes
import comtypes.client as client

class GamryDtaqEvents():
    def __init__(self, dtaq):
        self.dtaq = dtaq
        self.acquired_points = []
       
        
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
        

dtaqchrono=client.CreateObject('GamryCOM.GamryDtaqChrono')
dtaqsink = GamryDtaqEvents(dtaqchrono)

GamryCOM=client.GetModule(['{BD962F0D-A990-4823-9CF5-284D1CDD9C6D}', 1, 0])
devices=client.CreateObject('GamryCOM.GamryDeviceList')
print(devices.EnumSections())


pstat=client.CreateObject('GamryCOM.GamryPstat')
pstat.Init(devices.EnumSections()[0]) # grab first pstat
pstat.Open()
pstat.SetCtrlMode(GamryCOM.PstatMode)
pstat.SetCell(GamryCOM.CellOn)

dtaqchrono=client.CreateObject('GamryCOM.GamryDtaqChrono')
dtaqchrono.Init(pstat, GamryCOM.ChronoAmp)
dtaqsink = GamryDtaqEvents(dtaqchrono)
client.ShowEvents(dtaqcpiv)

#two-part step waveform
sigstep=client.CreateObject('GamryCOM.GamrySignalStep')
sigstep.Init(pstat, 0.5, 15, -0.1, 15, 0.01, GamryCOM.PstatMode)

pstat.SetSignal(sigstep)


try:
    dtaqchrono.Run(True)
except Exception as e:
    print("Big drama show")

client.PumpEvents(60)
print(len(dtaqsink.acquired_points))

del connection

pstat.Close()