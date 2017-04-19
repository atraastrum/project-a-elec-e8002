# -*- coding: utf-8 -*-
import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton

if __name__ == '__main__':
  app = QApplication(sys.argv)

  # main window
  w = QWidget()
  w.resize(800, 600)
  w.move(300, 300)
  w.setWindowTitle('Simple')
  w.show()

  # button 
  b = QPushButton()
  b.setParent(w)
  b.setText("Some Text")
  b.resize(100, 20)
  b.show()

   
  sys.exit(app.exec_())