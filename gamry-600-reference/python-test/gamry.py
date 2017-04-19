import PyQt5.QtCore  
import comtypes.client


GamryCOM = comtypes.client.GetModule(['{BD962F0D-A990-4823-9CF5-284D1CDD9C6D}', 1, 0])



from gamry_event_objects import GamryDeviceListEvents
class GamryDeviceList(PyQt5.QtCore.QObject):
  
  def __init__(self, parent=None):
    PyQt5.QtCore.QObject.__init__(self, parent)

    self.cominterface = comtypes.client.CreateObject('GamryCOM.GamryDeviceList')
    comtypes.client.ShowEvents(self.cominterface)
    sinkobj = GamryDeviceListEvents(self)
    comtypes.client.GetEvents(self.cominterface, sinkobj)

  devicelistchanged = PyQt5.QtCore.pyqtSignal()    


from gamry_event_objects import GamryDeviceListEvents

class GamryPstat(PyQt5.QtCore.QObject):
  
  def __init__(self, parent=None):
    PyQt5.QtCore.QObject.__init__(self, section_name, parent)

    self.cominterface = comtypes.client.CreateObject('GamryCOM.GamryPstat')
    self.cominterface.Init(section_name)  

    #comtypes.client.ShowEvents(self.cominterface)
    #sinkobj = GamryDeviceListEvents(self)
    #comtypes.client.GetEvents(self.cominterface, sinkobj)

  #changed = PyQt5.QtCore.pyqtSignal()  

  def startMeasurment(self):
    # Initialize the Pstat
    self.cominterface.Open()
    self.cominterface.SetCell(GamryCOM.CellOn)
    self.cominterface.SetCtrlMode(GamryCOM.PstatMode)

    # Initialize a Dtaq 
    dtaqchrono=client.CreateObject('GamryCOM.GamryDtaqChrono')
    dtaqchrono.Init(self.cominterface, GamryCOM.ChronoAmp)
    dtaqsink = GamryDtaqEvents(dtaqchrono, self)
    client.ShowEvents(dtaqchrono)
    client.GetEvents(dtaqchrono, dtaqsink)

    # Initialize a two-step wavefrom Signal 
    sigstep=client.CreateObject('GamryCOM.GamrySignalStep')
    sigstep.Init(self.cominterface, 0.5, 15, -0.1, 15, 0.01, GamryCOM.PstatMode)

    # Set Signal  
    self.cominterface.SetSignal(sigstep)

    # Acquire Data
    try:
      dtaqchrono.Run(True)
    except Exception as e:
      print("Big drama show")

    
    

