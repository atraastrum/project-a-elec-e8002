import comtypes
import comtypes.client as client
GamryCOM=client.GetModule(['{BD962F0D-A990-4823-9CF5-284D1CDD9C6D}', 1, 0])
class GamryDtaqEvents(object):
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
            self.acquired_points.extend(zip(*points))
        
    def _IGamryDtaqEvents_OnDataAvailable(self, this):
        self.cook()

    def _IGamryDtaqEvents_OnDataDone(self, this):
        self.cook() # a final cook
        # TODO:  indicate completion to enclosing code?

devices=client.CreateObject('GamryCOM.GamryDeviceList')
print devices.EnumSections()


pstat=client.CreateObject('GamryCOM.GamryPstat')
pstat.Init(devices.EnumSections()[0]) # grab first pstat
pstat.SetCtrlMode(GamryCOM.PstatMode)



dtaqchrono=client.CreateObject('GamryCOM.GamryDtaqChrono')
dtaqchrono.Init(pstat, GamryCOM.ChronoAmp)

#two-part step waveform
sigstep=client.CreateObject('GamryCOM.GamrySignalStep')
sigstep.Init(pstat, 0.5, 15, -0.1, 15, 0.01, GamryCOM.PstatMode)

pstat.SetSignal(sigstep)
pstat.SetCell(GamryCOM.CellOn)

dtaqsink = GamryDtaqEvents(dtaqchrono)

client.ShowEvents(dtaqcpiv)
connection = client.GetEvents(dtaqcpiv, dtaqsink)

try:
    dtaqchrono.Run(True)
except Exception as e:
    print("Big drama show")

client.PumpEvents(1)
print len(dtaqsink.acquired_points)

del connection

pstat.Close()