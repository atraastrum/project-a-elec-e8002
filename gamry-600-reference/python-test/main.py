# Main entry of the program
#import sys
#import os
#print(os.environ['PATH'])
#sys.path.append("C:\\Users\\boris\\Documents\\Project-A\\my-python-env\\Lib\\site-packages\\PyQt5\Qt\\bin") 
#sys.path.append("C:\\Users\\boris\\Documents\\Project-A\\my-python-env\\Lib\\site-packages\\PyQt5\Qt\\bin\\plugins\\platforms") 
#C:\Users\boris\AppData\Local\Programs\Python\Python36

if __name__ == "__main__":
  import sys
  from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout, QGroupBox, QHBoxLayout, QComboBox, QVBoxLayout
  from gamry import GamryDeviceList, GamryPstat

  class MainWindow(QWidget):
    def __init__(self, parent=None):
      QWidget.__init__(self, parent)
      self.resize(600, 600)
      self.move(300, 300)
      self.setWindowTitle("Gamry Control Application")

      # Create UI
      self.ui_grid = QVBoxLayout(self)

      ui_choose_device_gbox = QGroupBox("Device List")
      ui_hbox = QHBoxLayout()
      self.ui_choose_device_label = QLabel("N/A")
      self.ui_choose_device_combobox = QComboBox();
      ui_hbox.addWidget(self.ui_choose_device_label)
      ui_hbox.addWidget(self.ui_choose_device_combobox)
      ui_choose_device_gbox.setLayout(ui_hbox)  
      
      ui_potentiostat_gbox = QGroupBox("Potentiostat parameters")
      self.ui_ptstat_serial_number_label = QLabel("Serial Number: N/A")
      ui_hbox = QHBoxLayout()
      ui_hbox.addWidget(self.ui_ptstat_serial_number_label)
      ui_potentiostat_gbox.setLayout(ui_hbox)

      ui_stepsignal_gbox = QGroupBox("Step signal parameters")
      
      ui_data_gbox = QGroupBox("Measurment")

      self.ui_grid.addWidget(ui_choose_device_gbox)
      self.ui_grid.addWidget(ui_potentiostat_gbox)
      self.ui_grid.addWidget(ui_stepsignal_gbox)
      self.ui_grid.addWidget(ui_data_gbox)

      # Create Gamry Objects 
      self.gm_device_list = GamryDeviceList()
      self.gm_device_list.devicelistchanged.connect(self.update_device_list);
      self.update_device_list()
    
      self.gm_potentiostat = None

    def update_device_list(self):
      if self.gm_device_list.cominterface.Count() > 0:
        labels = self.gm_device_list.EnumLabels()
        sections = self.gm_device_list.EnumSections()

        self.ui_choose_device_label.setText("Selected " + labels[0]);

        if self.gm_potentiostat == None: 
          self.gm_potentiostat = GamryPstat(sections[0])
          srn = SerialNo()
          self.ui_ptstat_serial_number_label.setText("Serial Number: " + srn)
      else:
        self.ui_choose_device_label.setText("No devices are connected");    
      
      

  app = QApplication(sys.argv)
  mw = MainWindow()
  mw.show()
  sys.exit(app.exec_())
 


